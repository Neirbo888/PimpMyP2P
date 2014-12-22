#include "products/common/messages/pimp_message.h"
#include "products/common/network/socket_thread.h"
#include "products/common/ui/component_window.h"
#include "products/client/src/ui/peer_ui.h"
#include "products/client/src/core/peer_processor.h"
#include "products/client/src/core/peer_message_handler.h"

PeerProcessor::PeerProcessor()
: Thread("PimpPeer"),
  _fileManager(this),
  _messageHandler(nullptr),
  _ui(nullptr),
  _window(nullptr),
  _socketThread(nullptr),
  _state(kUninitialized),
  _progress(0)
{
  // Create the GUI
  _ui = new PeerUi(this);
  addChangeListener(_ui);
  _window = new ComponentWindow(_ui);
  
  // Get the local IP address
  Array<IPAddress> allAddresses;
  IPAddress::findAllAddresses(allAddresses);
  for (int i = 0; i < allAddresses.size(); i++)
    if (allAddresses.getReference(i).toString().startsWith("192.168."))
      _address = allAddresses.getUnchecked(i);
  
  // If no local network is connected, lets initialize with the loopback ip
  if (_address.toString().equalsIgnoreCase("0.0.0.0"))
    _address = juce::IPAddress::local();
  
  // Create our MessageHandler
  _messageHandler = new PeerMessageHandler(_address, _fileManager);
  
  // Create our SocketThread
  _socketThread = new SocketThread(4807, _messageHandler);
  
  startThread();
  this->notify();
}

PeerProcessor::~PeerProcessor()
{
  stop();
  unregisterToTracker();
}

void PeerProcessor::setState(StateType state)
{
  if (_state != state)
  {
    _state = state;
    this->notify();
  }
}
void PeerProcessor::actionListenerCallback(const String& message)
{
  publishLogMessage("Unhandled ActionListener callback");
}

void PeerProcessor::handleAsyncUpdate()
{
  if (_state == kRegistered ||
      _state == kShouldRegister)
  {
    registerToTracker();
  }
  else if (_state == kAnalyzing)
  {
    publishLogMessage("Shared folder is now "
                      + _fileManager.getSharedFolder().getFullPathName());
    setState(kReadyToRegister);
  }
  else
  {
    publishLogMessage("Unhandled AsyncUpdate callback");
  }
}

void PeerProcessor::stop()
{
  signalThreadShouldExit();
  stopThread(2000);
}

void PeerProcessor::run()
{
  while(!threadShouldExit())
  {
    if(this->wait(-1))
    {
      if (threadShouldExit())
      {
        Logger::writeToLog("Closing PeerProcessor thread");
        return;
      }
      switch (_state)
      {
        case kUninitialized:
          if (!_socketThread->isConnected())
          {
            /// @todo publish something on the ui
            publishLogMessage("Couldn't create listener on port 4807");
            setState(kUnavailable);
          }
          else
            setState(kIdle);
          break;
          
        case kShouldRegister:
          registerToTracker();
          break;
          
        case kShouldDownloadFile:
          downloadQueuedPeerFile();
          break;
          
        case kAnalyzing:
          _fileManager.startThread();
          break;
          
        default:
          break;
      }
      sendChangeMessage();
    }
  }
}

void PeerProcessor::setSharedFolder(const juce::File& folder)
{
  if (folder.exists())
  {
    _fileManager.setSharedFolder(folder);
    setState(kAnalyzing);
  }
  else
  {
    publishLogMessage("The folder is invalid");
  }
}

void PeerProcessor::queuePeerFileTask(PeerFile file)
{
  if (_state != kRegistered)
  {
    publishLogMessage("Enable to queue" + file.getFilename());
    return;
  }
  
  _queuedFile = file;
  setState(kShouldDownloadFile);
}

void PeerProcessor::downloadQueuedPeerFile()
{
  if (_queuedFile == PeerFile::emptyPeerFile())
  {
    publishLogMessage("Can't download empty file");
    return;
  }
  // Create our PimpMessage request
  PimpMessage request = PimpMessage::createPeerFileRequest(_queuedFile);
  
  
  // Prepare a stream output file to write the data
  juce::File outputFile (_fileManager.getSharedFolder().getFullPathName() +
                         juce::File::separator +
                         _queuedFile.getFilename());
  juce::Array<juce::IPAddress> peers = _queuedFile.getPeersAddresses();
  if (outputFile.existsAsFile())
  {
    publishLogMessage("Can't receive an already existing file");
    return;
  }
  
  if (peers.size() == 0)
  {
    publishLogMessage("Can't find any peers with this file");
    return;
  }
  
  publishLogMessage("Ready to download");
  
  for (juce::IPAddress peer : peers)
  {
    juce::ScopedPointer<StreamingSocket> socket = new StreamingSocket();
    socket->connect(peer.toString(), 4807);
    if (socket->isConnected())
    {
      request.sendToSocket(socket, _address);
      PimpMessage acknowledge = PimpMessage::createFromSocket(socket);
      if (acknowledge.isOk())
      {
        if (_fileManager.receiveFileFromSocket(_queuedFile, socket))
        {
          publishLogMessage(_queuedFile.getFilename() +
                            " has been successfuly downloaded");
          juce::File result (_fileManager.getSharedFolder().getFullPathName() +
                           juce::File::separator +
                           _queuedFile.getFilename());
          PeerFile resultPeer (result);
          publishLogMessage("MD5: " + _queuedFile.getMD5() +
                            " vs. " + resultPeer.getMD5());
          setState(kRegistered);
          return;
        }
        else
        {
          publishLogMessage(_queuedFile.getFilename() +
                            " has failed from peer : " + peer.toString());
        }
      }
    }
  }
}

void PeerProcessor::sendTrackerSearch(const juce::String keystring)
{
  PimpMessage request = PimpMessage::createPeerSearch(keystring);
  
  // Create a new socket to connect to our distant host
  ScopedPointer<StreamingSocket> socket = new StreamingSocket();
  socket->connect(_tracker.toString(), 4807);
  
  if (!socket->isConnected())
    publishLogMessage("Can't connect to distant host");
  else
  {
    request.sendToSocket(socket, _address);
    
    // Normally we should receive an acknowledge
    PimpMessage acknowledge = PimpMessage::createFromSocket(socket);
    
    // If the message receive is OK
    if (acknowledge.isOk())
    {
      PimpMessage results = PimpMessage::createFromSocket(socket);
      if (results.isTrackerSearchResult() && results.hasSearchResults())
      {
        juce::Array<PeerFile> resultArray = results.getSearchResults();
        _ui->publishSearchResults(resultArray);
      }
    }
  }
}

void PeerProcessor::registerToTracker()
{
  if (_tracker.toString() == "0.0.0.0")
  {
    publishLogMessage("Tracker ip is invalid");
    setState(kReadyToRegister);
    return;
  }
  ScopedPointer<StreamingSocket> socket = new StreamingSocket();
  socket->connect(_tracker.toString(), 4807);
  
  if (!socket->isConnected())
  {
    /// @todo publish something on the ui
    publishLogMessage("Can't connect to distant host");
    setState(kReadyToRegister);
  }
  else
  {
    PimpMessage registerRequest = PimpMessage::createPeerRefresh(_fileManager.getAvailableFiles());
    registerRequest.sendToSocket(socket, _address);
    
    // Normally we should receive an acknowledge
    PimpMessage acknowledge = PimpMessage::createFromSocket(socket);
    if (acknowledge.isOk())
    {
      publishLogMessage("Connected to " + _tracker.toString());
      setState(kRegistered);
    }
    else
    {
      _tracker = juce::IPAddress();
      publishLogMessage("Distant host is not ready");
      setState(kReadyToRegister);
    }
  }
}

void PeerProcessor::unregisterToTracker()
{
  if (_tracker.toString() == "0.0.0.0")
  {
    setState(kReadyToRegister);
    return;
  }
  ScopedPointer<StreamingSocket> socket = new StreamingSocket();
  socket->connect(_tracker.toString(), 4807);
  
  if (!socket->isConnected())
  {
    publishLogMessage("Can't connect to distant host");
    setState(kReadyToRegister);
    return;
  }
  else
  {
    PimpMessage unregisterRequest = PimpMessage::createPeerSignOut();
    unregisterRequest.sendToSocket(socket, _address);
    setState(kReadyToRegister);
    _tracker = juce::IPAddress();
  }
  socket->close();
}

void PeerProcessor::publishLogMessage(const juce::String &message)
{
  
  const MessageManagerLock mmLock (Thread::getCurrentThread());
  if (mmLock.lockWasGained())
    _ui->setStatusMessage(message);
  else
    Logger::writeToLog("KIKOOO");
  Logger::writeToLog(message);
}