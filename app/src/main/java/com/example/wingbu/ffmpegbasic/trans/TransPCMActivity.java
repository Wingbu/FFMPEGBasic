package com.example.wingbu.ffmpegbasic.trans;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

import com.example.wingbu.ffmpegbasic.R;
import com.example.wingbu.ffmpegbasic.file.FileIndexActivity;
import com.example.wingbu.ffmpegbasic.file.FileResultEntity;
import com.example.wingbu.ffmpegbasic.opensl.OpenSLActivity;
import com.example.wingbu.ffmpegbasic.utils.DateUtils;
import com.example.wingbu.ffmpegbasic.utils.TextUtils;
import com.example.wingbu.ffmpegbasic.utils.ToastUtils;

public class TransPCMActivity extends AppCompatActivity {

    public static final String TAG = "TransPCMActivity";

    private String mFilePath;

    private Button mBtnLeftRight;
    private Button mBtnVolumeHalf;
    private Button mBtnSpeedUp;
    private Button mBtn16To8;
    private Button mBtnPcmToWav;
    private Button mBtnGoPlay;

    private EditText etFilePath;
    private Button   btnChooseFilePath;

    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_trans_pcm);
        initView();
    }

    private void initView(){

        etFilePath = (EditText) findViewById(R.id.et_file_name);
        btnChooseFilePath = (Button) findViewById(R.id.btn_choose_file);


        mBtnLeftRight = (Button) findViewById(R.id.btn_divide_left_right);
        mBtnVolumeHalf = (Button) findViewById(R.id.btn_volume_half);
        mBtnSpeedUp= (Button) findViewById(R.id.btn_speed_up);
        mBtn16To8 = (Button) findViewById(R.id.btn_change_16_to_8);
        mBtnPcmToWav = (Button) findViewById(R.id.btn_trans_pcm_to_wav);
        mBtnGoPlay = (Button) findViewById(R.id.btn_goto_play_music);

        mBtnLeftRight.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                String date = DateUtils.getDate(System.currentTimeMillis(),DateUtils.DATE_FORMAT_1);
                String inputFIle = "sdcard/ff-input/NocturneNo2inEflat_44.1k_s16le.pcm";
                String outputFIleLeft = "sdcard/ff-input/output_left_"+ date +".pcm";
                String outputFIleRight = "sdcard/ff-input/output_right_"+ date +".pcm";
                Log.i(TAG," inputFIle = " + inputFIle);
                Log.i(TAG," outputFIleLeft = " + outputFIleLeft);
                Log.i(TAG," outputFIleRight = " + outputFIleRight);
                dividePcmToLeftRight(inputFIle,outputFIleLeft,outputFIleRight);
            }
        });

        mBtnVolumeHalf.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                String date = DateUtils.getDate(System.currentTimeMillis(),DateUtils.DATE_FORMAT_1);
                String inputFIle = "sdcard/ff-input/NocturneNo2inEflat_44.1k_s16le.pcm";
                String outputFIle = "sdcard/ff-input/output_volume_half_"+ date +".pcm";
                Log.i(TAG," inputFIle = " + inputFIle);
                Log.i(TAG," outputFIle = " + outputFIle);
                makePcmVolumeHalf(inputFIle,outputFIle);
            }
        });

        mBtnSpeedUp.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                String date = DateUtils.getDate(System.currentTimeMillis(),DateUtils.DATE_FORMAT_1);
                String inputFIle = "sdcard/ff-input/NocturneNo2inEflat_44.1k_s16le.pcm";
                String outputFIle = "sdcard/ff-input/output_speed_up_"+ date +".pcm";
                Log.i(TAG," inputFIle = " + inputFIle);
                Log.i(TAG," outputFIle = " + outputFIle);
                makePcmSpeedUp(inputFIle,outputFIle);
            }
        });

        mBtn16To8.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                String date = DateUtils.getDate(System.currentTimeMillis(),DateUtils.DATE_FORMAT_1);
                String inputFIle = "sdcard/ff-input/NocturneNo2inEflat_44.1k_s16le.pcm";
                String outputFIle = "sdcard/ff-input/output_16_8_"+ date +".pcm";
                Log.i(TAG," inputFIle = " + inputFIle);
                Log.i(TAG," outputFIle = " + outputFIle);
                makePcm16ToPcm8(inputFIle,outputFIle);
            }
        });

        mBtnPcmToWav.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {

            }
        });

        mBtnGoPlay.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if(TextUtils.isEmpty(mFilePath)){
                    ToastUtils.showShortToast(TransPCMActivity.this," file path is empty ");
                    return;
                }
                Intent intent = new Intent(TransPCMActivity.this, OpenSLActivity.class);
                startActivity(intent);
            }
        });

        btnChooseFilePath.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(TransPCMActivity.this , FileIndexActivity.class);
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

    public native int dividePcmToLeftRight(String inputPcmPath,String outputLeftPcmPath,String outputRightPcmPath);
    public native int transPcmToAac(String inputFilePath,String outputFilePath);
    public native int makePcmVolumeHalf(String inputFilePath,String outputFilePath);
    public native int makePcmSpeedUp(String inputFilePath,String outputFilePath);
    public native int makePcm16ToPcm8(String inputFilePath,String outputFilePath);
    public native int cutPcm(String inputFilePath,String outputFilePath,int start_num,int dur_num);
    public native int transPcmToWave(String inputFilePath,String outputFilePath);
}
