#include "inc/JNICallbackHelper.h"

JNICallbackHelper::JNICallbackHelper(JavaVM *vm, JNIEnv *env, jobject job) {
    this->vm = vm;
    this->env = env;
    this->job = env->NewGlobalRef(job);

    jclass clazz = env->GetObjectClass(this->job);
    jmd_init = env->GetMethodID(clazz, "onInitReady", "()V");
}

JNICallbackHelper::~JNICallbackHelper() {
    this->vm = nullptr;
    env->DeleteGlobalRef(job);
    job = nullptr;
    env = nullptr;
}

void JNICallbackHelper::onInit(int thread_mode) {
    if (thread_mode == THREAD_MAIN) {
        // 主线程
        env->CallVoidMethod(job, this->jmd_init);
    } else {
        // 子线程
        JNIEnv *env_child;
        vm->AttachCurrentThread(&env_child, nullptr);
        env_child->CallVoidMethod(job, this->jmd_init);
        vm->DetachCurrentThread();
    }
}

