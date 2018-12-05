package com.example.wingbu.ffmpegbasic;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

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

            }
        });

        mBtnTwo.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {

            }
        });

        mBtnThree.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {

            }
        });

        mBtnFour.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {

            }
        });

        mBtnFive.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {

            }
        });

        mBtnSix.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {

            }
        });
    }

    private void jumpToRawPlayMusic(){}

    private void jumpToPlayVideo(){}

    private void jumpToMixPlayVideo(){}
}
