#include <jni.h>
#include <string>
#include "test.h"
#include <iostream>
#include <android/log.h>
#include <string.h>
#include <stdlib.h>

using namespace std;

extern "C" {
#include "simple.h"
}

#define TAG "info--->"


extern void testextran(); //通过存储类 extern调用

typedef struct User {
    int id;
    char *name;
    char *city;
};


extern "C" JNIEXPORT jstring
JNICALL
Java_com_example_lishoulin_capplication_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    printhello();
    testextran();

    simple();
    write();


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