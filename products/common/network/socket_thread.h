/*
  ==============================================================================

    socket_thread.h
    Created: 19 Nov 2014 6:21:51pm
    Author:  Adrien Tisseraud

  ==============================================================================
*/

#ifndef SOCKET_THREAD_H_INCLUDED
#define SOCKET_THREAD_H_INCLUDED

#include "JuceHeader.h"
#include "products/common/messages/message_handler.h"

/// @class SocketThread
/// @brief Thread handling TCP requests from network and spawning handlers
/// thread each time a new request is received
class SocketThread
: public juce::Thread
{
public:
  /// @brief Constructor
  /// {int} port - Listening port
  SocketThread(int port, MessageHandler* messageHandler);
  
  /// @brief Destructor
  ~SocketThread();
  
  /// @brief Thread's run method
  void run();
  
  /// @brief Stop the running SocketThread
  void stop();
  
  /// @brief Must be true, otherwise the thread can't start
  const bool isConnected() const { return _connected; }
  
private:
  MessageHandler* _messageHandler;
  ScopedPointer<StreamingSocket> _socket;
  bool _connected; ///< Must be true
};


#endif  // SOCKET_THREAD_H_INCLUDED
