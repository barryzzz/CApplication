package com.example.lishoulin.capplication;

import android.Manifest;
import android.app.Activity;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.provider.Settings;
import android.support.annotation.IntDef;
import android.support.annotation.NonNull;
import android.support.annotation.RequiresApi;
import android.support.v4.app.ActivityCompat;
import android.support.v7.app.AlertDialog;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;
import android.widget.Toast;

import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;
import java.util.Arrays;

public class Main2Activity extends AppCompatActivity {

    @IntDef({Type.CODE_STORAGE, Type.CODE_CAMERA, Type.CODE_SENSORS, Type.CODE_LOCATION})
    @Retention(RetentionPolicy.SOURCE)
    public @interface Type {
        int CODE_STORAGE = 1001;
        int CODE_CAMERA = 1002;
        int CODE_SENSORS = 1003;
        int CODE_LOCATION = 1004;

    }

    private Context mContext;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main2);
        mContext = this;
    }

    public void doStorage(View view) {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
            PermissionsUtil.newInstance(this).requestPermission(Manifest.permission.WRITE_EXTERNAL_STORAGE, new PermissionsUtil.CallBack() {
                @Override
                public void onSuccess(String[] permissions) {
                    toast("存储");
                }

                @Override
                public void onFaild(String[] permissions) {

                }

                @Override
                public void onRefuse(String permission) {

                }
            });
        }
    }

    public void doCamera(View view) {
        PermissionsUtil.newInstance(this).requestPermission(Manifest.permission.CAMERA, new PermissionsUtil.CallBack() {
            @Override
            public void onSuccess(String[] permissions) {
                Log.e("info-->", Arrays.toString(permissions));
                toast("相机");
            }

            @Override
            public void onFaild(String[] permissions) {
                Log.e("info-->", Arrays.toString(permissions));

            }

            @RequiresApi(api = Build.VERSION_CODES.M)
            @Override
            public void onRefuse(String permission) {
                Log.e("info-->", permission);
                gotoSettingActivity(mContext);

            }
        });


    }

    public void doSensors(View view) {
        PermissionsUtil.newInstance(this).requestPermission(Manifest.permission.BODY_SENSORS, new PermissionsUtil.CallBack() {
            @Override
            public void onSuccess(String[] permissions) {
                toast("传感器");
            }

            @Override
            public void onFaild(String[] permissions) {

            }

            @Override
            public void onRefuse(String permission) {

            }
        });

    }

    public void doLocation(View view) {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
//            if (ActivityCompat.checkSelfPermission(this, Manifest.permission.ACCESS_COARSE_LOCATION) != PackageManager.PERMISSION_GRANTED) {
//                reqLocationPremission(this);
//            } else {
//                toast("定位");
//            }
            PermissionsUtil.newInstance(this).requestPermission(Manifest.permission.ACCESS_COARSE_LOCATION, new PermissionsUtil.CallBack() {
                @Override
                public void onSuccess(String[] permissions) {
                    Log.e("info-->", Arrays.toString(permissions));
                }

                @Override
                public void onFaild(String[] permissions) {
                    Log.e("info-->", Arrays.toString(permissions));

                }

                @RequiresApi(api = Build.VERSION_CODES.M)
                @Override
                public void onRefuse(String permission) {
                    Log.e("info-->", permission);
                    gotoSettingActivity(mContext);

                }
            });
        }

    }

    public void doAlert(View view) {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
            if (!Settings.canDrawOverlays(Application.getApplicationContext())) {
                reqAlterPremission(Application.getApplicationContext());
                return;
            }
            toast("悬浮窗");

        }
    }


    @RequiresApi(api = Build.VERSION_CODES.M)
    private void reqLocationPremission(Context context) {
        boolean isPremission = ActivityCompat.shouldShowRequestPermissionRationale((Activity) context, Manifest.permission.ACCESS_COARSE_LOCATION);
        Log.e("info---->", "location isPremission:" + isPremission);
//        if (!isPremission) {
//            toast("已经禁止申请权限");
//            gotoSettingActivity(this);
//
//        } else {
        ActivityCompat.requestPermissions((Activity) context, new String[]{Manifest.permission.ACCESS_COARSE_LOCATION}, Type.CODE_LOCATION);
//        }

    }

    @RequiresApi(api = Build.VERSION_CODES.M)
    private void requestPremission(Context context, String permission, @Type int type) {
        boolean isPremission = ActivityCompat.shouldShowRequestPermissionRationale((Activity) context, permission);
        if (!isPremission) {
            toast("已经禁止申请权限");
            gotoSettingActivity(context);
        } else {
            ActivityCompat.requestPermissions((Activity) context, new String[]{permission}, type);

        }
    }


    @RequiresApi(api = Build.VERSION_CODES.M)
    private void reqAlterPremission(Context context) {
        Intent intent = new Intent(Settings.ACTION_MANAGE_OVERLAY_PERMISSION,
                Uri.parse("package:" + context.getPackageName()));
        intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
        context.startActivity(intent);
    }

    @RequiresApi(api = Build.VERSION_CODES.M)
    private void gotoSettingActivity(final Context context) {

        AlertDialog.Builder builder = new AlertDialog.Builder(context);
        builder.setTitle(R.string.req_premission).setMessage(R.string.req_msg);
        builder.setPositiveButton(R.string.req_cancle, new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialog, int which) {

            }
        }).setNegativeButton(R.string.req_setting, new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialog, int which) {

                Intent intent = new Intent();
                intent.setAction(Settings.ACTION_APPLICATION_DETAILS_SETTINGS);
                intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
                intent.setData(Uri.fromParts("package", context.getPackageName(), null));
                context.startActivity(intent);
            }
        });
        builder.create().show();

    }


    void toast(String str) {
        Toast.makeText(this, str, Toast.LENGTH_LONG).show();
    }


}
