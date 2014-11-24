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
  _owner(owner)
{
  startThread();
}

PeerFileManager::~PeerFileManager()
{
  signalThreadShouldExit();
  stopThread(2000);
}

void PeerFileManager::setSharedFolder(const juce::File& folder)
{
  if (folder.exists())
    _sharedFolder = folder;
}

void PeerFileManager::run()
{
  while (!threadShouldExit())
  {
    if (_sharedFolder.exists())
    {
      bool contentHasChanged = false;
      juce::Array<juce::File> foundFiles;
      juce::Array<PeerFile> newAvailableFilesArray;
      
      _sharedFolder.findChildFiles(foundFiles,juce::File::findFiles, false, "*");
      for (juce::File* file = foundFiles.begin(); file != foundFiles.end(); file++)
        newAvailableFilesArray.add(PeerFile(*file));
      if (newAvailableFilesArray.size() == _availableFiles.size())
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
    }
    
    // Wait a little bit before doing another scan
    juce::Thread::wait(5000);
  }
  Logger::writeToLog("Closing PeerFileManager thread");
}