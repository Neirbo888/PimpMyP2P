#ifndef __audiogaming_component_window__
#define __audiogaming_component_window__


#include "JuceHeader.h"

/// @class  Component Window
/// @brief  A top level window able to hold a component and show it
/// @author Adrien Tisseraud
class ComponentWindow
: public DocumentWindow
{
 public:
  /// @brief Constructor
  /// @param[in] associatedComponent  The component held by the window
  ComponentWindow(Component* associatedComponent, bool closeOnClick = true);
  
  /// @brief Destructor
  ~ComponentWindow();
  
  /// @brief Component getter
  juce::Component* getAssociatedComponent() { return _component; }
  
  /// @brief Close button callback
  void closeButtonPressed();
  
 protected:
  /// @brief Base color for the UI
  juce::Colour _base_colour;
  
 private:
  juce::Component* _component;
};

#endif  // __audiogaming_component_window__
