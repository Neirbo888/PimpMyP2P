#include "products/common/messages/pimp_message.h"
#include "products/client/src/core/peer_file_manager.h"
#include "products/client/src/core/peer_processor.h"

PeerFileManager::PeerFileManager(PeerProcessor *owner)
: juce::Thread("FileManager thread"),
  _owner(owner),
  _sharedFolder(juce::File::nonexistent) {}

PeerFileManager::~PeerFileManager()
{
  signalThreadShouldExit();
  stopThread(2000);
}

void PeerFileManager::setSharedFolder(const juce::File& folder)
{
  if (folder.exists())
  {
    _sharedFolder = juce::File(folder);
    startThread();
  }
}

void PeerFileManager::run()
{
  juce::Array<juce::File> foundFiles;
  _availableFiles.clear();
  
  _sharedFolder.findChildFiles(foundFiles,juce::File::findFiles, false, "*");
  for (const juce::File& file : foundFiles)
  {
    _owner->setProgress((double)(foundFiles.indexOf(file))/(double)(foundFiles.size()));
    _owner->publishLogMessage("Scanning " + file.getFileNameWithoutExtension());
    _availableFiles.add(PeerFile(file));
  }
  
  _owner->setProgress(0);
  _owner->triggerAsyncUpdate();
}

void PeerFileManager::sendFileToSocket(const int index,
                                       juce::StreamingSocket *socket) const
{
  if (index >= getAvailableFiles().size() ||
      index < 0)
  {
    Logger::writeToLog("Trying to send invalid index");
    return;
  }
  
  const PeerFile& file = getAvailableFiles().getReference(index);
  juce::FileInputStream inputStream (file.getFile());
  
  if (!inputStream.openedOk())
  {
    Logger::writeToLog("Can't open input stream");
    return;
  }
  
  if (!socket)
  {
    Logger::writeToLog("Socket is invalid");
    return;
  }
  
  if (!socket->isConnected())
  {
    Logger::writeToLog("Socket has been closed");
    return;
  }
  
  union Ustuff { int i; unsigned char c[4]; };
  Ustuff outUnion;
  outUnion.i = file.getSize();
  socket->write(outUnion.c, 4);
  int totalSent = 0;
  do
  {
    int sizeToSend = 4096;
    if (file.getSize() - totalSent < 4096)
      sizeToSend = file.getSize() - totalSent;
    juce::MemoryBlock buffer (sizeToSend, true);
    int readBytes = inputStream.read(buffer.getData(), sizeToSend);
    socket->write(buffer.getData(), readBytes);
    totalSent += sizeToSend;
  } while (totalSent != file.getSize());
}

bool PeerFileManager::receiveFileFromSocket(const PeerFile& queuedFile,
                                            juce::StreamingSocket *socket)
{
  juce::File outputFile (_sharedFolder.getFullPathName() +
                         juce::File::separator +
                         queuedFile.getFilename());
  
  juce::FileOutputStream streamFile (outputFile);
  if (!streamFile.openedOk())
  {
    Logger::writeToLog("Can't open output stream");
    return false;
  }
  
  if (!socket)
  {
    Logger::writeToLog("Socket is invalid");
    return false;
  }
  
  if (!socket->isConnected())
  {
    Logger::writeToLog("Socket has been closed");
    return false;
  }
  
  union Ustuff { int i; unsigned char c[4]; };
  Ustuff outUnion;
  int bytesRead = socket->read(outUnion.c, 4, true);
  if (bytesRead != 4 || outUnion.i == 0)
  {
    Logger::writeToLog("Invalid size read");
    return false;
  }
  
  int totalReceived = 0;
  do
  {
    _owner->setProgress((double)(totalReceived)/(double)(outUnion.i));
    int sizeToReceive = 4096;
    if (queuedFile.getSize() - totalReceived < 4096)
      sizeToReceive = queuedFile.getSize() - totalReceived;
    
    juce::MemoryBlock buffer (sizeToReceive, true);
    int readBytes = socket->read(buffer.getData(), sizeToReceive, true);
    streamFile.write(buffer.getData(), readBytes);
    totalReceived += sizeToReceive;
  } while (totalReceived != queuedFile.getSize());
  
  _owner->setProgress(0);
  
  return true;
}