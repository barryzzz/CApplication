package com.xf.bspdiff;

import android.content.Context;
import android.os.Environment;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.TextView;
import android.widget.Toast;

import java.io.File;

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

       Log.e(TAG,pareseString("中文"));
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

    public native void fkDiff(String oldFile, String newFile, String patchFile);


    public native String pareseString(String str);



    public native int checkSignature(Context context);


    public void doClick(View view) {


        new Thread(new Runnable() {
            @Override
            public void run() {
                final File oldfile = new File(Environment.getExternalStorageDirectory(), "old.apk");
                final File newfile = new File(Environment.getExternalStorageDirectory(), "new.apk");
                final File difffile = new File(Environment.getExternalStorageDirectory(), "diff.patch");
                Log.e(TAG, "old:" + oldfile.getAbsolutePath());
                fkDiff(oldfile.getAbsolutePath(), newfile.getAbsolutePath(), difffile.getAbsolutePath());
                runOnUiThread(new Runnable() {
                    @Override
                    public void run() {
                        Toast.makeText(MainActivity.this,"apk合成成功",Toast.LENGTH_LONG).show();
                    }
                });

            }
        }).start();

    }
}
