package com.example.wingbu.ffmpegbasic.utils;

import android.content.Context;
import android.widget.Toast;

/**
 * Created by Wings on 2019/1/6.
 */

public class ToastUtils {

    public static void showShortToast(Context context , String s){
        Toast.makeText(context,s,Toast.LENGTH_SHORT).show();
    }

    public static void showShortToast(Context context , int stringId){
        Toast.makeText(context,stringId,Toast.LENGTH_SHORT).show();
    }

    public static void showLongToast(Context context , String s){
        Toast.makeText(context,s,Toast.LENGTH_LONG).show();
    }

    public static void showLongToast(Context context , int stringId){
        Toast.makeText(context,stringId,Toast.LENGTH_LONG).show();
    }
}
