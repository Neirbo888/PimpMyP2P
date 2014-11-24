#include "products/common/messages/pimp_message.h"
#include "products/common/network/socket_thread.h"
#include "products/common/ui/component_window.h"
#include "products/client/src/ui/main_window.h"
#include "products/client/src/core/peer_processor.h"
#include "products/client/src/core/peer_message_handler.h"

PeerProcessor::PeerProcessor()
: Thread("PimpPeer"),
  _fileManager(this),
  _messageHandler(nullptr),
  _socketThread(nullptr)
{
  // Create the GUI
  _component = new MainWindow(this);
  _window = new ComponentWindow(_component);
  
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
  
  if (!_socketThread->isConnected())
    Logger::writeToLog("Couldn't create listener on port 4807");
  
  startThread();
}

PeerProcessor::~PeerProcessor()
{
  stop();
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
  while(!threadShouldExit())
    this->wait(100000);
  Logger::writeToLog("Closing PeerProcessor thread");
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
    Logger::writeToLog("Can't connect to distant host");
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
    //_component->publishResults(results.getSearchResults());
  }
}