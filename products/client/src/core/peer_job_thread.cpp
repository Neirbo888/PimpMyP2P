/*
  ==============================================================================

    client_message_handler.cpp
    Created: 19 Nov 2014 5:13:59pm
    Author:  Adrien Tisseraud

  ==============================================================================
*/

#include "products/client/src/core/peer_job_thread.h"
#include "products/client/src/core/peer_message_handler.h"
#include "products/client/src/core/peer_file_manager.h"

PeerJobThread::PeerJobThread(PeerMessageHandler *owner,
                             juce::StreamingSocket *socket)
: Thread("PeerJobThread"),
  _owner(owner),
  _socket(socket)
{
  startThread();
}

PeerJobThread::~PeerJobThread()
{
  stop();
}

void PeerJobThread::stop() {
  _socket->close();
  signalThreadShouldExit();
  stopThread(2000);
}

void PeerJobThread::run()
{
  PimpMessage message = PimpMessage::createFromSocket(_socket);
  
  // If an error has been detected
  if (message.isCommand(PimpMessage::kError))
  {
    Logger::writeToLog("Error receiving command");
  }
  else
  {
    if (message.isCommand(PimpMessage::kPeerGetFile))
      handleSendRequest(message);
  }
  
  _socket->close();
  
  Logger::writeToLog("Finished PeerJobThread");
  _owner->triggerAsyncUpdate();
}

void PeerJobThread::handleSendRequest(const PimpMessage& request)
{
  if (request.hasPeerFile())
  {
    // Create an acknowledge message to be sent to our connected host
    PimpMessage acknowledge (_owner->getLocalIp());
    bool hasFile = false, hasValidPart = false, canBeOpened = false;
    
    // First thing, we need to check if we have the requested file
    const PeerFile peerFile = request.getPeerFile();
    
    // We bring our filemanager for that
    const PeerFileManager& fileManager = _owner->getFileManager();
    const juce::String path (fileManager.getSharedFolder().getFullPathName() +
                             juce::File::separator +
                             peerFile.getFilename());
    juce::FileInputStream streamFile (path);
    
    // Check the available files list with our requested file
    if (fileManager.getAvailableFiles().contains(peerFile))
      hasFile = true;
    
    // Check if the given range is valid if there is one
    if (request.hasByteRange())
    {
      Range<int> range = request.getByteRange();
      if (range.getLength() <= peerFile.getSize() &&
          range.getStart() >= 0 &&
          range.getStart() < peerFile.getSize() &&
          range.getEnd() > 0 &&
          range.getEnd() <= peerFile.getSize())
        hasValidPart = true;
    }
    else
      hasValidPart = true;
    
    if (streamFile.openedOk())
      canBeOpened = true;
    
    if (hasFile && hasValidPart && canBeOpened)
    {
      acknowledge.setCommand(PimpMessage::kOk);
      acknowledge.sendToSocket(_socket);
      
      int bytesRead;
      int totalSent = 0;
      int sizeToBeRead;
      int bytesToSend;
      
      if (request.hasByteRange())
      {
        Range<int> range = request.getByteRange();
        streamFile.setPosition(range.getStart());
        sizeToBeRead = range.getLength();
      }
      else
        sizeToBeRead = peerFile.getSize();
      
      do
      {
        juce::MemoryBlock buffer (4096, true);
        
        if (sizeToBeRead - totalSent < 4096)
          bytesToSend = sizeToBeRead - totalSent;
        else
          bytesToSend = 4096;
        
        bytesRead = streamFile.read(buffer.getData(), bytesToSend);
        _socket->write(buffer.getData(), bytesRead);
        
        totalSent += bytesRead;
      } while (totalSent != sizeToBeRead);
    }
    
    else
    {
      acknowledge.createErrorMessage("Something went wrong");
      acknowledge.sendToSocket(_socket);
    }
  }
}