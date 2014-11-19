/*
  ==============================================================================

    peer_file.cpp
    Created: 19 Nov 2014 9:44:05pm
    Author:  Adrien Tisseraud

  ==============================================================================
*/

#include "products/common/files/peer_file.h"

PeerFile::PeerFile(const juce::File& file)
: _file(file),
  _md5(MD5(_file)) {}

PeerFile::PeerFile(const PeerFile & newPeerFile)
: _file(newPeerFile.getFile()),
  _md5(MD5(_file)) {}

PeerFile::PeerFile() {}

PeerFile::~PeerFile() {}

bool PeerFile::operator==(const PeerFile & otherFile) const
{
  if (this->getMD5() != otherFile.getMD5())
    return false;
  if (this->getFile().getFileName() != otherFile.getFile().getFileName())
    return false;
  return true;
}

bool PeerFile::operator!=(const PeerFile & otherFile) const
{
  if (this->getMD5() == otherFile.getMD5())
    return false;
  if (this->getFile().getFileName() == otherFile.getFile().getFileName())
    return false;
  return true;
}