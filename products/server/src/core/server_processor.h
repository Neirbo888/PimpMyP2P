#ifndef PIMP_PROCESSOR_H_INCLUDED
#define PIMP_PROCESSOR_H_INCLUDED

#include "JuceHeader.h"

/// Forward declarations
class ComponentWindow;

/// @class PimpServerProcessor
/// @brief Heart of the pimp server
class PimpServerProcessor
: public ActionListener
{
public:
  /// @brief Constructor
  PimpServerProcessor();
  
  /// @brief Destructor
  ~PimpServerProcessor();
  
  /// @brief ActionListener callback
  void actionListenerCallback (const String& message);
  
private:
  ScopedPointer<ComponentWindow> _window; ///< Window displaying the GUI
  juce::Component* _component; ///< The proper gui
};



#endif  // PIMP_PROCESSOR_H_INCLUDED
