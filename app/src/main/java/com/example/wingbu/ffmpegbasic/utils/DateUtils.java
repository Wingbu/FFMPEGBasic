package com.example.wingbu.ffmpegbasic.utils;

import java.text.SimpleDateFormat;
import java.util.Date;

/**
 * 获取或者处理日期信息
 *
 * Created by Wings on 2019/1/9.
 */

public class DateUtils {

    public static final String DATE_FORMAT_1 = "yyyyMMddhhmmss";

    public static String getDate(long timeStamp , String format){
        Date now = new Date(timeStamp);
        SimpleDateFormat ft = new SimpleDateFormat (format);
        return ft.format(now);
    }
}
