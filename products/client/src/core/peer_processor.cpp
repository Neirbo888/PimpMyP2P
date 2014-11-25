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
  _state(kUninitialized)
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
  Logger::writeToLog("Unhandled async update");
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

void PeerProcessor::sendPeerGetFile(PeerFile file)
{
  // Create our PimpMessage request
  PimpMessage request (_address);
  request.createPeerGetFile(file);
  
  
  // Prepare a stream output file to write the data
  juce::File outputFile (_fileManager.getSharedFolder().getFullPathName() +
                         juce::File::separator +
                         file.getFilename());
  juce::FileOutputStream streamFile (outputFile);
  
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
  
  // Create a new socket to connect to our distant host
  ScopedPointer<StreamingSocket> socket = new StreamingSocket();
  socket->connect("DU LOL", 4807);
  
  // If connection can't be done, we get out
  if (!socket->isConnected())
  {
    Logger::writeToLog("Can't connect to distant host");
  }
  
  // Else, we can send the request
  else
  {
    // Let's send him the request
    request.sendToSocket(socket);
    
    // Normally we should receive an acknowledge
    char inBuffer[4096];
    socket->read(inBuffer,4096,false);
    PimpMessage acknowledge (inBuffer);
    
    if (acknowledge.isCommand(PimpMessage::kOk))
    {
      int bytesRead;
      do
      {
        int bytesRead = socket->read(inBuffer,4096,false);
        streamFile.write(inBuffer, bytesRead);
      } while (bytesRead == 4096);
    }
  }
}

void PeerProcessor::sendTrackerSearch(const juce::String keystring)
{
  PimpMessage request (_address);
  request.createPeerSearch(keystring);
  
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
    request.sendToSocket(socket);
    
    // Normally we should receive an acknowledge
    char inBuffer[4096];
    socket->read(inBuffer,4096,false);
    PimpMessage acknowledge (inBuffer);
    juce::String xmlResult;
    if (acknowledge.isCommand(PimpMessage::kOk))
    {
      int bytesRead;
      do
      {
        int bytesRead = socket->read(inBuffer,4096,false);
        xmlResult += inBuffer;
      } while (bytesRead == 4096);
    }
    PimpMessage results (xmlResult.toStdString());
    /// @todo publish something on the ui
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
  }
  else
  {
    PimpMessage registerRequest (_address);
    registerRequest.createPeerSignIn();
    registerRequest.sendToSocket(socket);
    
    // Normally we should receive an acknowledge
    char inBuffer[4096];
    socket->read(inBuffer,4096,false);
    PimpMessage acknowledge (inBuffer);
    if (acknowledge.isCommand(PimpMessage::kOk))
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
  if (_tracker.toString() == "0.0.0.0") return;
  ScopedPointer<StreamingSocket> socket = new StreamingSocket();
  socket->connect(_tracker.toString(), 4807);
  
  if (!socket->isConnected())
  {
    /// @todo publish something on the ui
    Logger::writeToLog("Can't connect to distant host");
  }
  else
  {
    PimpMessage unregisterRequest (_address);
    unregisterRequest.createPeerSignOut();
    unregisterRequest.sendToSocket(socket);
    setState(kIdle);
  }
  socket->close();
}