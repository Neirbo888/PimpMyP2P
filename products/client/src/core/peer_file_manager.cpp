/*
  ==============================================================================

    peer_file_manager.cpp
    Created: 19 Nov 2014 7:55:14pm
    Author:  Adrien Tisseraud

  ==============================================================================
*/

#include "products/client/src/core/peer_file_manager.h"
#include "products/client/src/core/peer_processor.h"

PeerFileManager::PeerFileManager(PeerProcessor *owner)
: juce::Thread("FileManager thread"),
  _owner(owner),
  _sharedFolder(juce::File::nonexistent) {}

PeerFileManager::~PeerFileManager()
{
  signalThreadShouldExit();
  stopThread(2000);
}

void PeerFileManager::setSharedFolder(const juce::File& folder)
{
  if (folder.exists())
  {
    _sharedFolder = juce::File(folder);
    startThread();
  }
}

void PeerFileManager::run()
{
  if (_sharedFolder.exists())
  {
    Logger::writeToLog("Scanning folder");
    bool contentHasChanged = false;
    juce::Array<juce::File> foundFiles;
    juce::Array<PeerFile> newAvailableFilesArray;
    
    _sharedFolder.findChildFiles(foundFiles,juce::File::findFiles, false, "*");
    for (const juce::File& file : foundFiles)
    {
      if (threadShouldExit()) return;
      newAvailableFilesArray.add(PeerFile(file));
    }
    if (foundFiles.size() == _availableFiles.size())
    {
      const juce::Array<PeerFile>& availableFiles = this->getAvailableFiles();
      for (PeerFile* peerFile = newAvailableFilesArray.begin();
           peerFile != newAvailableFilesArray.end(); peerFile++)
      {
        if (!availableFiles.contains(*peerFile)) {
          contentHasChanged = true;
          break;
        }
      }
    }
    else
      contentHasChanged = true;
    
    if (contentHasChanged)
    {
      ScopedLock lock (_mutex);
      _availableFiles = newAvailableFilesArray;
      _owner->triggerAsyncUpdate();
    }
    Logger::writeToLog("End scan");
  }
}