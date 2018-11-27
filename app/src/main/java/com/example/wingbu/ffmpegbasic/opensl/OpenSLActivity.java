package com.example.wingbu.ffmpegbasic.opensl;

import android.content.res.AssetManager;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

import com.example.wingbu.ffmpegbasic.R;

public class OpenSLActivity extends AppCompatActivity {

    static {
        System.loadLibrary("native-lib");
    }

    private AssetManager assetManager;

    private Button mBtnAsset;
    private Button mBtnUri;
    private Button mBtnPcm;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_open_sl);
        initView();
        assetManager = getAssets();
    }

    private void initView(){
        mBtnAsset = (Button) findViewById(R.id.btn_asset);
        mBtnUri = (Button) findViewById(R.id.btn_uri);
        mBtnPcm = (Button) findViewById(R.id.btn_pcm);

        mBtnAsset.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                playAsset(assetManager,"31.mp3");
            }
        });

        mBtnUri.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                playUri("http://mpge.5nd.com/2015/2015-11-26/69708/1.mp3");
            }
        });

        mBtnPcm.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                playPcm("/sdcard/ff-input/new_order_5_times_pcm.pcm");
            }
        });
    }

    public native void playAsset(AssetManager assetManager , String fileName );

    public native void playUri(String uri);

    public native void playPcm(String pcmPath_);
}
