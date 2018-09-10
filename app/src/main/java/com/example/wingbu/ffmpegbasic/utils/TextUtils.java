package com.example.wingbu.ffmpegbasic.utils;

/**
 * Created by Wings on 2018/9/10.
 */

public class TextUtils {

    /**
     * 判断字符串是否为空字符串
     * @param s
     * @return
     */
    public static boolean isEmpty(String s){
        if(null == s || s.length() == 0){
            return true;
        }
        return false;
    }
}
