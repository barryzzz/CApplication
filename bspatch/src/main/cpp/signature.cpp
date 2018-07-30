//
// Created by lishoulin on 2018/7/30.
//

#include <jni.h>


#define TAG "info--->"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,TAG ,__VA_ARGS__) // 定义LOGD类型
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG ,__VA_ARGS__) // 定义LOGI类型
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,TAG ,__VA_ARGS__) // 定义LOGW类型
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG ,__VA_ARGS__) // 定义LOGE类型
#define LOGF(...) __android_log_print(ANDROID_LOG_FATAL,TAG ,__VA_ARGS__) // 定义LOGF类型

const char *app_packagename = "com.xf.bspdiff";
const int hase_code = 1;



/**
 * ndk 签名校验，调用Java层的方法，与上面的hase_code 进行比对
 */
extern "C"
JNIEXPORT jint JNICALL
Java_com_xf_bspdiff_MainActivity_checkSignature(JNIEnv *env, jobject instance, jobject context) {

    /**
     * jni 操作Java方法真是麻烦
     */

    jclass context_class = env->GetObjectClass(context);

    jmethodID methodID_getPackageManager = env->GetMethodID(context_class, "getPackageManager",
                                                            "()Landroid/content/pm/PackageManager;");
    jobject packManager = env->CallObjectMethod(context, methodID_getPackageManager);

    jclass pm_clazz = env->GetObjectClass(packManager);


    jmethodID methodID_pm = env->GetMethodID(pm_clazz, "getPackageInfo",
                                             "(Ljava/lang/String;I)Landroid/content/pm/PackageInfo;");
    jmethodID jmethodID1_pack = env->GetMethodID(context_class, "getPackageName",
                                                 "()Ljava/lang/String;");

    jstring current_package = (jstring) (env->CallObjectMethod(context, jmethodID1_pack));

    const char *pack_name = env->GetStringUTFChars(current_package, 0);

    jmethodID methodID_current = env->GetMethodID(context_class, "getPackageName",
                                                  "()Ljava/lang/String;");



    return -1;

}