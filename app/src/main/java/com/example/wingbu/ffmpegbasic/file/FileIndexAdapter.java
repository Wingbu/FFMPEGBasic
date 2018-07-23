package com.example.wingbu.ffmpegbasic.file;

import android.content.Context;
import android.support.v7.widget.RecyclerView;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import com.example.wingbu.ffmpegbasic.R;

import java.io.File;
import java.util.ArrayList;

/**
 * Created by Wings on 2018/7/23.
 */

public class FileIndexAdapter extends RecyclerView.Adapter<FileIndexAdapter.FileIndexViewHolder>{

    private ArrayList<File> fileArrayList;
    private Context mContext;

    public FileIndexAdapter(Context context,ArrayList<File> list) {
        this.fileArrayList = list;
        this.mContext = context;
    }

    @Override
    public FileIndexViewHolder onCreateViewHolder(ViewGroup parent, int viewType) {
        FileIndexViewHolder holder = new FileIndexViewHolder(LayoutInflater.from(mContext).inflate(R.layout.item_file_index, parent, false));
        return holder;
    }

    @Override
    public void onBindViewHolder(FileIndexViewHolder holder, int position) {
        File file = fileArrayList.get(position);
        holder.tvFileName.setText(file.getName());
    }

    @Override
    public int getItemCount() {
        if(null == fileArrayList){
            return 0;
        }
        return fileArrayList.size();
    }

    public class FileIndexViewHolder extends RecyclerView.ViewHolder{

        public TextView tvFileName;

        public FileIndexViewHolder(View itemView) {
            super(itemView);
            tvFileName = itemView.findViewById(R.id.tv_file_name);
        }
    }
}
