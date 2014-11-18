#ifndef TCP_SENDER_PROCESSOR_H_INCLUDED
#define TCP_SENDER_PROCESSOR_H_INCLUDED

#include "JuceHeader.h"

/// Forward declarations
class ComponentWindow;

/// @class TcpSenderProcessor
/// @brief Heart of the TCP sender
class TcpSenderProcessor
: public ActionListener
{
public:
  /// @brief Constructor
  TcpSenderProcessor();
  
  /// @brief Destructor
  ~TcpSenderProcessor();
  
  /// @brief ActionListener callback
  void actionListenerCallback (const String& message);
  
  /// @brief Send a TCP datagram
  void send(juce::String ip, juce::String message);
  
private:
  ScopedPointer<ComponentWindow> _window; ///< Window displaying the GUI
  juce::Component* _component; ///< The proper gui
  juce::StreamingSocket _socket; ///< Socket
};



#endif  // TCP_SENDER_PROCESSOR_H_INCLUDED
