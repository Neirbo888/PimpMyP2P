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
#include "products/client/src/core/peer_processor.h"
#include "products/client/src/core/peer_file_manager.h"
#include "products/client/src/ui/pimp_table.h"
//[/Headers]

#include "main_window.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
MainWindow::MainWindow (PeerProcessor* processor)
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
    addAndMakeVisible (_pimpTable = new PimpTable (this));
    _pimpTable->setName ("Pimp Table");


    //[UserPreSize]
  // Create look and feel
  LookAndFeel::setDefaultLookAndFeel(&_lookAndFeel);
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
  setName("PimpMyMainWindow");
    //[/Constructor]
}

MainWindow::~MainWindow()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    _labelSearchField = nullptr;
    _editorSearchField = nullptr;
    _buttonSetDownloadFolder = nullptr;
    _buttonSearch = nullptr;
    _pimpTable = nullptr;


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
    _labelSearchField->setBounds (8, 8, 60, 24);
    _editorSearchField->setBounds (getWidth() - 96 - proportionOfWidth (0.4000f), getHeight() - 8 - 24, proportionOfWidth (0.4000f), 24);
    _buttonSetDownloadFolder->setBounds (getWidth() - 8 - 96, 8, 96, 24);
    _buttonSearch->setBounds (getWidth() - 8 - 80, getHeight() - 8 - 24, 80, 24);
    _pimpTable->setBounds (8, 40, getWidth() - 16, getHeight() - 80);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void MainWindow::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == _buttonSetDownloadFolder)
    {
        //[UserButtonCode__buttonSetDownloadFolder] -- add your button handler code here..
        FileChooser chooser("Choose a directory to open",File::nonexistent,"",true);
        if (chooser.browseForDirectory())
        {
          juce::File outputDir = chooser.getResult();
          _processor->setSharedFolder(outputDir);
        }
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
void MainWindow::changeListenerCallback(juce::ChangeBroadcaster *source)
{
  if (source == _pimpTable)
  {
    _processor->sendPeerGetFile(_pimpTable->getSelectedFile());
  }
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="MainWindow" componentName=""
                 parentClasses="public juce::Component, public juce::ChangeListener"
                 constructorParams="PeerProcessor* processor" variableInitialisers="_processor(processor)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ffdcdcdc"/>
  <LABEL name="Search Field Label" id="d25be79670612cf1" memberName="_labelSearchField"
         virtualName="" explicitFocusOrder="0" pos="8 8 60 24" textCol="ff595f66"
         edTextCol="ff000000" edBkgCol="0" labelText="Search :" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Helvetica"
         fontsize="11" bold="0" italic="0" justification="34"/>
  <TEXTEDITOR name="Search Field Editor" id="67e851ba8745bfe6" memberName="_editorSearchField"
              virtualName="" explicitFocusOrder="0" pos="96Rr 8Rr 40% 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="0"
              caret="0" popupmenu="0"/>
  <TEXTBUTTON name="Set Download Folder Button" id="a74c01732164b671" memberName="_buttonSetDownloadFolder"
              virtualName="" explicitFocusOrder="0" pos="8Rr 8 96 24" buttonText="Folder"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="Search Button" id="718de0990a41ea4e" memberName="_buttonSearch"
              virtualName="" explicitFocusOrder="0" pos="8Rr 8Rr 80 24" buttonText="Search"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <GENERICCOMPONENT name="Pimp Table" id="8d2da6dba96a2b23" memberName="_pimpTable"
                    virtualName="" explicitFocusOrder="0" pos="8 40 16M 80M" class="PimpTable"
                    params="this"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
