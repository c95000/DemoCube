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
/* 回调函数定义
/************************************************************************/

// 告警回调函数  
//lLoginID:设备句柄
//eAlarmType:告警类型   
//lAlarmChannel:告警通道  
//pUser:用户数据
typedef void (CALLBACK *pfARInfoCallBack)(LONG lLoginID,enAlarmType eAlarmType, BYTE lAlarmChannel, void* pUser);

//系统状态回调函数
//lLoginID:设备句柄
//tStatus:系统状态结构体
//pUser:用户数据
typedef void (CALLBACK *pfARSysStatusCallBack)(LONG lLoginID,TSystemStatus tStatus, void* pUser);

typedef struct _ARNET_FRAME_INFO
{
	DWORD nFrameType; //帧类型,见枚举类型enVidFrmType
	DWORD secCapTime;//采集时间 的秒部分
	DWORD usecCapTime;//采集时间 的微秒部分
}ARNET_FRAME_INFO;
// Description: 实时视频流回调函数
// Parameters:
//	[in] lRealHandle: ARNET_StartRealPlay的返回值
//	[in] pBuffer: 视频数据,以XPLAY.H中的GXXMedia结构打头
//	[in] dwBufSize:视频数据大小
//	[in] pFrameInfo: 视频帧信息
//	[in] pUser: 调用ARNET_StartRealPlay时，传进SDK的用户数据参数
// Return: 无
// Remark:v
typedef void (CALLBACK *pfARRealDataCallBack)(LONG lRealHandle, char *pBuffer, DWORD dwBufSize, ARNET_FRAME_INFO *pFrameInfo, void* pUser);
// Description: 实时视频流回调函数扩展 //FIX ME YOTO 20160422
// Parameters:
//	[in] szDeviceID: 设备唯一ID 字符串
//	[in] nCameraID: 设备通道号 0 表示1通道 1表示2通道；目前机器人支持6通道
//	[in] nStreamType: 流类型MBT_VIDEO=0,MBT_VIDEOSUB=1,MBT_AUDIO=2,MBT_VIDEOPS=5,MBT_VIDEOSUBPS=6,
//	[in] pBuffer: 视频数据,以XPLAY.H中的GXXMedia结构打头
//	[in] dwBufSize:视频数据大小
//	[in] pFrameInfo: 视频帧信息
//	[in] pUser: 调用ARNET_StartRealPlay时，传进SDK的用户数据参数
// Return: 无
// Remark:v
typedef void (CALLBACK *pfARRealDataCallBackEX)(char * szDeviceID, DWORD nCameraID,DWORD nStreamType,char *pBuffer, DWORD dwBufSize, ARNET_FRAME_INFO *pFrameInfo, void* pUser);
// Description: 音频流回调函数
// Parameters:
//	[in] lRealHandle: ARNET_StartAudio的返回值
//	[in] pBuffer:音频数据，目前只支持 G711A（8000HZ,64000bps）音频
//	[in] dwBufSize:音频数据大小
//	[in] dwDataType: 音频数据类型，0表示连续声音，256表示断句声音
//	[in] pUser: 调用ARNET_StartAudio时，传进SDK的用户数据参数
// Return: 无
// Remark:
typedef void  (CALLBACK *pfARAudioDataCallBack)(LONG lRealHandle, char *pBuffer, DWORD dwBufSize, DWORD dwDataType, void *pUser);

// Description: 录像视频流回调函数
// Parameters:
//	[in] lRealHandle: ARNET_StartGetRecord的返回值
//	[in] pBuffer: 视频数据,以XPLAY.H中的GXXMedia结构打头
//	[in] dwBufSize:视频数据大小
//	[in] pFrameInfo: 视频帧信息
//	[in] pUser: 调用ARNET_StartGetRecord时，传进SDK的用户数据参数
// Return: 无
// Remark:v
typedef void  (CALLBACK *pfARRecordDataCallBack)(LONG lPlayHandle, char *pBuffer, DWORD dwBufSize, ARNET_FRAME_INFO *pFrameInfo, void *pUser);

// 录像回放进度回调函数, nPlayingTime:当前播放时间 单位:秒  nProgress:播放进度(0 ~ 1000)
typedef void  (CALLBACK *pfARPlayBackPosCallBack)(LONG lPlayHandle, int nPlayingTime, int nProgress, void *pUser);

// 日志查询回调函数
typedef void  (CALLBACK *pfARQueryLogCallBack)(TPostSysLog *stSysLog , void *pUser);

// 录像查询回调函数
typedef void  (CALLBACK *pfARQueryRecordCallBack)(TRecFileInfo  stSDFileInfo,DWORD nTotalNum,DWORD nCurNo, void *pUser);

 // nStatus:1表示设备上线；0表示设备下线
typedef void (CALLBACK *pfARDeviceStatusCallBack)(LONG lLoginID,char *szDeviceID, int nStatus, void *pUser);

/************************************************************************/
/* 接口定义
/************************************************************************/

 /************************************************************************/
 /* 初始化
 /************************************************************************/
//Description:初始化SDK
//pParam 设置为 NULL 表示采用默认值,
//Return:TRUE 表示成功，FALSE 表示失败。      
//Remark: 调用其他 SDK函数的前提。
 SDK_API BOOL  ARNET_Init(ARNET_INIT_PARAM *pParam);  

//Description:释放SDK资源
//Parameters:
//Return:TRUE 表示成功，FALSE 表示失败。
//Remark: 在结束之前最后调用。
 SDK_API BOOL  ARNET_Cleanup();

 //Description:获取SDK 版本号
 //Parameters:
 //Return:IPC_SDK的版本号
 //Remark: 1个高字节表示主版本号，1 个低字节表示子版本号，1个字节修正版本号，1个字节表示修正版本号。如 0x01020310：表示版本为 1.2.3.10。
 SDK_API DWORD ARNET_GetSDKVersions();

//功能:读取最后操作的错误码
//返回值:最后操作的错误码
 SDK_API int ARNET_GetLastError();

 //Description: 设置设备上下线回调函数
 //Parameters:
 //	[in] fCallBack:登录请求信息
 //	[in] pUser:用户数据
 // Return:返回-1 表示设置失败, 返回0表示设置成功
 SDK_API LONG ARNET_SetDeviceStatusCallBack(pfARDeviceStatusCallBack fCallBack,void *pUser);


//Description: 获取异步登录设备的句柄
//Return:返回-1 表示获取失败, 具体的错误码由ARNET_GetLastError获取；其他值表示获取成功，返回值为设备句柄。
 SDK_API LONG ARNET_GetDevHandle();

 //Description: 异步登录设备
 //Parameters:
 // [in] ARNET_GetDevHandle的返回值（调用此函数之前必须调用 ARNET_GetDevHandle）
 //	[in] stLoginInfo:登录请求信息
 //  [out] lpDeviceInfo:返回的设备信息
 //  [in] cbSysStatusCallBack:系统状态回调函数
 //	[in] pStatusUser:状态回调函数用户数据
 //	[in] fMessageCallBack:告警回调函数
 //	[in] pMsgUser:告警回调函数用户数据
 // Return:返回-1 表示异步登录请求失败, 具体的错误码由ARNET_GetLastError获取；返回0表示登录请求成功
 //注意：此函数立即返回，调用成功不代码设备登录成功;上线下线由 ARNET_SetDeviceStatusCallBack设置的回调决定

 SDK_API  int ARNET_LoginAsync(LONG lLoginID, ARNET_LOGIN_INFO stLoginInfo,  LPARNET_DEVICE_INFO lpDeviceInfo,pfARSysStatusCallBack cbSysStatusCallBack,
	 void* pStatusUser,pfARInfoCallBack fMessageCallBack, void* pMsgUser);


 //Description: 登录设备
 //Parameters:
 //	[in] stLoginInfo:登录请求信息
 //  [out] lpDeviceInfo:返回的设备信息
 //  [in] cbSysStatusCallBack:系统状态回调函数
 //	[in] pStatusUser:状态回调函数用户数据
 //	[in] fMessageCallBack:告警回调函数
 //	[in] pMsgUser:告警回调函数用户数据
 // Return:返回-1 表示登录失败, 具体的错误码由ARNET_GetLastError获取；其他值表示登录成功，返回值为设备登录句柄。
 //Remark:
 SDK_API LONG ARNET_Login(ARNET_LOGIN_INFO stLoginInfo, LPARNET_DEVICE_INFO lpDeviceInfo,
	 pfARSysStatusCallBack cbSysStatusCallBack, void* pStatusUser,
	 pfARInfoCallBack fMessageCallBack, void* pMsgUser);

 //Description:注销设备登录
 //Parameters:
 //	[in] lLoginID:设备句柄，ARNET_Login的返回值
 //Return:  成功返回TRUE;失败返回FALSE,具体的错误码由ARNET_GetLastError获取   
 //Remark:                                                                              
 SDK_API BOOL ARNET_LogOut(LONG lLoginID);

 //Description: 打开设备
 //Parameters:
 //	[in] stOpenInfo: 设备打开需要的信息
 // [out] lpDeviceInfo: 返回的设备信息
 // [in] cbSysStatusCallBack:系统状态回调函数
 //	[in] pStatusUser:状态回调函数用户数据
 //	[in] fMessageCallBack:告警回调函数
 //	[in] pMsgUser:告警回调函数用户数据
 // Return:返回-1 表示登录失败, 具体的错误码由ARNET_GetLastError获取；其他值表示登录成功，返回值为设备登录句柄。
 //Remark:

SDK_API LONG ARNET_OpenDevice(ARNET_OPEN_INFO stOpenInfo, LPARNET_DEVICE_INFO lpDeviceInfo,pfARSysStatusCallBack cbSysStatusCallBack, void* pStatusUser,
	 pfARInfoCallBack fMessageCallBack, void* pMsgUser);

 //Description: 查询设备是否在线,同时支持普通和4G
 //Parameters:
 //[in] lLoginID:设备句柄
 //Return:在线返回TRUE，不现在返回FALSE
 SDK_API BOOL ARNET_IsConnected(LONG lLoginID);

 //Description: 注销设备登出用户,同时支持普通和4G
 //Parameters:
 //[in] lLoginID:设备句柄
 //Return:成功返回TRUE,失败返回FALSE,具体的错误码由ARNET_GetLastError获取                                                 
 SDK_API BOOL ARNET_CloseDev(LONG lLoginID);

 /************************************************************************/
 /* 主动上送信息回调
 /************************************************************************/
 //Description: POST消息回调函数
 //Parameters:
 //[in] lLoginID:设备句柄
 //[in] nCmd:消息类型
 //[in] pBuf:消息数据
 //[in] unBufSize:消息数据大小
 //[in] pUser：用户数据
 //Return:返回错误码      
typedef void (CALLBACK *pfARPostMsgCallBack)(LONG lLoginID,enPushOnCmd enCmd, char *pBuf, unsigned int unBufSize, void *pUser);

 //Description: 设备主动上送信息回调设置
 //Parameters:
 //[in] lLoginID:设备句柄
 //[in] fPostMsgCallBack:信息回调函数
 //[in] pUser：回调函数用户数据
 //Return:返回错误码      
 SDK_API LONG ARNET_SetPostMsgCallBack(LONG lLoginID,pfARPostMsgCallBack fPostMsgCallBack,void *pUser);

 //Description: 媒流体全局回调函数设置
 //Parameters:
 //[in] fRealDataCallBack:媒流体回调函数
 //[in] pUser：回调函数用户数据
 //Return:返回错误码   
 SDK_API LONG ARNET_SetRealPlayDataCallBack(pfARRealDataCallBackEX fRealDataCallBack,void *pUser);
 /************************************************************************/
 /* 视频流操作
 /************************************************************************/

 //Description:请求通道预览
 //Parameters:
 //	[in] lLoginID:设备句柄
 //	[in] nCameraID:暂时无效
 //	[in] nStreamType:码流类型，依据enMonBlockType定义
 //	[in] hWnd：码流显示窗口句柄，只在需要SDK内部调用解码库时使用
 //	[in] cbRealDataCallBack：实时流回调函数
 //	[in] pUser: 实时流回调函数用户数据
 //Return: 失败返回-1, 成功返回实时流句柄,具体的错误码由ARNET_GetLastError获取
 //Remark:
 SDK_API LONG ARNET_StartRealPlay(LONG lLoginID,DWORD nCameraID,DWORD nStreamType,
	 pfARRealDataCallBack cbRealDataCallBack, void *pUser);
 //Description:请求通道预览扩展协议
 //Parameters:
 //	[in] lLoginID:设备句柄
 //	[in] nCameraID:设备通道号: 0表示1通道, 1表示2通道；目前机器人支持6通道
 //	[in] nStreamType:码流类型，依据enMonBlockType定义流类型MBT_VIDEO=0,MBT_VIDEOSUB=1,MBT_AUDIO=2,MBT_VIDEOPS=5,MBT_VIDEOSUBPS=6,
 //	[in] pIp:媒流体服务器IP地址
 //	[in] nPort:媒流体服务器端口
 //	[in] enTranMode:媒流体服传输类型
 //	[in] cbRealDataCallBack：实时流回调函数 本地不接收流 设置为NULL
 //	[in] pUser: 实时流回调函数用户数据
 //Return: 失败返回-1, 成功返回实时流句柄,具体的错误码由ARNET_GetLastError获取
 //Remark:
 SDK_API LONG ARNET_StartRealPlayEX(LONG lLoginID,DWORD nCameraID,DWORD nStreamType,char *pIp, int nPort, EnumMonTranMode enTranMode,
	 pfARRealDataCallBack cbRealDataCallBack, void *pUser);
 //Description:关闭预览
 //Parameters:
 //	[in] lRealHandle:实时流句柄
 //Return:成功返回TRUE,失败返回FALSE,具体的错误码由ARNET_GetLastError获取
 //Remark:
 SDK_API BOOL ARNET_StopRealPlay(LONG lRealHandle);

 //Description:关闭实时流
 //Parameters:
 //	[in] szDeviceID:设备ID
 //	[in] nCameraID:设备通道号: 0表示1通道, 1表示2通道；目前机器人支持6通道
 //	[in] nStreamType:码流类型，依据enMonBlockType定义流类型MBT_VIDEO=0,MBT_VIDEOSUB=1,MBT_AUDIO=2,MBT_VIDEOPS=5,MBT_VIDEOSUBPS=6,

 SDK_API BOOL ARNET_StopRealPlayEX(char * szDeviceID, DWORD nCameraID,DWORD nStreamType);

 /************************************************************************/
 /* 语音对讲
 /************************************************************************/

 // 功能:开始双向语音对讲
 // Parameters:
 //	[in] lLoginID:设备登录句柄
 //	[in] cbAudioDataCallBack:音频流回调函数
 //	[in] pUser:回调函数用户
 // Return:失败返回-1, 成功返回对讲流句柄,具体的错误码由ARNET_GetLastError获取
 // Remark:
 SDK_API LONG ARNET_StartTalk(LONG lLoginID,pfARAudioDataCallBack cbAudioDataCallBack,void* pUser);

 //Description:停止双向语音对讲
 // Parameters:
 //[in] lTalkHandle:对讲流句柄
 // Return:成功返回TRUE,失败返回FALSE,具体的错误码由ARNET_GetLastError获取
 // Remark:
 SDK_API BOOL ARNET_StopTalk(LONG lTalkHandle);


// 功能:打开通道声音
 // Description:打开通道声音
 // Parameters:
 //	[in] lLoginID:设备句柄
 //	[in] dwAudioChan:暂时无效
 //	[in] cbAudioDataCallBack:音频流回调函数
 //	[in] pUser:回调函数用户
 // Return:失败返回-1, 成功返回音频流句柄,具体的错误码由ARNET_GetLastError获取
 // Remark:
 SDK_API LONG ARNET_StartAudio(LONG lLoginID,DWORD dwAudioChan,
	 pfARAudioDataCallBack cbAudioDataCallBack,void* pUser);

 // Description:关闭通道声音
 // Parameters:
 //	[in] lAudioHandle:音频流句柄
 // Return:成功返回TRUE,失败返回FALSE,具体的错误码由ARNET_GetLastError获取
 //	Remark:
 SDK_API BOOL ARNET_StopAudio(LONG lAudioHandle);

 // Description:请求对设备发声音
 // Parameters:
 //	[in] lLoginID:设备登录句柄
 //	[in]　dwAudioChan:暂时无效
 // Return:失败返回-1, 成功返回讲话句柄,具体的错误码由ARNET_GetLastError获取
 //	Remark:
 SDK_API LONG ARNET_StartSpeak(LONG lLoginID,DWORD dwAudioChan);

 // Description:请求对设备发声音扩展 
 // Parameters:
 //	[in] lLoginID:设备登录句柄
 //	[in]　pIp:媒流体IP地址
 //	[in]　nPort:媒流体端口
 //	[in]　enTranMode:媒流体 传输方式
 // Return:失败返回-1, 成功返回讲话句柄,具体的错误码由ARNET_GetLastError获取
 //	Remark:
 SDK_API LONG ARNET_StartSpeakEX(LONG lLoginID,char *pIp, int nPort, EnumMonTranMode enTranMode);

 // Description:对设备发送语音数据
 // Parameters:
 //	[in] lSpeakHandle:讲话句柄
 //	[in] pBuffer:存放语音数据的缓冲区,目前只支持 G711A（8000HZ,64000bps）音频
 //	[in] dwBufSize:语音数据大小
 // Return:成功返回TRUE,失败返回FALSE,具体的错误码由ARNET_GetLastError获取
 // Remark:
 SDK_API BOOL ARNET_SpeakSendData(LONG lSpeakHandle, char *pBuffer, DWORD dwBufSize);
 // Description:对设备发送语音数据扩展
 // Parameters:
 //	[in] szDeviceID:设备唯一ID
 //	[in] pBuffer:存放语音数据的缓冲区,目前只支持 G711A（8000HZ,64000bps）音频
 //	[in] dwBufSize:语音数据大小
 // Return:成功返回TRUE,失败返回FALSE,具体的错误码由ARNET_GetLastError获取
 // Remark:
 SDK_API BOOL ARNET_SpeakSendDataEX(char * szDeviceID, char *pBuffer, DWORD dwBufSize);

 // Description:停止对设备发声音
 // Parameters:
 //	[in] lSpeakHandle:讲话句柄
 // Return:成功返回TRUE,失败返回FALSE,具体的错误码由ARNET_GetLastError获取
 // Remark:
 SDK_API BOOL ARNET_StopSpeak(LONG lSpeakHandle);

 /************************************************************************/
 /* 远程升级
 /************************************************************************/

 // 功能:更新文件系统
 // lLoginID:设备登录句柄
 // eFileType:文件类型,现只支持GS_UPD_BIOS
 // dwFileSize:文件大小
 // iFileID:返回的文件ID
 // 成功返回TRUE,失败返回FALSE,具体的错误码由ARNET_GetLastError获取 
 SDK_API BOOL ARNET_UpdateFile(LONG lLoginID, enUpdateFileType eFileType, DWORD dwFileSize, int* iFileID);

 // 功能:发送更新文件
 // lLoginID:设备登录句柄
 // pbuf:更新文件数据
 // nLen:数据大小
 // iFileID:文件ID
 // 成功返回TRUE,失败返回FALSE,具体的错误码由ARNET_GetLastError获取 
 SDK_API BOOL ARNET_SendUpdateFile(LONG lLoginID,char *pbuf,int nLen, int iFileID);

 /************************************************************************/
 /* 参数读取和配置
 /************************************************************************/

 // 功能:参数读取和配置
 // nCmd:命令ID
 // pInBuf:发送buf
 // unInSize:发送buf大小
 // pOutBuf:接收buf
 // unOutSize:接收数据大小
 // iOutBufSize:接收buf大小
 // iFileID:文件ID
 // 成功返回 0,失败返回负数；具体的错误码由ARNET_GetLastError获取 
 SDK_API LONG ARNET_TransConfig(LONG lLoginID, int nCmd,
	 char *pInBuf, unsigned int unInSize,
	 char *pOutBuf, unsigned int *unOutSize,int iOutBufSize);
	 
 // 功能:参数配置
 // lLoginID:设备登录ID
 // nCmd:命令ID
 // pInBuf:发送buf
 // unInSize:发送buf大小
 // 成功返回 0,失败返回负数；具体的错误码由ARNET_GetLastError获取 
 SDK_API LONG ARNET_SetConfig(LONG lLoginID, int nCmd,char *pInBuf, unsigned int unInSize);
 
 // 功能:先机器人发送enRobotCmd命令
 // lLoginID:设备登录ID
 // nCmd:命令ID
 // pInBuf:发送buf
 // unInSize:发送buf大小
 // pOutBuf:接收buf
 // [in][out] unOutSize: 输入为pOutBuf的大小，输出为实际回复的数据大小
 // 成功返回 0,失败返回负数；具体的错误码由ARNET_GetLastError获取 
 SDK_API LONG ARNET_SendRobotCmd(LONG lLoginID, enRobotCmd nCmd,char *pInBuf, unsigned int unInSize,char *pOutBuf, unsigned int *unOutSize);


 // 功能:向机器人发送文本命令
 // [in] lLoginID:设备登录ID
 // [in] pInText: 向机器人发送的文本
 // [in] unInSize: 发送的文本大小
 // [out] pOutBuf: 接收机器人回复的buf
 // [in][out] unOutSize: 输入为pOutBuf的大小，输出为实际回复的数据大小
 // 成功返回 0,失败返回负数；具体的错误码由ARNET_GetLastError获取
 SDK_API LONG ARNET_SendRobotText(LONG lLoginID, char *pInText, unsigned int unInSize,char *pOutText, unsigned int *unOutSize);

 //Description:向设备发送命令接口
 // Parameters:
 // [in] lLoginID: 设备句柄
 // [in] nCmd: 下发的命令号
 // [in] pInBuf: 下发的命令数据
 // [in] unInSize: 下发的命令数据长度
 // Return：成功返回TRUE; 失败返回FALSE
 SDK_API  BOOL ARNET_SendCmd(LONG lLoginID, enPushDownCmd nCmd, char *pInBuf, unsigned int unInSize);

 /************************************************************************/
 /* 球机云台控制
 /************************************************************************/

 // 功能:云台控制
 // nPtzCmd:云台控制命令
 // nParam1:云台控制参数1，具体意思根据nPtzCmd不同而不同
 // nParam2:云台控制参数2，具体意思根据nPtzCmd不同而不同
 // 成功返回0,失败返回错误码,具体的错误码由ARNET_GetLastError获取 
 SDK_API BOOL ARNET_PtzCtrl(LONG lLoginID, enSPAction nPtzCmd,BYTE nParam1,BYTE nParam2);

 //Description:读取预置点
 //Parameters:
 //	[in] lLoginID:设备句柄
 //	[out] pPrePointList:返回预置点信息，包括总数、ID和名称
 //Return: 成功返回0;失败返回错误码,具体的错误码由ARNET_GetLastError获取
 //Remark:
 SDK_API BOOL ARNET_GetPrePoint(LONG lLoginID, ARNET_PRE_POINT_LIST *pPrePointList);

 //Description:预置点控制
 //Parameters:
 //	[in] lLoginID:设备句柄
 //	[in] enPtzCmd: 控制命令，可用SP_CLEAR_POINT清除预置点和SP_GOTO_POINT调用预置点
 //	[in] byID: 预置点ID
 //Return: 成功返回0;失败返回错误码,具体的错误码由ARNET_GetLastError获取
 //Remark:
 SDK_API BOOL ARNET_PrePointCtrl(LONG lLoginID, enSPAction enPtzCmd,BYTE byID);

 //Description:新增或修改预置点
 //Parameters:
 //	[in] lLoginID:设备句柄
 //	[in] byID: 预置点ID
 //	[in] pchName: 预置点名称，最大长度16个字符
 //Return: 成功返回0;失败返回错误码,具体的错误码由ARNET_GetLastError获取
 //Remark:
 SDK_API BOOL ARNET_ModifyPrePoint(LONG lLoginID,BYTE byID, char *pchName);


 //Description:读取巡航列表
 //Parameters:
 //	[in] lLoginID:设备句柄
 //	[out] pCruiseList:返回巡航列表，包括总数、ID和名称
 //Return: 成功返回0;失败返回错误码,具体的错误码由ARNET_GetLastError获取
 //Remark:
 SDK_API BOOL ARNET_GetCruiseList(LONG lLoginID, ARNET_CRUISE_LIST *pstCruiseList);

 //Description:读取某个巡航的详细信息
 //Parameters:
 //	[in] lLoginID:设备句柄
 //	[in] byID: 巡航ID
 //	[out] pstCruiseInfo:返回巡航信息，包括预置点和预置点停留时间
 //Return: 成功返回0;失败返回错误码,具体的错误码由ARNET_GetLastError获取
 //Remark:
 SDK_API BOOL ARNET_GetCruiseInfo(LONG lLoginID, BYTE byID, ARNET_CRUISE_INFO *pstCruiseInfo);

 //Description:调用巡航、停止巡航、删除巡航
 //Parameters:
 //	[in] lLoginID:设备句柄
 //	[in] enPtzCmd: 控制命令，可用SP_CRUISE_START调用巡航、SP_CRUISE_STOP停止巡航和SP_CRUISE_DELETE删除巡航
 //	[in] byID: 巡航ID
 //Return: 成功返回0;失败返回错误码,具体的错误码由ARNET_GetLastError获取
 //Remark:
 SDK_API BOOL ARNET_CruiseCtrl(LONG lLoginID, enSPAction enPtzCmd,BYTE byID);

 //Description:新增或修改巡航
 //Parameters:
 //	[in] lLoginID:设备句柄
 //	[in] byID: 巡航ID
 //	[in] pchName: 巡航名称，最大长度16个字符
 //	[in] stCruiseInfo: 巡航信息
 //Return: 成功返回0;失败返回错误码,具体的错误码由ARNET_GetLastError获取
 //Remark:
 SDK_API BOOL ARNET_ModifyCruise(LONG lLoginID,BYTE byID, char *pchName, ARNET_CRUISE_INFO stCruiseInfo);

 //Description:设置看守状态
 //Parameters:
 //	[in] lLoginID:设备句柄
 //	[in] byStatus: 1代表打开，2代表关闭
 //Return: 成功返回0;失败返回错误码,具体的错误码由ARNET_GetLastError获取
 //Remark:
 SDK_API BOOL ARNET_SetKeepWatchStatus(LONG lLoginID,BYTE byStatus);

 //Description:读取看守状态
 //Parameters:
 //	[in] lLoginID:设备句柄
 //	[out] byStatus: 1代表打开，2代表关闭
 //Return: 成功返回0;失败返回错误码,具体的错误码由ARNET_GetLastError获取
 //Remark:
 SDK_API BOOL ARNET_GetKeepWatchStatus(LONG lLoginID,BYTE *byStatus);

 //Description:3D定位
 //Parameters:
 //	[in] lLoginID:设备句柄
 //	[in] StartX: 3D定位起始点X坐标
 //	[in] StartY: 3D定位起始点Y坐标
 //	[in] EndX: 3D定位结束点X坐标
 //	[in] EndY: 3D定位结束点Y坐标
 //Return: 成功返回0;失败返回错误码,具体的错误码由ARNET_GetLastError获取
 //Remark:起始点和结束点的坐标需要换算为352*288的分辨率大小下发
 SDK_API BOOL ARNET_3DPTZCTRL(LONG lLoginID, WORD StartX,WORD StartY,WORD EndX,WORD EndY);


 /************************************************************************/
 /* 录像数据获取
 /************************************************************************/

 //Description: 开始录像数据获取
 //Parameters:	
 //	[in]lLoginID:设备登录句柄
 // [in] tGetRecord:录像获取条件结构体
 // [in] cbRecordDataCallBack: 录像数据接收回调函数
 // [in] pDataUser: 回调的时候直接传给用户
 //Return: 成功返回下载句柄,失败返回-1,具体的错误码由ARNET_GetLastError获取
 //Remark:

 SDK_API LONG ARNET_StartGetRecord(LONG lLoginID,TGetRecord tGetRecord,pfARRecordDataCallBack cbRecordDataCallBack, void* pDataUser,long long *pDataSize);

 //Description: 停止录像数据获取
 //Parameters:	
 //		[in] lRecordHandle:ARNET_StartGetRecord的返回值
 //Return: 成功返回TRUE,失败返回FALSE,具体的错误码由ARNET_GetLastError获取
 //Remark:
 SDK_API BOOL ARNET_StopGetRecord(LONG lRecordHandle);

// 功能:获取日志信息
// lLoginID:设备登录句柄
// stSysLogFilter:日志筛选条件
// 成功返回TRUE,失败返回FALSE,具体的错误码由ARNET_GetLastError获取 
 SDK_API BOOL ARNET_GetSysLog(LONG lLoginID, TSysLogFilter stSysLogFilter, pfARQueryLogCallBack cbQueryLogCallBack, void* pUser);

 //功能：添加标签
 //参数说明
 //lLoginID：登录句柄
 //pSei：标签的详细信息，其中stID置为-1 
 SDK_API  BOOL ARNET_Lable_Add(LONG lLoginID, AR_Lable *pSei);

 //功能：修改标签
 //参数说明
 //lLoginID：登录句柄
 //pSei：标签的详细信息，其中stID需大于等于0 
 SDK_API  BOOL ARNET_Lable_Update(LONG lLoginID, AR_Lable *pSei);

 //功能：删除标签
 //参数说明
 //lLoginID：登录句柄
 //nLableID：需要删除的标签ID，-1 表示删除所有标签
 SDK_API  BOOL ARNET_Lable_Delete(LONG lLoginID, int nLableID);

 //功能：居中标签
 //参数说明
 //lLoginID：登录句柄
 //nLableID：需要居中的标签ID
 SDK_API  BOOL ARNET_Lable_Center(LONG lLoginID, int nLableID);

 //功能：查询标签列表
 //参数说明
 //lLoginID：登录句柄
 //pSei：用于存储获取到的列表
 //pNum：输入表示pSei能存储的个数，输出表示获得的个数
 SDK_API  BOOL ARNET_Lable_Query(LONG lLoginID, AR_Lable *pSei, int *pNum);

 //功能：查询设备标签数量
 //参数说明
 //lLoginID：登录句柄
 //pDeviceMaxCount：用于获取设备支持的最大标签个数
 //pCount：用于获取已经创建的标签个数
 SDK_API BOOL ARNET_Lable_QueryCount(LONG lLoginID, int *pDeviceMaxCount,int *pCount);

 //功能：配置地理位置信息
 //参数说明
 //lLoginID：登录句柄
 //pLocation：地理位置信息
 SDK_API BOOL ARNET_AR_SetLocation(LONG lLoginID, AR_LOCATION  *pLocation);

 //功能：设置正北方向
 //参数说明
 //lLoginID：登录句柄
 //bAuto：0为自动，1为手动，设1时当前位置为正北方向，当前P变为360
SDK_API BOOL ARNET_AR_SetNorth(LONG lLoginID, BOOL bAuto);

//功能：设置筒机镜头参数初始化
//参数说明
//lLoginID：登录句柄
//bAuto：保留，目前只设1
SDK_API BOOL ARNET_AR_SetLenInit(LONG lLoginID, BOOL bAuto);

//功能：设置筒机自动聚焦
//参数说明
//lLoginID：登录句柄
//bAuto：保留，目前只设1
SDK_API BOOL ARNET_AR_SetAutoFocus(LONG lLoginID, BOOL bAuto);

 //功能：配置PTZ信息
 //参数说明
 //pPtz：航向角、俯仰角、视场角数据
 SDK_API BOOL ARNET_AR_SetPTZ(LONG lLoginID, AR_PTZ  *pPtz, AR_PTZ*pPtzCheck);

 //功能：GOTO PTZ
 //fPan: 水平角度相对于正北方向逆时针+顺时针-
 //fTilt: 垂直方向角度相对于水平线0度逆时针+顺时针-
 //fDistance: 焦距
 //fZoomValue: 距离
 SDK_API BOOL ARNET_GotoPTZ(LONG lLoginID, float fPan, float fTilt, float fDistance, float fZoomValue);

 //功能：设置参考点
 //pRef: 参考点数组
 //nNum: 数组大小
 SDK_API BOOL ARNET_AR_SetReference(LONG lLoginID, AR_Reference *pRef, int nNum);

 //功能：添加单个参考点到设备端，在原有的基础上增加
 SDK_API BOOL ARNET_AR_SetOneReference(LONG lLoginID, AR_Reference *pRef);

 SDK_API BOOL ARNET_AR_GetReference(LONG lLoginID, AR_Reference *pRef, int *pNum);

 SDK_API BOOL ARNET_AR_CmpToRef(LONG lLoginID, int x, int y, float *pHeight, float *pDeltT);

 SDK_API BOOL ARNET_AR_AddReference(LONG lLoginID, AR_PTZ ptzBottom1, AR_PTZ ptzTop1, AR_PTZ ptzBottom2, AR_PTZ ptzTop2, float fMeasuredH, AR_Reference *pRef);

 //功能：删除单个参考点
 //参数说明
 //lLoginID：登录句柄
 //index：要删除的参考点下标
 SDK_API BOOL ARNET_AR_DelRef(LONG lLoginID, int index);
 
 //功能：获取所有参考点当前屏幕坐标
 //参数说明
 //lLoginID：登录句柄
 //arPos[in]：参考点坐标数组首地址，坐标是在1920*1080的尺寸下
 //pNum[in/out]：传进去数组长度，传出实际获取的参考点个数
 SDK_API BOOL ARNET_AR_GetRefPos(LONG lLoginID, AR_POS *arPos, int *pNum);

 //功能：获取地理位置信息
 //参数说明
 //lLoginID：登录句柄
 //pLocation：地理位置信息
 SDK_API BOOL ARNET_AR_GetLocation(LONG lLoginID, AR_LOCATION  *pLocation);

 //功能：获取PTZ信息
 //参数说明
 //pPtz：航向角、俯仰角、视场角数据
 SDK_API BOOL ARNET_AR_GetPTZ(LONG lLoginID, AR_PTZ  *pPtz, AR_PTZ*pPtzCheck);

 //功能：获取传入点的PT值
 //参数说明：
 //lLoginID:登录句柄
 //p[out]:传入点的P值
 //t[out]:传入点的T值
 //x[in]:传入点的x坐标
 //y[in]:传入点的y坐标
 SDK_API BOOL ARNET_Lable_GetPT(LONG lLoginID, double *p, double *t, int x, int y);
 SDK_API BOOL ARNET_Lable_GetPT1(LONG lLoginID, double *p, double *t, int x, int y, int bPTed);

 SDK_API BOOL ARNET_AR_GetHeight(LONG lLoginID, float *fHeight, float fOriH, float fDeltT, int x1, int y1, int x2, int y2);

 SDK_API BOOL ARNET_AR_GetLength(LONG lLoginID, float *fLength, float fOriH, float fDeltT, int x1, int y1, int x2, int y2);

 SDK_API BOOL ARNET_SetARParamCallBack(LONG lLoginID,fARParamCBFun ARParamCBFun,void* pUser);

 SDK_API BOOL ARNET_Lable_Pos_Adjust(LONG lLoginID, int *pnLableID,int nNum,int x, int y);

 //功能：添加标签
 //参数说明
 //lLoginID：登录句柄
 //pSei：标签的详细信息，其中stID置为-1 
 SDK_API  BOOL ARNET_LableEx_Add(LONG lLoginID, AR_LableEx *pSei);

 //功能：修改标签
 //参数说明
 //lLoginID：登录句柄
 //pSei：标签的详细信息，其中stID需大于等于0 
 SDK_API  BOOL ARNET_LableEx_Update(LONG lLoginID, AR_LableEx *pSei);

 //功能：查询标签列表
 //参数说明
 //lLoginID：登录句柄
 //pSei：用于存储获取到的列表
 //pNum：输入表示pSei能存储的个数，输出表示获得的个数
 SDK_API  BOOL ARNET_LableEx_Query(LONG lLoginID, AR_LableEx *pSei, int *pNum);

 //typedef void (CALLBACK* fARLableExCBFun)(int handle, AR_OPERATION nOperation, AR_LableEx  *pSei, int nNum, void*  pUser);//增强现实标签回调函数
 SDK_API BOOL ARNET_SetARLableExCallBack(LONG lLoginID, fARLableExCBFun ARLableCBFun, void* pUser);

 // 云台定时任务 接口
 SDK_API BOOL ARNET_SetPTZTimedTask(LONG lLoginID, TPTZTimedTaskParam PTZTimedTaskParam);

 SDK_API BOOL ARNET_GetPTZTimedTask(LONG lLoginID, TPTZTimedTaskParam* PTZTimedTaskParam);
 
 //Description: 发送问题结果和人脸识别结果
 // Parameters:
 // [in] szDeviceID:设备ID
 // [in] pTextBuf: 问题答案文本数据
 // [in] nTextLen：问题答案文本数据长度
 // [in] pVoiceBuf: 问题答案音频数据
 // [in] nVoiceLen：问题答案音频数据长度
 // Return：成功返回TRUE; 失败返回FALSE
 SDK_API BOOL ARNET_SendQuestionAsw(LONG lLoginID, char *pTextBuf,int nTextLen,char *pVoiceBuf, int nVoiceLen);

 //Description:人脸检测图片全局回调函数
 // Parameters:
 // [in] lLoginID:设备句柄
 // [in] fARPictureCBFun: 图片回调函数
 // [in] pUser：用户数据
 // Return：成功返回TRUE; 失败返回FALSE
 SDK_API BOOL ARNET_SetGlobalARPictureCallBack(fGlobalARPictureCBFun CBFun,void* pUser);

#endif