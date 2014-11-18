#ifndef LOOK_AND_FEEL_H_INCLUDED
#define LOOK_AND_FEEL_H_INCLUDED

#include "JuceHeader.h"

class PimpLookAndFeel
: public juce::LookAndFeel_V3
{
 public:
  PimpLookAndFeel();
  ~PimpLookAndFeel();
  
  virtual void drawButtonText (Graphics& g, TextButton& button,
                               bool isMouseOverButton, bool isButtonDown);
  
  virtual void drawToggleButton (Graphics& g, ToggleButton& button,
                                 bool isMouseOverButton, bool isButtonDown);
  
  virtual void drawTextEditorOutline (Graphics& g, int width, int height,
                                      TextEditor& textEditor);
  
  virtual void drawButtonBackground (Graphics&, Button&,
                                     const Colour& backgroundColour,
                                     bool isMouseOverButton, bool isButtonDown);
  
  virtual void fillTextEditorBackground (Graphics& g, int width, int height,
                                         TextEditor& textEditor);
  
  virtual juce::Label* createSliderTextBox (Slider& slider);
  
  virtual void drawFileBrowserRow (Graphics& g, int width, int height,
                                   const String& filename, Image* icon,
                                   const String& fileSizeDescription,
                                   const String& fileTimeDescription,
                                   const bool isDirectory,
                                   const bool isItemSelected,
                                   const int itemIndex,
                                   DirectoryContentsDisplayComponent& dcc);
  
  virtual void drawScrollbar (Graphics& g, ScrollBar& scrollbar, int x, int y,
                              int width, int height, bool isScrollbarVertical,
                              int thumbStartPosition, int thumbSize,
                              bool isMouseOver, bool isMouseDown);
  
  virtual void drawProgressBar (Graphics& g, ProgressBar& progressBar,
                                int width, int height, double progress,
                                const String& textToShow);
  
  virtual juce::Font getComboBoxFont (ComboBox& box);
  
 private:
  class SliderLabelComp;
};

#endif  // LOOK_AND_FEEL_H_INCLUDED
