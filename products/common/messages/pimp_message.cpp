#include "products/common/messages/pimp_message.h"

PimpMessage::PimpMessage(juce::IPAddress srcIp)
: _message(new XmlElement("PimpMessage"))
{
  XmlElement* sourceIpXml = new XmlElement("SourceIp");
  sourceIpXml->setAttribute("Value", srcIp.toString());
  _message->addChildElement(sourceIpXml);
}

PimpMessage::PimpMessage(const std::string& xmlData)
{
  XmlDocument document (xmlData);
  _message = document.getDocumentElement();
  if (!_message)
  {
    _message = new XmlElement("PimpMessage");
    setCommand(kError);
  }
}

PimpMessage::~PimpMessage()
{
  _message = nullptr;
}

const juce::String PimpMessage::getXmlString() const
{
  return _message->createDocument(juce::String::empty);
}

const bool PimpMessage::isCommand(PimpMessage::CommandType cmd) const
{
  XmlElement *command = _message->getChildByName("Command");
  if (command)
    if (command->hasAttribute("Value"))
      return (CommandType)command->getIntAttribute("Value") == cmd;
  return false;
}

void PimpMessage::setCommand(PimpMessage::CommandType cmd)
{
  XmlElement *command = _message->getChildByName("Command");
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

const bool PimpMessage::hasPeerFile() const
{
  XmlElement *file = _message->getChildByName("PeerFile");
  if (file)
    return file->hasAttribute("Name");
  return false;
}

const PeerFile PimpMessage::getPeerFile() const
{
  XmlElement *file = _message->getChildByName("File");
  if (file)
    if (file->hasAttribute("Name"))
    {
      
    }
  return PeerFile::emptyPeerFile();
}

const bool PimpMessage::hasByteRange() const
{
  XmlElement *file = _message->getChildByName("File");
  if (file)
    return file->hasAttribute("Start") && file->hasAttribute("End");
  return false;
}

const juce::Range<int> PimpMessage::getByteRange() const
{
  XmlElement *file = _message->getChildByName("File");
  if (file)
    if (file->hasAttribute("Start") && file->hasAttribute("End"))
    {
      juce::Range<int> byteRange;
      byteRange.setStart(file->getIntAttribute("Start"));
      byteRange.setEnd(file->getIntAttribute("End"));
      return byteRange;
    }
  return juce::Range<int>::emptyRange(0);
}

const bool PimpMessage::hasKeywordsArray() const
{
  XmlElement *keywordsArray = _message->getChildByName("KeywordsArray");
  if (keywordsArray) return true;
  return false;
}

const juce::StringArray PimpMessage::getKeywordsArray() const
{
  juce::StringArray keywordsArray;
  XmlElement *keywordsArrayXml = _message->getChildByName("KeywordsArray");
  if (keywordsArrayXml)
  {
    
  }
  return keywordsArray;
}

void PimpMessage::createPeerGetFile(PeerFile file)
{
  XmlElement* commandXml = new XmlElement("Command");
  commandXml->setAttribute("Value", juce::String(kPeerGetFile));
  _message->addChildElement(commandXml);
  
  XmlElement* fileXml = new XmlElement("PeerFile");
  
  XmlElement *dummyName = new XmlElement("Name");
  dummyName->setAttribute("Value", file.getFile().getFileName());
  fileXml->addChildElement(dummyName);
  
  XmlElement *dummyMD5 = new XmlElement("MD5");
  dummyMD5->setAttribute("Value",file.getMD5().toHexString());
  fileXml->addChildElement(dummyMD5);
  
  _message->addChildElement(fileXml);
}

void PimpMessage::createPeerGetFile(PeerFile file,
                                    juce::Range<int> byteRange)
{
  createPeerGetFile(file);
  XmlElement *fileXml = _message->getChildByName("PeerFile");
  
  XmlElement *dummyStart = new XmlElement("Start");
  dummyStart->setAttribute("Value", byteRange.getStart());
  fileXml->addChildElement(dummyStart);
  
  XmlElement *dummyEnd = new XmlElement("Start");
  dummyEnd->setAttribute("Value", byteRange.getEnd());
  fileXml->addChildElement(dummyEnd);
}

void PimpMessage::createPeerSearch(juce::StringArray keywords)
{
  XmlElement* commandXml = new XmlElement("Command");
  commandXml->setAttribute("Value", juce::String(kPeerSearch));
  _message->addChildElement(commandXml);
  
  XmlElement *keywordsArrayXml = new XmlElement("KeywordsArray");
  for (juce::String* string = keywords.begin();
       string != keywords.end(); string++)
  {
    XmlElement *dummyKeyword = new XmlElement("Keyword");
    dummyKeyword->setAttribute("Value", *string);
    keywordsArrayXml->addChildElement(dummyKeyword);
  }
  _message->addChildElement(keywordsArrayXml);
}