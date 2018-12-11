package com.example.wingbu.ffmpegbasic.trans;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import com.example.wingbu.ffmpegbasic.R;
import com.example.wingbu.ffmpegbasic.file.FileIndexActivity;
import com.example.wingbu.ffmpegbasic.file.FileResultEntity;

public class TransVideoActivity extends AppCompatActivity {

    public static final String TAG = "TransVideoActivity";

    private String mFilePath;

    private Button mBtnMp4;
    private Button mBtnH264;
    private Button mBtnYuvToH264;
    private Button mBtnFlv;

    private TextView tvChoose;
    private TextView tvShowPath;

    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_trans_video);

        initView();
        initEvent();
    }

    private void initView(){
        mBtnYuvToH264 = (Button) findViewById(R.id.btn_yuv_h264);
        mBtnH264 = (Button) findViewById(R.id.btn_h264);
        mBtnMp4 = (Button) findViewById(R.id.btn_mp4);
        mBtnFlv = (Button) findViewById(R.id.btn_flv);

        tvChoose = (TextView) findViewById(R.id.tv_choose_path);
        tvShowPath = (TextView) findViewById(R.id.tv_input_path);
    }

    private void initEvent(){
        mBtnYuvToH264.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {

            }
        });

        mBtnH264.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {

            }
        });

        mBtnMp4.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {

            }
        });

        mBtnFlv.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {

            }
        });

        tvChoose.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                findVideoPath();
            }
        });
    }

    /**
     * 进入文件选择页，获取对应视频文件路径
     * @return
     */
    private void findVideoPath(){
        Intent intent = new Intent(TransVideoActivity.this, FileIndexActivity.class);
        startActivityForResult(intent, FileResultEntity.REQUEST_CODE);
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
            tvShowPath.setText(mFilePath);
            Log.i(TAG," mFilePath = " + mFilePath);
        }
    }

//    public native void transYuvToH264(String inputFilePath,String outputFilePath);
    public native int transYuvToJpeg(String inputFilePath,String outputFilePath);
}
