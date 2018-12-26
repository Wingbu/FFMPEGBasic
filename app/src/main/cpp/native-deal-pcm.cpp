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
Java_com_example_wingbu_ffmpegbasic_trans_TransVideoActivity_transYuvToJpeg(JNIEnv *env, jclass type,
                                                                            jstring inputFilePath, jstring outputFilePath) {
    AVFormatContext* pFormatCtx;
    AVOutputFormat* fmt;
    AVStream* video_st;
    AVCodecContext* pCodecCtx;
    AVCodec* pCodec;

    uint8_t* picture_buf;
    AVFrame* picture;
    AVPacket pkt;
    int y_size;
    int got_picture=0;
    int size;

    int ret=0;

    FILE *in_file = NULL;                            //YUV source
    int in_w=480,in_h=272;                           //YUV's width and height
    //const char* input_file = env->GetStringUTFChars(inputFilePath, 0);    //Input file
    const char* out_file = "";    //Output file

    in_file = fopen("", "rb");

    av_register_all();

    pFormatCtx = avformat_alloc_context();
    fmt = av_guess_format("mjepg",NULL,NULL);
    pFormatCtx->oformat = fmt;

    if(avio_open(&pFormatCtx->pb,out_file,AVIO_FLAG_READ_WRITE) < 0){
        FFLOGE("%s","Couldn't open output file.");
        return -1;
    }

    video_st = avformat_new_stream(pFormatCtx,0);
    if(video_st == NULL){
        FFLOGE("%s"," video_st == NULL.");
        return -1;
    }

    pCodecCtx = video_st->codec;
    pCodecCtx->codec_id = fmt->video_codec;
    pCodecCtx->codec_type = AVMEDIA_TYPE_VIDEO;
    pCodecCtx->pix_fmt = AV_PIX_FMT_YUV420P;

    pCodecCtx->width = in_w;
    pCodecCtx->height = in_h;

    pCodecCtx->time_base.num = 1;
    pCodecCtx->time_base.den = 25;

    av_dump_format(pFormatCtx,0,out_file,1);

    pCodec = avcodec_find_encoder(pCodecCtx->codec_id);

    if(!pCodec){
        FFLOGE("%s"," pCodec == NULL.");
        return -1;
    }

    if(avcodec_open2(pCodecCtx,pCodec,NULL) < 0){
        FFLOGE("%s"," Could not open codec.");
        return -1;
    }

    picture = av_frame_alloc();
    size = avpicture_get_size(pCodecCtx->pix_fmt,pCodecCtx->width,pCodecCtx->height);
    picture_buf = (uint8_t *)av_malloc(size);
    if(!picture_buf){
        FFLOGE("%s"," picture_buf == null");
        return -1;
    }

    avpicture_fill((AVPicture *)picture, picture_buf, pCodecCtx->pix_fmt, pCodecCtx->width, pCodecCtx->height);

    avformat_write_header(pFormatCtx,NULL);

    y_size = pCodecCtx->width * pCodecCtx->height;
    av_new_packet(&pkt,y_size*3);

    if (fread(picture_buf, 1, y_size*3/2, in_file) <= 0) {
        FFLOGE("%s"," Could not read input file.");
        return -1;
    }

    picture->data[0] = picture_buf;              // Y
    picture->data[1] = picture_buf+ y_size;      // U
    picture->data[2] = picture_buf+ y_size*5/4;  // V

    //Encode
    ret = avcodec_encode_video2(pCodecCtx, &pkt,picture, &got_picture);
    if(ret < 0){
        printf("Encode Error.\n");
        return -1;
    }
    if (got_picture==1){
        pkt.stream_index = video_st->index;
        ret = av_write_frame(pFormatCtx, &pkt);
    }

    av_free_packet(&pkt);
    //Write Trailer
    av_write_trailer(pFormatCtx);

    printf("Encode Successful.\n");

    if (video_st){
        avcodec_close(video_st->codec);
        av_free(picture);
        av_free(picture_buf);
    }
    avio_close(pFormatCtx->pb);
    avformat_free_context(pFormatCtx);

    fclose(in_file);

    return 0;
}

int flush_encoder(AVFormatContext *fmt_ctx,unsigned int stream_index){
    int ret;
    int got_frame;
    AVPacket enc_pkt;
    if (!(fmt_ctx->streams[stream_index]->codec->codec->capabilities &
          CODEC_CAP_DELAY))
        return 0;
    while (1) {
        enc_pkt.data = NULL;
        enc_pkt.size = 0;
        av_init_packet(&enc_pkt);
        ret = avcodec_encode_audio2 (fmt_ctx->streams[stream_index]->codec, &enc_pkt,
                                     NULL, &got_frame);
        av_frame_free(NULL);
        if (ret < 0)
            break;
        if (!got_frame){
            ret=0;
            break;
        }
        printf("Flush Encoder: Succeed to encode 1 frame!\tsize:%5d\n",enc_pkt.size);
        /* mux encoded frame */
        ret = av_write_frame(fmt_ctx, &enc_pkt);
        if (ret < 0)
            break;
    }
    return ret;
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_example_wingbu_ffmpegbasic_trans_TransVideoActivity_transPcmToAac(JNIEnv *env, jclass type,
                                                                            jstring inputFilePath, jstring outputFilePath) {
    AVFormatContext* pFormatCtx;
    AVOutputFormat* fmt;
    AVStream* audio_st;
    AVCodecContext* pCodecCtx;
    AVCodec* pCodec;

    uint8_t* frame_buf;
    AVFrame* pFrame;
    AVPacket pkt;

    int got_frame=0;
    int ret=0;
    int size=0;

    FILE *in_file=NULL;	                        //Raw PCM data
    int framenum=1000;                          //Audio frame number
    const char* out_file = "tdjm.aac";          //Output URL
    int i;

    in_file= fopen("tdjm.pcm", "rb");

    av_register_all();

    //Method 1.
    pFormatCtx = avformat_alloc_context();
    fmt = av_guess_format(NULL, out_file, NULL);
    pFormatCtx->oformat = fmt;

    //Open output URL
    if (avio_open(&pFormatCtx->pb,out_file, AVIO_FLAG_READ_WRITE) < 0){
        printf("Failed to open output file!\n");
        return -1;
    }

    audio_st = avformat_new_stream(pFormatCtx, 0);
    if (audio_st==NULL){
        return -1;
    }
    pCodecCtx = audio_st->codec;
    pCodecCtx->codec_id = fmt->audio_codec;
    pCodecCtx->codec_type = AVMEDIA_TYPE_AUDIO;
    pCodecCtx->sample_fmt = AV_SAMPLE_FMT_S16;
    pCodecCtx->sample_rate= 44100;
    pCodecCtx->channel_layout=AV_CH_LAYOUT_STEREO;
    pCodecCtx->channels = av_get_channel_layout_nb_channels(pCodecCtx->channel_layout);
    pCodecCtx->bit_rate = 64000;

    //Show some information
    av_dump_format(pFormatCtx, 0, out_file, 1);

    pCodec = avcodec_find_encoder(pCodecCtx->codec_id);
    if (!pCodec){
        printf("Can not find encoder!\n");
        return -1;
    }
    if (avcodec_open2(pCodecCtx, pCodec,NULL) < 0){
        printf("Failed to open encoder!\n");
        return -1;
    }
    pFrame = av_frame_alloc();
    pFrame->nb_samples= pCodecCtx->frame_size;
    pFrame->format= pCodecCtx->sample_fmt;

    size = av_samples_get_buffer_size(NULL, pCodecCtx->channels,pCodecCtx->frame_size,pCodecCtx->sample_fmt, 1);
    frame_buf = (uint8_t *)av_malloc(size);
    avcodec_fill_audio_frame(pFrame, pCodecCtx->channels, pCodecCtx->sample_fmt,(const uint8_t*)frame_buf, size, 1);

    //Write Header
    avformat_write_header(pFormatCtx,NULL);

    av_new_packet(&pkt,size);

    for (i=0; i<framenum; i++){
        //Read PCM
        if (fread(frame_buf, 1, size, in_file) <= 0){
            printf("Failed to read raw data! \n");
            return -1;
        }else if(feof(in_file)){
            break;
        }
        pFrame->data[0] = frame_buf;  //PCM Data

        pFrame->pts=i*100;
        got_frame=0;
        //Encode
        ret = avcodec_encode_audio2(pCodecCtx, &pkt,pFrame, &got_frame);
        if(ret < 0){
            printf("Failed to encode!\n");
            return -1;
        }
        if (got_frame==1){
            printf("Succeed to encode 1 frame! \tsize:%5d\n",pkt.size);
            pkt.stream_index = audio_st->index;
            ret = av_write_frame(pFormatCtx, &pkt);
            av_free_packet(&pkt);
        }
    }

    //Flush Encoder
    ret = flush_encoder(pFormatCtx,0);
    if (ret < 0) {
        printf("Flushing encoder failed\n");
        return -1;
    }

    //Write Trailer
    av_write_trailer(pFormatCtx);

    //Clean
    if (audio_st){
        avcodec_close(audio_st->codec);
        av_free(pFrame);
        av_free(frame_buf);
    }
    avio_close(pFormatCtx->pb);
    avformat_free_context(pFormatCtx);

    fclose(in_file);

    return 0;

}