#ifndef PIMP_MESSAGE_H_INCLUDED
#define PIMP_MESSAGE_H_INCLUDED

#include "JuceHeader.h"

/// @class PimpMessage
/// @brief Complex messages generator
class PimpMessage
{
public:
  
  /// @enum CommandType
  /// @brief List of all command that can be generated
  enum CommandType
  {
    kPeerGetFile = 0, ///< Used among peers to request files
    kTrackerRequestFiles, ///< A file list request from the tracker
    kPeerSignIn, ///< A peer wants to sign in the tracker
    kPeerSignOut, ///< A peer is signing out from the tracker
    kPeerFileList, ///< A peer sends its file list
    kTrackerSearchResult, ///< The tracker sends the result of a search
    kReady, ///< Distant host is ready
    kError, ///< Error
    kMaxCount
  };
  
  /// @brief Construct with a xml formatted string
  PimpMessage(const std::string& xmlData);
  
  /// @brief Construct with the source ip address
  PimpMessage(juce::IPAddress srcIp);
  
  /// @brief Destructor
  ~PimpMessage();
  
  const juce::String getXmlString() { return _message->createDocument(juce::String::empty); }
  
  /// @brief True if the given command is the same as the current PimpMessage
  const bool isCommand(CommandType cmd) const;
  
  /// @brief Sets the command of this PimpMessage
  void setCommand(CommandType cmd);
  
  /// @brief Creates a send request for a peer to send a file
  void createSendRequest(juce::String filename);
  
  /// @brief Creates a send request for a peer to send a part of a file
  void createSendRequest(juce::String filename,
                         juce::Range<int> byteRange);
  
  /// @brief True if this PeerGetFile has a filename
  const bool hasFilename() const;
  
  /// @brief If command is a PeerGetFile, will return the name of the file requested or juce::String::empty if not
  const juce::String getFilename() const;
  
  /// @brief True if this PeerGetFile has a byte range
  const bool hasByteRange() const;
  
  /// @brief If command is a PeerGetFile, will return the range of the file requested or juce::Range::empty if not
  const juce::Range<int> getByteRange() const;

  //PimpMessage(const PimpMessage &);
  
private:
  PimpMessage();
  
  ScopedPointer<XmlElement> _message;
};


#endif  // PIMP_MESSAGE_H_INCLUDED
