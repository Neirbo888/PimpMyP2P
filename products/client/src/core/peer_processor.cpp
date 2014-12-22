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
  Logger::writeToLog("Unhandled ActionListener callback");  
}

void PeerProcessor::handleAsyncUpdate()
{
  if (_state == kRegistered ||
      _state == kShouldRegister)
  {
    registerToTracker();
  }
  else
  {
    Logger::writeToLog("Unhandled AsyncUpdate callback");
  }
}

void PeerProcessor::stop()
{
  signalThreadShouldExit();
  stopThread(2000);
}

void PeerProcessor::run()
{
  // This ensure that we exit the thread when the threadShouldStop flag was
  // raised
  while(!threadShouldExit())
  {
    // Wait indefinitly until someone notifies the thread, provoking something
    // to happen (or not) in the state machine.
    if(this->wait(-1))
    {
      // This might be unnecessary but it ensure that when we've raised the
      // threadShouldStop flag, the thread is stopping like right now
      if (threadShouldExit())
      {
        Logger::writeToLog("Closing PeerProcessor thread");
        return;
      }
      // Let's look at the state of our PeerProcessor
      switch (_state)
      {
        case kUninitialized:
          // If the socket has failed to connect, there's nothing we can do,
          // we go to kUnavailable
          if (!_socketThread->isConnected())
          {
            /// @todo publish something on the ui
            Logger::writeToLog("Couldn't create listener on port 4807");
            setState(kUnavailable);
          }
          // If the Socket is connected, everything's allright, let's move on
          else
            setState(kIdle);
          break;
          
        case kShouldRegister:
          // Trying to resiter are we ?
          registerToTracker();
          break;
          
        case kShouldDownloadFile:
          // We should prepare to download
          downloadQueuedPeerFile();
          
        default:
          break;
      }
      sendChangeMessage();
    }
  }
}

void PeerProcessor::setSharedFolder(const juce::File& folder)
{
  _fileManager.setSharedFolder(folder);
}

void PeerProcessor::queuePeerFileTask(PeerFile file)
{
  if (_state != kRegistered)
  {
    Logger::writeToLog("Enable to queue" + file.getFilename());
    return;
  }
  
  
  setState(kShouldDownloadFile);
}

void PeerProcessor::downloadQueuedPeerFile()
{
  if (_queuedFile == PeerFile::emptyPeerFile())
  {
    Logger::writeToLog("Can't download empty file");
    return;
  }
  // Create our PimpMessage request
  PimpMessage request = PimpMessage::createPeerFileRequest(_queuedFile);
  
  
  // Prepare a stream output file to write the data
  juce::File outputFile (_fileManager.getSharedFolder().getFullPathName() +
                         juce::File::separator +
                         _queuedFile.getFilename());
  juce::FileOutputStream streamFile (outputFile);
  juce::Array<juce::IPAddress> peers = _queuedFile.getPeersAddresses();
  if (outputFile.existsAsFile())
  {
    Logger::writeToLog("Can't receive an already existing file");
    return;
  }
  if (streamFile.openedOk())
  {
    Logger::writeToLog("Can't open output stream");
    return;
  }
  
  if (peers.size() == 0)
  {
    Logger::writeToLog("Can't find any peers with this file");
    return;
  }
  
  Logger::writeToLog("Ready to download");
  
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
          Logger::writeToLog(_queuedFile.getFilename() +
                             " has been successfuly downloaded");
          setState(kRegistered);
          return;
        }
        else
        {
          Logger::writeToLog(_queuedFile.getFilename() +
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
  {
    /// @todo publish something on the ui
    Logger::writeToLog("Can't connect to distant host");
  }
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
    setState(kIdle);
    return;
  }
  ScopedPointer<StreamingSocket> socket = new StreamingSocket();
  socket->connect(_tracker.toString(), 4807);
  
  if (!socket->isConnected())
  {
    /// @todo publish something on the ui
    Logger::writeToLog("Can't connect to distant host");
    setState(kIdle);
  }
  else
  {
    PimpMessage registerRequest = PimpMessage::createPeerRefresh(_fileManager.getAvailableFiles());
    registerRequest.sendToSocket(socket, _address);
    
    // Normally we should receive an acknowledge
    PimpMessage acknowledge = PimpMessage::createFromSocket(socket);
    if (acknowledge.isOk())
    {
      setState(kRegistered);
    }
    else
    {
      _tracker = juce::IPAddress();
      setState(kIdle);
    }
  }
}

void PeerProcessor::unregisterToTracker()
{
  if (_tracker.toString() == "0.0.0.0")
  {
    setState(kIdle);
    return;
  }
  ScopedPointer<StreamingSocket> socket = new StreamingSocket();
  socket->connect(_tracker.toString(), 4807);
  
  if (!socket->isConnected())
  {
    /// @todo publish something on the ui
    Logger::writeToLog("Can't connect to distant host");
    setState(kIdle);
    return;
  }
  else
  {
    PimpMessage unregisterRequest = PimpMessage::createPeerSignOut();
    unregisterRequest.sendToSocket(socket, _address);
    setState(kIdle);
  }
  socket->close();
}