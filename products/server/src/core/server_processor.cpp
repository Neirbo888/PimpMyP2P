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

void PimpServerProcessor::registerNewClient(IPAddress address)
{

}

void PimpServerProcessor::unregisterClient(IPAddress address)
{

}

std::vector<juce::File> PimpServerProcessor::lookForFileFromKeyword(String keyword, bool refreshList)
{
	std::vector<juce::File> result;
	bool isFileInserted;

	StringArray keywords;
	keywords.addTokens(keyword, " _-", "");
	// Remove keywords shorter than 3 characters
	for (int i = 0; i <= keywords.size; i++)
	{
		if (keywords[i].length < 3)
		{
			keywords.remove(i);
		}
	}

	for (int i = 0; i <= _fileCache.size; i++)
	{
		isFileInserted = false;
		StringArray fileName;
		fileName.addTokens(_fileCache.at(i).getFileNameWithoutExtension()," _-","");
		// Remove words shorter than 3 characters
		for (int j = 0; j <= fileName.size; j++)
		{
			if (fileName[j].length < 3)
			{
				fileName.remove(j);
			}
		}

		for (int j = 0; j <= fileName.size; j++)
		{
			for (int k = 0; k <= keywords.size; k++)
			{
				if (fileName[j] == keywords[k] && isFileInserted == false)
				{
					result.push_back(_fileCache.at(i));
					isFileInserted = true;
				}
			}
		}
	}
}

void PimpServerProcessor::refreshFileCache()
{

}