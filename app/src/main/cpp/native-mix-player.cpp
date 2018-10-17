#include <jni.h>
#include <string>
#include <android/log.h>
#include <android/native_window.h>
#include <android/native_window_jni.h>

extern "C" {
    //编码
    #include "libavcodec/avcodec.h"
    //封装格式处理
    #include "libavformat/avformat.h"
    //像素处理
    #include "libswscale/swscale.h"

    #include "libavutil/imgutils.h"

    #include <unistd.h>
    #include <SLES/OpenSLES.h>
    #include <SLES/OpenSLES_Android.h>
}

#define FFLOGI(FORMAT,...) __android_log_print(ANDROID_LOG_INFO,"ffmpeg",FORMAT,##__VA_ARGS__);
#define FFLOGE(FORMAT,...) __android_log_print(ANDROID_LOG_ERROR,"ffmpeg",FORMAT,##__VA_ARGS__);


const char *filePath;
int64_t *totalTime;
int64_t duration;

AVFormatContext *avFormatContext;



void init(){

   // 1. 注册组件
   av_register_all();
   avformat_network_init();

   // 2. 封装格式上下文
   avFormatContext = avformat_alloc_context();

   // 3.打开视频文件
   if(avformat_open_input(&avFormatContext, filePath, NULL, NULL) != 0) {
       FFLOGI("Couldn't open file:%s\n", filePath);
       return ; // Couldn't open file
   }

   // 4.获取视频信息
   if(avformat_find_stream_info(avFormatContext, NULL) < 0) {
       FFLOGI("Couldn't find stream information.");
       return ;
   }

   // 5. 得到播放总时间
   if(avFormatContext->duration != AV_NOPTS_VALUE) {
      duration = avFormatContext->duration;//微秒
   }

}

extern "C"
JNIEXPORT jint JNICALL
Java_com_example_wingbu_ffmpegbasic_play_MixPlayActivity_play(JNIEnv *env, jclass type, jstring input_,jobject surface) {

    filePath = env->GetStringUTFChars(input_, 0);

    FFLOGI("play");

    init();


        // Find the first video stream
        int videoStream = -1, i;
        for (i = 0; i < pFormatCtx->nb_streams; i++) {
            if (pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO
                && videoStream < 0) {
                videoStream = i;
            }
        }
        if (videoStream == -1) {
            FFLOGI("Didn't find a video stream.");
            return -1; // Didn't find a video stream
        }

        // Get a pointer to the codec context for the video stream
        AVCodecContext *pCodecCtx = pFormatCtx->streams[videoStream]->codec;

        // Find the decoder for the video stream
        AVCodec *pCodec = avcodec_find_decoder(pCodecCtx->codec_id);
        if (pCodec == NULL) {
            FFLOGI("Codec not found.");
            return -1; // Codec not found
        }

        if (avcodec_open2(pCodecCtx, pCodec, NULL) < 0) {
            FFLOGI("Could not open codec.");
            return -1; // Could not open codec
        }

        // 获取native window
        ANativeWindow *nativeWindow = ANativeWindow_fromSurface(env, surface);

        // 获取视频宽高
        int videoWidth = pCodecCtx->width;
        int videoHeight = pCodecCtx->height;

        // 设置native window的buffer大小,可自动拉伸
        ANativeWindow_setBuffersGeometry(nativeWindow, videoWidth, videoHeight,
                                         WINDOW_FORMAT_RGBA_8888);
        ANativeWindow_Buffer windowBuffer;

        if (avcodec_open2(pCodecCtx, pCodec, NULL) < 0) {
            FFLOGI("Could not open codec.");
            return -1; // Could not open codec
        }

        // Allocate video frame
        AVFrame *pFrame = av_frame_alloc();

        // 用于渲染
        AVFrame *pFrameRGBA = av_frame_alloc();
        if (pFrameRGBA == NULL || pFrame == NULL) {
            FFLOGI("Could not allocate video frame.");
            return -1;
        }

        // Determine required buffer size and allocate buffer
        // buffer中数据就是用于渲染的,且格式为RGBA
        int numBytes = av_image_get_buffer_size(AV_PIX_FMT_RGBA, pCodecCtx->width, pCodecCtx->height,
                                                1);
        uint8_t *buffer = (uint8_t *) av_malloc(numBytes * sizeof(uint8_t));
        av_image_fill_arrays(pFrameRGBA->data, pFrameRGBA->linesize, buffer, AV_PIX_FMT_RGBA,
                             pCodecCtx->width, pCodecCtx->height, 1);

        // 由于解码出来的帧格式不是RGBA的,在渲染之前需要进行格式转换
        struct SwsContext *sws_ctx = sws_getContext(pCodecCtx->width,
                                                    pCodecCtx->height,
                                                    pCodecCtx->pix_fmt,
                                                    pCodecCtx->width,
                                                    pCodecCtx->height,
                                                    AV_PIX_FMT_RGBA,
                                                    SWS_BILINEAR,
                                                    NULL,
                                                    NULL,
                                                    NULL);

        int frameFinished;
        AVPacket packet;
        while (av_read_frame(pFormatCtx, &packet) >= 0) {
            // Is this a packet from the video stream?
            if (packet.stream_index == videoStream) {

                // Decode video frame
                avcodec_decode_video2(pCodecCtx, pFrame, &frameFinished, &packet);

                // 并不是decode一次就可解码出一帧
                if (frameFinished) {

                    // lock native window buffer
                    ANativeWindow_lock(nativeWindow, &windowBuffer, 0);

                    // 格式转换
                    sws_scale(sws_ctx, (uint8_t const *const *) pFrame->data,
                              pFrame->linesize, 0, pCodecCtx->height,
                              pFrameRGBA->data, pFrameRGBA->linesize);

                    // 获取stride
                    uint8_t *dst = (uint8_t *) windowBuffer.bits;
                    int dstStride = windowBuffer.stride * 4;
                    uint8_t *src = (pFrameRGBA->data[0]);
                    int srcStride = pFrameRGBA->linesize[0];

                    // 由于window的stride和帧的stride不同,因此需要逐行复制
                    int h;
                    for (h = 0; h < videoHeight; h++) {
                        memcpy(dst + h * dstStride, src + h * srcStride, srcStride);
                    }

                    ANativeWindow_unlockAndPost(nativeWindow);
                }

            }
            av_packet_unref(&packet);
        }

        av_free(buffer);
        av_free(pFrameRGBA);

        // Free the YUV frame
        av_free(pFrame);

        // Close the codecs
        avcodec_close(pCodecCtx);

        // Close the video file
        avformat_close_input(&pFormatCtx);
        return 0;
}
