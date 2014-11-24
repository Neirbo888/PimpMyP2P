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
    if (message.isCommand(PimpMessage::kPeerSearch))
      handleSearchRequest(message);
  }
  
  _socket->close();
  
  Logger::writeToLog("Finished TrackerJobThread");
  _owner->triggerAsyncUpdate();
}

void TrackerJobThread::handleSearchRequest(const PimpMessage& request)
{
  // Create an acknowledge
  PimpMessage acknowledge (_owner->getLocalIp());
  acknowledge.setCommand(PimpMessage::kOk);
  acknowledge.sendToSocket(_socket);
}