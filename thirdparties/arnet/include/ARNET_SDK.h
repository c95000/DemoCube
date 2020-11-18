#ifndef ARNET_SDK_DEF_H
#define ARNET_SDK_DEF_H

#include "ARNET_DATATYPE.h"
#include "net_protocol.h"
#include "AR_DEFINE.h"


#ifdef WIN32

#ifdef NET_SDK_EXPORTS
#define SDK_API  extern "C" __declspec(dllexport) 
#else
#define SDK_API  extern "C" __declspec(dllimport)
#endif

#else

#ifdef __cplusplus
#define SDK_API  extern "C" 
#else
#define SDK_API  
#endif


#define CALLBACK
typedef void* HWND;
#define LONG long
#define BYTE unsigned char
#define WORD unsigned short
#define DWORD unsigned int
#endif

/************************************************************************/
/* �ص���������
/************************************************************************/

// �澯�ص�����  
//lLoginID:�豸���
//eAlarmType:�澯����   
//lAlarmChannel:�澯ͨ��  
//pUser:�û�����
typedef void (CALLBACK *pfARInfoCallBack)(LONG lLoginID,enAlarmType eAlarmType, BYTE lAlarmChannel, void* pUser);

//ϵͳ״̬�ص�����
//lLoginID:�豸���
//tStatus:ϵͳ״̬�ṹ��
//pUser:�û�����
typedef void (CALLBACK *pfARSysStatusCallBack)(LONG lLoginID,TSystemStatus tStatus, void* pUser);

typedef struct _ARNET_FRAME_INFO
{
	DWORD nFrameType; //֡����,��ö������enVidFrmType
	DWORD secCapTime;//�ɼ�ʱ�� ���벿��
	DWORD usecCapTime;//�ɼ�ʱ�� ��΢�벿��
}ARNET_FRAME_INFO;
// Description: ʵʱ��Ƶ���ص�����
// Parameters:
//	[in] lRealHandle: ARNET_StartRealPlay�ķ���ֵ
//	[in] pBuffer: ��Ƶ����,��XPLAY.H�е�GXXMedia�ṹ��ͷ
//	[in] dwBufSize:��Ƶ���ݴ�С
//	[in] pFrameInfo: ��Ƶ֡��Ϣ
//	[in] pUser: ����ARNET_StartRealPlayʱ������SDK���û����ݲ���
// Return: ��
// Remark:v
typedef void (CALLBACK *pfARRealDataCallBack)(LONG lRealHandle, char *pBuffer, DWORD dwBufSize, ARNET_FRAME_INFO *pFrameInfo, void* pUser);
// Description: ʵʱ��Ƶ���ص�������չ //FIX ME YOTO 20160422
// Parameters:
//	[in] szDeviceID: �豸ΨһID �ַ���
//	[in] nCameraID: �豸ͨ���� 0 ��ʾ1ͨ�� 1��ʾ2ͨ����Ŀǰ������֧��6ͨ��
//	[in] nStreamType: ������MBT_VIDEO=0,MBT_VIDEOSUB=1,MBT_AUDIO=2,MBT_VIDEOPS=5,MBT_VIDEOSUBPS=6,
//	[in] pBuffer: ��Ƶ����,��XPLAY.H�е�GXXMedia�ṹ��ͷ
//	[in] dwBufSize:��Ƶ���ݴ�С
//	[in] pFrameInfo: ��Ƶ֡��Ϣ
//	[in] pUser: ����ARNET_StartRealPlayʱ������SDK���û����ݲ���
// Return: ��
// Remark:v
typedef void (CALLBACK *pfARRealDataCallBackEX)(char * szDeviceID, DWORD nCameraID,DWORD nStreamType,char *pBuffer, DWORD dwBufSize, ARNET_FRAME_INFO *pFrameInfo, void* pUser);
// Description: ��Ƶ���ص�����
// Parameters:
//	[in] lRealHandle: ARNET_StartAudio�ķ���ֵ
//	[in] pBuffer:��Ƶ���ݣ�Ŀǰֻ֧�� G711A��8000HZ,64000bps����Ƶ
//	[in] dwBufSize:��Ƶ���ݴ�С
//	[in] dwDataType: ��Ƶ�������ͣ�0��ʾ����������256��ʾ�Ͼ�����
//	[in] pUser: ����ARNET_StartAudioʱ������SDK���û����ݲ���
// Return: ��
// Remark:
typedef void  (CALLBACK *pfARAudioDataCallBack)(LONG lRealHandle, char *pBuffer, DWORD dwBufSize, DWORD dwDataType, void *pUser);

// Description: ¼����Ƶ���ص�����
// Parameters:
//	[in] lRealHandle: ARNET_StartGetRecord�ķ���ֵ
//	[in] pBuffer: ��Ƶ����,��XPLAY.H�е�GXXMedia�ṹ��ͷ
//	[in] dwBufSize:��Ƶ���ݴ�С
//	[in] pFrameInfo: ��Ƶ֡��Ϣ
//	[in] pUser: ����ARNET_StartGetRecordʱ������SDK���û����ݲ���
// Return: ��
// Remark:v
typedef void  (CALLBACK *pfARRecordDataCallBack)(LONG lPlayHandle, char *pBuffer, DWORD dwBufSize, ARNET_FRAME_INFO *pFrameInfo, void *pUser);

// ¼��طŽ��Ȼص�����, nPlayingTime:��ǰ����ʱ�� ��λ:��  nProgress:���Ž���(0 ~ 1000)
typedef void  (CALLBACK *pfARPlayBackPosCallBack)(LONG lPlayHandle, int nPlayingTime, int nProgress, void *pUser);

// ��־��ѯ�ص�����
typedef void  (CALLBACK *pfARQueryLogCallBack)(TPostSysLog *stSysLog , void *pUser);

// ¼���ѯ�ص�����
typedef void  (CALLBACK *pfARQueryRecordCallBack)(TRecFileInfo  stSDFileInfo,DWORD nTotalNum,DWORD nCurNo, void *pUser);

 // nStatus:1��ʾ�豸���ߣ�0��ʾ�豸����
typedef void (CALLBACK *pfARDeviceStatusCallBack)(LONG lLoginID,char *szDeviceID, int nStatus, void *pUser);

/************************************************************************/
/* �ӿڶ���
/************************************************************************/

 /************************************************************************/
 /* ��ʼ��
 /************************************************************************/
//Description:��ʼ��SDK
//pParam ����Ϊ NULL ��ʾ����Ĭ��ֵ,
//Return:TRUE ��ʾ�ɹ���FALSE ��ʾʧ�ܡ�      
//Remark: �������� SDK������ǰ�ᡣ
 SDK_API BOOL  ARNET_Init(ARNET_INIT_PARAM *pParam);  

//Description:�ͷ�SDK��Դ
//Parameters:
//Return:TRUE ��ʾ�ɹ���FALSE ��ʾʧ�ܡ�
//Remark: �ڽ���֮ǰ�����á�
 SDK_API BOOL  ARNET_Cleanup();

 //Description:��ȡSDK �汾��
 //Parameters:
 //Return:IPC_SDK�İ汾��
 //Remark: 1�����ֽڱ�ʾ���汾�ţ�1 �����ֽڱ�ʾ�Ӱ汾�ţ�1���ֽ������汾�ţ�1���ֽڱ�ʾ�����汾�š��� 0x01020310����ʾ�汾Ϊ 1.2.3.10��
 SDK_API DWORD ARNET_GetSDKVersions();

//����:��ȡ�������Ĵ�����
//����ֵ:�������Ĵ�����
 SDK_API int ARNET_GetLastError();

 //Description: �����豸�����߻ص�����
 //Parameters:
 //	[in] fCallBack:��¼������Ϣ
 //	[in] pUser:�û�����
 // Return:����-1 ��ʾ����ʧ��, ����0��ʾ���óɹ�
 SDK_API LONG ARNET_SetDeviceStatusCallBack(pfARDeviceStatusCallBack fCallBack,void *pUser);


//Description: ��ȡ�첽��¼�豸�ľ��
//Return:����-1 ��ʾ��ȡʧ��, ����Ĵ�������ARNET_GetLastError��ȡ������ֵ��ʾ��ȡ�ɹ�������ֵΪ�豸�����
 SDK_API LONG ARNET_GetDevHandle();

 //Description: �첽��¼�豸
 //Parameters:
 // [in] ARNET_GetDevHandle�ķ���ֵ�����ô˺���֮ǰ������� ARNET_GetDevHandle��
 //	[in] stLoginInfo:��¼������Ϣ
 //  [out] lpDeviceInfo:���ص��豸��Ϣ
 //  [in] cbSysStatusCallBack:ϵͳ״̬�ص�����
 //	[in] pStatusUser:״̬�ص������û�����
 //	[in] fMessageCallBack:�澯�ص�����
 //	[in] pMsgUser:�澯�ص������û�����
 // Return:����-1 ��ʾ�첽��¼����ʧ��, ����Ĵ�������ARNET_GetLastError��ȡ������0��ʾ��¼����ɹ�
 //ע�⣺�˺����������أ����óɹ��������豸��¼�ɹ�;���������� ARNET_SetDeviceStatusCallBack���õĻص�����

 SDK_API  int ARNET_LoginAsync(LONG lLoginID, ARNET_LOGIN_INFO stLoginInfo,  LPARNET_DEVICE_INFO lpDeviceInfo,pfARSysStatusCallBack cbSysStatusCallBack,
	 void* pStatusUser,pfARInfoCallBack fMessageCallBack, void* pMsgUser);


 //Description: ��¼�豸
 //Parameters:
 //	[in] stLoginInfo:��¼������Ϣ
 //  [out] lpDeviceInfo:���ص��豸��Ϣ
 //  [in] cbSysStatusCallBack:ϵͳ״̬�ص�����
 //	[in] pStatusUser:״̬�ص������û�����
 //	[in] fMessageCallBack:�澯�ص�����
 //	[in] pMsgUser:�澯�ص������û�����
 // Return:����-1 ��ʾ��¼ʧ��, ����Ĵ�������ARNET_GetLastError��ȡ������ֵ��ʾ��¼�ɹ�������ֵΪ�豸��¼�����
 //Remark:
 SDK_API LONG ARNET_Login(ARNET_LOGIN_INFO stLoginInfo, LPARNET_DEVICE_INFO lpDeviceInfo,
	 pfARSysStatusCallBack cbSysStatusCallBack, void* pStatusUser,
	 pfARInfoCallBack fMessageCallBack, void* pMsgUser);

 //Description:ע���豸��¼
 //Parameters:
 //	[in] lLoginID:�豸�����ARNET_Login�ķ���ֵ
 //Return:  �ɹ�����TRUE;ʧ�ܷ���FALSE,����Ĵ�������ARNET_GetLastError��ȡ   
 //Remark:                                                                              
 SDK_API BOOL ARNET_LogOut(LONG lLoginID);

 //Description: ���豸
 //Parameters:
 //	[in] stOpenInfo: �豸����Ҫ����Ϣ
 // [out] lpDeviceInfo: ���ص��豸��Ϣ
 // [in] cbSysStatusCallBack:ϵͳ״̬�ص�����
 //	[in] pStatusUser:״̬�ص������û�����
 //	[in] fMessageCallBack:�澯�ص�����
 //	[in] pMsgUser:�澯�ص������û�����
 // Return:����-1 ��ʾ��¼ʧ��, ����Ĵ�������ARNET_GetLastError��ȡ������ֵ��ʾ��¼�ɹ�������ֵΪ�豸��¼�����
 //Remark:

SDK_API LONG ARNET_OpenDevice(ARNET_OPEN_INFO stOpenInfo, LPARNET_DEVICE_INFO lpDeviceInfo,pfARSysStatusCallBack cbSysStatusCallBack, void* pStatusUser,
	 pfARInfoCallBack fMessageCallBack, void* pMsgUser);

 //Description: ��ѯ�豸�Ƿ�����,ͬʱ֧����ͨ��4G
 //Parameters:
 //[in] lLoginID:�豸���
 //Return:���߷���TRUE�������ڷ���FALSE
 SDK_API BOOL ARNET_IsConnected(LONG lLoginID);

 //Description: ע���豸�ǳ��û�,ͬʱ֧����ͨ��4G
 //Parameters:
 //[in] lLoginID:�豸���
 //Return:�ɹ�����TRUE,ʧ�ܷ���FALSE,����Ĵ�������ARNET_GetLastError��ȡ                                                 
 SDK_API BOOL ARNET_CloseDev(LONG lLoginID);

 /************************************************************************/
 /* ����������Ϣ�ص�
 /************************************************************************/
 //Description: POST��Ϣ�ص�����
 //Parameters:
 //[in] lLoginID:�豸���
 //[in] nCmd:��Ϣ����
 //[in] pBuf:��Ϣ����
 //[in] unBufSize:��Ϣ���ݴ�С
 //[in] pUser���û�����
 //Return:���ش�����      
typedef void (CALLBACK *pfARPostMsgCallBack)(LONG lLoginID,enPushOnCmd enCmd, char *pBuf, unsigned int unBufSize, void *pUser);

 //Description: �豸����������Ϣ�ص�����
 //Parameters:
 //[in] lLoginID:�豸���
 //[in] fPostMsgCallBack:��Ϣ�ص�����
 //[in] pUser���ص������û�����
 //Return:���ش�����      
 SDK_API LONG ARNET_SetPostMsgCallBack(LONG lLoginID,pfARPostMsgCallBack fPostMsgCallBack,void *pUser);

 //Description: ý����ȫ�ֻص���������
 //Parameters:
 //[in] fRealDataCallBack:ý����ص�����
 //[in] pUser���ص������û�����
 //Return:���ش�����   
 SDK_API LONG ARNET_SetRealPlayDataCallBack(pfARRealDataCallBackEX fRealDataCallBack,void *pUser);
 /************************************************************************/
 /* ��Ƶ������
 /************************************************************************/

 //Description:����ͨ��Ԥ��
 //Parameters:
 //	[in] lLoginID:�豸���
 //	[in] nCameraID:��ʱ��Ч
 //	[in] nStreamType:�������ͣ�����enMonBlockType����
 //	[in] hWnd��������ʾ���ھ����ֻ����ҪSDK�ڲ����ý����ʱʹ��
 //	[in] cbRealDataCallBack��ʵʱ���ص�����
 //	[in] pUser: ʵʱ���ص������û�����
 //Return: ʧ�ܷ���-1, �ɹ�����ʵʱ�����,����Ĵ�������ARNET_GetLastError��ȡ
 //Remark:
 SDK_API LONG ARNET_StartRealPlay(LONG lLoginID,DWORD nCameraID,DWORD nStreamType,
	 pfARRealDataCallBack cbRealDataCallBack, void *pUser);
 //Description:����ͨ��Ԥ����չЭ��
 //Parameters:
 //	[in] lLoginID:�豸���
 //	[in] nCameraID:�豸ͨ����: 0��ʾ1ͨ��, 1��ʾ2ͨ����Ŀǰ������֧��6ͨ��
 //	[in] nStreamType:�������ͣ�����enMonBlockType����������MBT_VIDEO=0,MBT_VIDEOSUB=1,MBT_AUDIO=2,MBT_VIDEOPS=5,MBT_VIDEOSUBPS=6,
 //	[in] pIp:ý���������IP��ַ
 //	[in] nPort:ý����������˿�
 //	[in] enTranMode:ý�������������
 //	[in] cbRealDataCallBack��ʵʱ���ص����� ���ز������� ����ΪNULL
 //	[in] pUser: ʵʱ���ص������û�����
 //Return: ʧ�ܷ���-1, �ɹ�����ʵʱ�����,����Ĵ�������ARNET_GetLastError��ȡ
 //Remark:
 SDK_API LONG ARNET_StartRealPlayEX(LONG lLoginID,DWORD nCameraID,DWORD nStreamType,char *pIp, int nPort, EnumMonTranMode enTranMode,
	 pfARRealDataCallBack cbRealDataCallBack, void *pUser);
 //Description:�ر�Ԥ��
 //Parameters:
 //	[in] lRealHandle:ʵʱ�����
 //Return:�ɹ�����TRUE,ʧ�ܷ���FALSE,����Ĵ�������ARNET_GetLastError��ȡ
 //Remark:
 SDK_API BOOL ARNET_StopRealPlay(LONG lRealHandle);

 //Description:�ر�ʵʱ��
 //Parameters:
 //	[in] szDeviceID:�豸ID
 //	[in] nCameraID:�豸ͨ����: 0��ʾ1ͨ��, 1��ʾ2ͨ����Ŀǰ������֧��6ͨ��
 //	[in] nStreamType:�������ͣ�����enMonBlockType����������MBT_VIDEO=0,MBT_VIDEOSUB=1,MBT_AUDIO=2,MBT_VIDEOPS=5,MBT_VIDEOSUBPS=6,

 SDK_API BOOL ARNET_StopRealPlayEX(char * szDeviceID, DWORD nCameraID,DWORD nStreamType);

 /************************************************************************/
 /* �����Խ�
 /************************************************************************/

 // ����:��ʼ˫�������Խ�
 // Parameters:
 //	[in] lLoginID:�豸��¼���
 //	[in] cbAudioDataCallBack:��Ƶ���ص�����
 //	[in] pUser:�ص������û�
 // Return:ʧ�ܷ���-1, �ɹ����ضԽ������,����Ĵ�������ARNET_GetLastError��ȡ
 // Remark:
 SDK_API LONG ARNET_StartTalk(LONG lLoginID,pfARAudioDataCallBack cbAudioDataCallBack,void* pUser);

 //Description:ֹͣ˫�������Խ�
 // Parameters:
 //[in] lTalkHandle:�Խ������
 // Return:�ɹ�����TRUE,ʧ�ܷ���FALSE,����Ĵ�������ARNET_GetLastError��ȡ
 // Remark:
 SDK_API BOOL ARNET_StopTalk(LONG lTalkHandle);


// ����:��ͨ������
 // Description:��ͨ������
 // Parameters:
 //	[in] lLoginID:�豸���
 //	[in] dwAudioChan:��ʱ��Ч
 //	[in] cbAudioDataCallBack:��Ƶ���ص�����
 //	[in] pUser:�ص������û�
 // Return:ʧ�ܷ���-1, �ɹ�������Ƶ�����,����Ĵ�������ARNET_GetLastError��ȡ
 // Remark:
 SDK_API LONG ARNET_StartAudio(LONG lLoginID,DWORD dwAudioChan,
	 pfARAudioDataCallBack cbAudioDataCallBack,void* pUser);

 // Description:�ر�ͨ������
 // Parameters:
 //	[in] lAudioHandle:��Ƶ�����
 // Return:�ɹ�����TRUE,ʧ�ܷ���FALSE,����Ĵ�������ARNET_GetLastError��ȡ
 //	Remark:
 SDK_API BOOL ARNET_StopAudio(LONG lAudioHandle);

 // Description:������豸������
 // Parameters:
 //	[in] lLoginID:�豸��¼���
 //	[in]��dwAudioChan:��ʱ��Ч
 // Return:ʧ�ܷ���-1, �ɹ����ؽ������,����Ĵ�������ARNET_GetLastError��ȡ
 //	Remark:
 SDK_API LONG ARNET_StartSpeak(LONG lLoginID,DWORD dwAudioChan);

 // Description:������豸��������չ 
 // Parameters:
 //	[in] lLoginID:�豸��¼���
 //	[in]��pIp:ý����IP��ַ
 //	[in]��nPort:ý����˿�
 //	[in]��enTranMode:ý���� ���䷽ʽ
 // Return:ʧ�ܷ���-1, �ɹ����ؽ������,����Ĵ�������ARNET_GetLastError��ȡ
 //	Remark:
 SDK_API LONG ARNET_StartSpeakEX(LONG lLoginID,char *pIp, int nPort, EnumMonTranMode enTranMode);

 // Description:���豸������������
 // Parameters:
 //	[in] lSpeakHandle:�������
 //	[in] pBuffer:����������ݵĻ�����,Ŀǰֻ֧�� G711A��8000HZ,64000bps����Ƶ
 //	[in] dwBufSize:�������ݴ�С
 // Return:�ɹ�����TRUE,ʧ�ܷ���FALSE,����Ĵ�������ARNET_GetLastError��ȡ
 // Remark:
 SDK_API BOOL ARNET_SpeakSendData(LONG lSpeakHandle, char *pBuffer, DWORD dwBufSize);
 // Description:���豸��������������չ
 // Parameters:
 //	[in] szDeviceID:�豸ΨһID
 //	[in] pBuffer:����������ݵĻ�����,Ŀǰֻ֧�� G711A��8000HZ,64000bps����Ƶ
 //	[in] dwBufSize:�������ݴ�С
 // Return:�ɹ�����TRUE,ʧ�ܷ���FALSE,����Ĵ�������ARNET_GetLastError��ȡ
 // Remark:
 SDK_API BOOL ARNET_SpeakSendDataEX(char * szDeviceID, char *pBuffer, DWORD dwBufSize);

 // Description:ֹͣ���豸������
 // Parameters:
 //	[in] lSpeakHandle:�������
 // Return:�ɹ�����TRUE,ʧ�ܷ���FALSE,����Ĵ�������ARNET_GetLastError��ȡ
 // Remark:
 SDK_API BOOL ARNET_StopSpeak(LONG lSpeakHandle);

 /************************************************************************/
 /* Զ������
 /************************************************************************/

 // ����:�����ļ�ϵͳ
 // lLoginID:�豸��¼���
 // eFileType:�ļ�����,��ֻ֧��GS_UPD_BIOS
 // dwFileSize:�ļ���С
 // iFileID:���ص��ļ�ID
 // �ɹ�����TRUE,ʧ�ܷ���FALSE,����Ĵ�������ARNET_GetLastError��ȡ 
 SDK_API BOOL ARNET_UpdateFile(LONG lLoginID, enUpdateFileType eFileType, DWORD dwFileSize, int* iFileID);

 // ����:���͸����ļ�
 // lLoginID:�豸��¼���
 // pbuf:�����ļ�����
 // nLen:���ݴ�С
 // iFileID:�ļ�ID
 // �ɹ�����TRUE,ʧ�ܷ���FALSE,����Ĵ�������ARNET_GetLastError��ȡ 
 SDK_API BOOL ARNET_SendUpdateFile(LONG lLoginID,char *pbuf,int nLen, int iFileID);

 /************************************************************************/
 /* ������ȡ������
 /************************************************************************/

 // ����:������ȡ������
 // nCmd:����ID
 // pInBuf:����buf
 // unInSize:����buf��С
 // pOutBuf:����buf
 // unOutSize:�������ݴ�С
 // iOutBufSize:����buf��С
 // iFileID:�ļ�ID
 // �ɹ����� 0,ʧ�ܷ��ظ���������Ĵ�������ARNET_GetLastError��ȡ 
 SDK_API LONG ARNET_TransConfig(LONG lLoginID, int nCmd,
	 char *pInBuf, unsigned int unInSize,
	 char *pOutBuf, unsigned int *unOutSize,int iOutBufSize);
	 
 // ����:��������
 // lLoginID:�豸��¼ID
 // nCmd:����ID
 // pInBuf:����buf
 // unInSize:����buf��С
 // �ɹ����� 0,ʧ�ܷ��ظ���������Ĵ�������ARNET_GetLastError��ȡ 
 SDK_API LONG ARNET_SetConfig(LONG lLoginID, int nCmd,char *pInBuf, unsigned int unInSize);
 
 // ����:�Ȼ����˷���enRobotCmd����
 // lLoginID:�豸��¼ID
 // nCmd:����ID
 // pInBuf:����buf
 // unInSize:����buf��С
 // pOutBuf:����buf
 // [in][out] unOutSize: ����ΪpOutBuf�Ĵ�С�����Ϊʵ�ʻظ������ݴ�С
 // �ɹ����� 0,ʧ�ܷ��ظ���������Ĵ�������ARNET_GetLastError��ȡ 
 SDK_API LONG ARNET_SendRobotCmd(LONG lLoginID, enRobotCmd nCmd,char *pInBuf, unsigned int unInSize,char *pOutBuf, unsigned int *unOutSize);


 // ����:������˷����ı�����
 // [in] lLoginID:�豸��¼ID
 // [in] pInText: ������˷��͵��ı�
 // [in] unInSize: ���͵��ı���С
 // [out] pOutBuf: ���ջ����˻ظ���buf
 // [in][out] unOutSize: ����ΪpOutBuf�Ĵ�С�����Ϊʵ�ʻظ������ݴ�С
 // �ɹ����� 0,ʧ�ܷ��ظ���������Ĵ�������ARNET_GetLastError��ȡ
 SDK_API LONG ARNET_SendRobotText(LONG lLoginID, char *pInText, unsigned int unInSize,char *pOutText, unsigned int *unOutSize);

 //Description:���豸��������ӿ�
 // Parameters:
 // [in] lLoginID: �豸���
 // [in] nCmd: �·��������
 // [in] pInBuf: �·�����������
 // [in] unInSize: �·����������ݳ���
 // Return���ɹ�����TRUE; ʧ�ܷ���FALSE
 SDK_API  BOOL ARNET_SendCmd(LONG lLoginID, enPushDownCmd nCmd, char *pInBuf, unsigned int unInSize);

 /************************************************************************/
 /* �����̨����
 /************************************************************************/

 // ����:��̨����
 // nPtzCmd:��̨��������
 // nParam1:��̨���Ʋ���1��������˼����nPtzCmd��ͬ����ͬ
 // nParam2:��̨���Ʋ���2��������˼����nPtzCmd��ͬ����ͬ
 // �ɹ�����0,ʧ�ܷ��ش�����,����Ĵ�������ARNET_GetLastError��ȡ 
 SDK_API BOOL ARNET_PtzCtrl(LONG lLoginID, enSPAction nPtzCmd,BYTE nParam1,BYTE nParam2);

 //Description:��ȡԤ�õ�
 //Parameters:
 //	[in] lLoginID:�豸���
 //	[out] pPrePointList:����Ԥ�õ���Ϣ������������ID������
 //Return: �ɹ�����0;ʧ�ܷ��ش�����,����Ĵ�������ARNET_GetLastError��ȡ
 //Remark:
 SDK_API BOOL ARNET_GetPrePoint(LONG lLoginID, ARNET_PRE_POINT_LIST *pPrePointList);

 //Description:Ԥ�õ����
 //Parameters:
 //	[in] lLoginID:�豸���
 //	[in] enPtzCmd: �����������SP_CLEAR_POINT���Ԥ�õ��SP_GOTO_POINT����Ԥ�õ�
 //	[in] byID: Ԥ�õ�ID
 //Return: �ɹ�����0;ʧ�ܷ��ش�����,����Ĵ�������ARNET_GetLastError��ȡ
 //Remark:
 SDK_API BOOL ARNET_PrePointCtrl(LONG lLoginID, enSPAction enPtzCmd,BYTE byID);

 //Description:�������޸�Ԥ�õ�
 //Parameters:
 //	[in] lLoginID:�豸���
 //	[in] byID: Ԥ�õ�ID
 //	[in] pchName: Ԥ�õ����ƣ���󳤶�16���ַ�
 //Return: �ɹ�����0;ʧ�ܷ��ش�����,����Ĵ�������ARNET_GetLastError��ȡ
 //Remark:
 SDK_API BOOL ARNET_ModifyPrePoint(LONG lLoginID,BYTE byID, char *pchName);


 //Description:��ȡѲ���б�
 //Parameters:
 //	[in] lLoginID:�豸���
 //	[out] pCruiseList:����Ѳ���б�����������ID������
 //Return: �ɹ�����0;ʧ�ܷ��ش�����,����Ĵ�������ARNET_GetLastError��ȡ
 //Remark:
 SDK_API BOOL ARNET_GetCruiseList(LONG lLoginID, ARNET_CRUISE_LIST *pstCruiseList);

 //Description:��ȡĳ��Ѳ������ϸ��Ϣ
 //Parameters:
 //	[in] lLoginID:�豸���
 //	[in] byID: Ѳ��ID
 //	[out] pstCruiseInfo:����Ѳ����Ϣ������Ԥ�õ��Ԥ�õ�ͣ��ʱ��
 //Return: �ɹ�����0;ʧ�ܷ��ش�����,����Ĵ�������ARNET_GetLastError��ȡ
 //Remark:
 SDK_API BOOL ARNET_GetCruiseInfo(LONG lLoginID, BYTE byID, ARNET_CRUISE_INFO *pstCruiseInfo);

 //Description:����Ѳ����ֹͣѲ����ɾ��Ѳ��
 //Parameters:
 //	[in] lLoginID:�豸���
 //	[in] enPtzCmd: �����������SP_CRUISE_START����Ѳ����SP_CRUISE_STOPֹͣѲ����SP_CRUISE_DELETEɾ��Ѳ��
 //	[in] byID: Ѳ��ID
 //Return: �ɹ�����0;ʧ�ܷ��ش�����,����Ĵ�������ARNET_GetLastError��ȡ
 //Remark:
 SDK_API BOOL ARNET_CruiseCtrl(LONG lLoginID, enSPAction enPtzCmd,BYTE byID);

 //Description:�������޸�Ѳ��
 //Parameters:
 //	[in] lLoginID:�豸���
 //	[in] byID: Ѳ��ID
 //	[in] pchName: Ѳ�����ƣ���󳤶�16���ַ�
 //	[in] stCruiseInfo: Ѳ����Ϣ
 //Return: �ɹ�����0;ʧ�ܷ��ش�����,����Ĵ�������ARNET_GetLastError��ȡ
 //Remark:
 SDK_API BOOL ARNET_ModifyCruise(LONG lLoginID,BYTE byID, char *pchName, ARNET_CRUISE_INFO stCruiseInfo);

 //Description:���ÿ���״̬
 //Parameters:
 //	[in] lLoginID:�豸���
 //	[in] byStatus: 1����򿪣�2����ر�
 //Return: �ɹ�����0;ʧ�ܷ��ش�����,����Ĵ�������ARNET_GetLastError��ȡ
 //Remark:
 SDK_API BOOL ARNET_SetKeepWatchStatus(LONG lLoginID,BYTE byStatus);

 //Description:��ȡ����״̬
 //Parameters:
 //	[in] lLoginID:�豸���
 //	[out] byStatus: 1����򿪣�2����ر�
 //Return: �ɹ�����0;ʧ�ܷ��ش�����,����Ĵ�������ARNET_GetLastError��ȡ
 //Remark:
 SDK_API BOOL ARNET_GetKeepWatchStatus(LONG lLoginID,BYTE *byStatus);

 //Description:3D��λ
 //Parameters:
 //	[in] lLoginID:�豸���
 //	[in] StartX: 3D��λ��ʼ��X����
 //	[in] StartY: 3D��λ��ʼ��Y����
 //	[in] EndX: 3D��λ������X����
 //	[in] EndY: 3D��λ������Y����
 //Return: �ɹ�����0;ʧ�ܷ��ش�����,����Ĵ�������ARNET_GetLastError��ȡ
 //Remark:��ʼ��ͽ������������Ҫ����Ϊ352*288�ķֱ��ʴ�С�·�
 SDK_API BOOL ARNET_3DPTZCTRL(LONG lLoginID, WORD StartX,WORD StartY,WORD EndX,WORD EndY);


 /************************************************************************/
 /* ¼�����ݻ�ȡ
 /************************************************************************/

 //Description: ��ʼ¼�����ݻ�ȡ
 //Parameters:	
 //	[in]lLoginID:�豸��¼���
 // [in] tGetRecord:¼���ȡ�����ṹ��
 // [in] cbRecordDataCallBack: ¼�����ݽ��ջص�����
 // [in] pDataUser: �ص���ʱ��ֱ�Ӵ����û�
 //Return: �ɹ��������ؾ��,ʧ�ܷ���-1,����Ĵ�������ARNET_GetLastError��ȡ
 //Remark:

 SDK_API LONG ARNET_StartGetRecord(LONG lLoginID,TGetRecord tGetRecord,pfARRecordDataCallBack cbRecordDataCallBack, void* pDataUser,long long *pDataSize);

 //Description: ֹͣ¼�����ݻ�ȡ
 //Parameters:	
 //		[in] lRecordHandle:ARNET_StartGetRecord�ķ���ֵ
 //Return: �ɹ�����TRUE,ʧ�ܷ���FALSE,����Ĵ�������ARNET_GetLastError��ȡ
 //Remark:
 SDK_API BOOL ARNET_StopGetRecord(LONG lRecordHandle);

// ����:��ȡ��־��Ϣ
// lLoginID:�豸��¼���
// stSysLogFilter:��־ɸѡ����
// �ɹ�����TRUE,ʧ�ܷ���FALSE,����Ĵ�������ARNET_GetLastError��ȡ 
 SDK_API BOOL ARNET_GetSysLog(LONG lLoginID, TSysLogFilter stSysLogFilter, pfARQueryLogCallBack cbQueryLogCallBack, void* pUser);

 //���ܣ���ӱ�ǩ
 //����˵��
 //lLoginID����¼���
 //pSei����ǩ����ϸ��Ϣ������stID��Ϊ-1 
 SDK_API  BOOL ARNET_Lable_Add(LONG lLoginID, AR_Lable *pSei);

 //���ܣ��޸ı�ǩ
 //����˵��
 //lLoginID����¼���
 //pSei����ǩ����ϸ��Ϣ������stID����ڵ���0 
 SDK_API  BOOL ARNET_Lable_Update(LONG lLoginID, AR_Lable *pSei);

 //���ܣ�ɾ����ǩ
 //����˵��
 //lLoginID����¼���
 //nLableID����Ҫɾ���ı�ǩID��-1 ��ʾɾ�����б�ǩ
 SDK_API  BOOL ARNET_Lable_Delete(LONG lLoginID, int nLableID);

 //���ܣ����б�ǩ
 //����˵��
 //lLoginID����¼���
 //nLableID����Ҫ���еı�ǩID
 SDK_API  BOOL ARNET_Lable_Center(LONG lLoginID, int nLableID);

 //���ܣ���ѯ��ǩ�б�
 //����˵��
 //lLoginID����¼���
 //pSei�����ڴ洢��ȡ�����б�
 //pNum�������ʾpSei�ܴ洢�ĸ����������ʾ��õĸ���
 SDK_API  BOOL ARNET_Lable_Query(LONG lLoginID, AR_Lable *pSei, int *pNum);

 //���ܣ���ѯ�豸��ǩ����
 //����˵��
 //lLoginID����¼���
 //pDeviceMaxCount�����ڻ�ȡ�豸֧�ֵ�����ǩ����
 //pCount�����ڻ�ȡ�Ѿ������ı�ǩ����
 SDK_API BOOL ARNET_Lable_QueryCount(LONG lLoginID, int *pDeviceMaxCount,int *pCount);

 //���ܣ����õ���λ����Ϣ
 //����˵��
 //lLoginID����¼���
 //pLocation������λ����Ϣ
 SDK_API BOOL ARNET_AR_SetLocation(LONG lLoginID, AR_LOCATION  *pLocation);

 //���ܣ�������������
 //����˵��
 //lLoginID����¼���
 //bAuto��0Ϊ�Զ���1Ϊ�ֶ�����1ʱ��ǰλ��Ϊ�������򣬵�ǰP��Ϊ360
SDK_API BOOL ARNET_AR_SetNorth(LONG lLoginID, BOOL bAuto);

//���ܣ�����Ͳ����ͷ������ʼ��
//����˵��
//lLoginID����¼���
//bAuto��������Ŀǰֻ��1
SDK_API BOOL ARNET_AR_SetLenInit(LONG lLoginID, BOOL bAuto);

//���ܣ�����Ͳ���Զ��۽�
//����˵��
//lLoginID����¼���
//bAuto��������Ŀǰֻ��1
SDK_API BOOL ARNET_AR_SetAutoFocus(LONG lLoginID, BOOL bAuto);

 //���ܣ�����PTZ��Ϣ
 //����˵��
 //pPtz������ǡ������ǡ��ӳ�������
 SDK_API BOOL ARNET_AR_SetPTZ(LONG lLoginID, AR_PTZ  *pPtz, AR_PTZ*pPtzCheck);

 //���ܣ�GOTO PTZ
 //fPan: ˮƽ�Ƕ����������������ʱ��+˳ʱ��-
 //fTilt: ��ֱ����Ƕ������ˮƽ��0����ʱ��+˳ʱ��-
 //fDistance: ����
 //fZoomValue: ����
 SDK_API BOOL ARNET_GotoPTZ(LONG lLoginID, float fPan, float fTilt, float fDistance, float fZoomValue);

 //���ܣ����òο���
 //pRef: �ο�������
 //nNum: �����С
 SDK_API BOOL ARNET_AR_SetReference(LONG lLoginID, AR_Reference *pRef, int nNum);

 //���ܣ���ӵ����ο��㵽�豸�ˣ���ԭ�еĻ���������
 SDK_API BOOL ARNET_AR_SetOneReference(LONG lLoginID, AR_Reference *pRef);

 SDK_API BOOL ARNET_AR_GetReference(LONG lLoginID, AR_Reference *pRef, int *pNum);

 SDK_API BOOL ARNET_AR_CmpToRef(LONG lLoginID, int x, int y, float *pHeight, float *pDeltT);

 SDK_API BOOL ARNET_AR_AddReference(LONG lLoginID, AR_PTZ ptzBottom1, AR_PTZ ptzTop1, AR_PTZ ptzBottom2, AR_PTZ ptzTop2, float fMeasuredH, AR_Reference *pRef);

 //���ܣ�ɾ�������ο���
 //����˵��
 //lLoginID����¼���
 //index��Ҫɾ���Ĳο����±�
 SDK_API BOOL ARNET_AR_DelRef(LONG lLoginID, int index);
 
 //���ܣ���ȡ���вο��㵱ǰ��Ļ����
 //����˵��
 //lLoginID����¼���
 //arPos[in]���ο������������׵�ַ����������1920*1080�ĳߴ���
 //pNum[in/out]������ȥ���鳤�ȣ�����ʵ�ʻ�ȡ�Ĳο������
 SDK_API BOOL ARNET_AR_GetRefPos(LONG lLoginID, AR_POS *arPos, int *pNum);

 //���ܣ���ȡ����λ����Ϣ
 //����˵��
 //lLoginID����¼���
 //pLocation������λ����Ϣ
 SDK_API BOOL ARNET_AR_GetLocation(LONG lLoginID, AR_LOCATION  *pLocation);

 //���ܣ���ȡPTZ��Ϣ
 //����˵��
 //pPtz������ǡ������ǡ��ӳ�������
 SDK_API BOOL ARNET_AR_GetPTZ(LONG lLoginID, AR_PTZ  *pPtz, AR_PTZ*pPtzCheck);

 //���ܣ���ȡ������PTֵ
 //����˵����
 //lLoginID:��¼���
 //p[out]:������Pֵ
 //t[out]:������Tֵ
 //x[in]:������x����
 //y[in]:������y����
 SDK_API BOOL ARNET_Lable_GetPT(LONG lLoginID, double *p, double *t, int x, int y);
 SDK_API BOOL ARNET_Lable_GetPT1(LONG lLoginID, double *p, double *t, int x, int y, int bPTed);

 SDK_API BOOL ARNET_AR_GetHeight(LONG lLoginID, float *fHeight, float fOriH, float fDeltT, int x1, int y1, int x2, int y2);

 SDK_API BOOL ARNET_AR_GetLength(LONG lLoginID, float *fLength, float fOriH, float fDeltT, int x1, int y1, int x2, int y2);

 SDK_API BOOL ARNET_SetARParamCallBack(LONG lLoginID,fARParamCBFun ARParamCBFun,void* pUser);

 SDK_API BOOL ARNET_Lable_Pos_Adjust(LONG lLoginID, int *pnLableID,int nNum,int x, int y);

 //���ܣ���ӱ�ǩ
 //����˵��
 //lLoginID����¼���
 //pSei����ǩ����ϸ��Ϣ������stID��Ϊ-1 
 SDK_API  BOOL ARNET_LableEx_Add(LONG lLoginID, AR_LableEx *pSei);

 //���ܣ��޸ı�ǩ
 //����˵��
 //lLoginID����¼���
 //pSei����ǩ����ϸ��Ϣ������stID����ڵ���0 
 SDK_API  BOOL ARNET_LableEx_Update(LONG lLoginID, AR_LableEx *pSei);

 //���ܣ���ѯ��ǩ�б�
 //����˵��
 //lLoginID����¼���
 //pSei�����ڴ洢��ȡ�����б�
 //pNum�������ʾpSei�ܴ洢�ĸ����������ʾ��õĸ���
 SDK_API  BOOL ARNET_LableEx_Query(LONG lLoginID, AR_LableEx *pSei, int *pNum);

 //typedef void (CALLBACK* fARLableExCBFun)(int handle, AR_OPERATION nOperation, AR_LableEx  *pSei, int nNum, void*  pUser);//��ǿ��ʵ��ǩ�ص�����
 SDK_API BOOL ARNET_SetARLableExCallBack(LONG lLoginID, fARLableExCBFun ARLableCBFun, void* pUser);

 // ��̨��ʱ���� �ӿ�
 SDK_API BOOL ARNET_SetPTZTimedTask(LONG lLoginID, TPTZTimedTaskParam PTZTimedTaskParam);

 SDK_API BOOL ARNET_GetPTZTimedTask(LONG lLoginID, TPTZTimedTaskParam* PTZTimedTaskParam);
 
 //Description: ����������������ʶ����
 // Parameters:
 // [in] szDeviceID:�豸ID
 // [in] pTextBuf: ������ı�����
 // [in] nTextLen��������ı����ݳ���
 // [in] pVoiceBuf: �������Ƶ����
 // [in] nVoiceLen���������Ƶ���ݳ���
 // Return���ɹ�����TRUE; ʧ�ܷ���FALSE
 SDK_API BOOL ARNET_SendQuestionAsw(LONG lLoginID, char *pTextBuf,int nTextLen,char *pVoiceBuf, int nVoiceLen);

 //Description:�������ͼƬȫ�ֻص�����
 // Parameters:
 // [in] lLoginID:�豸���
 // [in] fARPictureCBFun: ͼƬ�ص�����
 // [in] pUser���û�����
 // Return���ɹ�����TRUE; ʧ�ܷ���FALSE
 SDK_API BOOL ARNET_SetGlobalARPictureCallBack(fGlobalARPictureCBFun CBFun,void* pUser);

#endif