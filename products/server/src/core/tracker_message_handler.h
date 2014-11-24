/*
  ==============================================================================

    tracker_message_handler.h
    Created: 24 Nov 2014 7:59:59am
    Author:  Adrien Tisseraud

  ==============================================================================
*/

#ifndef TRACKER_MESSAGE_HANDLER_H_INCLUDED
#define TRACKER_MESSAGE_HANDLER_H_INCLUDED


#include "JuceHeader.h"
#include "products/common/messages/message_handler.h"
#include "products/server/src/core/tracker_file_manager.h"

/// @class TrackerMessageHandler
/// @brief Specific handler for tracker related requests
class TrackerMessageHandler
: public MessageHandler
{
public:
  /// @brief Constructor
  TrackerMessageHandler(juce::IPAddress local,
                        const TrackerFileManager& fileManager);
  
  /// @brief Destructor
  ~TrackerMessageHandler();
  
  /// @see MessageHandler::spawnNewJob
  void spawnNewJob(StreamingSocket* socket);
  
private:
  /// @brief Owner's file manager
  const TrackerFileManager& _fileManager;
  
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TrackerMessageHandler)
};


#endif  // TRACKER_MESSAGE_HANDLER_H_INCLUDED
