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
  
private:
  ScopedPointer<ComponentWindow> _window; ///< Window displaying the GUI
  File _sharedFolder;
  juce::Component* _component; ///< The proper gui
};



#endif  // PIMP_PROCESSOR_H_INCLUDED
