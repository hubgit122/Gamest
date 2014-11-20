package ssq.gamest.port.android;

import android.os.Bundle;
import android.preference.PreferenceActivity;

import fr.fagno.android.caws.R;

public class ServerPreferenceActivity extends PreferenceActivity {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		addPreferencesFromResource(R.xml.preference);
	}
}
