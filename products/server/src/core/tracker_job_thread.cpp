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
  
  if (message.isError())
    Logger::writeToLog("Error receiving command");
  else
  {
    if (message.isPeerSearch())
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
  juce::String searchString;
  if (request.hasSearchString())
  {
    searchString = request.getSearchString();
  
    // Send our peer that we've received his request and will be processing
    PimpMessage acknowledge = PimpMessage::createOk();
    acknowledge.sendToSocket(_socket, _owner->getLocalIp());
    
    juce::Array<PeerFile> searchResults;
    searchResults = _owner->getFileManager().getSimilarFiles(searchString);
    
    PimpMessage resultMessage = PimpMessage::createTrackerSearchResult(searchResults);
    resultMessage.sendToSocket(_socket, _owner->getLocalIp());
  }
  else
  {
    PimpMessage error = PimpMessage::createErrorMessage("Can't find searchstring");
    error.sendToSocket(_socket, _owner->getLocalIp());
  }
}

void TrackerJobThread::handlePeerRefresh(const PimpMessage &request)
{
  const juce::IPAddress peerIP = request.getSource();
  
  if (peerIP.toString() != "0.0.0.0")
  {
    _owner->getFileManager().registerPeer(peerIP);
    PimpMessage acknowledge = PimpMessage::createOk();
    acknowledge.sendToSocket(_socket, _owner->getLocalIp());
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
    PimpMessage error = PimpMessage::createErrorMessage("Error handling peer refresh");
    error.sendToSocket(_socket, _owner->getLocalIp());
  }
}

void TrackerJobThread::handlePeerSignOut(const PimpMessage &request)
{
  const juce::IPAddress peerIP = request.getSource();
  if (peerIP.toString() != "0.0.0.0")
  {
    _owner->getFileManager().unregisterPeer(peerIP);
  }
}