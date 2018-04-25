//
// Created by lishoulin on 18/4/18.
//
#include <iostream>
#include "test.h"
#include <android/log.h>

using namespace std;

#define TAG "info--->"
#define MAX_TIME 100


void printhello() {
    std::cout << "hello world jni method" << std::endl;
    const char *str = "hello world jni method";
    str = "xxx";
    __android_log_print(ANDROID_LOG_ERROR, TAG, "%s \n", str);

    __android_log_print(ANDROID_LOG_ERROR, TAG, "%d \n", MAX_TIME);


}


void start_thread() {
}
