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
  // Create a char tab to store what's coming
  char inBuffer[4096];
  
  int bytesRead = _socket->read(inBuffer,4096,false);
  
  // If an error has been detected
  if (bytesRead == -1)
  {
    Logger::writeToLog("Error receiving command");
  }
  else
  {
    PimpMessage message (inBuffer);
    if (message.isCommand(PimpMessage::kPeerGetFile))
      handleSendRequest(message);
  }
  
  Logger::writeToLog("Finished PeerJobThread");
  _owner->triggerAsyncUpdate();
}

void PeerJobThread::handleSendRequest(const PimpMessage& request)
{
  if (request.hasPeerFile())
  {
    PimpMessage acknowledge (_owner->getLocalIp());
    PeerFile peerFile = request.getPeerFile();
    PeerFileManager *fileManager = _owner->getFileManager();
    
    FileInputStream streamFile (fileManager->getSharedFolder().getFullPathName() + juce::File::separator + peerFile.getFile().getFileName());
    
    if (fileManager->getAvailableFiles().contains(peerFile) &&
        streamFile.openedOk())
    {
      acknowledge.setCommand(PimpMessage::kReady);
      std::string out = acknowledge.getXmlString().toStdString();
      
      // Let's send him the acknowledge
      _socket->write(out.c_str(), out.length());
      
      if (request.hasByteRange())
      {
        
      }
      else
      {
        int bytesRead;
        char inBuffer[4096];
        do
        {
          bytesRead = streamFile.read(inBuffer,4096);
          _socket->write(inBuffer, bytesRead);
        } while (bytesRead == 4096);
      }
    }
    else
    {
      acknowledge.setCommand(PimpMessage::kError);
      std::string out = acknowledge.getXmlString().toStdString();
      // Let's send him the acknowledge
      _socket->write(out.c_str(), out.length());
    }
  }
}