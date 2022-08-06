#include "mp4encoder.h"
#include "Configure.h"
#include "QDateTime"
#include <QDir>

Mp4Encoder::Mp4Encoder(QObject *parent) : QObject(parent)
{

}

Mp4Encoder::~Mp4Encoder() {

}

int Mp4Encoder::flush_encoder(AVFormatContext *fmt_ctx,unsigned int stream_index) {
    int ret;
    int got_frame;
    AVPacket enc_pkt;
    if (!(fmt_ctx->streams[stream_index]->codec->codec->capabilities &
        AV_CODEC_CAP_DELAY))
        return 0;
    while (1) {
        enc_pkt.data = NULL;
        enc_pkt.size = 0;
        av_init_packet(&enc_pkt);
        ret = avcodec_encode_video2 (fmt_ctx->streams[stream_index]->codec, &enc_pkt,
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


int Mp4Encoder::start(int width, int height, const char* output_file) {
    AVFormatContext* pFormatCtx;
        AVOutputFormat* fmt;
        AVStream* video_st;
        AVCodecContext* pCodecCtx;
        AVCodec* pCodec;
        AVPacket pkt;
        uint8_t* picture_buf;
        AVFrame* pFrame;
        int picture_size;
        int y_size;
        int framecnt=0;
        //FILE *in_file = fopen("src01_480x272.yuv", "rb");	//Input raw YUV data
        FILE *in_file = fopen("D:\\vs\\test.yuv", "rb");   //Input raw YUV data
        int in_w=858,in_h=482;                              //Input data's width and height
        int framenum=400;                                   //Frames to encode
        //const char* out_file = "src01.h264";              //Output Filepath
        //const char* out_file = "src01.ts";
        //const char* out_file = "src01.hevc";
        const char* out_file = "D:\\vs\\test.h264";

        av_register_all();
        //Method1.
        pFormatCtx = avformat_alloc_context();
        //Guess Format
        fmt = av_guess_format(NULL, out_file, NULL);
        pFormatCtx->oformat = fmt;

        //Method 2.
        //avformat_alloc_output_context2(&pFormatCtx, NULL, NULL, out_file);
        //fmt = pFormatCtx->oformat;

        //Open output URL
        if (avio_open(&pFormatCtx->pb,out_file, AVIO_FLAG_READ_WRITE) < 0){
            printf("Failed to open output file! \n");
            return -1;
        }

        video_st = avformat_new_stream(pFormatCtx, 0);
        //video_st->time_base.num = 1;
        //video_st->time_base.den = 25;

        if (video_st==NULL){
            return -1;
        }
        //Param that must set
        pCodecCtx = video_st->codec;
        //pCodecCtx->codec_id =AV_CODEC_ID_HEVC;
        pCodecCtx->codec_id = fmt->video_codec;
        pCodecCtx->codec_type = AVMEDIA_TYPE_VIDEO;
        pCodecCtx->pix_fmt = AV_PIX_FMT_YUV420P;
        pCodecCtx->width = in_w;
        pCodecCtx->height = in_h;
        pCodecCtx->bit_rate = 400000;
        pCodecCtx->gop_size=250;

        pCodecCtx->time_base.num = 1;
        pCodecCtx->time_base.den = 25;

        //H264
        //pCodecCtx->me_range = 16;
        //pCodecCtx->max_qdiff = 4;
        //pCodecCtx->qcompress = 0.6;
        pCodecCtx->qmin = 10;
        pCodecCtx->qmax = 51;

        //Optional Param
        pCodecCtx->max_b_frames=3;

        // Set Option
        AVDictionary *param = 0;
        //H.264
        if(pCodecCtx->codec_id == AV_CODEC_ID_H264) {
            av_dict_set(&param, "preset", "slow", 0);
            av_dict_set(&param, "tune", "zerolatency", 0);
            //av_dict_set(¶m, "profile", "main", 0);
        }
        //H.265
        if(pCodecCtx->codec_id == AV_CODEC_ID_H265){
            av_dict_set(&param, "preset", "ultrafast", 0);
            av_dict_set(&param, "tune", "zero-latency", 0);
        }

        //Show some Information
        av_dump_format(pFormatCtx, 0, out_file, 1);

        pCodec = avcodec_find_encoder(pCodecCtx->codec_id);
        if (!pCodec){
            printf("Can not find encoder! \n");
            return -1;
        }
        if (avcodec_open2(pCodecCtx, pCodec,&param) < 0){
            printf("Failed to open encoder! \n");
            return -1;
        }


        pFrame = av_frame_alloc();
        picture_size = avpicture_get_size(pCodecCtx->pix_fmt, pCodecCtx->width, pCodecCtx->height);
        picture_buf = (uint8_t *)av_malloc(picture_size);
        avpicture_fill((AVPicture *)pFrame, picture_buf, pCodecCtx->pix_fmt, pCodecCtx->width, pCodecCtx->height);

        //Write File Header
        avformat_write_header(pFormatCtx,NULL);

        av_new_packet(&pkt,picture_size);

        y_size = pCodecCtx->width * pCodecCtx->height;

        for (int i=0; i<framenum; i++){
            //Read raw YUV data
            if (fread(picture_buf, 1, y_size*3/2, in_file) <= 0){
                printf("Failed to read raw data! \n");
                return -1;
            }else if(feof(in_file)){
                break;
            }
            pFrame->data[0] = picture_buf;              // Y
            pFrame->data[1] = picture_buf+ y_size;      // U
            pFrame->data[2] = picture_buf+ y_size*5/4;  // V
            //PTS
            //pFrame->pts=i;
            pFrame->pts=i*(video_st->time_base.den)/((video_st->time_base.num)*25);
            int got_picture=0;
            //Encode
            int ret = avcodec_encode_video2(pCodecCtx, &pkt,pFrame, &got_picture);
            if(ret < 0){
                printf("Failed to encode! \n");
                return -1;
            }
            if (got_picture==1){
                printf("Succeed to encode frame: %5d\tsize:%5d\n",framecnt,pkt.size);
                framecnt++;
                pkt.stream_index = video_st->index;
                ret = av_write_frame(pFormatCtx, &pkt);
                av_free_packet(&pkt);
            }
        }
        //Flush Encoder
        int ret = flush_encoder(pFormatCtx,0);
        if (ret < 0) {
            printf("Flushing encoder failed\n");
            return -1;
        }

        //Write file trailer
        av_write_trailer(pFormatCtx);

        //Clean
        if (video_st){
            avcodec_close(video_st->codec);
            av_free(pFrame);
            av_free(picture_buf);
        }
        avio_close(pFormatCtx->pb);
        avformat_free_context(pFormatCtx);

        fclose(in_file);
}

int Mp4Encoder::encode(const char* data, const int size) {
    return 0;
}

int Mp4Encoder::yuv2h264_start(int width, int height) {
        int picture_size;
        int y_size;
        int framecnt=0;

        int in_w=width,in_h=height;                              //Input data's width and height
        int framenum=400;

        outputFileName = Configure::getInstance()->getVideopath() + QDir::separator() + QDateTime::currentDateTime().toString("yyyy-MM-dd hh-mm-ss-zzz");

        //Frames to encode
        const char* out_file = outputFileName.append(".h264").toStdString().c_str();

        av_register_all();
        //Method1.
        pFormatCtx = avformat_alloc_context();
        //Guess Format
        fmt = av_guess_format(NULL, out_file, NULL);
        pFormatCtx->oformat = fmt;

        //Open output URL
        if (avio_open(&pFormatCtx->pb, out_file, AVIO_FLAG_READ_WRITE) < 0){
            printf("Failed to open output file! \n");
            return -1;
        }

        video_st = avformat_new_stream(pFormatCtx, 0);
        //video_st->time_base.num = 1;
        //video_st->time_base.den = 25;

        if (video_st==NULL){
            return -1;
        }
        //Param that must set
        pCodecCtx = video_st->codec;
        //pCodecCtx->codec_id =AV_CODEC_ID_HEVC;
        pCodecCtx->codec_id = fmt->video_codec;
        pCodecCtx->codec_type = AVMEDIA_TYPE_VIDEO;
        pCodecCtx->pix_fmt = AV_PIX_FMT_YUV420P;
        pCodecCtx->width = in_w;
        pCodecCtx->height = in_h;
        pCodecCtx->bit_rate = 400000;
        pCodecCtx->gop_size=250;

        pCodecCtx->time_base.num = 1;
        pCodecCtx->time_base.den = 25;

        //H264
        //pCodecCtx->me_range = 16;
        //pCodecCtx->max_qdiff = 4;
        //pCodecCtx->qcompress = 0.6;
        pCodecCtx->qmin = 10;
        pCodecCtx->qmax = 51;

        //Optional Param
        pCodecCtx->max_b_frames=3;

        // Set Option
        AVDictionary *param = 0;
        //H.264
        if(pCodecCtx->codec_id == AV_CODEC_ID_H264) {
            av_dict_set(&param, "preset", "slow", 0);
            av_dict_set(&param, "tune", "zerolatency", 0);
            //av_dict_set(¶m, "profile", "main", 0);
        }
        //H.265
        if(pCodecCtx->codec_id == AV_CODEC_ID_H265){
            av_dict_set(&param, "preset", "ultrafast", 0);
            av_dict_set(&param, "tune", "zero-latency", 0);
        }

        //Show some Information
        av_dump_format(pFormatCtx, 0, out_file, 1);

        pCodec = avcodec_find_encoder(pCodecCtx->codec_id);
        if (!pCodec){
            printf("Can not find encoder! \n");
            return -1;
        }
        if (avcodec_open2(pCodecCtx, pCodec,&param) < 0){
            printf("Failed to open encoder! \n");
            return -1;
        }


        pFrame = av_frame_alloc();
        picture_size = avpicture_get_size(pCodecCtx->pix_fmt, pCodecCtx->width, pCodecCtx->height);
        picture_buf = (uint8_t *)av_malloc(picture_size);
        avpicture_fill((AVPicture *)pFrame, picture_buf, pCodecCtx->pix_fmt, pCodecCtx->width, pCodecCtx->height);

        //Write File Header
        avformat_write_header(pFormatCtx,NULL);

        av_new_packet(&pkt,picture_size);
}
int Mp4Encoder::yuv2h264_stop() {
    //Flush Encoder
    int ret = flush_encoder(pFormatCtx,0);
    if (ret < 0) {
        printf("Flushing encoder failed\n");
        return -1;
    }
    printf("Line:%d %s()", __LINE__, __FUNCTION__);
    //Write file trailer
    av_write_trailer(pFormatCtx);

    //Clean
    if (video_st){
        avcodec_close(video_st->codec);
        av_free(pFrame);
        av_free(picture_buf);
    }
    printf("Line:%d %s()", __LINE__, __FUNCTION__);
    avio_close(pFormatCtx->pb);
    avformat_free_context(pFormatCtx);
    printf("Line:%d %s()", __LINE__, __FUNCTION__);
}

int i = 0;
int Mp4Encoder::yuv2h264_encode(uint8_t* picture_buf, const int size, int64_t msec) {
    int y_size = pCodecCtx->width * pCodecCtx->height;
    pFrame->data[0] = picture_buf;              // Y
    pFrame->data[1] = picture_buf+ y_size;      // U
    pFrame->data[2] = picture_buf+ y_size*5/4;  // V
    //PTS
    //pFrame->pts=i;
    pFrame->pts=i*(video_st->time_base.den)/((video_st->time_base.num)*25);
    i++;
    int got_picture=0;
    //Encode
    int ret = avcodec_encode_video2(pCodecCtx, &pkt,pFrame, &got_picture);
    if(ret < 0){
        printf("Failed to encode! \n");
        return -1;
    }
    if (got_picture==1){
        printf("Succeed to encode tsize:%5d\n",pkt.size);
        pkt.stream_index = video_st->index;
        ret = av_write_frame(pFormatCtx, &pkt);
        av_free_packet(&pkt);
    }
}

int Mp4Encoder::h2642mp4(const char *in_filename_v_, const char *out_filename_) {
    AVOutputFormat *ofmt = NULL;
        //Input AVFormatContext and Output AVFormatContext
        AVFormatContext *ifmt_ctx_v = NULL, *ifmt_ctx_a = NULL, *ofmt_ctx = NULL;
        AVPacket pkt;
        int ret, i;
        int videoindex_v = 0, videoindex_out = 0;
        int frame_index = 0;
        int64_t cur_pts_v = 0, cur_pts_a = 0;
//        const char *in_filename_v = "D:\\vs\\test.h264";
        const char *in_filename_v = in_filename_v_;
//        const char *out_filename = "D:\\vs\\test.mp4";//Output file URL
        const char *out_filename = out_filename_;
        av_register_all();
        //Input
        if ((ret = avformat_open_input(&ifmt_ctx_v, in_filename_v, 0, 0)) < 0) {
            printf("Could not open input file.");
            goto end;

        }
        if ((ret = avformat_find_stream_info(ifmt_ctx_v, 0)) < 0) {
            printf("Failed to retrieve input stream information");
            goto end;
        }

        printf("===========Input Information==========\n");
        av_dump_format(ifmt_ctx_v, 0, in_filename_v, 0);
        //av_dump_format(ifmt_ctx_a, 0, in_filename_a, 0);
        printf("======================================\n");
        //Output
        ret = avformat_alloc_output_context2(&ofmt_ctx, NULL, NULL, out_filename);
        if (!ofmt_ctx) {
            printf("Could not create output context\n");
            ret = AVERROR_UNKNOWN;
            goto end;
        }
        ofmt = ofmt_ctx->oformat;
        printf("ifmt_ctx_v->nb_streams=%d\n", ifmt_ctx_v->nb_streams);
        for (i = 0; i < ifmt_ctx_v->nb_streams; i++) {
            //Create output AVStream according to input AVStream
            //if(ifmt_ctx_v->streams[i]->codec->codec_type==AVMEDIA_TYPE_VIDEO)
            {
                AVStream *in_stream = ifmt_ctx_v->streams[i];
                AVStream *out_stream = avformat_new_stream(ofmt_ctx, in_stream->codec->codec);
                videoindex_v = i;
                if (!out_stream) {
                    printf("Failed allocating output stream\n");
                    ret = AVERROR_UNKNOWN;
                    goto end;
                }
                videoindex_out = out_stream->index;
                //Copy the settings of AVCodecContext
                if (avcodec_copy_context(out_stream->codec, in_stream->codec) < 0) {
                    printf("Failed to copy context from input to output stream codec context\n");
                    goto end;
                }
                out_stream->codec->codec_tag = 0;
                if (ofmt_ctx->oformat->flags & AVFMT_GLOBALHEADER)
                    out_stream->codec->flags |= AV_CODEC_FLAG_GLOBAL_HEADER;
                //break;
            }
        }

        printf("==========Output Information==========\n");
        av_dump_format(ofmt_ctx, 0, out_filename, 1);
        printf("======================================\n");
        //Open output file
        if (!(ofmt->flags & AVFMT_NOFILE)) {
            if (avio_open(&ofmt_ctx->pb, out_filename, AVIO_FLAG_WRITE) < 0) {
                printf("Could not open output file '%s'", out_filename);
                goto end;
            }
        }
        //Write file header
        if (avformat_write_header(ofmt_ctx, NULL) < 0) {
            printf("Error occurred when opening output file\n");
            goto end;
        }

        while (1) {
            AVFormatContext *ifmt_ctx;
            int stream_index = 0;
            AVStream *in_stream, *out_stream;
            //Get an AVPacket
            //if(av_compare_ts(cur_pts_v,ifmt_ctx_v->streams[videoindex_v]->time_base,cur_pts_a,ifmt_ctx_a->streams[audioindex_a]->time_base) <= 0)
            {
                ifmt_ctx = ifmt_ctx_v;
                stream_index = videoindex_out;
                if (av_read_frame(ifmt_ctx, &pkt) >= 0) {
                    do {
                        in_stream = ifmt_ctx->streams[pkt.stream_index];
                        out_stream = ofmt_ctx->streams[stream_index];
                        printf("stream_index==%d,pkt.stream_index==%d,videoindex_v=%d\n", stream_index, pkt.stream_index, videoindex_v);
                        if (pkt.stream_index == videoindex_v) {
                            //FIX：No PTS (Example: Raw H.264)
                            //Simple Write PTS
                            if (pkt.pts == AV_NOPTS_VALUE) {
                                printf("frame_index==%d\n", frame_index);
                                //Write PTS
                                AVRational time_base1 = in_stream->time_base;
                                //Duration between 2 frames (us)
                                int64_t calc_duration = (double)AV_TIME_BASE / av_q2d(in_stream->r_frame_rate);
                                //Parameters
                                pkt.pts = (double)(frame_index*calc_duration) / (double)(av_q2d(time_base1)*AV_TIME_BASE);
                                pkt.dts = pkt.pts;
                                pkt.duration = (double)calc_duration / (double)(av_q2d(time_base1)*AV_TIME_BASE);
                                frame_index++;
                            }
                            cur_pts_v = pkt.pts;
                            break;
                        }
                    } while (av_read_frame(ifmt_ctx, &pkt) >= 0);
                }
                else {
                    break;
                }
            }

            //Convert PTS/DTS
            pkt.pts = av_rescale_q_rnd(pkt.pts, in_stream->time_base, out_stream->time_base, (AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
            pkt.dts = av_rescale_q_rnd(pkt.dts, in_stream->time_base, out_stream->time_base, (AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
            pkt.duration = av_rescale_q(pkt.duration, in_stream->time_base, out_stream->time_base);
            pkt.pos = -1;
            pkt.stream_index = stream_index;
            printf("Write 1 Packet. size:%5d\tpts:%lld\n", pkt.size, pkt.pts);
            //Write
            if (av_interleaved_write_frame(ofmt_ctx, &pkt) < 0) {
                printf("Error muxing packet\n");
                break;
            }
            av_free_packet(&pkt);
        }
        //Write file trailer
        av_write_trailer(ofmt_ctx);

    end:
        avformat_close_input(&ifmt_ctx_v);
        //avformat_close_input(&ifmt_ctx_a);
        /* close output */
        if (ofmt_ctx && !(ofmt->flags & AVFMT_NOFILE))
            avio_close(ofmt_ctx->pb);
        avformat_free_context(ofmt_ctx);
        if (ret < 0 && ret != AVERROR_EOF) {
            printf("Error occurred.\n");
            return -1;
        }
        return 0;
}
