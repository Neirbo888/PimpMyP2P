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
                                                      TRANS("PimpMyP2P Tracker")));
    _labelSearchField->setFont (Font ("Helvetica", 27.90f, Font::plain));
    _labelSearchField->setJustificationType (Justification::centred);
    _labelSearchField->setEditable (false, false, false);
    _labelSearchField->setColour (Label::textColourId, Colour (0xff595f66));
    _labelSearchField->setColour (TextEditor::textColourId, Colours::black);
    _labelSearchField->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


    //[UserPreSize]
  // Create look and feel
  LookAndFeel::setDefaultLookAndFeel(&_lookAndFeel);
    //[/UserPreSize]

    setSize (300, 100);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

TrackerUi::~TrackerUi()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    _labelSearchField = nullptr;


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
    _labelSearchField->setBounds (0, 0, 300, 100);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
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
                 initialHeight="100">
  <BACKGROUND backgroundColour="ffdcdcdc"/>
  <LABEL name="Search Field Label" id="d25be79670612cf1" memberName="_labelSearchField"
         virtualName="" explicitFocusOrder="0" pos="0 0 300 100" textCol="ff595f66"
         edTextCol="ff000000" edBkgCol="0" labelText="PimpMyP2P Tracker"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Helvetica" fontsize="27.899999999999998579" bold="0"
         italic="0" justification="36"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
