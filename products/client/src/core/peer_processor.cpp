#include "products/common/messages/pimp_message.h"
#include "products/common/network/socket_thread.h"
#include "products/common/ui/component_window.h"
#include "products/client/src/ui/main_window.h"
#include "products/client/src/core/peer_processor.h"
#include "products/client/src/core/peer_message_handler.h"

PeerProcessor::PeerProcessor()
: Thread("PimpClient"),
  _messageHandler(nullptr),
  _socketThread(nullptr)
{
  // Create the GUI
  _component = new MainWindow(this);
  _window = new ComponentWindow(_component);
  
  // Create the file manager
  _fileManager = new PeerFileManager(this);
  
  // Get the local IP address
  Array<IPAddress> allAddresses;
  IPAddress::findAllAddresses(allAddresses);
  for (int i = 0; i < allAddresses.size(); i++)
    if (allAddresses.getReference(i).toString().startsWith("192.168."))
      _address = allAddresses.getUnchecked(i);
  
  // Create our MessageHandler
  if (!_address.toString().equalsIgnoreCase("0.0.0.0"))
    _messageHandler = new PeerMessageHandler(_address,_fileManager);
  
  // Create our SocketThread
  if (_messageHandler)
    _socketThread = new SocketThread(4807, _messageHandler);
  else
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

void PeerProcessor::stop() {
  signalThreadShouldExit();
  stopThread(2000);
}

void PeerProcessor::run()
{
  while(!threadShouldExit()) {}
  Logger::writeToLog("Closing PeerProcessor thread");
}

void PeerProcessor::sendPeerGetFile(juce::IPAddress destination,
                                    PeerFile file)
{
  // Create our PimpMessage request
  PimpMessage request (_address);
  request.createPeerGetFile(file);
  std::string out = request.getXmlString().toStdString();
  
  // Create a new socket to connect to our distant host
  ScopedPointer<StreamingSocket> socket = new StreamingSocket();
  socket->connect(destination.toString(), 4807);
  
  // If connection was successful
  if (socket->isConnected())
  {
    // Let's send him the request
    socket->write(out.c_str(), out.length());
    
    // Prepare a stream output file to write the data
    juce::File outputFile ("/Users/Adrien/Music/iTunes/iTunes\ Media/Music/Neirbo/Oldies/One2.mp3");
    juce::FileOutputStream streamFile (outputFile);
    if (streamFile.openedOk())
    {
      int bytesRead;
      char inBuffer[4096];
      do
      {
        bytesRead = socket->read(inBuffer,4096,false);
        streamFile.write(inBuffer, bytesRead);
      } while (bytesRead == 4096);
    }
    std::cout << std::endl << "fin" << std::endl;
  }
}

void PeerProcessor::sendTrackerSearch(juce::StringArray keywords)
{
  PimpMessage request (_address);
  request.createPeerSearch(keywords);
}