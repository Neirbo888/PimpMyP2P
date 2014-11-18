#ifndef PIMP_PROCESSOR_H_INCLUDED
#define PIMP_PROCESSOR_H_INCLUDED

#include "JuceHeader.h"

/// Forward declarations
class ComponentWindow;

/// @class PimpServerProcessor
/// @brief Heart of the pimp server
class PimpServerProcessor
: public ActionListener
{
public:
  /// @brief Constructor
  PimpServerProcessor();
  
  /// @brief Destructor
  ~PimpServerProcessor();
  
  /// @brief ActionListener callback
  void actionListenerCallback (const String& message);

  /// @brief register a new client
  void registerNewClient(IPAddress address);

  /// @brief unregister a client
  void unregisterClient(IPAddress address);

  /// @brief look for a file in the file cache using a keword
  std::vector<juce::PeerFile> lookForFileFromKeyword(String keyword, bool refreshList);

  /// @brief refresh the file cache
  void refreshFileCache();
  
private:
  ScopedPointer<ComponentWindow> _window; ///< Window displaying the GUI
  juce::Component* _component; ///< The proper gui

  IPAddress _address;
  std::vector<IPAddress> _clientList;
  std::vector<juce::PeerFile> _fileCache;
};



#endif  // PIMP_PROCESSOR_H_INCLUDED
