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

// THIS MUST BE DELETED (maybe)
#include "products/common/files/peer_file.h"
//[/Headers]

#include "peer_ui.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
PeerUi::PeerUi (PeerProcessor* processor)
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

    addAndMakeVisible (_buttonSetFolder = new TextButton ("Set Folder Button"));
    _buttonSetFolder->setButtonText (TRANS("Set Folder"));
    _buttonSetFolder->addListener (this);

    addAndMakeVisible (_buttonSearch = new TextButton ("Search Button"));
    _buttonSearch->setButtonText (TRANS("Search"));
    _buttonSearch->addListener (this);

    addAndMakeVisible (_pimpTable = new PimpTable (this));
    _pimpTable->setName ("Pimp Table");

    addAndMakeVisible (_buttonConnect = new TextButton ("Connect Button"));
    _buttonConnect->setButtonText (TRANS("Connect"));
    _buttonConnect->addListener (this);

    addAndMakeVisible (_editorTrackerIP = new TextEditor ("Tracker IP Editor"));
    _editorTrackerIP->setMultiLine (false);
    _editorTrackerIP->setReturnKeyStartsNewLine (false);
    _editorTrackerIP->setReadOnly (false);
    _editorTrackerIP->setScrollbarsShown (false);
    _editorTrackerIP->setCaretVisible (false);
    _editorTrackerIP->setPopupMenuEnabled (false);
    _editorTrackerIP->setText (String::empty);

    addAndMakeVisible (_buttonDisconnect = new TextButton ("Disconnect Button"));
    _buttonDisconnect->setButtonText (TRANS("Disconnect"));
    _buttonDisconnect->addListener (this);


    //[UserPreSize]
  // Create look and feel
  LookAndFeel::setDefaultLookAndFeel(&_lookAndFeel);
  _editorSearchField->addListener(this);
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
  setName("PimpMyMainWindow");
    //[/Constructor]
}

PeerUi::~PeerUi()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    _labelSearchField = nullptr;
    _editorSearchField = nullptr;
    _buttonSetFolder = nullptr;
    _buttonSearch = nullptr;
    _pimpTable = nullptr;
    _buttonConnect = nullptr;
    _editorTrackerIP = nullptr;
    _buttonDisconnect = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void PeerUi::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::gainsboro);

    //[UserPaint] Add your own custom painting code here..
  if (_processor->getState() == PeerProcessor::kRegistered)
  {
    g.setColour (Colour (0xffffd776));
    g.fillEllipse (231.0f, 16.0f, 8.0f, 8.0f);
  }
  else
  {
    g.setColour (Colour (0xff99a3ff));
    g.fillEllipse (231.0f, 16.0f, 8.0f, 8.0f);
  }
    //[/UserPaint]
}

void PeerUi::resized()
{
    _labelSearchField->setBounds (8, 8, 60, 24);
    _editorSearchField->setBounds (getWidth() - 96 - proportionOfWidth (0.4000f), getHeight() - 8 - 24, proportionOfWidth (0.4000f), 24);
    _buttonSetFolder->setBounds (getWidth() - 8 - 96, 8, 96, 24);
    _buttonSearch->setBounds (getWidth() - 8 - 80, getHeight() - 8 - 24, 80, 24);
    _pimpTable->setBounds (8, 40, getWidth() - 16, getHeight() - 80);
    _buttonConnect->setBounds (getWidth() - 112 - 72, 8, 72, 24);
    _editorTrackerIP->setBounds (getWidth() - 192 - proportionOfWidth (0.2667f), getHeight() - 368 - 24, proportionOfWidth (0.2667f), 24);
    _buttonDisconnect->setBounds (getWidth() - 112 - 72, 8, 72, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void PeerUi::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == _buttonSetFolder)
    {
        //[UserButtonCode__buttonSetFolder] -- add your button handler code here..
      FileChooser chooser("Choose a directory to open",File::nonexistent,"",true);
      if (chooser.browseForDirectory())
      {
        juce::File outputDir = chooser.getResult();
        _processor->setSharedFolder(outputDir);
      }
        //[/UserButtonCode__buttonSetFolder]
    }
    else if (buttonThatWasClicked == _buttonSearch)
    {
        //[UserButtonCode__buttonSearch] -- add your button handler code here..
        if (_editorSearchField->getTotalNumChars() > 2)
          _processor->sendTrackerSearch(_editorSearchField->getText());
        //[/UserButtonCode__buttonSearch]
    }
    else if (buttonThatWasClicked == _buttonConnect)
    {
        //[UserButtonCode__buttonConnect] -- add your button handler code here..
      if (_editorTrackerIP->getText() != "0.0.0.0")
      {
        _processor->setTrackerIp(juce::IPAddress (_editorTrackerIP->getText()));
        _processor->setState(PeerProcessor::kShouldRegister);
      }
        //[/UserButtonCode__buttonConnect]
    }
    else if (buttonThatWasClicked == _buttonDisconnect)
    {
        //[UserButtonCode__buttonDisconnect] -- add your button handler code here..
      _processor->unregisterToTracker();
        //[/UserButtonCode__buttonDisconnect]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void PeerUi::UpdateUi()
{
  switch (_processor->getState()) {
    case PeerProcessor::kUnavailable:
      _buttonConnect->setEnabled(false);
      _buttonConnect->setVisible(true);
      _buttonDisconnect->setEnabled(false);
      _buttonDisconnect->setVisible(false);
      _buttonSearch->setEnabled(false);
      _buttonSetFolder->setEnabled(true);
      _editorSearchField->setEnabled(false);
      _editorTrackerIP->setEnabled(false);
      break;
    case PeerProcessor::kIdle:
      _buttonSearch->setEnabled(false);
      _buttonConnect->setEnabled(true);
      _buttonConnect->setVisible(true);
      _buttonDisconnect->setEnabled(false);
      _buttonDisconnect->setVisible(false);
      _editorTrackerIP->setEnabled(true);
      _editorSearchField->setEnabled(false);
      break;
    case PeerProcessor::kShouldRegister:
      _buttonSearch->setEnabled(false);
      _editorSearchField->setEnabled(false);
      _buttonConnect->setEnabled(false);
      _buttonConnect->setEnabled(false);
      _buttonConnect->setVisible(false);
      _buttonDisconnect->setEnabled(false);
      _buttonDisconnect->setVisible(false);
      break;
    case PeerProcessor::kRegistered:
      _buttonConnect->setEnabled(false);
      _buttonConnect->setVisible(false);
      _buttonDisconnect->setEnabled(true);
      _buttonDisconnect->setVisible(true);
      _buttonSearch->setEnabled(true);
      _buttonConnect->setEnabled(true);
      _editorSearchField->setEnabled(true);
      break;
    default:
      break;
  }
  repaint();
}

void PeerUi::changeListenerCallback(juce::ChangeBroadcaster *source)
{
  if (source == _pimpTable)
    _processor->queuePeerFileTask(_pimpTable->getSelectedFile());
  else if (source == _processor)
    UpdateUi();
}

void PeerUi::publishSearchResults(juce::Array<PeerFile> results)
{
  _pimpTable->loadData(results);
}

void PeerUi::textEditorReturnKeyPressed (TextEditor& editor)
{
  if (editor.getName() == _editorSearchField->getName())
  {
    if (_editorSearchField->getTotalNumChars() > 2)
      _processor->sendTrackerSearch(_editorSearchField->getText());
  }
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="PeerUi" componentName=""
                 parentClasses="public juce::Component, public juce::ChangeListener, public juce::TextEditor::Listener"
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
  <TEXTBUTTON name="Set Folder Button" id="a74c01732164b671" memberName="_buttonSetFolder"
              virtualName="" explicitFocusOrder="0" pos="8Rr 8 96 24" buttonText="Set Folder"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="Search Button" id="718de0990a41ea4e" memberName="_buttonSearch"
              virtualName="" explicitFocusOrder="0" pos="8Rr 8Rr 80 24" buttonText="Search"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <GENERICCOMPONENT name="Pimp Table" id="8d2da6dba96a2b23" memberName="_pimpTable"
                    virtualName="" explicitFocusOrder="0" pos="8 40 16M 80M" class="PimpTable"
                    params="this"/>
  <TEXTBUTTON name="Connect Button" id="7e7d4511e4a51ca9" memberName="_buttonConnect"
              virtualName="" explicitFocusOrder="0" pos="112Rr 8 72 24" buttonText="Connect"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTEDITOR name="Tracker IP Editor" id="152c82c01ae8cf62" memberName="_editorTrackerIP"
              virtualName="" explicitFocusOrder="0" pos="192Rr 368Rr 26.667% 24"
              initialText="" multiline="0" retKeyStartsLine="0" readonly="0"
              scrollbars="0" caret="0" popupmenu="0"/>
  <TEXTBUTTON name="Disconnect Button" id="99a70b8a258bd7c6" memberName="_buttonDisconnect"
              virtualName="" explicitFocusOrder="0" pos="112Rr 8 72 24" buttonText="Disconnect"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
