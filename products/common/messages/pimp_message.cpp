#include "products/common/messages/pimp_message.h"

PimpMessage::PimpMessage(const std::string& xmlData)
{
  XmlDocument document (xmlData);
  _message = document.getDocumentElement();
  if (!_message)
  {
    _message = new XmlElement("PimpMessage");
    setCommand(kError);
    auto errorXml = new XmlElement("ErrorMessage");
    errorXml->addTextElement("Can't parse Xml string");
    _message->addChildElement(errorXml);
  }
}

PimpMessage::PimpMessage(CommandType type)
: _message(new XmlElement("PimpMessage"))
{
  setCommand(type);
}

PimpMessage::~PimpMessage() {}

const juce::String PimpMessage::getXmlString() const
{
  return _message->createDocument(juce::String::empty);
}

const bool PimpMessage::isCommand(PimpMessage::CommandType cmd) const
{
  auto command = _message->getChildByName("Command");
  if (command)
    if (command->hasAttribute("Value"))
      return (CommandType)command->getIntAttribute("Value") == cmd;
  return false;
}

void PimpMessage::setCommand(PimpMessage::CommandType cmd)
{
  auto command = _message->getChildByName("Command");
  if (!command)
  {
    command = new XmlElement("Command");
    command->setAttribute("Value", cmd);
    _message->addChildElement(command);
  }
  else
  {
    command->setAttribute("Value", cmd);
  }
}

const bool PimpMessage::hasSource() const
{
  auto sourceXml = _message->getChildByName("SourceIp");
  if (sourceXml && sourceXml->hasAttribute("Value"))
      return true;
  return false;
}

const juce::IPAddress PimpMessage::getSource() const
{
  if (hasSource())
  {
    auto sourceXml = _message->getChildByName("SourceIp");
    return juce::IPAddress(sourceXml->getStringAttribute("Value"));
  }
  return juce::IPAddress();
}

const bool PimpMessage::hasPeerFile() const
{
  auto peerFileXml = _message->getChildByName("PeerFile");
  if (peerFileXml)
    return hasValidPeerFile(peerFileXml);
  return false;
}

const PeerFile PimpMessage::getPeerFile() const
{
  
  return getPeerFileFromXmlElement(_message->getChildByName("PeerFile"));
}

const bool PimpMessage::hasRange() const
{
  auto rangeXml = _message->getChildByName("Range");
  if (rangeXml)
    return rangeXml->hasAttribute("Start") && rangeXml->hasAttribute("End");
  return false;
}

const juce::Range<int> PimpMessage::getRange() const
{
  if (hasRange())
  {
    auto rangeXml = _message->getChildByName("Range");
    return juce::Range<int> (rangeXml->getIntAttribute("Start"),
                             rangeXml->getIntAttribute("End"));
  }
  return juce::Range<int>::emptyRange(0);
}

const bool PimpMessage::hasSearchString() const
{
  auto searchStringXml = _message->getChildByName("SearchString");
  if (searchStringXml) return true;
  return false;
}

const juce::String PimpMessage::getSearchString() const
{
  auto searchStringXml = _message->getChildByName("SearchString");
  if (searchStringXml)
    return searchStringXml->getStringAttribute("Value");
  return juce::String::empty;
}

const bool PimpMessage::hasSearchResults() const
{
  auto searchResultsXml = _message->getChildByName("SearchResults");
  if (searchResultsXml) return true;
  return false;
}

juce::Array<PeerFile> PimpMessage::getSearchResults()
{
  juce::Array<PeerFile> result;
  auto searchResultsXml = _message->getChildByName("SearchResults");
  
  if (searchResultsXml)
  {
    for (int fileIndex = 0;
         fileIndex < searchResultsXml->getNumChildElements();
         fileIndex++)
    {
      auto xmlFile = searchResultsXml->getChildElement(fileIndex);
      auto dummyFile = getPeerFileFromXmlElement(xmlFile);
      if (dummyFile != PeerFile::emptyPeerFile())
        result.add(dummyFile);
    }
  }
  
  return result;
}

const bool PimpMessage::hasLocalFileList() const
{
  auto localFileListXml = _message->getChildByName("LocalFileList");
  if (localFileListXml) return true;
  return false;
}

const juce::Array<PeerFile> PimpMessage::getLocalFileList() const
{
  juce::Array<PeerFile> localFiles;
  auto localFilesXml = _message->getChildByName("LocalFileList");
  if (localFilesXml)
  {
    for (int fileIndex = 0;
         fileIndex < localFilesXml->getNumChildElements();
         fileIndex++)
    {
      const PeerFile file = getPeerFileFromXmlElement(localFilesXml->getChildElement(fileIndex));
      if (file != PeerFile::emptyPeerFile())
      {
        localFiles.add(file);
      }
    }
  }
  return localFiles;
}

void PimpMessage::sendToSocket(juce::StreamingSocket *socket,
                               juce::IPAddress source)
{
  if (socket && socket->isConnected())
  {
    XmlElement localMessage (*_message);
    auto sourceIpXml = new XmlElement("SourceIp");
    sourceIpXml->setAttribute("Value", source.toString());
    localMessage.addChildElement(sourceIpXml);
    
    juce::String out = localMessage.createDocument(juce::String::empty);
    
    union Ustuff { int i; unsigned char c[4]; };
    Ustuff outUnion;
    outUnion.i = out.length();
    socket->write(outUnion.c, 4);
    socket->write(out.toRawUTF8(), outUnion.i);
  }
}

PimpMessage PimpMessage::createPeerFileRequest(PeerFile file)
{
  PimpMessage peerFileRequest (kPeerFileRequest);
  peerFileRequest._message->addChildElement(getXmlElementFromPeerFile(file));
  
  return peerFileRequest;
}

PimpMessage PimpMessage::createPeerSearch(juce::String keystring)
{
  PimpMessage peerSearch (kPeerSearch);
  
  auto searchStringXml = new XmlElement("SearchString");
  searchStringXml->setAttribute("Value", keystring);
  peerSearch._message->addChildElement(searchStringXml);
  
  return peerSearch;
}

PimpMessage PimpMessage::createErrorMessage(juce::String message)
{
  PimpMessage error (kError);
  auto errorXml = new XmlElement("ErrorMessage");
  errorXml->addTextElement(message);
  error._message->addChildElement(errorXml);
  return error;
}

PimpMessage PimpMessage::createOk()
{
  PimpMessage ok (kOk);
  return ok;
}

PimpMessage PimpMessage::createTrackerSearchResult(const juce::Array<PeerFile>& files)
{
  PimpMessage trackerSearchResult (kTrackerSearchResult);
  
  auto resultsXml = new XmlElement("SearchResults");
  
  for (const PeerFile& file : files)
    resultsXml->addChildElement(getXmlElementFromPeerFile(file));
  
  trackerSearchResult._message->addChildElement(resultsXml);
  
  return trackerSearchResult;
}

PimpMessage PimpMessage::createPeerRefresh(const juce::Array<PeerFile> localFiles)
{
  PimpMessage peerRefresh (kPeerRefresh);
  if (localFiles.size() != 0)
  {
    auto filelistXml = new XmlElement("LocalFileList");
    
    for (const PeerFile& file : localFiles)
    {
      filelistXml->addChildElement(getXmlElementFromPeerFile(file));
    }
    
    peerRefresh._message->addChildElement(filelistXml);
  }
  
  return peerRefresh;
}

PimpMessage PimpMessage::createPeerSignOut()
{
  PimpMessage peerSignOut (kPeerSignOut);
  return peerSignOut;
}

const bool PimpMessage::hasValidPeerFile(juce::XmlElement *element)
{
  if (element->hasTagName("PeerFile"))
  {
    auto nameXml = element->getChildByName("Name");
    if (!nameXml)
      return false;
    if (!nameXml->hasAttribute("Value"))
      return false;
    
    auto sizeXml = element->getChildByName("Size");
    if (!sizeXml)
      return false;
    if (!sizeXml->hasAttribute("Value"))
      return false;
    
    auto md5Xml = element->getChildByName("MD5");
    if (!md5Xml)
      return false;
    if (!md5Xml->hasAttribute("Value"))
      return false;
    
    auto peersXml = element->getChildByName("PeersList");
    if (!peersXml)
      return false;
    
    for (int peerIndex = 0; peerIndex < peersXml->getNumChildElements();
         peerIndex++)
      if (!peersXml->getChildElement(peerIndex)->hasAttribute("Value"))
        return false;
    
    return true;
  }
  return false;
}

const PeerFile PimpMessage::getPeerFileFromXmlElement(juce::XmlElement *element)
{
  if (!element)
  {
    Logger::writeToLog("Trying to parse a nullptr to a PeerFile");
    return PeerFile::emptyPeerFile();
  }
  if (hasValidPeerFile(element))
  {
    auto nameXml = element->getChildByName("Name");
    auto sizeXml = element->getChildByName("Size");
    auto md5Xml = element->getChildByName("MD5");
    auto peersXml = element->getChildByName("PeersList");
    
    juce::Array<juce::IPAddress> peersList;
    for (int peerIndex = 0; peerIndex < peersXml->getNumChildElements();
         peerIndex++)
    {
      auto dummyPeer = peersXml->getChildElement(peerIndex);
      peersList.add(juce::IPAddress(dummyPeer->getStringAttribute("Value")));
    }
    
    return PeerFile(nameXml->getStringAttribute("Value"),
                    md5Xml->getStringAttribute("Value"),
                    sizeXml->getIntAttribute("Value"),
                    peersList);
  }
  
  Logger::writeToLog("Trying to parse an invalid XmlElement to a PeerFile");
  return PeerFile::emptyPeerFile();
}

juce::XmlElement* PimpMessage::getXmlElementFromPeerFile(PeerFile file)
{
  if (file == PeerFile::emptyPeerFile())
  {
    Logger::writeToLog("Trying to parse an empty PeerFile to an XmlElement");
    return nullptr;
  }
  
  auto fileXml = new XmlElement("PeerFile");
  
  auto dummyName = new XmlElement("Name");
  dummyName->setAttribute("Value", file.getFilename());
  fileXml->addChildElement(dummyName);
  
  auto dummyMD5 = new XmlElement("MD5");
  dummyMD5->setAttribute("Value",file.getMD5());
  fileXml->addChildElement(dummyMD5);
  
  auto dummySize = new XmlElement("Size");
  dummySize->setAttribute("Value", (double)(file.getSize()));
  fileXml->addChildElement(dummySize);
  
  auto dummyPeersAddresses = new XmlElement("PeersList");
  for (const juce::IPAddress& address : file.getPeersAddresses())
  {
    auto dummyPeer = new XmlElement("Peer");
    dummyPeer->setAttribute("Value", address.toString());
    dummyPeersAddresses->addChildElement(dummyPeer);
  }
  fileXml->addChildElement(dummyPeersAddresses);
  
  return fileXml;
}

PimpMessage PimpMessage::createFromSocket(juce::StreamingSocket *socket)
{
  if (socket && socket->isConnected())
  {
    union Ustuff { int i; unsigned char c[4]; };
    Ustuff outUnion;
    int bytesRead = socket->read(outUnion.c, 4, true);
    if (bytesRead == 4 && outUnion.i != 0)
    {
      juce::MemoryBlock buffer (outUnion.i, true);
      bytesRead = socket->read(buffer.getData(), outUnion.i, true);
      Logger::writeToLog("PIMPMESSAGE RECEIVED:");
      Logger::writeToLog(buffer.toString());
      return PimpMessage(buffer.toString().toStdString());
    }
  }
  return PimpMessage::createErrorMessage("Can't create from socket");
}

PimpMessage PimpMessage::createPeerFileSend(PeerFile file,
                                            juce::Range<int> range,
                                            int part)
{
  PimpMessage peerFileSend (kPeerFileSend);
  peerFileSend._message->addChildElement(getXmlElementFromPeerFile(file));
  
  auto rangeXml = new XmlElement("Range");
  rangeXml->setAttribute("Start", range.getStart());
  rangeXml->setAttribute("End", range.getEnd());
  peerFileSend._message->addChildElement(rangeXml);
  
  auto partXml = new XmlElement("Part");
  partXml->setAttribute("Value", part);
  peerFileSend._message->addChildElement(partXml);  
  return peerFileSend;
}

const bool PimpMessage::hasPartNumber() const
{
  auto partNumberXml = _message->getChildByName("PartNumber");
  if (partNumberXml)
    return partNumberXml->hasAttribute("Value");
  return false;
}

const int PimpMessage::getPartNumber() const
{
  if (hasPartNumber())
    return _message->getChildByName("PartNumber")->getIntAttribute("Value");
  return -1;
}

PimpMessage::PimpMessage(const PimpMessage& otherMessage)
{
  XmlDocument document (otherMessage.getXmlString());
  _message = document.getDocumentElement();
  if (!_message)
  {
    _message = new XmlElement("PimpMessage");
    setCommand(kError);
    auto errorXml = new XmlElement("ErrorMessage");
    errorXml->addTextElement("Copy constructor failed");
    _message->addChildElement(errorXml);
  }
}