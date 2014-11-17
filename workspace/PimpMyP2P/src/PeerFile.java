import java.net.Inet4Address;
import java.util.ArrayList;

///@class: PeerFile
///@brief: Keep track of a file and all the peers that possess it
public class PeerFile {
	
	///@brief: Constructor
	PeerFile(String filename)
	{
		_filename = filename;
	}

	///@brief: Return the current Peer list for this PeerFile
	public ArrayList<Inet4Address> getPeers()
	{
		return _peers;
	}

	///@brief: Add the given IP from the Peer list
	public void addPeer(Inet4Address address)
	{
		_peers.add(address);
	}
	
	///@brief: Remove the given IP from the Peer list
	public void removePeer(Inet4Address address)
	{
		_peers.remove(address);
	}
	
	///@brief: Return true if the given keyword seems similar with this PeerFile
	public boolean isSimilarToKeyword(String keyword)
	{
		return false;
	}

	private String _filename; ///< Name of the file
	private ArrayList<Inet4Address> _peers = new ArrayList<Inet4Address>(); ///< Peer list that possess this file
}
