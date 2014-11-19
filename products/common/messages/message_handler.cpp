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
  juce::Array<juce::Thread*> newThreadsArray;
  for (juce::Thread** thread = _threads.begin(); thread != _threads.end();
       thread++)
  {
    if ((*thread)->isThreadRunning())
      newThreadsArray.add(*thread);
    else
      deleteAndZero(*thread);
  }
  _threads.clear();
  _threads = newThreadsArray;
}

void MessageHandler::clear()
{
  for (juce::Thread** thread = _threads.begin(); thread != _threads.end();
       thread++)
  {
    (*thread)->signalThreadShouldExit();
    (*thread)->stopThread(2000);
    deleteAndZero(*thread);
  }
  _threads.clear();
}