#include <jni.h>
#include "test.h"
#include <iostream>
#include <android/log.h>
#include <string.h>
#include <stdlib.h>
#include <sys/inotify.h>
#include <unistd.h>
#include <malloc.h>


using namespace std;

extern "C" {
#include "simple.h"
}
extern "C" {
#include "bspatch.h"
}

#define TAG "info--->"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,TAG ,__VA_ARGS__) // 定义LOGD类型
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG ,__VA_ARGS__) // 定义LOGI类型
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,TAG ,__VA_ARGS__) // 定义LOGW类型
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG ,__VA_ARGS__) // 定义LOGE类型
#define LOGF(...) __android_log_print(ANDROID_LOG_FATAL,TAG ,__VA_ARGS__) // 定义LOGF类型


extern void testextran(); //通过存储类 extern调用

typedef struct User {
    int id;
    char *name;
    char *city;
};


extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_lishoulin_capplication_JNINativeBridge_stringFromNative(JNIEnv *env, jclass type) {

    std::string hello = "Hello from C++";
    printhello();
    testextran();

    simple();
    writeSample();

    learn_c();

    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_lishoulin_capplication_JniBridge_stringFromJNI(JNIEnv *env, jclass type) {
    std::string hello = "Hello from C++";
    printhello();
    testextran();

    simple();
    writeSample();

    learn_c();

    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT jintArray JNICALL
Java_com_example_lishoulin_capplication_JNINativeBridge_sort1(JNIEnv *env, jclass type,
                                                              jintArray data_) {
    jint *data = env->GetIntArrayElements(data_, NULL);

    int count = env->GetArrayLength(data_);

    int *arr = sort1(data, count);
    env->ReleaseIntArrayElements(data_, arr, 0);

    return data_;

}




extern "C"
JNIEXPORT void JNICALL
Java_com_example_lishoulin_capplication_JNINativeBridge_classSort(JNIEnv *env, jclass type,
                                                                  jobject users) {
    struct User user;
    user.name = (char *) malloc(sizeof(char)); //结构体成员是指针，需要进行初始化指针
    user.city = (char *) malloc(sizeof(char)); //结构体成员是指针，需要进行初始化指针
//    jclass jcUser = env->FindClass("com/example/lishoulin/capplication/User");

    jclass jcUser = env->GetObjectClass(users);
    jfieldID jcuserId = env->GetFieldID(jcUser, "id", "I");

    jfieldID jcUserName = env->GetFieldID(jcUser, "name", "Ljava/lang/String;");
    jfieldID jcUserCity = env->GetFieldID(jcUser, "city", "Ljava/lang/String;");
    jstring name = (jstring) env->GetObjectField(users, jcUserName);
    jstring city = (jstring) env->GetObjectField(users, jcUserCity);

    const char *username = (char *) env->GetStringUTFChars(name, NULL);
    const char *usercity = (char *) env->GetStringUTFChars(city, NULL);


    user.id = env->GetIntField(users, jcuserId);
    strcpy(user.name, username);
    strcpy(user.city, usercity);


    __android_log_print(ANDROID_LOG_ERROR, "info---->", "user id:%d \n", user.id);

    __android_log_print(ANDROID_LOG_ERROR, "info---->", "user name:%s \n", user.name);

    __android_log_print(ANDROID_LOG_ERROR, "info---->", "user city:%s \n", user.city);

}

extern "C"
JNIEXPORT jint JNICALL
Java_com_example_lishoulin_capplication_JNINativeBridge_pareseJson(JNIEnv *env, jclass type,
                                                                   jstring json_) {
    const char *json = env->GetStringUTFChars(json_, 0);

    int state = parse(json);

    env->ReleaseStringUTFChars(json_, json);

    return state;
}


extern "C"
JNIEXPORT void JNICALL
Java_com_example_lishoulin_capplication_JNINativeBridge_getListUsers(JNIEnv *env, jclass type,
                                                                     jobject users) {
    jclass list_cls = env->GetObjectClass(users);

    jmethodID list_get = env->GetMethodID(list_cls, "get", "(I)Ljava/lang/Object;");

    jmethodID list_size = env->GetMethodID(list_cls, "size", "()I");

    jint len = env->CallIntMethod(users, list_size);

    LOGE("list size:%d \n", len);
    LOGE("输出接收来的list集合");
    for (int i = 0; i < len; i++) {
        jobject obj_user = env->CallObjectMethod(users, list_get, i);
        jclass cls_user = env->GetObjectClass(obj_user);


        jfieldID jcuserId = env->GetFieldID(cls_user, "id", "I");
        jfieldID jcUserName = env->GetFieldID(cls_user, "name", "Ljava/lang/String;");
        jfieldID jcUserCity = env->GetFieldID(cls_user, "city", "Ljava/lang/String;");
        jstring name = (jstring) env->GetObjectField(obj_user, jcUserName);
        jstring city = (jstring) env->GetObjectField(obj_user, jcUserCity);

        const int userId = env->GetIntField(users, jcuserId);
        const char *username = (char *) env->GetStringUTFChars(name, NULL);
        const char *usercity = (char *) env->GetStringUTFChars(city, NULL);


        LOGE("userId:%d \n", userId);
        LOGE("username:%s \n", username);
        LOGE("usercity:%s \n", usercity);

    }
}

extern "C"
JNIEXPORT jobject JNICALL
Java_com_example_lishoulin_capplication_JNINativeBridge_getListData(JNIEnv *env, jclass type) {

    jclass list_cls = env->FindClass("java/util/ArrayList");
    jmethodID list_init = env->GetMethodID(list_cls, "<init>", "()V");
    jobject obj_ArrayList = env->NewObject(list_cls, list_init, "");

    jmethodID list_add = env->GetMethodID(list_cls, "add", "(Ljava/lang/Object;)Z");

    jclass cls_user = env->FindClass("com/example/lishoulin/capplication/User");
    jmethodID user_init = env->GetMethodID(cls_user, "<init>", "()V");

//    创建一个user对象
//    jobject oj_user = env->NewObject(cls_user, user_init, "");

    for (int i = 0; i < 5; i++) {
        jobject oj_user = env->NewObject(cls_user, user_init, "");

        jfieldID jcuserId = env->GetFieldID(cls_user, "id", "I");
        jfieldID jcUserName = env->GetFieldID(cls_user, "name", "Ljava/lang/String;");
        jfieldID jcUserCity = env->GetFieldID(cls_user, "city", "Ljava/lang/String;");

        env->SetIntField(oj_user, jcuserId, i);
        env->SetObjectField(oj_user, jcUserName, env->NewStringUTF("yrd"));
        env->SetObjectField(oj_user, jcUserCity, env->NewStringUTF("sz"));

        //添加到list集合
        env->CallObjectMethod(obj_ArrayList, list_add, oj_user);

    }

    return obj_ArrayList;


}
static JNINativeMethod gNative_lib[] = {

};

int register_native_lib(JNIEnv *env) {

}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_lishoulin_capplication_JNINativeBridge_fkDiff(JNIEnv *env, jclass type,
                                                               jstring oldFile_, jstring newFile_,
                                                               jstring patchFile_) {
    const char *oldFile = env->GetStringUTFChars(oldFile_, 0);
    const char *newFile = env->GetStringUTFChars(newFile_, 0);
    const char *patchFile = env->GetStringUTFChars(patchFile_, 0);

    const char *comm = "bspatch";
    char *argv[4];
    argv[0] = const_cast<char *>(comm);
    argv[1] = const_cast<char *>(oldFile);
    argv[2] = const_cast<char *>(newFile);
    argv[3] = const_cast<char *>(patchFile);

    LOGE("oldfile:%s \n", argv[1]);
    LOGE("difffile:%s \n", argv[3]);

    fkdiff(4, argv);


//

    env->ReleaseStringUTFChars(oldFile_, oldFile);
    env->ReleaseStringUTFChars(newFile_, newFile);
    env->ReleaseStringUTFChars(patchFile_, patchFile);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_lishoulin_capplication_JNINativeBridge_callUnInstallListener(JNIEnv *env,
                                                                              jclass type,
                                                                              jint version,
                                                                              jstring path_) {
    const char *path = env->GetStringUTFChars(path_, 0);
    pid_t pid = fork();
    if (pid < 0) {
        LOGE("进程克隆失败");
    } else if (pid > 0) {
        LOGE("父进程");
    } else {
        LOGE("子进程！");
        int fuile = inotify_init();
        int watch = inotify_add_watch(fuile, path, IN_DELETE_SELF);
        void *p = malloc(sizeof(struct inotify_event));
        read(fuile, p, sizeof(struct inotify_event));
        inotify_rm_watch(fuile, watch);
        LOGD("接下来进行操作，来条状网页!!!");

    }

    env->ReleaseStringUTFChars(path_, path);
}