package ssq.utils;
import it.sauronsoftware.base64.Base64;

/** */
/**
 * <p>
 * BASE64������빤�߰�
 * </p>
 * <p>
 * ����javabase64-1.3.1.jar
 * </p>
 * 
 * @author IceWee
 * @date 2012-5-19
 * @version 1.0
 */
public class Base64Utils
{
	/** */
	/**
	 * <p>
	 * BASE64�ַ�������Ϊ����������
	 * </p>
	 * 
	 * @param base64
	 * @return
	 * @throws Exception
	 */
	public static byte[] decode(String base64)
	{
		try
		{
			return Base64.decode(base64.getBytes());
		}
		catch (Exception e)
		{
			e.printStackTrace();
			return "null".getBytes();
		}
	}
	
	/** */
	/**
	 * <p>
	 * ���������ݱ���ΪBASE64�ַ���
	 * </p>
	 * 
	 * @param bytes
	 * @return
	 * @throws Exception
	 */
	public static String encode(byte[] bytes) throws Exception
	{
		return new String(Base64.encode(bytes));
	}
}
