/*
  ==============================================================================

    peer_file_manager.h
    Created: 19 Nov 2014 7:55:14pm
    Author:  Adrien Tisseraud

  ==============================================================================
*/

#ifndef PEER_FILE_MANAGER_H_INCLUDED
#define PEER_FILE_MANAGER_H_INCLUDED

#include "JuceHeader.h"
#include "products/common/files/peer_file.h"

// Forward declarations
class PeerProcessor;

/// @class PeerFileManager
/// @brief Handles the list of shared files, 
class PeerFileManager
: public juce::Thread
{
public:
  /// @brief Constructor
  PeerFileManager(PeerProcessor* owner);
  
  /// @brief Destructor
  ~PeerFileManager();
  
  /// @brief Set the current shared folder
  void setSharedFolder(juce::File folder);
  
  /// @brief Return an array containing all the available files
  const juce::Array<PeerFile>& getAvailableFiles() const { return _availableFiles; }
  
  /// @brief Return the current shared folder
  const juce::File& getSharedFolder() const { return _sharedFolder; }
  
  /// @brief File manager run method
  void run();
private:
  PeerProcessor *_owner; ///< Peer processor owning this manager
  juce::File _sharedFolder; ///< Shared folder containing shared files
  juce::Array<PeerFile> _availableFiles;  ///< List of available shared files
  juce::CriticalSection _mutex; ///< Mutex to lock access to the available files
  
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PeerFileManager)
};

#endif  // PEER_FILE_MANAGER_H_INCLUDED
