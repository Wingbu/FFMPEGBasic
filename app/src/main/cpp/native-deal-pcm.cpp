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

extern "C"
JNIEXPORT jint JNICALL
Java_com_example_wingbu_ffmpegbasic_trans_TransPCMActivity_makePcmVolumeHalf(JNIEnv *env, jclass type,
                                                                         jstring inputFilePath, jstring outputFilePath) {
//    FILE *fp=fopen(url,"rb+");
//    FILE *fp1=fopen("output_halfleft.pcm","wb+");
//
//    int cnt=0;
//
//    unsigned char *sample=(unsigned char *)malloc(4);
//
//    while(!feof(fp)){
//        short *samplenum=NULL;
//        fread(sample,1,4,fp);
//
//        samplenum=(short *)sample;
//        *samplenum=*samplenum/2;
//        //L
//        fwrite(sample,1,2,fp1);
//        //R
//        fwrite(sample+2,1,2,fp1);
//
//        cnt++;
//    }
//    printf("Sample Cnt:%d\n",cnt);
//
//    free(sample);
//    fclose(fp);
//    fclose(fp1);
    return 0;
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_example_wingbu_ffmpegbasic_trans_TransPCMActivity_makePcmSpeedUp(JNIEnv *env, jclass type,
                                                                         jstring inputFilePath, jstring outputFilePath) {
//    FILE *fp=fopen(url,"rb+");
//    FILE *fp1=fopen("output_doublespeed.pcm","wb+");
//
//    int cnt=0;
//
//    unsigned char *sample=(unsigned char *)malloc(4);
//
//    while(!feof(fp)){
//
//        fread(sample,1,4,fp);
//
//        if(cnt%2!=0){
//            //L
//            fwrite(sample,1,2,fp1);
//            //R
//            fwrite(sample+2,1,2,fp1);
//        }
//        cnt++;
//    }
//    printf("Sample Cnt:%d\n",cnt);
//
//    free(sample);
//    fclose(fp);
//    fclose(fp1);

    return 0;
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_example_wingbu_ffmpegbasic_trans_TransPCMActivity_makePcm16ToPcm8(JNIEnv *env, jclass type,
                                                                          jstring inputFilePath, jstring outputFilePath) {
//    FILE *fp=fopen(url,"rb+");
//    FILE *fp1=fopen("output_8.pcm","wb+");
//
//    int cnt=0;
//
//    unsigned char *sample=(unsigned char *)malloc(4);
//
//    while(!feof(fp)){
//
//        short *samplenum16=NULL;
//        char samplenum8=0;
//        unsigned char samplenum8_u=0;
//        fread(sample,1,4,fp);
//        //(-32768-32767)
//        samplenum16=(short *)sample;
//        samplenum8=(*samplenum16)>>8;
//        //(0-255)
//        samplenum8_u=samplenum8+128;
//        //L
//        fwrite(&samplenum8_u,1,1,fp1);
//
//        samplenum16=(short *)(sample+2);
//        samplenum8=(*samplenum16)>>8;
//        samplenum8_u=samplenum8+128;
//        //R
//        fwrite(&samplenum8_u,1,1,fp1);
//        cnt++;
//    }
//    printf("Sample Cnt:%d\n",cnt);
//
//    free(sample);
//    fclose(fp);
//    fclose(fp1);
    return 0;
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_example_wingbu_ffmpegbasic_trans_TransPCMActivity_cutPcm(JNIEnv *env, jclass type,
                                                                          jstring inputFilePath, jstring outputFilePath,
                                                                          jint start_num,jint dur_num) {
//    FILE *fp=fopen(url,"rb+");
//    FILE *fp1=fopen("output_cut.pcm","wb+");
//    FILE *fp_stat=fopen("output_cut.txt","wb+");
//
//    unsigned char *sample=(unsigned char *)malloc(2);
//
//    int cnt=0;
//    while(!feof(fp)){
//        fread(sample,1,2,fp);
//        if(cnt>start_num&&cnt<=(start_num+dur_num)){
//            fwrite(sample,1,2,fp1);
//
//            short samplenum=sample[1];
//            samplenum=samplenum*256;
//            samplenum=samplenum+sample[0];
//
//            fprintf(fp_stat,"%6d,",samplenum);
//            if(cnt%10==0)
//                fprintf(fp_stat,"\n",samplenum);
//        }
//        cnt++;
//    }
//
//    free(sample);
//    fclose(fp);
//    fclose(fp1);
//    fclose(fp_stat);
    return 0;
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_example_wingbu_ffmpegbasic_trans_TransPCMActivity_transPcmToWave(JNIEnv *env, jclass type,
                                                                         jstring inputFilePath, jstring outputFilePath) {
    return 0;
}