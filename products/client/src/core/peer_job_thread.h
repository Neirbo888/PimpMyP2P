/*
  ==============================================================================

    client_message_handler.h
    Created: 19 Nov 2014 5:13:59pm
    Author:  Adrien Tisseraud

  ==============================================================================
*/

#ifndef PEER_JOB_THREAD_H_INCLUDED
#define PEER_JOB_THREAD_H_INCLUDED

#include "products/common/messages/pimp_message.h"

// Forward declarations
class PeerMessageHandler;

/// @class PeerJobThread
/// @brief Thread handling the different requests a peer can receive
class PeerJobThread
: public juce::Thread
{
public:
  /// @brief Constructor
  /// @param {PeerMessageHandler*} owner - Handler that has spawned this thread
  /// @param {juce::StreamingSocket} socket - Socket related to this request,
  /// will be deleted when this job is done
  PeerJobThread(PeerMessageHandler* owner,
                juce::StreamingSocket *socket);
  
  /// @brief Destructor
  ~PeerJobThread();
  
  /// @brief Run method for the handler thread
  void run();
  
  /// @brief Stop the running PeerJobThread
  void stop();
  
  /// @brief Handler for sending files to a client
  void handleSendRequest(const PimpMessage& request);
  
private:
  /// @brief Handler that has spawned this thread
  PeerMessageHandler *_owner;
  /// @brief TCP socket
  ScopedPointer<StreamingSocket> _socket;
  
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PeerJobThread)
};

#endif  // PEER_JOB_THREAD_H_INCLUDED
