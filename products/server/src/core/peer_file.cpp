/*
  ==============================================================================

    peer_file.cpp
    Created: 18 Nov 2014 1:27:48pm
    Author:  Marc

  ==============================================================================
*/

#include "peer_file.h"

PeerFile::PeerFile()
{

}

PeerFile::~PeerFile()
{

}

bool PeerFile::isSimilarTo(String word)
{
	StringArray keywords;
	keywords.addTokens(word, " _-", "");

	StringArray fileNameParts;
	fileNameParts.addTokens(_fileName, " _-", "");
	// Remove words shorter than 3 characters in file name
	for (int i = 0; i <= fileNameParts.size; i++)
	{
		if (fileNameParts[i].length < 3)
		{
			fileNameParts.remove(i);
		}
	}

	for (int i = 0; i <=fileNameParts.size; i++)
	{
		for (int j = 0; j <= keywords.size; j++)
		{
			if (fileNameParts[i].equalsIgnoreCase(keywords[j]))
			{
				return(true);
			}
		}
	}
	return(false);
}

String PeerFile::getFileName()
{
	return _fileName;
}
