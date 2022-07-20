//
// Created by Marc on 2022/7/20.
//

#ifndef MY_APPLICATION_NDK_MARCSPLAYERCPP_H
#define MY_APPLICATION_NDK_MARCSPLAYERCPP_H
#include "JNICallbackHelper.h"
#include "AudioChannel.h"
#include "VideoChannel.h"

extern "C" {
#include <libavformat/avformat.h>
#include <pthread.h>
};

class MarcsPlayerCPP {

public:
    MarcsPlayerCPP(const char *data_source, JNICallbackHelper *helper);

    ~MarcsPlayerCPP();

    void init();

    void init_();

private:
    char *data_source = 0;
    pthread_t pid_init;
    AVFormatContext *formatContext = nullptr;
    AudioChannel *audio_channel = nullptr;
    VideoChannel *video_channel = nullptr;
    JNICallbackHelper *helper = 0;

};


#endif //MY_APPLICATION_NDK_MARCSPLAYERCPP_H
