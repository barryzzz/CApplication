package com.example.lishoulin.capplication

import android.os.Bundle
import android.support.v7.app.AppCompatActivity
import android.util.Log
import kotlinx.android.synthetic.main.activity_main.*
import java.util.*

class MainKtActivity : AppCompatActivity() {

    private val TAG = "MainKtActivity"


    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        sample_text.text = JniBridge.stringFromJNI()

        val array = intArrayOf(3, 1, 2, 6, 8, 1)
        val temp = JNINativeBridge.sort1(array)
        Log.e(TAG, Arrays.toString(temp))

        val user = User()
        user.id = 1001
        user.city = "Gz"
        user.name = "lsl"

        val users = ArrayList<User>()
        users.add(user)

        JNINativeBridge.classSort(user)
        JNINativeBridge.pareseJson(getJson())
        JNINativeBridge.getListUsers(users)
        val list = JNINativeBridge.getListData()
        Log.e(TAG, "list大小${list.size}")
    }


    fun getJson(): String = "{\n" +
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
            "}"


    companion object {
        init {
            System.loadLibrary("native-lib")
        }
    }


}