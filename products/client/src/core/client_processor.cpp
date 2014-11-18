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
: Thread("PimpClient")
{
  _component = new MainWindow(this);
  _window = new ComponentWindow(_component);
  _connected = _socket.createListener(4807);
  if (!_connected)
    std::cout << "Error" << std::endl;
  startThread();
}

PimpClientProcessor::~PimpClientProcessor()
{
  this->stop();
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

void PimpClientProcessor::scanSharedFolder()
{
	juce::Array<juce::File> found_files;
	if (_sharedFolder.findChildFiles(found_files, juce::File::findFiles, false, "*"))
	{
		for (juce::File* file = found_files.begin(); file != found_files.end();file++)
		{
			_files.push_back(juce::File(file->getFullPathName()));
		}
	}
}

void PimpClientProcessor::stop() {
  _socket.close();
  signalThreadShouldExit();
  stopThread(2000);
}

void PimpClientProcessor::run()
{
  if (_connected)
  {
    Logger::writeToLog("Waiting for tcp connection on port 4807");
    while (!threadShouldExit())
    {
      StreamingSocket* socket = _socket.waitForNextConnection();
      
      char inBuffer[65535];
      int bytesRead = socket->read(inBuffer,65535,false);
      for (int i = 0; i < bytesRead; i++)
      {
        std::cout << inBuffer[i];
      }
      std::cout << std::endl << "fin" << std::endl;
      deleteAndZero(socket);
    }
  }
  Logger::writeToLog("Closing receiving thread");
}