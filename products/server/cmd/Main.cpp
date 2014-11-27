/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#include "JuceHeader.h"
#include "products/server/src/core/tracker_processor.h"


//==============================================================================
int main (int argc, char* argv[])
{
  ScopedPointer<TrackerProcessor> _processor = new TrackerProcessor(true);
  while(1)
  {
    sleep(100000);
  }
  return 0;
}
