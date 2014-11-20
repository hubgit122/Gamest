package ssq.gamest.constants;

public class Constants {
	public static final Boolean LOG_ON = false;
	public static final Boolean DEBUG_ON = false;
	
	public static final String CAWS_MESSAGE = "cawsmessage";
	public static final String PREF_SERVER_PORT = "prefServerPort";
	public static final int DEFAULT_SERVER_PORT = 8080;

	public static final String IS_SERVICE_STARTED = "isServiceStarted";
	
	public static enum platform { ANDROID,  WINDOWS, LINUX};
	public static final platform PLATFORM = platform.ANDROID;
}
