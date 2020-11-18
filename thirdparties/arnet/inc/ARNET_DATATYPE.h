#if !defined(SDK_DATATYPE_H__INCLUDED_)
#define SDK_DATATYPE_H__INCLUDED_

#include<windef.h>

#ifndef WIN32

#ifndef BOOL
typedef int BOOL;
#endif
#ifndef BYTE
typedef unsigned char BYTE;
#endif
#ifndef PBYTE
typedef unsigned char * PBYTE;
#endif
#ifndef LPBYTE
typedef unsigned char * LPBYTE;
#endif
#ifndef WORD
typedef unsigned short WORD;
#endif
#ifndef DWORD
typedef unsigned int DWORD;
#endif
#ifndef UINT
typedef unsigned int UINT;
#endif

#ifndef FALSE
#define FALSE 0
#endif
#ifndef TRUE
#define TRUE  1
#endif
#endif
#define SDK_DEVICE_SERIAL_LEN          32
#define SDK_USER_NAME_LEN              16
#define SDK_USER_PSW_LEN               16
#define SDK_MAX_PRODUCT_MODEL_LEN      32
#define SDK_MAX_REC_FILE_PATH          64
#define SDK_PRE_POINT_NAME_LEN		   17/*预置点名称长度*/
#define SDK_PRE_POINT_MAX_NUM		   255/*预置点最大个数*/
#define SDK_CRUISE_MAX_NUM			   12/*巡航最大个数*/
#define SDK_MAX_BALL_PARAM_BUF		   10000/*球机参数buf*/

#ifdef _WIN32
#pragma pack(1)
#endif
//SDK专用错误码
enum	
{
	IPCRET_SDK_INIT_ERROR = -301,//SDK初始化出错
	IPCRET_RESPONE_TIMEOUT = -302,//设备回复超时(无响应)
	IPCRET_OPENFILEERROR = -303,//打开文件出错
	IPCRET_MGHANDLE_NOTEXIST = -304,//设备句柄不存在
	IPCRET_WRONG_PARAMETER = -305,//参数错误
	IPCRET_DEALERROR = -306,//回复数据的长度不对
	IPCRET_OUTBUF_NOT_ENOUGH = -307,//输出缓存不足
	IPCRET_CONNECT_BREAK	= -308,//连接断开
	IPCRET_SDK_UNINIT		= -309,//SDK未初始化
	IPCRET_RESPONE_ERR = -310,//设备回复数据错误
	IPCRET_RECVBUF_TOO_SMALL = -311,//缓冲区太小
	IPCRET_NOT_SUPPORT = -312,//设备不支持此命令
	IPCRET_MEDIACONNECT_TIMEOUT = -320,//媒体连接超时
	IPCRET_MEDIAASW_TIMEOUT = -321,//媒体心跳应答超时
	IPCRET_GET_HANDLE_FAILED = -322,//句柄分配失败
};

typedef enum EnumDeviceType
{
	GS_DEV_IPC = 0,    // IP Camera
	GS_DEV_DVS,        // Video Server
	GS_DEV_DVR,        // Video Recorder
	GS_DEV_MAX
}EnumDeviceType;

typedef enum  EnumVidEncType
{
	GS_VIDENC_NONE,     // No video encode type
	GS_VIDENC_HIS264,   // Hisilicon H264
	GS_VIDENC_HIK264,   // Hikvision H264 (Seems 263+)
	GS_VIDENC_DIVXMP4,  // DIVX MPEG4
	GS_VIDENC_XVIDMP4,  // XVID MPEG4
}EnumVidEncType;

typedef enum EnumAudEncType
{
	GS_AUDENC_DEFAULT,      // Default : AUDENC_G726
	GS_AUDENC_G711A,        /* G.711 A率*/
	GS_AUDENC_G711Mu,       /* G.711 Mu率*/
	GS_AUDENC_G723,         /* G.723 */
	GS_AUDENC_G722,         /* G.722 */
	GS_AUDENC_G726,         /* hisilicon define as G.726 */
	GS_AUDENC_ADPCM,        /* hisilicon define as ADPCM */
	GS_AUDENC_ULAW,         /* mu-law */
	GS_AUDENC_ALAW,         /* a-law */
	GS_AUDENC_GSM,          /* GSM */
	GS_AUDENC_S16BE_STEREO, /* linear 16, 44.1khz, 2 channel */
	GS_AUDENC_S16BE_MONO,   /* linear 16, 44.1khz, 1 channel */
	GS_AUDENC_MPEGAUDIO,    /* mpeg audio */
	GS_AUDENC_AAC,    /* aac audio */
}EnumAudEncType;


typedef enum EnumVidStd
{
	GS_STD_PAL,
	GS_STD_NTSC
}EnumVidStd;

typedef enum
{
	GS_VR_720P  = 0x01,   // 720P
	GS_VR_VGA  = 0x02,    // VGA
	GS_VR_CIF  = 0x04,    // CIF
	GS_VR_QVGA  = 0x08,   // QVGA
	GS_VR_SXGA   = 0x10,

	GS_VR_D1     = 0x20, // 704 x 576 , 704 x 480
	GS_VR_QCIF   = 0x40, // 176 x 144
}EnumVideoResolution;

typedef enum
{                     //   [PAL]       [NTSC]
	GS_VRN_D1     = 0x01, // 704 x 576 , 704 x 480
	GS_VRN_HD1    = 0x02, // 704 x 288 , 704 x 240
	GS_VRN_CIF    = 0x03, // 352 x 288 , 352 x 240
	GS_VRN_QCIF   = 0x04, // 176 x 144
	GS_VRN_VGA    = 0x05, // 640 x 480
	GS_VRN_HVGA   = 0x06, // 640 x 240
	GS_VRN_QVGA   = 0x07, // 320 x 240
	GS_VRN_720P   = 0x08, // 1280 x 720
	GS_VRN_SXGA   = 0x09, // 1280 x 1024
	GS_VRN_UXGA   = 0x0A, // 1600 x 1200
	GS_VRN_1080P  = 0x0B, // 1920 x 1080
	GS_VRN_XGA    = 0x0C, // 1024 x 768
	GS_VRN_HDVGA  = 0x0D, // 1280 x 960
}EnumVideoResolutionName;

typedef enum
{
	GS_MTM_TCP,
	GS_MTM_UDP,
	GS_MTM_MULTICAST,
	RTSP_UNVIEW,//宇视rtsp码流
	RTSP_GSUNVIEW,//高新兴宇视rtsp PS码流
	RTSP_DVS,//DVS rtsp码流
	RTSP_DALI,//大立 rtsp码流
}EnumMonTranMode;


typedef enum
{
	GS_PBS_PAUSE,         // Pause, no transmission
	GS_PBS_PLAY,          // Normal speed, frame rate as real-time record
	GS_PBS_HALF,          // 1/2 normal
	GS_PBS_QUARTER,       // 1/4 normal
	GS_PBS_DOUBLE,        // 2x normal
	GS_PBS_FOURFOLD,      // 4x normal
	GS_PBS_DOWNLOAD_FILE, // Max Speed to download record file
}EnumPbSpeed;

typedef enum
{
	GS_ST_CCD,
	GS_ST_CMOS,
}EnumSensorType;

typedef enum
{
	GS_HDT_NONE,
	GS_HDT_720P,
	GS_HDT_SXGA,
	GS_HDT_UXGA,
	GS_HDT_1080P,
}EnumHighDefType; // High Definition Type

typedef enum
{
	I_FRAME = 0,
	P_FRAME = 1,
	G711A_FRAME = 4
}enVidFrmType;	//帧类型

typedef struct  ARNET_LOGIN_INFO       // 用户登录参数
{
	char             sDevIP[20];                      // 设备ip
	WORD             wDevPort;                     // 设备端口
	char             LoginName[SDK_USER_NAME_LEN+1];   // 登录用户名
	char             LoginPsw[SDK_USER_PSW_LEN+1];     // 登录密码
	EnumMonTranMode  eMonTranMode;                 // 协议模式
	WORD             wClientUdpPort;               // 客户端UDP端口号，当MonTranMode == MTM_UDP有效
	BYTE             bUdpMakeHole;                 // 当UdpMakeHole == 1时服务器忽略ClientUdpPort.
}ARNET_LOGIN_INFO;
typedef ARNET_LOGIN_INFO NET_LOGIN_INFO;

typedef struct ARNET_IMAGEFIXEDATTRT
{
	EnumVideoResolution       eVidRes;			            // 图像分辨率
	EnumVideoResolutionName   eVidResName;	                // 图像相对分辨率
	WORD                      Width;						// 图像宽度
	WORD                      Height;						// 图像高度
	BYTE                      MaxFrmRate;					// 最大帧率
	WORD                      DefaultBps;					// 默认码流
	BYTE                      Reserved[5];
}ARNET_IMAGEFIXEDATTRT;
typedef ARNET_IMAGEFIXEDATTRT NET_IMAGEFIXEDATTRT;

typedef struct ARNET_DEVICE_INFO    // 设备信息
{
	EnumDeviceType      eDevType;
	char                ProductModel[SDK_MAX_PRODUCT_MODEL_LEN+1];
	char                DeviceSerial[SDK_DEVICE_SERIAL_LEN+1];
	WORD                wBiosVer;
	WORD                wNetVer;
	EnumVidStd          eVidStd;
	EnumVidEncType      eVidEncType;
	EnumAudEncType      eAudEncType;
	BYTE                ChanCnt;
	BYTE                AlmInCnt;
	BYTE                AlmOutCnt;
	BYTE                SupportedVidRes;
	BYTE                bSupportStorage;
	BYTE                bStoragePlugged;
	WORD                wRecState;
	BYTE                bSupportWifi;
	BYTE                bSupport2Streams;
	EnumSensorType      eSensorType;
	EnumHighDefType     eHighDefType;
	BYTE                SupportedVidResSub;
	ARNET_IMAGEFIXEDATTRT ImgFixAttr[4];
	ARNET_IMAGEFIXEDATTRT ImgFixAttrSub[2];
	DWORD				dwPairID;
	BYTE                Reserved[59];
}ARNET_DEVICE_INFO, *LPARNET_DEVICE_INFO;
typedef ARNET_DEVICE_INFO NET_DEVICE_INFO;
typedef LPARNET_DEVICE_INFO LPNET_DEVICE_INFO;

typedef struct ARNET_PRE_POINT
{
	BYTE byId;                   //预置点1~255
	char chName[SDK_PRE_POINT_NAME_LEN];//预置点名称
}ARNET_PRE_POINT;
typedef ARNET_PRE_POINT NET_PRE_POINT;

typedef struct ARNET_PRE_POINT_LIST
{
	BYTE byNum;  // 预置点个数
	ARNET_PRE_POINT stPrePoint[SDK_PRE_POINT_MAX_NUM]; // 预置点信息
}ARNET_PRE_POINT_LIST;
typedef ARNET_PRE_POINT_LIST NET_PRE_POINT_LIST;

typedef struct ARNET_CRUISE
{
	BYTE byId;                   //巡航1-12
	char chName[SDK_PRE_POINT_NAME_LEN];//巡航名称
}ARNET_CRUISE;
typedef ARNET_CRUISE  NET_CRUISE;

typedef struct ARNET_CRUISE_LIST
{
	BYTE byNum;  // 巡航个数
	ARNET_CRUISE stCruiseList[SDK_CRUISE_MAX_NUM]; // 巡航信息
}ARNET_CRUISE_LIST;
typedef ARNET_CRUISE_LIST NET_CRUISE_LIST;

typedef struct ARNET_CRUISE_PREPOINT_INFO
{
	BYTE byPrePointId;	//巡航的预置点
	BYTE byWaitTime;	//停留时间
}ARNET_CRUISE_PREPOINT_INFO;//每条巡航的信息
typedef ARNET_CRUISE_PREPOINT_INFO  NET_CRUISE_PREPOINT_INFO;

typedef struct ARNET_CRUISE_INFO
{
	BYTE byPrePointNum;	//巡航中设置的预置点个数
	ARNET_CRUISE_PREPOINT_INFO stInfo[32];//支持32预置点
}ARNET_CRUISE_INFO;
typedef ARNET_CRUISE_INFO  NET_CRUISE_INFO;

typedef struct ARNET_TRAJECTORY//qxs 2013.7.31
{
	BYTE byId;                   //轨迹ID 1~8
	char chName[SDK_PRE_POINT_NAME_LEN];//轨迹名称
}ARNET_TRAJECTORY;
typedef ARNET_TRAJECTORY  NET_TRAJECTORY;

typedef struct ARNET_TRAJECTORY_LIST
{
	BYTE byNum;  // 轨迹个数
	ARNET_TRAJECTORY stTrajectory[8]; // 轨迹信息
}ARNET_TRAJECTORY_LIST;

// 云台定时任务 控件接口数据结构
struct _TPTZTimedTask
{
	BYTE bTaskEnable; // 任务使能 1， 任务不使能 2
	BYTE Week;        // 0 整个星期有效， 1-7 某个星期几有效
	BYTE StartHour;   // 启动时钟数
	BYTE StartMin;    // 启动分钟数
	BYTE EndHour;     // 停止时钟数
	BYTE EndMin;      // 停止分钟数
	BYTE ActType;     // 任务类型：预置位 1，扫描 2, 巡航 4，轨迹 5
	BYTE ActId;       // 任务类型中的id号 预置位 1-255，扫描 1-12, 巡航 1-12，轨迹 1-8
	BYTE Reserved[7];
};// 15 BYTE
typedef struct _TPTZTimedTask TPTZTimedTask;

#define PTZ_TIMED_TASK_MAX_NUM 8

struct _TPTZTimedTaskParam
{
	TPTZTimedTask TaskParam[PTZ_TIMED_TASK_MAX_NUM];
};
typedef struct _TPTZTimedTaskParam TPTZTimedTaskParam;


typedef struct ARNET_INIT_PARAM
{
	int nHeartBeatInterval;	//心跳间隔 ，设置为0表示默认值5000毫秒
	int nDisconnectTime;    //断线超时时间，设置为0表示默认值30000毫秒
	int nAutoReConnectTime; //自动重连时间，旧的参数，目前SDK内部不重连
	char m_szServerIP[20];		//被动连接服务IP，设置为NULL表示默认本机ip,目前请填NULL
	int m_nServePort;			//被动连接服务端口，设置为0表示不启动4G服务
}ARNET_INIT_PARAM;
typedef ARNET_INIT_PARAM NET_INIT_PARAM;

typedef struct TGetRecord
{
	int eMonBlockType;//录像文件格式,见net_protocol.h文件的enMonBlockType定义中，大于MBT_STORAGEH264的选项
	unsigned short dwEventType; //0x0000:表示查询全部事件类型;0x0001:中心断开;0x0002:网络断开;0x0004:IP冲突
	long long     nStartTime;// 录像开始时间,从1970年1月1日开始的秒数
	long long     nStopTime;//录像结束时间
}TGetRecord;

typedef struct  ARNET_OPEN_INFO       // 用户登录参数
{
	char		szDeviceID[SDK_DEVICE_SERIAL_LEN+1];  //设备ID
	char       LoginName[SDK_USER_NAME_LEN+1];   // 登录用户名
	char       LoginPsw[SDK_USER_PSW_LEN+1];     // 登录密码
}ARNET_OPEN_INFO;
typedef ARNET_OPEN_INFO NET_OPEN_INFO;

#ifdef _WIN32
#pragma pack()
#endif

#endif