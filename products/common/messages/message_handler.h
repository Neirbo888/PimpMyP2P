/*
  ==============================================================================

    message_handler.h
    Created: 19 Nov 2014 5:13:40pm
    Author:  Adrien Tisseraud

  ==============================================================================
*/

#ifndef MESSAGE_HANDLER_H_INCLUDED
#define MESSAGE_HANDLER_H_INCLUDED

#include "JuceHeader.h"

/// @class MessageHandler
/// @brief Abstract class spawning threads when TCP requests are received, must
/// be derived and customize by either a Tracker or a Peer or something else ?
class MessageHandler
: public juce::AsyncUpdater
{
public:
  /// @brief Destructor
  virtual ~MessageHandler();
  
  /// @brief Callback that is called everytime a thread dies
  virtual void handleAsyncUpdate();
  
  /// @brief The SocketThread calls this method each time a TCP request is
  /// received, this causes a new thread to be spawned to handle the request
  virtual void spawnNewJob(StreamingSocket* socket) = 0;
  
  /// @brief Return the local IP
  const IPAddress& getLocalIp() { return _local; }
  
  /// @brief Clears the current thread list
  void clear();
  
protected:
  /// @brief Construct a MessageHandler with the local IPAdress
  MessageHandler(juce::IPAddress local);
  
  juce::Array<juce::Thread*> _threads; ///< Running threads spawned by this handler
  juce::IPAddress _local; ///< Local ip address
  
private:
  /// @brief Default constructor is private
  MessageHandler();
};

#endif  // MESSAGE_HANDLER_H_INCLUDED
