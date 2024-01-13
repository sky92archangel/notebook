# FFmpeg

[TOC]

全称  fast forward mpeg 用于处理音视频流媒体开源工具库

## 下载和配置软件

进入官网

```
https://ffmpeg.org/download.html
```

进入下载得到编译完成的软件，此时FFMPEG更新到了4.3

```
ffmpeg-4.3-win64-static
```

解压并放入软件专用文件夹即可，并在环境变量中添加如下，以便在任何目录中使用该软件

```shell
ffmpeg-4.3-win64-static/bin
```



安装验证

```shell
$ ffmpeg --version
```

查看是否安装完成；



## 简要开始

### 文档介绍

根目录下有三个文件夹和两个文档，其中LICENSE.txt为版权许可，README.txt为说明

```shell
LICENSE.txt
README.txt
bin/
doc/
presets/
```

bin文件夹中存在三个文件，其中ffmpeg.exe为编码工具，ffplay.exe为简易播放器，ffprobe.exe为视频信息查看工具；

```shell
ffmpeg.exe
ffplay.exe
ffprobe.exe
```

presets文件夹中存放预设

```shell
ffprobe.xsd
libvpx-1080p.ffpreset
libvpx-1080p50_60.ffpreset
libvpx-360p.ffpreset
libvpx-720p.ffpreset
libvpx-720p50_60.ffpreset
```

doc文件夹中为网页形式的详细软件文档，大多数操作细节可参考内容

```shell
bootstrap.min.css
default.css
developer.html
faq.html
fate.html
ffmpeg-all.html
ffmpeg-bitstream-filters.html
ffmpeg-codecs.html
ffmpeg-devices.html
ffmpeg-filters.html
ffmpeg-formats.html
ffmpeg-protocols.html
ffmpeg-resampler.html
ffmpeg-scaler.html
ffmpeg-utils.html
ffmpeg.html
ffplay-all.html
ffplay.html
ffprobe-all.html
ffprobe.html
general.html
git-howto.html
libavcodec.html
libavdevice.html
libavfilter.html
libavformat.html
libavutil.html
libswresample.html
libswscale.html
mailing-list-faq.html
nut.html
platform.html
style.min.css
```

FFMPEG采用LGPL和GPL混合版权许可，其实人可自由使用做软件且必须将其代码开放；

### 命令行帮助

```shell
$ ffmpeg -h
```

### 简易播放

```shell
$ ffplay example.mp4
$ ffplay example.mp3		#播放音频  方向键可进行前进和后退 F全屏  P和SPACE暂停   W 切换显示
```

按下ESC或者Q即可退出；

### 快速查看媒体信息

```SHELL
$ ffprobe MediaExample.mp4
ffprobe version 4.3 Copyright (c) 2007-2020 the FFmpeg developers
  built with gcc 9.3.1 (GCC) 20200621
  configuration: --enable-gpl --enable-version3 --enable-sdl2 --enable-fontconfig --enable-gnutls --enable-iconv --enable-libass --enable-libdav1d --enable-libbluray --enable-libfreetype --enable-libmp3lame --enable-libopencore-amrnb --enable-libopencore-amrwb --enable-libopenjpeg --enable-libopus --enable-libshine --enable-libsnappy --enable-libsoxr --enable-libsrt --enable-libtheora --enable-libtwolame --enable-libvpx --enable-libwavpack --enable-libwebp --enable-libx264 --enable-libx265 --enable-libxml2 --enable-libzimg --enable-lzma --enable-zlib --enable-gmp --enable-libvidstab --enable-libvmaf --enable-libvorbis --enable-libvo-amrwbenc --enable-libmysofa --enable-libspeex --enable-libxvid --enable-libaom --enable-libgsm --disable-w32threads --enable-libmfx --enable-ffnvcodec --enable-cuda-llvm --enable-cuvid --enable-d3d11va --enable-nvenc --enable-nvdec --enable-dxva2 --enable-avisynth --enable-libopenmpt --enable-amf
  libavutil      56. 51.100 / 56. 51.100
  libavcodec     58. 91.100 / 58. 91.100
  libavformat    58. 45.100 / 58. 45.100
  libavdevice    58. 10.100 / 58. 10.100
  libavfilter     7. 85.100 /  7. 85.100
  libswscale      5.  7.100 /  5.  7.100
  libswresample   3.  7.100 /  3.  7.100
  libpostproc    55.  7.100 / 55.  7.100
Input #0, mov,mp4,m4a,3gp,3g2,mj2, from 'MediaExample.mp4':
  Metadata:
    major_brand     : isom
    minor_version   : 512
    compatible_brands: isomiso2avc1mp41
    encoder         : Lavf55.33.100
  Duration: 00:00:30.04, start: 0.000000, bitrate: 4470 kb/s
    Stream #0:0(und): Video: h264 (Main) (avc1 / 0x31637661), yuv420p(tv, bt709), 1920x1088, 4211 kb/s, 30 fps, 30 tbr, 90k tbn, 60 tbc (default)
    Metadata:
      handler_name    : VideoHandler
    Stream #0:1(eng): Audio: aac (LC) (mp4a / 0x6134706D), 44100 Hz, stereo, fltp, 256 kb/s (default)
    Metadata:
      handler_name    : SoundHandler

```

可见视频采用了H264编码格式，avc1封装，采用了yuv420p颜色空间，1920x1088像素，比特率4211kb/s，帧率30

音频采用了acc格式，LC规格，mp4a封装，采用率44100 Hz，立体声，比特率256 kb/s

## 格式转换

### 介绍

视频文件的后缀通常能判断为其封装格式，各类组织和公司都制定了很多标准，用于将视频和音频字幕等都放在一个容器内封装起来；其中有些兼容有些不兼容，不兼容时需要改变编码才能转换，通常我们采用兼容性好的封装方式和编码进行视频的转换方式；

| 视频封装方法                                        | 视频文件格式               |
| --------------------------------------------------- | -------------------------- |
| AVI                                                 | AVI                        |
| WMV                                                 | WMV                        |
| MPEG-1/MPEG-2/MPEG-4 (moving picture experts group) | MPG/MPEG/VOB/DAT/3GP   MP4 |
| Matroska                                            | MKV                        |
| Real Video                                          | RM/RMVB                    |
| Quick Time File Format (Apple Inc.)                 | MOV                        |
| Flash Video                                         | FLV                        |

MKV最为开放但是体积大，AVI较老，MOV为苹果公司制定，MP4为最流行；

### 视频封装转换

```shell
$ ffmpeg.exe -i MediaExample.mp4 MediaExample.mkv
# 这里将MP4封装 转换为 MKV封装
# -i 为 输入缩写
```

## 编码转换

### 介绍

ffmpeg支持很多编码格式，可以查看，基本具有上百种；

```shell
$ ffmpeg -codecs
```

常用视频网站使用的时H264视频编码+AAC音频编码；

当然还有 WebM封装，VP8视频编码+Voribis音频编码 ，谷歌youtube就使用这个方案；仅仅为了避免版权问题；

还有一套完全开源的编码方案：OGG封装 ， Theora视频编码 + Vorbis音频编码 ；无专利问题；

如需要制作超过1080P的2K 4K视频 还需要使用其他编码；

提示：用nvenc编码器  hevc_nvenc编码器 硬件加速飞快 

### 音频转码

```shell
$ ffmpeg -i example.flac -acodec libmp3lame -ar 44100 -ab 320k -ac 2 output.mp3
#这里将flac音频转为mp3    输入example.flac  输出output.mp3
# -i 为 输入缩写
#-acodec    a为audio音频缩写   codec为编码器   指定了 libmp3lame编码 就是mp3  若不输入则自动根据输出文件判断编码
# -ar 44100 a为audio音频缩写  r为采样率  常用 44100Hz或48000Hz
# -ab 320  a为audio音频缩写  b为比特率   指定比特率320kb/s
# -ac 2 c为channel  这里设置声道数   
```

### 视频压制

```shell
$ ffmpeg -i input.webm -s 1920x1080 -pix_fmt yuv420p -vcodec libx264 -preset medium -profile:v high -level:v 4.1 -crf 23 -r 30 -acodec aac -ar 44100 -ac 2 -b:a 128k output.mp4
#将webm文件转为mp4文件
#-s 1920x1080   s为size  指定尺寸缩放到1080P
# -pix_fmt yuv420p 即为 pixel format 来指定颜色空间 常有 YUV NV RGB 具体查看可以使用 ffmpeg -pix_fmts 查看
# -vcodec libx264 视频编码设定H264 
# -preset medium 编码器预设，指定编码工作性能 ，调节精度，精度越高编码越慢，资源占用越多，
# 编码器预设共10个参数，ultrafast superfast veryfast faster fast medium slow slower veryslow placebo 
# 常用veryfast占用低，质量低，体积大；压制一般用veryslow，体积小，参数控制好，压制时占用高；
#  -profile:v high 编码器的压缩比配置  越高，输出结果越小，但是画质下降，实时通讯使用baseline，流媒体采用main，超清采用high
#  -level:v 4.1 编码器的规范 压缩比和画质做权衡  1080视频采用4.1
#  -crf 23 总体码率控制 constant rate factor 恒定速率因子模式 用于全局画质控制 无法把握细节
#  crf越低画质越好，体积越大，范围0-51   常常使用18-28之间
#  -r 30  设定为30帧
# -acodec aac     a为audio音频缩写   codec为编码器  这里设定为aac编码
# -ar 44100   a为audio音频缩写  r为采样率   常用 44100Hz或48000Hz
# -b:a 128k   a为audio音频缩写  b为比特率   指定比特率320kb/s  同写法 -ab 128k  ，  -b:a 为推荐写法
```

### 码率控制模式

ffmpeg支持三种码率控制的的模式   -qp  -crf   -b

三种模式都是单遍编码，所以使用时适合搭配veryslow，可以避免大量错误；

#### qp模式

-qp   恒定量化器模式  constant quantizer

利用特殊算法将画质转为数字，每一帧都用这个做画质判定

范围 0-51  ，其中0为无损，但结果文件体积巨大；

 ```shell
#无损压缩 快速编码
$ ffmpeg -i input.mp4 -vcodec libx264 -preset ultrafast -qp 0 output.mkv
#无损压缩 高压缩比
$ ffmpeg -i input.mp4 -vcodec libx264 -preset veryslow -qp 0 output.mkv
 ```

#### crf模式

这就是个浮动的qp模式，将码率用在敏感的片段上，静止或慢镜头片段适当降低码率，达到大幅降低文件体积的目的；

#### bitrate模式

-b 固定目标码率模式 bitrate ， 用于对码率和体积都有限制的情况，直接设定控制目标码率和体积；用于视频网站内部视频处理；不常用；

bitrate模式默认采用 VBR 动态比特率  Variable Bit Rate 编码，自动预设简单内容少码率，复杂内容画面多码率

```shell
$ ffmpeg -i input.mp4 -vcodec libx264 -preset veryslow output.mkv
```

网络视频采用ABR 平均比特率  average bit rate

```shell
$ ffmpeg -i input.mp4 -vcodec libx264 -preset veryslow -b:v 3000k output.mkv
```

CBR 恒定比特率 constant bit rate 即为在ABR上添加细节，目前极少见

```shell
$ ffmpeg -i input.mp4 -vcodec libx264 -preset veryslow -b:v 4000k -minrate 4000k -maxrate 4000k -bufsize 1835k output.mkv
```



## 合并与提取

单独提取视频

```shell
$ ffmpeg -i input.mp4 -vcodec copy -an output.mp4
# -vcodec copy 保持原有视频编码
# -an 剔除方式静音
```

单独提取音频

```shell
$ ffmpeg -i input.mp4 -vn -acodec copy output.m4a
#  -vn 剔除视频
# 如果视频具有多个音频  则需要另外  -map 0:3  
```

音视频合并

```shell
$ ffmpeg -i a.m4a -i v.mp4 -c copy out.mp4
#  -c copy 保持编码不懂
#  可以瞬间完成合并
```



## 截取

### 音频截取

```shell
$ ffmpeg -i  input.mp3 -ss 00:01:00 -to 00:01:10 -acodec copy output.mp3
#  -ss 00:01:00 -to 00:01:10   截取时间  时:分:秒 
$ ffmpeg -i  input.mp3 -ss 00:01:00 -t 10 -acodec copy output.mp3
#  -ss 00:01:00 -t10   截取时间  持续10秒 
# -sseof 可以从末尾开始计算时间

$ ffmpeg -i  input.mp4 -ss 00:01:00 -t 10 -acodec copy output.mp4
$ ffmpeg -ss 00:01:00  -i input.mp4-t 10 -acodec copy output.mp4
#上述将ss放在输入前  模式采用关键帧技术 但是其截取时间会不精确 所以采用如下
$ ffmpeg -ss 00:01:00  -i input.mp4-t 10 -acodec copy -copyts output.mp4
# -copyts 用于保留时间戳 保证时间准确
```

### 串联连接视频

```shell
$ ffmpeg -i "concat:01.mp4|02.mp4|03.mp4" -c copy output.mp4
# 如果编码相同可以快速合并 三个视频  但是如果编码不同 则操作非常复杂  需要其他软件辅助 如 avidemux
```



## 截图 水印 动图

截图

```shell
$ ffmpeg -i input.mp4 -ss 5 -vframes 1 img.jpg
#  -ss 5 定位第五秒截取
#  -vframes 1  定位当前秒的第1帧
```

水印，准备一个图片如 log.png  建议采用png 可以带有透明通道

```shell
$ ffmpeg -i input.mp4  -i log.png -filter_complex "overlay=20:20" output.mp4
#  -filter_complex "overlay=20:20"  添加滤镜   位置为距离左边20像素  距离顶部20像素  
```

动图

```shell
$ ffmpeg -i  input.mp4 -ss 7.5 -to 8.5 -s 640x320 -r 15  out.gif 
```

视频转图片

```shell
$ ffmpeg -i GGGabc.mp4 -t 5 -s 1080x1080 -r 15 %3d.jpg    
# -t 5表示选取视频中的前五秒进行视频转图像
# -s 1080x1080表示视频转图片后图片的像素
# -r 15表示每秒截取15张图片，也就是15帧
# %3d.jpg表示生成图片后的图片的命名格式会以001.jpg，002.jpg....命名
```

图片转视频

```shell
$ ffmpeg -r 15 -i %3d.jpg video.avi
# -i %3d.jpg表示要选取图片的命名格式，就是调用001.jpg，002.jpg......等图片组成视频
# -r 15表示15张图片一秒，就是一秒十五帧
```

 

## 录制和直播

### 录制

```shell
$ ffmpeg -f gdigrab -i desktop rec.mp4
#  -f gdigrab 用于捕获视频设备的组件 不同操作系统工具不同  gdigrab目前只能抓取视频没有音频
# 此时需要换为  screen capture recorder 但不推荐
# 最佳方案为 OBS studio  开源 免费 稳定 强大

#下面是采用声卡时可能做到录音的操作
ffmpeg -f gdigrab -i desktop -f dshow -i audio="麦克风 (Cirrus Logic CS4206B (AB 9" -vcodec libx264 -acodec aac -strict -2 rec.mp4 

```

直播录播推流

```shell
$ ffmpeg -re -i rec.mp4  按照网站编码要求  -f  flv  "你的rtmp地址/你的直播码"
```































