#include "ffdecoder.h"
#include <QDateTime>

static void printError(int ret) {
    char msg[512];
    av_make_error_string(msg, 512, ret);
    printf("Error(%d)(%s).\n", ret, msg);
}

static void writeFile(const QString& filename, const char* data, int size) {
    QFile f(filename);
    f.open(QIODevice::WriteOnly | QIODevice::Append);
    f.write(data, size);
    f.close();
}


FFDecoder::FFDecoder(QObject *parent) : QThread(parent)
{

}

FFDecoder::~FFDecoder() {

}

void FFDecoder::run() {
    printf("FFDecoder %s() enter. tid:%d", __FUNCTION__, QThread::currentThreadId());
    m_state = FFDECODER_PLAYING;

    int count = 0;
    std::string urlStr = inputSource.toStdString();
    const char* url = urlStr.c_str();
    printf("running... %s", url);
    // A1. 打开视频文件：读取文件头，将文件格式信息存储在"fmt context"中
    ret = avformat_open_input(&p_fmt_ctx, url, NULL, NULL);
    if (ret != 0)
    {
        printf("avformat_open_input() failed: %d\n", ret);
        printError(ret);
        return;
    }

    // A2. 搜索流信息：读取一段视频文件数据，尝试解码，将取到的流信息填入pFormatCtx->streams
        //     p_fmt_ctx->streams是一个指针数组，数组大小是pFormatCtx->nb_streams
    ret = avformat_find_stream_info(p_fmt_ctx, NULL);
    if (ret < 0)
    {
        printf("avformat_find_stream_info() failed\n");
        printError(ret);
        return;
    }

    // 将文件相关信息打印在标准错误设备上
    av_dump_format(p_fmt_ctx, 0, url, 0);

    // A3. 查找第一个视频流
    v_idx = -1;
    for (unsigned int i=0; i < p_fmt_ctx->nb_streams; i++)
    {
        if (p_fmt_ctx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO)
        {
            v_idx = i;
            printf("Find a video stream, index %d\n", v_idx);
            break;
        }
    }
    if (v_idx == -1)
    {
        printf("Cann't find a video stream\n");
        return;
    }


    // A5. 为视频流构建解码器AVCodecContext

    // A5.1 获取解码器参数AVCodecParameters
    p_codec_par = p_fmt_ctx->streams[v_idx]->codecpar;
    // A5.2 获取解码器
    p_codec = avcodec_find_decoder(p_codec_par->codec_id);
    if (p_codec == NULL)
    {
        printf("Cann't find codec!\n");
        return;
    }

    // A5.3 构建解码器AVCodecContext
    // A5.3.1 p_codec_ctx初始化：分配结构体，使用p_codec初始化相应成员为默认值
    p_codec_ctx = avcodec_alloc_context3(p_codec);

    // A5.3.2 p_codec_ctx初始化：p_codec_par ==> p_codec_ctx，初始化相应成员
    ret = avcodec_parameters_to_context(p_codec_ctx, p_codec_par);
    if (ret < 0)
    {
        printf("avcodec_parameters_to_context() failed %d\n", ret);
        return;
    }

    // A5.3.3 p_codec_ctx初始化：使用p_codec初始化p_codec_ctx，初始化完成
    ret = avcodec_open2(p_codec_ctx, p_codec, NULL);
    if (ret < 0)
    {
        printf("avcodec_open2() failed %d\n", ret);
        return;
    }

    // A6. 分配AVFrame
    // A6.1 分配AVFrame结构，注意并不分配data buffer(即AVFrame.*data[])
    p_frm_raw = av_frame_alloc();
    p_frm_yuv = av_frame_alloc();

    // A6.2 为AVFrame.*data[]手工分配缓冲区，用于存储sws_scale()中目的帧视频数据
    //     p_frm_raw的data_buffer由av_read_frame()分配，因此不需手工分配
    //     p_frm_yuv的data_buffer无处分配，因此在此处手工分配
    printf("video size: %d x %d", p_codec_ctx->width, p_codec_ctx->height);
    buf_size = av_image_get_buffer_size(AV_PIX_FMT_YUV420P,
                                       p_codec_ctx->width,
                                       p_codec_ctx->height,
                                       align
                                      );

    // buffer将作为p_frm_yuv的视频数据缓冲区
    buffer = (uint8_t *)av_malloc(buf_size);
    // 使用给定参数设定p_frm_yuv->data和p_frm_yuv->linesize
    av_image_fill_arrays(p_frm_yuv->data,           // dst data[]
                        p_frm_yuv->linesize,       // dst linesize[]
                        buffer,                    // src buffer
                        AV_PIX_FMT_YUV420P,        // pixel format
                        p_codec_ctx->width,        // width
                        p_codec_ctx->height,       // height
                        align                          // align
                       );

    if(video_format_cb != nullptr) {
        video_format_cb(opaque, &p_codec_ctx->width, &p_codec_ctx->height, p_frm_yuv->linesize);
    }

//    GLVideoWidget *glVideoWidget = nullptr;
//    if(nullptr != videoView) {
//        glVideoWidget = dynamic_cast<GLVideoWidget*>(videoView);
//    }

//    if(nullptr != glVideoWidget) {
//        glVideoWidget->setYUV420pParameters(p_codec_ctx->width, p_codec_ctx->height, p_frm_yuv->linesize);
//    }


    // A7. 初始化SWS context，用于后续图像转换
    //     此处第6个参数使用的是FFmpeg中的像素格式，对比参考注释B4
    //     FFmpeg中的像素格式AV_PIX_FMT_YUV420P对应SDL中的像素格式SDL_PIXELFORMAT_IYUV
    //     如果解码后得到图像的不被SDL支持，不进行图像转换的话，SDL是无法正常显示图像的
    //     如果解码后得到图像的能被SDL支持，则不必进行图像转换
    //     这里为了编码简便，统一转换为SDL支持的格式AV_PIX_FMT_YUV420P==>SDL_PIXELFORMAT_IYUV
    sws_ctx = sws_getContext(p_codec_ctx->width,    // src width
                            p_codec_ctx->height,   // src height
                            p_codec_ctx->pix_fmt,  // src format
                            p_codec_ctx->width,    // dst width
                            p_codec_ctx->height,   // dst height
                            AV_PIX_FMT_YUV420P,    // dst format
                            SWS_BICUBIC,           // flags
                            NULL,                  // src filter
                            NULL,                  // dst filter
                            NULL                   // param
                           );

    p_packet = (AVPacket *)av_malloc(sizeof(AVPacket));

    QString picPath = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
    QString fileName = picPath + QDir::separator() + QDateTime::currentDateTime().toString("yyyy-MM-dd hh-mm-ss-zzz") + ".yuv";

    // A8. 从视频文件中读取一个packet
    //     packet可能是视频帧、音频帧或其他数据，解码器只会解码视频帧或音频帧，非音视频数据并不会被
    //     扔掉、从而能向解码器提供尽可能多的信息
    //     对于视频来说，一个packet只包含一个frame
    //     对于音频来说，若是帧长固定的格式则一个packet可包含整数个frame，
    //                   若是帧长可变的格式则一个packet只包含一个frame
    while (av_read_frame(p_fmt_ctx, p_packet) == 0)
    {
        if (p_packet->stream_index == v_idx)  // 仅处理视频帧
        {
            // A9. 视频解码：packet ==> frame
            // A9.1 向解码器喂数据，一个packet可能是一个视频帧或多个音频帧，此处音频帧已被上一句滤掉
            ret = avcodec_send_packet(p_codec_ctx, p_packet);
            if (ret != 0)
            {
                printf("avcodec_send_packet() failed %d\n", ret);
                return;
            }
            // A9.2 接收解码器输出的数据，此处只处理视频帧，每次接收一个packet，将之解码得到一个frame

//            *      AVERROR(EAGAIN):   output is not available in this state - user must try
//            *                         to send new input
//            *      AVERROR_EOF:       the decoder has been fully flushed, and there will be
//            *                         no more output frames
//            *      AVERROR(EINVAL):   codec not opened, or it is an encoder
//            *      AVERROR_INPUT_CHANGED:   current decoded frame has changed parameters
//            *                               with respect to first decoded frame. Applicable
//            *                               when flag AV_CODEC_FLAG_DROPCHANGED is set.
//            *      other negative values: legitimate decoding errors
            ret = avcodec_receive_frame(p_codec_ctx, p_frm_raw);
            if (ret != 0)
            {
                printf("avcodec_receive_frame() failed %d\n", ret);
                continue;
//                printErr(ret);
//                return;
            }

//            printf("got_picture_ptr:%d format:%d  %d x %d picType:%d", got_picture_ptr, pFrame->format, pFrame->width, pFrame->height, pFrame->pict_type);
//            printf("data pts: %lld %p format: %d size: %d", p_frm_raw->pts, p_frm_raw->buf, p_frm_raw->format, p_frm_raw->pkt_size);
//            printf("");

            // A10. 图像转换：p_frm_raw->data ==> p_frm_yuv->data
            // 将源图像中一片连续的区域经过处理后更新到目标图像对应区域，处理的图像区域必须逐行连续
            // plane: 如YUV有Y、U、V三个plane，RGB有R、G、B三个plane
            // slice: 图像中一片连续的行，必须是连续的，顺序由顶部到底部或由底部到顶部
            // stride/pitch: 一行图像所占的字节数，Stride=BytesPerPixel*Width+Padding，注意对齐
            // AVFrame.*data[]: 每个数组元素指向对应plane
            // AVFrame.linesize[]: 每个数组元素表示对应plane中一行图像所占的字节数
            sws_scale(sws_ctx,                                  // sws context
                      (const uint8_t *const *)p_frm_raw->data,  // src slice
                      p_frm_raw->linesize,                      // src stride
                      0,                                        // src slice y
                      p_codec_ctx->height,                      // src slice height
                      p_frm_yuv->data,                          // dst planes
                      p_frm_yuv->linesize                       // dst strides
                     );

            //printf("output yuv: pts: %lld %p format: %d size: %d", p_frm_yuv->pts, p_frm_yuv->data, p_frm_yuv->format, p_frm_yuv->pkt_size);
            printf("output yuv: %p %p %p (%d %d %d)", p_frm_yuv->data[0], p_frm_yuv->data[1], p_frm_yuv->data[2],
                    p_frm_yuv->linesize[0], p_frm_yuv->linesize[1], p_frm_yuv->linesize[2]);

//            if(count++ == 300) {
//                printf("output yuv: (%d %d)", p_frm_yuv->data[1] - p_frm_yuv->data[0], p_frm_yuv->data[2] - p_frm_yuv->data[1]);
//                writeFile(fileName, (char *)p_frm_yuv->data[0], p_frm_yuv->linesize[0] * p_codec_ctx->height);
//                writeFile(fileName, (char *)p_frm_yuv->data[1], p_frm_yuv->linesize[1] * p_codec_ctx->height/2);
//                writeFile(fileName, (char *)p_frm_yuv->data[2], p_frm_yuv->linesize[2] * p_codec_ctx->height/2);
//            }

            if(nullptr != data_available_cb) {
                QByteArray ba;
                ba.append((char *)p_frm_yuv->data[0], p_frm_yuv->linesize[0] * p_codec_ctx->height);
                ba.append((char *)p_frm_yuv->data[1], p_frm_yuv->linesize[1] * p_codec_ctx->height / 2);
                ba.append((char *)p_frm_yuv->data[2], p_frm_yuv->linesize[2] * p_codec_ctx->height / 2);
//                glVideoWidget->setFrameData(ba);
                data_available_cb(opaque, ba);
            }


            // B5. 使用新的YUV像素数据更新SDL_Rect
//            SDL_UpdateYUVTexture(sdl_texture,                   // sdl texture
//                                 &sdl_rect,                     // sdl rect
//                                 p_frm_yuv->data[0],            // y plane
//                                 p_frm_yuv->linesize[0],        // y pitch
//                                 p_frm_yuv->data[1],            // u plane
//                                 p_frm_yuv->linesize[1],        // u pitch
//                                 p_frm_yuv->data[2],            // v plane
//                                 p_frm_yuv->linesize[2]         // v pitch
//                                 );

//            // B6. 使用特定颜色清空当前渲染目标
//            SDL_RenderClear(sdl_renderer);
//            // B7. 使用部分图像数据(texture)更新当前渲染目标
//            SDL_RenderCopy(sdl_renderer,                        // sdl renderer
//                           sdl_texture,                         // sdl texture
//                           NULL,                                // src rect, if NULL copy texture
//                           &sdl_rect                            // dst rect
//                          );
//            // B8. 执行渲染，更新屏幕显示
//            SDL_RenderPresent(sdl_renderer);

//            // B9. 控制帧率为25FPS，此处不够准确，未考虑解码消耗的时间
//            SDL_Delay(40);
        }
        av_packet_unref(p_packet);
    }

    avformat_close_input(&p_fmt_ctx);
    printf("OK");
    m_state = FFDECODER_STOPPED;
    emit stopped();


//    emit played();
//    while(m_state != FFDECODER_ERROR && m_state != FFDECODER_STOPPED) {
//        printf("FFDecoder %s() running. state:%d %s", __FUNCTION__, m_state, QDateTime::currentDateTime().toString("hh:mm:ss:zzz").toStdString().c_str());

//        msleep(2000);
//    }

    printf("FFDecoder %s() exit", __FUNCTION__);
}

void FFDecoder::setSource(const QString &inputSrc, ffdecoder_video_format_cb video_format_cb, ffdecoder_data_available_cb data_available_cb, void* opaque) {
    this->video_format_cb = video_format_cb;
    this->data_available_cb = data_available_cb;
    this->opaque = opaque;
    inputSource = inputSrc;
}

void FFDecoder::play() {
    if(m_state == FFDECODER_PAUSED) {
        m_state = FFDECODER_PLAYING;
        emit played();
    } else {
        start();
    }
}

void FFDecoder::stop() {
    printf("L:%d FFDecoder %s() ", __LINE__, __FUNCTION__);
    m_state = FFDECODER_STOPPED;
    quit();
    printf("L:%d FFDecoder %s() ", __LINE__, __FUNCTION__);
    wait();
    printf("L:%d FFDecoder %s() ", __LINE__, __FUNCTION__);

    emit stopped();
}

void FFDecoder::pause() {
    m_state = FFDECODER_PAUSED;
    emit paused();
}

void FFDecoder::resume() {
    m_state = FFDECODER_PLAYING;
    emit played();
}
