package com.example.wingbu.ffmpegbasic.trans;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;

import com.example.wingbu.ffmpegbasic.R;
import com.example.wingbu.ffmpegbasic.file.FileIndexActivity;
import com.example.wingbu.ffmpegbasic.file.FileResultEntity;

public class TransVideoActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_trans_video);
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

        }
    }
}
