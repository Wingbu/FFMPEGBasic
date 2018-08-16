package com.example.wingbu.ffmpegbasic;

import android.os.Environment;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

import java.io.File;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tv = (TextView) findViewById(R.id.sample_text);
        tv.setText(stringFromJHello());

        String input = new File("sdcard/ff-input/example.mp4").getAbsolutePath();
        String output = new File("sdcard/ff-input/carphone_qcif.yuv").getAbsolutePath();
        String s = Environment.getExternalStorageDirectory().toString();
        Log.i("Wings", Environment.getExternalStorageDirectory().toString());
//        File file = new File("sdcard/sintel.mp4");
//        boolean is = file.exists();
        decode("sdcard/ff-input/example.mp4", "sdcard/ff-input/carphone_qcif.yuv");
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();
    public native String stringFromJHello();
    public native static void decode(String input,String output);
}
