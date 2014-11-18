/*
  ==============================================================================

    app_processor.cpp
    Created: 17 Nov 2014 6:48:41pm
    Author:  Adrien Tisseraud

  ==============================================================================
*/

#include "products/common/ui/component_window.h"
#include "products/client/src/ui/main_window.h"
#include "products/client/src/core/client_processor.h"

PimpClientProcessor::PimpClientProcessor()
{
  _component = new MainWindow(this);
  _window = new ComponentWindow(_component);
}

PimpClientProcessor::~PimpClientProcessor()
{
  
}

void PimpClientProcessor::actionListenerCallback(const String& message)
{
  
}

void PimpClientProcessor::setSharedFolder(juce::File folder)
{
  if (folder.exists())
  {
    _sharedFolder = folder;
    // Maybe set a new state machine transition here
  }
}