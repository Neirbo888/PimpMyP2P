#include "products/common/ui/look_and_feel.h"

PimpLookAndFeel::PimpLookAndFeel()
{
  setColour(TextEditor::focusedOutlineColourId, juce::Colour(0xffa5bed5));
  setColour(TextEditor::backgroundColourId, juce::Colour(0xfff0f2f2));
  setColour(TextEditor::highlightColourId, juce::Colour(0xffa0a0a0));
  
  setColour(TextButton::buttonColourId, juce::Colour(0xffa5bed5));
  setColour(TextButton::textColourOffId, juce::Colour(0xff595f66));
  
  setColour(Slider::textBoxTextColourId, juce::Colour(0xff595f66));
  setColour(Slider::textBoxHighlightColourId, juce::Colour(0xffa0a0a0));
  
  setColour(Label::textColourId, juce::Colour(0xff595f66));
  
  setColour(ToggleButton::textColourId, juce::Colour(0xff595f66));
  
  setColour(DirectoryContentsDisplayComponent::highlightColourId, juce::Colour(0xffa5bed5).brighter());
  setColour(DirectoryContentsDisplayComponent::textColourId, juce::Colour(0xff595f66));
  setColour(ListBox::backgroundColourId, juce::Colour());
  
  
  setColour(ScrollBar::trackColourId, juce::Colour(0xfff0f2f2));
  setColour(ScrollBar::backgroundColourId, juce::Colour(0xfff0f2f2));
}

PimpLookAndFeel::~PimpLookAndFeel() {}

void PimpLookAndFeel::drawButtonText (Graphics& g, TextButton& button,
                                              bool isMouseOverButton,
                                              bool isButtonDown)
{
  Font font ("Helvetica", 11.00f, Font::plain);
  //Font font (getTextButtonFont (button));
  g.setFont (font);
  g.setColour (button.findColour (button.getToggleState() ? TextButton::textColourOnId
                                                          : TextButton::textColourOffId)
                     .withMultipliedAlpha (button.isEnabled() ? 1.0f : 0.5f));

  const int yIndent = jmin (4, button.proportionOfHeight (0.3f));
  const int cornerSize = jmin (button.getHeight(), button.getWidth()) / 2;

  const int fontHeight = roundToInt (font.getHeight() * 0.6f);
  const int leftIndent  = jmin (fontHeight, 2 + cornerSize / (button.isConnectedOnLeft() ? 4 : 2));
  const int rightIndent = jmin (fontHeight, 2 + cornerSize / (button.isConnectedOnRight() ? 4 : 2));

  g.drawFittedText (button.getButtonText(),
                    leftIndent,
                    yIndent,
                    button.getWidth() - leftIndent - rightIndent,
                    button.getHeight() - yIndent * 2,
                    Justification::centred, 2);
}

void PimpLookAndFeel::drawToggleButton (Graphics& g,
                                                ToggleButton& button,
                                                bool isMouseOverButton,
                                                bool isButtonDown)
{
  float fontSize = jmin (15.0f, button.getHeight() * 0.75f);
  const int tickWidth = (int)(fontSize * 1.1f);
  
  const int boxSize = (int)(tickWidth * 0.7f);
  
  const int y = (int)((button.getHeight() - tickWidth) * 0.5f + (tickWidth - boxSize) * 0.5f);
  
  g.setColour(juce::Colours::white);
  g.fillRect(4, y, boxSize, boxSize);
  g.setColour(findColour(TextEditor::focusedOutlineColourId).darker());
  g.drawRect(4, y, boxSize, boxSize);
  
  if (button.getToggleState())
  {
    g.fillRect(4 + 2, y + 2, boxSize - 4, boxSize - 4);
  }
  

  Font font ("Helvetica", 11.00f, Font::plain);
  g.setColour (findColour(ToggleButton::textColourId));
  g.setFont (font);

  if (! button.isEnabled())
    g.setOpacity (0.5f);

  const int textX = (int) tickWidth + 5;

  g.drawFittedText (button.getButtonText(),
                    textX, 0,
                    button.getWidth() - textX - 2, button.getHeight(),
                    Justification::centredLeft, 10);
}

void PimpLookAndFeel::drawTextEditorOutline (Graphics& g, int width,
                                                     int height,
                                                     TextEditor& textEditor)
{
  if (textEditor.isEnabled())
  {
    if (textEditor.hasKeyboardFocus (true) && ! textEditor.isReadOnly())
    {
      g.setColour (textEditor.findColour (TextEditor::focusedOutlineColourId));
      g.drawRect (0, 0, width, height, 1);
    }
    else
    {
      g.setColour (textEditor.findColour (TextEditor::outlineColourId));
      g.drawRect (0, 0, width, height);
    }
  }
}

void PimpLookAndFeel::drawButtonBackground (Graphics& g, Button& button,
                                                    const Colour& backgroundColour,
                                                    bool isMouseOverButton,
                                                    bool isButtonDown)
{
  if (button.isEnabled())
  {
    if (!isButtonDown)
      g.setColour (button.findColour (TextButton::buttonColourId));
    else
      g.setColour (button.findColour (TextButton::buttonColourId).brighter());
  }
  else
    g.setColour(juce::Colour (0xffc4cad2));

  g.fillAll();
}

void PimpLookAndFeel::fillTextEditorBackground (Graphics& g, int width,
                                                        int height,
                                                        TextEditor& textEditor)
{
  g.fillAll (textEditor.findColour (TextEditor::backgroundColourId));
  
  g.setColour(textEditor.findColour (TextEditor::focusedOutlineColourId));
  g.drawLine(0, height-1, width, height-1, 2);
}

class PimpLookAndFeel::SliderLabelComp  : public Label
{
public:
    SliderLabelComp() : Label (String::empty, String::empty) {}

    void mouseWheelMove (const MouseEvent&, const MouseWheelDetails&) {}
};

Label* PimpLookAndFeel::createSliderTextBox (Slider& slider)
{
  Label* const l = new SliderLabelComp();
  l->setFont(Font ("Helvetica", 10.00f, Font::plain));

  l->setJustificationType (Justification::centred);

  l->setColour (Label::textColourId, slider.findColour (Slider::textBoxTextColourId));

  l->setColour (Label::backgroundColourId,
                (slider.getSliderStyle() == Slider::LinearBar || slider.getSliderStyle() == Slider::LinearBarVertical)
                          ? Colours::transparentBlack
                          : slider.findColour (Slider::textBoxBackgroundColourId));
  l->setColour (Label::outlineColourId, slider.findColour (Slider::textBoxOutlineColourId));

  l->setColour (TextEditor::textColourId, slider.findColour (Slider::textBoxTextColourId));

  l->setColour (TextEditor::backgroundColourId,
                slider.findColour (Slider::textBoxBackgroundColourId)
                      .withAlpha ((slider.getSliderStyle() == Slider::LinearBar || slider.getSliderStyle() == Slider::LinearBarVertical)
                                      ? 0.7f : 1.0f));

  l->setColour (TextEditor::outlineColourId, slider.findColour (Slider::textBoxOutlineColourId));

  l->setColour (TextEditor::highlightColourId, slider.findColour (Slider::textBoxHighlightColourId));

  return l;
}

void PimpLookAndFeel::drawFileBrowserRow (Graphics& g, int width,
                                                  int height,
                                                  const String& filename,
                                                  Image* icon,
                                                  const String& fileSizeDescription,
                                                  const String& fileTimeDescription,
                                                  const bool isDirectory, const bool isItemSelected,
                                                  const int itemIndex,
                                                  DirectoryContentsDisplayComponent& dcc)
{
  Component* const fileListComp = dynamic_cast<Component*> (&dcc);

  if (isItemSelected)
    g.fillAll (fileListComp != nullptr ? fileListComp->findColour (DirectoryContentsDisplayComponent::highlightColourId)
                                       : findColour (DirectoryContentsDisplayComponent::highlightColourId));

  const int x = 32;
  g.setColour (Colours::black);

  if (icon != nullptr && icon->isValid())
  {
    g.drawImageWithin (*icon, 2, 2, x - 4, height - 4,
                       RectanglePlacement::centred | RectanglePlacement::onlyReduceInSize,
                       false);
  }
  else
  {
    if (const Drawable* d = isDirectory ? getDefaultFolderImage()
                                        : getDefaultDocumentFileImage())
        d->drawWithin (g, Rectangle<float> (2.0f, 2.0f, x - 4.0f, height - 4.0f),
                       RectanglePlacement::centred | RectanglePlacement::onlyReduceInSize, 1.0f);
  }

  g.setColour (fileListComp != nullptr ? fileListComp->findColour (DirectoryContentsDisplayComponent::textColourId)
                                       : findColour (DirectoryContentsDisplayComponent::textColourId));
  
  g.setFont(Font ("Helvetica", 11.00f, Font::plain));

  if (width > 450 && ! isDirectory)
  {
      const int sizeX = roundToInt (width * 0.7f);
      const int dateX = roundToInt (width * 0.8f);

      g.drawFittedText (filename,
                        x, 0, sizeX - x, height,
                        Justification::centredLeft, 1);

      g.setFont (height * 0.5f);
      g.setColour (Colours::darkgrey);

      if (! isDirectory)
      {
          g.drawFittedText (fileSizeDescription,
                            sizeX, 0, dateX - sizeX - 8, height,
                            Justification::centredRight, 1);

          g.drawFittedText (fileTimeDescription,
                            dateX, 0, width - 8 - dateX, height,
                            Justification::centredRight, 1);
      }
  }
  else
  {
      g.drawFittedText (filename,
                        x, 0, width - x, height,
                        Justification::centredLeft, 1);

  }
}

void PimpLookAndFeel::drawScrollbar (Graphics& g, ScrollBar& scrollbar,
                                             int x, int y, int width, int height,
                                             bool isScrollbarVertical,
                                             int thumbStartPosition,
                                             int thumbSize, bool isMouseOver,
                                             bool isMouseDown)
{
  Path thumbPath;
  
  g.fillAll(scrollbar.findColour(ScrollBar::backgroundColourId));
  

  if (thumbSize > 0)
  {
    const float thumbIndent = (isScrollbarVertical ? width : height) * 0.25f;
    const float thumbIndentx2 = thumbIndent * 2.0f;

    if (isScrollbarVertical)
      thumbPath.addRoundedRectangle (x + thumbIndent, thumbStartPosition + thumbIndent,
                                     width - thumbIndentx2, thumbSize - thumbIndentx2, (width - thumbIndentx2) * 0.5f);
    else
      thumbPath.addRoundedRectangle (thumbStartPosition + thumbIndent, y + thumbIndent,
                                     thumbSize - thumbIndentx2, height - thumbIndentx2, (height - thumbIndentx2) * 0.5f);
  }

  Colour thumbCol (scrollbar.findColour (ScrollBar::thumbColourId, true));

  if (isMouseOver || isMouseDown)
      thumbCol = thumbCol.withMultipliedAlpha (2.0f);

  g.setColour (thumbCol);
  g.fillPath (thumbPath);

  g.setColour (thumbCol.contrasting ((isMouseOver  || isMouseDown) ? 0.2f : 0.1f));
  g.strokePath (thumbPath, PathStrokeType (1.0f));
}

void PimpLookAndFeel::drawProgressBar (Graphics& g,
                                               ProgressBar& progressBar,
                                               int width, int height,
                                               double progress,
                                               const String& textToShow)
{
  g.setColour(juce::Colour (0xff595f66));
  
  if (progress >= 0.0f && progress < 1.0f)
  {
    g.fillRect(1.0f, 1.0f,
               (float) jlimit (0.0, width - 2.0, progress * (width - 2.0)),
               (float) (height - 2));
  }
}

juce::Font PimpLookAndFeel::getComboBoxFont (ComboBox& box)
{
    return Font ("Helvetica", 11.00f, Font::plain);
}