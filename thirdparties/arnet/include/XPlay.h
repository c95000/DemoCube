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
	DECODEC_ID_NONE = 0,	 //δ֪������	
	DECODEC_ID_H264 = 28,    //h264��Ƶ
	DECODEC_ID_PS = 29,      //ps�����ʽ�Ļ����
	DECODEC_ID_YUV = 100     //yuv���ݣ��ݲ�֧��
};

typedef enum
{
	X_DrawLib_GDI,
	X_DrawLib_DDRAW,
	X_DrawLib_D3D
}X_DRAWLIB;

typedef enum          
{
	X_Draw_RealTime,  //ʵʱģʽ
	X_Draw_Balanced,  //����ģʽ
	X_Draw_Fluent     //����ģʽ
}X_DRAWDODE;

typedef enum		  //���õĻ�ͼ��
{
	X_STREAM_REALTIME,
	X_STREAM_FILE,
	X_LOCAL_FILE
}X_STREAMMODE;
/////////////
typedef enum
{
	X_AUDENC_G711A,        /* G.711 A��*/
	X_AUDENC_G711Mu,       /* G.711 Mu��*/
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
}X_EnumAudInType;//��Ƶ��������

typedef enum
{
	X_DECTYPE_DEFAULT = 0,
	X_DECTYPE_CPU = 1,
	X_DECTYPE_IntelGpu = 2,
	X_DECTYPE_NvidiaGpu = 4
}X_DECTYPE;

typedef struct
{
	X_EnumAudInType       eInType;//Ŀǰֻ֧��X_AUDIO_IN_TYPE_MIC
	X_EnumAudEncType      eEncType;
	int	nSamplesPerSec; //�����ʣ�Ŀǰֻ֧��8000
	int nBitsPerSample;//ÿ�������λ����Ŀǰֻ֧��16λ
	int nBytesPerSec;   //���ʣ�Ŀǰֻ֧��16000
}X_AUDIO_PARA;

//#ifndef GXXMedia
typedef struct tag_GXXMedia_00
{
	DWORD dwMagicCode;//ģ����'G','X','X','H'
	DWORD secCapTime;//�ɼ�ʱ�� ���벿��
	DWORD usecCapTime;//�ɼ�ʱ�� ��΢�벿��
}GXXMedia;
//#endif

typedef int XHANDLE;
#define INVALID_XHANDLE -1

typedef enum
{
	FRAME_INFO_TYPE_YUV420 = 0
}FRAME_INFO_TYPE;


struct X_FRAME_INFO{
	LONG nWidth;	//yuv���ݿ��
	LONG nHeight;   //yuv���ݸ߶�
	LONG nStamp;    //֡�Ĳɼ�ʱ�� ��λΪ����
	LONG nType;     //֡����I_FRAME = 0,P_FRAME = 1,G711A_FRAME = 4
	LONG nFrameRate;//֡�ʣ�ĿǰĬ��Ϊ25֡
};

// Description:yuv���ݻص���������
// Parameters:
//	[in] handle: ���ž��
//	[in] pBuf: yuv�����׵�ַ
//	[in] nSize: yuv���ݳ���
//	[in] pFrameInfo: ֡��Ϣ
//	[in] pUser: �û�����
typedef void (CALLBACK* fDecodeCBFun)(int handle,
								   char  *pBuf,
								   LONG  nSize,
								   X_FRAME_INFO  *pFrameInfo,
								   void*  pUser,
								   LONG  nReserved1
								   );

typedef enum
{
	QUERY_INFO_TYPE_TIME = 0, //��������: unsigned long long
	QUERY_INFO_TYPE_MEDIA = 1, //��������: X_MEDIA_INFO
	QUERY_INFO_TYPE_CalcData = 2, //��������: X_MEDIA_CalcData
	QUERY_INFO_TYPE_PlayerInfo = 3, //��������: X_MEDIA_CalcData
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
	inline BOOL SetRect(double dleft, double dtop, double dright, double dbotom)
	{
		left = dleft;
		top = dtop;
		right = dright;
		bottom = dbotom;

		return TRUE;
	}
};

//OSD���ӻص���������
typedef void (CALLBACK* fDrawCBFun)(int handle, HDC hdc, void* pUser);

//OSD���ӻص��������ͣ�����֡ʱ�����
typedef void (CALLBACK* fDrawCBFun2)(int handle, HDC hdc, void* pUser, unsigned long long u64Time);
//////////////////////////////ʵʱ�����Žӿ�///////////////////////////////////////////////////
// Description:��ʵʱ�����ž��
// Parameters:
//	[in] MediaID:��ʱ��Ч
//	[in] hWnd:��ʾ��Ƶ�Ĵ��ھ��������ʾ������ΪNULL
//	[in] DrawMode:��ʾģʽ��ȡֵ��X_DRAWDODE˵��
// Return:ʧ�ܷ���-1, �ɹ�����ʵʱƵ�����
XPLAY_API XHANDLE X_VideoOpen(MediaID mid,int hWnd,X_DRAWDODE DrawMode);

// Description:�������ž��
// Parameters:
//	[in] StreamMode: ��ģʽ��ȡֵ��X_STREAMMODE˵��
//	[in] DrawMode: ��ʾģʽ��ȡֵ��X_DRAWDODE˵��
// Return:// Return: �ɹ����ش��ڵ���0����ʾ�����ž��; ʧ�ܷ���-1
XPLAY_API XHANDLE X_OpenStream(X_STREAMMODE StreamMode ,X_DRAWDODE DrawMode);

// Description:�������ž��
// Parameters:
//	[in] StreamMode: ��ģʽ��ȡֵ��X_STREAMMODE˵��
//	[in] DrawMode: ��ʾģʽ��ȡֵ��X_DRAWDODE˵��
//  [in] iDecType: ���������ͣ�ȡֵ��X_DECTYPE˵��
// Return:// Return: �ɹ����ش��ڵ���0����ʾ�����ž��; ʧ�ܷ���-1
XPLAY_API XHANDLE X_OpenStream2(X_STREAMMODE StreamMode, X_DRAWDODE DrawMode, X_DECTYPE DecType);

// Description:���Žӿ�
// Parameters:
// [in] hWnd:��ʾ��Ƶ�Ĵ��ھ��
// Return:�ɹ�����TRUE, ʧ�ܷ���FALSE
XPLAY_API BOOL X_PlayEx(XHANDLE handle, HWND hWnd);


// Description:���������ݵ����ſ�
// Parameters:
//	[in] handle: ���ž��
//	[in] pBuf���������׵�ַ
//	[in] nLen: �����ݳ���
// Return: �ɹ�����0; ʧ�ܷ���-1,��ʾ���������������Ժ�����
XPLAY_API int X_VideoInputData(XHANDLE handle,BYTE *pBuf,int nLen);

// Description:���������ݵ����ſ�ڶ����ӿ�
// Parameters:
//	[in] handle: ���ž��
//	[in] pBuf���������׵�ַ
//	[in] nLen: �����ݳ���
//  [in] u64Time: ʱ���
// Return: �ɹ�����0; ʧ�ܷ���-1,��ʾ���������������Ժ�����
XPLAY_API int X_VideoInputData2(XHANDLE handle,BYTE *pBuf,int nLen, UINT64 u64Time);

// Description:�ر�ʵʱ�����ž��
// Parameters:
//	[in] handle: ���ž��
// Return:�ɹ�����0;ʧ�ܷ���-1 
XPLAY_API int X_VideoClose(XHANDLE handle);

// Description:�������߹ر���Ƶ
// Parameters:
//	[in] handle:X_VideoOpen�ķ���ֵ
//	[in] bOpenVoice:true ��ʾ������Ƶ��false��ʾ�ر���Ƶ	
// Return: �ɹ�����0; ʧ�ܷ���-1
XPLAY_API int X_VideoCtrl(XHANDLE handle,bool bOpenVoice);

// Description:ץͼ
// Parameters:
//	[in] handle: ���ž��
//	[in] sPicFileName: �ļ�������Ҫȫ·��
// Return:�ɹ�����TRUE;ʧ�ܷ���FALSE
XPLAY_API BOOL X_Snapshot(XHANDLE handle, const char *sPicFileName);

// Description:ץͼ��X_Snapshot����չ�ӿ�
// Parameters:
//	[in] handle: ���ž��
//	[in] sPicFileName: �ļ�������Ҫȫ·��
//	[in] nPicType��0��ʾ����BMP��ʽ��1��ʾ����JPG��ʽ
// Return:�ɹ�����TRUE;ʧ�ܷ���FALSE
XPLAY_API BOOL X_CapturePicture(XHANDLE handle, const char *sPicFileName,int nPicType);

// Description:YUV���ݻص����ýӿڣ�ֻ����ص�������ʾ��Ƶ
// Parameters:
//	[in] handle: ���ž��
//	[in] DecodeCBFun: YUV���ݻص�����
//	[in] pUser���û����ݣ��ص�ʱ���ظ��û�
// Return: �ɹ�����TRUE;ʧ�ܷ���FALSE
XPLAY_API BOOL X_SetDecCallBack(XHANDLE handle,fDecodeCBFun DecodeCBFun,void* pUser);

// Description:YUV���ݻص����ýӿڣ�����ص���ͬʱ��ʾ��Ƶ
// Parameters:
//	[in] handle: ���ž��
//	[in] DecodeCBFun: YUV���ݻص�����
//	[in] pUser���û����ݣ��ص�ʱ���ظ��û�
// Return: �ɹ�����TRUE;ʧ�ܷ���FALSE
XPLAY_API BOOL X_SetVisibleDecCallBack(XHANDLE handle,fDecodeCBFun DecodeCBFun,void* pUser);

// Description:��ѯ֡��Ϣ�ӿ�
// Parameters:
//	[in] handle: ���ž��
//	[in] DecodeCBFun: YUV���ݻص�����
//	[in] pUser���û����ݣ��ص�ʱ���ظ��û�
// Return: �ɹ�����TRUE;ʧ�ܷ���FALSE
XPLAY_API BOOL X_QueryInfo(XHANDLE handle,int InfoType,BYTE *pBuf,int nLen,int *nRetLen);

// Description:OSD���ӻص����ýӿ�
// Parameters:
//	[in] handle: ���ž��
//	[in] DecodeCBFun: OSD���ӻص�����
//	[in] pUser���û����ݣ��ص�ʱ���ظ��û�
// Return: �ɹ�����TRUE;ʧ�ܷ���FALSE
XPLAY_API BOOL X_SetDrawFun(XHANDLE handle,fDrawCBFun DrawCBFun,void* pUser);

// Description:OSD���ӻص����ýӿڶ�����X_SetDrawFun�ص�����֡ʱ�����
// Parameters:
//	[in] handle: ���ž��
//	[in] DecodeCBFun: OSD���ӻص�����
//	[in] pUser���û����ݣ��ص�ʱ���ظ��û�
// Return: �ɹ�����TRUE;ʧ�ܷ���FALSE
XPLAY_API BOOL X_SetDrawFun2(XHANDLE handle, fDrawCBFun2 DrawCBFun, void* pUser);

//���û�ͼ�⣬�ɽӿڣ����ڵ��ò�������
XPLAY_API int SetDrawLib(XHANDLE handle,int nDrawLib);

// Description:��ȡ��Ƶ�ֱ��ʽӿ�
// Parameters:
//	[in] handle: ���ž��
//	[in] pWidth: ������ȡYUV���ݿ��
//	[in] pHeight��������ȡYUV���ݸ߶�
// Return: �ɹ�����TRUE;ʧ�ܷ���FALSE
XPLAY_API BOOL X_GetVideoSize(XHANDLE handle,int *pWidth,int *pHeight);

// Description:�ӱ����Žӿ�
// Parameters:
//	[in] handle: ���ž��
// Return: �ɹ�����TRUE;ʧ�ܷ���FALSE
XPLAY_API BOOL X_Fast(XHANDLE handle);

// Description:�������Žӿ�
// Parameters:
//	[in] handle: ���ž��
// Return:�ɹ�����TRUE, ʧ�ܷ���FALSE
XPLAY_API BOOL X_Slow(XHANDLE handle);

// Description:ֱ�����ò����ٶȽӿ�
// Parameters:
//	[in] handle: ���ž��
//  [in]  dSpeed ���ű���������1��ʾ��ţ�С��1��ʾ����
// Return: �ɹ�����TRUE;ʧ�ܷ���FALSE
XPLAY_API BOOL X_SetPlaySpeed(XHANDLE handle,double dSpeed);

// Description:���Žӿ�
// Parameters:
//	[in] handle: ���ž��
// Return: �ɹ�����TRUE;ʧ�ܷ���FALSE
XPLAY_API BOOL X_Play(XHANDLE handle);

// Description:��ͣ�ӿ�
// Parameters:
//	[in] handle:���ž��
// Return: �ɹ�����TRUE;ʧ�ܷ���FALSE
XPLAY_API BOOL X_Pause(XHANDLE handle);

//////////////////////////////��Ƶ�ӿ�///////////////////////////////////////////////////
// ����:��������
// ����
//	[in] dwVolume��0�� 0xffff
// ����: �ɹ�����TRUE, ʧ�ܷ���FALSE
XPLAY_API BOOL X_SetVolume(XHANDLE handle,DWORD dwVolume);

// Description:����Ƶ�����ž��
// Parameters:
//	[in] para����Ƶ��������X_AUDIO_PARA˵��
// Return: �ɹ����ش��ڵ���0����ʾ��Ƶ���ž��; ʧ�ܷ���-1
XPLAY_API XHANDLE X_AudioOpen(X_AUDIO_PARA para);

// Description:������Ƶ�����ݵ����ſ�
// Parameters:
//	[in] handle: ��Ƶ���ž��
//	[in] pBuf���������׵�ַ
//	[in] nLen: �����ݳ���
// Return:�ɹ�����0; ʧ�ܷ���-1
XPLAY_API int X_AudioInputData(XHANDLE handle,BYTE *pBuf,int nLen);

// Description:�ر���Ƶ���ž��
// Parameters:
//	[in] handle: ��Ƶ���ž��
// Return:�ɹ�����0; ʧ�ܷ���-1
XPLAY_API int X_AudioClose(XHANDLE handle);

// Description:��Ƶ�ɼ��ص���������
// Parameters:
//	[in] pBuffer: ��Ƶ�����׵�ַ
//	[in] dwBufSize: ��Ƶ���ݴ�С
//	[in] pUser: �û�����
// Return: ��
typedef void (CALLBACK *fVoiceDataCallBack)(char *pBuffer, DWORD dwBufSize,void* pUser);

// Description:����Ƶ�ɼ����
// Parameters:
//	[in] pBuffer: ��Ƶ�����׵�ַ
//	[in] cbVoice: ��Ƶ���ݻص�����
//	[in] pUser: �û����ݣ��ص�ʱ���ظ��û�
// Return: �ɹ����ش��ڵ���0����ʾ��Ƶ�ɼ����; ʧ�ܷ���-1
XPLAY_API XHANDLE X_AudioCaptureOpen(X_AUDIO_PARA param,fVoiceDataCallBack cbVoice,void* pUser);

// Description:�ر���Ƶ�ɼ����
// Parameters:
//	[in] handle: ��Ƶ�ɼ����
// Return: �ɹ�����0; ʧ�ܷ���-1
XPLAY_API int X_AudioCaptureClose(XHANDLE handle);

/////////////////////////////�ļ�����ר�ýӿ�////////////////////////////////////////////////////
// Description:���ļ����ž�����˽ӿ�ֻ֧���ļ����ţ�
// Parameters:
//	[in] strFileName:ý���ļ���
//	[in] hWnd:��ʾ��Ƶ�Ĵ��ھ��������ʾ������ΪNULL
// Return: �ɹ����ش��ڵ���0����ʾ�ļ����ž��; ʧ�ܷ���-1
XPLAY_API XHANDLE X_FileOpen(char *strFileName,int hWnd);

// Description:�����ļ�����λ�ã��˽ӿ�ֻ֧���ļ����ţ�
// Parameters:
//  [in] handle: �ļ����ž��
//	[in] dPos: ����λ��������ļ��ܳ��ȵı�ֵ���ļ���ʼλ��Ϊ0���ļ�����λ��Ϊ1
// Return: �ɹ�����TRUE; ʧ�ܷ���FALSE
XPLAY_API BOOL X_SetPlayPos(XHANDLE handle,double dPos);

// Description:��ȡ�ļ�����λ�ã��˽ӿ�ֻ֧���ļ����ţ�
// Parameters:
//  [in] handle: �ļ����ž��
// Return:������λ��������ļ��ܳ��ȵı�ֵ���ļ���ʼλ��Ϊ0���ļ�����λ��Ϊ1
XPLAY_API double X_GetPlayPos(XHANDLE handle);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Description:���ӻ����޸���ʾ����,����ʵ�ֶര����ʾ��ֲ��Ŵ���ʾ
// Parameters:
//  [in]  nRegionNum: ��ʾ������
//  [in]  pSrcRect: �ü����Σ������YUV���ݵ�����
//  [in]  hDestWnd: ��ʾ���ڵľ��
//  [in]  bEnable:  TURE��ʾ������ʾ����FALSE��ʾ�ر���ʾ����
// Return�� �ɹ�����TRUE; ʧ�ܷ���FALSE
XPLAY_API BOOL X_SetDisplayRegion(XHANDLE handle,DWORD nRegionNum, CRectD *pSrcRect,HWND hDestWnd,BOOL bEnable);

// Description:������Ƶ����
// Parameters:
//	[in]nRegionNum: ��ʾ����,����Ŀǰδ��
//	[in]nBrightness: ����,Ĭ��Ϊ;��Χ0-128
//  [in]nContrast: �Աȶ�,Ĭ��Ϊ;��Χ0-128
//  [in]nSaturation: ���Ͷ�,Ĭ��Ϊ;��Χ0-128 
//  [in]nHue: ɫ��,Ĭ��Ϊ;��Χ0-128 
// Return���ɹ�����TRUE; ʧ�ܷ���FALSE
XPLAY_API BOOL X_SetColor(XHANDLE handle, DWORD nRegionNum, int nBrightness, int nContrast, int nSaturation, int nHue);

// Description:������Ƶ����
// Parameters:
//	[in]nRegionNum: ��ʾ����,����Ŀǰδ�á�
//	[in]nBrightness: ����,Ĭ��Ϊ64;��Χ0-128
//  [in]nContrast: �Աȶ�,Ĭ��Ϊ64;��Χ0-128
//  [in]nSaturation: ���Ͷ�,Ĭ��Ϊ64;��Χ0-128 
//  [in]nHue: ɫ��,Ĭ��Ϊ64;��Χ0-128 
// Return���ɹ�����TRUE; ʧ�ܷ���FALSE 
XPLAY_API BOOL X_GetColor(XHANDLE handle, DWORD nRegionNum,int *nBrightness,int *nContrast, int *nSaturation, int *nHue);

// Description:������Ƶ����
// Parameters:
//	[in] handle: �ļ����ž�� 
// Return���ļ��ܵ�ʱ�䳤��ֵ,��λΪ����
XPLAY_API DWORD X_GetFileTime(XHANDLE handle);

// Description: ��ȡ֡��
// Parameters:
//	[in] handle: �ļ����ž�� 
// Return��֡��
XPLAY_API DWORD X_GetFrameRate(XHANDLE handle);

// Description: ���õ�ǰ�ļ�����ʱ��
// Parameters:
//	[in] handle: �ļ����ž��
//	[in] nTime: ��ʼ���ŵ�λ��,��λΪ����
// return: �ɹ�����TRUE; ʧ�ܷ���FALSE
XPLAY_API BOOL X_SetPlayedTime(XHANDLE handle,DWORD nTime);

// Description: ��ȡ��ǰ�ļ�����ʱ��
// Parameters:
//	[in] handle: �ļ����ž��
// return: �ļ���ǰ���ŵ�ʱ��,��λ����
XPLAY_API DWORD X_GetPlayedTime(XHANDLE handle);

// Description�������ļ����Ž�����Ϣ
// Parameters:
//  [in] handle: �ļ����ž��
//  [in] hWnd: ��Ϣ���յĴ���
//  [in] nMsg: �û��Զ����������Ϣ�������ŵ��ļ�����ʱ�û���hWnd���ڹ������յ������Ϣ��
//			����Ϣ�е�wParam����lParam�����Ի��handle��ֵ
// return: �ɹ�����TRUE; ʧ�ܷ���FALSE
XPLAY_API BOOL X_SetFileEndMsg(XHANDLE handle,HWND hWnd,UINT nMsg);

//Description: �ļ������ص�����
// Parameters��
// [in] handle: �ļ����ž��
// [in] pUser����Ӧ�û��Զ������
// return: ��
typedef void (CALLBACK* X_FileEndCBFun)(XHANDLE handle,void* pUser);

//Description�������ļ����Ž����ص�����
// Parameters��
//  [in] handle: �ļ����ž��
//  [in] pFileEndCBFun: �ļ������ص�����
//  [in] pUser: �û��Զ������
// return: �ɹ�����TRUE; ʧ�ܷ���FALSE
XPLAY_API BOOL X_SetFileEndCallBack(XHANDLE handle,X_FileEndCBFun FileEndCBFun,void* pUser);


struct CXPoint
{
	FLOAT x, y;
};
XPLAY_API int X_CreatePicture(XHANDLE handle, void* pSrcData,UINT  SrcDataSize,	COLORREF TransparentColor, RECT* pSrcRect, 
				  CXPoint* pScaling, CXPoint* pRotationCenter, 	FLOAT Rotation,  CXPoint* pTranslation, DWORD Transparency);
XPLAY_API int X_DeletePicture(XHANDLE handle, int hPicture);


// Description��������Ƶ��ͼ��ʽ�������ڲ��ž����ǰ���ò���Ч���Ѿ��򿪵Ĳ��ž����Ҫ���´򿪲���Ч��
// Parameters��
//  [in] nDrawLib: ��ͼ��ʽ
// return: �ɹ�����TRUE; ʧ�ܷ���FALSE
XPLAY_API BOOL X_SetDrawLib(X_DRAWLIB nDrawLib);

// Description��������Ƶ��ֱͬ����GDI��ͼ��ʽ��֧�����ã�
// Parameters��
//  [in] bEnable: TRUE��ʾ������FALSE��ʾ�ر�
// return: �ɹ�����TRUE; ʧ�ܷ���FALSE
XPLAY_API BOOL X_SetVerticalSync(BOOL bEnable);

enum X_BmpMode
{
	X_BmpMode_NONE = 0,
	X_BmpMode_YUV420 = 1,
	X_BmpMode_D3D11Texture = 2
};
struct X_INIT_PARAM
{
	unsigned int uiGetBmpMode; // ��ȡ������λͼ�ķ�ʽ����X_BmpMode��֧�ֶ���ʱ��ѡ�λ���ֵ�˲�����
};
XPLAY_API int X_Init(X_INIT_PARAM ini);


//Description:YUVתBMP����
// Parameters:
// [in] pYUVBuf:YUV����
// [in] nWidth:YUVͼ��Ŀ�
// [in] nHeight:YUVͼ��ĸ�
// [out] pRGBBuf:ת���ɵ�RGB����
// [in/out] nRGBBufLen:����pRGBBuf�����ݳ��ȣ�����RGBbuf��ʵ�ʳ��ȣ�
//					   �����Ȳ�������FALSE������ʵ����Ҫ�ĳ���
// Return���ɹ�����TRUE; ʧ�ܷ���FALSE
XPLAY_API BOOL X_YUV2BMP(BYTE *pYUVBuf, int nWidth, int nHeight, BYTE *pRGBBuf, int *nRGBBufLen);

//���ܣ�������Ż���
//����˵��
// [in] handle����Ƶ���ž��
// Return���ɹ�����TRUE; ʧ�ܷ���FALSE
XPLAY_API BOOL X_ClearPlayBuffer(XHANDLE handle);

//���ܣ���ȡRGB24λͼ
//����˵��
// [in] handle����Ƶ���ž��
// [in] pBuf��������
// [in/out] piSize: �����ʾpBuf�Ļ����С�������ʾ���ݴ�С
// [out] piWidth: ������Ƶ��
// [out] piHeight: ������Ƶ��
// Return���ɹ�����TRUE; ʧ�ܷ���FALSE
XPLAY_API int X_GetBmp(XHANDLE handle, char *pBuf, int *piSize, int *piWidth, int *piHeight);

//���ܣ���ȡRGB24λͼ �ڶ����ӿ�
//����˵��
// [in] handle����Ƶ���ž��
// [in] pBuf��������
// [in/out] piSize: �����ʾpBuf�Ļ����С�������ʾ���ݴ�С
// [out] piWidth: ������Ƶ��
// [out] piHeight: ������Ƶ��
// [out] pu64Time: ֡��ʱ���
// Return���ɹ�����TRUE; ʧ�ܷ���FALSE
XPLAY_API int X_GetBmp2(XHANDLE handle, char *pBuf, int *piSize, int *piWidth, int *piHeight, UINT64 *pu64Time);

struct X_DecoderCfg
{
	int iNvdCount;  // Ӣΰ������·��
	int iImsCount;  // Intel�����·��
	int bDecoderRender; //1��ʾ�������ڲ���Ⱦ��0��ʾ�������ⲿ��Ⱦ
	int iDrawLibNo;   //��ͼ�� 0;gdi, 1:ddraw, 2��d3d

	int iBufSize; //����ǰ����Ƶ�����С����λ��KB, Ĭ����5M
	int	iDelayTimeMs; // ƽ��������Ƶʱ����ʱ����λ�Ǻ���

	int iLogLevel; // LFATAL:5 LERROR : 4 LWARN : 3 LINFO : 2 LDEBUG : 1 �� ���ó�1��ӡ����־��࣬5����
};

XPLAY_API int X_SetDecoderCfg(X_DecoderCfg *pCfg);
XPLAY_API int X_GetDecoderCfg(X_DecoderCfg *pCfg);

XPLAY_API int X_GetAvailableDecoder(unsigned int *pMark);

#endif