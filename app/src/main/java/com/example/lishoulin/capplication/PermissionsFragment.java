package com.example.lishoulin.capplication;

import android.annotation.TargetApi;
import android.content.pm.PackageManager;
import android.os.Build;
import android.os.Bundle;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.support.v4.app.ActivityCompat;

import java.util.ArrayList;
import java.util.List;

public class PermissionsFragment extends android.app.Fragment {


    private static final int CODE_REQ_PER = 90001;

    private CallBack mCallBack;


    public PermissionsFragment() {

    }

    @Override
    public void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setRetainInstance(true);
    }


    /**
     * 单独权限申请
     *
     * @param permission
     */
    void requestPermission(String permission, CallBack callBack) {
        if (!isMarshmallow()) {
            callBack.onGranted();
            return;
        }
        if (!isGranted(permission)) {
            requestPermission(new String[]{permission}, callBack);
            return;
        }
        callBack.onGranted();
    }


    /**
     * 多个权限申请
     *
     * @param permissions
     */
    @TargetApi(Build.VERSION_CODES.M)
    void requestPermission(String[] permissions, CallBack callBack) {
        if (permissions == null || permissions.length == 0) {
            throw new RuntimeException("permission array is null or empty");
        }
        this.mCallBack = callBack;

        List<String> mStringList = new ArrayList<>();
        mStringList.clear();

        for (int i = 0; i < permissions.length; i++) {
            if (!isGranted(permissions[i])) {
                mStringList.add(permissions[i]);
            }
        }
        if (mStringList.size() > 0) {
            String[] strs = mStringList.toArray(new String[mStringList.size()]);
            requestPermissions(strs, CODE_REQ_PER);
        } else {
            mCallBack.onGranted();
        }
    }


    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions, @NonNull int[] grantResults) {
        if (requestCode != CODE_REQ_PER) return;
        List<String> faiList = new ArrayList<>();
        for (int i = 0; i < permissions.length; i++) {
            if (!(grantResults[i] == PackageManager.PERMISSION_GRANTED)) {
                //申请失败的
                faiList.add(permissions[i]);
            }
        }
        if (permissions.length == 1) {
            if (!isShouldShowRequestPermissionRationale(permissions[0]) &&
                    !(grantResults[0] == PackageManager.PERMISSION_GRANTED)) {
                mCallBack.onRefusedAndDenied(permissions[0]);
            }
        }
        if (faiList.size() <= 0) {
            mCallBack.onGranted();
        } else {
            mCallBack.onRefused(faiList.toArray(new String[faiList.size()]));
        }

    }

    @TargetApi(Build.VERSION_CODES.M)
    private boolean isShouldShowRequestPermissionRationale(String permission) {
        return ActivityCompat.shouldShowRequestPermissionRationale(getActivity(), permission);
    }

    private boolean isMarshmallow() {
        return Build.VERSION.SDK_INT >= Build.VERSION_CODES.M;
    }

    @TargetApi(Build.VERSION_CODES.M)
    private boolean isGranted(String permission) {
        return ActivityCompat.checkSelfPermission(getActivity(), permission) == PackageManager.PERMISSION_GRANTED;
    }


    public interface CallBack {
        void onGranted();

        void onRefused(String[] permissions);

        void onRefusedAndDenied(String permission);

    }


}
