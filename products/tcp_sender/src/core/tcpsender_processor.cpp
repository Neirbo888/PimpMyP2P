/*
  ==============================================================================

    app_processor.cpp
    Created: 17 Nov 2014 6:48:41pm
    Author:  Adrien Tisseraud

  ==============================================================================
*/

#include "products/common/ui/component_window.h"
#include "products/tcp_sender/src/ui/main_window.h"
#include "products/tcp_sender/src/core/tcpsender_processor.h"

TcpSenderProcessor::TcpSenderProcessor()
{
  _component = new MainWindow(this);
  _window = new ComponentWindow(_component);
}

TcpSenderProcessor::~TcpSenderProcessor()
{
  
}

void TcpSenderProcessor::actionListenerCallback(const String& message)
{
  
}

void TcpSenderProcessor::send(juce::String ip, juce::String message)
{
  juce::String address = ip.substring(0, ip.indexOf(":"));
  int port = ip.substring(ip.indexOf(":") + 1).getIntValue();
  if (_socket.connect(address, port))
  {
    //_socket.write(message.toRawUTF8(), message.length());
    juce::File inputFile ("/Users/Adrien/Music/iTunes/iTunes\ Media/Music/Neirbo/Oldies/One.mp3");
    FileInputStream streamFile (inputFile);
    char inBuffer[4097];
    if (streamFile.openedOk())
    {
      int bytesRead;
      while ((bytesRead = streamFile.read(inBuffer,4096)) == 4096) {
        _socket.write(inBuffer, bytesRead);
      }
    }
  }
  _socket.close();
}