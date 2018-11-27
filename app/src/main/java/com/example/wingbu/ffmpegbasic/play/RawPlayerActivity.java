package com.example.wingbu.ffmpegbasic.play;

import android.media.MediaPlayer;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import com.example.wingbu.ffmpegbasic.R;

public class RawPlayerActivity extends AppCompatActivity {

    private MediaPlayer mp;//mediaPlayer对象
    private Button playBtn,pauseBtn,stopBtn;//播放 暂停/继续 停止 按钮
    private TextView hint;//显示当前播放状态
    private boolean isPause=false;//是否暂停

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_raw_player);
    }

    private void init() {
        playBtn = (Button) findViewById(R.id.btn_player);
        pauseBtn = (Button) findViewById(R.id.btn_pause);
        stopBtn = (Button) findViewById(R.id.btn_stop);

        playBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {

            }
        });

        pauseBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {

            }
        });

        stopBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {

            }
        });
    }
}
