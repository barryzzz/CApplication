#include <jni.h>
#include <string>
#include <android/log.h>

extern "C" {
#include "bspatch.h"
}


#define TAG "info--->"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,TAG ,__VA_ARGS__) // 定义LOGD类型
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG ,__VA_ARGS__) // 定义LOGI类型
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,TAG ,__VA_ARGS__) // 定义LOGW类型
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG ,__VA_ARGS__) // 定义LOGE类型
#define LOGF(...) __android_log_print(ANDROID_LOG_FATAL,TAG ,__VA_ARGS__) // 定义LOGF类型




extern "C"
JNIEXPORT void JNICALL
Java_com_example_lishoulin_capplication_JNINativeBridge_fkDiff(JNIEnv *env, jobject instance, jstring oldFile_,
                                        jstring newFile_, jstring patchFile_) {
    const char *oldFile = env->GetStringUTFChars(oldFile_, NULL);
    const char *newFile = env->GetStringUTFChars(newFile_, NULL);
    const char *patchFile = env->GetStringUTFChars(patchFile_, NULL);
    if (oldFile == NULL) {
        return;
    }
    if (newFile == NULL) {
        return;
    }
    if (patchFile == NULL) {
        return;
    }

    const char *comm = "bspatch";
    char *argv[4];
    argv[0] = const_cast<char *>(comm);
    argv[1] = const_cast<char *>(oldFile);
    argv[2] = const_cast<char *>(newFile);
    argv[3] = const_cast<char *>(patchFile);

    LOGE("oldfile:%s \n", argv[1]);
    LOGE("difffile:%s \n", argv[3]);

    fkdiff(4, argv);

    env->ReleaseStringUTFChars(oldFile_, oldFile);
    env->ReleaseStringUTFChars(newFile_, newFile);
    env->ReleaseStringUTFChars(patchFile_, patchFile);


}



