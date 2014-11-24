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
  /// @brief Constructs a PeerFile from a local file, the MD5 hash and the size
  /// are computed from the filesystem's info
  /// @param {juce::File} file - Local file
  PeerFile(const juce::File& file);
  
  /// @brief Constructs a PeerFile from informations received over the network
  /// @param {juce::String} filename - Name of the file
  /// @param {juce::String} md5 - MD5 hash for this file
  /// @param {int} size - Size in bytes
  PeerFile(juce::String filename, juce::String md5, int size);
  
  /// @brief Constructs a PeerFile as a copy of another one
  /// @param {PeerFile} otherFile - PeerFile that will be copied
  PeerFile(const PeerFile & otherFile);
  
  /// @brief Destructor
  ~PeerFile();
  
  /// @brief Get the associated file
  const juce::File& getFile() const { return _file; }
  
  /// @brief Get the name of this file
  const juce::String& getFilename() const { return _filename; }
  
  /// @brief Get the MD5 message for this file
  const juce::String& getMD5() const { return _md5; }
  
  /// @brief Get the size of the file
  const int getSize() const { return _size; }
  
  /// @brief Test the equality between two PeerFile
  bool operator==(const PeerFile&) const;
  
  /// @brief Test the inequality between two PeerFile
  bool operator!=(const PeerFile &) const;
  
  /// @brief Test if this PeerFile is empty
  const bool isEmpty() const { return (_size == 0) &&
                                      (_filename == juce::String::empty) &&
                                      (_file == juce::File::nonexistent) &&
                                      (_md5 == juce::String::empty); }
  
  /// @brief True if this file is currently stored on this filesystem, meaning
  /// that the getFile() method will give a valid file object
  const bool isLocal() const { return _isLocal; }
  
  /// @brief Returns an empty PeerFile
  static PeerFile emptyPeerFile () { return PeerFile(); }
  
  /// @brief Returns the list of Peers possessing this file
  const juce::Array<IPAddress>& getPeersAddresses() const { return _peers; }
  
  /// @brief Add an IPAddress to the Peers list
  void addPeer(juce::IPAddress peer);
  
  /// @brief Remove an IPAddress from the Peers list
  void removePeer(juce::IPAddress peer);

private:
  /// @brief Private default constructor
  PeerFile();
  
  /// @brief File associated
  juce::File _file;
  /// @brief Name of the file
  juce::String _filename;
  /// @brief MD5 Hash for this file
  juce::String _md5;
  /// @brief Size of the file
  int _size;
  /// @brief Define is the file is local or distant
  bool _isLocal;
  /// @brief List of Peers possessing this file
  juce::Array<juce::IPAddress> _peers;
};



#endif  // PEER_FILE_H_INCLUDED
