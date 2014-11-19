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

const bool PimpMessage::hasFilename() const
{
  XmlElement *file = _message->getChildByName("File");
  if (file)
    return file->hasAttribute("Name");
  return false;
}

const juce::String PimpMessage::getFilename() const
{
  XmlElement *file = _message->getChildByName("File");
  if (file)
    if (file->hasAttribute("Name"))
      return file->getStringAttribute("Name");
  return juce::String::empty;
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

void PimpMessage::createSendRequest(juce::String filename)
{
  XmlElement* commandXml = new XmlElement("Command");
  commandXml->setAttribute("Value", juce::String(kPeerGetFile));
  _message->addChildElement(commandXml);
  
  XmlElement* fileXml = new XmlElement("File");
  fileXml->setAttribute("Name", filename);
  _message->addChildElement(fileXml);
}

void PimpMessage::createSendRequest(juce::String filename,
                                    juce::Range<int> byteRange)
{
  createSendRequest(filename);
  XmlElement *fileXml = _message->getChildByName("File");
  fileXml->setAttribute("Start", byteRange.getStart());
  fileXml->setAttribute("End", byteRange.getEnd());
}