#ifndef PEER_PROCESSOR_H_INCLUDED
#define PEER_PROCESSOR_H_INCLUDED

#include "JuceHeader.h"
#include "products/client/src/core/peer_file_manager.h"

/// Forward declarations
class ComponentWindow;
class MainWindow;
class PeerMessageHandler;
class SocketThread;

/// @class PeerProcessor
/// @brief Heart of the pimp client
class PeerProcessor
: public juce::ActionListener,
  public juce::Thread,
  public juce::AsyncUpdater
{
public:
  /// @brief Constructor
  PeerProcessor();
  
  /// @brief Destructor
  ~PeerProcessor();
  
  /// @brief ActionListener callback
  void actionListenerCallback (const String& message);
  
  /// @brief Callback that is called everytime a change is detected in the file
  /// system
  void handleAsyncUpdate();
  
  /// @brief PeerProcessor thread
  void run();
  
  /// @brief Stop the receiver thread
  void stop();
  
  /// @brief Get the file manager
  const PeerFileManager& getFileManager() { return _fileManager; }
  
  /// @brief Sends a PeerGetFile request to a peer
  void sendPeerGetFile(PeerFile file);
  
  /// @brief Sends a PeerSearch request to the tracker
  /// @param {juce::String} keystring - KeyString that will be sent to the
  /// tracker
  void sendTrackerSearch(const juce::String keystring);
  
  /// @brief Set the shared folder
  /// @param {juce::File} folder - The new shared folder
  void setSharedFolder(const juce::File& folder);
  
private:
  /// @brief Should be initialized with the current LAN IP of this computer,
  /// assuming it's a Class C network. Otherwise, it should be the loopback IP.
  juce::IPAddress _address;
  /// @brief IP Address of the tracker
  juce::IPAddress _tracker;
  /// @brief FileManager keeping track of the files in the shared folder
  PeerFileManager _fileManager;
  /// @brief Spawns threads each time a TCP connection is made to handle the
  /// request
  ScopedPointer<PeerMessageHandler> _messageHandler;
  /// @brief GUI
  MainWindow* _component;
  /// @brief Window displaying the GUI
  ScopedPointer<ComponentWindow> _window;
  /// @brief Thread listening the TCP socket
  ScopedPointer<SocketThread> _socketThread;
  
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PeerProcessor)
};



#endif  // PEER_PROCESSOR_H_INCLUDED
