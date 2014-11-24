#ifndef PIMP_MESSAGE_H_INCLUDED
#define PIMP_MESSAGE_H_INCLUDED

#include "JuceHeader.h"
#include "products/common/files/peer_file.h"

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
    kPeerSearch, ///< A peer sends a search to the tracker
    kTrackerSearchResult, ///< The tracker sends the result of a search
    kOk, ///< Confirmation
    kError, ///< Error
    kMaxCount
  };
  
  /// @brief Construct with a xml formatted string
  PimpMessage(const std::string& xmlData);
  
  /// @brief Construct with the source ip address
  PimpMessage(juce::IPAddress srcIp);
  
  /// @brief Destructor
  ~PimpMessage();
  
  /// @brief Returns an XML formatted string containing this PimpMessage
  const juce::String getXmlString() const;
  
  /// @brief True if the given command is the same as the current PimpMessage
  const bool isCommand(CommandType cmd) const;
  
  /// @brief Sets the command of this PimpMessage
  void setCommand(CommandType cmd);
  
  /// @brief True if this PimpMessage has a PeerFile attribute
  const bool hasPeerFile() const;
  
  /// @brief Will return the name of the file or juce::String::empty if there's
  /// either no file name defined or even no File attribute at all
  const PeerFile getPeerFile() const;
  
  /// @brief True if this PimpMessage has a File attribute with a byte range
  /// defined
  const bool hasByteRange() const;
  
  /// @brief Will return the range of the file or juce::Range::empty if there's
  /// either no range defined or even no File attribute at all
  const juce::Range<int> getByteRange() const;
  
  /// @brief True if this PimpMessage has a keywords array
  const bool hasKeywordsArray() const;
  
  /// @brief Will return a StringArray filled with all the keywords if the
  /// message has a KeywordsArray attribute, if not the StringArray will be
  /// empty
  const juce::StringArray getKeywordsArray() const;
  
  /// @brief Send the current PimpMessage to the given socket
  /// @param {juce::StreamingSocket*} socket - Socket where the message will be
  /// sent
  void sendToSocket(juce::StreamingSocket* socket);
  
  /// @brief Creates a PeerGetFile request to download a file from another peer
  /// @param {PeerFile} file - File to download
  void createPeerGetFile(PeerFile file);
  
  /// @brief Creates a PeerGetFile request to download a file part from another
  /// peer
  /// @param {PeerFile} file - File to download
  /// @param {juce::Range<int>} byteRange - Range of the part to download
  void createPeerGetFile(PeerFile file,
                         juce::Range<int> byteRange);
  
  /// @brief Creates a search request for the tracker
  /// @param {juce::StringArray} keywords - Array containing all the keywords
  void createPeerSearch(juce::StringArray keywords);
  
  /// @brief Creates an error message
  /// @param {juce::String} message - Error message string
  void createErrorMessage(juce::String message);
  
private:
  /// @brief Default constructor is private
  PimpMessage();
  
  /// @brief The content of a PimpMessage is stored in a XmlElement
  juce::ScopedPointer<juce::XmlElement> _message;
};


#endif  // PIMP_MESSAGE_H_INCLUDED
