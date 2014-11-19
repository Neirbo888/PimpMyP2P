/*
  ==============================================================================

    app_processor.cpp
    Created: 17 Nov 2014 6:48:41pm
    Author:  Adrien Tisseraud

  ==============================================================================
*/

#include "products/common/ui/component_window.h"
#include "products/client/src/ui/main_window.h"
#include "products/client/src/core/client_processor.h"

PimpClientProcessor::PimpClientProcessor()
: Thread("PimpClient"),
  _component(new MainWindow(this)),
  _window(new ComponentWindow(_component))
{
  Array<IPAddress> allAddresses;
  IPAddress::findAllAddresses(allAddresses);
  for (int i = 0; i < allAddresses.size(); i++)
    if (allAddresses.getReference(i).toString().startsWith("192.168."))
      _address = allAddresses.getUnchecked(i);
  
  
  _connected = _socket.createListener(4807) &&
               !_address.toString().equalsIgnoreCase("0.0.0.0");
  if (!_connected)
    Logger::writeToLog("Couldn't create listener on port 4807");
  startThread();
}

PimpClientProcessor::~PimpClientProcessor()
{
  this->stop();
}

void PimpClientProcessor::actionListenerCallback(const String& message)
{
  
}

void PimpClientProcessor::setSharedFolder(juce::File folder)
{
  if (folder.exists())
  {
    _sharedFolder = folder;
    // Maybe set a new state machine transition here
  }
}

void PimpClientProcessor::scanSharedFolder()
{
	juce::Array<juce::File> found_files;
	if (_sharedFolder.findChildFiles(found_files, juce::File::findFiles, false, "*"))
	{
		for (juce::File* file = found_files.begin(); file != found_files.end();file++)
		{
			_files.push_back(juce::File(file->getFullPathName()));
		}
	}
}

void PimpClientProcessor::stop() {
  _socket.close();
  signalThreadShouldExit();
  stopThread(2000);
}

void PimpClientProcessor::run()
{
  if (_connected)
  {
    Logger::writeToLog("Waiting for tcp connection on port 4807");
    while (!threadShouldExit())
    {
      // We wait here until a new connection has been made
      StreamingSocket* socket = _socket.waitForNextConnection();
      if (socket)
      {
        // Create a char tab to store what's coming
        char inBuffer[4096];
        
        int bytesRead = socket->read(inBuffer,4096,false);
        
        // If an error has been detected
        if (bytesRead == -1)
        {
          Logger::writeToLog("Error receiving command");
        }
        else
        {
          PimpMessage message (inBuffer);
          if (message.isCommand(PimpMessage::kPeerGetFile))
            handleSendRequest(message, socket);
        }
        deleteAndZero(socket);
      }
    }
  }
  Logger::writeToLog("Closing receiving thread");
}

void PimpClientProcessor::handleSendRequest(const PimpMessage& request,
                                            juce::StreamingSocket *socket)
{
  if (request.hasFilename())
  {
    if (request.hasByteRange())
    {
      
    }
    else
    {
      juce::File inputFile ("/Users/Adrien/Music/iTunes/iTunes\ Media/Music/Neirbo/Oldies/One.mp3");
      FileInputStream streamFile (inputFile);
      char inBuffer[4096];
      if (streamFile.openedOk())
      {
        int bytesRead;
        do
        {
          bytesRead = streamFile.read(inBuffer,4096);
          socket->write(inBuffer, bytesRead);
        } while (bytesRead == 4096);
      }
    }
  }
}

void PimpClientProcessor::sendPeerGetFile(juce::IPAddress destination,
                                          juce::String filename)
{
  // Create our PimpMessage request
  PimpMessage sendRequest (_address);
  sendRequest.createSendRequest(filename);
  std::string out = sendRequest.getXmlString().toStdString();
  
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