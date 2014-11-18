#ifndef PIMP_PROCESSOR_H_INCLUDED
#define PIMP_PROCESSOR_H_INCLUDED

#include "JuceHeader.h"

/// Forward declarations
class ComponentWindow;

/// @class PimpClientProcessor
/// @brief Heart of the pimp client
class PimpClientProcessor
: public juce::ActionListener,
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
  
private:
  ScopedPointer<ComponentWindow> _window; ///< Window displaying the GUI
  juce::File _sharedFolder;
  bool _connected;
  juce::Component* _component; ///< The proper gui
  juce::StreamingSocket _socket;
  std::vector<juce::File> _files;
};



#endif  // PIMP_PROCESSOR_H_INCLUDED
