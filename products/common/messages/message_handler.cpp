/*
  ==============================================================================

    message_handler.cpp
    Created: 19 Nov 2014 5:13:40pm
    Author:  Adrien Tisseraud

  ==============================================================================
*/

#include "products/common/messages/message_handler.h"

MessageHandler::MessageHandler(juce::IPAddress local)
: _local(local) {}

MessageHandler::MessageHandler() {}

MessageHandler::~MessageHandler()
{
  clear();
}

void MessageHandler::handleAsyncUpdate()
{
  for (int i = _threads.size(); --i >= 0;)
    if (!_threads.getReference(i)->isThreadRunning())
    {
      deleteAndZero(_threads.getReference(i));
      _threads.remove(i);
    }
}

void MessageHandler::clear()
{
  for (auto thread : _threads)
  {
    thread->signalThreadShouldExit();
    thread->stopThread(2000);
    deleteAndZero(thread);
  }
  _threads.clear();
}