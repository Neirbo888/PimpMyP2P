#ifndef PIMP_MESSAGE_H_INCLUDED
#define PIMP_MESSAGE_H_INCLUDED

#include "JuceHeader.h"
#include "products/common/files/peer_file.h"

/// @class PimpMessage
/// @brief Complex messages generator
class PimpMessage
{
public:
  
  /// @brief Construct with a xml formatted string
  PimpMessage(const std::string& xmlData);
  
  /// @brief Destructor
  ~PimpMessage();
  
  /// @brief Get the PeerFile object held in this PimpMessage if there is one
  const PeerFile getPeerFile() const;
  
  /// @brief True if the current PimpMessage holds a PeerFile
  const bool hasPeerFile() const;
  
  /// @brief Returns an XML formatted string containing this PimpMessage
  const juce::String getXmlString() const;
  
  /// @brief True if the current PimpMessage holds a source ip
  const bool hasSource() const;
  
  /// @brief Will return the source of the message if the current PimpMessage
  const juce::IPAddress getSource() const;
  
  /// @brief True if this PimpMessage has a Range attribute defined
  const bool hasRange() const;
  
  /// @brief Will return the range of the file or juce::Range::empty if there's
  /// either no range defined or even no File attribute at all
  const juce::Range<int> getRange() const;
  
  /// @brief True if this PimpMessage has a PartNumber attribute defined
  const bool hasPartNumber() const;
  
  /// @brief Will return the number of the part or -1 if there's no PartNumber
  /// attribute in this PimpMessage
  const int getPartNumber() const;
  
  /// @brief True if this PimpMessage has a SearchString
  const bool hasSearchString() const;
  
  /// @brief Will return the search that was input if the message has a
  /// SearchString attribute, if not the String will be empty
  const juce::String getSearchString() const;
  
  /// @brief True if this PimpMessage has a SearchResults
  const bool hasSearchResults() const;
  
  /// @brief Will return a list of PeerFile if the message has a SearchResults
  /// attribute, if not the list will be empty
  juce::Array<PeerFile> getSearchResults();
  
  /// @brief True if this PimpMessage has a Local Filelist
  const bool hasLocalFileList() const;
  
  /// @brief Will return the local file list if this PimpMessage has one
  const juce::Array<PeerFile> getLocalFileList() const;
  
  ///////////////////////// MESSAGE NATURE ////////////////////////////////////
  
  /// @brief True if this PimpMessage is a kPeerRefresh
  const bool isPeerRefresh() const { return isCommand(kPeerRefresh); }
  
  /// @brief True if this PimpMessage is a kPeerSignOut
  const bool isPeerSignOut() const  { return isCommand(kPeerSignOut); }
  
  /// @brief True if this PimpMessage is a kError
  const bool isError() const  { return isCommand(kError); }
  
  /// @brief True if this PimpMessage is a kPeerFileRequest
  const bool isPeerFileRequest() const  { return isCommand(kPeerFileRequest); }
  
  /// @brief True if this PimpMessage is a kPeerFileSend
  const bool isPeerFileSend() const  { return isCommand(kPeerFileSend); }
  
  /// @brief True if this PimpMessage is a kPeerSearch
  const bool isPeerSearch() const  { return isCommand(kPeerSearch); }
  
  /// @brief True if this PimpMessage is a kTrackerSearchResult
  const bool isTrackerSearchResult() const
  {
    return isCommand(kTrackerSearchResult);
  }
  
  /// @brief True if this PimpMessage is a kOk
  const bool isOk() const  { return isCommand(kOk); }
  
  ///////////////////////// MESSAGES CREATION /////////////////////////////////
  
  /// @brief Creates a PeerGetFile request to download a file from another peer
  /// @param {PeerFile} file - File to download
  static PimpMessage createPeerFileRequest(PeerFile file);
  
  /// @brief Creates a search request for the tracker
  /// @param {juce::StringArray} keywords - Array containing all the keywords
  static PimpMessage createPeerSearch(const juce::String keystring);
  
  /// @brief Creates an error message
  /// @param {juce::String} message - Error message string
  static PimpMessage createErrorMessage(const juce::String message);
  
  /// @brief Create a tracker search result message based on the given PeerFile
  /// list
  /// @param {juce::Array<PeerFile>} peerFiles - Files that has been found
  static PimpMessage createTrackerSearchResult(const juce::Array<PeerFile>& files);
 
  /// @brief Create a sign in message that will be sent from a peer to the
  /// tracker
  static PimpMessage createPeerRefresh(const juce::Array<PeerFile> localFiles);
  
  /// @brief Create a sign out message that will be sent from a peer to the
  /// tracker
  static PimpMessage createPeerSignOut();
  
  /// @brief Create a OK message
  static PimpMessage createOk();
  
  /// @brief Create a PimpMessage from received from the given socket
  /// @param {juce::StreamingSocket*} socket - An opened and connected socket
  /// where the PimpMessage will be read.
  static PimpMessage createFromSocket(juce::StreamingSocket* socket);
  
  ////////////////////////// SOCKET //////////////// //////////////////////////
  
  /// @brief Send the current PimpMessage to the given socket
  /// @param {juce::StreamingSocket*} socket - Socket where the message will be
  /// sent
  /// @param {juce::IPAddress} source - IP Address of the computer sending this
  /// request
  void sendToSocket(juce::StreamingSocket* socket,
                    juce::IPAddress source);
  
  /// @brief Constructs a PimpMessage as a copy of another one
  /// @param {PeerFile} otherMessage - PimpMessage that will be copied
  PimpMessage(const PimpMessage & otherMessage);
  
private:
  ////////////////////// COMMAND SETTING AND GETTING /////////////////////////
  
  /// @enum CommandType
  /// @brief List of all command that can be generated
  enum CommandType
  {
    kPeerFileRequest = 0, ///< Used among peers to request files
    kPeerFileSend = 1, ///< Used among peers to send files
    kPeerRefresh = 2, ///< A peer wants to refresh its status with the tracker
    kPeerSignOut = 3, ///< A peer is signing out from the tracker
    kPeerSearch = 4, ///< A peer sends a search to the tracker
    kTrackerSearchResult = 5, ///< The tracker sends the result of a search
    kOk = 6, ///< Confirmation
    kError = 7, ///< Error
    kMaxCount ///< Command count
  };
  
  /// @brief Sets the command of this PimpMessage
  void setCommand(CommandType cmd);
  
  /// @brief True if the given command is the same as the current PimpMessage
  const bool isCommand(CommandType cmd) const;
  
  
  ////////////////////////////// HELPERS /////////////////////////////////////
  
  /// @brief True if the given XmlElement looks like a valid PeerFile field
  /// @param {juce::XmlElement*} element - The XmlElement holding the PeerFile
  /// informations
  static const bool hasValidPeerFile(juce::XmlElement* element);
  
  /// @brief Append a PeerFile field to the given XmlElement
  /// @param {const PeerFile&} file - The PeerFile that will be appended
  static juce::XmlElement* getXmlElementFromPeerFile(PeerFile file);
  
  /// @brief Returns a PeerFile object from informations held in an XmlElement
  /// @param {juce::XmlElement*} element - The XmlElement holding the PeerFile
  /// informations
  static const PeerFile getPeerFileFromXmlElement(juce::XmlElement* element);
  
  /// @brief Private constructor setting command
  PimpMessage(CommandType type);
  
  /// @brief The content of a PimpMessage is stored in a XmlElement
  ScopedPointer<juce::XmlElement> _message;
};


#endif  // PIMP_MESSAGE_H_INCLUDED
