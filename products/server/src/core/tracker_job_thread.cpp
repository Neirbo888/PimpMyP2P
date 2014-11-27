/*
  ==============================================================================

    tracker_job_thread.cpp
    Created: 24 Nov 2014 8:00:12am
    Author:  Adrien Tisseraud

  ==============================================================================
*/

#include "products/server/src/core/tracker_job_thread.h"
#include "products/server/src/core/tracker_message_handler.h"
#include "products/server/src/core/tracker_file_manager.h"

TrackerJobThread::TrackerJobThread(TrackerMessageHandler *owner,
                                   juce::StreamingSocket *socket)
: Thread("TrackerJobThread"),
_owner(owner),
_socket(socket)
{
  startThread();
}

TrackerJobThread::~TrackerJobThread()
{
  stop();
}

void TrackerJobThread::stop() {
  _socket->close();
  signalThreadShouldExit();
  stopThread(2000);
}

void TrackerJobThread::run()
{
  // Create a char tab to store what's coming
  juce::String in;
  int bytesRead;
  char inBuffer[4096];
  do
  {
    bytesRead = _socket->read(inBuffer,4096,false);
    in += juce::String(inBuffer,bytesRead);
  } while (bytesRead == 4096);
  
  // If an error has been detected
  if (bytesRead == -1)
  {
    Logger::writeToLog("Error receiving command");
  }
  else
  {
    PimpMessage message (in.toStdString());
    if (message.isCommand(PimpMessage::kPeerSearch))
      handleSearchRequest(message);
    else if (message.isPeerRefresh())
      handlePeerRefresh(message);
    else if (message.isPeerSignOut())
      handlePeerSignOut(message);
    else
      Logger::writeToLog("Error no handler");
  }
  
  _socket->close();
  
  _owner->triggerAsyncUpdate();
  Logger::writeToLog("Finished TrackerJobThread");
}

void TrackerJobThread::handleSearchRequest(const PimpMessage& request)
{
  // Create an acknowledge
  PimpMessage acknowledge (_owner->getLocalIp());
  
  juce::String searchString;
  if (request.hasSearchString())
  {
    searchString = request.getSearchString();
  
    // Send our peer that we've received his request and will be processing
    acknowledge.setCommand(PimpMessage::kOk);
    acknowledge.sendToSocket(_socket);
    
    juce::Array<PeerFile> searchResults;
    searchResults = _owner->getFileManager().getSimilarFiles(searchString);
    
    PimpMessage resultMessage (_owner->getLocalIp());
    resultMessage.createTrackerSearchResult(searchResults);
    resultMessage.sendToSocket(_socket);
  }
  else
  {
    acknowledge.createErrorMessage("Can't find searchstring");
    acknowledge.sendToSocket(_socket);
  }
}

void TrackerJobThread::handlePeerRefresh(const PimpMessage &request)
{
  // Create an acknowledge
  PimpMessage acknowledge (_owner->getLocalIp());
  const juce::IPAddress peerIP = request.getSource();
  
  // If the peer ip is valid, well let's register him and let him know
  if (peerIP.toString() != "0.0.0.0")
  {
    _owner->getFileManager().registerPeer(peerIP);
    acknowledge.setCommand(PimpMessage::kOk);
    acknowledge.sendToSocket(_socket);
    if (request.hasLocalFileList())
    {
      _owner->getFileManager().cleanPeer(peerIP);
      juce::Array<PeerFile>& array = _owner->getFileManager().getAvailableFiles();
      for (PeerFile p : request.getLocalFileList())
      {
        if (array.contains(p))
        {
          int index = array.indexOf(p);
          array.getReference(index).addPeer(peerIP);
        }
        else
        {
          p.addPeer(peerIP);
          array.add(p);
        }
      }
      for (PeerFile p : _owner->getFileManager().getAvailableFiles())
      {
        std::cout << p << std::endl;
      }
    }
  }
  // Else, let him know that something went wrong
  else
  {
    acknowledge.setCommand(PimpMessage::kError);
  }
  acknowledge.sendToSocket(_socket);
}

void TrackerJobThread::handlePeerSignOut(const PimpMessage &request)
{
  const juce::IPAddress peerIP = request.getSource();
  if (peerIP.toString() != "0.0.0.0")
  {
    _owner->getFileManager().unregisterPeer(peerIP);
  }
}