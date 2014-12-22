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

#ifndef __JUCE_HEADER_8F90A442528F133__
#define __JUCE_HEADER_8F90A442528F133__

//[Headers]     -- You can add your own extra header files here --
#include "JuceHeader.h"
#include "products/common/ui/look_and_feel.h"

class PeerProcessor;
class PimpTable;
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class PeerUi  : public juce::Component,
                public juce::ChangeListener,
                public juce::TextEditor::Listener,
                public ButtonListener
{
public:
    //==============================================================================
    PeerUi (PeerProcessor* processor);
    ~PeerUi();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void changeListenerCallback(juce::ChangeBroadcaster *source);
    void UpdateUi();
    void publishSearchResults(juce::Array<PeerFile> results);
    void textEditorReturnKeyPressed (TextEditor&);
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void buttonClicked (Button* buttonThatWasClicked);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    PimpLookAndFeel _lookAndFeel;
    PeerProcessor* _processor;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<Label> _labelSearchField;
    ScopedPointer<TextEditor> _editorSearchField;
    ScopedPointer<TextButton> _buttonSetFolder;
    ScopedPointer<TextButton> _buttonSearch;
    ScopedPointer<PimpTable> _pimpTable;
    ScopedPointer<TextButton> _buttonConnect;
    ScopedPointer<TextEditor> _editorTrackerIP;
    ScopedPointer<TextButton> _buttonDisconnect;
    ScopedPointer<juce::ProgressBar> _progressBar;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PeerUi)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_8F90A442528F133__
