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
    
    // Check if the file can be opened on the filesystem
    if (streamFile.openedOk())
      canBeOpened = true;
    
    // If everything's good, well let's just say we're ready to send
    if (hasFile && hasValidPart && canBeOpened)
    {
      acknowledge.setCommand(PimpMessage::kOk);
      acknowledge.sendToSocket(_socket);
      
      // And we can start to send the file
      int bytesRead;
      char inBuffer[4096];
      
      // If it's a part upload, we must calculate the range to send
      if (request.hasByteRange())
      {
        // First we retrieve our range
        Range<int> range = request.getByteRange();
        
        // We must keep track of how much data we've sent, starting at 0
        int totalSent = 0;
        
        // Set the read head to the start position in the file
        streamFile.setPosition(range.getStart());
        do
        {
          int sizeToBeSent;
          
          // An arbitrary choice of mine, I chose that my packet size must not
          // be over 4096 bytes.
          if (range.getLength() - totalSent > 4096)
            sizeToBeSent = 4096;
          else
            sizeToBeSent = range.getLength() - totalSent;
          
          // Read the fixed amount of data in the file stream
          bytesRead = streamFile.read(inBuffer, sizeToBeSent);
          
          // And write it directly in the socket
          _socket->write(inBuffer, bytesRead);
          
          // Increment our data counter and iterate
          totalSent += bytesRead;
        } while (totalSent != range.getLength());
      }
      else
      {
        do
        {
          bytesRead = streamFile.read(inBuffer,4096);
          _socket->write(inBuffer, bytesRead);
        } while (bytesRead == 4096);
      }
    }
    
    // If something went wrong, let's be good here and tell our connected host
    // that there was an error and we're going to shut him off real soon
    else
    {
      acknowledge.createErrorMessage("Something went wrong");
      acknowledge.sendToSocket(_socket);
    }
  }
}