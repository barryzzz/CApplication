package com.example.lishoulin.capplication;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

import java.util.Arrays;
import java.util.Collections;

public class MainActivity extends AppCompatActivity {
    private static final String TAG = "MainActivity";

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tv = (TextView) findViewById(R.id.sample_text);
        tv.setText(stringFromJNI());
        int[] array = {3, 1, 2, 6, 8, 1};
        int[] temp = JNINativeBridge.sort1(array);
        Log.e(TAG, "onCreate: " + Arrays.toString(temp));

        User user = new User();
        user.id = 1001;
        user.city = "Gz";
        user.name = "lsl";

        JNINativeBridge.classSort(user);
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();


}
