/*
  ==============================================================================

    tracker_file_manager.h
    Created: 24 Nov 2014 7:57:28am
    Author:  Adrien Tisseraud

  ==============================================================================
*/

#ifndef TRACKER_FILE_MANAGER_H_INCLUDED
#define TRACKER_FILE_MANAGER_H_INCLUDED


#include "JuceHeader.h"
#include "products/common/files/peer_file.h"

// Forward declarations
class TrackerProcessor;

/// @class TrackerFileManager
/// @brief Handles files shared accross different peers
class TrackerFileManager
{
public:
  /// @brief Constructor
  TrackerFileManager(TrackerProcessor* owner);
  
  /// @brief Destructor
  ~TrackerFileManager();
  
  /// @brief Return an array containing all the available files
  const juce::Array<PeerFile>& getAvailableFiles() const { return _availableFiles; }
  
  /// @brief Return an array containing files that looks similar to the given
  /// PeerFile
  const juce::Array<PeerFile> getSimilarFiles(const PeerFile& peerFile) const;
  
  /// @brief Register new peer
  void registerPeer(const juce::IPAddress& peer);
  
  /// @brief Unregister existing peer
  void unregisterPeer(const juce::IPAddress& peer);
  
  const juce::StringArray getKeywords(const juce::String& string) const;
  
private:
  /// @brief Peer processor owning this manager
  TrackerProcessor *_owner;
  /// @brief List of available shared files
  juce::Array<PeerFile> _availableFiles;
  /// @brief List of available peers
  juce::Array<juce::IPAddress> _availablePeers;
  /// @brief List of words that are ignored when finding similarities
  juce::StringArray _ignoredWords;
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TrackerFileManager)
};


#endif  // TRACKER_FILE_MANAGER_H_INCLUDED
