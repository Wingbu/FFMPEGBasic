package com.example.wingbu.ffmpegbasic.opensl;

import android.content.Intent;
import android.content.res.AssetManager;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;

import com.example.wingbu.ffmpegbasic.R;
import com.example.wingbu.ffmpegbasic.file.FileIndexActivity;
import com.example.wingbu.ffmpegbasic.file.FileResultEntity;
import com.example.wingbu.ffmpegbasic.trans.TransPCMActivity;

/**
 * 使用OpenSL播放音频
 *  包括：播放asset文件，播放URI，以及播放PCM文件
 */
public class OpenSLActivity extends AppCompatActivity {

    public static final String TAG = "OpenSLActivity";

    static {
        System.loadLibrary("native-lib");
    }

    private AssetManager assetManager;

    private String mFilePath = "/sdcard/ff-input/NocturneNo2inEflat_44.1k_s16le.pcm";

    private EditText etFilePath;
    private Button   btnChooseFilePath;

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

        etFilePath = (EditText) findViewById(R.id.et_file_name);
        btnChooseFilePath = (Button) findViewById(R.id.btn_choose_file);
        etFilePath.setText(mFilePath);

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
                playPcm(mFilePath);
            }
        });

        btnChooseFilePath.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(OpenSLActivity.this , FileIndexActivity.class);
                startActivityForResult(intent, FileResultEntity.REQUEST_CODE);
            }
        });
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        if(requestCode != FileResultEntity.REQUEST_CODE){
            return;
        }
        if(resultCode == FileResultEntity.RESULT_CODE_FAIL){
            return;
        }
        if(null == data){
            return;
        }
        if(resultCode == FileResultEntity.RESULT_CODE_SUCCESS ){
            mFilePath = data.getStringExtra(FileResultEntity.RESULT_TAG);
            etFilePath.setText(mFilePath);
            Log.i(TAG," mFilePath = " + mFilePath);
        }
    }

    public native void playAsset(AssetManager assetManager , String fileName );

    public native void playUri(String uri);

    public native void playPcm(String pcmPath_);
}
