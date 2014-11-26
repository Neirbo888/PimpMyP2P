/*
  ==============================================================================

    tracker_file_manager.cpp
    Created: 24 Nov 2014 7:57:28am
    Author:  Adrien Tisseraud

  ==============================================================================
*/

#include "products/server/src/core/tracker_file_manager.h"
#include "products/server/src/core/tracker_processor.h"
#include "products/common/messages/pimp_message.h"

TrackerFileManager::TrackerFileManager(TrackerProcessor* owner)
: _owner(owner)
{
  _ignoredWords.add("les");
  _ignoredWords.add("une");
  _ignoredWords.add("des");
  _ignoredWords.add("avec");
}

TrackerFileManager::~TrackerFileManager() {}

const juce::Array<PeerFile> TrackerFileManager::getSimilarFiles(const juce::String& keyword) const
{
  juce::Array<PeerFile> result;
  auto keywordsDistant = getKeywords(keyword);
  
  for (PeerFile p : _availableFiles)
  {
    auto keywordsLocal = getKeywords(p.getFilename());
    for (juce::String s : keywordsDistant)
      if (keywordsLocal.contains(s))
      {
        result.add(p);
        break;
      }
  }
  return result;
}

const juce::StringArray TrackerFileManager::getKeywords(const juce::String &string) const
{
  auto keywords = juce::StringArray::fromTokens(string, " _-'.", "");
  keywords.removeEmptyStrings();
  keywords.removeDuplicates(true);
  for (juce::String s : _ignoredWords)
    keywords.removeString(s, true);
  for (int i = keywords.size(); --i >= 0;)
    if (keywords.getReference(i).length() <= 2)
      keywords.remove(i);
  return keywords;
}

void TrackerFileManager::registerPeer(const juce::IPAddress peer)
{
  if (!_availablePeers.contains(peer))
    _availablePeers.add(peer);
}

void TrackerFileManager::unregisterPeer(const juce::IPAddress peer)
{
  if (_availablePeers.contains(peer))
  {
    int index = _availablePeers.indexOf(peer);
    _availablePeers.remove(index);
  }
}

void TrackerFileManager::cleanPeer(juce::IPAddress peer)
{
  for (int i = _availableFiles.size(); --i >= 0;)
  {
    const juce::Array<juce::IPAddress>& peerList = _availableFiles.getReference(i).getPeersAddresses();
    PeerFile& file = _availableFiles.getReference(i);
    if (peerList.contains(peer) && peerList.size() == 1)
    {
      _availableFiles.remove(i);
    }
    else if (peerList.contains(peer))
    {
      file.removePeer(peer);
    }
  }
}