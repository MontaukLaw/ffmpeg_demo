#include <jni.h>
#include <string>
#include <android/log.h>
#include "MarcsPlayerCPP.h"
#include "JNICallbackHelper.h"

extern "C" {
#include "libget/get.h"
#include <libavutil/avutil.h>
}

#include "libcppcount/caculate.h"
#include <jni.h>

#define TAG "native-lib.cpp"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__);

extern "C" JNIEXPORT jstring JNICALL
Java_com_wulala_myapplicationndk_MainActivity_stringFromJNI(JNIEnv *env, jobject /* this */) {
    std::string hello = "Hello from C++";
    std::string s = "集成成功！FFmpeg Version：";
    s.append(av_version_info());
    // hello = get_action();
    LOGD("get %s", get_action());
    LOGD("result 1+1 = %d", add_action(1, 1));
    return env->NewStringUTF(s.c_str());
}

JavaVM *jvm = nullptr;
MarcsPlayerCPP *player = nullptr;

jint JNI_OnLoad(JavaVM *vm, void *args) {
    ::jvm = vm;
    return JNI_VERSION_1_6;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_wulala_myapplicationndk_MarcsPlayer_releaseNative(JNIEnv *env, jobject thiz) {
}

extern "C"
JNIEXPORT void JNICALL
Java_com_wulala_myapplicationndk_MarcsPlayer_playNative(JNIEnv *env, jobject thiz) {
    LOGD("enter play native\n");
}

extern "C"
JNIEXPORT void JNICALL
Java_com_wulala_myapplicationndk_MarcsPlayer_stopNative(JNIEnv *env, jobject thiz) {
}
extern "C"
JNIEXPORT void JNICALL
Java_com_wulala_myapplicationndk_MarcsPlayer_initNative(JNIEnv *env, jobject thiz, jstring data_source) {

    const char *play_source = env->GetStringUTFChars(data_source, 0);

    auto *helper = new JNICallbackHelper(jvm, env,thiz);

    player = new MarcsPlayerCPP(play_source, helper);

    player->init();

    env->ReleaseStringUTFChars(data_source, play_source);
}