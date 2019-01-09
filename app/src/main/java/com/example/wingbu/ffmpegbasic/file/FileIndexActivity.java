package com.example.wingbu.ffmpegbasic.file;

import android.app.Activity;
import android.app.AlertDialog;
import android.app.Dialog;
import android.content.DialogInterface;
import android.content.Intent;
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
import com.example.wingbu.ffmpegbasic.utils.ToastUtils;

import java.io.File;
import java.util.ArrayList;

/**
 * 文件选择页
 *    用于本demo使用时选择对应的音频视频文件
 */
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
                    setOnActivityResult(file);
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

    private void setOnActivityResult(File file){
        //参数校验
        if( null == file){
            ToastUtils.showShortToast(FileIndexActivity.this,"未选择文件");
            return;
        }

        //返回结果
        Intent resultIntent = new Intent();
        resultIntent.putExtra(FileResultEntity.RESULT_TAG,file.getAbsolutePath());
        setResult(FileResultEntity.RESULT_CODE_SUCCESS,resultIntent);
        finish();
    }

    private void showDeleteDialog(final File file){
        //参数校验
        if( null == file){
            ToastUtils.showShortToast(FileIndexActivity.this,"未选择文件");
            return;
        }

        AlertDialog.Builder builder = new AlertDialog.Builder(FileIndexActivity.this);
        builder.setMessage("是否删除"+file.getName());
        builder.setPositiveButton("确定", new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialog, int which) {
                boolean isDelete = file.delete();
                if(isDelete){
                    ToastUtils.showShortToast(FileIndexActivity.this,"删除成功");
                    refreshFileList();
                }else {
                    ToastUtils.showShortToast(FileIndexActivity.this,"删除失败");
                }
                dialog.dismiss();
                refreshFileList();
            }
        });
        builder.setNegativeButton("取消", new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialog, int which) {
                dialog.dismiss();
            }
        });
        builder.show();
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

    /**
     * 进入文件选择页，获取对应视频文件路径，result返回文件路径
     * @param activity   启动页的activity
     */
    public void startActivityToFindFilePath(Activity activity){
        Intent intent = new Intent(activity , FileIndexActivity.class);
        startActivityForResult(intent, FileResultEntity.REQUEST_CODE);
    }
}
