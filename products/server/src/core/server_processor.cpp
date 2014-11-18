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
	_clientList.push_back(address);
}

void PimpServerProcessor::unregisterClient(IPAddress address)
{
	for (std::vector<IPAddress>::iterator iter = _clientList.begin(); iter != _clientList.end(); iter++)
	{
		if (*iter == address)
		{
			_clientList.erase(iter)
		}
	}
}

std::vector<PeerFile> PimpServerProcessor::lookForFileFromKeyword(String keyword, bool refreshList)
{
	std::vector<PeerFile> result;
	bool isFileInserted;

	for (int i = 0; i <= _fileCache.size; i++)
	{
		if (_fileCache[i].isSimilarTo(keyword) && isFileInserted == false)
		{
			result.push_back(_fileCache.at(i));
		}
	}
	return result;
}

void PimpServerProcessor::refreshFileCache()
{

}