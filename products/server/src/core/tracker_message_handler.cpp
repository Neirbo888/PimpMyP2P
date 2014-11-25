/*
  ==============================================================================

    tracker_message_handler.cpp
    Created: 24 Nov 2014 7:59:59am
    Author:  Adrien Tisseraud

  ==============================================================================
*/

#include "products/server/src/core/tracker_message_handler.h"
#include "products/server/src/core/tracker_job_thread.h"
#include "products/server/src/core/tracker_file_manager.h"

TrackerMessageHandler::TrackerMessageHandler(juce::IPAddress local,
                                             TrackerFileManager& fileManager)
: MessageHandler(local),
_fileManager(fileManager) {}

TrackerMessageHandler::~TrackerMessageHandler() {}

void TrackerMessageHandler::spawnNewJob(juce::StreamingSocket *socket)
{
  auto job = new TrackerJobThread(this, socket);
  _threads.add(job);
}