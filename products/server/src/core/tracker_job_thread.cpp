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
  PimpMessage message = PimpMessage::createFromSocket(_socket);
  
  if (message.isCommand(PimpMessage::kError))
    Logger::writeToLog("Error receiving command");
  else
  {
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
}

void TrackerJobThread::handleSearchRequest(const PimpMessage& request)
{
  Logger::writeToLog("Handling search request");
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
  Logger::writeToLog("Handling peer refresh");
  // Create an acknowledge
  PimpMessage acknowledge (_owner->getLocalIp());
  const juce::IPAddress peerIP = request.getSource();
  
  if (peerIP.toString() != "0.0.0.0")
  {
    _owner->getFileManager().registerPeer(peerIP);
    acknowledge.setCommand(PimpMessage::kOk);
    acknowledge.sendToSocket(_socket);
    if (request.hasLocalFileList())
    {
      _owner->getFileManager().cleanPeer(peerIP);
      juce::Array<PeerFile>& localFiles = _owner->getFileManager().getAvailableFiles();
      juce::Array<PeerFile> distantFiles = request.getLocalFileList();
      Logger::writeToLog("Peer has " + juce::String(distantFiles.size()) + " files");
      for (PeerFile p : distantFiles)
      {
        if (localFiles.contains(p))
        {
          int index = localFiles.indexOf(p);
          localFiles.getReference(index).addPeer(peerIP);
        }
        else
        {
          p.addPeer(peerIP);
          localFiles.add(p);
        }
      }
    }
  }
  // Else, let him know that something went wrong
  else
  {
    acknowledge.setCommand(PimpMessage::kError);
    acknowledge.sendToSocket(_socket);
  }
}

void TrackerJobThread::handlePeerSignOut(const PimpMessage &request)
{
  Logger::writeToLog("Handling peer signout");
  const juce::IPAddress peerIP = request.getSource();
  if (peerIP.toString() != "0.0.0.0")
  {
    _owner->getFileManager().unregisterPeer(peerIP);
  }
}