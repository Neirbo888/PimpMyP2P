/*
  ==============================================================================

    peer_message_handler.cpp
    Created: 19 Nov 2014 7:01:37pm
    Author:  Adrien Tisseraud

  ==============================================================================
*/

#include "products/client/src/core/peer_message_handler.h"
#include "products/client/src/core/peer_job_thread.h"
#include "products/client/src/core/peer_file_manager.h"

PeerMessageHandler::PeerMessageHandler(juce::IPAddress local,
                                       PeerFileManager *fileManager)
: MessageHandler(local) {}

PeerMessageHandler::~PeerMessageHandler() {}

void PeerMessageHandler::spawnNewJob(juce::StreamingSocket *socket)
{
  PeerJobThread* job = new PeerJobThread(this, socket);
  _threads.add(job);
}