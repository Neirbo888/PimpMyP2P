/*
  ==============================================================================

    tracker_job_thread.h
    Created: 24 Nov 2014 8:00:12am
    Author:  Adrien Tisseraud

  ==============================================================================
*/

#ifndef TRACKER_JOB_THREAD_H_INCLUDED
#define TRACKER_JOB_THREAD_H_INCLUDED

#include "products/common/messages/pimp_message.h"

// Forward declarations
class TrackerMessageHandler;

/// @class TrackerJobThread
/// @brief Thread handling the different requests a tracker can receive
class TrackerJobThread
: public juce::Thread
{
public:
  /// @brief Constructor
  /// @param {TrackerMessageHandler*} owner - Handler that has spawned this thread
  /// @param {juce::StreamingSocket} socket - Socket related to this request,
  /// will be deleted when this job is done
  TrackerJobThread(TrackerMessageHandler* owner,
                   juce::StreamingSocket *socket);
  
  /// @brief Destructor
  ~TrackerJobThread();
  
  /// @brief Run method for the handler thread
  void run();
  
  /// @brief Stop the running TrackerJobThread
  void stop();
  
  /// @brief Handler for search from a peer
  void handleSearchRequest(const PimpMessage& request);
  
private:
  /// @brief Handler that has spawned this thread
  TrackerMessageHandler *_owner;
  /// @brief TCP socket
  ScopedPointer<StreamingSocket> _socket;
  
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TrackerJobThread)
};

#endif  // TRACKER_JOB_THREAD_H_INCLUDED
