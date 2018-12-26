package com.example.wingbu.ffmpegbasic.trans;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.Button;
import android.widget.TextView;

import com.example.wingbu.ffmpegbasic.R;

public class TransPCMActivity extends AppCompatActivity {

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
        setContentView(R.layout.activity_trans_pcm);
    }

    public native int devidePcmToLeftRight(String inputPcmPath,String outputLeftPcmPath,String outputRightPcmPath);
    public native int transPcmToAac(String inputFilePath,String outputFilePath);
}
