package ssq.gamest.port.android;

import ssq.gamest.constants.Constants;
import android.app.Application;
import android.content.Context;
import android.content.SharedPreferences;
import android.preference.PreferenceManager;
import android.util.Log;

public class App extends Application
{
	public static boolean isServiceStarted(Context context)
	{
		SharedPreferences pref = PreferenceManager.getDefaultSharedPreferences(context);
		return pref.getBoolean(Constants.IS_SERVICE_STARTED, false);
	}

	public static void setServiceStarted(Context context, boolean isStarted){
		SharedPreferences pref = PreferenceManager.getDefaultSharedPreferences(context);
		SharedPreferences.Editor editor = pref.edit();
		editor.putBoolean(Constants.IS_SERVICE_STARTED, isStarted);
		editor.commit();
	}
}
