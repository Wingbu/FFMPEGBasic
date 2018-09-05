package com.example.wingbu.ffmpegbasic.play;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

import com.example.wingbu.ffmpegbasic.R;

public class VideoPlayActivity extends AppCompatActivity implements SurfaceHolder.Callback{

    static {
        System.loadLibrary("native-lib");
    }

    SurfaceHolder mSurfaceHolder;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_video_play);
        SurfaceView surfaceView = (SurfaceView) findViewById(R.id.surface_view);
        mSurfaceHolder = surfaceView.getHolder();
        mSurfaceHolder.addCallback(this);
    }

    @Override
    public void surfaceCreated(final SurfaceHolder surfaceHolder) {
        new Thread(new Runnable() {
            @Override
            public void run() {
                Log.i("ffmpeg"," surfaceCreated ");
                play("sdcard/ff-input/example.avi",surfaceHolder.getSurface());
            }
        }).start();
    }

    @Override
    public void surfaceChanged(SurfaceHolder surfaceHolder, int i, int i1, int i2) {

    }

    @Override
    public void surfaceDestroyed(SurfaceHolder surfaceHolder) {

    }

    public native int play(String input_,Object surface);
}
