#ifndef PIMP_PROCESSOR_H_INCLUDED
#define PIMP_PROCESSOR_H_INCLUDED

#include "JuceHeader.h"
#include "products/common/messages/pimp_message.h"

/// Forward declarations
class ComponentWindow;

/// @class PimpClientProcessor
/// @brief Heart of the pimp client
class PimpClientProcessor
: public juce::ActionListener,
  public juce::ActionBroadcaster,
  public juce::Thread
{
public:
  /// @brief Constructor
  PimpClientProcessor();
  
  /// @brief Destructor
  ~PimpClientProcessor();
  
  /// @brief ActionListener callback
  void actionListenerCallback (const String& message);
  
  /// @brief Set the share directory
  void setSharedFolder(juce::File folder);

  /// @brief Scan the share directory to retrieve file list
  void scanSharedFolder();
  
  /// @brief Datagram thread
  void run();
  
  /// @brief Stop the receiver thread
  void stop();
  
  /// @brief Handler for sending files to a client
  void handleSendRequest(const PimpMessage& request, StreamingSocket* socket);
  
  /// @brief Send a PeerGetFile request to a peer
  void sendPeerGetFile(juce::IPAddress destination, juce::String filename);
  
private:
  IPAddress _address; ///< Local ip address
  juce::Component* _component; ///< The proper gui
  ScopedPointer<ComponentWindow> _window; ///< Window displaying the GUI
  juce::File _sharedFolder;
  bool _connected;
  juce::StreamingSocket _socket; ///< TCP socket
  std::vector<juce::File> _files;
  
};



#endif  // PIMP_PROCESSOR_H_INCLUDED
