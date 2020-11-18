#if !defined(SDK_DATATYPE_H__INCLUDED_)
#define SDK_DATATYPE_H__INCLUDED_

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
#define SDK_PRE_POINT_NAME_LEN		   17/*Ԥ�õ����Ƴ���*/
#define SDK_PRE_POINT_MAX_NUM		   255/*Ԥ�õ�������*/
#define SDK_CRUISE_MAX_NUM			   12/*Ѳ��������*/
#define SDK_MAX_BALL_PARAM_BUF		   10000/*�������buf*/

#ifdef _WIN32
#pragma pack(1)
#endif
//SDKר�ô�����
enum	
{
	IPCRET_SDK_INIT_ERROR = -301,//SDK��ʼ������
	IPCRET_RESPONE_TIMEOUT = -302,//�豸�ظ���ʱ(����Ӧ)
	IPCRET_OPENFILEERROR = -303,//���ļ�����
	IPCRET_MGHANDLE_NOTEXIST = -304,//�豸���������
	IPCRET_WRONG_PARAMETER = -305,//��������
	IPCRET_DEALERROR = -306,//�ظ����ݵĳ��Ȳ���
	IPCRET_OUTBUF_NOT_ENOUGH = -307,//������治��
	IPCRET_CONNECT_BREAK	= -308,//���ӶϿ�
	IPCRET_SDK_UNINIT		= -309,//SDKδ��ʼ��
	IPCRET_RESPONE_ERR = -310,//�豸�ظ����ݴ���
	IPCRET_RECVBUF_TOO_SMALL = -311,//������̫С
	IPCRET_NOT_SUPPORT = -312,//�豸��֧�ִ�����
	IPCRET_MEDIACONNECT_TIMEOUT = -320,//ý�����ӳ�ʱ
	IPCRET_MEDIAASW_TIMEOUT = -321,//ý������Ӧ��ʱ
	IPCRET_GET_HANDLE_FAILED = -322,//�������ʧ��
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
	GS_AUDENC_G711A,        /* G.711 A��*/
	GS_AUDENC_G711Mu,       /* G.711 Mu��*/
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
	RTSP_UNVIEW,//����rtsp����
	RTSP_GSUNVIEW,//����������rtsp PS����
	RTSP_DVS,//DVS rtsp����
	RTSP_DALI,//���� rtsp����
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
}enVidFrmType;	//֡����

typedef struct  ARNET_LOGIN_INFO       // �û���¼����
{
	char             sDevIP[20];                      // �豸ip
	WORD             wDevPort;                     // �豸�˿�
	char             LoginName[SDK_USER_NAME_LEN+1];   // ��¼�û���
	char             LoginPsw[SDK_USER_PSW_LEN+1];     // ��¼����
	EnumMonTranMode  eMonTranMode;                 // Э��ģʽ
	WORD             wClientUdpPort;               // �ͻ���UDP�˿ںţ���MonTranMode == MTM_UDP��Ч
	BYTE             bUdpMakeHole;                 // ��UdpMakeHole == 1ʱ����������ClientUdpPort.
}ARNET_LOGIN_INFO;
typedef ARNET_LOGIN_INFO NET_LOGIN_INFO;

typedef struct ARNET_IMAGEFIXEDATTRT
{
	EnumVideoResolution       eVidRes;			            // ͼ��ֱ���
	EnumVideoResolutionName   eVidResName;	                // ͼ����Էֱ���
	WORD                      Width;						// ͼ����
	WORD                      Height;						// ͼ��߶�
	BYTE                      MaxFrmRate;					// ���֡��
	WORD                      DefaultBps;					// Ĭ������
	BYTE                      Reserved[5];
}ARNET_IMAGEFIXEDATTRT;
typedef ARNET_IMAGEFIXEDATTRT NET_IMAGEFIXEDATTRT;

typedef struct ARNET_DEVICE_INFO    // �豸��Ϣ
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
	BYTE byId;                   //Ԥ�õ�1~255
	char chName[SDK_PRE_POINT_NAME_LEN];//Ԥ�õ�����
}ARNET_PRE_POINT;
typedef ARNET_PRE_POINT NET_PRE_POINT;

typedef struct ARNET_PRE_POINT_LIST
{
	BYTE byNum;  // Ԥ�õ����
	ARNET_PRE_POINT stPrePoint[SDK_PRE_POINT_MAX_NUM]; // Ԥ�õ���Ϣ
}ARNET_PRE_POINT_LIST;
typedef ARNET_PRE_POINT_LIST NET_PRE_POINT_LIST;

typedef struct ARNET_CRUISE
{
	BYTE byId;                   //Ѳ��1-12
	char chName[SDK_PRE_POINT_NAME_LEN];//Ѳ������
}ARNET_CRUISE;
typedef ARNET_CRUISE  NET_CRUISE;

typedef struct ARNET_CRUISE_LIST
{
	BYTE byNum;  // Ѳ������
	ARNET_CRUISE stCruiseList[SDK_CRUISE_MAX_NUM]; // Ѳ����Ϣ
}ARNET_CRUISE_LIST;
typedef ARNET_CRUISE_LIST NET_CRUISE_LIST;

typedef struct ARNET_CRUISE_PREPOINT_INFO
{
	BYTE byPrePointId;	//Ѳ����Ԥ�õ�
	BYTE byWaitTime;	//ͣ��ʱ��
}ARNET_CRUISE_PREPOINT_INFO;//ÿ��Ѳ������Ϣ
typedef ARNET_CRUISE_PREPOINT_INFO  NET_CRUISE_PREPOINT_INFO;

typedef struct ARNET_CRUISE_INFO
{
	BYTE byPrePointNum;	//Ѳ�������õ�Ԥ�õ����
	ARNET_CRUISE_PREPOINT_INFO stInfo[32];//֧��32Ԥ�õ�
}ARNET_CRUISE_INFO;
typedef ARNET_CRUISE_INFO  NET_CRUISE_INFO;

typedef struct ARNET_TRAJECTORY//qxs 2013.7.31
{
	BYTE byId;                   //�켣ID 1~8
	char chName[SDK_PRE_POINT_NAME_LEN];//�켣����
}ARNET_TRAJECTORY;
typedef ARNET_TRAJECTORY  NET_TRAJECTORY;

typedef struct ARNET_TRAJECTORY_LIST
{
	BYTE byNum;  // �켣����
	ARNET_TRAJECTORY stTrajectory[8]; // �켣��Ϣ
}ARNET_TRAJECTORY_LIST;

// ��̨��ʱ���� �ؼ��ӿ����ݽṹ
struct _TPTZTimedTask
{
	BYTE bTaskEnable; // ����ʹ�� 1�� ����ʹ�� 2
	BYTE Week;        // 0 ����������Ч�� 1-7 ĳ�����ڼ���Ч
	BYTE StartHour;   // ����ʱ����
	BYTE StartMin;    // ����������
	BYTE EndHour;     // ֹͣʱ����
	BYTE EndMin;      // ֹͣ������
	BYTE ActType;     // �������ͣ�Ԥ��λ 1��ɨ�� 2, Ѳ�� 4���켣 5
	BYTE ActId;       // ���������е�id�� Ԥ��λ 1-255��ɨ�� 1-12, Ѳ�� 1-12���켣 1-8
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
	int nHeartBeatInterval;	//������� ������Ϊ0��ʾĬ��ֵ5000����
	int nDisconnectTime;    //���߳�ʱʱ�䣬����Ϊ0��ʾĬ��ֵ30000����
	int nAutoReConnectTime; //�Զ�����ʱ�䣬�ɵĲ�����ĿǰSDK�ڲ�������
	char m_szServerIP[20];		//�������ӷ���IP������ΪNULL��ʾĬ�ϱ���ip,Ŀǰ����NULL
	int m_nServePort;			//�������ӷ���˿ڣ�����Ϊ0��ʾ������4G����
}ARNET_INIT_PARAM;
typedef ARNET_INIT_PARAM NET_INIT_PARAM;

typedef struct TGetRecord
{
	int eMonBlockType;//¼���ļ���ʽ,��net_protocol.h�ļ���enMonBlockType�����У�����MBT_STORAGEH264��ѡ��
	unsigned short dwEventType; //0x0000:��ʾ��ѯȫ���¼�����;0x0001:���ĶϿ�;0x0002:����Ͽ�;0x0004:IP��ͻ
	long long     nStartTime;// ¼��ʼʱ��,��1970��1��1�տ�ʼ������
	long long     nStopTime;//¼�����ʱ��
}TGetRecord;

typedef struct  ARNET_OPEN_INFO       // �û���¼����
{
	char		szDeviceID[SDK_DEVICE_SERIAL_LEN+1];  //�豸ID
	char       LoginName[SDK_USER_NAME_LEN+1];   // ��¼�û���
	char       LoginPsw[SDK_USER_PSW_LEN+1];     // ��¼����
}ARNET_OPEN_INFO;
typedef ARNET_OPEN_INFO NET_OPEN_INFO;

#ifdef _WIN32
#pragma pack()
#endif

#endif