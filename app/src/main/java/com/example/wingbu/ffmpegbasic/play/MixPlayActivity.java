package com.example.wingbu.ffmpegbasic.play;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;

import com.example.wingbu.ffmpegbasic.R;

public class MixPlayActivity extends AppCompatActivity {

    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_mix_play);
    }

    public native void play(String input_ , Object surface);
}
