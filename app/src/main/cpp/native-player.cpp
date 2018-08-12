#include <jni.h>
#include <string>
#include <android/log.h>
#include <android/native_window.h>
#include <android/native_window_jni.h>

extern "C" {
    #include "libavcodec/avcodec.h"
    #include "libavformat/avformat.h"
    #include "libswscale/swscale.h"
}

#define FFLOGI(FORMAT,...) __android_log_print(ANDROID_LOG_INFO,"ffmpeg",FORMAT,##__VA_ARGS__);
#define FFLOGE(FORMAT,...) __android_log_print(ANDROID_LOG_ERROR,"ffmpeg",FORMAT,##__VA_ARGS__);

extern "C"
JNIEXPORT jint JNICALL
Java_com_example_wingbu_ffmpegbasic_play_VideoPlayActivity_play(JNIEnv *env, jclass type, jstring input_,
                                                     jobject surface) {
    const char *videoFile = env->GetStringUTFChars(input_, 0);
    FFLOGI("%s",videoFile);

    av_register_all();


    AVFormatContext *pFormatCtx = avformat_alloc_context();

    if(avformat_open_input(&pFormatCtx,videoFile,NULL,NULL) != 0){
       FFLOGI("Couldn't open file:%s\n",videoFile);
       return -1;
    }

    if(avformat_find_stream_info(pFormatCtx,NULL) > 0){
       FFLOGI("Couldn't find stream information.");
       return -1;
    }

    int videoStream = -1,i;
    for(i = 0 ; i < pFormatCtx -> nb_streams; i++){
       if( pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO && videoStream < 0){
           videoStream = i;
       }
    }

    if (videoStream == -1) {
         FFLOGI("Didn't find a video stream.");
         return -1; // Didn't find a video stream
    }

    AVCodecContext *pCodecContext = pFormatCtx->streams[videoStream]->codec;

    AVCodec *pCodec = avcodec_find_decoder(pCodecContext->codec_id);

    if(pCodec == NULL){
       FFLOGI("codec not found");
       return -1;
    }

    if(avcodec_open2(pCodecContext,pCodec,NULL) < 0){
       FFLOGI("can not open codec");
       return -1;
    }

    ANativeWindow *nativeWindow = ANativeWindow_fromSurface(env,surface);

    int videoWidth = pCodecContext -> width;
    int videoHeight = pCodecContext -> height;

    ANativeWindow_setBuffersGeometry(nativeWindow,videoWidth,videoHeight,WINDOW_FORMAT_RGBA_8888);

    ANativeWindow_Buffer windowBuffer;

    if(avcodec_open2(pCodecContext,pCodec,NULL) < 0){
       FFLOGI("can not open codec ");
       return -1;
    }

    AVFrame *pFrame = av_frame_alloc();

    AVFrame *pFrameRGBA = av_frame_alloc();
    if(pFrameRGBA == NULL || pFrame ==NULL){
       FFLOGI(" can not allocate video frame ");
       return -1;
    }

    int numBytes = av_image_get_buffer_size(AV_PIX_FMT_RGBA,pCodecContext->width,pCodecContext->height,1);
    uint8_t *buffer = (uint8_t *)av_malloc(numBytes * sizeof(uint8_t));
    av_image_fill_arrays(pFrameRGBA->data,pFrameRGBA->linesize,buffer,AV_PIX_FMT_RGBA,
                                          pCodecContext->width,pCodecContext->height,1);

    struct SwsContext *sws_ctx = sws_getContext(pCodecContext->width,pCodecContext->height,
                                                pCodecContext->pix_fmt,
                                                pCodecContext->width,pCodecContext->height,
                                                AV_PIX_FMT_RGBA,SWS_BILINEAR,
                                                NULL,NULL,NULL);

    int frameFinished;
    AVPacket packet;
    while(av_read_frame(pFormatCtx,&packet) >= 0){
        if(packet.stream_index == videoStream){
           avcodec_decode_video2(pCodecContext,pFrame,&frameFinished,&packet);
           if(frameFinished){
              ANativeWindow_lock(nativeWindow,&windowBuffer,0);
              sws_scale(sws_ctx,(uint8_t const *const *)pFrame->data,
                        pFrame->linesize,0,pCodecContext->height,
                        pFrameRGBA->data,pFrameRGBA->linesize);

              uint8_t *dst = (uint8_t *) windowBuffer.bits;
              int dstStride = windowBuffer.stride * 4;
              uint8_t *src = (pFrameRGBA->data[0]);
              int srcStride = pFrameRGBA->linesize[0];

              int h;
              for(h = 0 ; h < videoHeight ; h++){
                 memcpy(dst + h * dstStride , src + h * srcStride , srcStride);
              }

              ANativeWindow_unlockAndPost(nativeWindow);
           }
        }
        av_packet_unref(&packet);
    }
    av_free(buffer);
    av_free(pFrameRGBA);
    av_free(pFrame);

    avcodec_close(pCodecContext);
    avformat_close_input(&pFormatCtx);
    return 0;
}
