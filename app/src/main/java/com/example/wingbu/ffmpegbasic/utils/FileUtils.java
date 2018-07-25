package com.example.wingbu.ffmpegbasic.utils;

import android.util.Log;

import java.io.File;
import java.io.IOException;

/**
 * 本地文件管理
 *
 * Created by Wings on 2018/7/21.
 */

public class FileUtils {

    public static final String TAG = "FileUtils";

    public static final String BASE_PATH = "sdcard/";
    public static final String OUTPUT_PATH = "ff-output";
    public static final String INPUT_PATH = "ff-input";
    public static final String BASE_INPUT_PATH = "sdcard/ff-input/";
    public static final String BASE_OUTPUT_PATH = "sdcard/ff-output/";

    /**
     * 创建文件或文件夹
     *
     * @param path       文件名路径
     * @param fileName   文件名或问文件夹名
     *
     */
    public static void createFile(String path,String fileName) {
        File file = new File(path + fileName);
        if (fileName.indexOf(".") != -1) {
            // 说明包含，即使创建文件, 返回值为-1就说明不包含.,即使文件
            try {
                file.createNewFile();
            } catch (IOException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
                Log.i(TAG,"  " + e.getMessage());
            }
            Log.i(TAG,"创建了文件");
        } else {
            // 创建文件夹
            file.mkdir();
            Log.i(TAG,"创建了文件夹");
        }

    }

    /**
     * 获取路径下的所有文件
     * @param path
     * @return
     */
    public static File[] getFiles(String path){
        File file=new File(path);
        if(!file.exists()){
            return null;
        }
        File[] files=file.listFiles();
        return files;
    }

    /**
     * 判断该文件是否存在
     * @param path
     * @param fileName
     * @return
     */
    public static boolean isFileExit(String path,String fileName){
        File outputPath = new File(path + fileName);
        if(outputPath.exists()){
            return true;
        }
        return false;
    }

    /**
     * 根据文件名判断是文件还是文件夹，文件返回true，文件夹返回false
     * @param fileName
     * @return
     */
    public static boolean isFileName(String fileName){
        if(null == fileName || fileName.length() == 0){
            return false;
        }
        if(fileName.indexOf(".") != -1){
            return true;
        }
        return false;
    }

    /**
     * 删除文件 如果是文件夹则循环删除
     * @param path
     * @param fileName
     */
    public static void deleteFile(String path,String fileName){
        File file = new File(path + fileName);
        if(file.exists()){
            if(fileName.indexOf(".") != -1){
                file.delete();
            }else {
                File[] files = getFiles(path+fileName);
                for (File file1 : files){
                    deleteFile(path+fileName+"/",file1.getName());
                }
                file.delete();
            }
        }else {
            Log.i(TAG," deleteFile()   file not exit ");
        }
    }
}
