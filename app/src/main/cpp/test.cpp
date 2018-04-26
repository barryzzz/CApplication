//
// Created by lishoulin on 18/4/18.
//
#include <iostream>
#include "test.h"
#include <android/log.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define random(x)(rand()%x)

using namespace std;

#define TAG "info--->"
#define MAX_TIME 100
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,TAG ,__VA_ARGS__) // 定义LOGD类型
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG ,__VA_ARGS__) // 定义LOGI类型
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,TAG ,__VA_ARGS__) // 定义LOGW类型
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG ,__VA_ARGS__) // 定义LOGE类型
#define LOGF(...) __android_log_print(ANDROID_LOG_FATAL,TAG ,__VA_ARGS__) // 定义LOGF类型


void printhello() {
    std::cout << "hello world jni method" << std::endl;
    const char *str = "hello world jni method";
    str = "xxx";
    __android_log_print(ANDROID_LOG_ERROR, TAG, "%s \n", str);

    __android_log_print(ANDROID_LOG_ERROR, TAG, "%d \n", MAX_TIME);


}


void start_thread() {
}


class Person {
public:
    int id;
    string name;

    void setCity(string city);

    string getCity();

private:
    string city;

protected:
    int age;
};

void Person::setCity(string city) {
    this->city = city;
}

string Person::getCity() {
    return city;
}



void learn_c() {
    srand(time(0));//设置种子

    for (int i = 0; i < 10; ++i) {
        LOGE("%d", random(10));
    }
    Person person;
    person.id = 1;
    person.name = "lsl";
    person.setCity("gz");


    LOGE("======================");
    LOGE("my name is %s", person.name.c_str());
    LOGE("my city is %s", person.getCity().c_str());

}