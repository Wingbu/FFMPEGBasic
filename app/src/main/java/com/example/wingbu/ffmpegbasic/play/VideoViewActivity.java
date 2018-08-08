package com.example.wingbu.ffmpegbasic.play;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.VideoView;

import com.example.wingbu.ffmpegbasic.R;
import com.example.wingbu.ffmpegbasic.utils.FilePathUtils;

public class VideoViewActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_video_view);

        final VideoView videoView = (VideoView) findViewById(R.id.videoView1);

        Button setButton = (Button) this.findViewById(R.id.button_set);
        Button startButton = (Button) this.findViewById(R.id.button_start);
        Button pauseButton = (Button) this.findViewById(R.id.button_pause);
        Button stopButton = (Button) this.findViewById(R.id.button_stop);
        final EditText urlEditText= (EditText) this.findViewById(R.id.input_url);


        setButton.setOnClickListener(new View.OnClickListener() {
            public void onClick(View arg0){
                String folderurl = FilePathUtils.BASE_INPUT_PATH;
                String urltext = urlEditText.getText().toString();
                //Small FIX, Avoid '/'
                if(urltext.charAt(0)=='/'){
                    urltext=urltext.substring(1);
                }
                String inputurl = folderurl + urltext;
                Log.e("url",inputurl);

                videoView.setVideoPath(inputurl);
                //videoView.setMediaController(new MediaController(MainActivity.this));
            }
        });

        startButton.setOnClickListener(new View.OnClickListener() {
            public void onClick(View arg0){
                videoView.start();
            }
        });

        pauseButton.setOnClickListener(new View.OnClickListener() {
            public void onClick(View arg0){
                videoView.pause();
            }
        });

        stopButton.setOnClickListener(new View.OnClickListener() {
            public void onClick(View arg0){
                videoView.stopPlayback();
            }
        });

    }
}
