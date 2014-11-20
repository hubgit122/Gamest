package ssq.utils;

import java.io.ByteArrayOutputStream;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.security.Key;
import java.security.KeyFactory;
import java.security.KeyPair;
import java.security.KeyPairGenerator;
import java.security.NoSuchAlgorithmException;
import java.security.PrivateKey;
import java.security.PublicKey;
import java.security.Signature;
import java.security.spec.InvalidKeySpecException;
import java.security.spec.PKCS8EncodedKeySpec;
import java.security.spec.X509EncodedKeySpec;
import javax.crypto.Cipher;

/** */
/**
* <p>
* RSA公钥/私钥/签名工具包
* </p>
* <p>
* 罗纳德·李维斯特（Ron [R]ivest）、阿迪·萨莫尔（Adi [S]hamir）和伦纳德·阿德曼（Leonard [A]dleman）
* </p>
* <p>
* 字符串格式的密钥在未在特殊说明情况下都为BASE64编码格式<br/>
* 由于非对称加密速度极其缓慢，一般文件不使用它来加密而是使用对称加密，<br/>
* 非对称加密算法可以用来对对称加密的密钥加密，这样保证密钥的安全也就保证了数据的安全
* </p>
* 
* @author IceWee
* @date 2012-4-26
* @version 1.0
*/
public class RSAUtils
{
	
	/** */
	/**
	* 加密算法RSA
	*/
	public static final String	KEY_ALGORITHM		= "RSA";
	
	/** */
	/**
	* 签名算法
	*/
	public static final String	SIGNATURE_ALGORITHM	= "MD5withRSA";
	
	/** */
	/**
	* RSA最大加密明文大小
	*/
	private static final int	MAX_ENCRYPT_BLOCK	= 117;
	
	/** */
	/**
	* RSA最大解密密文大小
	*/
	private static final int	MAX_DECRYPT_BLOCK	= 128;
	
	/** */
	/**
	* <p>
	* 生成密钥对(公钥和私钥)
	* </p>
	* 
	* @return
	* @throws Exception
	*/
	public static KeyPair genKeyPair() throws Exception
	{
		KeyPairGenerator keyPairGen = KeyPairGenerator.getInstance(KEY_ALGORITHM);
		keyPairGen.initialize(1024);
		KeyPair keyPair = keyPairGen.generateKeyPair();
//		RSAPublicKey publicKey = (RSAPublicKey) keyPair.getPublic();
//		RSAPrivateKey privateKey = (RSAPrivateKey) keyPair.getPrivate();
		return keyPair;
	}

	public static KeyPair getKeyPair() throws Exception
	{
		FileInputStream fis = new FileInputStream("C:/RSAKey.txt");
		ObjectInputStream oos = new ObjectInputStream(fis);
		KeyPair kp = (KeyPair) oos.readObject();
		oos.close();
		fis.close();
		return kp;
	}
	
	public static void saveKeyPair(KeyPair kp) throws Exception
	{
		FileOutputStream fos = new FileOutputStream(DirUtil.getProjectRoot() + "/keys");
		ObjectOutputStream oos = new ObjectOutputStream(fos);
		//生成密钥
		oos.writeObject(kp);
		oos.close();
		fos.close();
	}
	
	/** */
	/**
	* <p>
	* 用私钥对信息生成数字签名
	* </p>
	* 
	* @param data 已加密数据
	* @param privateKey 私钥(BASE64编码)
	* 
	* @return
	* @throws Exception
	*/
	public static String sign(byte[] data, String privateKey) throws Exception
	{
		byte[] keyBytes = Base64Utils.decode(privateKey);
		PKCS8EncodedKeySpec pkcs8KeySpec = new PKCS8EncodedKeySpec(keyBytes);
		KeyFactory keyFactory = KeyFactory.getInstance(KEY_ALGORITHM);
		PrivateKey privateK = keyFactory.generatePrivate(pkcs8KeySpec);
		Signature signature = Signature.getInstance(SIGNATURE_ALGORITHM);
		signature.initSign(privateK);
		signature.update(data);
		return Base64Utils.encode(signature.sign());
	}
	
	/** */
	/**
	* <p>
	* 校验数字签名
	* </p>
	* 
	* @param data 已加密数据
	* @param publicKey 公钥(BASE64编码)
	* @param sign 数字签名
	* 
	* @return
	* @throws Exception
	* 
	*/
	public static boolean verify(byte[] data, String publicKey, String sign) throws Exception
	{
		byte[] keyBytes = Base64Utils.decode(publicKey);
		X509EncodedKeySpec keySpec = new X509EncodedKeySpec(keyBytes);
		KeyFactory keyFactory = KeyFactory.getInstance(KEY_ALGORITHM);
		PublicKey publicK = keyFactory.generatePublic(keySpec);
		Signature signature = Signature.getInstance(SIGNATURE_ALGORITHM);
		signature.initVerify(publicK);
		signature.update(data);
		return signature.verify(Base64Utils.decode(sign));
	}
	
	/** */
	/**
	* <P>
	* 私钥解密
	* </p>
	* 
	* @param encryptedData 已加密数据
	* @param privateKey 私钥(BASE64编码)
	* @return
	* @throws Exception
	*/
	public static byte[] decryptByPrivateKey(byte[] encryptedData, String privateKey) throws Exception
	{
		byte[] keyBytes = Base64Utils.decode(privateKey);
		PKCS8EncodedKeySpec pkcs8KeySpec = new PKCS8EncodedKeySpec(keyBytes);
		KeyFactory keyFactory = KeyFactory.getInstance(KEY_ALGORITHM);
		Key privateK = keyFactory.generatePrivate(pkcs8KeySpec);
		Cipher cipher = Cipher.getInstance(keyFactory.getAlgorithm());
		cipher.init(Cipher.DECRYPT_MODE, privateK);
		int inputLen = encryptedData.length;
		ByteArrayOutputStream out = new ByteArrayOutputStream();
		int offSet = 0;
		byte[] cache;
		int i = 0;
		// 对数据分段解密
		while (inputLen - offSet > 0)
		{
			if (inputLen - offSet > MAX_DECRYPT_BLOCK)
			{
				cache = cipher.doFinal(encryptedData, offSet, MAX_DECRYPT_BLOCK);
			}
			else
			{
				cache = cipher.doFinal(encryptedData, offSet, inputLen - offSet);
			}
			out.write(cache, 0, cache.length);
			i++;
			offSet = i * MAX_DECRYPT_BLOCK;
		}
		byte[] decryptedData = out.toByteArray();
		out.close();
		return decryptedData;
	}
	
	/** */
	/**
	* <p>
	* 公钥解密
	* </p>
	* 
	* @param encryptedData 已加密数据
	* @param publicKey 公钥(BASE64编码)
	* @return
	* @throws Exception
	*/
	public static byte[] decryptByPublicKey(byte[] encryptedData, String publicKey) throws Exception
	{
		byte[] keyBytes = Base64Utils.decode(publicKey);
		X509EncodedKeySpec x509KeySpec = new X509EncodedKeySpec(keyBytes);
		KeyFactory keyFactory = KeyFactory.getInstance(KEY_ALGORITHM);
		Key publicK = keyFactory.generatePublic(x509KeySpec);
		Cipher cipher = Cipher.getInstance(keyFactory.getAlgorithm());
		cipher.init(Cipher.DECRYPT_MODE, publicK);
		int inputLen = encryptedData.length;
		ByteArrayOutputStream out = new ByteArrayOutputStream();
		int offSet = 0;
		byte[] cache;
		int i = 0;
		// 对数据分段解密
		while (inputLen - offSet > 0)
		{
			if (inputLen - offSet > MAX_DECRYPT_BLOCK)
			{
				cache = cipher.doFinal(encryptedData, offSet, MAX_DECRYPT_BLOCK);
			}
			else
			{
				cache = cipher.doFinal(encryptedData, offSet, inputLen - offSet);
			}
			out.write(cache, 0, cache.length);
			i++;
			offSet = i * MAX_DECRYPT_BLOCK;
		}
		byte[] decryptedData = out.toByteArray();
		out.close();
		return decryptedData;
	}
	
	/** */
	/**
	* <p>
	* 公钥加密
	* </p>
	* 
	* @param data 源数据
	* @param publicKey 公钥(BASE64编码)
	* @return
	* @throws Exception
	*/
	public static byte[] encryptByPublicKey(byte[] data, String publicKey) throws Exception
	{
		byte[] keyBytes = Base64Utils.decode(publicKey);
		X509EncodedKeySpec x509KeySpec = new X509EncodedKeySpec(keyBytes);
		KeyFactory keyFactory = KeyFactory.getInstance(KEY_ALGORITHM);
		Key publicK = keyFactory.generatePublic(x509KeySpec);
		// 对数据加密
		Cipher cipher = Cipher.getInstance(keyFactory.getAlgorithm());
		cipher.init(Cipher.ENCRYPT_MODE, publicK);
		int inputLen = data.length;
		ByteArrayOutputStream out = new ByteArrayOutputStream();
		int offSet = 0;
		byte[] cache;
		int i = 0;
		// 对数据分段加密
		while (inputLen - offSet > 0)
		{
			if (inputLen - offSet > MAX_ENCRYPT_BLOCK)
			{
				cache = cipher.doFinal(data, offSet, MAX_ENCRYPT_BLOCK);
			}
			else
			{
				cache = cipher.doFinal(data, offSet, inputLen - offSet);
			}
			out.write(cache, 0, cache.length);
			i++;
			offSet = i * MAX_ENCRYPT_BLOCK;
		}
		byte[] encryptedData = out.toByteArray();
		out.close();
		return encryptedData;
	}
	
	/** */
	/**
	* <p>
	* 私钥加密
	* </p>
	* 
	* @param data 源数据
	* @param privateKey 私钥(BASE64编码)
	* @return
	* @throws Exception
	*/
	public static byte[] encryptByPrivateKey(byte[] data, String privateKey) throws Exception
	{
		byte[] keyBytes = Base64Utils.decode(privateKey);
		PKCS8EncodedKeySpec pkcs8KeySpec = new PKCS8EncodedKeySpec(keyBytes);
		KeyFactory keyFactory = KeyFactory.getInstance(KEY_ALGORITHM);
		Key privateK = keyFactory.generatePrivate(pkcs8KeySpec);
		Cipher cipher = Cipher.getInstance(keyFactory.getAlgorithm());
		cipher.init(Cipher.ENCRYPT_MODE, privateK);
		int inputLen = data.length;
		ByteArrayOutputStream out = new ByteArrayOutputStream();
		int offSet = 0;
		byte[] cache;
		int i = 0;
		// 对数据分段加密
		while (inputLen - offSet > 0)
		{
			if (inputLen - offSet > MAX_ENCRYPT_BLOCK)
			{
				cache = cipher.doFinal(data, offSet, MAX_ENCRYPT_BLOCK);
			}
			else
			{
				cache = cipher.doFinal(data, offSet, inputLen - offSet);
			}
			out.write(cache, 0, cache.length);
			i++;
			offSet = i * MAX_ENCRYPT_BLOCK;
		}
		byte[] encryptedData = out.toByteArray();
		out.close();
		return encryptedData;
	}
	
	/**
	  * 实例化公钥
	  *
	  * @return
	  */
	public static PublicKey getPubKey(String pubKey)
	{
		PublicKey publicKey = null;
		try
		{
			java.security.spec.X509EncodedKeySpec bobPubKeySpec = new java.security.spec.X509EncodedKeySpec(Base64Utils.decode(pubKey));
			// RSA对称加密算法
			java.security.KeyFactory keyFactory;
			keyFactory = java.security.KeyFactory.getInstance("RSA");
			// 取公钥匙对象
			publicKey = keyFactory.generatePublic(bobPubKeySpec);
		}
		catch (NoSuchAlgorithmException e)
		{
			e.printStackTrace();
		}
		catch (InvalidKeySpecException e)
		{
			e.printStackTrace();
		}
		return publicKey;
	}
	
	/**
	 * 实例化私钥
	 *
	 * @return
	 */
	public static PrivateKey getPrivateKey(String priKey)
	{
		PrivateKey privateKey = null;
		PKCS8EncodedKeySpec priPKCS8;
		try
		{
			priPKCS8 = new PKCS8EncodedKeySpec(Base64Utils.decode(priKey));
			KeyFactory keyf = KeyFactory.getInstance("RSA");
			privateKey = keyf.generatePrivate(priPKCS8);
		}
		catch (NoSuchAlgorithmException e)
		{
			e.printStackTrace();
		}
		catch (InvalidKeySpecException e)
		{
			e.printStackTrace();
		}
		return privateKey;
	}
	
	/**
	 * 得到密钥字符串（经过base64编码）
	 * @return
	 */
	public static String getKeyString(Key key) throws Exception
	{
		byte[] keyBytes = key.getEncoded();
		String s = Base64Utils.encode(keyBytes);
		return s;
	}
	
}
