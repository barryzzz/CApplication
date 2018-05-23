package com.example.lishoulin.capplication;

import android.app.Activity;
import android.app.FragmentManager;
import android.content.Context;
import android.content.pm.PackageManager;
import android.os.Bundle;
import android.support.annotation.MainThread;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.support.v4.app.ActivityCompat;
import android.util.Log;

import java.util.ArrayList;
import java.util.List;

public class PermissionsUtil extends android.app.Fragment {

    private static final String TAG = "PermissionsUtil";
    private static PermissionsUtil sPermissionsUtil;
    private static Context sContext;

    private static final int CODE_REQ_PER = 10001;
    private List<String> mStringList = new ArrayList<>();

    private CallBack mCallBack;

    @Override
    public void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setRetainInstance(true);
    }


    @MainThread
    public static PermissionsUtil newInstance(Context context) {
        sContext = context;
        sPermissionsUtil = findFragment(context);
        if (sPermissionsUtil == null) {
            sPermissionsUtil = new PermissionsUtil();
            FragmentManager fragmentManager = ((Activity) context).getFragmentManager();
            fragmentManager.beginTransaction().add(sPermissionsUtil, TAG).commitAllowingStateLoss();
            fragmentManager.executePendingTransactions();
        }
        return sPermissionsUtil;
    }

    private static PermissionsUtil findFragment(Context context) {
        Activity activity = ((Activity) context);
        return (PermissionsUtil) activity.getFragmentManager().findFragmentByTag(TAG);
    }

    /**
     * 单独权限申请
     *
     * @param permission
     */
    public void requestPermission(String permission, CallBack callBack) {

        if (ActivityCompat.checkSelfPermission(sContext, permission) != PackageManager.PERMISSION_GRANTED) {
            boolean isPermission = ActivityCompat.shouldShowRequestPermissionRationale((Activity) sContext, permission);
            Log.e(TAG, "权限:" + isPermission);
            if (!isPermission) {
                //权限被禁止了
                callBack.onRefuse(permission);
            } else {
                //申请权限
                requestPermission(new String[]{permission}, callBack);
            }
        } else {
            callBack.onSuccess(new String[]{permission});
        }


    }


    /**
     * 多个权限申请
     *
     * @param permissions
     */
    public void requestPermission(String[] permissions, CallBack callBack) {
        if (permissions == null) {
            throw new RuntimeException("permission array is null");
        }
        this.mCallBack = callBack;
        mStringList.clear();
        for (int i = 0; i < permissions.length; i++) {
            if (ActivityCompat.checkSelfPermission(sContext, permissions[0]) != PackageManager.PERMISSION_GRANTED) {
                mStringList.add(permissions[i]);
            }
        }
        if (mStringList.size() > 0) {
            String[] strs = mStringList.toArray(new String[mStringList.size()]);
            ActivityCompat.requestPermissions((Activity) sContext, strs, CODE_REQ_PER);
        }
    }


    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions, @NonNull int[] grantResults) {
        if (requestCode != CODE_REQ_PER) return;

        List<String> sucList = new ArrayList<>();
        List<String> faiList = new ArrayList<>();
        for (int i = 0; i < permissions.length; i++) {
            if (grantResults[i] == PackageManager.PERMISSION_GRANTED) {
                //申请成功的
                sucList.add(permissions[i]);
            } else {
                //申请失败的
                faiList.add(permissions[i]);
            }
        }
        if (sucList.size() == permissions.length) {
            mCallBack.onSuccess(sucList.toArray(new String[sucList.size()]));

        } else {
            mCallBack.onSuccess(sucList.toArray(new String[sucList.size()]));
            mCallBack.onFaild(faiList.toArray(new String[faiList.size()]));
        }

    }


    public interface CallBack {
        void onSuccess(String[] permissions);

        void onFaild(String[] permissions);

        void onRefuse(String permission);

    }


}
