package com.example.wingbu.ffmpegbasic;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

import com.example.wingbu.ffmpegbasic.opensl.OpenSLActivity;
import com.example.wingbu.ffmpegbasic.play.MixPlayActivity;
import com.example.wingbu.ffmpegbasic.play.RawPlayerActivity;
import com.example.wingbu.ffmpegbasic.play.VideoPlayActivity;
import com.example.wingbu.ffmpegbasic.play.VideoViewActivity;
import com.example.wingbu.ffmpegbasic.trans.TransPCMActivity;

public class IndexActivity extends AppCompatActivity {

    private Button mBtnOne;
    private Button mBtnTwo;
    private Button mBtnThree;
    private Button mBtnFour;
    private Button mBtnFive;
    private Button mBtnSix;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_index);
        initView();
    }

    private void initView(){
        mBtnOne = (Button) findViewById(R.id.btn_index_1);
        mBtnTwo = (Button) findViewById(R.id.btn_index_2);
        mBtnThree = (Button) findViewById(R.id.btn_index_3);
        mBtnFour = (Button) findViewById(R.id.btn_index_4);
        mBtnFive = (Button) findViewById(R.id.btn_index_5);
        mBtnSix = (Button) findViewById(R.id.btn_index_6);

        mBtnOne.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                jumpToRawPlayMusic();
            }
        });

        mBtnTwo.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                jumpToOpenSLPlayMusic();
            }
        });

        mBtnThree.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                jumpToPlayVideo();
            }
        });

        mBtnFour.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                jumpToMixPlayVideo();
            }
        });

        mBtnFive.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                jumpToViewPlayVideo();
            }
        });

        mBtnSix.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                jumpToDealPcm();
            }
        });
    }

    private void jumpToRawPlayMusic(){
        Intent intent = new Intent(IndexActivity.this, RawPlayerActivity.class);
        startActivity(intent);
    }

    private void jumpToOpenSLPlayMusic(){
        Intent intent = new Intent(IndexActivity.this, OpenSLActivity.class);
        startActivity(intent);
    }

    private void jumpToPlayVideo(){
        Intent intent = new Intent(IndexActivity.this, VideoPlayActivity.class);
        startActivity(intent);
    }

    private void jumpToMixPlayVideo(){
        Intent intent = new Intent(IndexActivity.this, MixPlayActivity.class);
        startActivity(intent);
    }

    private void jumpToViewPlayVideo(){
        Intent intent = new Intent(IndexActivity.this, VideoViewActivity.class);
        startActivity(intent);
    }

    private void jumpToDealPcm(){
        Intent intent = new Intent(IndexActivity.this, TransPCMActivity.class);
        startActivity(intent);
    }

}
