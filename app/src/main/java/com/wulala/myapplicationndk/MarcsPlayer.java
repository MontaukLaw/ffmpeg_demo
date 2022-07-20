package com.wulala.myapplicationndk;

import android.util.Log;

public class MarcsPlayer {

    private static final String TAG = MarcsPlayer.class.getSimpleName();

    static {
        System.loadLibrary("myapplicationndk");
    }

    private OnInitReadyListener onReadyListener;

    public MarcsPlayer() {
    }

    // 保存文件地址或者媒体流地址
    private String dataSource;

    public void setDataSource(String mDataSource) {
        Log.d(TAG, "setDataSource: " + mDataSource);
        this.dataSource = mDataSource;
    }

    // 准备资源
    public void getReady() {
        Log.d(TAG, "initNative: ");
        initNative(dataSource);
    }

    public void play() {
        playNative();
    }

    public void stop() {
        stopNative();
    }

    // 给jni调用
    public void onInitReady() {
        if (null != this.onReadyListener) {
            this.onReadyListener.onInitReady();
        }
    }

    public void setOnReadyListener(OnInitReadyListener onReadyListener) {
        this.onReadyListener = onReadyListener;
    }

    interface OnInitReadyListener {
        void onInitReady();
    }

    // 释放资源
    public void release() {
        releaseNative();
    }

    private native void initNative(String dataSource);

    private native void releaseNative();

    private native void playNative();

    private native void stopNative();


}
