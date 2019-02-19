# FFMPEGBasic
Android的音视频部分示例。

主要包含的功能如下：
+ 使用MediaPlayer播放raw音频文件
+ 使用OpenSL播放音频，包括播放assets文件；播放uri文件；手机上的pcm音频文件（可在本页面选择文件）
+ 使用FFMPEG和SurfaceView播放手机本地视频文件
+ 使用VideoView播放手机本地视频文件
+ JNI操作pcm音频文件，包括：1.将PCM文件分为左右声道，2.PCM音量减半，3.将PCM加速播放，4.PCM16位转为8位，5.将PCM文件转为wav文件。
