#include<jni.h>
#include<android/log.h>

#include<SLES/OpenSLES.h>
#include<SLES/OpenSLES_Android.h>

#include<sys/types.h>
#include<android/asset_manager.h>
#include<android/asset_manager_jni.h>

#include<stdio.h>
#include<malloc.h>

#define LOGI(FORMAT,...) __android_log_print(ANDROID_LOG_INFO ,"open-sl",FORMAT,##__VA_VRGS__);
#define LOGE(FORMAT,...) __android_log_print(ANDROID_LOG_ERROR,"open-sl",FORMAT,##__VA_VRGS__);


//引擎接口
SLObjectItf engineObject = NULL;
SLEngineItf engineEngine = NULL;

//混音器
SLObjectItf outputMixObject = NULL;
SLEnvironmentalReverbItf outputMixEnvironmentalReverb = NULL;
SLEnvironmentalReverbSettings reverbSettings = SL_I3DL2_ENVIRONMENT_PRESET_STONECORRIDOR;

//assets 播放器
SLObjectItf fdPlayerObject = NULL;
SLPlayerItf fdPlayerPlayer = NULL;
SLVolumeItf fdPlayerVolume = NULL; //声音控制接口

//uri 播放器
SLObjectItf uriPlayerObject = NULL;
SLPlayerItf uriPlayerPlay = NULL;
SLVolumeItf uriPlayerVolume = NULL;


void release();

void createEngine()
{
    SLresult result;
    result = slCreateEngine(&engineObject, 0, NULL, 0, NULL, NULL);
    result = (*engineObject)->Realize(engineObject, SL_BOOLEAN_FALSE);
    result = (*engineObject)->GetInterface(engineObject, SL_IID_ENGINE, &engineEngine);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_wingbu_ffmpegbasic_opensl_OpenSLActivity_playAsset(JNIEnv* env,jobject instance,jobject assetManager,jstring filename) {

    release();
    const char *utf8 = env->GetStringUTFChars(filename, NULL);

    // use asset manager to open asset by filename
    AAssetManager* mgr = AAssetManager_fromJava(env, assetManager);
    AAsset* asset = AAssetManager_open(mgr, utf8, AASSET_MODE_UNKNOWN);
    env->ReleaseStringUTFChars(filename, utf8);

    // open asset as file descriptor
    off_t start, length;
    int fd = AAsset_openFileDescriptor(asset, &start, &length);
    AAsset_close(asset);

    SLresult result;


    //第一步，创建引擎
    createEngine();

    //第二步，创建混音器
    const SLInterfaceID mids[1] = {SL_IID_ENVIRONMENTALREVERB};
    const SLboolean mreq[1] = {SL_BOOLEAN_FALSE};
    result = (*engineEngine)->CreateOutputMix(engineEngine, &outputMixObject, 1, mids, mreq);
    (void)result;
    result = (*outputMixObject)->Realize(outputMixObject, SL_BOOLEAN_FALSE);
    (void)result;
    result = (*outputMixObject)->GetInterface(outputMixObject, SL_IID_ENVIRONMENTALREVERB, &outputMixEnvironmentalReverb);
    if (SL_RESULT_SUCCESS == result) {
          result = (*outputMixEnvironmentalReverb)->SetEnvironmentalReverbProperties(outputMixEnvironmentalReverb, &reverbSettings);
          (void)result;
    }
    //第三步，设置播放器参数和创建播放器
    // 1、 配置 audio source
    SLDataLocator_AndroidFD loc_fd = {SL_DATALOCATOR_ANDROIDFD, fd, start, length};
    SLDataFormat_MIME format_mime = {SL_DATAFORMAT_MIME, NULL, SL_CONTAINERTYPE_UNSPECIFIED};
    SLDataSource audioSrc = {&loc_fd, &format_mime};

    // 2、 配置 audio sink
    SLDataLocator_OutputMix loc_outmix = {SL_DATALOCATOR_OUTPUTMIX, outputMixObject};
    SLDataSink audioSnk = {&loc_outmix, NULL};

    // 创建播放器
    const SLInterfaceID ids[3] = {SL_IID_SEEK, SL_IID_MUTESOLO, SL_IID_VOLUME};
    const SLboolean req[3] = {SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE};
    result = (*engineEngine)->CreateAudioPlayer(engineEngine, &fdPlayerObject, &audioSrc, &audioSnk, 3, ids, req);
    (void)result;

    // 实现播放器
    result = (*fdPlayerObject)->Realize(fdPlayerObject, SL_BOOLEAN_FALSE);
    (void)result;

    // 得到播放器接口
    result = (*fdPlayerObject)->GetInterface(fdPlayerObject, SL_IID_PLAY, &fdPlayerPlay);
    (void)result;

     // 得到声音控制接口
     result = (*fdPlayerObject)->GetInterface(fdPlayerObject, SL_IID_VOLUME, &fdPlayerVolume);
     (void)result;

    // 设置播放状态
    if (NULL != fdPlayerPlay) {
         result = (*fdPlayerPlay)->SetPlayState(fdPlayerPlay, SL_PLAYSTATE_PLAYING);
         (void)result;
     }

     //设置播放音量 （100 * -50：静音 ）
     (*fdPlayerVolume)->SetVolumeLevel(fdPlayerVolume, 20 * -50);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_wingbu_ffmpegbasic_opensl_OpenSLActivity_playUri(JNIEnv* env,jobject instance,jstring uri) {
    Slresult result;
    release();

    const char* utf8 = env->GetStringUTFChars(uri,NULL);

    //第一步：创建引擎
    createEngine();

    //第二步：创建混音器
    const SLInterfaceID mids[1] = {SL_IID_ENVIRONMENTALREVERB};
    const SLboolean mreq[1] = {SL_BOOLEAN_FALSE};
    result = (*engineEngine)->CreateOutputMix(engineEngine,&outputMixObject,1,mids,mreq);
    (void)result;
    result = (*outputMixObject)->Realize(outputMixObject,SL_BOOLEAN_FALSE);
    (void)result;
    result = (*outputMixObject)->GetInterface(outputMixObject,SL_IID_ENVIRONMENTALREVERB,&outputMixEnvironmentalReverb);
    if(SL_RESULT_SUCCESS == result){
        result = (*outputMixEnvironmentalReverb)->SetEnvironmentalReverbProperties(outputMixEnvironmentalReverb,&reverbSettings);
        (void)result;
    }

    //第三步：设置播放器参数和创建播放器
    // configure audio source
    // (requires the INTERNET permission depending on the uri parameter)
    SLDataLocator_URI loc_uri = {SL_DATALOCATOR_URI,(SLChar *)utf8};
    SL_DATAFORMAT_MIME format_mime = {SL_DATAFORMAT_MIME, NULL ,SL_CONTAINERTYPE_UNSPECIFIED};
    SLDataSource audioSrc = {&loc_uri,&format_mime};

    //configure audio sink
    SL_DATALOCATOR_OUTPUTMIX loc_outmix = {SL_DATALOCATOR_OUTPUTMIX,outputMixObject};
    SLDataSink audioSnk = {&loc_outmix,NULL};

    //create audio player
    const SLInterfaceID ids[3] = {SL_IID_SEEK,SL_IID_MUTESOLO,SL_IID_VOLUME};
    const SLboolean req[3] = {SL_BOOLEAN_TRUE,SL_BOOLEAN_TRUE,SL_BOOLEAN_TRUE}
    result = (*engineEngine)->CreateAudioPlayer(engineEngine,&uriPlayerObject,&audioSrc,&audioSnk,3,ids,req);

    (void)result;

    //release the java string and utf8
    env->ReleaseStringUTFChars(uri,utf8);

    //realize the player
    result = （*uriPlayerObject)->Realize(uriPlayerObject,SL_BOOLEAN_FALSE);
    // this will always succeed on Android, but we check result for portability to other platforms
    if (SL_RESULT_SUCCESS != result) {
        (*uriPlayerObject)->Destroy(uriPlayerObject);
        uriPlayerObject = NULL;
        return;
    }

    //get the play interface
    result = (*uriPlayerObject)->GetInterface(uriPlayerObject,SL_IID_PLAY,&uriPlayerPlay);
    (void)result;

    // get the volume interface
    result = (*uriPlayerObject)->GetInterface(uriPlayerObject, SL_IID_VOLUME, &uriPlayerVolume);
    (void)result;

    if (NULL != uriPlayerPlay) {
        // set the player's state
        result = (*uriPlayerPlay)->SetPlayState(uriPlayerPlay, SL_PLAYSTATE_PLAYING);
        (void)result;
    }

    //设置播放音量 （100 * -50：静音 ）
    //    (*uriPlayerVolume)->SetVolumeLevel(uriPlayerVolume, 0 * -50);
}

void release()
{

    if (pcmPlayerObject != NULL) {
        (*pcmPlayerObject)->Destroy(pcmPlayerObject);
        pcmPlayerObject = NULL;
        pcmPlayerPlay = NULL;
        pcmPlayerVolume = NULL;
        pcmBufferQueue = NULL;
        pcmFile = NULL;
        buffer = NULL;
        out_buffer = NULL;
    }

    // destroy file descriptor audio player object, and invalidate all associated interfaces
    if (fdPlayerObject != NULL) {
        (*fdPlayerObject)->Destroy(fdPlayerObject);
        fdPlayerObject = NULL;
        fdPlayerPlay = NULL;
        fdPlayerVolume = NULL;
    }

    // destroy URI audio player object, and invalidate all associated interfaces
    if (uriPlayerObject != NULL) {
        (*uriPlayerObject)->Destroy(uriPlayerObject);
        uriPlayerObject = NULL;
        uriPlayerPlay = NULL;
        uriPlayerVolume = NULL;
    }

    // destroy output mix object, and invalidate all associated interfaces
    if (outputMixObject != NULL) {
        (*outputMixObject)->Destroy(outputMixObject);
        outputMixObject = NULL;
        outputMixEnvironmentalReverb = NULL;
    }

    // destroy engine object, and invalidate all associated interfaces
    if (engineObject != NULL) {
        (*engineObject)->Destroy(engineObject);
        engineObject = NULL;
        engineEngine = NULL;
    }

}