#ifndef TRACKER_PROCESSOR_H_INCLUDED
#define TRACKER_PROCESSOR_H_INCLUDED

#include "JuceHeader.h"
#include "products/server/src/core/tracker_file_manager.h"

#include "peer_file.h"

/// Forward declarations
class ComponentWindow;
class TrackerMessageHandler;
class SocketThread;

/// @class TrackerProcessor
/// @brief Heart of the pimp server
class TrackerProcessor
: public juce::ActionListener,
  public juce::AsyncUpdater,
  public juce::Thread
{
public:
  /// @brief Constructor
  TrackerProcessor();
  
  /// @brief Destructor
  ~TrackerProcessor();
  
  /// @brief ActionListener callback
  void actionListenerCallback (const String& message);
  
  /// @brief Callback that is called everytime a change is detected in the file
  /// system
  void handleAsyncUpdate();
  
  /// @brief TrackerProcessor thread
  void run();
  
  /// @brief Stops the running Tracker thread
  void stop();
  
private:
  /// @brief Should be initialized with the current LAN IP of this computer,
  /// assuming it's a Class C network. Otherwise, it should be the loopback IP.
  juce::IPAddress _address;
  /// @brief FileManager keeping track of the files available on different peers
  TrackerFileManager _fileManager;
  /// @brief Spawns threads each time a TCP connection is made to handle the
  /// request
  ScopedPointer<TrackerMessageHandler> _messageHandler;
  /// @brief GUI
  juce::Component* _component;
  /// @brief Window displaying the GUI
  ScopedPointer<ComponentWindow> _window;
  /// @brief Thread listening the TCP socket
  ScopedPointer<SocketThread> _socketThread;
};



#endif  // TRACKER_PROCESSOR_H_INCLUDED
