package com.example.wingbu.ffmpegbasic.file;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.support.v7.widget.RecyclerView;

import com.example.wingbu.ffmpegbasic.R;

public class FileIndexActivity extends AppCompatActivity {

    public static final String TAG = "FileIndexActivity";

    private RecyclerView rvFile;
    private FileIndexAdapter adapter;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_file_index);

        rvFile = (RecyclerView) findViewById(R.id.rv_file);

    }
}
