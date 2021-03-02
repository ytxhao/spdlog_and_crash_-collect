package com.test.spdlog_and_crash_collect;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.text.TextUtils;
import android.util.Log;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        String logPath = "";
        if (getExternalFilesDir("ams") != null) {
            logPath = getExternalFilesDir("ams").getAbsolutePath()+"/ams_rotating.txt";
        }
        // Example of a call to a native method
        TextView tv = findViewById(R.id.sample_text);
        Log.d("MainActivity","logPath="+logPath);
        tv.setText(stringFromJNI(logPath));
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI(String filePath);
}