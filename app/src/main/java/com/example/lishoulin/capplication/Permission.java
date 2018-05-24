package com.example.lishoulin.capplication;

import android.app.Activity;
import android.app.FragmentManager;
import android.content.Context;
import android.content.Intent;
import android.net.Uri;
import android.os.Build;
import android.provider.Settings;

public class Permission {

    private static final String TAG = "Permission";
    private PermissionsFragment mPermissionsFragment;

    public Permission(Activity activity) {
        mPermissionsFragment = findFragment(activity);
        if (mPermissionsFragment == null) {
            mPermissionsFragment = new PermissionsFragment();
            FragmentManager manager = activity.getFragmentManager();
            manager.beginTransaction()
                    .add(mPermissionsFragment, TAG)
                    .commitAllowingStateLoss();
            manager.executePendingTransactions();
        }
    }


    private static PermissionsFragment findFragment(Activity activity) {
        return (PermissionsFragment) activity.getFragmentManager().findFragmentByTag(TAG);
    }

    /**
     * 单独权限申请，进行已经被拒绝处理
     *
     * @param permission
     * @param callback
     */
    public void requestPermission(String permission, PermissionsFragment.CallBack callback) {
        if (mPermissionsFragment == null) {
            throw new IllegalArgumentException("permission is not init!");
        }
        mPermissionsFragment.requestPermission(permission, callback);
    }

    /**
     * 多个权限申请，不做已被拒绝处理
     *
     * @param permissions
     * @param callback
     */
    public void requestPermission(String[] permissions, PermissionsFragment.CallBack callback) {
        if (mPermissionsFragment == null) {
            throw new IllegalArgumentException("permission is not init!");
        }
        mPermissionsFragment.requestPermission(permissions, callback);
    }

    /**
     * 判断是否有悬浮窗权限
     *
     * @param context
     * @return
     */
    public boolean isAlterWindow(Context context) {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
            return Settings.canDrawOverlays(context);
        }
        return true;
    }

    /**
     * 申请悬浮窗权限
     */
    public void requestAlertWindow(Context context) {
        Intent intent = new Intent(Settings.ACTION_MANAGE_OVERLAY_PERMISSION,
                Uri.parse("package:" + context.getPackageName()));
        intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
        context.startActivity(intent);
    }


}
