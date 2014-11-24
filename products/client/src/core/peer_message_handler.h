/*
  ==============================================================================

    peer_message_handler.h
    Created: 19 Nov 2014 7:01:37pm
    Author:  Adrien Tisseraud

  ==============================================================================
*/

#ifndef PEER_MESSAGE_HANDLER_H_INCLUDED
#define PEER_MESSAGE_HANDLER_H_INCLUDED

#include "JuceHeader.h"
#include "products/common/messages/message_handler.h"

// Forward declarations
class PeerFileManager;

/// @class PeerMessageHandler
/// @brief Specific handler for peers related requests
class PeerMessageHandler
: public MessageHandler
{
public:
  /// @brief Constructor
  PeerMessageHandler(juce::IPAddress local, const PeerFileManager& fileManager);
  
  /// @brief Destructor
  ~PeerMessageHandler();
  
  /// @see MessageHandler::spawnNewJob
  void spawnNewJob(StreamingSocket* socket);
  
  /// @brief Get the file handler
  const PeerFileManager& getFileManager() { return _fileManager; }
  
private:
  /// @brief Owner's file manager
  const PeerFileManager& _fileManager;
  
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PeerMessageHandler)
};

#endif  // PEER_MESSAGE_HANDLER_H_INCLUDED
