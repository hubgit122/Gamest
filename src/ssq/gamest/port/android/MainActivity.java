package ssq.gamest.port.android;

import ssq.gamest.constants.Constants;
import ssq.utils.Utility;
import android.app.Activity;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.preference.PreferenceManager;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;
import fr.fagno.android.caws.R;

public class MainActivity extends Activity {
	private Toast toast;
	
	private static final int PREFERENCE_REQUEST_CODE = 1001;

	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.main); 
		setButtonHandlers();
		boolean isRunning = App.isServiceStarted(this);
		setButtonText(isRunning);
		setInfoText(isRunning);
		toast = new Toast(this);
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		MenuInflater inflater = getMenuInflater();
		inflater.inflate(R.menu.contextmenu, menu);
		return true;
	}

	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
		boolean result = true;

		switch (item.getItemId()) {
		case R.id.menuPreference:{
			startActivityForResult(new Intent(this,ServerPreferenceActivity.class), PREFERENCE_REQUEST_CODE);
			break;
		}
		default:{
			result = super.onOptionsItemSelected(item);
		}
		}
		return result;
	}

	@Override
	protected void onActivityResult(int requestCode, int resultCode, Intent data) {
		super.onActivityResult(requestCode, resultCode, data);

		switch(requestCode){
		case PREFERENCE_REQUEST_CODE:{
			break;
		}
		}
	}

	private void setButtonHandlers() {
		((Button)findViewById(R.id.btnStartStop)).setOnClickListener(btnClick);
	}

	private void setButtonText(boolean isServiceRunning){
		((Button)findViewById(R.id.btnStartStop)).setText(
				getString(isServiceRunning ? R.string.stop_caption : R.string.start_caption));
	}

	private void setInfoText(boolean isServiceRunning){
		TextView txtLog = (TextView)findViewById(R.id.txtLog);
		String text = getString(R.string.log_notrunning);

		if(isServiceRunning){
			SharedPreferences pref = PreferenceManager.getDefaultSharedPreferences(this);
			text = getString(R.string.log_running) + "\n" + getString(R.string.log_msg1) + " 'http://" + Utility.getLocalIpAddress() + ":" + pref.getString(Constants.PREF_SERVER_PORT, "" + Constants.DEFAULT_SERVER_PORT) + "' " + getString(R.string.log_msg2);
		}
		txtLog.setText(text);
	}

	private View.OnClickListener btnClick = new View.OnClickListener() {

		@Override
		public void onClick(View v) {
			switch(v.getId()){
			case R.id.btnStartStop:{
				Intent intent = new Intent(MainActivity.this,HTTPService.class);

				if(App.isServiceStarted(MainActivity.this)){
					stopService(intent);
					App.setServiceStarted(MainActivity.this, false);
					setButtonText(false);
					setInfoText(false);
				}
				else{
					SharedPreferences pref = PreferenceManager.getDefaultSharedPreferences(getApplicationContext());
					int serverPort = Integer.parseInt(pref.getString(Constants.PREF_SERVER_PORT, "" + Constants.DEFAULT_SERVER_PORT));
					if(Utility.available(serverPort)){
						startService(intent);
						App.setServiceStarted(MainActivity.this, true);
						setButtonText(true);
						setInfoText(true);
					}else{
						toast = Toast.makeText(getApplicationContext(), "Port " + serverPort + " already in use!", Toast.LENGTH_LONG);
						toast.show();
					}
				}
				break;
			}
			}
		}
	};
	
	@Override
	  public void onDestroy() {
	    super.onDestroy();
	  }
}