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
#include "products/tcp_sender/src/core/tcpsender_processor.h"
//[/Headers]

#include "main_window.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
MainWindow::MainWindow (TcpSenderProcessor* processor)
    : _processor(processor)
{
    addAndMakeVisible (_buttonSend = new TextButton ("Send Button"));
    _buttonSend->setButtonText (TRANS("Send"));
    _buttonSend->addListener (this);

    addAndMakeVisible (_labelIPEditor = new Label ("IP Editor Label",
                                                   TRANS("Ip to connect to :")));
    _labelIPEditor->setFont (Font ("Helvetica", 11.00f, Font::plain));
    _labelIPEditor->setJustificationType (Justification::centredRight);
    _labelIPEditor->setEditable (false, false, false);
    _labelIPEditor->setColour (Label::textColourId, Colour (0xff595f66));
    _labelIPEditor->setColour (TextEditor::textColourId, Colours::black);
    _labelIPEditor->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (_editorIP = new TextEditor ("IP Editor"));
    _editorIP->setMultiLine (false);
    _editorIP->setReturnKeyStartsNewLine (false);
    _editorIP->setReadOnly (false);
    _editorIP->setScrollbarsShown (false);
    _editorIP->setCaretVisible (false);
    _editorIP->setPopupMenuEnabled (false);
    _editorIP->setText (TRANS("127.0.0.1:4807"));

    addAndMakeVisible (_editorString = new TextEditor ("String Editor"));
    _editorString->setMultiLine (false);
    _editorString->setReturnKeyStartsNewLine (false);
    _editorString->setReadOnly (false);
    _editorString->setScrollbarsShown (false);
    _editorString->setCaretVisible (false);
    _editorString->setPopupMenuEnabled (false);
    _editorString->setText (TRANS("lol kikoolol"));

    addAndMakeVisible (_labelStringEditor = new Label ("String Editor Label",
                                                       TRANS("String to send")));
    _labelStringEditor->setFont (Font ("Helvetica", 11.00f, Font::plain));
    _labelStringEditor->setJustificationType (Justification::centredRight);
    _labelStringEditor->setEditable (false, false, false);
    _labelStringEditor->setColour (Label::textColourId, Colour (0xff595f66));
    _labelStringEditor->setColour (TextEditor::textColourId, Colours::black);
    _labelStringEditor->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


    //[UserPreSize]
  // Create look and feel
  LookAndFeel::setDefaultLookAndFeel(&_lookAndFeel);
    //[/UserPreSize]

    setSize (440, 80);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

MainWindow::~MainWindow()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    _buttonSend = nullptr;
    _labelIPEditor = nullptr;
    _editorIP = nullptr;
    _editorString = nullptr;
    _labelStringEditor = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void MainWindow::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::gainsboro);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void MainWindow::resized()
{
    _buttonSend->setBounds (328, 8, 96, 56);
    _labelIPEditor->setBounds (8, 8, 96, 24);
    _editorIP->setBounds (112, 8, 200, 24);
    _editorString->setBounds (112, 40, 200, 24);
    _labelStringEditor->setBounds (8, 40, 96, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void MainWindow::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == _buttonSend)
    {
        //[UserButtonCode__buttonSend] -- add your button handler code here..
      _processor->send(_editorIP->getText(),
                       _editorString->getText());
        //[/UserButtonCode__buttonSend]
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

<JUCER_COMPONENT documentType="Component" className="MainWindow" componentName=""
                 parentClasses="public Component" constructorParams="TcpSenderProcessor* processor"
                 variableInitialisers="_processor(processor)" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="1" initialWidth="440"
                 initialHeight="80">
  <BACKGROUND backgroundColour="ffdcdcdc"/>
  <TEXTBUTTON name="Send Button" id="718de0990a41ea4e" memberName="_buttonSend"
              virtualName="" explicitFocusOrder="0" pos="328 8 96 56" buttonText="Send"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <LABEL name="IP Editor Label" id="d25be79670612cf1" memberName="_labelIPEditor"
         virtualName="" explicitFocusOrder="0" pos="8 8 96 24" textCol="ff595f66"
         edTextCol="ff000000" edBkgCol="0" labelText="Ip to connect to :"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Helvetica" fontsize="11" bold="0" italic="0" justification="34"/>
  <TEXTEDITOR name="IP Editor" id="67e851ba8745bfe6" memberName="_editorIP"
              virtualName="" explicitFocusOrder="0" pos="112 8 200 24" initialText="127.0.0.1:4807"
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="0"
              caret="0" popupmenu="0"/>
  <TEXTEDITOR name="String Editor" id="546f9ecf18c33f55" memberName="_editorString"
              virtualName="" explicitFocusOrder="0" pos="112 40 200 24" initialText="lol kikoolol"
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="0"
              caret="0" popupmenu="0"/>
  <LABEL name="String Editor Label" id="1239fa73147f3912" memberName="_labelStringEditor"
         virtualName="" explicitFocusOrder="0" pos="8 40 96 24" textCol="ff595f66"
         edTextCol="ff000000" edBkgCol="0" labelText="String to send"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Helvetica" fontsize="11" bold="0" italic="0" justification="34"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
