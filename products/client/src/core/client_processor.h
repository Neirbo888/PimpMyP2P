#ifndef PIMP_PROCESSOR_H_INCLUDED
#define PIMP_PROCESSOR_H_INCLUDED

#include "JuceHeader.h"

/// Forward declarations
class ComponentWindow;

/// @class PimpClientProcessor
/// @brief Heart of the pimp client
class PimpClientProcessor
: public ActionListener
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
  
private:
  ScopedPointer<ComponentWindow> _window; ///< Window displaying the GUI
  juce::File _sharedFolder;
  juce::Component* _component; ///< The proper gui
  std::vector<juce::File> _files;
};



#endif  // PIMP_PROCESSOR_H_INCLUDED
