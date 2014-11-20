package ssq.utils;

import android.util.Log;
import ssq.gamest.constants.Constants;
import ssq.gamest.constants.Constants.platform;

public class LogUtilities
{
	public static final String	LOG		= "gamest";
	public static final String	WARNING	= "gamest warning";
	
	public static void logString(String message)
	{
		if (Constants.LOG_ON)
			if (Constants.PLATFORM == platform.ANDROID)
			{
				Log.i(LOG, message);
			}
			else
			{
				System.err.println(LOG + " : " + message);
			}
	}
	
	public static void logString(String message, String tag)
	{
		if (Constants.LOG_ON)
			if (Constants.PLATFORM == platform.ANDROID)
			{
				Log.i(tag, message);
			}
			else
			{
				System.err.println(tag + " : " + message);
			}
	}
	
	public static void logWarningString(String message)
	{
		if (Constants.LOG_ON)
			if (Constants.PLATFORM == platform.ANDROID)
			{
				Log.i(WARNING, message);
			}
			else
			{
				System.err.println(WARNING + " : " + message);
			}
	}
}
