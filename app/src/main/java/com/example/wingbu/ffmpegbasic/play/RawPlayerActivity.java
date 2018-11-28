package com.example.wingbu.ffmpegbasic.play;

import android.media.MediaPlayer;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import com.example.wingbu.ffmpegbasic.R;

public class RawPlayerActivity extends AppCompatActivity {

    private MediaPlayer mediaPlayer;//mediaPlayer对象
    private Button playBtn,pauseBtn,stopBtn;//播放 暂停/继续 停止 按钮
    private TextView hint;//显示当前播放状态
    private boolean isPause=false;//是否暂停

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_raw_player);
        init();
        mediaPlayer = MediaPlayer.create(RawPlayerActivity.this, R.raw.new_order_5_times_pcm);//创建mediaplayer对象
        mediaPlayer.setOnCompletionListener(new MediaPlayer.OnCompletionListener() {
            @Override
            public void onCompletion(MediaPlayer mediaPlayer) {
                play();
            }
        });
    }

    @Override
    protected void onDestroy() {
        if(mediaPlayer.isPlaying()){
            mediaPlayer.stop();
        }
        mediaPlayer.release();//释放资源
        super.onDestroy();
    }

    private void init() {
        hint = (TextView) findViewById(R.id.hint);
        playBtn = (Button) findViewById(R.id.btn_player);
        pauseBtn = (Button) findViewById(R.id.btn_pause);
        stopBtn = (Button) findViewById(R.id.btn_stop);

        playBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                play();
                if(isPause){
                    pauseBtn.setText("暂停");
                    isPause=false;
                }

            }
        });

        pauseBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if(mediaPlayer.isPlaying() && isPause == false){
                    mediaPlayer.pause();
                    isPause=true;
                    pauseBtn.setText("继续");
                    hint.setText("暂停播放音频...");
                    playBtn.setEnabled(true);
                }else {
                    mediaPlayer.start();
                    pauseBtn.setText("暂停");
                    hint.setText("继续播放音频...");
                    isPause=false;
                    playBtn.setEnabled(false);
                }
            }
        });

        stopBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                mediaPlayer.stop();
                hint.setText("停止播放音频...");
                pauseBtn.setEnabled(false);
                stopBtn.setEnabled(false);
                playBtn.setEnabled(true);
            }
        });
    }

    private void play(){
        try{
            mediaPlayer.reset();
            mediaPlayer = MediaPlayer.create(RawPlayerActivity.this, R.raw.new_order_5_times_pcm);//重新设置要播放的音频
            mediaPlayer.start();//开始播放
            hint.setText("正在播放音频...");
            playBtn.setEnabled(false);
            pauseBtn.setEnabled(true);
            stopBtn.setEnabled(true);
        }catch(Exception e){
            e.printStackTrace();//输出异常信息
        }

    }
    private void pause(){}
    private void stop(){}
}
