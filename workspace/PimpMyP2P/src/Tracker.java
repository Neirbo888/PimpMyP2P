import java.util.ArrayList;
import java.util.HashMap;


public class Tracker extends Thread {
	private ArrayList<String> _connectedPeers = new ArrayList<String>();
	private ArrayList<PeerFile> _peerFiles = new ArrayList<PeerFile>();
	
	Tracker()
	{
		
	}
	
	public void refreshFileCache()
	{
		
	}
	
	///@brief: Return a list of peers that has a file corresponding to keyword
	public ArrayList<PeerFile> getPeerFilesForKeyword(String keyword, boolean refreshFirst)
	{
		if (refreshFirst)
			refreshFileCache();
		// We should wait until the refresh is done here
		
		ArrayList<PeerFile> similarPeerFiles = new ArrayList<PeerFile>();
		for (PeerFile file : _peerFiles)
			if (file.isSimilarToKeyword(keyword))
				similarPeerFiles.add(file);
		return similarPeerFiles;
	}
	
	
}
