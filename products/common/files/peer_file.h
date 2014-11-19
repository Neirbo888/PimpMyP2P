/*
  ==============================================================================

    peer_file.h
    Created: 19 Nov 2014 9:44:05pm
    Author:  Adrien Tisseraud

  ==============================================================================
*/

#ifndef PEER_FILE_H_INCLUDED
#define PEER_FILE_H_INCLUDED

#include "JuceHeader.h"

/// @class PeerFile
/// @brief Holds information about a file owned by one or several peers
class PeerFile
{
public:
  /// @brief Constructor
  PeerFile(const juce::File& file);
  
  /// @brief Copy constructor
  PeerFile(const PeerFile &);
  
  /// @brief Destructor
  ~PeerFile();
  
  /// @brief Get the associated file
  const juce::File& getFile() const { return _file; }
  
  /// @brief Get the MD5 message for this file
  const juce::MD5& getMD5() const { return _md5; }
  
  /// @brief Test the equality between two PeerFile
  bool operator==(const PeerFile&) const;
  
  /// @brief Test the inequality between two PeerFile
  bool operator!=(const PeerFile &) const;
  
  /// @brief Returns an empty PeerFile
  static PeerFile emptyPeerFile () { return PeerFile(); }

private:
  /// @brief Private default constructor
  PeerFile();
  
  juce::File _file; ///< File associated
  juce::MD5 _md5; ///< MD5 Hash for this file
};



#endif  // PEER_FILE_H_INCLUDED
