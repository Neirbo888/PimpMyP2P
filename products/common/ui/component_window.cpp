#include "products/common/ui/component_window.h"

ComponentWindow::ComponentWindow(Component* associatedComponent, bool closeOnClick)
: TopLevelWindow("No title",false),
  _component(associatedComponent)
{
  _base_colour = juce::Colour (0xffb82c2f);
  
  if (closeOnClick)
    _component->addMouseListener(this, true);
  
  addAndMakeVisible(_component);
  setSize(100, 100);
}

ComponentWindow::~ComponentWindow()
{
  _component = nullptr;
}

void ComponentWindow::paint(juce::Graphics &g)
{
  g.fillAll (Colours::white);
}

void ComponentWindow::resized()
{
  if (getParentComponent() != nullptr) {
    Point<int> center = getParentComponent()->getLocalBounds().getCentre();
    if (_component != nullptr)
      setBounds(_component->getLocalBounds());
    setCentrePosition(center.getX(), center.getY());
  }
}

void ComponentWindow::mouseDown(const juce::MouseEvent& event)
{
  if (event.eventComponent == _component)
    hideWindow();
}

void ComponentWindow::showWindow()
{
  if (_component != nullptr)
  {
    resized();
    setVisible(true);
  }
}

void ComponentWindow::hideWindow()
{
  if (isVisible())
    setVisible(false);
}