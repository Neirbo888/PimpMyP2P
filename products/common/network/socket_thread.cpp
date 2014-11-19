/*
  ==============================================================================

    socket_thread.cpp
    Created: 19 Nov 2014 6:21:51pm
    Author:  Adrien Tisseraud

  ==============================================================================
*/

#include "products/common/network/socket_thread.h"
#include "products/common/messages/message_handler.h"

SocketThread::SocketThread(int port, MessageHandler* messageHandler)
: Thread("SocketThread"),
  _messageHandler(messageHandler),
  _socket(new StreamingSocket())
{
  _connected = _socket->createListener(port);
  startThread();
}

SocketThread::~SocketThread()
{
  stop();
  _socket = nullptr;
}

void SocketThread::stop() {
  _socket->close();
  signalThreadShouldExit();
  stopThread(2000);
}

void SocketThread::run()
{
  if (_connected)
  {
    Logger::writeToLog("Waiting for tcp connection on port 4807");
    while (!threadShouldExit())
    {
      // We wait here until a new connection has been made
      StreamingSocket* socket = _socket->waitForNextConnection();
      
      // If something was received we spawn a new job thread
      if (socket)
        _messageHandler->spawnNewJob(socket);
    }
  }
  Logger::writeToLog("Closing Socket thread");
}