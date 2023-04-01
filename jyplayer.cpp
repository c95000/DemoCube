#include "jyplayer.h"


#include <QDateTime>
#include <QStandardPaths>
#include <QDir>
#include "Configure.h"
#include "mp4encoder.h"
#include <QDebug>
#define printf qDebug

JyPlayer::JyPlayer(const QString& inputsource, QObject *parent) : QThread(parent)
  ,source(inputsource)
  ,state(IDLE)
  ,glVideoWidget(nullptr)
{

}

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

void JyPlayer::run() {
    playDirectly(source.toStdString().c_str());
}

int JyPlayer::playDirectly(const char *source) {
    fprintf(stderr, "tid: %d\n", QThread::currentThreadId());

    AVFormatContext *format_ctx = NULL;
    AVCodecContext *codec_ctx = NULL;
    AVCodecContext *audio_codec_ctx = NULL;
    struct SwsContext *sws_ctx = NULL;

    playing = true;

    uint8_t *rgb_data = NULL;
    int rgb_linesize;
    // Check command line arguments
    if (!source) {
        fprintf(stderr, "Usage: %s input_file output_pattern\n", __FUNCTION__);
        return 1;
    }

    // Open the input file
    if (avformat_open_input(&format_ctx, source, NULL, NULL) < 0) {
        fprintf(stderr, "Error: Could not open input file '%s'\n", source);
        return 1;
    }
    // Find the video stream
    if (avformat_find_stream_info(format_ctx, NULL) < 0) {
        fprintf(stderr, "Error: Could not find stream information\n");
        return 1;
    }

    int video_stream_index = -1;
    int audio_stream_index = -1;

    const AVCodec *codec = NULL;
    const AVCodec *audio_codec = NULL;

    for (int i = 0; i < format_ctx->nb_streams; i++) {
        if (format_ctx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
            video_stream_index = i;
            break;
        }
    }

    for (int i = 0; i < format_ctx->nb_streams; i++) {
        if (format_ctx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_AUDIO) {
            audio_stream_index = i;
            break;
        }
    }

    if(video_stream_index >= 0) {
        // Find the video codec and open it
        codec = avcodec_find_decoder(format_ctx->streams[video_stream_index]->codecpar->codec_id);
        if (codec == NULL) {
            fprintf(stderr, "Error: Unsupported codec\n");
            return 1;
        }
        fprintf(stderr, "codec name: %s\n", codec->name);
        fprintf(stderr, "codec long_name: %s\n", codec->long_name);
        fprintf(stderr, "codec wrapper_name: %s\n", codec->wrapper_name);

        codec_ctx = avcodec_alloc_context3(codec);
        if (avcodec_parameters_to_context(codec_ctx, format_ctx->streams[video_stream_index]->codecpar) < 0) {
            fprintf(stderr, "Error: Could not copy codec parameters\n");
            return 1;
        }

        if (avcodec_open2(codec_ctx, codec, NULL) < 0) {
            fprintf(stderr, "Error: Could not open codec\n");
            return 1;
        }
    }

    if(audio_stream_index >= 0) {
        // Find the video codec and open it
        audio_codec = avcodec_find_decoder(format_ctx->streams[audio_stream_index]->codecpar->codec_id);
        if (audio_codec == NULL) {
            fprintf(stderr, "Error: Unsupported audio_codec\n");
            return 1;
        }

        fprintf(stderr, "audio_codec name: %s\n", audio_codec->name);
        fprintf(stderr, "audio_codec long_name: %s\n", audio_codec->long_name);
        fprintf(stderr, "audio_codec wrapper_name: %s\n", audio_codec->wrapper_name);

        audio_codec_ctx = avcodec_alloc_context3(audio_codec);
        if (avcodec_parameters_to_context(audio_codec_ctx, format_ctx->streams[audio_stream_index]->codecpar) < 0) {
            fprintf(stderr, "Error: Could not copy codec parameters\n");
            return 1;
        }

        if (avcodec_open2(audio_codec_ctx, audio_codec, NULL) < 0) {
            fprintf(stderr, "Error: Could not open codec\n");
            return 1;
        }
    }

    AVPacket *packet = NULL;
    AVFrame *frame = NULL;

    // Allocate memory for the frame and packet
    packet = av_packet_alloc();
    frame = av_frame_alloc();
    if (packet == NULL || frame == NULL) {
        fprintf(stderr, "Error: Could not allocate memory for frame and packet\n");
        return 1;
    }

    // Initialize the packet
    packet = av_packet_alloc();
    packet->data = NULL;
    packet->size = 0;

    // Initialize the scaler for RGB conversion
    sws_ctx = sws_getContext(codec_ctx->width, codec_ctx->height, codec_ctx->pix_fmt,
                             codec_ctx->width, codec_ctx->height, AV_PIX_FMT_RGB24,
                             SWS_BILINEAR, NULL, NULL, NULL);
    if (sws_ctx == NULL) {
        fprintf(stderr, "Error: Could not initialize scaler\n");
        return 1;
    }

    // Loop through each packet in the input file
    while (playing && av_read_frame(format_ctx, packet) >= 0) {
        if (packet->stream_index == video_stream_index) {
            // Decode the video packet
            int ret = avcodec_send_packet(codec_ctx, packet);
            if (ret < 0) {
                fprintf(stderr, "Error decoding video packet\n");
                break;
            }
            while (ret >= 0) {
                ret = avcodec_receive_frame(codec_ctx, frame);
                if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF) {
                    break;
                } else if (ret < 0) {
                    fprintf(stderr, "Error decoding video frame\n");
                    break;
                } else {

                }
                fprintf(stderr, "pos: %d \n", packet->dts);
            }
            av_packet_unref(packet);
        }
        if(packet->stream_index == audio_stream_index) {
            // Decode the audio packet
            int ret = avcodec_send_packet(audio_codec_ctx, packet);
            if (ret < 0) {
                fprintf(stderr, "Error decoding audio packet\n");
                break;
            }
            while (ret >= 0) {
                ret = avcodec_receive_frame(audio_codec_ctx, frame);
                if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF) {
                    break;
                } else if (ret < 0) {
                    fprintf(stderr, "Error decoding audio frame\n");
                    break;
                } else {

                }
                fprintf(stderr, "audio pos: %d \n", packet->dts);
            }
            av_packet_unref(packet);
        }
    }

    // Free resources
    av_packet_free(&packet);
    av_frame_free(&frame);

    avcodec_free_context(&codec_ctx);
    avcodec_free_context(&audio_codec_ctx);
    avformat_close_input(&format_ctx);
    sws_freeContext(sws_ctx);
    fprintf(stderr, "play '%s' successed.\n", source);
    return 0;
}

int JyPlayer::startPlay(const QString& inputsource, GLVideoWidget* glVideoWidget) {
    this->source = inputsource;
    this->glVideoWidget = glVideoWidget;

    QString picPath = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
    h264FileName = picPath + QDir::separator() + QDateTime::currentDateTime().toString("yyyy-MM-dd hh-mm-ss-zzz") + ".h264";

    return startPlay();
}

int JyPlayer::startPlay() {
    setState(enJYPLAYER_STATE::PREPARING);
    start();
    return 0;
}

int JyPlayer::stopPlay() {
    setState(enJYPLAYER_STATE::STOPPED);
    printf("stopPlay -- ");
    quit();
    printf("stopPlay -- quit");
    wait();
    printf("stopPlay -- wait");

    return 0;
}

int JyPlayer::pausePlay() {
    setState(enJYPLAYER_STATE::PAUSED);
    return 0;
}

int JyPlayer::resumePlay() {
    return 0;
}

int JyPlayer::togglePlay() {
    if(state == PREPARING || state == PLAYING)
    {
        stopPlay();
    }
    else
    {
        startPlay();
    }
    return 0;
}

bool JyPlayer::isWorking() {
    if(state != IDLE) {
        return true;
    } else {
        return false;
    }
}

int JyPlayer::startRecord() {
    if(state == PLAYING && !isRecording) {
        recordedFileName = Configure::getInstance()->getVideopath() + QDir::separator() +
                    QDateTime::currentDateTime().toString("yyyy-MM-dd hh-mm-ss-zzz");
//        if(NULL == h264File) {
//            h264File = fopen(recordedFileName.toStdString().c_str(), "wba");
//        }
        qh264File.setFileName(recordedFileName + ".h264");
        qh264File.open(QIODevice::ReadWrite);
        isGotIFrame = false;
        isRecording = true;
    }
    return 0;
}

int JyPlayer::stopRecord() {
    if(state == PLAYING && isRecording) {
        isRecording = false;
        qh264File.flush();
        qh264File.close();

//        Mp4Encoder::h2642mp4((recordedFileName + ".h264").toStdString().c_str(),
//                             ((recordedFileName + ".mp4")).toStdString().c_str());
//        QFile::remove(recordedFileName + ".h264");
    }
    return 0;
}

void JyPlayer::setState(enJYPLAYER_STATE state){
    if(this->state == state) {
        return;
    }

    this->state = state;
    if(state == PLAYING) {
        emit started();
    } else if(state == STOPPED) {
        emit stopped();
    } else if(state == PAUSED) {
        emit paused();
    }
}

