import java.io.BufferedOutputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectOutputStream;
import java.math.BigInteger;
import java.security.KeyFactory;
import java.security.KeyPair;
import java.security.KeyPairGenerator;
import java.security.NoSuchAlgorithmException;
import java.security.PrivateKey;
import java.security.PublicKey;
import java.security.spec.InvalidKeySpecException;
import java.security.spec.RSAPrivateKeySpec;
import java.security.spec.RSAPublicKeySpec;


public class Server {

	private PublicKey publicKey;
	private PrivateKey privateKey;
	
	final static String PRIVATE_KEY_FILE = "privateKey";
	final static String PUBLIC_KEY_FILE = "publicKey";

	public Server()
	{
		
	}

	public void saveKeys(String fileName, BigInteger mod, BigInteger exp) throws IOException
	{
		FileOutputStream fos = null;  
		ObjectOutputStream oos = null;  

		try {  
			System.out.println("Generating "+fileName + "...");  
			fos = new FileOutputStream(fileName);  
			oos = new ObjectOutputStream(new BufferedOutputStream(fos));  

			oos.writeObject(mod);  
			oos.writeObject(exp);     

			System.out.println(fileName + " generated successfully");  
		} catch (Exception e) {  
			e.printStackTrace();  
		}  
		finally{  
			if(oos != null){  
				oos.close();  

				if(fos != null){  
					fos.close();  
				}  
			}  
		}    
	}

	public static void main(String[] args) throws IOException {  

		Server server = new Server();

		try {  
			System.out.println("-------GENRATE PUBLIC and PRIVATE KEY-------------");  
			KeyPairGenerator keyPairGenerator = KeyPairGenerator.getInstance("RSA");  
			keyPairGenerator.initialize(1024);  
			KeyPair keyPair = keyPairGenerator.generateKeyPair();  
			server.publicKey = keyPair.getPublic();  
			server.privateKey = keyPair.getPrivate();  
			System.out.println("Public Key - " + server.publicKey);  
			System.out.println("Private Key - " + server.privateKey);  

			//Pullingout parameters which makes up Key  
			System.out.println("\n------- PULLING OUT PARAMETERS WHICH MAKES KEYPAIR----------\n");  
			KeyFactory keyFactory = KeyFactory.getInstance("RSA");  
			RSAPublicKeySpec rsaPubKeySpec = keyFactory.getKeySpec(server.publicKey, RSAPublicKeySpec.class);  
			RSAPrivateKeySpec rsaPrivKeySpec = keyFactory.getKeySpec(server.privateKey, RSAPrivateKeySpec.class);  
			System.out.println("PubKey Modulus : " + rsaPubKeySpec.getModulus());  
			System.out.println("PubKey Exponent : " + rsaPubKeySpec.getPublicExponent());  
			System.out.println("PrivKey Modulus : " + rsaPrivKeySpec.getModulus());  
			System.out.println("PrivKey Exponent : " + rsaPrivKeySpec.getPrivateExponent());  

			//Share public key with other so they can encrypt data and decrypt thoses using private key(Don't share with Other)  
			System.out.println("\n--------SAVING PUBLIC KEY AND PRIVATE KEY TO FILES-------\n");
			server.saveKeys(PUBLIC_KEY_FILE, rsaPubKeySpec.getModulus(), rsaPubKeySpec.getPublicExponent());  
			server.saveKeys(PRIVATE_KEY_FILE, rsaPrivKeySpec.getModulus(), rsaPrivKeySpec.getPrivateExponent()); 

		} catch (NoSuchAlgorithmException e) {  
			e.printStackTrace();  
		}catch (InvalidKeySpecException e) {  
			e.printStackTrace();  
		}  

	}  

}
