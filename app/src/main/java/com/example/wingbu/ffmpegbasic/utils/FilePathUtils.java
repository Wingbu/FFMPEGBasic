package com.example.wingbu.ffmpegbasic.utils;

/**
 * Created by Wings on 2018/7/25.
 */

public class FilePathUtils {

    public static final String TAG = "FilePathUtils";

    public static final String BASE_PATH = "sdcard/";
    public static final String OUTPUT_PATH = "ff-output";
    public static final String INPUT_PATH = "ff-input";
    public static final String BASE_INPUT_PATH = "sdcard/ff-input/";
    public static final String BASE_OUTPUT_PATH = "sdcard/ff-output/";

    /**
     * 只查看sdcard/目录下的文件，认为sdcard/为根目录，当仅有一个"/"的时候，为根目录
     * @param filePath
     * @return
     */
    public static boolean isFinalFilePath(String filePath){
        if(null == filePath || filePath.length() == 0){
            return false;
        }
        if(filePath.indexOf("/") == filePath.lastIndexOf("/") && filePath.endsWith("/")){
            return true;
        }
        return false;
    }

    /**
     * 拼接成一个新的文件夹路径
     * @param path
     * @param folderName
     * @return
     */
    public static String combineFilePath(String path , String folderName){
        if(!path.endsWith("/")){
            path = path + "/";
        }
        if(folderName.indexOf(".") != -1){
            return path;
        }
        StringBuilder stringBuilder = new StringBuilder().append(path).append(folderName).append("/");
        return stringBuilder.toString();
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
     * 获取上一级文件目录
     * @param filePath
     * @return
     */
    public static String getUpFilePath(String filePath){
        if(null == filePath || filePath.length() == 0){
            return filePath;
        }
        if(filePath.indexOf("/") != filePath.lastIndexOf("/")){
            if(filePath.endsWith("/")){
                filePath = filePath.substring(0,filePath.length());
            }
            int subPosition = filePath.lastIndexOf("/");
            String result = filePath.substring(0,subPosition);
            return result;
        }
        return filePath;
    }
}
