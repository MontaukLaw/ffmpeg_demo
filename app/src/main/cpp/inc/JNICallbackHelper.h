#ifndef MY_APPLICATION_NDK_JNICALLBACKHELPER_H
#define MY_APPLICATION_NDK_JNICALLBACKHELPER_H

#include <jni.h>
#include "util.h"

class JNICallbackHelper {
public:
    JNICallbackHelper(JavaVM *vm, JNIEnv *env, jobject job);

    virtual ~JNICallbackHelper();

    void onInit(int thread_mode);

private:
    JavaVM *vm = nullptr;
    JNIEnv*env = nullptr;
    jobject job;
    jmethodID jmd_init;

};

#endif //MY_APPLICATION_NDK_JNICALLBACKHELPER_H
