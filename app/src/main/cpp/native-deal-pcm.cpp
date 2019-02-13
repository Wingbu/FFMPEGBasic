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
Java_com_example_wingbu_ffmpegbasic_trans_TransPCMActivity_dividePcmToLeftRight(JNIEnv *env, jclass type,
                                                                            jstring inputPcmPath, jstring outputLeftPcmPath, jstring outputRightPcmPath) {

    //获取输入输出文件名
    const char *input_path = env->GetStringUTFChars(inputPcmPath, 0);
    const char *output_left_path = env->GetStringUTFChars(outputLeftPcmPath, 0);
    const char *output_right_path = env->GetStringUTFChars(outputRightPcmPath, 0);

    FFLOGI("输入视频文件：%s",input_path);
    FFLOGI("左声道输出视频文件：%s", output_left_path);
    FFLOGI("右声道输出视频文件：%s",output_right_path);

    FILE *input = fopen(input_path,"rb+");
    FILE *output_left = fopen(output_left_path,"wb+");
    FILE *output_right = fopen(output_right_path,"wb+");

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

    //获取输入输出文件名
    const char *input_path = env->GetStringUTFChars(inputFilePath, 0);
    const char *output_path = env->GetStringUTFChars(outputFilePath, 0);

    FFLOGI("输入视频文件：%s",input_path);
    FFLOGI("输出视频文件：%s", output_path);

    FILE *fp=fopen(input_path,"rb+");
    FILE *fp1=fopen(output_path,"wb+");

    int cnt=0;

    unsigned char *sample=(unsigned char *)malloc(4);

    while(!feof(fp)){
        short *samplenum=NULL;
        fread(sample,1,4,fp);

        samplenum=(short *)sample;
        *samplenum=*samplenum/2;
        //L
        fwrite(sample,1,2,fp1);
        //R
        fwrite(sample+2,1,2,fp1);

        cnt++;
    }
    printf("Sample Cnt:%d\n",cnt);

    free(sample);
    fclose(fp);
    fclose(fp1);
    return 0;
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_example_wingbu_ffmpegbasic_trans_TransPCMActivity_makePcmSpeedUp(JNIEnv *env, jclass type,
                                                                         jstring inputFilePath, jstring outputFilePath) {

    //获取输入输出文件名
    const char *input_path = env->GetStringUTFChars(inputFilePath, 0);
    const char *output_path = env->GetStringUTFChars(outputFilePath, 0);

    FFLOGI("输入视频文件：%s",input_path);
    FFLOGI("输出视频文件：%s", output_path);

    FILE *fp=fopen(input_path,"rb+");
    FILE *fp1=fopen(output_path,"wb+");

    int cnt=0;

    unsigned char *sample=(unsigned char *)malloc(4);

    while(!feof(fp)){

        fread(sample,1,4,fp);

        if(cnt%2!=0){
            //L
            fwrite(sample,1,2,fp1);
            //R
            fwrite(sample+2,1,2,fp1);
        }
        cnt++;
    }
    printf("Sample Cnt:%d\n",cnt);

    free(sample);
    fclose(fp);
    fclose(fp1);

    return 0;
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_example_wingbu_ffmpegbasic_trans_TransPCMActivity_makePcm16ToPcm8(JNIEnv *env, jclass type,
                                                                          jstring inputFilePath, jstring outputFilePath) {
    //获取输入输出文件名
    const char *input_path = env->GetStringUTFChars(inputFilePath, 0);
    const char *output_path = env->GetStringUTFChars(outputFilePath, 0);

    FFLOGI("输入视频文件：%s",input_path);
    FFLOGI("输出视频文件：%s", output_path);

    FILE *fp=fopen(input_path,"rb+");
    FILE *fp1=fopen(output_path,"wb+");

    int cnt=0;

    unsigned char *sample=(unsigned char *)malloc(4);

    while(!feof(fp)){

        short *samplenum16=NULL;
        char samplenum8=0;
        unsigned char samplenum8_u=0;
        fread(sample,1,4,fp);
        //(-32768-32767)
        samplenum16=(short *)sample;
        samplenum8=(*samplenum16)>>8;
        //(0-255)
        samplenum8_u=samplenum8+128;
        //L
        fwrite(&samplenum8_u,1,1,fp1);

        samplenum16=(short *)(sample+2);
        samplenum8=(*samplenum16)>>8;
        samplenum8_u=samplenum8+128;
        //R
        fwrite(&samplenum8_u,1,1,fp1);
        cnt++;
    }
    printf("Sample Cnt:%d\n",cnt);

    free(sample);
    fclose(fp);
    fclose(fp1);
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
                                                                         jstring inputFilePath, jint channels,jint sample_rate, jstring outputFilePath ) {
    typedef struct WAVE_HEADER{
        char               fccID[4];    //文档标识：大写字符串"RIFF",标明该文件为有效的 RIFF 格式文档
        unsigned   long    dwSize;      //文件数据长度：从下一个字段首地址开始到文件末尾的总字节数。该字段的数值加 8 为当前文件的实际长度。
        char               fccType[4];  //文件格式类型：所有 WAV 格式的文件此处为字符串"WAVE",标明该文件是 WAV 格式文件。
    }WAVE_HEADER;

    typedef struct WAVE_FMT{
        char                 fccID[4];          //格式块标识：小写字符串,"fmt "。注意帶上空格
        unsigned   long      dwSize;            //格式块长度：其数值不确定,取决于编码格式。可以是 16、 18 、20、40 等，指的是本块剩余字节数
        unsigned   short     wFormatTag;        //编码格式代码：常见的 WAV 文件使用 PCM 脉冲编码调制格式,该数值通常为 1。
        unsigned   short     wChannels;         //声道个数：单声道为 1,立体声或双声道为 2
        unsigned   long      dwSamplesPerSec;   //采样频率：每个声道单位时间采样次数。常用的采样频率有 11025, 22050 和 44100 kHz。
        unsigned   long      dwAvgBytesPerSec;  //数据传输速率：该数值为 声道数×采样频率×每样本的数据位数/8。播放软件利用此值可以估计缓冲区的大小。
        unsigned   short     wBlockAlign;       //数据块对齐单位：采样帧大小。该数值为:声道数×位数/8。播放软件需要一次处理多个该值大小的字节数据,用该数值调整缓冲区。
        unsigned   short     uiBitsPerSample;   //采样位数：存储每个采样值所用的二进制数位数。常见的位数有 4、8、12、16、24、32
    }WAVE_FMT;

    typedef struct WAVE_DATA{
        char          fccID[4];      //块标识，小写字符串,"data"
        unsigned long dwSize;        //块长度
    }WAVE_DATA;

    if(channels==0||sample_rate==0){
        channels = 2;
        sample_rate = 44100;
    }
    int bits = 16;

    WAVE_HEADER   pcmHEADER;
    WAVE_FMT   pcmFMT;
    WAVE_DATA   pcmDATA;

    unsigned   short   m_pcmData;
    FILE   *fp,*fpout;

    //获取输入输出文件名
    const char *input_path = env->GetStringUTFChars(inputFilePath, 0);
    const char *output_path = env->GetStringUTFChars(outputFilePath, 0);

    fp=fopen(input_path, "rb");
    if(fp == NULL) {
        printf("open pcm file error\n");
        return -1;
    }
    fpout=fopen(output_path, "wb+");
    if(fpout == NULL) {
        printf("create wav file error\n");
        return -1;
    }

    //WAVE_HEADER
    memcpy(pcmHEADER.fccID,"RIFF",strlen("RIFF"));
    memcpy(pcmHEADER.fccType,"WAVE",strlen("WAVE"));
    fseek(fpout,sizeof(WAVE_HEADER),1);
    //WAVE_FMT
    pcmFMT.dwSamplesPerSec=sample_rate;
    pcmFMT.dwAvgBytesPerSec=pcmFMT.dwSamplesPerSec*sizeof(m_pcmData);
    pcmFMT.uiBitsPerSample=bits;
    memcpy(pcmFMT.fccID,"fmt ",strlen("fmt "));
    pcmFMT.dwSize=16;
    pcmFMT.wBlockAlign=2;
    pcmFMT.wChannels=channels;
    pcmFMT.wFormatTag=1;

    fwrite(&pcmFMT,sizeof(WAVE_FMT),1,fpout);

    //WAVE_DATA;
    memcpy(pcmDATA.fccID,"data",strlen("data"));
    pcmDATA.dwSize=0;
    fseek(fpout,sizeof(WAVE_DATA),SEEK_CUR);

    fread(&m_pcmData,sizeof(unsigned short),1,fp);
    while(!feof(fp)){
        pcmDATA.dwSize+=2;
        fwrite(&m_pcmData,sizeof(unsigned short),1,fpout);
        fread(&m_pcmData,sizeof(unsigned short),1,fp);
    }

    pcmHEADER.dwSize=44+pcmDATA.dwSize;

    rewind(fpout);
    fwrite(&pcmHEADER,sizeof(WAVE_HEADER),1,fpout);
    fseek(fpout,sizeof(WAVE_FMT),SEEK_CUR);
    fwrite(&pcmDATA,sizeof(WAVE_DATA),1,fpout);

    fclose(fp);
    fclose(fpout);

    return 0;
}