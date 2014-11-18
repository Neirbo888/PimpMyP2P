/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 3.1.0

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-13 by Raw Material Software Ltd.

  ==============================================================================
*/

#ifndef __JUCE_HEADER_1200E0CE2CF00B59__
#define __JUCE_HEADER_1200E0CE2CF00B59__

//[Headers]     -- You can add your own extra header files here --
#include "JuceHeader.h"
#include "products/common/ui/look_and_feel.h"

class TcpSenderProcessor;
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class MainWindow  : public Component,
                    public ButtonListener
{
public:
    //==============================================================================
    MainWindow (TcpSenderProcessor* processor);
    ~MainWindow();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void buttonClicked (Button* buttonThatWasClicked);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    PimpLookAndFeel _lookAndFeel;
    TcpSenderProcessor* _processor;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<TextButton> _buttonSend;
    ScopedPointer<Label> _labelIPEditor;
    ScopedPointer<TextEditor> _editorIP;
    ScopedPointer<TextEditor> _editorString;
    ScopedPointer<Label> _labelStringEditor;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainWindow)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_1200E0CE2CF00B59__
