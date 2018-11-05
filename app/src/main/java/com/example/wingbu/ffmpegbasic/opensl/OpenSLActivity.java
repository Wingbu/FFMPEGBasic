package com.example.wingbu.ffmpegbasic.opensl;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

import com.example.wingbu.ffmpegbasic.R;

public class OpenSLActivity extends AppCompatActivity {

    private Button mBtnAsset;
    private Button mBtnUri;
    private Button mBtnPcm;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_open_sl);
        initView();
    }

    private void initView(){
        mBtnAsset = (Button) findViewById(R.id.btn_asset);
        mBtnUri = (Button) findViewById(R.id.btn_uri);
        mBtnPcm = (Button) findViewById(R.id.btn_pcm);

        mBtnAsset.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {

            }
        });

        mBtnUri.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {

            }
        });

        mBtnPcm.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {

            }
        });
    }
}
