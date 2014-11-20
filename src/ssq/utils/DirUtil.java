package ssq.utils;

import java.io.File;

public class DirUtil
{
	public static String getProjectRoot()
	{
		return System.getProperty("user.dir");
	}
	
	public static String getKeyRoot()
	{
		return getProjectRoot() + File.separator + "keys";
	}
	
	public static String getWebRoot()
	{
		return getProjectRoot() + File.separator + "web";
	}
}