/*
  ==============================================================================

    peer_file.h
    Created: 18 Nov 2014 1:27:48pm
    Author:  Marc

  ==============================================================================
*/

#ifndef PEER_FILE_H_INCLUDED
#define PEER_FILE_H_INCLUDED

#include "JuceHeader.h"

class PeerFile
{
private:
	String _fileName;
	std::vector<IPAddress> _peers;


public:
	/// @brief tests if the file is similar using a keyword
	bool isSimilarTo(String word);
	String getFileName();
};



#endif  // PEER_FILE_H_INCLUDED
