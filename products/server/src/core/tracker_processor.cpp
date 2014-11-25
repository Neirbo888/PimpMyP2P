#include "products/common/messages/pimp_message.h"
#include "products/common/network/socket_thread.h"
#include "products/common/ui/component_window.h"
#include "products/server/src/ui/tracker_ui.h"
#include "products/server/src/core/tracker_processor.h"
#include "products/server/src/core/tracker_message_handler.h"

TrackerProcessor::TrackerProcessor()
: Thread("PimpTracker"),
_fileManager(this),
_messageHandler(nullptr),
_socketThread(nullptr)
{
  // Create the GUI
  _ui = new TrackerUi(this);
  _window = new ComponentWindow(_ui);
  
  // Get the local IP address
  juce::Array<IPAddress> allAddresses;
  juce::IPAddress::findAllAddresses(allAddresses);
  for (int i = 0; i < allAddresses.size(); i++)
    if (allAddresses.getReference(i).toString().startsWith("192.168."))
      _address = allAddresses.getUnchecked(i);
  
  // If no local network is connected, lets initialize with the loopback ip
  if (_address.toString() == "0.0.0.0")
    _address = juce::IPAddress::local();
  
  // Create our MessageHandler
  _messageHandler = new TrackerMessageHandler(_address, _fileManager);
  
  // Create our SocketThread
  _socketThread = new SocketThread(4807, _messageHandler);
  
  if (!_socketThread->isConnected())
    Logger::writeToLog("Couldn't create listener on port 4807");
  
  startThread();
}

TrackerProcessor::~TrackerProcessor()
{
  stop();
}

void TrackerProcessor::actionListenerCallback(const String& message)
{
  Logger::writeToLog("Unhandled ActionListener callback");
}

void TrackerProcessor::handleAsyncUpdate()
{
  Logger::writeToLog("Unhandled async update");
}

void TrackerProcessor::stop()
{
  signalThreadShouldExit();
  stopThread(2000);
}

void TrackerProcessor::run()
{
  while(!threadShouldExit())
    this->wait(100000);
  Logger::writeToLog("Closing TrackerProcessor thread");
}