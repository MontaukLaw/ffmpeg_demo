package com.wulala.myapplicationndk;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.os.Environment;
import android.util.Log;
import android.widget.TextView;
import android.widget.Toast;

import com.wulala.myapplicationndk.databinding.ActivityMainBinding;

import java.io.File;

public class MainActivity extends AppCompatActivity {

    private final static String TAG = MainActivity.class.getSimpleName();

    private MarcsPlayer marcsPlayer;

    // Used to load the 'myapplicationndk' library on application startup.
    // 如果使用动态库, 就需要loadLibrary
//    static {
//        // 如果getndk这个库是动态的, 就需要在这里引入一下
//        System.loadLibrary("getndk");
//
//        // 因为主库一般是动态的, 所以需要引入
//        System.loadLibrary("myapplicationndk");
//    }

    private ActivityMainBinding binding;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        marcsPlayer = new MarcsPlayer();

        marcsPlayer.setDataSource(new File(getFilesDir() +
                File.separator + "q.mp4").getAbsolutePath());

        marcsPlayer.setOnReadyListener(new MarcsPlayer.OnInitReadyListener() {
            @Override
            public void onInitReady() {
                runOnUiThread(new Runnable() {
                    @Override
                    public void run() {
                        Toast.makeText(MainActivity.this, "准备好了, 即将播放", Toast.LENGTH_SHORT).show();
                    }
                });

                marcsPlayer.play();
            }
        });
    }

    @Override
    protected void onResume() {
        super.onResume();
        marcsPlayer.getReady();
    }

    @Override
    protected void onStop() {
        super.onStop();
        marcsPlayer.stop();
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        marcsPlayer.release();
    }

    public native String stringFromJNI();

    // public native String get_action();
}