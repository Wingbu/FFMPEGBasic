#include <stdio.h>
#include <jni.h>
#include <android/log.h>

extern "C"{
//编码
#include "libavcodec/avcodec.h"
//封装格式处理
#include "libavformat/avformat.h"
};

#define FFLOGI(FORMAT,...) __android_log_print(ANDROID_LOG_INFO,"ffmpeg",FORMAT,##__VA_ARGS__);
#define FFLOGE(FORMAT,...) __android_log_print(ANDROID_LOG_ERROR,"ffmpeg",FORMAT,##__VA_ARGS__);

extern "C"
JNIEXPORT jint JNICALL
Java_com_example_wingbu_ffmpegbasic_trans_TransPCMActivity_devidePcmToLeftRight(JNIEnv *env, jclass type,
                                                                            jstring inputPcmPath, jstring outputLeftPcmPath, jstring outputRightPcmPath) {
    FILE *input = fopen("","rb+");
    FILE *output_left = fopen("","wb+");
    FILE *output_right = fopen("","wb+");

    unsigned char *sample = (unsigned char*)malloc(4);

    while(!feof(input)){
        fread(sample,1,4,input);
        //left
        fwrite(sample,1,2,output_left);
        //right
        fwrite(sample+2,1,2,output_right);
    }

    free(input);

    fclose(input);
    fclose(output_left);
    fclose(output_right);

    return 0;
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_example_wingbu_ffmpegbasic_trans_TransPCMActivity_transPcmToAac(JNIEnv *env, jclass type,
                                                                            jstring inputFilePath, jstring outputFilePath) {
    return 0;
}