#ifndef PEER_PROCESSOR_H_INCLUDED
#define PEER_PROCESSOR_H_INCLUDED

#include "JuceHeader.h"
#include "products/client/src/core/peer_file_manager.h"

/// Forward declarations
class ComponentWindow;
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
  
  /// @brief Datagram thread
  void run();
  
  /// @brief Stop the receiver thread
  void stop();
  
  /// @brief Get the file manager
  PeerFileManager* const getFileManager() { return _fileManager; }
  
  /// @brief Sends a PeerGetFile request to a peer
  void sendPeerGetFile(juce::IPAddress destination, PeerFile file);
  
  /// @brief Sends a PeerSearch request to the tracker
  void sendTrackerSearch(juce::StringArray keyword);
  
private:
  juce::IPAddress _address; ///< Local ip address
  juce::IPAddress _tracker; ///< IP Address of the tracker
  
  juce::Component* _component; ///< GUI
  juce::ScopedPointer<ComponentWindow> _window; ///< Window displaying the GUI
  
  juce::ScopedPointer<PeerMessageHandler> _messageHandler; ///< MessageHandler for tcp requests
  juce::ScopedPointer<PeerFileManager> _fileManager;
  
  juce::ScopedPointer<SocketThread> _socketThread; ///< Thread handling TCP requests
  
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PeerProcessor)
};



#endif  // PEER_PROCESSOR_H_INCLUDED
