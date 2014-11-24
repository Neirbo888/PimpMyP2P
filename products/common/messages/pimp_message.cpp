#include "products/common/messages/pimp_message.h"

PimpMessage::PimpMessage(juce::IPAddress srcIp)
: _message(new XmlElement("PimpMessage"))
{
  auto sourceIpXml = new XmlElement("SourceIp");
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

const bool PimpMessage::hasPeerFile() const
{
  auto file = _message->getChildByName("PeerFile");
  if (file)
    return file->hasAttribute("Name") &&
           file->hasAttribute("MD5") &&
           file->hasAttribute("Size");
  return false;
}

const PeerFile PimpMessage::getPeerFile() const
{
  auto file = _message->getChildByName("PeerFile");
  if (file)
    if (file->hasAttribute("Name") &&
        file->hasAttribute("MD5") &&
        file->hasAttribute("Size"))
    {
      return PeerFile(file->getStringAttribute("Name"),
                      file->getStringAttribute("MD5"),
                      file->getIntAttribute("Size"));
    }
  return PeerFile::emptyPeerFile();
}

const bool PimpMessage::hasByteRange() const
{
  auto range = _message->getChildByName("Range");
  if (range)
    return range->hasAttribute("Start") && range->hasAttribute("End");
  return false;
}

const juce::Range<int> PimpMessage::getByteRange() const
{
  auto range = _message->getChildByName("Range");
  if (range)
    if (range->hasAttribute("Start") && range->hasAttribute("End"))
    {
      juce::Range<int> byteRange;
      byteRange.setStart(range->getIntAttribute("Start"));
      byteRange.setEnd(range->getIntAttribute("End"));
      return byteRange;
    }
  return juce::Range<int>::emptyRange(0);
}

const bool PimpMessage::hasKeywordsArray() const
{
  auto keywordsArray = _message->getChildByName("KeywordsArray");
  if (keywordsArray) return true;
  return false;
}

const juce::StringArray PimpMessage::getKeywordsArray() const
{
  juce::StringArray keywordsArray;
  auto keywordsArrayXml = _message->getChildByName("KeywordsArray");
  if (keywordsArrayXml)
  {
    
  }
  return keywordsArray;
}

void PimpMessage::createPeerGetFile(PeerFile file)
{
  auto commandXml = new XmlElement("Command");
  commandXml->setAttribute("Value", juce::String(kPeerGetFile));
  _message->addChildElement(commandXml);
  
  auto fileXml = new XmlElement("PeerFile");
  
  auto dummyName = new XmlElement("Name");
  dummyName->setAttribute("Value", file.getFile().getFileName());
  fileXml->addChildElement(dummyName);
  
  auto dummyMD5 = new XmlElement("MD5");
  dummyMD5->setAttribute("Value",file.getMD5());
  fileXml->addChildElement(dummyMD5);
  
  auto dummySize = new XmlElement("Size");
  dummySize->setAttribute("Value", (double)(file.getFile().getSize()));
  fileXml->addChildElement(dummySize);
  
  _message->addChildElement(fileXml);
}

void PimpMessage::createPeerGetFile(PeerFile file,
                                    juce::Range<int> byteRange)
{
  createPeerGetFile(file);
  auto rangeXml = new XmlElement("Range");
  
  auto dummyStart = new XmlElement("Start");
  dummyStart->setAttribute("Value", byteRange.getStart());
  rangeXml->addChildElement(dummyStart);
  
  auto dummyEnd = new XmlElement("End");
  dummyEnd->setAttribute("Value", byteRange.getEnd());
  rangeXml->addChildElement(dummyEnd);
  
  _message->addChildElement(rangeXml);
}

void PimpMessage::createPeerSearch(juce::StringArray keywords)
{
  auto  commandXml = new XmlElement("Command");
  commandXml->setAttribute("Value", juce::String(kPeerSearch));
  _message->addChildElement(commandXml);
  
  auto keywordsArrayXml = new XmlElement("KeywordsArray");
  for (juce::String s : keywords)
  {
    auto dummyKeyword = new XmlElement("Keyword");
    dummyKeyword->setAttribute("Value", s);
    keywordsArrayXml->addChildElement(dummyKeyword);
  }
  _message->addChildElement(keywordsArrayXml);
}

void PimpMessage::createErrorMessage(juce::String message)
{
  auto errorMessage = new XmlElement("Error");
  errorMessage->addTextElement(message);
  _message->addChildElement(errorMessage);
}