#ifndef XPLAY_DEF_H
#define XPLAY_DEF_H

#ifdef XPLAY_EXPORTS
#define XPLAY_API  extern "C" __declspec(dllexport) 

#else
#define XPLAY_API  extern "C" __declspec(dllimport)
#endif

#define X_MAX_DISPLAY_WND	5

enum MediaID
{
	DECODEC_ID_NONE = 0,	 //未知流类型	
	DECODEC_ID_H264 = 28,    //h264视频
	DECODEC_ID_PS = 29,      //ps封包格式的混合流
	DECODEC_ID_YUV = 100     //yuv数据，暂不支持
};

typedef enum
{
	X_DrawLib_GDI,
	X_DrawLib_DDRAW,
	X_DrawLib_D3D
}X_DRAWLIB;

typedef enum          
{
	X_Draw_RealTime,  //实时模式
	X_Draw_Balanced,  //均衡模式
	X_Draw_Fluent     //流畅模式
}X_DRAWDODE;

typedef enum		  //采用的绘图库
{
	X_STREAM_REALTIME,
	X_STREAM_FILE,
	X_LOCAL_FILE
}X_STREAMMODE;
/////////////
typedef enum
{
	X_AUDENC_G711A,        /* G.711 A率*/
	X_AUDENC_G711Mu,       /* G.711 Mu率*/
	X_AUDENC_G726,         /* hisilicon define as G.726 */
	X_AUDENC_ADPCM,        /* hisilicon define as ADPCM */
	X_AUDENC_ULAW,         /* mu-law */
	X_AUDENC_ALAW,         /* a-law */
	X_AUDENC_AAC,        /* AAC */
}X_EnumAudEncType;

typedef enum
{
	X_AUDIO_IN_TYPE_MIC,
	X_AUDIO_IN_TYPE_MAX	
}X_EnumAudInType;//音频输入类型

typedef enum
{
	X_DECTYPE_DEFAULT = 0,
	X_DECTYPE_CPU = 1,
	X_DECTYPE_IntelGpu = 2,
	X_DECTYPE_NvidiaGpu = 4
}X_DECTYPE;

typedef struct
{
	X_EnumAudInType       eInType;//目前只支持X_AUDIO_IN_TYPE_MIC
	X_EnumAudEncType      eEncType;
	int	nSamplesPerSec; //采样率，目前只支持8000
	int nBitsPerSample;//每个样点的位数，目前只支持16位
	int nBytesPerSec;   //码率，目前只支持16000
}X_AUDIO_PARA;

//#ifndef GXXMedia
typedef struct tag_GXXMedia_00
{
	DWORD dwMagicCode;//模数：'G','X','X','H'
	DWORD secCapTime;//采集时间 的秒部分
	DWORD usecCapTime;//采集时间 的微秒部分
}GXXMedia;
//#endif

typedef int XHANDLE;
#define INVALID_XHANDLE -1

typedef enum
{
	FRAME_INFO_TYPE_YUV420 = 0
}FRAME_INFO_TYPE;


struct X_FRAME_INFO{
	LONG nWidth;	//yuv数据宽度
	LONG nHeight;   //yuv数据高度
	LONG nStamp;    //帧的采集时间 单位为毫秒
	LONG nType;     //帧类型I_FRAME = 0,P_FRAME = 1,G711A_FRAME = 4
	LONG nFrameRate;//帧率，目前默认为25帧
};

// Description:yuv数据回调函数类型
// Parameters:
//	[in] handle: 播放句柄
//	[in] pBuf: yuv数据首地址
//	[in] nSize: yuv数据长度
//	[in] pFrameInfo: 帧信息
//	[in] pUser: 用户数据
typedef void (CALLBACK* fDecodeCBFun)(int handle,
								   char  *pBuf,
								   LONG  nSize,
								   X_FRAME_INFO  *pFrameInfo,
								   void*  pUser,
								   LONG  nReserved1
								   );

typedef enum
{
	QUERY_INFO_TYPE_TIME = 0, //数据内容: unsigned long long
	QUERY_INFO_TYPE_MEDIA = 1, //数据内容: X_MEDIA_INFO
	QUERY_INFO_TYPE_CalcData = 2, //数据内容: X_MEDIA_CalcData
	QUERY_INFO_TYPE_PlayerInfo = 3, //数据内容: X_MEDIA_CalcData
}QUERY_INFO_TYPE;

typedef struct{
	LONG lWidth;
	LONG lHeight;
	LONG lFrameRate;
	LONG lChannel;
	LONG lBitPerSample;
	LONG lSamplesPerSec;
}X_MEDIA_INFO;

typedef struct{
	int CodeID;
	int iBitRate;
	float fFrameRate;
}X_MEDIA_CalcData;

typedef struct {
	char szDecoderName[16];
	char szRendererName[16];
}X_MEDIA_PlayerInfo;

struct CRectD
{
	double    left;
	double    top;
	double    right;
	double    bottom;

	inline BOOL IsRectEmpty()
	{
		return (left == 0 && right == 0 && top == 0 && bottom == 0);
	}
	inline BOOL SetRect(double left, double top, double right, double botom)
	{
		left = left;
		top = top;
		right = right;
		botom = botom;

		return TRUE;
	}
};

//OSD叠加回调函数类型
typedef void (CALLBACK* fDrawCBFun)(int handle, HDC hdc, void* pUser);

//OSD叠加回调函数类型，增加帧时间参数
typedef void (CALLBACK* fDrawCBFun2)(int handle, HDC hdc, void* pUser, unsigned long long u64Time);
//////////////////////////////实时流播放接口///////////////////////////////////////////////////
// Description:打开实时流播放句柄
// Parameters:
//	[in] MediaID:暂时无效
//	[in] hWnd:显示视频的窗口句柄，不显示可以设为NULL
//	[in] DrawMode:显示模式，取值见X_DRAWDODE说明
// Return:失败返回-1, 成功返回实时频流句柄
XPLAY_API XHANDLE X_VideoOpen(MediaID mid,int hWnd,X_DRAWDODE DrawMode);

// Description:打开流播放句柄
// Parameters:
//	[in] StreamMode: 流模式，取值见X_STREAMMODE说明
//	[in] DrawMode: 显示模式，取值见X_DRAWDODE说明
// Return:// Return: 成功返回大于等于0，表示流播放句柄; 失败返回-1
XPLAY_API XHANDLE X_OpenStream(X_STREAMMODE StreamMode ,X_DRAWDODE DrawMode);

// Description:打开流播放句柄
// Parameters:
//	[in] StreamMode: 流模式，取值见X_STREAMMODE说明
//	[in] DrawMode: 显示模式，取值见X_DRAWDODE说明
//  [in] iDecType: 解码器类型，取值见X_DECTYPE说明
// Return:// Return: 成功返回大于等于0，表示流播放句柄; 失败返回-1
XPLAY_API XHANDLE X_OpenStream2(X_STREAMMODE StreamMode, X_DRAWDODE DrawMode, X_DECTYPE DecType);

// Description:播放接口
// Parameters:
// [in] hWnd:显示视频的窗口句柄
// Return:成功返回TRUE, 失败返回FALSE
XPLAY_API BOOL X_PlayEx(XHANDLE handle, HWND hWnd);


// Description:输入流数据到播放库
// Parameters:
//	[in] handle: 播放句柄
//	[in] pBuf：流数据首地址
//	[in] nLen: 流数据长度
// Return: 成功返回0; 失败返回-1,表示缓冲已满，可以稍后再试
XPLAY_API int X_VideoInputData(XHANDLE handle,BYTE *pBuf,int nLen);

// Description:输入流数据到播放库第二代接口
// Parameters:
//	[in] handle: 播放句柄
//	[in] pBuf：流数据首地址
//	[in] nLen: 流数据长度
//  [in] u64Time: 时间戳
// Return: 成功返回0; 失败返回-1,表示缓冲已满，可以稍后再试
XPLAY_API int X_VideoInputData2(XHANDLE handle,BYTE *pBuf,int nLen, UINT64 u64Time);

// Description:关闭实时流播放句柄
// Parameters:
//	[in] handle: 播放句柄
// Return:成功返回0;失败返回-1 
XPLAY_API int X_VideoClose(XHANDLE handle);

// Description:开启或者关闭音频
// Parameters:
//	[in] handle:X_VideoOpen的返回值
//	[in] bOpenVoice:true 表示开启音频，false表示关闭音频	
// Return: 成功返回0; 失败返回-1
XPLAY_API int X_VideoCtrl(XHANDLE handle,bool bOpenVoice);

// Description:抓图
// Parameters:
//	[in] handle: 播放句柄
//	[in] sPicFileName: 文件名，需要全路径
// Return:成功返回TRUE;失败返回FALSE
XPLAY_API BOOL X_Snapshot(XHANDLE handle, const char *sPicFileName);

// Description:抓图，X_Snapshot的扩展接口
// Parameters:
//	[in] handle: 播放句柄
//	[in] sPicFileName: 文件名，需要全路径
//	[in] nPicType：0表示保存BMP格式，1表示保存JPG格式
// Return:成功返回TRUE;失败返回FALSE
XPLAY_API BOOL X_CapturePicture(XHANDLE handle, const char *sPicFileName,int nPicType);

// Description:YUV数据回调设置接口，只解码回调，不显示视频
// Parameters:
//	[in] handle: 播放句柄
//	[in] DecodeCBFun: YUV数据回调函数
//	[in] pUser：用户数据，回调时返回给用户
// Return: 成功返回TRUE;失败返回FALSE
XPLAY_API BOOL X_SetDecCallBack(XHANDLE handle,fDecodeCBFun DecodeCBFun,void* pUser);

// Description:YUV数据回调设置接口，解码回调，同时显示视频
// Parameters:
//	[in] handle: 播放句柄
//	[in] DecodeCBFun: YUV数据回调函数
//	[in] pUser：用户数据，回调时返回给用户
// Return: 成功返回TRUE;失败返回FALSE
XPLAY_API BOOL X_SetVisibleDecCallBack(XHANDLE handle,fDecodeCBFun DecodeCBFun,void* pUser);

// Description:查询帧信息接口
// Parameters:
//	[in] handle: 播放句柄
//	[in] DecodeCBFun: YUV数据回调函数
//	[in] pUser：用户数据，回调时返回给用户
// Return: 成功返回TRUE;失败返回FALSE
XPLAY_API BOOL X_QueryInfo(XHANDLE handle,int InfoType,BYTE *pBuf,int nLen,int *nRetLen);

// Description:OSD叠加回调设置接口
// Parameters:
//	[in] handle: 播放句柄
//	[in] DecodeCBFun: OSD叠加回调函数
//	[in] pUser：用户数据，回调时返回给用户
// Return: 成功返回TRUE;失败返回FALSE
XPLAY_API BOOL X_SetDrawFun(XHANDLE handle,fDrawCBFun DrawCBFun,void* pUser);

// Description:OSD叠加回调设置接口二，比X_SetDrawFun回调增加帧时间参数
// Parameters:
//	[in] handle: 播放句柄
//	[in] DecodeCBFun: OSD叠加回调函数
//	[in] pUser：用户数据，回调时返回给用户
// Return: 成功返回TRUE;失败返回FALSE
XPLAY_API BOOL X_SetDrawFun2(XHANDLE handle, fDrawCBFun2 DrawCBFun, void* pUser);

//设置绘图库，旧接口，现在调用不起作用
XPLAY_API int SetDrawLib(XHANDLE handle,int nDrawLib);

// Description:获取视频分辨率接口
// Parameters:
//	[in] handle: 播放句柄
//	[in] pWidth: 用来获取YUV数据宽度
//	[in] pHeight：用来获取YUV数据高度
// Return: 成功返回TRUE;失败返回FALSE
XPLAY_API BOOL X_GetVideoSize(XHANDLE handle,int *pWidth,int *pHeight);

// Description:加倍播放接口
// Parameters:
//	[in] handle: 播放句柄
// Return: 成功返回TRUE;失败返回FALSE
XPLAY_API BOOL X_Fast(XHANDLE handle);

// Description:减倍播放接口
// Parameters:
//	[in] handle: 播放句柄
// Return:成功返回TRUE, 失败返回FALSE
XPLAY_API BOOL X_Slow(XHANDLE handle);

// Description:直接设置播放速度接口
// Parameters:
//	[in] handle: 播放句柄
//  [in]  dSpeed 播放倍数，大于1表示快放，小于1表示慢放
// Return: 成功返回TRUE;失败返回FALSE
XPLAY_API BOOL X_SetPlaySpeed(XHANDLE handle,double dSpeed);

// Description:播放接口
// Parameters:
//	[in] handle: 播放句柄
// Return: 成功返回TRUE;失败返回FALSE
XPLAY_API BOOL X_Play(XHANDLE handle);

// Description:暂停接口
// Parameters:
//	[in] handle:播放句柄
// Return: 成功返回TRUE;失败返回FALSE
XPLAY_API BOOL X_Pause(XHANDLE handle);

//////////////////////////////音频接口///////////////////////////////////////////////////
// 功能:设置音量
// 参数
//	[in] dwVolume：0到 0xffff
// 返回: 成功返回TRUE, 失败返回FALSE
XPLAY_API BOOL X_SetVolume(XHANDLE handle,DWORD dwVolume);

// Description:打开音频流播放句柄
// Parameters:
//	[in] para：音频参数，见X_AUDIO_PARA说明
// Return: 成功返回大于等于0，表示音频播放句柄; 失败返回-1
XPLAY_API XHANDLE X_AudioOpen(X_AUDIO_PARA para);

// Description:输入音频流数据到播放库
// Parameters:
//	[in] handle: 音频播放句柄
//	[in] pBuf：流数据首地址
//	[in] nLen: 流数据长度
// Return:成功返回0; 失败返回-1
XPLAY_API int X_AudioInputData(XHANDLE handle,BYTE *pBuf,int nLen);

// Description:关闭音频播放句柄
// Parameters:
//	[in] handle: 音频播放句柄
// Return:成功返回0; 失败返回-1
XPLAY_API int X_AudioClose(XHANDLE handle);

// Description:音频采集回调函数类型
// Parameters:
//	[in] pBuffer: 音频数据首地址
//	[in] dwBufSize: 音频数据大小
//	[in] pUser: 用户数据
// Return: 无
typedef void (CALLBACK *fVoiceDataCallBack)(char *pBuffer, DWORD dwBufSize,void* pUser);

// Description:打开音频采集句柄
// Parameters:
//	[in] pBuffer: 音频数据首地址
//	[in] cbVoice: 音频数据回调函数
//	[in] pUser: 用户数据，回调时返回给用户
// Return: 成功返回大于等于0，表示音频采集句柄; 失败返回-1
XPLAY_API XHANDLE X_AudioCaptureOpen(X_AUDIO_PARA param,fVoiceDataCallBack cbVoice,void* pUser);

// Description:关闭音频采集句柄
// Parameters:
//	[in] handle: 音频采集句柄
// Return: 成功返回0; 失败返回-1
XPLAY_API int X_AudioCaptureClose(XHANDLE handle);

/////////////////////////////文件播放专用接口////////////////////////////////////////////////////
// Description:打开文件播放句柄（此接口只支持文件播放）
// Parameters:
//	[in] strFileName:媒体文件名
//	[in] hWnd:显示视频的窗口句柄，不显示可以设为NULL
// Return: 成功返回大于等于0，表示文件播放句柄; 失败返回-1
XPLAY_API XHANDLE X_FileOpen(char *strFileName,int hWnd);

// Description:设置文件播放位置（此接口只支持文件播放）
// Parameters:
//  [in] handle: 文件播放句柄
//	[in] dPos: 播放位置相对于文件总长度的比值，文件开始位置为0，文件结束位置为1
// Return: 成功返回TRUE; 失败返回FALSE
XPLAY_API BOOL X_SetPlayPos(XHANDLE handle,double dPos);

// Description:获取文件播放位置（此接口只支持文件播放）
// Parameters:
//  [in] handle: 文件播放句柄
// Return:，播放位置相对于文件总长度的比值，文件开始位置为0，文件结束位置为1
XPLAY_API double X_GetPlayPos(XHANDLE handle);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Description:增加或者修改显示区域,可以实现多窗口显示或局部放大显示
// Parameters:
//  [in]  nRegionNum: 显示区域编号
//  [in]  pSrcRect: 裁剪矩形，相对于YUV数据的坐标
//  [in]  hDestWnd: 显示窗口的句柄
//  [in]  bEnable:  TURE表示开启显示区域，FALSE表示关闭显示区域
// Return： 成功返回TRUE; 失败返回FALSE
XPLAY_API BOOL X_SetDisplayRegion(XHANDLE handle,DWORD nRegionNum, CRectD *pSrcRect,HWND hDestWnd,BOOL bEnable);

// Description:设置视频参数
// Parameters:
//	[in]nRegionNum: 显示区域,这里目前未用
//	[in]nBrightness: 亮度,默认为;范围0-128
//  [in]nContrast: 对比度,默认为;范围0-128
//  [in]nSaturation: 饱和度,默认为;范围0-128 
//  [in]nHue: 色调,默认为;范围0-128 
// Return：成功返回TRUE; 失败返回FALSE
XPLAY_API BOOL X_SetColor(XHANDLE handle, DWORD nRegionNum, int nBrightness, int nContrast, int nSaturation, int nHue);

// Description:设置视频参数
// Parameters:
//	[in]nRegionNum: 显示区域,这里目前未用。
//	[in]nBrightness: 亮度,默认为64;范围0-128
//  [in]nContrast: 对比度,默认为64;范围0-128
//  [in]nSaturation: 饱和度,默认为64;范围0-128 
//  [in]nHue: 色调,默认为64;范围0-128 
// Return：成功返回TRUE; 失败返回FALSE 
XPLAY_API BOOL X_GetColor(XHANDLE handle, DWORD nRegionNum,int *nBrightness,int *nContrast, int *nSaturation, int *nHue);

// Description:设置视频参数
// Parameters:
//	[in] handle: 文件播放句柄 
// Return：文件总的时间长度值,单位为毫秒
XPLAY_API DWORD X_GetFileTime(XHANDLE handle);

// Description: 获取帧率
// Parameters:
//	[in] handle: 文件播放句柄 
// Return：帧率
XPLAY_API DWORD X_GetFrameRate(XHANDLE handle);

// Description: 设置当前文件播放时间
// Parameters:
//	[in] handle: 文件播放句柄
//	[in] nTime: 开始播放的位置,单位为毫秒
// return: 成功返回TRUE; 失败返回FALSE
XPLAY_API BOOL X_SetPlayedTime(XHANDLE handle,DWORD nTime);

// Description: 获取当前文件播放时间
// Parameters:
//	[in] handle: 文件播放句柄
// return: 文件当前播放的时间,单位毫秒
XPLAY_API DWORD X_GetPlayedTime(XHANDLE handle);

// Description：设置文件播放结束消息
// Parameters:
//  [in] handle: 文件播放句柄
//  [in] hWnd: 消息接收的窗口
//  [in] nMsg: 用户自定义的输入消息，当播放到文件结束时用户在hWnd窗口过程中收到这个消息。
//			此消息中的wParam或者lParam都可以获得handle的值
// return: 成功返回TRUE; 失败返回FALSE
XPLAY_API BOOL X_SetFileEndMsg(XHANDLE handle,HWND hWnd,UINT nMsg);

//Description: 文件结束回调类型
// Parameters：
// [in] handle: 文件播放句柄
// [in] pUser：对应用户自定义参数
// return: 无
typedef void (CALLBACK* X_FileEndCBFun)(XHANDLE handle,void* pUser);

//Description：设置文件播放结束回调函数
// Parameters：
//  [in] handle: 文件播放句柄
//  [in] pFileEndCBFun: 文件结束回调函数
//  [in] pUser: 用户自定义参数
// return: 成功返回TRUE; 失败返回FALSE
XPLAY_API BOOL X_SetFileEndCallBack(XHANDLE handle,X_FileEndCBFun FileEndCBFun,void* pUser);


struct CXPoint
{
	FLOAT x, y;
};
XPLAY_API int X_CreatePicture(XHANDLE handle, void* pSrcData,UINT  SrcDataSize,	COLORREF TransparentColor, RECT* pSrcRect, 
				  CXPoint* pScaling, CXPoint* pRotationCenter, 	FLOAT Rotation,  CXPoint* pTranslation, DWORD Transparency);
XPLAY_API int X_DeletePicture(XHANDLE handle, int hPicture);


// Description：设置视频绘图方式（必须在播放句柄打开前设置才有效，已经打开的播放句柄需要重新打开才生效）
// Parameters：
//  [in] nDrawLib: 绘图方式
// return: 成功返回TRUE; 失败返回FALSE
XPLAY_API BOOL X_SetDrawLib(X_DRAWLIB nDrawLib);

// Description：设置视频垂直同步（GDI绘图方式不支持配置）
// Parameters：
//  [in] bEnable: TRUE表示开启，FALSE表示关闭
// return: 成功返回TRUE; 失败返回FALSE
XPLAY_API BOOL X_SetVerticalSync(BOOL bEnable);

enum X_BmpMode
{
	X_BmpMode_NONE = 0,
	X_BmpMode_YUV420 = 1,
	X_BmpMode_D3D11Texture = 2
};
struct X_INIT_PARAM
{
	unsigned int uiGetBmpMode; // 获取解码后的位图的方式，见X_BmpMode；支持多种时，选项按位或后赋值此参数。
};
XPLAY_API int X_Init(X_INIT_PARAM ini);


//Description:YUV转BMP数据
// Parameters:
// [in] pYUVBuf:YUV数据
// [in] nWidth:YUV图像的宽
// [in] nHeight:YUV图像的高
// [out] pRGBBuf:转换成的RGB数据
// [in/out] nRGBBufLen:传入pRGBBuf的数据长度，传出RGBbuf的实际长度，
//					   若长度不够返回FALSE并传出实际需要的长度
// Return：成功返回TRUE; 失败返回FALSE
XPLAY_API BOOL X_YUV2BMP(BYTE *pYUVBuf, int nWidth, int nHeight, BYTE *pRGBBuf, int *nRGBBufLen);

//功能：清除播放缓冲
//参数说明
// [in] handle：视频播放句柄
// Return：成功返回TRUE; 失败返回FALSE
XPLAY_API BOOL X_ClearPlayBuffer(XHANDLE handle);

//功能：获取RGB24位图
//参数说明
// [in] handle：视频播放句柄
// [in] pBuf：缓冲区
// [in/out] piSize: 输入表示pBuf的缓冲大小，输出表示数据大小
// [out] piWidth: 返回视频宽
// [out] piHeight: 返回视频高
// Return：成功返回TRUE; 失败返回FALSE
XPLAY_API int X_GetBmp(XHANDLE handle, char *pBuf, int *piSize, int *piWidth, int *piHeight);

//功能：获取RGB24位图 第二代接口
//参数说明
// [in] handle：视频播放句柄
// [in] pBuf：缓冲区
// [in/out] piSize: 输入表示pBuf的缓冲大小，输出表示数据大小
// [out] piWidth: 返回视频宽
// [out] piHeight: 返回视频高
// [out] pu64Time: 帧的时间戳
// Return：成功返回TRUE; 失败返回FALSE
XPLAY_API int X_GetBmp2(XHANDLE handle, char *pBuf, int *piSize, int *piWidth, int *piHeight, UINT64 *pu64Time);

struct X_DecoderCfg
{
	int iNvdCount;  // 英伟达解码的路数
	int iImsCount;  // Intel解码的路数
	int bDecoderRender; //1表示解码插件内部渲染，0表示解码插件外部渲染
	int iDrawLibNo;   //绘图库 0;gdi, 1:ddraw, 2：d3d

	int iBufSize; //解码前的视频缓冲大小，单位是KB, 默认是5M
	int	iDelayTimeMs; // 平滑播放视频时的延时，单位是毫秒

	int iLogLevel; // LFATAL:5 LERROR : 4 LWARN : 3 LINFO : 2 LDEBUG : 1 ； 设置成1打印的日志最多，5最少
};

XPLAY_API int X_SetDecoderCfg(X_DecoderCfg *pCfg);
XPLAY_API int X_GetDecoderCfg(X_DecoderCfg *pCfg);

XPLAY_API int X_GetAvailableDecoder(unsigned int *pMark);

#endif