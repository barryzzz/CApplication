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


extern "C" JNIEXPORT jstring
JNICALL
Java_com_xf_bspdiff_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";


    return env->NewStringUTF(hello.c_str());
}


extern "C"
JNIEXPORT void JNICALL
Java_com_xf_bspdiff_MainActivity_fkDiff(JNIEnv *env, jobject instance, jstring oldFile_,
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



extern "C" JNIEXPORT jstring
JNICALL
Java_com_xf_bspdiff_MainActivity_pareseString(JNIEnv *env, jobject jobject1, jstring str_) {
    const jchar *c_str = NULL;
    char buff[128];
    char *p = buff;
    c_str = env->GetStringCritical(str_, NULL);  //返回字符串指针
    if (c_str == NULL) {
        return env->NewStringUTF("字符串不能为空哦");
    }

    while (*c_str) {
        *p++ = *c_str++;
    }
    /**
     * Java端传递中文字符串，使用jstring 去接收
     */
    int a = env->GetStringLength(str_);
    int b = env->GetStringUTFLength(str_);
    LOGE("a数：%d %d",a,b);
    /**
     * 在 GetStringCritical 和 ReleaseStringCritical 两个函数之间的 Native 代码
     * 不能调用任何会让线程阻塞或者等待 JVM 中其他线程的 Native 函数或 JNI 函数。
     */
    env->ReleaseStringCritical(str_, c_str);

    return env->NewStringUTF(buff);

}