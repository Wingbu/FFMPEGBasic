package com.example.wingbu.ffmpegbasic.file;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.view.View;
import android.view.inputmethod.InputMethodSession;
import android.widget.TextView;

import com.example.wingbu.ffmpegbasic.R;
import com.example.wingbu.ffmpegbasic.utils.FilePathUtils;
import com.example.wingbu.ffmpegbasic.utils.FileUtils;

import java.io.File;
import java.util.ArrayList;

public class FileIndexActivity extends AppCompatActivity {

    public static final String TAG = "FileIndexActivity";

    private String filePath = FilePathUtils.BASE_INPUT_PATH;

    private TextView tvIndex;
    private TextView tvUp;

    private RecyclerView rvFile;
    private FileIndexAdapter adapter;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_file_index);

        tvIndex = (TextView) findViewById(R.id.tv_index);
        tvUp = (TextView) findViewById(R.id.tv_up);
        tvUp.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                filePath = FilePathUtils.getUpFilePath(filePath);
                refreshFileList();
            }
        });


        rvFile = (RecyclerView) findViewById(R.id.rv_file);
        refreshFileList();
    }

    private void refreshFileList(){
        if(FilePathUtils.isFileName(filePath)){
            return;
        }
        tvIndex.setText(filePath);
        adapter = new FileIndexAdapter(FileIndexActivity.this,getFileList());
        adapter.setOnFileClickListener(new FileIndexAdapter.OnFileClickListener() {
            @Override
            public void onFileClick(File file) {
                if(FilePathUtils.isFileName(file.getName())){
                    return;
                }
                filePath = file.getAbsolutePath();
                if(!filePath.endsWith("/")){
                    filePath = filePath + "/";
                }

                refreshFileList();
            }
        });
        adapter.setOnFileLongClickListener(new FileIndexAdapter.OnFileLongClickListener() {
            @Override
            public void onFileLongClick(File file) {
                showDeleteDialog(file);
            }
        });
        rvFile.setLayoutManager(new LinearLayoutManager(getApplicationContext()));
        rvFile.setAdapter(adapter);
    }

    private void showDeleteDialog(File file){

    }

    private ArrayList<File> getFileList(){
        if(null == filePath || filePath.length() == 0 ){
            return null;
        }
        ArrayList<File> result = new ArrayList<>();
        File[] files = FileUtils.getFiles(filePath);
        if(null == files || files.length == 0){
            return null;
        }
        for ( File file : files){
            result.add(file);
        }
        return result;
    }
}
