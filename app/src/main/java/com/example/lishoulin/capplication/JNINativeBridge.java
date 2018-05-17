package com.example.lishoulin.capplication;

import java.util.ArrayList;

public class JNINativeBridge {
    /**
     * 数字排序1
     *
     * @return
     */
    public static native int[] sort1(int[] data);


    public static native void classSort(User users);

    public static native int pareseJson(String json);


    public static native void getListUsers(ArrayList<User> users);


    public static native ArrayList<User> getListData();


    public static native String stringFromNative();

}
