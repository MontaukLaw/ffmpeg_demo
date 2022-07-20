#include "inc/MarcsPlayerCPP.h"
#include <android/log.h>

#define TAG_CPP "MarcsPlayerCPP.cpp"
#define LOGCPP(...) __android_log_print(ANDROID_LOG_DEBUG, TAG_CPP, __VA_ARGS__);

MarcsPlayerCPP::MarcsPlayerCPP(const char *data_source, JNICallbackHelper *helper) {

    this->data_source = new char[strlen(data_source) + 1];
    strcpy(this->data_source, data_source);
    this->helper = helper;
}


void *task_init(void *args) {
    MarcsPlayerCPP *player = static_cast<MarcsPlayerCPP *>(args);
    player->init_();
    return nullptr;
}

// java主线程会调用上面的函数
void MarcsPlayerCPP::init() {
    pthread_create(&pid_init, 0, task_init, this);
}

void MarcsPlayerCPP::init_() {
    // step 1. open stream data source
    formatContext = avformat_alloc_context();

    // 字典键值对
    AVDictionary *overtimeDictionary = nullptr;
    av_dict_set(&overtimeDictionary, "timeout", "5000000", 0); // us

    LOGCPP("%s", data_source);

    int ret = avformat_open_input(&formatContext, data_source, 0, &overtimeDictionary);

    av_dict_free(&overtimeDictionary);

    if (ret) {
        LOGCPP("Open data source error\n");
        return;
    } else {
        LOGCPP("Found input data source \n");
    }

    // step 2. find steam info
    ret = avformat_find_stream_info(formatContext, 0);

    if (ret < 0) {

        return;
    }

    // step 3. find stream one by one
    for (int i = 0; i < this->formatContext->nb_streams; i++) {
        AVStream *stream = formatContext->streams[i];

        AVCodecParameters *parameters = stream->codecpar;

        AVCodec *codec = avcodec_find_decoder(parameters->codec_id);
        AVCodecContext *codecContext = avcodec_alloc_context3(codec);

        if (!codecContext) {
            return;
        }

        ret = avcodec_parameters_to_context(codecContext, parameters);
        if (ret < 0) {
            return;
        }

        ret = avcodec_open2(codecContext, codec, nullptr);
        if (ret) {
            return;
        }

        if (parameters->codec_type == AVMediaType::AVMEDIA_TYPE_AUDIO) {
            audio_channel = new AudioChannel();

        } else if (parameters->codec_type == AVMediaType::AVMEDIA_TYPE_VIDEO) {
            video_channel = new VideoChannel();
        }

    }

    if (!audio_channel && !video_channel) {
        return;
    }

    if (helper) {
        helper->onInit(THREAD_CHILD);
    }
}

MarcsPlayerCPP::~MarcsPlayerCPP() {
    if (this->data_source) {
        delete data_source;
        data_source = nullptr;
    }

    if (this->helper) {
        delete helper;
        helper = nullptr;
    }
}
