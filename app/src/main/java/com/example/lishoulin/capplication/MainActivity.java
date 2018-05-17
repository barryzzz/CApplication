package com.example.lishoulin.capplication;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.widget.TextView;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

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
        tv.setText(JNINativeBridge.stringFromNative());
        int[] array = {3, 1, 2, 6, 8, 1};
        int[] temp = JNINativeBridge.sort1(array);
        Log.e(TAG, "onCreate: " + Arrays.toString(temp));

        User user = new User();
        user.id = 1001;
        user.city = "Gz";
        user.name = "lsl";
        ArrayList<User> users = new ArrayList<>();
        users.add(user);

        JNINativeBridge.classSort(user);

        JNINativeBridge.pareseJson(getJson());

        JNINativeBridge.getListUsers(users);

        List<User> list = JNINativeBridge.getListData();
        Log.e(TAG, "list大小:" + list.size());
    }

    public static String getJson() {

        return "{\n" +
                "  \"name\": \"含有中文Awesome 4K\",\n" +
                "  \"resolutions\": [\n" +
                "    {\n" +
                "      \"width\": 1280,\n" +
                "      \"height\": 720\n" +
                "    },\n" +
                "    {\n" +
                "      \"width\": 1920,\n" +
                "      \"height\": 1080\n" +
                "    },\n" +
                "    {\n" +
                "      \"width\": 3840,\n" +
                "      \"height\": \"xxx\"\n" +
                "    }\n" +
                "  ]\n" +
                "}";
    }


}
