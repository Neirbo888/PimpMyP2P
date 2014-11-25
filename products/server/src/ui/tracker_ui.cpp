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

//[Headers] You can add your own extra header files here...
#include "products/server/src/core/tracker_processor.h"
//[/Headers]

#include "tracker_ui.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
TrackerUi::TrackerUi (TrackerProcessor* processor)
    : _processor(processor)
{
    addAndMakeVisible (_labelSearchField = new Label ("Search Field Label",
                                                      TRANS("Search :")));
    _labelSearchField->setFont (Font ("Helvetica", 11.00f, Font::plain));
    _labelSearchField->setJustificationType (Justification::centredRight);
    _labelSearchField->setEditable (false, false, false);
    _labelSearchField->setColour (Label::textColourId, Colour (0xff595f66));
    _labelSearchField->setColour (TextEditor::textColourId, Colours::black);
    _labelSearchField->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (_editorSearchField = new TextEditor ("Search Field Editor"));
    _editorSearchField->setMultiLine (false);
    _editorSearchField->setReturnKeyStartsNewLine (false);
    _editorSearchField->setReadOnly (false);
    _editorSearchField->setScrollbarsShown (false);
    _editorSearchField->setCaretVisible (false);
    _editorSearchField->setPopupMenuEnabled (false);
    _editorSearchField->setText (String::empty);

    addAndMakeVisible (_buttonSetDownloadFolder = new TextButton ("Set Download Folder Button"));
    _buttonSetDownloadFolder->setButtonText (TRANS("Folder"));
    _buttonSetDownloadFolder->addListener (this);

    addAndMakeVisible (_buttonSearch = new TextButton ("Search Button"));
    _buttonSearch->setButtonText (TRANS("Search"));
    _buttonSearch->addListener (this);


    //[UserPreSize]
  // Create look and feel
  LookAndFeel::setDefaultLookAndFeel(&_lookAndFeel);
    //[/UserPreSize]

    setSize (300, 500);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

TrackerUi::~TrackerUi()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    _labelSearchField = nullptr;
    _editorSearchField = nullptr;
    _buttonSetDownloadFolder = nullptr;
    _buttonSearch = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void TrackerUi::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::gainsboro);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void TrackerUi::resized()
{
    _labelSearchField->setBounds (216, 144, 60, 24);
    _editorSearchField->setBounds (8, 467, 200, 24);
    _buttonSetDownloadFolder->setBounds (196, 8, 96, 24);
    _buttonSearch->setBounds (220, 467, 72, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void TrackerUi::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == _buttonSetDownloadFolder)
    {
        //[UserButtonCode__buttonSetDownloadFolder] -- add your button handler code here..

        //[/UserButtonCode__buttonSetDownloadFolder]
    }
    else if (buttonThatWasClicked == _buttonSearch)
    {
        //[UserButtonCode__buttonSearch] -- add your button handler code here..
        //[/UserButtonCode__buttonSearch]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="TrackerUi" componentName=""
                 parentClasses="public Component" constructorParams="TrackerProcessor* processor"
                 variableInitialisers="_processor(processor)" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="1" initialWidth="300"
                 initialHeight="500">
  <BACKGROUND backgroundColour="ffdcdcdc"/>
  <LABEL name="Search Field Label" id="d25be79670612cf1" memberName="_labelSearchField"
         virtualName="" explicitFocusOrder="0" pos="216 144 60 24" textCol="ff595f66"
         edTextCol="ff000000" edBkgCol="0" labelText="Search :" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Helvetica"
         fontsize="11" bold="0" italic="0" justification="34"/>
  <TEXTEDITOR name="Search Field Editor" id="67e851ba8745bfe6" memberName="_editorSearchField"
              virtualName="" explicitFocusOrder="0" pos="8 467 200 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="0"
              caret="0" popupmenu="0"/>
  <TEXTBUTTON name="Set Download Folder Button" id="a74c01732164b671" memberName="_buttonSetDownloadFolder"
              virtualName="" explicitFocusOrder="0" pos="196 8 96 24" buttonText="Folder"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="Search Button" id="718de0990a41ea4e" memberName="_buttonSearch"
              virtualName="" explicitFocusOrder="0" pos="220 467 72 24" buttonText="Search"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
