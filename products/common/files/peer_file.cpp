#include "products/common/files/peer_file.h"

PeerFile::PeerFile(const juce::File& file)
{
  if (file.existsAsFile())
  {
    _file = file;
    _filename = _file.getFileName();
    _md5 = juce::MD5(_file).toHexString();
    _size = _file.getSize();
    _isLocal = true;
  }
  else
  {
    _file = juce::File::nonexistent;
    _filename = juce::String::empty;
    _md5 = juce::String::empty;
    _size = 0;
    _isLocal = false;
  }
}

PeerFile::PeerFile(juce::String filename, juce::String md5, int size,
                   juce::Array<juce::IPAddress> peers)
: _file(juce::File::nonexistent),
  _filename(filename),
  _md5(md5),
  _size(size),
  _peers(peers),
  _isLocal(false) {}

PeerFile::PeerFile(const PeerFile & otherFile)
: _file(otherFile.getFile()),
  _filename(otherFile.getFilename()),
  _md5(otherFile.getMD5()),
  _size(otherFile.getSize()),
  _peers(otherFile.getPeersAddresses()),
  _isLocal(otherFile.isLocal()) {}

PeerFile::~PeerFile() {}

bool PeerFile::operator==(const PeerFile & otherFile) const
{
  if (this->getMD5() != otherFile.getMD5())
    return false;
  if (this->getFilename() != otherFile.getFilename())
    return false;
  if (this->getSize() != otherFile.getSize())
    return false;
  return true;
}

bool PeerFile::operator!=(const PeerFile & otherFile) const
{
  if (this->getMD5() == otherFile.getMD5())
    return false;
  if (this->getFilename() == otherFile.getFilename())
    return false;
  if (this->getSize() == otherFile.getSize())
    return false;
  return true;
}

void PeerFile::addPeer(juce::IPAddress peer)
{
  if (!_peers.contains(peer))
    _peers.add(peer);
}

void PeerFile::removePeer(juce::IPAddress peer)
{
  int index = _peers.indexOf(peer);
  if (index >= 0)
    _peers.remove(index);
}

std::ostream & operator<<(std::ostream & ofs, PeerFile const & p)
{
  juce::String string;
  string = "<File>\n\tName:" + p.getFilename() + "\n" + "\tMD5:" + p.getMD5() +
  "\n" + "\tSize:" + juce::String(p.getSize()) + "\n\tPeers:\n";
  for (juce::IPAddress peer : p.getPeersAddresses())
  {
    string = string + "\t\t" + peer.toString() + "\n";
  }
  string += "</file>\n";
  ofs << string;
  return ofs;
}