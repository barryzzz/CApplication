//
// Created by lishoulin on 18/4/19.
//

#include "simple.h"
#include <android/log.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "cJSON.h"

#define TAG "info---->"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,TAG ,__VA_ARGS__) // 定义LOGD类型
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG ,__VA_ARGS__) // 定义LOGI类型
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,TAG ,__VA_ARGS__) // 定义LOGW类型
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG ,__VA_ARGS__) // 定义LOGE类型
#define LOGF(...) __android_log_print(ANDROID_LOG_FATAL,TAG ,__VA_ARGS__) // 定义LOGF类型

int MAX_NUM = 100;

void simple() {
    __android_log_print(ANDROID_LOG_ERROR, TAG, "%s \n", "simple");
    register int mouth = 10;
    __android_log_print(ANDROID_LOG_DEBUG, TAG, "内存地址： %d \n", mouth);

}


void write() {
    __android_log_print(ANDROID_LOG_ERROR, TAG, "%s \n", "simple write");

    FILE *fp = NULL;
    fp = fopen("/sdcard/simple.txt", "a+");
    if (fp == NULL) {
        __android_log_print(ANDROID_LOG_ERROR, TAG, "%s \n", strerror(errno));
    } else {
        fputs("my name is lsl", fp);
        fclose(fp);
    }

}


int *sort1(int data[], int count) {
    int temp;
    LOGE("count: %d \n", sizeof(data) / sizeof(data[0]));

    for (int i = 1; i < count; i++) {
        for (int j = 0; j < i; j++) {
            if (data[i] < data[j]) {
                temp = data[i];
                data[i] = data[j];
                data[j] = temp;
            }
        }
    }
    return data;
}

int parse(const char *monitor) {
    const cJSON *resolution = NULL;
    const cJSON *resolutions = NULL;
    const cJSON *name = NULL;
    int status = 0;
    cJSON *monitor_json = cJSON_Parse(monitor);
    if (monitor_json == NULL) {
        const char *error = cJSON_GetErrorPtr();
        if (error != NULL) {
            fprintf(stderr, "Error before: %s\n", error);
        }
        status = 0;
        goto end;
    }

    name = cJSON_GetObjectItemCaseSensitive(monitor_json, "name");
    resolutions = cJSON_GetObjectItemCaseSensitive(monitor_json, "resolutions");

    printf("name value:%s \n", name->valuestring);
    LOGE("name value:%s \n", name->valuestring);

    cJSON_ArrayForEach(resolution, resolutions) {
        cJSON *w = cJSON_GetObjectItemCaseSensitive(resolution, "width");
        cJSON *h = cJSON_GetObjectItemCaseSensitive(resolution, "height");
        if (!cJSON_IsNumber(h)) {
            fprintf(stderr, "not number\n");
        }
        printf("width:%d height:%d \n", w->valueint, h->valueint);
        LOGE("width:%d height:%d \n", w->valueint, h->valueint);

    }
    end:
    cJSON_Delete(monitor_json);
    return status;
}