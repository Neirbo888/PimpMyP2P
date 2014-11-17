#ifndef __audiogaming_component_window__
#define __audiogaming_component_window__


#include "JuceHeader.h"

/// @class  Component Window
/// @brief  A top level window able to hold a component and show it
/// @author Adrien Tisseraud
class ComponentWindow
: public TopLevelWindow
{
 public:
  /// @brief Constructor
  /// @param[in] associatedComponent  The component held by the window
  ComponentWindow(Component* associatedComponent, bool closeOnClick = true);
  
  /// @brief Destructor
  ~ComponentWindow();
  
  /// @brief Paint routine
  void paint(juce::Graphics &g);
  
  /// @brief Resize routine placing the window at the centre of its parent
  void resized();
  
  /// @brief Component getter
  juce::Component* getAssociatedComponent() { return _component; }
  
  /// @brief Mouse callback
  void mouseDown(const juce::MouseEvent& event);
  
  /// @brief Show the window
  void showWindow();
  
  /// @brief Hide the window
  void hideWindow();
  
 protected:
  juce::Colour _base_colour;
  
 private:
  ScopedPointer<Component> _component;
};

#endif  // __audiogaming_component_window__
