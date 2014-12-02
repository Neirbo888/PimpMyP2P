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
      handlePeerFileRequest(message);
  }
  
  _socket->close();
  
  Logger::writeToLog("Finished PeerJobThread");
  _owner->triggerAsyncUpdate();
}

void PeerJobThread::handlePeerFileRequest(const PimpMessage& request)
{
  
}