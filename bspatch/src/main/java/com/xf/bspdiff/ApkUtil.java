package com.xf.bspdiff;

import android.content.Context;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.content.pm.Signature;

/**
 * @author lishoulin
 * @version 1.0
 * @date 2018/7/30
 */
public class ApkUtil {

    public static int getSignature(Context context) {
        try {
            PackageInfo packageInfo = context.getPackageManager()
                    .getPackageInfo("com.xf.bspdiff", PackageManager.GET_SIGNATURES);
            Signature[] signas = packageInfo.signatures;
            Signature sign = signas[0];
            return sign.hashCode();
        } catch (PackageManager.NameNotFoundException e) {
            e.printStackTrace();
        }

        return -1;

    }
}
