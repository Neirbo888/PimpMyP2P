/*
  ==============================================================================

    app_processor.cpp
    Created: 17 Nov 2014 6:48:41pm
    Author:  Adrien Tisseraud

  ==============================================================================
*/

#include "products/common/ui/component_window.h"
#include "products/server/src/ui/main_window.h"
#include "products/server/src/core/server_processor.h"

PimpServerProcessor::PimpServerProcessor()
{
  _component = new MainWindow(this);
  _window = new ComponentWindow(_component);
}

PimpServerProcessor::~PimpServerProcessor()
{
  
}

void PimpServerProcessor::actionListenerCallback(const String& message)
{
  
}