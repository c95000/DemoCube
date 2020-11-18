//////////////////////////////////////////////////////////////////////////////////////////
/*******************************   NETWORK PROTOCOL    **********************************/
//////////////////////////////////////////////////////////////////////////////////////////


/******************************* ˵�� **********************************************
  1)  �ͻ��˷�������˵�ÿһ�������������˶��᷵��һ��Ӧ����������ע���������⡣
  2)  û��������¼�������˷����������˲��᷵���κ�Ӧ�𣬳��������¼����ѯ�豸
      ��Ϣ�������⡣
  3)  ����˷��ص�Ӧ�����а����˿ͻ��˵�������������뼰��������
***********************************************************************************/

/******************************* ���Դ� ********************************************
  Chan  ->  Channel
  Col   ->  Column
  Cnt   ->  Count
  Pos   ->  Position
  Scr   ->  Screen
  Avg   ->  Average
  Prev  ->  Preview
  Rec   ->  Record
  Orig  ->  Original
  Cur   ->  Current
***********************************************************************************/


#ifndef __NET_PROTOCOL_H__
#define __NET_PROTOCOL_H__

#include "net_protocol_robot.h"

#if !defined(WIN32)
	#define __PACKED__        __attribute__ ((__packed__))
#else
	#define __PACKED__ 
#endif

#if !defined(WIN32)

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

#ifndef INVALID_SOCKET
	#define INVALID_SOCKET  (-1)
#endif

#ifndef NULL
	#define NULL ((void *)0)
#endif

#endif

#define NEW_TIME_CMD	//add lee

#define NETWORK_PROTOCOL_VERSION   0x0102
#define MAKE_MAGIC_CODE(a,b,c,d)   (a | (b<<8) | (c<<16) | (d<<24))
//#define SYSCFG_MAGIC_CODE          MAKE_MAGIC_CODE('A', 'E', 'B', 'C') // Config file magic code
#define NETWORK_MAGIC_CODE         MAKE_MAGIC_CODE('G', 'X', 'X', 'H') // Network command magic code
#define MAX_TRANSPACK_SIZE         	(8192*128) //�������󳤶� 8192*4
#define SERVER_TCP_PORT            	36666        //TCP���Ӷ˿�
#define SERVER_STREAM_TCP_PORT  36667        //����TCP���Ӷ˿�
#define CLIENT_UDP_PORT            	36668        //�ͻ���UDP�˿�
#define MULTICAST_PORT            		36888
#define SERVER_UDP_MAKE_HOLE_PORT  36681
#define HST_VID_P2P_PORT           36680
#define CHAN_NAME_LEN              32
#define SERVER_NAME_LEN            32
#define DEVICE_SERIAL_LEN          32
#define IPADDR_LEN                 15
#define USER_NAME_LEN              16
#define USER_PSW_LEN               16
#define MAX_USER_CNT               32
#define MAX_DETECT_AREA_CNT        2
#define MAX_ALARM_IN               8
#define MAX_ALARM_OUT              8
#define MAX_PLAN_PER_DAY           4
#define MAX_PROTOCOL_NAME_LEN      20
#define MAX_PRODUCT_MODEL_LEN      32
#define ALARM_OUT_PORT_NAME_LEN    32
#define IP_ADDR_LEN                15
#define DDNS_DOMAIN_NAME_LEN       63
#define DDNS_USER_NAME_LEN         19
#define DDNS_USER_PSWD_LEN         19
#define PPPOE_USER_NAME_LEN        31
#define PPPOE_USER_PSWD_LEN        31
#define MAX_REC_FILE_PATH          64
#define WIFI_NETWORK_NAME_LEN      32
#define MIN_WIFI_WEP_KEY_LEN       5
#define MAX_WIFI_WEP_KEY_LEN       13
#define MIN_WIFI_WPA_PSK_LEN       8
#define MAX_WIFI_WPA_PSK_LEN       64
#define HST_VID_SVR_USER_LEN       31
#define HST_VID_SVR_PSWD_LEN       15
#define FTP_USER_NAME_LEN          32			
#define FTP_USER_PSWD_LEN          32			
#define FTP_PATH_LEN			   64			
#define SMTP_SUBJECT_LEN		   64			
#define SMTP_EMAIL_ADDR_LEN		   64			
#define SMTP_USER_NAME_LEN         32			
#define SMTP_USER_PSWD_LEN         32			
#define MAX_AlARMTYPE_NUM			4//�������͵�����			

#define MAX_VIDEO_OVERLAY_REGION  8  /*������ƵOSD��������added by zengqingfeng 20120607*/
#define MAX_VIDEO_COVER_REGION  8	/*������Ƶ�ڵ�����added by zengqingfeng 20120607*/
#define MAX_MOTION_DETECT_REGION  8	/*�����ƶ��������added by zengqingfeng 20120612*/
#define MAX_IP_FILTER_LIST   20/*���ipʱ��added by zengqingfeng 20120704*/
#define ALLOW_ACCESS		1	/*����ǰip�����豸*/
#define NOT_ALLOW_ACCESS		0	/*������ǰip�����豸*/
#define MAX_SNAP_PLAN_PER_DAY	6	/*���ʱץ��ʱ��Ϊ6��added by zengqingfeng 2012706*/
#define MAX_RECORD_PLAN_PER_DAY	6	/*���ʱ¼��ʱ��Ϊ6��added by zengqingfeng 20120706*/
#define MAX_DIGITAL_WATERMASK_CONTENT_LEN		16/*����ˮӡ�ַ�����added by zengqingfeng 20120801*/
#define SYS_LOG_MSG_LEN_MAX		70 /*ϵͳ��־ ��Ϣ����add lee,syslog*/
#define MAX_COM_NUM				1/*��������*/
//#define CLIENT_CONNECT_NUM_MAX	10/*�ͻ������������*/
#define ALARM_REC_TIME_MIN		20/*�澯����¼����Сʱ��*/
#define ALARM_REC_TIME_MAX		300/*�澯����¼�����ʱ��*/
#define ALARM_OUTPUT_TIME_MIN		10/*�澯���������Сʱ��*/
#define ALARM_OUTPUT_TIME_MAX		300/*�澯����������ʱ��*/
#define ALARM_SNAP_INTERVAL_MIN		1/*�澯����ץ����С���*/
#define ALARM_SNAP_INTERVAL_MAX		5/*�澯����ץ�������*/
#define ALARM_SNAP_CNT_MIN		1/*�澯����ץ����С����*/
#define ALARM_SNAP_CNT_MAX		10/*�澯����ץ���������*/
#define ALARM_DEBOUNCE_TIME_MIN		1/*�澯ȥ������Сʱ��*/
#define ALARM_DEBOUNCE_TIME_MAX		100/*�澯ȥ�������ʱ��*/
#define PRE_POINT_NAME_LEN		32/*Ԥ�õ����Ƴ���*/
#define PRE_POINT_NUM_MAX		256/*Ԥ�õ���Ŀ*/
#define NET_MAC_LEN				17/*MAC 00:26:C5:01:02:03*/
#define NTP_SERVER_ADD_LEN		32/*NTP��������ַ����*/
#define NTP_SERVER_PORT_DEFAULT	123/*NTP������Ĭ�϶˿� 123*/
#define FTP_SERVER_PORT_DEFAULT	21/*FTP������Ĭ�϶˿� 21*/
#define SMTP_SERVER_PORT_DEFAULT	25/*SMTP������Ĭ�϶˿� 25*/
#define MVDDNS_DDNS_SERVER_PORT_DEFAULT		30000/*mvddns.net DDNS������Ĭ�϶˿� 30000*/
#define PUBYUN_DDNS_SERVER_PORT_DEFAULT		80/*pubyun.com DDNS������Ĭ�϶˿� 80*/
#define MAX_ONLINE_NUM	                     10 /*��������û�����*/
#define MAX_DOWNLOAD_FILE_PATH          64/*��������ļ���·������*/
#define MAX_ANALY_SYSINFO_LEN  128 //FIX ME zhangyt add 2012-12-19

#define MAX_OPERATION_NAME_LEN 16
#define MAX_TWO_SCAN	3
#define MAX_TRAJECTORY		4
#define MAX_CRUISE	4

//����������
typedef enum		
{
	STATUS_SUCCESS_WAIT_RESULT=  2,//����ɹ����ȴ��������
	STATUS_SUCCESS_REBOOT     =  1,//�����ɹ����豸��������
	ERR_SUCCESS               =  0,//�����ɹ���������Ч��
	ERR_UNKNOWN               = -1,//δ֪����
	ERR_REACH_MAX_CLIENT_CNN  = -2,//�ﵽ���ͻ���������
	ERR_INVALID_USER          = -3,//��Ч�û�
	ERR_INVALID_PSWD          = -4,//��Ч����
	ERR_NO_POWER              = -5,//û��Ȩ��
	ERR_INVALID_CHAN_NUM      = -6,//��Чͨ����
	ERR_USER_LIST_FULL        = -7,//�ﵽ����û���
	ERR_USER_IS_EXISTENT      = -8,//�û��Ѵ���
	ERR_USER_IS_NOT_EXISTENT  = -9,//�û�������
	ERR_INVALID_PARAMETER     = -10,//��Ч����
	ERR_REACH_MAX_DOWNLOAD    = -11,//�ﵽ���������
	ERR_OPEN_FILE_FAILED      = -12,//���ļ�����
	ERR_EXCLUSIVE_BY_USER     = -13,//�ѱ������û�ռ��
	ERR_CHAN_IS_NOT_OPEN      = -14,//ͨ��û�д�
	ERR_FILE_SIZE_OVERFLOW    = -15,//�ļ�����
	ERR_INVALID_FILE_TYPE     = -16,//�Ƿ��ļ�����
	ERR_NOT_SUPPORT_STORAGE   = -17,//��֧�ִ洢
	ERR_NOT_PLUG_STORAGE      = -18,//δ�ҵ��洢�豸
	ERR_RESOURCE_INSUFFICIENT = -19,//��Դ����
	ERR_INVALID_FILE_SIZE     = -20,//��Ч�ļ�����
	ERR_INVALID_FILE_HEAD     = -21,//��Ч�ļ�ͷ
	ERR_USER_ALREADY_LOGIN    = -22,//�û��ѵ�¼
	ERR_NOT_ENOUGH_MEMORY     = -23,//�洢�ռ䲻��
	ERR_INVALID_UPDATE_TYPE   = -24,//��Ч��������
	ERR_INVALID_PRODUCT_MODEL = -25,//��Ч��Ʒ�ͺ�
	ERR_INVALID_SW_VERSION    = -26,//��Ч����汾
	ERR_CONNECT_TIMEOUT       = -27,//���ӳ�ʱ
	ERR_INVALID_USER_OR_PSWD  = -28,//�û������������
	ERR_OPERATION_IS_BUSY     = -29,//����̫Ƶ��
	ERR_INVALID_FILE_PATH     = -30,//��Ч�ļ�·��
	ERR_OSD_CAN_NOT_OVERLAY   = -31,//OSD�޷�����
	ERR_NOT_ALLOW_ACCESS      = -32,//���������
	ERR_OSD_OVERLAY_FAILED    = -33,//OSD����ʧ��
	ERR_DELETE_USER_ONLINE    = -34,//�޷�ɾ�������û�
	ERR_COVER_REGION_FAILED   = -35,//�ڵ��������
	ERR_FORMAT_SD_FAILED	=-36,//��ʽ��SD��ʧ��
	ERR_CMD_OUT_TIME  =-37,//�������ʱ
	ERR_IN_UPDATE = -38 ,//��������
	ERR_UPDATE_FALSE = -39,//����ʧ��
	ERR_OPERATION_FALSE = -40,//����ʧ��
	ERR_INVALID_IP_ADDR = -41,//IP��ַ���Ϸ�
	ERR_INVALID_NET_MASK = -42,//�������벻�Ϸ�
	ERR_INVALID_GATEWAY = -43,//Ĭ�����ز��Ϸ�
	ERR_INVALID_DNS_FIRST = -44,//��ѡDNS���Ϸ�
	ERR_INVALID_DNS_SECOND = -45,//����DNS���Ϸ�
	ERR_NOT_IN_SAME_NET = -46,//IP��ַ��Ĭ�����ز���ͬһ����
	ERR_OPERATION_AFTER_REBOOT_DEV = -47,//�����豸���ٽ��в���
	ERR_OVER_MAX = -48,//����������ø���
	ERR_NOT_SUPPORT = -49,//����Ϸ�
	ERR_INVALID_LoginID = -50,//��Ч�ĵ�¼ID
	ERR_NO_ELECBOARD = -51,//���ذ�Ͽ�����
}enErrCode;

typedef enum
{
	DEV_IPC,  // IP Camera
	DEV_DVS,  // Video Server
	DEV_DVR,  // Video Recorder
	DEV_MAX
}enDeviceType;

typedef enum
{
	VIDENC_NONE,     // No video encode type
	VIDENC_HIS264,   // Hisilicon H264
	VIDENC_HIK264,   // Hikvision H264 (Seems 263+)
	VIDENC_DIVXMP4,  // DIVX MPEG4
	VIDENC_XVIDMP4,  // XVID MPEG4
	VIDENC_HIS265,   // Hisilicon H265
}enVidEncType;

typedef enum
{
	AUDENC_DEFAULT,      // Default : AUDENC_G726
	AUDENC_G711A,        /* G.711 A��*/
    AUDENC_G711Mu,       /* G.711 Mu��*/
	AUDENC_G723,         /* G.723 */
	AUDENC_G722,         /* G.722 */
	AUDENC_G726,         /* hisilicon define as G.726 */
	AUDENC_ADPCM,        /* hisilicon define as ADPCM */
	AUDENC_ULAW,         /* mu-law */
    AUDENC_ALAW,         /* a-law */
	AUDENC_GSM,          /* GSM */
    AUDENC_S16BE_STEREO, /* linear 16, 44.1khz, 2 channel */
    AUDENC_S16BE_MONO,   /* linear 16, 44.1khz, 1 channel */
    AUDENC_MPEGAUDIO,    /* mpeg audio */
    AUDENC_MAX			//add lee,20120726
}enAudEncType;

typedef enum
{
	AUDRATE_DEFAULT, // Default : AUDRATE_32KBPS
	AUDRATE_16KBPS,
	AUDRATE_24KBPS,
	AUDRATE_32KBPS,
	AUDRATE_64KBPS,
	AUDRATE_MAX,		//add lee,20120726
	AUDRATE_8KBPS
}enAudCodeRate;

typedef enum
{
	STD_PAL,
	STD_NTSC,
	STD_MAX
}enVidStd;

typedef enum
{
	USER_NOP,          // No operation, Reserved.
	USER_ADD,          // Add
	USER_DELETE,       // Delete
	USER_CHANGE_PSWD,  // Change password
	USER_CHANGE_POWER  // Change power
}enModifyUser;

typedef enum
{
	POWER_USER_MAN          = 0x80000000, // User Management
	POWER_UPDATE_FILE       = 0x40000000, // Update Software
	POWER_DEV_SYS_SET       = 0x20000000, // Front End System Settings
	POWER_PTZ_CONTROL       = 0x10000000, // PTZ Control
	POWER_WATCH_VIDEO       = 0x00000001, // Watch Real-time Monitor Video
	POWER_LOCAL_RECORD      = 0x00000002, // Local Record
	POWER_LOCAL_PLAYBACK    = 0x00000004, // Local Playback
	POWER_MANUAL_ALARM      = 0x00000008, // Manual Alarm
	POWER_LOCAL_ALARM_SET   = 0x00000010, // Local Alarm Settings
	POWER_LOCAL_RECORD_SET  = 0x00000020, // Local Record Settings
}enUserPower;

typedef enum
{
	POWER_MULTI_LOG_IN      = 0x80000000, // Enable user multiple logging in
}enUserPowerExt;

typedef enum
{
	ALMTYPE_LOST          = 0x01,/*��Ƶ��ʧ*/
	ALMTYPE_MOTION        = 0x02,/*�ƶ����澯*/
	ALMTYPE_PROBE         = 0x04, /*IO�澯*/
	ALMTYPE_MANUAL        = 0x08, /*�ֶ�����*/

	//add lee,alarminfo 
	ALMTYPE_NET_DOWN	  = 0X0010,//����Ͽ�
	ALMTYPE_IP_CLASH	  = 0X0020,//IP��ַ��ͻ
	ALMTYPE_SD_NON		  = 0X0040,//��SD��
	ALMTYPE_SD_LACK_SPACE = 0X0080,//SD���ռ䲻��
	ALMTYPE_SD_ERR		  = 0X0100,//SD������

	ALMTYPE_HIDEALARM	  = 0X0200,//�ڵ��澯

	ALMTYPE_PANCHK_FAIL	  = 0X0400,//���ˮƽ�Լ�澯
	ALMTYPE_TILTCHK_FAIL  = 0X0800,//�����ֱ�Լ�澯

	ALMTYPE_RECONN_SUCC     = 0X1000,//�����ɹ�
	ALMTYPE_RECONN_FAIL     = 0X2000,//����ʧ��

	ALMTYPE_MODCOMM_ERR	  = 0X4000,//��оͨ��ʧ��
	ALMTYPE_TRAFFIC       = 0x8000,//���ܽ�ͨ
	ALMTYPE_PLATE         = 0x10000,//����ʶ��
}enAlarmType;

typedef enum
{
	FILE_TYPE_PICTURE          = 0x01,/*ץ��ͼƬ�ļ�*/
	FILE_TYPE_RECORD        = 0x02,/*¼���ļ�*/
	
}enFileType;

typedef enum
{
	FILE_SUBTYPE_ALARM        = 0x01,/*�澯����ץ�Ļ���¼���ļ�*/
	FILE_SUBTYPE_TIMING	=0X02,/*��ʱ¼����߶�ʱץ���ļ�*/	
	FILE_SUBTYPE_MANUAL          = 0x04,/*�ֶ�ץ�Ļ���¼���ļ�*/
	
}enFileSubType;

typedef enum
{
	BITRATE_CONSTANT,
	BITRATE_VARIABLE
}enBitRateMode;

typedef enum
{
	VR_1   = 0x01,	//��һ�ֱַ���
	VR_2   = 0x02,	//�ڶ��ֱַ���
	VR_3   = 0x04,	//�����ֱַ���
	VR_4   = 0x08,	//�����ֱַ���
}enVideoResolution;

typedef enum
{                     //   [PAL]       [NTSC]
	VRN_D1    = 0x01, // 704 x 576 , 704 x 480
	VRN_HD1   = 0x02, // 704 x 288 , 704 x 240
	VRN_CIF   = 0x03, // 352 x 288 , 352 x 240
	VRN_QCIF  = 0x04, // 176 x 144
	VRN_VGA   = 0x05, // 640 x 480
	VRN_HVGA  = 0x06, // 640 x 240
	VRN_QVGA  = 0x07, // 320 x 240
	VRN_720P  = 0x08, // 1280 x 720
	VRN_SXGA  = 0x09, // 1280 x 1024
	VRN_UXGA  = 0x0A, // 1600 x 1200
	VRN_1080P = 0x0B, // 1920 x 1080
	VRN_XGA   = 0x0C, // 1024 x 768
	VRN_HDVGA  = 0x0D, // 1280 x 960
}enVideoResolutionName;

typedef enum
{
	USER_ADMIN    = -1,
	USER_OPERATOR = 0
}enUserLevel;

typedef enum
{
	MBT_VIDEO=0,
	MBT_VIDEOSUB=1,
	MBT_AUDIO=2,
	MBT_VIDEOTHRD=3,
	MBT_VIDEOTHRDPS=4,
	MBT_VIDEOPS=5,
	MBT_VIDEOSUBPS=6,


	MBT_STORAGEH264=51,
	MBT_STORAGESUBH264=52,
	MBT_STORAGEPS=53,
	MBT_STORAGESUBPS=54,
	MBT_STORAGEJPEG=55,
	MBT_STORAGESUBJPEG=56,
	MBT_SEISTREAM=100
}enMonBlockType;

typedef enum
{
	MTM_TCP,
	MTM_UDP,
	MTM_MULTICAST
}enMonTranMode;

typedef enum
{
	WPT_RECORD        = 0x01, // Record
	WPT_LOST_DETECT   = 0x02, // Video Lost Detection
	WPT_MOTION_DETECT = 0x04, // Motion Detection
	WPT_PROBE_DETECT  = 0x08, // Probe Detection
	WPT_FTP_UPLOAD    = 0x10, // Upload AV data to FTP server
	WPT_ALARM_SNAP      = 0x20, // Snap when alarm
	WPT_FTP_UPLOAD_SNAP = 0x40,// Upload snap picture to FTP server
	WPT_TIMING_SNAP 	= 0X80,/*���Ӷ�ʱץ��added by zengqingfeng 20120629*/
}enWorkPlanType;

typedef enum
{
	WEEK_MON,
	WEEK_TUE,
	WEEK_WED,
	WEEK_THU,
	WEEK_FRI,
	WEEK_SAT,
	WEEK_SUN,
	WEEK_MAX_DAY,
}enWeekDay;

typedef enum
{
	COM_RS485,
	COM_RS232
}enComPort;

typedef enum
{
	BR_300,
	BR_600,
	BR_1200,
	BR_1800,
	BR_2400,
	BR_4800,
	BR_9600,
	BR_19200,
	BR_38400,
	BR_57600,
	BR_115200,
	BR_MAX
}enBaudRate;

typedef enum
{
	DBIT_5,
	DBIT_6,
	DBIT_7,
	DBIT_8,
	DBIT_MAX
}enDataBits;

typedef enum
{
	SBIT_1,
	SBIT_1P5,
	SBIT_2,
	SBIT_MAX
}enStopBits;

typedef enum
{
	PCHK_NONE,
	PCHK_ODD,
	PCHK_EVEN,
	PCHK_MARK,
	PCHK_SPACE,
	PCHK_MAX
}enParityCheck;

typedef enum
{
	FLOW_NONE,
	FLOW_HARDWARE,
	FLOW_SOFTWARE,
	FLOW_MAX
}enFlowCtrl;

typedef enum
{
	// Up, Down, Left, Right
	PTZ_UP_START = 0,
	PTZ_UP_STOP,
	PTZ_DOWN_START,
	PTZ_DOWN_STOP,
	PTZ_LEFT_START,
	PTZ_LEFT_STOP,
	PTZ_RIGHT_START,
	PTZ_RIGHT_STOP,
	// (Optional) : LeftUp, LeftDown, RightUp, RightDown
	PTZ_LEFT_UP_START,
	PTZ_LEFT_UP_STOP,
	PTZ_LEFT_DOWN_START,
	PTZ_LEFT_DOWN_STOP,
	PTZ_RIGHT_UP_START,
	PTZ_RIGHT_UP_STOP,
	PTZ_RIGHT_DOWN_START,
	PTZ_RIGHT_DOWN_STOP,

	// Focus, Zoom, Iris
	PTZ_FOCUS_FAR_START = 20,
	PTZ_FOCUS_FAR_STOP,
	PTZ_FOCUS_NEAR_START,
	PTZ_FOCUS_NEAR_STOP,
	PTZ_ZOOM_TELE_START,
	PTZ_ZOOM_TELE_STOP,
	PTZ_ZOOM_WIDE_START,//�ӽǱ��Ҳ���Ǳ䱶С
	PTZ_ZOOM_WIDE_STOP,
	PTZ_IRIS_CLOSE_START,
	PTZ_IRIS_CLOSE_STOP,
	PTZ_IRIS_OPEN_START,
	PTZ_IRIS_OPEN_STOP,

	// Rotation, Light, Rain, Track, IO
	PTZ_ROTATION_START = 40,
	PTZ_ROTATION_STOP,
	PTZ_LIGHT_START,
	PTZ_LIGHT_STOP,
	PTZ_RAIN_START,
	PTZ_RAIN_STOP,
	PTZ_TRACK_START,
	PTZ_TRACK_STOP,
	PTZ_IO_START,
	PTZ_IO_STOP,

	// PTZ Point
	PTZ_SET_POINT = 60,
	PTZ_SET_POINT_ROTATION,
	PTZ_GOTO_POINT,
	PTZ_CLEAR_POINT,
	PTZ_SET_POINT_LEFT,
	PTZ_GOTO_POINT_LEFT,
	PTZ_SET_POINT_RIGHT,
	PTZ_GOTO_POINT_RIGHT,

	// Mouse click of PTZ moving & zooming
	PTZ_MOUSE_CLICK_MOVE_ZOOM = 80,

	//PTZ Auto Scan
	PTZ_AUTO_SCAN = 100,
	PTZ_AUTO_SCAN_PRESET,   //Ԥ��λ�Զ�Ѳ��

	//Zoom Camera Action
	ZC_ALL_DEFAULT = 120,
	ZC_WIDEDYNAMIC_OPEN, //wide Dynamic open
	ZC_WIDEDYNAMIC_CLOSE,
	ZC_BACKLIGHT_OPEN,
	ZC_BACKLIGHT_CLOSE,
	ZC_WHITEBALANCE_AUTO,
	ZC_WHITEBALANCE_MANUAL,
	ZC_RGAIN_UP,
	ZC_RGAIN_DOWN,
	ZC_BGAIN_UP,
	ZC_BGAIN_DOWN,
	ZC_AEMODE_AUTO,
	ZC_AEMODE_MANUAL,
	ZC_IRIS_UP,
	ZC_IRIS_DOWN,
	ZC_GAIN_UP,
	ZC_GAIN_DOWN,
	ZC_BRIGHT_UP,
	ZC_BRIGHT_DOWN,
	ZC_SHUTTER_AUTO,
	ZC_SHUTTER_MANUAL,
	ZC_SHUTTER_UP,
	ZC_SHUTTER_DOWN,
	ZC_APERTURE_UP,
	ZC_APERTURE_DOWN,
	
	ZC_HR_ON,
	ZC_HR_OFF,
	ZC_LRREVERSE_ON,
	ZC_LRREVERSE_OFF,
	ZC_FREEZE_ON,
	ZC_FREEZE_OFF,
	ZC_PFLIP_ON,
	ZC_PFLIP_OFF,
	ZC_ICR_ON,
	ZC_ICR_OFF,
	ZC_AUTOICR_ON,
	ZC_AUTOICR_OFF,
	ZC_COLOR_UP,
	ZC_COLOR_DOWN,

}enPtzAction;

typedef enum
{
	SP_FOCUS = 1,/*�۽�*/
	SP_HR = 2,/*ˮƽ����*/
	SP_BRIGHT = 3,/*����*/
	SP_SATUATION = 4,/*���Ͷ�*/
	SP_SHARPNESS = 5,/*���*/
	SP_BACKLIGHT_COMPENRATION_VALUE = 6,/*���ⲹ��ֵ*/
	SP_WHITEBALANCE_AEMODE = 7,/*��ƽ��ģʽ*/
	SP_WHITEBALANCE_RGAIN = 8,/*R����*/
	SP_WHITEBALANCE_BGAIN = 9 , /*B����*/
	SP_ZOOM = 10,/*�䱶*/
	SP_ZOOM_SPEED = 11,/*�䱶�ٶ�*/
	SP_BACKLIGHT_COMPENRATION = 12,/*���ⲹ��*/
	SP_DAY_NIGHT_CHANGE = 13,/*��ҹ�л�ģʽ*/
	SP_WIDEDYNAMIC = 14, /*��̬*/

	SP_SHUTTER_MODEL= 15,/*�ع�ģʽ*/
	SP_ELECTRONIC_SHUTTER = 16,/*���ӿ�����*/
	SP_IRIS_VALUE = 17,/*��Ȧֵ*/

	SP_AUTO_GAIN = 20,/*�Զ�����*/
	SP_FREEZE_FRAME = 21,/*ͼ�񶳽�*/
	SP_HORIZONTAL_SCAN = 22,/*ˮƽɨ��*/
	SP_HORIZONTAL_SCAN_SPEED = 23,/*ˮƽɨ���ٶ�*/
	SP_RESET = 24,/*�������*/
	SP_INFRARED_CTL = 25,/*����ƿ���*/
	SP_5DEGREE_VERTICAL_NEGATIVE = 26,/*��ֱ��5��*/
	SP_DAY_NIGHT_CHANGE_SENSITIVITY = 27,/*��ҹ�л�������*/
	SP_ZC_RESET = 28,/*��о��λ*/
	SP_KEEP_WATCH_WAITTIME = 29,/*����*/
	SP_KEEP_WATCH_TYPE = 30,/*������������*/
	SP_KEEP_WATCH_START = 31,/*������ʼ ֹͣ*/

	SP_TWO_SCANING_START = 32,/*������ɨ-����*/
	SP_TWO_SCANING_ORIGIN= 33,/*������ɨ-���*/
	SP_TWO_SCANING_TERMINAL = 34,/*������ɨ-�յ�*/
	SP_TWO_SCANING_SPEED = 35,/*������ɨ-�ٶȱ���*/
	SP_TWO_SCANING_READ = 36,/*������ɨ-��ȡ*/
	SP_TWO_SCANING_DEL = 37,/*������ɨ-ɾ��*/
	SP_ALL_DEFAULT = 38,/*�ָ�����Ĭ�ϲ���*/
	SP_AUTO_SCAN_PRESET = 39,   /*ɨ��16��Ԥ�õ�*/
	SP_TRAJECTORY_START_TRANSCRIBE = 40,/*�켣-��ʼ¼��*/
	SP_TRAJECTORY_STOP_TRANSCRIBE = 41,/*�켣-ֹͣ¼��*/
	SP_TRAJECTORY_START = 42,/*�켣-��ʼ����*/
	SP_TRAJECTORY_STOP = 43,/*�켣-ֹͣ����*/
	SP_TRAJECTORY_DELETE = 44,/*�켣-ɾ��*/
	SP_TRAJECTORY_READ= 45,/*�켣-��ȡ*/
	SP_CRUISE_READ_NUM = 46,/*Ѳ��ɨ��-��ȡ����*/
	SP_CRUISE_READ_CONTENT = 47,/*Ѳ��ɨ��-��ȡĳ��������*/
	SP_POWER_OFF_MEMORY_ONOFF = 48,/*�ϵ����-��/�ر�*/
	SP_READ_POINT_PARAM = 49,/*��ȡԤ�õ�������Ϣ*/

	SP_SHUTTER_TYPE = 50,/*������*/
	SP_SHUTTER_SPEED = 51,/*�����ٶ�*/
	SP_APERTURE_VALUE = 52,/*��Ȧֵ*/
	SP_MANUAL_CRLSPEED = 53,/*�ֶ���������ٶ�*/
	SP_POWERON_ACTION = 54,/*�ϵ綯��*/
	SP_AUTOFLIP = 55,/*�Զ���ת*/
	SP_FOCUS_NEARLIMIT = 56,/*�۽�����*/
	SP_UPDATEPACK_INFO = 57,/*��ư���Ϣ*/
	SP_UPDATEPACK_DATA = 58,/*��ư�����*/
	SP_VERTICAL_FLIP = 59,/*��ֱ����*/
	SP_3DPTZ = 60,// 3D��λ
	SP_FOCUS_POSITON = 61,/*�۽�λ��*/

	SP_VIDEO_FORMAT = 62,/*��Ƶ��ʽ*/
	SP_OSD_OPERATION = 63,/*OSD����*/
	SP_SWITCH_HIDE = 64,/*��˽�ڵ�����*/
	SP_EDIT_HIDE = 65,/*��˽�ڵ��༭*/
	SP_CHANGE_HIDE = 66,/*��˽�ڵ���С�ı�*/
	SP_RECSTATUS_TRAJECTORY = 67,/*�켣��¼״̬*/
	SP_TITLE_DISPLAY = 68,/*������ʾ��Ϣ*/
	SP_EXTERNAL_485_ADDRESS = 69,/*�ⲿ485������ַ*/
	SP_EXTERNAL_485_BAUDRATE = 70,/*�ⲿ485����������*/
	SP_EXTERNAL_485_PROTOCOL = 72,/*�ⲿ485����Э��*/

	SP_CRUISE_READ_SEND_DATA = 71,/*Ѳ��ɨ��-׼����������*/
	SP_CRUISE_SEND_DATA = 73,/*Ѳ��ɨ��-��������*/
	SP_CRUISE_STOP_SEND_DATA = 75,/*Ѳ��ɨ��-������������*/
	SP_CRUISE_DELETE = 77,/*Ѳ��ɨ��-ɾ��*/
	SP_CRUISE_START = 79,/*Ѳ��ɨ��-��ʼ*/
	SP_CRUISE_STOP = 81,/*Ѳ��ɨ��-ֹͣ*/

	SP_CHROMA = 80,/*ɫ��*/
	SP_DELFOG = 86,/*͸��*/
	SP_DELFOGCLASS = 87,/*͸��ȼ�*/
	SP_FLICKER = 88,/*����˸*/
	SP_NIGHTVIEWING = 89,/*ҹ��*/
	SP_DNR = 90,/*����*/
	SP_DEBUG = 91,/*����*/
	SP_AD_VALUE = 92,/*����AD��ȡ*/	
	SP_CONTRAST = 93,/*�Աȶ�*/
	SP_EXP_COMP = 94,/*�عⲹ������*/ 
	SP_EXP_COMP_VALUE = 95,/*�عⲹ��ֵ*/ 
	SP_GAMMA = 96,/*gammaֵ*/ 
	SP_NORTH_ADJUST = 97,/*����У׼*/	
	SP_XY_ZOOM_STATUS = 98,/*����䱶����״̬*/
	SP_TIME_TASK = 99,/*��ʱ����*/ 
	SP_UP = 110,
	SP_DOWN = 111,
	SP_LEFT = 112,
	SP_RIGHT = 113,
	SP_LEFT_UP = 114,
	SP_RIGHT_UP = 115,
	SP_LEFT_DOWN = 116,
	SP_RIGHT_DOWN = 117,
	SP_ZOOM_TELE = 118,/*�䱶��*/
	SP_ZOOM_WIDE = 119,/*�䱶��*/

	SP_FOCUS_NEAR = 120,/*�۽���*/
	SP_FOCUS_FAR = 121,/*�۽�Զ*/
	SP_IRIS_OPEN = 122,/*��ȦС*/
	SP_IRIS_CLOSE = 123,/*��Ȧ��*/

	SP_LIGHT_STOP = 124,/*�ƹ��*/
	SP_LIGHT_START = 125,/*�ƹ⿪*/
	SP_GOTO_POINT = 126,/*ת��Ԥ�õ�*/
	SP_SET_POINT = 127,	/*����Ԥ�õ�*/
	SP_CLEAR_POINT = 128,/*ɾ��Ԥ�õ�*/
	SP_PTZ_STOP = 129,/*ֹͣ*/
	PTZ_SP_PRESET_MANUL_FOCUS = 141, //Ԥ�õ�ǿ���ֶ��۽�
	PTZ_SP_CRUISE_SET_GB28181 = 142,//28181����Ѳ������Э��
	PTZ_SP_Get_Roll_Azimuth = 143,
	PTZ_IO_TEST 			= 144,//IO��������
	PTZ_SP_3DNR = 145,/*3D����*/
	PTZ_SIX_AXIS = 146,
	PTZ_TRACE_POS = 147,
	PTZ_SP_3D_STOP = 148,//������
	PTZ_SP_WIPER = 149,/*��ˢ   Parma1ȡֵ�� 1:�� 2: ��*/
	PTZ_SP_RAIN_LEAVEL = 150,/*��������ȼ���*/
	PTZ_SP_DEBUG_INFO = 152,/*��ذ������Ϣ*/
	PTZ_SP_MAN_HEAT = 153,/*�ֶ����ȿ���*/
	PTZ_SP_LIFE_TIME = 154,/*�������*/
	PTZ_SP_STATE = 155, /*���״̬*/
	PTZ_MOVE_ANGLE = 156,	/*������нǶ�*/	
		
}enSPAction;/*������ƶ���*/


typedef enum
{
	ZCT_NONE           = 0,
	ZCT_HITACHI_SC110  = 1,   //������о
	ZCT_SCM2231P       = 2,   //���ǻ�о
	ZCT_FCBCX490DP     = 3,   //�����о
	
}enZcType; // Zoom Camera Type

typedef enum
{
	UPD_RESERVED, // Reserved.
	UPD_PTZ,      // PTZ Protocol, <** Reserved **>.
	UPD_BIOS      // BIOS Program
}enUpdateFileType;

typedef enum
{
	LOG_UpdateFileResult,
	LOG_PPPoEDialResult,
	LOG_PPPoEDisconnected,
	LOG_CmmStrInfo,
	LOG_EndPostSrchRec,
	LOG_EndPostDiskDirInfo,
}enCmmLogType;

typedef enum
{
	PBS_PAUSE,         // Pause, no transmission
	PBS_PLAY,          // Normal speed, frame rate as real-time record
	PBS_HALF,          // 1/2 normal
	PBS_QUARTER,       // 1/4 normal
	PBS_DOUBLE,        // 2x normal
	PBS_FOURFOLD,      // 4x normal
	PBS_DOWNLOAD_FILE, // Max Speed to download record file
}enPbSpeed;

typedef enum
{
	DDNSP_dyndns_org,
	DDNSP_dyndns_com,
	DDNSP_gnway_com,

	DDNSP_oray_cn,
	DDNSP_mvddns_net,
	DDNSP_pubyun_com,

}enDdnsProvider;

typedef enum
{
	DT_SDCard,
	DT_HardDisk,
}enDiskType;

typedef enum
{
	WET_NONE,
	WET_WEP,
	WET_TKIP, // WPA-PSK
	WET_AES,  // WPA2-PSK
}enWifiEncryType;

typedef enum
{
	ST_CCD,
	ST_CMOS,
}enSensorType;

typedef enum
{
	HDT_NONE,
	HDT_720P,
	HDT_SXGA,
	HDT_UXGA,
	HDT_1080P,
}enHighDefType; // High Definition Type

typedef enum
{
	HVP_Stream,
	HVP_P2P,
}enHstVidProtocol;


typedef enum
{
	OSD_TYPE_TIME,	/*ʱ��*/
	OSD_TYPE_CHANNAME,	/*ͨ����������*/
	OSD_TYPE_FRAMERATE,		/*֡��*/
	OSD_TYPE_BITRATE,	/*����*/
	OSD_TYPE_IFRAME,	/*I֡*/
	OSD_TYPE_TITLE,		/*��̨����*/
	OSD_TYPE_COORDINATE,	/*����*/
	//OSD_TYPE_ZOOM,		/*�䱶*/
	OSD_TYPE_TEXT1,		/*�ı�����*/
	OSD_TYPE_TEXT2,		/*�ı�����*/
	OSD_TYPE_TEXT3,		/*�ı�����*/
	OSD_TYPE_TEXT4,		/*�ı�����*/
	OSD_TYPE_TEXT5,		/*�ı�����*/
	OSD_TYPE_LINKAGE1,
	OSD_TYPE_LINKAGE2,
	OSD_TYPE_LINKAGE3,
	OSD_TYPE_LINKAGE4,
	MASK_TYPE_1,
	MASK_TYPE_2,
	MASK_TYPE_3,
	MASK_TYPE_4,
	MASK_TYPE_5,
	MASK_TYPE_6,
	MASK_TYPE_7,
	MASK_TYPE_8,
	OSD_TYPE_TRIFFIC1,
	OSD_TYPE_TRIFFIC2,

}enOverlayType;/*added by zengqingfeng 20120607*/

typedef enum
{
	IP_LIST_TYPE_BLACK,	/*������*/
	IP_LIST_TYPE_WHITE,	/*������*/
	IP_LIST_TYPE_BLACK_AND_WHITE,	/*��+������*/
	NOT_USE_IP_LIST,

}enIpListTpye;/*added by zengqingfeng 20120704*/

typedef enum
{
	REC_CONTROL_AUTO,/*����¼��ʱ�����Զ��л�����һ��¼���ļ�*/
	REC_CONTROL_CLOSE,/*����¼��ʱ����ر�¼���ļ�*/

}enRecControlType;/*added by zengqingfeng 20120704*/

typedef enum
{
	NEVER,/*���Զ�����*/
	REBOOT_EVERY_DAY,/*ÿ���Զ�����*/
	REBOOT_EVERY_WEEK,/*ÿ���Զ�����*/
	REBOOT_EVERY_MONTH,/*ÿ���Զ�����*/
}enAutoReboot;/*added by zengqingfeng 20120725*/

/*added by zengqingfeng start 20120801*/
typedef enum
{
	GAIN_MODE_AUTO,/*�Զ�����*/
	GAIN_MODE_MANUAL,/*�ֶ�����*/
	
}enGainMode;/*����ģʽ*/

typedef enum
{
	EXPOSURE_MODE_AUTO,/*�Զ��ع�*/
	EXPOSURE_MODE_MANUAL,/*�ֶ��ع�*/
	
}enExposureMode;/*�ع�ģʽ*/

typedef enum
{
	SCENARIO_MODE_AUTO,/*�Զ�*/
	SCENARIO_MODE_SUNNY_DAY,/*����*/
	SCENARIO_MODE_CLOUDY_DAY,/*����*/
	SCENARIO_MODE_NIGHT_DAY,/*ҹ��*/
	SCENARIO_MODE_INDOOR_DAY,/*����*/
	SCENARIO_MODE_OUTDOOR_DAY,/*���⣬add test*/
	
}enScenarioMode;/*�龰ģʽ*/

typedef enum
{
	NIGHT_MODE_DAY,/*����*/
	NIGHT_MODE_NIGHT,/*ҹ��*/	
	NIGHT_MODE_AUTO,/*�Զ�*/	
	
}enNightMode;/*��ҹģʽ*/

typedef enum
{
	CODE_FORMAT_H264,/*h.264*/
	CODE_FORMAT_MJPEG,/*m-jpge*/	
	CODE_FORMAT_MPEG4,//FIX ME zhangyt add 2012-12-19
	CODE_FORMAT_RAW,//FIX ME zhangyt add 2012-12-19
	CODE_FORMAT_H265,/*h.265*/
}enCodeFormat;/*�����ʽ*/

typedef enum
{
	STREAM_TYPE_MANUAL,/*��ͨ*/
	STREAM_TYPE_MOTION_ALARM,/*�ƶ����*/	
	STREAM_TYPE_PROBE_ALARM,/*����*/
	
}enStreamType;/*��������*/

/*added by zengqingfeng end 20120801*/

//�������Ͷ���:����ͼƬ������Ƶ���طš��ƶ����ʵʱ��Դ���ݵ�����
typedef enum gsVIDEO_STREAM_TYPE_E
{	    
    //û��
    VIDEO_STREAM_NONE = 0x000,
    VIDEO_STREAM_MAIN = 0x0001,
    VIDEO_STREAM_MINOR = 0x0002,
    VIDEO_STREAM_JPEG = 0x0004,
    VIDEO_STREAM_AUDIO = 0x0008,
    VIDEO_STREAM_PALY_BACK = 0x0010,
    VIDEO_STREAM_MD = 0x0020,
 } VIDEO_STREAM_TYPE_E;

typedef enum
{
	ALL_OPEN,/*����*/
	ALL_CLOSE,/*����*/
}enTransducerType;/*����������*/

typedef enum
{
	DEFAULT_VIDEO_PARAM	=1,
	DEFAULT_CODE_PARAM	=2,
	DEFAULT_OVERLAY_REGION_PARAM =3,
	DEFAULT_COVER_REGION_PARAM	=4,
	DEFAULT_PICTURE_PARAM	=5,
	DEFAULT_AUDIO_PARAM	=6,
	DEFAULT_COMM_PARAM	=7,
	DEFAULT_WIRED_NET_PARAM	=8,
	DEFAULT_NET_BASE_PARAM	=9,
	DEFAULT_IP_FILTER_PARAM	=10,
	DEFAULT_NET_SMTP_PARAM	=11,
	DEFAULT_NET_FTP_PARAM		=12,
	DEFAULT_MOTION_DETECT_PARAM	=13,
	DEFAULT_BLOCK_ALARM_PARAM	=14,
	DEFAULT_PROBE_ALARM_PARAM	=15,
	DEFAULT_MIS_ALARM		=16,
	DEFAULT_NORMAL_REC_PARAM	=17,
	DEFAULT_TIMING_SNAP_PARAM	=18,
	DEFAULT_SD_PARAM		=19,
	DEFAULT_REC_PARAM		=20,
	DEFAULT_SYS_BASE_PARAM	=21,
	DEFAULT_SYS_TIME_PARAM	=22,
	DEFAULT_AUTO_REBOOT_PARAM	=23,
	DEFAULT_NET_DDNS_PARAM	=24,//add lee,20121022
	DEFAULT_NET_PPPOE_PARAM	=25,
	DEFAULT_GB28181_PARAM	=26,	
	DEFAULT_WIRELESS_PARAM	=27,
	DEFAULT_PLATE_DETECTION_PARAM	=28,
}enDefaultParamType;/*Ĭ�ϲ���*/


/***************************************/ //begin lee
typedef enum
{
	DATE_MODE_CROSSBAND,	//��-��-��
	DATE_MODE_SLASH,		//��/��/��
	DATE_MODE_MAX
}enDateMode;//���ڸ�ʽ

typedef enum
{
	TIME_MODE_24,		//24Сʱ��
	TIME_MODE_12,		//12Сʱ��
	TIME_MODE_MAX
}enTimeMode;//ʱ���ʽ

typedef enum
{
	GMT_W1200,//��12��
	GMT_W1100,
	GMT_W1000,
	GMT_W0900,
	GMT_W0800,
	GMT_W0700,
	GMT_W0600,
	GMT_W0500,
	GMT_W0400,
	GMT_W0300,
	GMT_W0200,
	GMT_W0100,
	GMT_0000,
	GMT_E0100,//��1��
	GMT_E0200,
	GMT_E0300,
	GMT_E0400,
	GMT_E0500,
	GMT_E0600,
	GMT_E0700,
	GMT_E0800,
	GMT_E0900,
	GMT_E1000,
	GMT_E1100,
	GMT_E1200,
	TIME_ZONE_MAX
}enTimeZone;//ʱ��

typedef enum
{
	DST_TYPE_DATE,//���ڸ�ʽ:�£��գ�ʱ����
	DST_TYPE_WEEK,//�ܸ�ʽ:��,�µĵڼ��ܣ����ڼ���ʱ����
	DST_TYPE_MAX
}enDSTType;//����ʱʱ���ʽ


typedef enum
{
	MESSAGE_TYPE_ALL 			= 0xff,			//ȫ������
	MESSAGE_TYPE_SYS 			= (1<<0),		//ϵͳ����
	MESSAGE_TYPE_USER			= (1<<1),		//�û�����
	MESSAGE_TYPE_ALARM			= (1<<2),		//�����¼�
}enMessageType;//��־�¼����Ͷ���

typedef enum
{
	AUDIO_IN_TYPE_MIC,
	AUDIO_IN_TYPE_MAX	
}enAudInType;//��Ƶ��������

typedef enum
{
	AUD_SAMPLE_RATE_DEFAULT, // Default : RATE_8KBPS
	AUD_SAMPLE_RATE_8KBPS,
	AUD_SAMPLE_RATE_16KBPS,
	AUD_SAMPLE_RATE_32KBPS,
	AUD_SAMPLE_RATE_44KBPS,//44.1
	AUD_SAMPLE_RATE_48KBPS,
	AUD_SAMPLE_RATE_MAX,
}enAudSampleRate;//��Ƶ������

typedef enum
{
	COM_USE_TYPE_PTZ, // ��̨
	COM_USE_TYPE_TRANS,//͸��
	COM_USE_TYPE_MAX
}enComUseType;//������;

typedef enum
{
	PTZ_PROTOCOL_PELCO_D,
	PTZ_PROTOCOL_PELCO_P,
	LDS_VEHICLE_DETECTION_SENSORS,		//LDS������		qxs 2013.3.7
	VOCATION_SPEED_MEASURING_RADAR,		//�Ŀ������״�	qxs 2013.3.7
	DOME_PROTOCOL_GXX,
	PTZ_PROTOCOL_MAX
}enPTZProtocol;//��̨Э��

typedef enum
{
	IP_MODE_STATIC,//��̬
	IP_MODE_DYNAMIC,//��̬
	IP_MODE_MAX
}enIPMode;//IPģʽ

typedef enum
{
	IP_VER_4,
	IP_VER_6,
	IP_VER_MAX
}enIPVer;//IP�汾

typedef enum
{
	TRANS_QOS_QUALLITY_FST,//��������
	TRANS_QOS_TRANS_FST,//������������
	TRANS_QOS_MAX
}enTransQoS;//�����������

typedef enum
{
	LANGUAGE_CHINESE,//����
	LANGUAGE_ENGLISH,//Ӣ��
	LANGUAGE_MAX
}enLanguage;//����

typedef enum
{
	DDNS_SERVER_TYPE_MVDDNS_NET,//mvddns.net,default port=30000.
	DDNS_SERVER_TYPE_PUBYUN_COM,//pubyun.com(3322.org),default port=80.
	DDNS_SERVER_TYPE_MAX
}enDdnsServerType;

typedef enum
{
	UPDATE_STEP_SENDING=0,
	UPDATE_STEP_SEND_FINISH,
	UPDATE_STEP_UPDATE_FINISH,
}enUpdateStep;

typedef enum
{
	STATUS_SD,		//SD��״̬
	STATUS_LOGIN,   	//��½״̬
	STATUS_UPDATE,	//�豸��������״̬
	STATUS_FORMAT_DISK,/*��ʽ������*/
	STATUS_CPU_MEM_INFO,/*cpu���ڴ���Ϣ*/
	STATUS_PTZ_TRAJECTORY_INFO,/*�켣��¼״̬*/
	STATUS_RECORD_DOWN,/*¼������״̬*/
	STATUS_REBOOT,//�豸����
	STATUS_REPAIR_DISK_FS,/*�޸������ļ�ϵͳ*/
	STATUS_PTZ_XYZOOM_SET,/*����䱶����״̬*/
	STATUS_PTZ_ANGLE_INFO,/*�����б״̬*/
	STATUS_PASSAGE_MODE_INFO,/*����ģʽ״̬*/
	STATUS_DOT1X_AUTHENTICATION,/*802.1x��֤״̬*/
	STATUS_MECHROUTE_TEST_OK,//��е�г̲��Գɹ�
}enStatusType;
/***************************************///added by wjq 2012-9-13

typedef enum
{
	DEVICE_TYPE_GOSUNCN =0,			/*�������豸*/
	DEVICE_TYPE_DDT	=1				/*�ϵ����豸*/
}enBallDeviceType;

/*****************************FIX ME 2012-11-13 ץ�Ļ���ز��� */
typedef enum
{
	WB_VIDEO_MODEL_Manual,	//�ֶ�ģʽ
	WB_VIDEO_MODEL_AUTO,	//�Զ�ģʽ
	WB_VIDEO_MODEL_AUTO_TRCK,	//�Զ�����ģʽ
	WB_VIDEO_MODEL_ONE,	//һ�ΰ�ƽ��
	WB_VIDEO_MODEL_IN,	//����
	WB_VIDEO_MODEL_OUT,	//����
	WB_VIDEO_MODEL_NIGHT,	//ҹ��
	WB_VIDEO_MODEL_EVENING,	//����
	WB_VIDEO_MODEL_SUNNY,	//����
	WB_VIDEO_MODEL_CLOUDY,	//����
	WB_VIDEO_MODEL_SHADY,	//����
	WB_VIDEO_MODEL_LAMP,	//�׳��
	WB_VIDEO_MODEL_FLUO_LAMP,	//ӫ���
	WB_VIDEO_MODEL_FLASH_LAMP,	//�����
	WB_VIDEO_MODEL_OTHER,	//����
}WHITE_BALANCE_VIDEO_MODE_E;


typedef enum
{
	// Wide dynamic
	WD_MODE_OPEN,//����
	WD_MODE_CLOSE,//�ر�
	WD_MODE_2,// ģʽ2
	WD_MODE_3,// ģʽ3
	WD_MODE_4,// ģʽ4
	WD_MODE_5,// ģʽ5
} WIDE_DYNAMIC_MODE_E;


typedef enum
{
	IL_MODE_AUTO,/*�Զ�*/
	IL_MODE_MANAUL_OPEN,/*�ֶ���*/
	IL_MODE_MANAUL_CLOSE,/*�ֶ���*/
	IL_MODE_FAR_OPEN,/*Զ�ƿ�*/
	IL_MODE_CLOSETO_OPEN,/*���ƿ�*/

}INFRARED_LIGHT_MODE_E;
/*****************************FIX ME 2012-11-13 ץ�Ļ���ز��� end*/

typedef enum
{
	E_ENCRYMODE_NULL = 0,
	E_ENCRYMODE_WEP = 1,
	E_ENCRYMODE_WAP = 2,
	E_ENCRYMODE_WAP2 = 3,
}enEncryMode;

typedef enum
{
	E_EVENT_TYPE_MD 		=1,			/*move detection*/
	E_EVENT_TYPE_IO			=2,			/*IO */
	E_EVENT_TYPE_NET_DOWN 	=3,			/*net down*/
	E_EVENT_TYPE_NET_CLASH 	=4,			/*ip clash*/
	E_EVENT_TYPE_NO_SD		=5,			/*no sd*/
	E_EVENT_TYPE_SD_LACK 	=6,			/*SDLackSpace*/
	E_EVENT_TYPE_SD_ERROR	=7,			/*SD Error */
	E_EVENT_TYPE_HIDE		=8,			/*hide alarm*/
	E_EVENT_TYPE_NOSIGNAL	=9,			/*signal lost alarm*/
	E_EVENT_TYPE_LOSTFRAME	=10,			/*signal lost alarm*/
	E_EVENT_TYPE_SERIAL 	=11,			/*serial event*/
	E_EVENT_TYPE_IA 		=12,			/*Intelligent analysis event*/
	E_EVENT_TYPE_NAS 		=13,			/*NAS event*/
	E_EVENT_TYPE_SYS_MISC 	=14,			/*system error event*/
	E_EVENT_TYPE_SYS_15		=15,
	E_EVENT_TYPE_SYS_16		=16,
	E_EVENT_TYPE_SYS_17		=17,
	E_EVENT_TYPE_SYS_18		=18,
}enEventType;


typedef enum
{
	E_EVENT_RULE_NULL		=0,			/*NULL*/
	E_EVENT_RULE_IO			=1,			/*IO output */
	E_EVENT_RULE_SNAP		=2,			/*snap */
	E_EVENT_RULE_RECD		=3,			/*recd  */
	E_EVENT_RULE_PTZ		=4,			/*PTZ ctrl */
	E_EVENT_RULE_SERIAL		=5,			/*trans serial data */
	E_EVENT_RULE_OSD		=6,			/*OSD ctrl */
	E_EVENT_RULE_UPINFO		=7,			/*upto center */
	E_EVENT_RULE_BNC		=8,			/*BNC ctrl */
	E_EVENT_RULE_IA			=9,			/*Intelligent analysis  ctrl */
	E_EVENT_RULE_AUDIO		=10,			/*Audio output*/
	E_EVENT_RULE_SOUNDRECD	=11,			/*sound recording*/
	E_EVENT_RULE_SHELL		=12,			/*linux shell script*/
	E_EVENT_RULE_UPTXT		=13,			/*up to center this txt info*/
	E_EVENT_RULE_MAX		=32,			/**/	
}enEventRuleType;

typedef enum
{
	E_MODE_SCENE_OFF = 0,
	E_MODE_SCENE_DAY =1,
}enSceneMode;

//У׼��������
typedef enum
{
	E_CORRECT_TYPE_VIEW,//�ӳ���
	E_CORRECT_TYPE_RETURN_DIFF,//�س̲�
	E_CORRECT_TYPE_FOCUSCURVE,//�۽�����
}enCorrectType;

/////*************cmd start*******************/////
typedef enum
{
	// Client Request Command,   Client -> Server
	CMD_ReqLogin           = 10001000,
	CMD_AswLogin           = 10002000,
	CMD_ReqHeartBeat       = 10001001,
	CMD_AswHeartBeat       = 10002001,
	CMD_ReqLogout          = 10001999, // No Answer	
	CMD_ReqMon             = 20001001,
	CMD_AswMon             = 20002001,
	CMD_ReqStartPb         = 20001023,
	CMD_AswStartPb         = 20002023,
	CMD_ReqSetPbSpeed      = 20001024,
	CMD_AswSetPbSpeed      = 20002024,
	CMD_ReqStopPb          = 20001025,
	CMD_AswStopPb          = 20002025,
	CMD_ReqSetPbPos        = 20001026,
	CMD_AswSetPbPos        = 20002026,	
	CMD_ReqTalkback        = 20001027,
	CMD_AswTalkback        = 20002027,
	CMD_ReqStorageData	   = 20001028,//���󱾵ش洢����
	CMD_AswStorageData	   = 20002028,//��Ӧ���ش洢����
	CMD_ReqSnapshot        = 30001035,
	CMD_AswSnapshot        = 30002035,
	CMD_ReqUpdateFile      = 30001008,
	CMD_AswUpdateFile      = 30002008,
	CMD_ReqDownloadFile	   = 30001096,/*���������ļ�*/
	CMD_AswDownloadFile	   = 30002096,/*Ӧ�������ļ�*/
	CMD_ReqSysLog          = 30001013,
	CMD_AswSysLog          = 30002013,
	CMD_ReqSrchSDFile      = 30001022,
	CMD_AswSrchSDFile      = 30002022,
	//CMD_ReqGetAllPrePointName = 30001088,/*Ԥ�õ�����*/
	CMD_AswGetAllPrePointName = 30002088,/*Ԥ�õ�����*/

////////////////// set or get //////////////////////////////
	//CMD_ReqSetSensorAddr   = 40001900,
	//CMD_ReqGetSensorAddr   = 40001901,
	CMD_ReqPtzAct          = 40001006,
	CMD_ReqManualAlarm     = 40001007,
	CMD_ReqGetUserList     = 40001011,
	CMD_ReqModifyUser      = 40001012,
	CMD_ReqGetDevInfo      = 40001014,
	CMD_ReqIFrame          = 40001019,
	CMD_ReqStorageInfo     = 40001028,
	CMD_ReqDiskMaintain      = 40001029,
	//CMD_ReqDiskDirInfo     = 40001030,
	CMD_ReqSetNetFtpCfg    = 40001045,/*add lee, 20120723*/
	CMD_ReqGetNetFtpCfg    = 40001046,
	CMD_ReqSetNetSmtpCfg   = 40001047,
	CMD_ReqGetNetSmtpCfg   = 40001048,	
	CMD_ReqGetOverlayRegionSet       = 40001049,/*OSD����*/
	CMD_ReqSetOverlayRegionSet       = 40001050,
	CMD_ReqGetCoverRegionSet       = 40001051,/*��˽�ڵ�*/
	CMD_ReqSetCoverRegionSet       = 40001052,
	CMD_ReqGetPictureParamSet       = 40001053,/*ͼƬ����*/
	CMD_ReqSetPictureParamSet       = 40001054,
	CMD_ReqGetTimingSnapInfo     = 40001055,/*���Ӷ�ȡ��ʱץ�Ĳ���added by zengqingfeng 20120704*/
	CMD_ReqSetTimingSnapInfo     = 40001056,/*�������ö�ʱץ�Ĳ���added by zengqingfeng 20120704*/
	CMD_ReqGetNormalRecInfo     = 40001057,/*���Ӷ�ȡ��ʱ¼�����added by zengqingfeng 20120721*/
	CMD_ReqSetNormalRecInfo     = 40001058,/*�������ö�ʱ¼�����added by zengqingfeng 20120721*/
	CMD_ReqGetRecParamInfo     = 40001059,/*���Ӷ�ȡ¼�����added by zengqingfeng 20120721*/
	CMD_ReqSetRecParamInfo     = 40001060,/*��������¼�����added by zengqingfeng 20120721*/
	CMD_ReqGetIpFilterInfo     = 40001061,/*���Ӷ�ȡip��������added by zengqingfeng 20120704*/
	CMD_ReqSetIpFilterInfo     = 40001062,/*��������ip����added by zengqingfeng 20120704*/
	CMD_ReqGetMotionDetectSet  = 40001063,/*�ƶ����*/
	CMD_ReqSetMotionDetectSet  = 40001064,
	CMD_ReqSetSysTimeSet   = 40001065,/*add lee, 20120723*/
	CMD_ReqGetSysTimeSet   = 40001066,
	CMD_ReqAlarmInfo       = 40001067,//add lee, alarminfo
	CMD_ReqGetProbeDetectSet= 40001068,/*IO�澯����*/
	CMD_ReqSetProbeDetectSet= 40001069,	
	CMD_ReqSetAudioPara    = 40001070,//add lee, 20120725
	CMD_ReqGetAudioPara    = 40001071,
	CMD_ReqSetComPara	   = 40001072,
	CMD_ReqGetComPara      = 40001073,
	CMD_ReqSetWiredNetPara = 40001074,
	CMD_ReqGetWiredNetPara = 40001075,
	CMD_ReqSetNetBasePara  = 40001076,
	CMD_ReqGetNetBasePara  = 40001077,
	CMD_ReqSetMisAlarmPara = 40001078,
	CMD_ReqGetMisAlarmPara = 40001079,
	CMD_ReqGetSDSet	       = 40001080,/*SD��*/
	CMD_ReqSetSDSet		   = 40001081,
	CMD_ReqSetSysBasePara  = 40001082,
	CMD_ReqGetSysBasePara  = 40001083,
	CMD_ReqGetAutoRebootSet	= 40001084,/*�Զ�����*/
	CMD_ReqSetAutoRebootSet	= 40001085,
	CMD_ReqSetManualRebootSet	= 40001086,/*�ֶ�����*/
	CMD_ReqGetVideoParam = 40001089,/*��ȡ��Ƶ����*/
	CMD_ReqSetVideoParam = 40001090,/*������Ƶ����*/
	CMD_ReqGetCodeParam = 40001091,/*��ȡ�������*/
	CMD_ReqSetCodeParam = 40001092,/*���ñ������*/
	CMD_ReqSetDefaultParam = 40001093,/*����Ĭ�ϲ���*/
	CMD_ReqDelSysLog		= 40001094,/*���ϵͳ��־*/
    CMD_ReqGetOnlineUserList= 40001095,/*��ȡ�����û��б�*/
	CMD_ReqSetNetDdnsCfg	= 40001097,/*DDNS ����, add lee,20121019*/
	CMD_ReqGetNetDdnsCfg	= 40001098,/*DDNS ����, add lee,20121019*/
	CMD_ReqSetNetPppoeCfg	= 40001099,/*PPPOE ����, add lee,20121019*/
	CMD_ReqGetNetPppoeCfg	= 40001100,/*PPPOE ����, add lee,20121019*/
	CMD_ReqSetSnapOrSetSnapCfg       = 40001101,//FIX ME zhangyt update 2012-12-19
	CMD_ReqGetSnapOrSetSnapCfg       = 40001102,//FIX ME zhangyt update 2012-12-19
	CMD_ReqGetSystemStatus		    = 40001103,
	//CMD_ReqSetExposure	= 40001104,	//�ع�����
	//CMD_ReqGetExposure	= 40001105,	//�ع��ȡ
	//CMD_ReqControlDO	= 40001106,	//����DO
	CMD_ReqSetBallMachineParam	= 40001107,/*����������added by zengqingfeng 20130129*/
	CMD_ReqGetBallMachineParam 	= 40001108,/*�����ȡ���added by zengqingfeng 20130129*/
	CMD_ReqSendTransData     = 40001109,/*����͸������added by zengqingfeng 20130129*/
	CMD_ReqSetPtzPara       = 40001110,/*�������õ���Ԥ�õ�/ɨ��/�켣����added by zengqingfeng 20130129*/
	CMD_ReqSetHideAlarm		= 40001111,//�ڵ��澯����
	CMD_ReqGetHideAlarm		= 40001112,//�ڵ��澯��ȡ
	CMD_ReqSetComLinkage	= 40001113,//���ô�������	qxs	2013.3.6
	CMD_ReqGetComLinkage	= 40001114,//��ȡ��������	qxs	2013.3.6
	CMD_ReqSetGB28181Set	= 40001115,//����GB28181XML		qxs	2013.3.11
	CMD_ReqGetGB28181Set	= 40001116,//��ȡGB28181XML		qxs	2013.3.11
	CMD_ReqFindDev			= 40001117,//UDP�����豸Э��		 qxs	2013.3.21
	CMD_ReqSetDevNet		= 40001118,//UDP�޸��豸�������     qxs	2013.3.21
	CMD_ReqTestCmd			= 40001119,//����Э��				 qxs	2013.4.27
	CMD_ReqSetEventProperty	= 40001120,//�����¼�����				 qxs	2013.6.8
	CMD_ReqGetEventProperty	= 40001121,//��ȡ�¼�����				 qxs	2013.6.8
	CMD_ReqSetLinkage       = 40001122,//������������qxs	2013.6.8
	CMD_ReqGetLinkage       = 40001123,//��ȡ��������qxs	2013.6.8
	CMD_ReqStorageCfgSet	= 40001124,//���󱾵ش洢��������
	CMD_ReqStorageCfgGet	= 40001125,//���󱾵ش洢���û�ȡ
	CMD_ReqWirelessCfgSet	= 40001126,//�����������������������
	CMD_ReqWirelessCfgGet	= 40001127,//������������������û�ȡ
	CMD_ReqSetARInfo		= 40001130,//������ǿ��ʾ����
	CMD_ReqBdParamSet   	= 40001131,//���󱱶���λ��������
	CMD_ReqBdParamGet	    = 40001132,//���󱱶���λ������ȡ
	CMD_ReqWifiCfgSet		= 40001133,//����wifi��������
	CMD_ReqWifiCfgGet		= 40001134,//����wifi������ȡ
	CMD_ReqRouterListGet	= 40001135,//����·�����б�
	CMD_ReqCorrectPos		= 40001136,//����У׼λ��
	CMD_ReqTrafficPlateCodeSet = 40001137,//����������ƺ�����¼
	CMD_ReqTrafficPlateCodeGet = 40001138,//�����ȡ���ƺ�����¼
	CMD_ReqSnapRecordGet	= 40001139,//�����ȡͼƬץ�ļ�¼
	CMD_ReqSnapStorageGet	= 40001140,//�����ȡͼƬץ������
	CMD_ReqRecPlanSet		= 40001141,//����ƻ�¼���������
	CMD_ReqRecPlanGet		= 40001142,//����ƻ�¼�������ȡ
	CMD_ReqOpticAxisSet		= 40001143,//�������У׼������
	CMD_ReqLensParamSet		= 40001144,//����Ͳ����ͷ��������
	CMD_ReqStorageManualCtrlSet	= 40001145,//�����ֶ�¼�����
	CMD_ReqStorageManualCtrlGet	= 40001146,//�����ֶ�¼�������Ϣ
	CMD_ReqIniSet					=40001200,//ini���ü���ȡ
	CMD_SetFaceDetect = 40001201,//��������ʶ������				 lyj 2015.3.11
	CMD_GetFaceDetect = 40001202,//��ȡ����ʶ������				 lyj 2015.3.11
	CMD_ReqTelnetStatusSet = 40001203,//���������豸Telnet����״̬				 cjh 2015.7.7
	CMD_ReqTelnetStatusGet = 40001204,//�����ȡ�豸Telnet����״̬				 cjh 2015.7.7
	CMD_ReqCorrectParamSet	= 40001205,//IPCУ׼�����·�
	CMD_ReqCorrectParamGet	= 40001206,//IPCУ׼�����ϴ�
	// Server Answer Command,    Server -> Client
	//CMD_AswSetSensorAddr	= 40002900,
	//CMD_AswGetSensorAddr	= 40002901,
	CMD_AswPtzAct          = 40002006,
	CMD_AswManualAlarm	= 40002007,
	CMD_AswGetUserList	= 40002011,
	CMD_AswModifyUser	= 40002012,
	CMD_AswGetDevInfo	= 40002014,
	CMD_AswIFrame	= 40002019,
	CMD_AswStorageInfo	= 40002028,
	CMD_AswDiskMaintain	= 40002029,
	//CMD_AswDiskDirInfo	= 40002030,
	CMD_AswSetNetFtpCfg	= 40002045,/*add lee, 20120723*/
	CMD_AswGetNetFtpCfg	= 40002046,
	CMD_AswSetNetSmtpCfg   = 40002047,
	CMD_AswGetNetSmtpCfg   = 40002048,
	CMD_AswGetOverlayRegionSet	= 40002049,/*OSD�ַ�����*/
	CMD_AswSetOverlayRegionSet	= 40002050,
	CMD_AswGetCoverRegionSet	= 40002051,/*��˽�ڵ�*/
	CMD_AswSetCoverRegionSet	= 40002052,
	CMD_AswGetPictureParamSet	= 40002053,/*ͼƬ����*/
	CMD_AswSetPictureParamSet	= 40002054,	
	CMD_AswGetTimingSnapInfo	= 40002055,/*���Ӷ�ȡ��ʱץ�Ĳ���added by zengqingfeng 20120704*/
	CMD_AswSetTimingSnapInfo	= 40002056,/*�������ö�ʱץ�Ĳ���added by zengqingfeng 20120704*/
	CMD_AswGetNormalRecInfo	= 40002057,/*���Ӷ�ȡ��ʱ¼�����added by zengqingfeng 20120721*/
	CMD_AswSetNormalRecInfo	= 40002058,/*�������ö�ʱ¼�����added by zengqingfeng 20120721*/
	CMD_AswGetRecParamInfo	= 40002059,/*���Ӷ�ȡ¼�����added by zengqingfeng 20120721*/
	CMD_AswSetRecParamInfo	= 40002060,/*��������¼�����added by zengqingfeng 20120721*/
	CMD_AswGetIpFilterInfo	= 40002061,/*��������ip����added by zengqingfeng 20120704*/
	CMD_AswSetIpFilterInfo	= 40002062,/*��������ip����added by zengqingfeng 20120704*/
	CMD_AswGetMotionDetectSet	= 40002063,/*�ƶ����*/
	CMD_AswSetMotionDetectSet	= 40002064,
	CMD_AswSetSysTimeSet   = 40002065,/*add lee, 20120723*/
	CMD_AswGetSysTimeSet   = 40002066,
	CMD_AswAlarmInfo       = 40002067,//add lee, alarminfo
	CMD_AswGetProbeDetectSet= 40002068,/*IO�澯*/
	CMD_AswSetProbeDetectSet= 40002069,
	CMD_AswSetAudioPara    = 40002070,//add lee, 20120725
	CMD_AswGetAudioPara    = 40002071,
	CMD_AswSetComPara	   = 40002072,
	CMD_AswGetComPara      = 40002073,
	CMD_AswSetWiredNetPara = 40002074,
	CMD_AswGetWiredNetPara = 40002075,
	CMD_AswSetNetBasePara  = 40002076,
	CMD_AswGetNetBasePara  = 40002077,
	CMD_AswSetMisAlarmPara = 40002078,
	CMD_AswGetMisAlarmPara = 40002079,
	CMD_AswGetSDSet		= 40002080,/*SD��*/
	CMD_AswSetSDSet		= 40002081,
	CMD_AswSetSysBasePara  = 40002082,
	CMD_AswGetSysBasePara  = 40002083,
	CMD_AswGetAutoRebootSet		= 40002084,/*�Զ�����*/
	CMD_AswSetAutoRebootSet		= 40002085,
	CMD_AswSetManualRebootSet	= 40002086,/*�ֶ�����*/
	CMD_AswGetVideoParam = 40002089,/*��Ƶ����*/
	CMD_AswSetVideoParam = 40002090,/*��Ƶ����*/
	CMD_AswGetCodeParam = 40002091,/*�������*/
	CMD_AswSetCodeParam = 40002092,/*�������*/
	CMD_AswSetDefaultParam = 40002093,/*Ĭ�ϲ���*/
	CMD_AswDelSysLog		= 40002094,/*���ϵͳ��־*/
    CMD_AswGetOnlineUserList = 40002095,/*  Ӧ���ȡ�����û��� */
	CMD_AswSetNetDdnsCfg	= 40002097,/*DDNS ����, add lee,20121019*/
	CMD_AswGetNetDdnsCfg	= 40002098,/*DDNS ����, add lee,20121019*/
	CMD_AswSetNetPppoeCfg	= 40002099,/*PPPOE ����, add lee,20121019*/
	CMD_AswGetNetPppoeCfg	= 40002100,/*PPPOE ����, add lee,20121019*/
	CMD_AswSetSnapOrSetSnapCfg  = 40002101,
	CMD_AswGetSnapOrSetSnapCfg  = 40002102,
	CMD_AswGetSystemStatus      = 40002103,
	//CMD_AswSetExposure	= 40002104,	//�ع�����
	//CMD_AswGetExposure	= 40002105,	//�ع��ȡ
	//CMD_AswControlDO	= 40002106,	//����DO
	CMD_AswSetBallMachineParam 	= 40002107,/*Ӧ�������� added by zengqingfeng 20130129*/
	CMD_AswGetBallMachineParam 	= 40002108,/*Ӧ���ȡ��� added by zengqingfeng 20130129*/
	CMD_AswSendTransData    = 40002109,/*Ӧ��͸������ added by zengqingfeng 20130129*/
	CMD_AswSetPtzPara       = 40002110,/*Ӧ�����õ���Ԥ�õ�/�켣/ɨ������ added by zengqingfeng 20130129*/
	CMD_AswSetHideAlarm     = 40002111,//�ڵ��澯����Ӧ��
	CMD_AswGetHideAlarm		= 40002112,//�ڵ��澯��ȡӦ��
	CMD_AswSetComLinkage	= 40002113,//���ô�������Ӧ��	qxs	2013.3.6
	CMD_AswGetComLinkage	= 40002114,//��ȡ��������Ӧ��	qxs	2013.3.6
	CMD_AswSetGB28181Set	= 40002115,//����GB28181XML		qxs	2013.3.11
	CMD_AswGetGB28181Set	= 40002116,//��ȡGB28181XML		qxs	2013.3.11
	CMD_AswFindDev			= 40002117,//UDP�����豸Э��		 qxs	2013.3.21
	CMD_AswSetDevNet		= 40002118,//UDP�޸��豸�������     qxs	2013.3.21
	CMD_AswTestCmd			= 40002119,//����Э��			     qxs	2013.4.27
	CMD_AswSetEventProperty	= 40002120,//�����¼�����				 qxs	2013.6.8
	CMD_AswGetEventProperty = 40002121,//��ȡ�¼�����				 qxs	2013.6.8
	CMD_AswSetLinkage       = 40002122,//������������qxs	2013.6.8
	CMD_AswGetLinkage       = 40002123,//��ȡ��������qxs	2013.6.8
	CMD_AswStorageCfgSet	= 40002124,//��Ӧ���ش洢��������
	CMD_AswStorageCfgGet	= 40002125,//��Ӧ���ش洢���û�ȡ
	CMD_AswWirelessCfgSet	= 40002126,//��Ӧ�������������������
	CMD_AswWirelessCfgGet	= 40002127,//��Ӧ��������������û�ȡ
	CMD_AswSetARInfo		= 40002130,//��Ӧ������ǿ��ʾ����
	CMD_AswBdParamSet		= 40002131,//Ӧ�𱱶���λ��������
	CMD_AswBdParamGet		= 40002132,//Ӧ�𱱶���λ������ȡ
	CMD_AswWifiCfgSet		= 40002133,//��Ӧwifi��������
	CMD_AswWifiCfgGet		= 40002134,//��Ӧwifi������ȡ
	CMD_AswRouterListGet	= 40002135,//��Ӧ·�����б��ȡ
	CMD_AswCorrectPos		= 40002136,//Ӧ��У׼λ��
	CMD_AswTrafficPlateCodeSet	= 40002137,//��Ӧ�������ƺ�����¼
	CMD_AswTrafficPlateCodeGet	= 40002138,//��Ӧ��ȡ���ƺ�����¼
	CMD_AswSnapRecordGet	= 40002139,//��Ӧ��ȡͼƬץ�ļ�¼
	CMD_AswSnapStorageGet	= 40002140,//��Ӧ��ȡͼƬץ������
	CMD_AswRecPlanSet		= 40002141,//��Ӧ�ƻ�¼���������
	CMD_AswRecPlanGet		= 40002142,//��Ӧ�ƻ�¼�������ȡ
	CMD_AswOpticAxisSet		= 40002143,//��Ӧ����У׼������
	CMD_AswLensParamSet		= 40002144,//��ӦͲ����ͷ��������
	CMD_AswStorageManualCtrlSet	= 40002145,//��Ӧ�ֶ�¼�����
	CMD_AswStorageManualCtrlGet	= 40002146,//��Ӧ�ֶ�¼�������Ϣ
	CMD_AswIniSet					=40002200,//ini���ü���ȡ
	CMD_AswSetFaceDetect = 40002201,//��������ʶ������Ӧ��				 lyj 2015.3.11	
	CMD_AswGetFaceDetect = 40002202,//��ȡ����ʶ������Ӧ��				 lyj 2015.3.11		
	CMD_AswTelnetStatusSet = 40002203,//��Ӧ�����豸Telnet����״̬				 cjh 2015.7.7
	CMD_AswTelnetStatusGet = 40002204,//��Ӧ��ȡ�豸Telnet����״̬			     cjh 2015.7.7
	CMD_AswCorrectParamSet	= 40002205,//��ӦIPCУ׼�����·�
	CMD_AswCorrectParamGet	= 40002206,//��ӦIPCУ׼�����ϴ�

	// Post Command,    Server <-> Client
	CMD_PostSysLog         = 3001, // Server post system log. Currently reserved.
	CMD_PostMonData        = 3002, // Server transmit monitor video & audio data to Client.
	CMD_PostAlarmInfo      = 3003, // Server send alarm info to client.
	CMD_PostUpdateFileData = 3004, // Client update front end device's file.
	CMD_PostSrchSDFile     = 3005, // Search record file result.
	CMD_PostPbData         = 3006, // Server post record playback file data to client.
	CMD_PostPbProg         = 3007, // Server post playback progress to client.
	CMD_PostVoiceUpData    = 3008, // Talkback, client send voice data to server.
	CMD_PostVoiceDownData  = 3009, // Talkback, server send voice data to client.
	CMD_PostSnapshotData   = 3016,
	//CMD_PostPrePointName = 3017,/*Ԥ�õ�����*/
	CMD_PostSystemStatus   = 3018,/*��ȡϵͳ״̬*/
	CMD_PostDownloadFileData    = 3019,/*�������������ļ�*/
	CMD_PostIntelligentanalysisInfo= 3020, // �����������ܷ���������Ϣ
	CMD_PostStreamHeartbeat        = 3021, // ý������·����
	CMD_PostClientDevInfo		= 3022,//������Ϊclient���豸����Ϣ����
	CMD_PostWirelessStatus         = 3100, //�ϴ���������״̬
	CMD_PostGpsInfo        = 3101, // ����GPS����
	CMD_PostWifiStatus			= 3102,//wifi����״̬��Ϣ����
	CMD_PostSnapRecord                  = 3103, // �豸����ͼƬ��¼
	CMD_PostSnapStorage                 = 3104, // �豸����ͼƬ����
	CMD_PostXinBiaoArrival              = 3110, // �ű굽��
	
	CMD_PostGuomaiDeviceInfo            = 3220,  // �����豸��Ϣ
	CMD_PostGuomaiGps                  = 3221,  // �����豸GPS 
	CMD_PostGuomaiSos                  = 3222,  // �����豸SOS 
	CMD_PostGuomaiDevState             = 3223,  // �����豸״̬��Ϣ

	CMD_ReqCenterServerGet = 60001000,//TK1�����ȡ���ķ�������ַ��Ϣ
	CMD_AswCenterServerGet = 60002000,//TK1��Ӧ��ȡ���ķ�������ַ��Ϣ
	CMD_ReqCenterServerSet = 60001001,//TK1�����������ķ�������ַ��Ϣ
	CMD_AswCenterServerSet = 60002001,//TK1��Ӧ�������ķ�������ַ��Ϣ
	CMD_ReqAIEnableSwitchGet = 60001002,//�����ȡ���ܷ����㷨ʹ�ܿ���	
	CMD_AswAIEnableSwitchGet = 60002002,//��Ӧ��ȡ���ܷ����㷨ʹ�ܿ���
	CMD_ReqAIEnableSwitchSet = 60001003,//�����������ܷ����㷨ʹ�ܿ���	
	CMD_AswAIEnableSwitchSet = 60002003,//��Ӧ�������ܷ����㷨ʹ�ܿ���
	CMD_ReqAIServerStatusGet	= 60001004,//�����ȡ���ܷ�����״̬ 		 
	CMD_AswAIServerStatusGet	= 60002004,//��Ӧ��ȡ���ܷ�����״̬ 
	CMD_PosSerialCmd	= 60003005,//���ʹ�����Ϣ 

	CMD_ReqWifiConnStatusSet = 70001000, // ����DM368 WIFI����������
	CMD_AswWifiConnStatusSet = 70002000, // ��ӦDM368 WIFI���������ˣ� ʹ��ͨ�ýṹ��ظ�
	
	CMD_ReqSetRobotRouteDetail = 40001601, //��������������·��
	CMD_AswSetRobotRouteDetail = 40002601, //��������������·��Ӧ��
	CMD_ReqGetRobotRouteDetail = 40001602, //��������ʾ��ȡ·��
	CMD_AswGetRobotRouteDetail = 40002602, //��������ʾ��ȡ·��Ӧ��

	CMD_ReqRobotParamSetGet		=50001500,//���������˲������úͻ�ȡ
	CMD_AswRobotParamSetGet		=50002500,//���������˲������úͻ�ȡ����
	CMD_PushOnRobotInfo		    = 5000,//������������������
	CMD_PushDownRobotInfo		= 6000,//�������������������·�


}enNetCmd;

//typedef enum
//{
//	RC_RobotPushOnImageAi	= 301,//��������ͼ�����,����ΪTReqRobotPushOnImageAi
//}enNetSubCmd;

#define INIT_NET_PACK(pack,cmd)    { memset(&(pack), 0, sizeof((pack))); \
                                     (pack).head.dwMagicCode = NETWORK_MAGIC_CODE; \
                                     (pack).head.wSize = sizeof((pack)); \
									 (pack).head.wCmdId = cmd; }


#if defined(WIN32)
	#pragma pack(1)
#endif


/****************************************************************************************/
/***********************                                       **************************/
/***********************            General Structs            **************************/
/***********************                                       **************************/
/****************************************************************************************/
/*Э��ͷ�ṹ��*/
struct _TCmdHead
{
	DWORD dwMagicCode; // Always be NETWORK_MAGIC_CODE
	DWORD  wSize;       // Total packet size, including TCmdHead & Cmd Data
	DWORD  wCmdId;      // command id
}__PACKED__;
typedef struct _TCmdHead TCmdHead;


/**************************************************/
/************      ƽ̨�ӿڿ�ʼ      **************/
/**************************************************/

struct _TReqGetCorrectInfo
{
	TCmdHead 		head;
	enCorrectType   type;			//У����������
}__PACKED__;
typedef struct _TReqGetCorrectInfo TReqGetCorrectInfo;

struct _TAswGetCorrectInfo
{
	TCmdHead 		head;
	int				nResult;
	enCorrectType   type;			//У����������
	unsigned int    dataLen;		//У�����ݴ�С
	char			cData[0];	//У������
}__PACKED__;
typedef struct _TAswGetCorrectInfo TAswGetCorrectInfo;

struct _TVideoParam
{
	// Color Adjust 
	BYTE Luminance;								//����[0-100]
	BYTE Contrast;								//�Աȶ�[0-100]
	BYTE Saturation;							//���Ͷ�[0-100]
	BYTE Hue;									//���[0-100]

	// Invert image horizontal & vertical
	BYTE bHorzInvert;							//ˮƽ����
	BYTE bVertInvert;							//��ֱ����

	enGainMode eGainMode;						/*����ģʽ*/
	BYTE bGainModeMax;							/*��������*/
	enExposureMode eExposureMode;				/*�ع�ģʽ*/
	BYTE bMExposureValue;						/*�ֶ��ع�ֵ*/
	BYTE bAutoIris;								/*�Զ���Ȧ*/
	BYTE bLightInhibition;						/*ǿ������*/
	BYTE bBacklightCompensation;				/*���ⲹ��*/
	enScenarioMode eScenarioMode;				/*�龰ģʽ*/
	enNightMode eNightMode;						/*��ҹģʽ*/	
	BYTE ucLumNow;								/*��ǰ����ֵ,������*/
	BYTE ucNightModeLumMax;						/*��ҹģʽΪ�Զ�: ����С�ڸ�ֵʱ���л����ڰ�ģʽ*/
	BYTE ucDayModeLumMin;						/*��ҹģʽΪ�Զ�: ���ȴ��ڸ�ֵʱ���л�����ɫģʽ�������ucNightModeLumMax*/
	BYTE ucDNModeClt;							/*��ҹģʽΪ�Զ�: ��ҹ�ο���׼ 0:�������� 1:�Զ�����*/	
	// Reserved bytes, for future extension

	/*****************************FIX ME 2012-11-13 ץ�Ļ���ز���*/
	BYTE  ucHue;								/*ɫ��[0-100]*/
	unsigned int uiMShutterSpeed;				/*�ֶ��ع�ʱ�� 
	 											1/1 1/2  1/3  1/4  1/6  1/12  1/25  1/30  1/60 1/90 1/100 1/125 1/180
												1/195 1/215 1/230 1/250 1/350 1/500 1/725 1/1000 1/1500 1/2000 1/3000 1/4000 1/6000 1/10000 1/30000*/
	unsigned int uiAutoShutterLimit;			/*�ع�ʱ�����ֵ 
	 											1/1 1/2  1/3  1/4  1/6  1/12  1/25  1/30  1/60 1/90 1/100 1/125 1/180
												1/195 1/215 1/230 1/250 1/350 1/500 1/725 1/1000 1/1500 1/2000 1/3000 1/4000 1/6000 1/10000 1/30000*/
	BYTE	bAutoIrisMode;						/*�Զ���Ȧģʽ0�رգ�1����*/
	BYTE  	ucManualIris;						/*�ֶ���Ȧֵ��0 - 6 F1.6 F2.0 F2.4 F2.8 F3.4 F4.0 F4.8*/
	char 	BExpCPS;							/*�عⲹ��[-128-127]*/
	BYTE 	ucExpCPSMode; 						/*�عⲹ��ģʽ 0�أ�1:ȫ�ֲ�����2:�������򲹳�*/
	WHITE_BALANCE_VIDEO_MODE_E eWBMode;			/*��ƽ��ģʽ*/
	BYTE  ucRGGain;								/*R/G����[0-127]*/
	BYTE  ucBGGain;								/*B/G����[0-127]*/
	BYTE  ucManualGain;							/*�ֶ���������[0-100]*/
	BYTE  ucAutoGainLimit;						/*�Զ��������ֵ[0-100]*/

	WIDE_DYNAMIC_MODE_E eWDMode;				/*��̬ģʽ*/
	unsigned short usBLCPS_X;					/* Backlight compensation  x����*/
	unsigned short usBLCPS_Y;					/* Backlight compensation  y����*/
	unsigned short usBLCPS_W;					/* Backlight compensation  ���*/
	unsigned short usBLCPS_H;					/* Backlight compensation  �߶�*/
	BYTE  ucBacklightCompensation;				/*���ⲹ��[0-255]*/
	BYTE  ucToNoiseMode;						/*ȥ���ģʽ[0-16] 0���أ�1������2��3Dȥ�룬3������ȥ��*/
	BYTE  ucEShutterClass;						/* ���������ŵȼ� 0�أ�1. 1/1 2. 1/2 3. 1/3 4. 1/4 5. 1/6 6. 1/12 7. 1/25 8. 1/30*/
	BYTE  ucDayToNightChnV;						/* ��ҹת����ֵ[��->ҹ] [0-127]*/
	BYTE  ucNightToDayChnV;						/* ��ҹת����ֵ[ҹ->��] [0-127]*/
	BYTE  ucNightDayChnSensity;					/* ��ҹת�������� [0-127]*/
	BYTE  ucNightDayChnDaley;					/* ��ҹת����ʱ [0-127]*/
	BYTE  bLIKInfraredlit;						/*��������� 0�ر�  1����*/
	INFRARED_LIGHT_MODE_E eInfraredlitMode;		/*�����ģʽ*/
	BYTE	ucGammaVal;							/*٤��У��ֵ 0:�أ�1:0����2:1����3:2��*/
	BYTE 	ucSensitiveVal;						/*��������/������ģʽ [0-127]*/
	BYTE	ucDelFogClass;						/*ȥ��ȼ� [0-100]  0 �ر� 1 �Զ� >1 �ֶ�ǿ��*/
	BYTE	ucCamCorrection;					/*��ͷ���� [0-127]*/
	BYTE	bShadEnable;						/*Shad ����0�� 1��*/
	BYTE	bFixDeadPix;						/*ȥ���㿪��0�� 1��*/
	BYTE	ucAntiFlicker;						/*ȥ��˸0�� 1:50HZ  2:60HZ*/
	//��52�ֽ�
	//��ת��ģʽ	0	1	0	ģʽ��0����ɫ 1���ڰ�
	/*****************************FIX ME 2012-11-13 ץ�Ļ���ز��� end*/
	enSceneMode eSceneMode;						/*�û��Զ��峡����Ӧ*///zhangyongtao add 2015-05-15
	BYTE    bStabilizer;						/*�������� 2�� 1��*/
	BYTE    ucStabilizerFunc;					/*�������� 0:���ֱ䱶ģʽ,1:�����˲�ģʽ,2:�Զ�����ģʽ*/
	BYTE    ucStabilizerFuncLevel;				/*���ܵȼ� ���ֱ䱶ģʽ[0:10%,1:20%,2:30%] �����˲�ģʽ[0:��,1:��,2:��] �Զ�����ģʽ[0:off,1:half,2:full]*/
	BYTE    ucSceneFlag;						//0��ʾ��Ƶ�������� 1��ʾ����ģʽ����
	BYTE    ucLocalScene;						//0��ʾ���� 1��ʾ���� ��ǰ�ĳ�������һ���Ǳ�ʾ���ϻ��߰���
	BYTE    ucStartHour;						//��ʼʱ�����24Сʱ����
	BYTE    ucEndHour;							//����ʱ�� ������ֿ�ʼʱ��Ƚ���ʱ���˵���м��Խ���賿

	BYTE	bPassageMode;						/*����ģʽ: =0 �ر�, =����,����*/
	BYTE	uc2DNR;	 							/*2D ���� 0 - 100*/
	BYTE 	uc3DNR; 							/*3D ����* 0 - 100*/
	BYTE	ucFocusMode;						/*�۽�ģʽ��0  �ֶ� 1 �Զ� 2 һ�ξ۽�*/;
	BYTE 	ucFocusDistanceMin;					/*��С�۽�����*/	
	BYTE	ucWDRStrength;						/*��̬ǿ�� 0 - 100*/	
	BYTE	ucAutoTimeMin;						/*�ع�ʱ����Сֵ 
												1/1 1/2  1/3  1/4  1/6  1/12  1/25  1/30  1/60 1/90 1/100 1/125 1/180
												1/195 1/215 1/230 1/250 1/350 1/500 1/725 1/1000 1/1500 1/2000 1/3000 1/4000 1/6000 1/10000 1/30000*/
	BYTE 	ucAutoGainMin;						/*�������� 0 - 100*/
	BYTE	ucAutoIrisMax;						/*��Ȧ���ֵ 0 - 6 F1.6 F2.0 F2.4 F2.8 F3.4 F4.0 F4.8*/
	BYTE	ucAutoIrisMin;						/*��Ȧ��Сֵ 0 - 6 F1.6 F2.0 F2.4 F2.8 F3.4 F4.0 F4.8*/
	BYTE	ucDefogMode;						//͸��ģʽ��0:�رգ�1:�Զ���2:�ֶ�
	BYTE	ucDigitalZoom;						//���ֱ䱶��0:�رգ�1:����
	// Reserved bytes, for future extension
	BYTE    ucOpticalDefog;                      //��ѧ͸��0����ʾ�رգ�1��ʾ������2��ʾ�Զ�
	BYTE Reserved[21];//liuxiangtao update 33->22 2017-12-28
}__PACKED__; // Total 128 bytes
typedef struct _TVideoParam TVideoParam;

struct _TReqGetVideoParam
{
	TCmdHead head;
	BYTE ChanNum;
}__PACKED__;
typedef struct _TReqGetVideoParam TReqGetVideoParam;

struct _TAswGetVideoParam
{
	TCmdHead head;
	int nResult;
	BYTE ChanNum;
	TVideoParam stVideoParamCfg;

}__PACKED__;
typedef struct _TAswGetVideoParam TAswGetVideoParam;

struct _TReqSetVideoParam
{
	TCmdHead head;
	BYTE ChanNum;
	TVideoParam stVideoParam;
}__PACKED__;
typedef struct _TReqSetVideoParam TReqSetVideoParam;

struct _TAswSetVideoParam
{
	TCmdHead head;
	int nResult;
	BYTE ChanNum;
	TVideoParam stVideoParamCfg;

}__PACKED__;
typedef struct _TAswSetVideoParam TAswSetVideoParam;



/*�������*/
struct _TMainStreamParam
{
	// Encode
	enStreamType eStreamType;/*��������*/
	enCodeFormat eCodeFormat;/*�����ʽ*/
	DWORD dwVidRes;/*��2�ֽڱ�ʾ�ֱ��ʵĿ��2�ֽڱ�ʾ�ֱ��ʵĸ����� 1900*1080 dwVidRes=0x0780 0438*/
	BYTE FrmRate;//֡��
	enBitRateMode BitRateMode;//���ʿ��� 0:�̶����ʣ�1:�ɱ�����
	WORD BitRate;//����
	BYTE IFrmInterval;//I֡���
	BYTE bDigitalWatermark;/*����ˮӡ*/
	BYTE bWatermarkContent[MAX_DIGITAL_WATERMASK_CONTENT_LEN+1];/*ˮӡ��*/
	BYTE QuantLevel;//ͼ�������ȼ�(ȡֵ0-5)
	// Reserved bytes, for future extension
	/*****************************FIX ME 2012-11-13 ץ�Ļ���ز��� */
	//BYTE	ucFrameCtrl;/* ��������  �����ʣ������ʣ���������*/ 
	BYTE 	ucFrameInfo;/* ��P֡��BBP֡?*/
	BYTE	bFrameEncryption;/*��������0:�� 1:��*/
	//��2���ֽ�
	/*****************************FIX ME 2012-11-13 ץ�Ļ���ز��� end*/


	DWORD dwFps;		/*����֡�� ֡��*1000,��25000=25fps*/
	BYTE  ucPorI	;	/*0:p ��ʾ���� 1:I ��ʾ����*/

	/****add by hy 2017-07-18*****/
	BYTE ucRateSmoothing;/*����ƽ���ȼ�1-9*/

	// Reserved bytes, for future extension
	BYTE Reserved[7-6]; //zhangyt 2013-05-29 7->5
}__PACKED__; // Total 48bytes
typedef struct _TMainStreamParam TMainStreamParam;

struct _TSubStreamParam
{
	BYTE bSubSteam;/*�Ƿ����ô�����*/
	enStreamType eStreamType;/*��������*/
	enCodeFormat eCodeFormat;/*�����ʽ*/
	DWORD dwVidRes;/*��2�ֽڱ�ʾ�ֱ��ʵĿ��2�ֽڱ�ʾ�ֱ��ʵĸ����� 1900*1080 dwVidRes=0x0780 0438*/
	BYTE FrmRate;//֡��
	enBitRateMode BitRateMode;//���ʿ��� 0:�̶����ʣ�1:�ɱ�����
	WORD BitRate;//����
	BYTE IFrmInterval;//I֡���
	BYTE QuantLevel; //ͼ�������ȼ�(ȡֵ0-5)

	// Reserved bytes, for future extension
	/*****************************FIX ME 2012-11-13 ץ�Ļ���ز��� */
	//BYTE	ucFrameCtrl;/* ��������  ?�����ʣ������ʣ���������*/ 
	BYTE 	ucFrameInfo;/* ��P֡��BBP֡?*/
	BYTE	bFrameEncryption;/*��������0:�� 1:��*/
	//��3���ֽ�
	/*****************************FIX ME 2012-11-13 ץ�Ļ���ز��� end*/
	DWORD dwFps;		/*����֡�� ֡��*1000,��25000=25fps*/
	BYTE  ucPorI;	/*0:p ��ʾ���� 1:I ��ʾ����*/

	/****add by hy 2017-07-18*****/
	BYTE ucRateSmoothing;/*����ƽ���ȼ�1-9*/

	BYTE Reserved[8-6]; //zhangyt 2013-05-29 8->8-5
}__PACKED__; // Total 32bytes
typedef struct _TSubStreamParam TSubStreamParam;

struct _TCodeParam
{
	// Encode
	TMainStreamParam stMainStreamParam;/*����������*/
	TSubStreamParam stSubStramParam;/*����������*/

	BYTE	bROIEnable;/* 0:�� 1:��*/ 
	unsigned short usROI_X;/* ROI  x����*/
	unsigned short usROI_Y;/* ROI y����*/
	unsigned short usROI_W;/* ROI  ���*/
	unsigned short usROI_H;// ROI	�߶�*/

	BYTE	bSubROIEnable;/* 0:�� 1:��*/ 
	unsigned short usSubROI_X;/* ROI  x����*/
	unsigned short usSubROI_Y;/* ROI y����*/
	unsigned short usSubROI_W;/* ROI  ���*/
	unsigned short usSubROI_H;// ROI	�߶�*/

	TSubStreamParam stThrdStramParam;/*������������*/
	BYTE	bThrdROIEnable;/* 0:�� 1:��*/ 
	unsigned short usThrdROI_X;/* ROI  x����*/
	unsigned short usThrdROI_Y;/* ROI y����*/
	unsigned short usThrdROI_W;/* ROI  ���*/
	unsigned short usThrdROI_H;// ROI	�߶�*/

	BYTE Reserved[174-41];
}__PACKED__; // Total 256bytes
typedef struct _TCodeParam TCodeParam;

struct _TReqGetCodeParam
{
	TCmdHead head;
	BYTE ChanNum;
}__PACKED__;
typedef struct _TReqGetCodeParam TReqGetCodeParam;

struct _TAswGetCodeParam
{
	TCmdHead head;
	int nResult;
	BYTE ChanNum;
	TCodeParam stCodeParamCfg;

}__PACKED__;
typedef struct _TAswGetCodeParam TAswGetCodeParam;

struct _TReqSetCodeParam
{
	TCmdHead head;
	BYTE ChanNum;
	TCodeParam stCodeParam;
}__PACKED__;
typedef struct _TReqSetCodeParam TReqSetCodeParam;

struct _TAswSetCodeParam
{
	TCmdHead head;
	int nResult;
	BYTE ChanNum;
	TCodeParam stCodeParamCfg;

}__PACKED__;
typedef struct _TAswSetCodeParam TAswSetCodeParam;



/*�ֶ���������*/
struct _TReqSetManualRebootSet
{
	TCmdHead head;
}__PACKED__;
typedef struct _TReqSetManualRebootSet TReqSetManualRebootSet;

struct _TAswSetManualRebootSet
{
	TCmdHead head;
	int nResult;
}__PACKED__;
typedef struct _TAswSetManualRebootSet TAswSetManualRebootSet;



/*¼������*/
struct _TReqStorageCfgSet		
{
	TCmdHead head;	
	char byEnable;	//0:off, 1:on
	enMonBlockType eMonBlockType;
}__PACKED__;
typedef struct _TReqStorageCfgSet TReqStorageCfgSet;

struct _TAswStorageCfgSet	
{
	TCmdHead head;
	int nResult;
}__PACKED__;
typedef struct _TAswStorageCfgSet TAswStorageCfgSet;

struct _TReqStorageCfgGet		
{
	TCmdHead head;
	enMonBlockType eMonBlockType;
}__PACKED__;
typedef struct _TReqStorageCfgGet TReqStorageCfgGet;

struct _TAswStorageCfgGet	
{
	TCmdHead head;
	int nResult;	
	char byEnable;	//0:off, 1:on	
	enMonBlockType eMonBlockType;
}__PACKED__;
typedef struct _TAswStorageCfgGet TAswStorageCfgGet;

/*�ֶ�¼����Ƽ���ȡ*/
struct _TReqStorageManualCtrlSet		
{
	TCmdHead head;	
	char byEnable;	//0:off, 1:on
	enMonBlockType eMonBlockType;
}__PACKED__;
typedef struct _TReqStorageManualCtrlSet TReqStorageManualCtrlSet;
struct _TAswStorageManualCtrlSet	
{
	TCmdHead head;
	int nResult;
}__PACKED__;
typedef struct _TAswStorageManualCtrlSet TAswStorageManualCtrlSet;

struct _TReqStorageManualCtrlGet	
{
	TCmdHead head;
	enMonBlockType eMonBlockType;
}__PACKED__;
typedef struct _TReqStorageManualCtrlGet TReqStorageManualCtrlGet;
struct _TAswStorageManualCtrlGet		
{
	TCmdHead head;	
	int nResult;	
	char byEnable;	//0:off, 1:on
	enMonBlockType eMonBlockType;
}__PACKED__;
typedef struct _TAswStorageManualCtrlGet TAswStorageManualCtrlGet;

/*¼���ѯ*/
struct _TReqStorageData		
{
	TCmdHead head;
	char byFlag; // 1:��ʾ���� 0:��ʾֹͣ
	enMonBlockType eMonBlockType;
	unsigned short dwEventType; //0x0000:��ʾ��ѯȫ���¼�����;0x0001:���ĶϿ�;0x0002:����Ͽ�;0x0004:IP��ͻ 		
	long long     nStartTime;
	long long     nStopTime;
}__PACKED__;
typedef struct _TReqStorageData TReqStorageData;

struct _TAswStorageData
{
	TCmdHead head;
	int nResult;
	unsigned long long nDataSize; //����¼�����ݴ��ٵ�λ�ֽ�
}__PACKED__;
typedef struct _TAswStorageData	 TAswStorageData;

/**************************************************/
/************      ƽ̨�ӿڽ���      **************/
/**************************************************/




/*motion detection struct*/
struct _TEventMotiondetection
{
	BYTE byEnable;			//	1 bytes	�Ƿ����ø��¼�
	BYTE bySensitivity;		//	1 bytes	������
	BYTE byThreshold;		//  1 bytes	��ֵ
	WORD wDebounceTime;	//	2 bytes	ȥ����ʱ��
	WORD wRgnX;			//	2 bytes	X����
	WORD wRgnY;			//	2 bytes	Y����
	WORD wRgnW;			//	2 bytes	���
	WORD wRgnH;			//	2 bytes	�߶�

}__PACKED__;/*13bytes*/
typedef struct _TEventMotiondetection TEventMotiondetection;

/*io detection struct*/
struct _TEventIOetection
{
	BYTE byEnable;				//	1 bytes	�Ƿ����ø��¼�
	WORD wDebounceTime;		//	2 bytes	ȥ����ʱ��
	BYTE byTransducerType;	//	1 bytes	����������0��������1������

}__PACKED__;/*7bytes*/
typedef struct _TEventIOetection TEventIOetection;

/*sd struct*/
struct _TEventSD
{
	BYTE byEnable;				//	1 bytes	�Ƿ����ø��¼�
	BYTE byLeastSpacePercent;	//	1 bytes	�ռ䱨����ֵ

}__PACKED__;/*2bytes*/
typedef struct _TEventSD TEventSD;

/*serial struct*/
struct _TEventSerial
{
	BYTE byEnable;				//	1 bytes	�Ƿ����ø��¼�
	BYTE byComUseType;//	1 bytes	������;��
	enPTZProtocol yPTZProtocol;	//	4 bytes	��̨Э�飺
}__PACKED__;/*9bytes*/
typedef struct _TEventSerial TEventSerial;

/*common struct*/
struct _TEventCommon
{
	BYTE byEnable;				//	1 bytes	�Ƿ����ø��¼�
}__PACKED__;/*1bytes*/
typedef struct _TEventCommon TEventCommon;

struct _TEvent
{
	BYTE byEventType;	//	1 bytes	�¼�����
	BYTE byEventId;			//	1 bytes	�¼�ID
	BYTE byEventLen;			//	1 bytes	�¼����ݳ���M
	BYTE byEventContent[0];		//	M bytes	�¼�����
}__PACKED__;
typedef struct _TEvent TEvent;


/*io rule */
struct _TRuleIO
{
	WORD wRuleDelay;		//	2bytes	�ӳ�
	WORD wRuleDur;			//	2bytes	����ʱ����0:��ʾһֱ
	BYTE byTransducerType;	//	1 bytes	����������
	WORD wAlmOutIONum;		//	2 bytes	���IO ���
	DWORD dwOutInteval;		//	4 bytes	������ms,0�����Ǹ�����
	DWORD dwOutCnt;			//	4bytes	�������Ĭ��1��
}__PACKED__;/*18bytes*/
typedef struct _TRuleIO TRuleIO;

/*snap rule */
struct _TRuleSnap
{
	WORD wRuleDelay;		//	2bytes	�ӳ�
	WORD wRuleDur;			//	2bytes	����ʱ����0:��ʾһֱ
	DWORD dwSnapInterval	;	// 4 bytes	ץ�ļ��
	WORD wSnapCnt;			//	2 bytes	ץ������
	WORD wSendBitFlag;			//	2 bytes	ͼƬ���Ϳ���bit0:FTP;bit1:Email;bit2:���ر���; bit3:���͵�����;bit4:����
}__PACKED__;/*12bytes*/
typedef struct _TRuleSnap TRuleSnap;

/*recd rule */
struct _TRuleRecd
{
	WORD wRuleDelay;		//	2bytes	�ӳ�
	WORD wRuleDur;			//	2bytes	����ʱ����0:��ʾһֱ
	DWORD dwRecordTime;		//	4 bytes	¼��ʱ��
	WORD wSendBitFlag;			//	2 bytes	ͼƬ���Ϳ���bit0:FTP;bit1:Email;bit2:���ر���; bit3:���͵�����;bit4:����
}__PACKED__;/*10bytes*/
typedef struct _TRuleRecd TRuleRecd;

/*ptz rule */
struct _TRulePtz
{
	WORD wRuleDelay;		//	2bytes	�ӳ�
	WORD wRuleDur;			//	2bytes	����ʱ����0:��ʾһֱ
	BYTE byRulePtzType;			//	1 bytes	������������, 0:Ԥ�õ㣬1��ɨ�裬2��Ѳ����3���켣
	BYTE byRulePtzValue;			//	1 bytes	��ӦԤ�õ��/ɨ����ID/Ѳ��ID/�켣ID

}__PACKED__;/*6bytes*/
typedef struct _TRulePtz TRulePtz;

/*serial rule */
struct _TRuleSerial
{
	WORD wRuleDelay;		//	2bytes	�ӳ�
	WORD wRuleDur;			//	2bytes	����ʱ����0:��ʾһֱ
	BYTE bySeiralNum;			//	1 bytes	���ں�
	BYTE bySerialData[0];			//	 Linkage_Len �C 5 bytes	���͸����ڵ�����
}__PACKED__;/*5bytes*/
typedef struct _TRuleSerial TRuleSerial;

/*osd rule */
struct _TRuleOsd
{
	WORD wRuleDelay;		//	2bytes	�ӳ�
	WORD wRuleDur;			//	2bytes	����ʱ����0:��ʾһֱ
	BYTE byOverlayType;			//	1bytes	��������
	BYTE byOSDcontent[36];		//	36bytes	��������
	WORD wX;					//	2bytes	���������X����
	WORD wY;					//	2bytes	���������Y����
}__PACKED__;/*48bytes*/
typedef struct _TRuleOsd TRuleOsd;

/*up alarm info  rule */
struct _TRuleUpInfo
{
	WORD wRuleDelay;		//	2bytes	�ӳ�
	WORD wRuleDur;			//	2bytes	����ʱ����0:��ʾһֱ
	DWORD dwClientBitMap;		//	4 bytes	client������Ӧ��λͼbit0 ��ʾ��һ���ͻ���

}__PACKED__;/*8bytes*/
typedef struct _TRuleUpInfo TRuleUpInfo;

/*BNC rule */
struct _TRuleBnc
{
	WORD wRuleDelay;		//	2bytes	�ӳ�
	WORD wRuleDur;			//	2bytes	����ʱ����0:��ʾһֱ
	BYTE byOpen	;				// 1 bytes	0�رգ�1��

}__PACKED__;/*5bytes*/
typedef struct _TRuleBnc TRuleBnc;

struct _TRule
{
	BYTE byRuleNum;		//	1 bytes	ΪΨһ����ID ÿ���¼��Ĺ����Ϊ1-8��ʾ��Ӧ�ı��¼���8��������ӹ���ʱ��Ҫָ��ʹ����һ������š�
	BYTE byRuleEnable;		//	1 bytes	����ʹ�ܣ�0��ͣ�ã�1������
	BYTE byRuleType;		//	1 bytes	��������
	BYTE byRuleLen;			//	1 bytes	�������ݳ���M
	BYTE byRuleContent[0];	//	Mbytes	��������

}__PACKED__;
typedef struct _TRule TRule;

struct _TEventRule
{
	BYTE byEventType;	//	1bytes	�¼�����
	BYTE byEventId;			//	1 bytes	�¼�ID
	BYTE byRuleCount;			//	1 bytes	����������Ŀ
}__PACKED__;
typedef struct _TEventRule TEventRule;

struct _TTime
{
	WORD Year;    // 1970 ~ 2100
	BYTE Month;   // 1 ~ 12
	BYTE Day;     // 1 ~ 31
	BYTE Hour;    // 0 ~ 23
	BYTE Minute;  // 0 ~ 59
	BYTE Second;  // 0 ~ 59
}__PACKED__;
typedef struct _TTime TTime;


/*��չOSD��������Ϊ4��added by zengqingfeng 20120607*/
struct _TOverlayRegionSet
{
	// OSD
	enOverlayType bOverlayType;/*OSD ����*/
	char chOsdContent[CHAN_NAME_LEN+1];/*OSD ����*/
	BYTE bShowFlag;
	WORD usPos_X;
	WORD usPos_Y;
	
	BYTE Reserved[15];
}__PACKED__; 
typedef struct _TOverlayRegionSet TOverlayRegionSet;


/*�ڵ�����Ϊ4��added by zengqingfeng 20120607*/
struct _TCoverRegionSet
{
	BYTE bShowMosaic;
	WORD Mosaic_X;
	WORD Mosaic_Y;
	WORD Mosaic_W;
	WORD Mosaic_H;
	
	BYTE Reserved[9];
}__PACKED__; 
typedef struct _TCoverRegionSet TCoverRegionSet;


/*��Ƶ����*/
struct _TVideoSettings
{
	
	TVideoParam stVideoParamCfg;
	TCodeParam stCodeParamCfg;

	// Reserved bytes, for future extension
	BYTE Reserved[102];
}__PACKED__; // Total 128 bytes
typedef struct _TVideoSettings TVideoSettings;


/*Ϊ����չ�ƶ��������Ϊ4��added by zengqingfeng 20120612*/
struct _TMotionRegionSet
{
	//�ƶ��������
	BYTE  bShowDetectRegion;/*���ڱ�ʾ��ǰ�ƶ���������Ƿ���Ҫ�����ã�=0��������*/
	WORD usRgnX;/*X����*/
	WORD usRgnY; /*Y����*/
	WORD usRgnW; /*���*/
	WORD usRgnH; /*�߶�*/

	// Reserved bytes, for future extension
	BYTE Reserved[2];
}__PACKED__; // Total 11 bytes
typedef struct _TMotionRegionSet TMotionRegionSet;

struct _TMotionDetectionSet
{
	BYTE bMotionDetect;/*�Ƿ���Ҫ����ƶ����*/
	WORD MotionOutMask;/*�����ʶ*/
//	WORD wAlmOutDelay;/*�����ʱ*/
	WORD wAlmOutDur; /*���ʱ��*/
	BYTE Sensitivity;/*������*/
	BYTE Threshold;/*��ֵ*/
	
	TMotionRegionSet stMotionRegionCfg[MAX_MOTION_DETECT_REGION];//�ƶ��������
	WORD wDebounceTime;/*ȥ����ʱ��*/

	/*����ץ��*/
	BOOL bSnapFlag;/*�Ƿ���Ҫץ��*/
	BYTE chSnapInterval;/*ץ�ļ��*/
	BYTE chSnapCnt;/*ץ������*/
	BYTE bSnapSendToFTP;/*ͼƬ�Ƿ���Ҫ���͵�FTP*/
	BYTE bSnapSendToEmail;/*ͼƬ�Ƿ���Ҫ���͵���������Email*/
	BYTE bSnapSendToSD;/*ͼƬ�Ƿ���Ҫ���͵�SD��*/

	/*����¼��*/
	BOOL bRecFlag;/*�Ƿ���Ҫ¼��*/
	int nRecordTime;/*¼��ʱ��*/
	BYTE bRecSendToFTP;/*¼��ʱ�����͵�FTP��������*/
	BYTE bRecSendToSD;/*¼��ʱ�����͵�SD��������*/
	
	/*������̨*/
	BYTE bLinkPtzFlag;	/*�Ƿ���Ҫ������̨*/
	BYTE bLinkPtzType;	/*������������, 0:Ԥ�õ㣬1��ɨ�裬2��Ѳ����3���켣*/
	BYTE bLinkPtzValue;/*��ӦԤ�õ��/ɨ����ID/Ѳ��ID/�켣ID��������*/

	// Reserved bytes, for future extension
	BYTE Reserved[3];

}__PACKED__; // Total 122 bytes
typedef struct _TMotionDetectionSet TMotionDetectionSet;

//�ڵ��澯
struct _THideAlarmSet
{
	BYTE bHideAlarm;/*�Ƿ���Ҫ����ڵ��澯*/
	BOOL bAlmOutFlag;/*�Ƿ���Ҫ�澯���*/
	WORD wAlmOutDur; /*�澯���ʱ��*/

	BOOL bSnapFlag;	/*�Ƿ���Ҫץ��*/
	char chSnapInterval;	/*ץ�ļ��*/
	char chSnapCnt;	/*ץ������*/
	BYTE bSnapSendToFTP;/*ͼƬ�Ƿ���Ҫ���͵�FTP*/
	BYTE bSnapSendToEmail;/*ͼƬ�Ƿ���Ҫ���͵���������Email*/
	BYTE bSnapSendToSD;/*ͼƬ�Ƿ���Ҫ���͵�SD��*/


	/*����¼��*/
	BOOL bRecFlag;	/*�Ƿ���Ҫ¼��*/
	int nRecordTime;/*¼��ʱ��*/
	BYTE bRecSendToFTP;/*¼��ʱ�����͵�FTP��������*/
	BYTE bRecSendToSD;/*¼��ʱ�����͵�SD��������*/


	/*������̨*/
	BYTE bLinkPtzFlag;	/*�Ƿ���Ҫ������̨*/
	BYTE bLinkPtzType;	/*������������, 0:Ԥ�õ㣬1��ɨ�裬2��Ѳ����3���켣*/
	BYTE bLinkPtzValue;/*��ӦԤ�õ��/ɨ����ID/Ѳ��ID/�켣ID��������*/

	// Reserved bytes, for future extension
	BYTE Reserved[5]; /*Ԥ��3�ֽڱ�Ϊ5�ֽ�*/       
}__PACKED__; // Total 122 bytes
typedef struct _THideAlarmSet THideAlarmSet;


/*I0����*/
struct _TProbeDetectionSet
{
	BYTE bProbeDetect;
	WORD MotionOutMask;/*�����ʶ*/
//	WORD wAlmOutDelay;/*�����ʱ*/
	WORD wAlmOutDur;/*���ʱ��*/
	WORD wDebounceTime;/*ȥ����ʱ��*/

	BYTE chProbeAlarmInChn;/* ����ͨ��*/
	BYTE chProbeAlarmOutChn;/*���ͨ��*/
	enTransducerType eTransducerType;/*����������*/

	/*����ץ��*/
	BOOL bSnapFlag;	/*�Ƿ���Ҫץ��*/
	BYTE chSnapInterval;	/*ץ�ļ��*/
	BYTE chSnapCnt;	/*ץ������*/
	BYTE bSnapSendToFTP;/*ͼƬ�Ƿ���Ҫ���͵�FTP*/
	BYTE bSnapSendToEmail;/*ͼƬ�Ƿ���Ҫ���͵�Email��������*/
	BYTE bSnapSendToSD;/*¼��ʱ�����͵�SD��������*/
	BYTE bSnapSendToCenter;	//����ץ�����͵����� qxs 2013.3.7

	/*����¼��*/
	BOOL bRecFlag;	/*�Ƿ���Ҫ¼��*/
	int nRecordTime;/*¼��ʱ��*/
	BYTE bRecSendToFTP;/*�Ƿ���Ҫ���͵�FTP*/
	BYTE bRecSendToSD;/*¼��ʱ�����͵�SD��������*/
	
	/*������̨*/
	BYTE bLinkPtzFlag;	/*�Ƿ���Ҫ������̨*/
	BYTE bLinkPtzType;	/*������������, 0:Ԥ�õ㣬1��ɨ�裬2��Ѳ����3���켣*/
	BYTE bLinkPtzValue;/*��ӦԤ�õ��/ɨ����ID/Ѳ��ID/�켣ID��������*/

	// Reserved bytes, for future extension
	BYTE Reserved[4];
}__PACKED__; // Total 40 bytes
typedef struct _TProbeDetectionSet TProbeDetectionSet;


/*����ͼƬ��������added by zengqingfeng 20120628*/
 struct _TSnapPictureSet
{
 	BOOL bSnapFlag;	/*�Ƿ���Ҫץ��*/
	BYTE chSnapInterval;	/*ץ�ļ��*/
	BYTE chSnapCnt;	/*ץ������*/
	BOOL bSendToFTP;/*�Ƿ���Ҫ���͵�FTP*/
	BOOL bSendToEmail;/*�Ƿ���Ҫ���͵�Email*/
}__PACKED__; // Total 64 bytes
typedef struct _TSnapPictureSet T_SnapPictureSet ;	

struct _TTimingPlanPeriodSet
{	
	BYTE bEnable;/*�Ƿ��������ʱ��*/
	BYTE StartHour;/*��ʼСʱ*/
	BYTE StartMinute;/*��ʼ����*/
	BYTE StartSecond;/*��ʼ��*/
	BYTE StopHour;/*����Сʱ*/
	BYTE StopMinute;/*��������*/
	BYTE StopSecond;/*������*/
	
	// Reserved bytes, for future extension
	BYTE Reserved[3];
}__PACKED__; 
typedef struct _TTimingPlanPeriodSet TTimingPlanPeriodSet;

struct _TTimingPlanDaySet
{	
	BYTE bEnable;/*�Ƿ���������*/
	TTimingPlanPeriodSet stTimingPlanPeriodCfg[MAX_SNAP_PLAN_PER_DAY];
	
	
	// Reserved bytes, for future extension
	BYTE Reserved[3];
}__PACKED__; 
typedef struct _TTimingPlanDaySet TTimingPlanDaySet;

struct _TNormalRecordSet
{
 	BOOL bEnableFlag;	/*�Ƿ���Ҫ¼��*/
	BOOL bSendToFTP;/*�Ƿ���Ҫ���͵�FTP*/
	BOOL bSendToEmail;/*�Ƿ���Ҫ���͵�Email*/
	TTimingPlanDaySet stNormalRecordPlan[WEEK_MAX_DAY];

	// Reserved bytes, for future extension
	BYTE Reserved[4];
}__PACKED__; 
typedef struct _TNormalRecordSet TNormalRecordSet;

struct _TRecordInfo
{
 	BOOL bEnableFlag;	/*�Ƿ���Ҫ¼��*/
	BOOL bSendToFTP;/*�Ƿ���Ҫ���͵�FTP*/
	BOOL bSendToEmail;/*�Ƿ���Ҫ���͵�Email*/
	int nRecordTime;/*¼��ʱ��*/
	int nDelayTime;/*¼����ʱ*/
	// Reserved bytes, for future extension
	BYTE Reserved[4];
}__PACKED__; 

typedef struct _TRecordInfo TRecordInfoSet;

struct _TRecParam
{
	unsigned char ucEnable;/*�Ƿ���ҪԤ¼*/
	unsigned char ucPreRecLen; /*Ԥ¼ʱ��*/
	int nMaxRecFileTime;/*¼���ļ�ʱ��*/
	enRecControlType eRecControlType;/*¼�����*/
	// Reserved bytes, for future extension
	BYTE Reserved[4];
	
}__PACKED__; 
typedef struct _TRecParam TRecParamSet;

struct _TRecordSet
{
	TRecordInfoSet  stManualAlarmRecordCfg;/*�����ֶ��澯����¼�����ò���*/
	TNormalRecordSet  stNormalRecordCfg;/*���Ӷ�ʱ¼�����ò���*/

	// Reserved bytes, for future extension
	BYTE Reserved[4];
}__PACKED__; 
typedef struct _TRecordSet TRecordSet;


/*added by zengqingfeng 20120726*/
struct _TAutoRebootSet
{
	enAutoReboot eAutoRebootType;
	int nRebootDay;
	int nRebootHour;
	int nRebootMin;
	
	BYTE Reserved[4];
}__PACKED__; // Total 20 bytes
typedef struct _TAutoRebootSet TAutoRebootSet;


/*����ip���˵���ز���added by zengqingfeng 20120704*/
struct _TIpListSet
{
 	unsigned int nIpListStart;	/*IP�����п�ʼ��IP*/
	unsigned int nIpListEnd; 	/*IP�����н�����IP*/
	
	BYTE Reserved[4];
}__PACKED__; 
typedef struct _TIpListSet TIpListSet;

struct _TIpFilterSet
{
 	enIpListTpye  chIpListTpye;	/*IP������ʽ*/
	TIpListSet stBlackIpListCfg[MAX_IP_FILTER_LIST]; 	/*IP������*/
	TIpListSet stWhiteIpListCfg[MAX_IP_FILTER_LIST]; 	/*IP������*/
	
	BYTE Reserved[4];
}__PACKED__; 
typedef struct _TIpFilterSet TIpFilterSet;


struct _TImageFixedAttr
{
	enVideoResolution     eVidRes;
	enVideoResolutionName eVidResName;
	WORD Width;
	WORD Height;
	BYTE MaxFrmRate;
	WORD DefaultBps;

	// Reserved bytes, for future extension
	BYTE Reserved[5];
}__PACKED__; // Total 20 bytes
typedef struct _TImageFixedAttr TImageFixedAttr;

struct _TDeviceInfo
{
	enDeviceType  eDevType;
	char          ProductModel[MAX_PRODUCT_MODEL_LEN+1];
	char          DeviceSerial[DEVICE_SERIAL_LEN+1];
	WORD          wBiosVer; // BIOS version
	WORD          wNetVer;  // Network protocol version
	enVidStd      eVidStd;
	enVidEncType  eVidEncType;
	enAudEncType  eAudEncType;
	BYTE          ChanCnt;
	BYTE          AlmInCnt;
	BYTE          AlmOutCnt;
	BYTE          SupportedVidRes; // Mask of enVideoResolution
	BYTE          bSupportStorage;
	BYTE          bStoragePlugged;
	WORD          wRecState; // Max 16 channels, 1 bit 1 channel.
	BYTE          bSupportWifi;
	BYTE          bSupport2Streams;
	enSensorType  eSensorType;
	enHighDefType eHighDefType;
	BYTE          SupportedVidResSub; // Mask of enVideoResolution
	
	TImageFixedAttr ImgFixAttr[4]; // For Main Channel, Max Support 4 Types of Video Resolution.
								   // ImgFixAttr[0] : VR_D1,  ImgFixAttr[1] : VR_HD1,
								   // ImgFixAttr[2] : VR_CIF, ImgFixAttr[3] : VR_QCIF
								   
	TImageFixedAttr ImgFixAttrSub[2]; // For Sub Channel, Max Support 2 Types of Video Resolution.
								      // ImgFixAttr[0] : VR_CIF,  ImgFixAttr[1] : VR_QCIF
	char          QDUid[DEVICE_SERIAL_LEN+1];
	char          SYunKey[29];
	// Reserved bytes, for future extension
	BYTE          Reserved[1];
}__PACKED__; // Total 256 bytes
typedef struct _TDeviceInfo TDeviceInfo;


struct _TUser
{
	BYTE bValid;
	char Name[USER_NAME_LEN+1];
	char Pswd[USER_PSW_LEN+1];
	enUserLevel eLevel;
	DWORD dwPower; // Mask of enUserPower
	DWORD dwPowerExt; // Mask of enUserPowerExt
	
	// Reserved bytes, for future extension
	BYTE Reserved[17];
}__PACKED__; // Total 64 bytes
typedef struct _TUser TUser;

struct _TUserList
{
	TUser User[MAX_USER_CNT];
}__PACKED__;
typedef struct _TUserList TUserList;


struct _TRecFileInfo
{
	BYTE ChanNum;
	BYTE bFileTypeMask; /*0x01:picturr file,0x02:rec file*/
	BYTE bFileSubTypeMask;/*0x01:alarm rec/pictur file,0x02:timing rec/pictur file,0x04:manual rec/pictur file*/
	WORD wAlarmTypeMask;/*�澯���ͣ���enAlarmType*/
	TTime BegTime;/*��ʼʱ��*/
	TTime EndTime;/*����ʱ��*/
}__PACKED__;
typedef struct _TRecFileInfo TRecFileInfo;

struct _TPtzActParam
{
	BYTE Param1; // 1) To Set/Get point, this means point value, range: 0 ~ 255
	             // 2) To move Left/Up/Right/Down, this means speed, range: 1 ~ 10
	             // 3) To mouse click, this means zooming ration, range: 0 ~ 99
	             
	BYTE Param2; // 1) To mouse click, this means PosX ration, range: 0~0x63, 0x80~0xE3
	
	BYTE Param3; // 1) To mouse click, this means PosY ration, range: 0~0x63, 0x80~0xE3

	// Reserved bytes, for future extension
	BYTE Reserved[29];
}__PACKED__; // Total 32 bytes
typedef struct _TPtzActParam TPtzActParam;

struct _TSDSet
{
	BYTE bCycleRec; // When bCycleRec == 0 && Disk Full, record stop.
					// When bCycleRec == 1 && Disk Full, Cycle record.
	BOOL bStorageStrategy;/*�Ƿ����ô洢����*/

	// Reserved bytes, for future extension
	BYTE Reserved[3];
}__PACKED__; // Total 8 bytes
typedef struct _TSDSet TSDSet;


struct _TDiskInfo
{
	enDiskType eDiskType;
	DWORD dwTotalSize; // Unit : Mega Bytes
	DWORD dwFreeSize; // Unit : Mega Bytes
	char DiskPath[MAX_REC_FILE_PATH+1];

	// Reserved bytes, for future extension
	BYTE Reserved[51];
}__PACKED__; // Total 128 bytes
typedef struct _TDiskInfo TDiskInfo;


struct _TDynChangeSet
{
	BYTE FrmRate;     // Main channel frame rate
	BYTE FrmRateSub;  // Sub channel frame rate
	enVideoResolution eVidRes;      // Main channel Video Resolution
	enVideoResolution eVidResSub;   // Sub channel Video Resolution
	
	BYTE Reserved[54];
}__PACKED__; // Total 64 bytes
typedef struct _TDynChangeSet TDynChangeSet;


/***************************************/ //begin lee
struct _TNetFtpSet					
{
	BYTE bFTPEnable;							//�Ƿ��
	char FTPSvrIp[IP_ADDR_LEN+1];				//FTP������IP
	WORD wFTPSvrPort;							//FTP�˿�
	char FTPSvrUserName[FTP_USER_NAME_LEN+1];	//�û���
	char FTPSvrUserPswd[FTP_USER_PSWD_LEN+1];	//����
	WORD wFTPFileLen;							//�ļ���Сunit: MByte
	char FTPPath[FTP_PATH_LEN+1];				//�ļ�·��
// Reserved bytes, for future extension
	BYTE Reserved[8];
}__PACKED__; // Total 160 bytes
typedef struct _TNetFtpSet TNetFtpSet;

struct _TNetSmtpSet					
{
	BYTE bSMTPEnable;							//�Ƿ��
	char SMTPIp[DDNS_DOMAIN_NAME_LEN+1];		//SMTP������IP,IP_ADDR_LEN->
	WORD wSMTPPort;								//SMTP�˿�
	char SMTPUserName[SMTP_USER_NAME_LEN+1];	//SMTP�û���33
	char SMTPUserPswd[SMTP_USER_PSWD_LEN+1];	//SMTP����33
	char SMTPFromAddr[SMTP_EMAIL_ADDR_LEN+1];	//���͵�ַ65
	char SMTPSbuject[SMTP_SUBJECT_LEN+1];		//�ʼ�����65
	char SMTPToAddr1[SMTP_EMAIL_ADDR_LEN+1];	//���յ�ַ1
	char SMTPToAddr2[SMTP_EMAIL_ADDR_LEN+1];	//���յ�ַ2
	char SMTPToAddr3[SMTP_EMAIL_ADDR_LEN+1];	//���յ�ַ3
	BYTE bSmtpSendAlarmImage;					//�Ƿ���ͼƬ
	BYTE bSendSysStatus;						//����ϵͳ״̬
	WORD wSendSysStatusTime;					//����ϵͳ״̬ʱ������λ:����(1~4500)
	// Reserved bytes, for future extension
	BYTE Reserved[20];
}__PACKED__; // Total 680bytes
typedef struct _TNetSmtpSet TNetSmtpSet;

// DDNS Config
struct _TNetDdnsSet					
{
	BYTE bDdnsEnable;							//DDNS�����Ƿ�����
	enDdnsServerType eDdnsServerType;			//DDNS ����������
	char DdnsSvrIp[DDNS_DOMAIN_NAME_LEN+1];		//DDNS ��������ַ
	WORD wDdnsSvrPort;							//DDNS �������˿�
	char DomainName[DDNS_DOMAIN_NAME_LEN+1];	//�豸����
	char DdnsSvrUserName[DDNS_USER_NAME_LEN+1]; //DDNS �û�����
	char DdnsSvrUserPswd[DDNS_USER_PSWD_LEN+1]; //DDNS �û�����

// Reserved bytes, for future extension
	BYTE Reserved[20];
}__PACKED__; // Total 195 bytes
typedef struct _TNetDdnsSet TNetDdnsSet;


// PPPoE
struct _TNetPppoeSet
{
	BYTE bPppoeEnable;							//PPPOE�����Ƿ�����
	char PppoeUserName[PPPOE_USER_NAME_LEN+1];	//PPPOE �û�����
	char PppoeUserPswd[PPPOE_USER_PSWD_LEN+1];	//PPPOE �û�����
	char PppoeDevIp[IP_ADDR_LEN+1];				//PPPOE ���Ż�ȡ�����豸IP�������䡣
	
// Reserved bytes, for future extension
	BYTE Reserved[20];

}__PACKED__;// Total 101 bytes
typedef struct _TNetPppoeSet TNetPppoeSet;

struct _TNTPSet
{
	BYTE bEnable;									//=0,������;=����,����.
	char chTimeServerAddr[NTP_SERVER_ADD_LEN+1];	//ʱ���������ַ,33
	short nTimeServerPort;							//Ĭ�Ͼ���123.
	short nUpdataTime;								//����Ƶ�ʣ���λ������
}__PACKED__;
typedef struct _TNTPSet TNTPSet;

struct _TDSTTime//����ʱʱ���ʽ
{
	BYTE	Month;	// 1 ~ 12
	BYTE	Day;	// 1 ~ 31
	BYTE	Hour;	// 0 ~ 23
	BYTE	Minute;	// 0 ~ 59
	BYTE	Week;	// 1 ~ 5 
	BYTE	WDay;	// 1 ~ 7
}__PACKED__;
typedef struct _TDSTTime TDSTTime;

struct _TDSTSet	//DatelightSavingTime ����ʱ
{
	BYTE		bEnable;//=0,������;=����,����.
	enDSTType	DSTType;
	TDSTTime	DSTTimeBegin;
	TDSTTime	DSTTimeEnd;
}__PACKED__;
typedef struct _TDSTSet TDSTSet;

struct _TTimeSet
{
	enDateMode	eDateMode;
	enTimeMode	eTimeMode;
	enTimeZone  eTimeZone;//ʱ��
	TTime 		LocalTime;
	TNTPSet		NTPSet;
	TDSTSet		DSTSet;	//����ʱ
	BYTE		reserve[10];
}__PACKED__;
typedef struct _TTimeSet TTimeSet;

//ϵͳ��־��¼��ʽ
struct _TSysLog
{
	TTime Time;
	char UserName[USER_NAME_LEN+1];//USER_NAME_LEN=16
	char UserIP[15+1];
	enMessageType eMessageType;
	char msg[SYS_LOG_MSG_LEN_MAX+1];
}__PACKED__;
typedef struct _TSysLog TSysLog;

struct _TSysLogFilter
{
	char UserName[USER_NAME_LEN+1]; //USER_NAME_LEN=16
	TTime StartTime;
	TTime EndTime;
	enMessageType eMessageType;//�¼�����
}__PACKED__;
typedef struct _TSysLogFilter TSysLogFilter;

/*�����������*/
struct _TWiredNetPara
{
	char	DeviceSerial[DEVICE_SERIAL_LEN+1];//���кţ�DEVICE_SERIAL_LEN=16
	enIPMode eIPMode;
	enIPVer eIPVer;
	
	char NetMAC[NET_MAC_LEN+1];//NET_MAC_LEN=17
	char IpAddr[IP_ADDR_LEN+1];//IP_ADDR_LEN=15
	char NetMask[IP_ADDR_LEN+1];
	char GateWayIp[IP_ADDR_LEN+1];
	char DnsSvrIpFirst[IP_ADDR_LEN+1];//��ѡDNS
	char DnsSvrIpSecond[IP_ADDR_LEN+1];//����DNS
	
	BYTE reserved[100];
}__PACKED__;
typedef struct _TWiredNetPara TWiredNetPara;

/*�����������*/
struct _TNetBasePara
{
	BYTE	ClientConnectNumMax;//���������
	WORD 	wSvrTCPPort;
	WORD 	wSvrUDPPort;
	WORD 	wSvrHTTPPort;
	WORD 	wSvrRTSPPort;
	enTransQoS eTransQoS;
		
	BYTE reserved[100];
}__PACKED__;
typedef struct _TNetBasePara TNetBasePara;

/*����Ͽ��澯*/
struct _TNetDownAlarm
{
	BYTE bAlarmEnable;/*�ø澯�Ƿ�����*/
	BYTE bAlarmRec;		/*�Ƿ�����¼��*/
	WORD nRecordTime;/*¼��ʱ��*/
	BYTE bAlarmIOOutput;	/*�Ƿ�����IO�������*/
	WORD nIOOutputTime;/*IO�������ʱ��*/
	BYTE reserve[10];
}__PACKED__;
typedef struct _TNetDownAlarm TNetDownAlarm;

/*IP��ͻ�澯*/
struct _TIPClashAlarm
{
	BYTE bAlarmEnable;/*�ø澯�Ƿ�����*/
	BYTE bAlarmRec;		/*�Ƿ�����¼��*/
	WORD nRecordTime;/*¼��ʱ��*/
	BYTE bAlarmIOOutput;	/*�Ƿ�����IO�������*/
	WORD nIOOutputTime;/*IO�������ʱ��*/
	BYTE reserve[10];
}__PACKED__;
typedef struct _TIPClashAlarm TIPClashAlarm;

/*��SD���澯*/
struct _TNoSDAlarm
{
	BYTE bAlarmEnable;/*�ø澯�Ƿ�����*/
	BYTE bAlarmIOOutput;	/*�Ƿ�����IO�������*/
	WORD nIOOutputTime;/*IO�������ʱ��*/
	BYTE reserve[10];
}__PACKED__;
typedef struct _TNoSDAlarm TNoSDAlarm;

/*SD���ռ䲻��澯*/
struct _TSDLackSpaceAlarm
{
	BYTE bAlarmEnable;/*�ø澯�Ƿ�����*/
	BYTE LeastSpacePercent;/*�ռ䱨����ֵ*/
	BYTE bAlarmIOOutput;	/*�Ƿ�����IO�������*/
	WORD nIOOutputTime;/*IO�������ʱ��*/
	BYTE reserve[10];
}__PACKED__;
typedef struct _TSDLackSpaceAlarm TSDLackSpaceAlarm;

/*SD�����ϸ澯*/
struct _TSDErrAlarm
{
	BYTE bAlarmEnable;/*�ø澯�Ƿ�����*/
	BYTE bAlarmIOOutput;	/*�Ƿ�����IO�������*/
	WORD nIOOutputTime;/*IO�������ʱ��*/
	BYTE reserve[10];
}__PACKED__;
typedef struct _TSDErrAlarm TSDErrAlarm;

/*�¼�����--�쳣����*/
struct _TMisAlarmPara
{
	TNetDownAlarm		NetDownAlarm;
	TIPClashAlarm 		IPClashAlarm;
	TNoSDAlarm			NoSDAlarm;
	TSDLackSpaceAlarm	SDLackSpaceAlarm;
	TSDErrAlarm			SDErrAlarm;
	BYTE reserved[100];
}__PACKED__;
typedef struct _TMisAlarmPara TMisAlarmPara;

/*ϵͳ����--��������*/
struct _TSysBasePara
{
	char DeviceName[SERVER_NAME_LEN+1];//SERVER_NAME_LEN=32
	enLanguage	eLanguage;
	enVidStd eVidStd;

	char DevSerial[SERVER_NAME_LEN+1]; // �豸���к�
	BYTE reserved[67];
}__PACKED__;
typedef struct _TSysBasePara TSysBasePara;

/*add lee, 20120727*/
struct _TAudioPara
{
	BYTE bDisableAudio;
	enAudInType eInType;
	enAudEncType eEncType;
	enAudCodeRate eCodeRate;//���ʣ���������
	enAudSampleRate	eAudSampleRate;//������,ֻ֧��8K??
	BYTE cInVol;
	BYTE cOutVol;
	BYTE reserved[20];
}__PACKED__;
typedef struct _TAudioPara TAudioPara;

struct _TComPara
{
	enBaudRate eBaudRate;
	enDataBits eDataBits;
	enStopBits eStopBits;
	enParityCheck eParityCheck;
	enComUseType eComUseType;

	enPTZProtocol ePTZProtocol;
	BYTE cPTZAddr;

	BYTE reserved[40];
}__PACKED__;
typedef struct _TComPara TComPara;

/*��������ץ��	qxs 2013.3.7*/
struct _TComLinkage
{
	BOOL bComLinkage;
	WORD wMotionOutMask;/*�����ʶ*/
	WORD wAlmOutDur;/*���ʱ��*/
	BYTE byProbeAlarmOutChn;/*���ͨ��*/
	enTransducerType eTransducerType;/*����������*/

	/*����ץ��*/
	BOOL bSnapFlag;	/*�Ƿ���Ҫץ��*/
	BYTE bySnapInterval;	/*ץ�ļ��*/
	BYTE bySnapCnt;	/*ץ������*/
	BYTE bySnapSendToFTP;/*ͼƬ�Ƿ���Ҫ���͵�FTP*/
	BYTE bySnapSendToEmail;/*ͼƬ�Ƿ���Ҫ���͵�Email��������*/
	BYTE bySnapSendToSD;/*¼��ʱ�����͵�SD��������*/
	BYTE bySnapSendToCenter;	//����ץ�����͵����� qxs 2013.3.7

	/*����¼��*/
	BOOL bRecFlag;	/*�Ƿ���Ҫ¼��*/
	int nRecordTime;/*¼��ʱ��*/
	BYTE byRecSendToFTP;/*�Ƿ���Ҫ���͵�FTP*/
	BYTE byRecSendToSD;/*¼��ʱ�����͵�SD��������*/

	/*������̨*/
	BOOL bLinkPtzFlag;	/*�Ƿ���Ҫ������̨*/
	BYTE byLinkPtzType;	/*������������, 0:Ԥ�õ㣬1��ɨ�裬2��Ѳ����3���켣*/
	BYTE byLinkPtzValue;/*��ӦԤ�õ��/ɨ����ID/Ѳ��ID/�켣ID��������*/

	BYTE reserved[29];
}__PACKED__;
typedef struct _TComLinkage TComLinkage;

struct _TNetSet
{
	TWiredNetPara 	WiredNetPara;/*�����������*/
	TNetBasePara 	NetBasePara;/*�����������*/
	TNetSmtpSet 	NetSmtpSet;/*�ʼ�*/
	TNetFtpSet		NetFtpSet;/*FTP����*/
	TNetDdnsSet		NetDdnsSet;/*DDNS����*/
	TNetPppoeSet	NetPppoeSet;/*PPPOE����*/
	
}__PACKED__;
typedef struct _TNetSet TNetSet;//��������

/*�����û���Ϣ*/
struct _TOnlineUser           
{     
     char Name[USER_NAME_LEN+1];//�û�����
     char  IpAddr[IPADDR_LEN+1];//iP��ַ
     TTime  loadtime;//�û���¼ʱ��
     char Reserved[5];
}__PACKED__; 
typedef struct _TOnlineUser TOnlineUser;

/*�����û��б�*/
struct _TOnlineUserList
{  
   BYTE  OnlineNum;//�����û���
  TOnlineUser  OnlineUser[MAX_ONLINE_NUM];
}__PACKED__;
typedef struct _TOnlineUserList   TOnlineUserList;

// 0.eStatusType = STATUS_SDʱ
//dwStatus1:0,SD������;1,SD������;2,SD��δ��ʽ��;3,SD���ļ�ϵͳ����;4.SD��ֻ��;5.SD����ʽ���У�6.SD���ļ�ϵͳ�޸���; 7. ������ɣ��ȴ��豸������8.�������ֶ�����
//dwStatus2:��ʹ�ÿռ�(MB);dwStatus3:�ܿ�(MB)
// 1.eStatusType = STATUS_LOGINʱ
//dwStatus1��ʾ��ǰ��¼�û���Ŀ��dwStatus2��ʾ����û�����
// 2.eStatusType = STATUS_UPDATEʱ
//dwStatus1��0���ļ������У�1�������ļ���ɣ�2������������dwStatus2�������룻
//���������ɹ�ʱ��eStatusType = STATUS_UPDATE��dwStatus1=2��dwStatus2=0
// 3.eStatusType = STATUS_FORMAT_DISKʱ
//dwStatus1Ϊtrue��ʾ��ʽ���ɹ���flase��ʾ��ʽ��ʧ�ܣ�
// 4.eStatusType = STATUS_CPU_MEM_INFOʱ
//dwStatus1��CPUռ����*1000��dwStatus2���ڴ�ռ����*1000���磺555Ϊ55.5%
// 5.eStatusType = STATUS_PTZ_TRAJECTORY_INFO
// 6.eStatusType = STATUS_RECORD_DOWN dwStatus1,dwStatus2,dwStatus3��Ϊ0����ʾ���سɹ�
// 7.eStatusType = STATUS_REBOOTʱ 
//dwStatus1:����ԭ��0,����;1,�ֶ�����;2,��ʱ����,3,SD���ָ�;4,SD����ʽ��;5,IP�޸�;6,�ֱ����޸�
// 8.eStatusType = STATUS_REPAIR_DISK_FSʱ
//dwStatus1Ϊ1��ʾSD���޸��ɹ���0��ʾSD���޸�ʧ�ܣ�
//10.eStatusType = STATUS_PTZ_ANGLE_INFOʱ
//dwStatus1 һ������ֵ��ʾĿǰ�����װ����б�Ƕ�
//dwStatus2 һ������ֵ��ʾĿǰ�����ֱ�����PTZ �Ĵ�ֱ�ǶȵĲ�ֵҲ����У׼ֵ
struct  _TSystemStatus
{
	enStatusType enType;	//ϵͳ״̬����
	DWORD dwStatus1;     //״̬һ
	DWORD dwStatus2;     //״̬��
	DWORD dwStatus3;     //״̬��
	BYTE Reserved[16]; 	//�����ֽ�
}__PACKED__;
typedef struct _TSystemStatus  TSystemStatus;

/*added by zengqingfeng 20130202*/
struct _TPtzParam
{
	BYTE bPtzParamValue;/*Ԥ�õ�0~255,ɨ���1-3���켣��1-6��Ѳ����1-7*/
	char chPtzParamName[MAX_OPERATION_NAME_LEN+1];
}__PACKED__;
typedef struct _TPtzParam TPtzParam;

/*added by hy 20140321*/
struct _TNetDiscoverPack
{	
	TWiredNetPara 	WiredNetPara;/*�����������*/

	char		DeviceName[SERVER_NAME_LEN+1];//SERVER_NAME_LEN=32
	char        ProductModel[MAX_PRODUCT_MODEL_LEN+1];//MAX_PRODUCT_MODEL_LEN=32
	WORD        wBiosVer; // BIOS version
	WORD        wNetVer;  // Network protocol version
	WORD		wElecBoardVer;//��ذ�汾
	BYTE		byGB28181Enable;/*GB28181�Ƿ�����,=0:�����ã�=����:����*/
	BYTE		byStorageEnable;/*SD������¼���Ƿ�����,=0:�����ã�=����:����*/
	BYTE        bySdCardState;//SD����װ״̬
	WORD		wCameraVer;//��о�汾
	WORD		wMainMcuVer; // ��MCU�汾
	WORD		wSlaveMcuVer; //��MCU�汾
	char		chBuildDate[10];/*��������:20180926*/
	BYTE		reserved[176-20];
}__PACKED__;
typedef struct _TNetDiscoverPack TNetDiscoverPack;

struct _TNetDiscoverSetPack
{	
	char          LoginName[USER_NAME_LEN+1];	//����ʱ��Ҫ��֤�û���������
	char          LoginPsw[USER_PSW_LEN+1];
	TWiredNetPara 	WiredNetPara;/*�����������*/
	char		DeviceName[SERVER_NAME_LEN+1];
	char        ProductModel[MAX_PRODUCT_MODEL_LEN+1];
	WORD        wBiosVer; // BIOS version
	WORD        wNetVer;  // Network protocol version
}__PACKED__;
typedef struct _TNetDiscoverSetPack TNetDiscoverSetPack;


struct _T3DPtz	//������Ҫ����ΪCIFʹ��,��XС�ڵ���352��YС�ڵ���288
{	
	BYTE	byPtzCtrlType;		//��̨������������
	WORD	wStartPoint_X;		//��ʼ��X����
	WORD	wStartPoint_Y;		//��ʼ��Y����
	WORD	wEndPoint_X;		//������X����
	WORD	wEndPoint_Y;		//������Y����
}__PACKED__;
typedef struct _T3DPtz T3DPtz;

typedef enum
{
	RSCMD_PostMonData        = 80003001, //����ý��������
}enRSNetCmd;

struct _TRSCmdHead
{
	DWORD dwMagicCode; // Always be NETWORK_MAGIC_CODE
	DWORD dwSize;       // Total packet size, including TCmdHead & Cmd Data
	DWORD dwCmdId;      // command id
	WORD wRSType;		//RS����
	WORD wRSCount;		//RS��Ԫ��
	WORD wRSUnitLen;	//RS��Ԫ����
	WORD wGuardStrLen;	//�����ִ�����
	BYTE Reserved[12];
}__PACKED__;
typedef struct _TRSCmdHead TRSCmdHead;


struct _TRDUnit
{
	DWORD dwMagicCode; // GXXR OR GXXD
	BYTE Data[0];
}__PACKED__;
typedef struct _TRDUnit TRDUnit;

struct _TMonCfg
{
	//bit0:1��ʾ֡�����һ��;
	//bit1-3:000��ʾI֡��001��ʾP֡��100��ʾ��Ƶ
	//bit[7:4]������Ĭ��Ϊ0
	BYTE byFlag;	
	BYTE MonBlockType; // enMonBlockType
	WORD VidFrmNum;    // Video frame number that this packet is related to
	DWORD secCapTime;//�ɼ�ʱ�� ���벿��
	DWORD usecCapTime;//�ɼ�ʱ�� ��΢�벿��
	DWORD FrameLen;
}__PACKED__;
typedef struct _TMonCfg TMonCfg;


/*plate detection struct*/
struct _TEventPlatedetection
{
	BYTE byEnable;			    //	1 bytes	�Ƿ����ø��¼�
	WORD wPalateWidthMin;	    //	2 bytes	��С����ʶ����
	WORD wPalateWidthAvg;	    //	2 bytes	ƽ������ʶ����
	WORD wPalateWidthMax;	    //  2 bytes	�����ʶ����
	WORD wRgnX;			//	2 bytes	X����
	WORD wRgnY;			//	2 bytes	Y����
	WORD wRgnW;			//	2 bytes	���
	WORD wRgnH;			//	2 bytes	�߶�

}__PACKED__;/*15bytes*/
typedef struct _TEventPlatedetection TEventPlatedetection;

/****************************************************************************************/
/***********************                                       **************************/
/***********************  Request and Answer Command Structs   **************************/
/***********************                                       **************************/
/****************************************************************************************/

/*�����ȡ���� ����ͨ�ýṹ��*/
struct _TReqGetCMD
{
	TCmdHead head;
}__PACKED__;
typedef struct _TReqGetCMD TReqGetCMD;

/*�ظ����ò��� ����ͨ�ýṹ��*/
struct _TAswSetCMD
{
	TCmdHead head;
	int nResult;
}__PACKED__;
typedef struct _TAswSetCMD TAswSetCMD;





/*�����¼*/
struct _TReqLogin
{
	TCmdHead head;
	WORD wClientNetVer;// Client network protocol version
	char LoginName[USER_NAME_LEN+1];
	char LoginPsw[USER_PSW_LEN+1];
	enMonTranMode eMonTranMode;
	TTime LocalTime;
	WORD wClientUdpPort;// Only valid when eMonTranMode == MTM_UDP.
	BYTE bUdpMakeHole; // when 'bUdpMakeHole' == 1, 'wClientUdpPort' will be ignored by Server.
	int nDisconnectTime;//���߳�ʱʱ�䣬����Ϊ0��ʾĬ��ֵ30000����
	BYTE Reserved[66];
}__PACKED__; // Total 128 bytes
typedef struct _TReqLogin TReqLogin;

/*Ӧ���¼*/
struct _TAswLogin 
{
	TCmdHead head;
	int   nResult;
	// Client original request parameters, <*** 128 bytes, include CmdHead ***>
	WORD          wClientNetVer; // Client network protocol version
	char          LoginName[USER_NAME_LEN+1];
	char          LoginPsw[USER_PSW_LEN+1];
	enMonTranMode eMonTranMode;
	TTime         LocalTime;
	WORD          wClientUdpPort;
	BYTE          bUdpMakeHole;

	BYTE          Reserved1[70];

	// Server answer data, <*** 384 bytes ***>
	TDeviceInfo   DevInfo;
	enUserLevel   eUserLevel;
	DWORD         dwUserPower;
	DWORD         dwUdpMakeHoleID; // This is a unique ID alloc by Server when 'bUdpMakeHole' == 1.
	DWORD         dwUserPowerExt;
	int			  nSockID;			//������·��ý����·���ID

	BYTE          Reserved2[104];

}__PACKED__; // Total 512 bytes
typedef struct _TAswLogin TAswLogin;


/*����ע��*/
struct _TReqLogout
{
	TCmdHead head;
}__PACKED__;
typedef struct _TReqLogout TReqLogout;


/*������*/
struct _TReqMon
{
	TCmdHead head;
	BYTE ChanNum;
	BYTE bStreamType; //0:������1:������2:��Ƶ3:yuv422 4:RGB
	BYTE bOpen;

	enMonTranMode enTranMode;
	BYTE	IP[4];
	/*���ڵ���ʱָ����IP��ַ UDP�����鲥ʱ ���ֽ���ǰ���ֽ��ں�����192.168.30.64
	��ʾΪIP[0]=0xC0; IP[1]=0xA8; IP[2]=0x1E; IP[3]=0x40; 
	*/
	unsigned short nPort; 
	BYTE   Reserved[2];

}__PACKED__;
typedef struct _TReqMon TReqMon;

struct _TAswMon
{
	TCmdHead head;
	int nResult;
	// Client original request parameters
	BYTE ChanNum;
	BYTE bOpen;
	// Server answer data
}__PACKED__;
typedef struct _TAswMon TAswMon;


/*�����ȡ�û��б�*/
struct _TReqGetUserList
{
	TCmdHead head;
}__PACKED__;
typedef struct _TReqGetUserList TReqGetUserList;


/*��ȡ�û��б�Ӧ��*/
struct _TAswGetUserList
{
	TCmdHead head;
	// Server answer data
	int nResult;
	TUserList UserList;
}__PACKED__;
typedef struct _TAswGetUserList TAswGetUserList;

struct _TReqModifyUser
{
	TCmdHead head;
	enModifyUser eModifyType;
	TUser User;
	char  OldPswd[USER_PSW_LEN+1];
}__PACKED__;
typedef struct _TReqModifyUser TReqModifyUser;

struct _TAswModifyUser
{
	TCmdHead head;
	int nResult;
	// Client original request parameters
	enModifyUser eModifyType;
	TUser User;
	char  OldPswd[USER_PSW_LEN+1];
	// Server answer data

}__PACKED__;
typedef struct _TAswModifyUser TAswModifyUser;


/*����ϵͳ��־*/
struct _TReqSysLog
{
	TCmdHead 		head;
	TSysLogFilter	SysLogFilter;
	BYTE reserv[20];
}__PACKED__;
typedef struct _TReqSysLog TReqSysLog;

struct _TAswSysLog
{
	TCmdHead head;
	int nResult;
}__PACKED__;
typedef struct _TAswSysLog TAswSysLog;


/*��̨����*/
struct _TReqPtzAct
{
	TCmdHead head;
	BYTE ChanNum;
	enPtzAction ePtzAct;
	TPtzActParam ActParam;
}__PACKED__;
typedef struct _TReqPtzAct TReqPtzAct;

struct _TAswPtzAct
{
	TCmdHead head;
	int nResult;
	// Client original request parameters
	BYTE ChanNum;
	enPtzAction ePtzAct;
	TPtzActParam ActParam;
	// Server answer data

}__PACKED__;
typedef struct _TAswPtzAct TAswPtzAct;


/*�ֶ��澯*/
struct _TReqManualAlarm
{
	TCmdHead head;
	BYTE ChanNum;
	BYTE bOpen;
}__PACKED__;
typedef struct _TReqManualAlarm TReqManualAlarm;

struct _TAswManualAlarm
{
	TCmdHead head;
	int nResult;
	// Client original request parameters
	BYTE ChanNum;
	BYTE bOpen;
	// Server answer data

}__PACKED__;
typedef struct _TAswManualAlarm TAswManualAlarm;


/*��������*/
struct _TReqUpdateFile
{
	TCmdHead head;
	enUpdateFileType eFileType;
	DWORD dwFileSize;
}__PACKED__;
typedef struct _TReqUpdateFile TReqUpdateFile;

struct _TAswUpdateFile
{
	TCmdHead head;
	int nResult;
	// Client original request parameters
	enUpdateFileType eFileType;
	DWORD dwFileSize;
	// Server answer data

	int nFileID;
}__PACKED__;
typedef struct _TAswUpdateFile TAswUpdateFile;


/*ֹͣ���������ļ�*/
struct _TReqStopPostFile
{
	TCmdHead head;
	int nFileID;
}__PACKED__;
typedef struct _TReqStopPostFile TReqStopPostFile;

struct _TAswStopPostFile
{
	TCmdHead head;
	int nResult;
	// Client original request parameters
	int nFileID;
	// Server answer data

}__PACKED__;
typedef struct _TAswStopPostFile TAswStopPostFile;


/*��ȡ�豸��Ϣ*/
struct _TReqGetDevInfo
{
	TCmdHead head;
}__PACKED__;
typedef struct _TReqGetDevInfo TReqGetDevInfo;

struct _TAswGetDevInfo
{
	TCmdHead head;
	// Server answer data
	int nResult;
	TDeviceInfo DevInfo;
}__PACKED__;
typedef struct _TAswGetDevInfo TAswGetDevInfo;


/*����I֡*/
struct _TReqIFrame
{
	TCmdHead head;
	BYTE ChanNum;
}__PACKED__;
typedef struct _TReqIFrame TReqIFrame;

struct _TAswIFrame
{
	TCmdHead head;
	int nResult;
	// Client original request parameters
	BYTE ChanNum;
	// Server answer data

}__PACKED__;
typedef struct _TAswIFrame TAswIFrame;


/*����SD���ļ�*/
struct _TReqSrchSDFile
{
	TCmdHead head;
	BYTE ChanNumMask; // Channels to search, 1 bit 1 channel
	BYTE bFileTypeMask; /*0x01:picturr file,0x02:rec file*/
	BYTE bFileSubTypeMask;/*0x01:alarm rec/pictur file,0x02:timing rec/pictur file,0x04:manual rec/pictur file*/
	WORD wAlarmTypeMask;/*�澯���ͣ���enAlarmType*/
	TTime BegTime;/*��ѯ��ʼʱ��*/
	TTime EndTime;/*��ѯ����ʱ��*/
}__PACKED__;
typedef struct _TReqSrchSDFile TReqSrchSDFile;

struct _TAswSrchSDFile
{
	TCmdHead head;
	int nResult;
	// Client original request parameters
	BYTE ChanNumMask;
	BYTE bFileTypeMask; /*0x01:picturr file,0x02:rec file*/
	BYTE bFileSubTypeMask;/*0x01:alarm rec/pictur file,0x02:timing rec/pictur file,0x04:manual rec/pictur file*/
	WORD wAlarmTypeMask;/*�澯���ͣ���enAlarmType*/
	TTime BegTime;/*��ѯ��ʼʱ��*/
	TTime EndTime;/*��ѯ����ʱ��*/
}__PACKED__;
typedef struct _TAswSrchSDFile TAswSrchSDFile;


struct _TReqStartPb
{
	TCmdHead head;
	char FilePath[MAX_REC_FILE_PATH+1];
}__PACKED__;
typedef struct _TReqStartPb TReqStartPb;

struct _TAswStartPb
{
	TCmdHead head;
	int nResult;
	// Client original request parameters
	char FilePath[MAX_REC_FILE_PATH+1];
	// Server answer data

	int nPbID;
}__PACKED__;
typedef struct _TAswStartPb TAswStartPb;


struct _TReqSetPbSpeed
{
	TCmdHead head;
	int nPbID;
	enPbSpeed ePbSpeed;
}__PACKED__;
typedef struct _TReqSetPbSpeed TReqSetPbSpeed;

struct _TAswSetPbSpeed
{
	TCmdHead head;
	int nResult;
	// Client original request parameters
	int nPbID;
	enPbSpeed ePbSpeed;
	// Server answer data

}__PACKED__;
typedef struct _TAswSetPbSpeed TAswSetPbSpeed;


struct _TReqStopPb
{
	TCmdHead head;
	int nPbID;
}__PACKED__;
typedef struct _TReqStopPb TReqStopPb;

struct _TAswStopPb
{
	TCmdHead head;
	int nResult;
	// Client original request parameters
	int nPbID;
	// Server answer data

}__PACKED__;
typedef struct _TAswStopPb TAswStopPb;


struct _TReqSetPbPos
{
	TCmdHead head;
	int nPbID;
	int nPos; // Playing Progress: 0 ~ 1000
}__PACKED__;
typedef struct _TReqSetPbPos TReqSetPbPos;

struct _TAswSetPbPos
{
	TCmdHead head;
	int nResult;
	// Client original request parameters
	int nPbID;
	int nPos; // Playing Progress: From 0 ~ 1000
	// Server answer data

}__PACKED__;
typedef struct _TAswSetPbPos TAswSetPbPos;


struct _TReqTalkback
{
	TCmdHead head;
	BYTE bOpen;
}__PACKED__;
typedef struct _TReqTalkback TReqTalkback;

struct _TReqTalkbackEX
{
	TCmdHead head;
	BYTE bOpen;
	enMonTranMode enTranMode;
	BYTE	IP[4];
	/*���ڵ���ʱָ����IP��ַ UDP�����鲥ʱ ���ֽ���ǰ���ֽ��ں�����192.168.30.64
	��ʾΪIP[0]=0xC0; IP[1]=0xA8; IP[2]=0x1E; IP[3]=0x40; 
	*/
	unsigned short nPort; 
	BYTE   Reserved[12];
}__PACKED__;
typedef struct _TReqTalkbackEX TReqTalkbackEX;

struct _TAswTalkback
{
	TCmdHead head;
	int nResult;
	// Client original request parameters
	BYTE bOpen;
	// Server answer data

	TUser Occupier; // When nResult==ERR_EXCLUSIVE_BY_USER, this tell client the occupier info.
}__PACKED__;
typedef struct _TAswTalkback TAswTalkback;



struct _TReqStorageInfo
{
	TCmdHead head;
}__PACKED__;
typedef struct _TReqStorageInfo TReqStorageInfo;

struct _TAswStorageInfo
{
	TCmdHead head;
	int nResult;
	// Server answer data
	BYTE DiskCount;
	TDiskInfo DiskList[1]; // List Count = DiskCount
}__PACKED__;
typedef struct _TAswStorageInfo TAswStorageInfo;
typedef struct _TAswStorageInfo *TAswStorageInfoPtr;


/*sd������*/
struct _TReqDiskMaintain
{
	TCmdHead head;
	char DiskPath[MAX_REC_FILE_PATH+1];
	BYTE MaintainType;//0��������1����ʽ��2���ָ�SD�ļ�ϵͳ����SD��Ч��
}__PACKED__;
typedef struct _TReqDiskMaintain TReqDiskMaintain;

struct _TAswDiskMaintain
{
	TCmdHead head;
	int nResult;
	// Client original request parameters
	char DiskPath[MAX_REC_FILE_PATH+1];
	BYTE MaintainType;//0��������1����ʽ��2���ָ�SD�ļ�ϵͳ����SD��Ч��
	// Server answer data
}__PACKED__;
typedef struct _TAswDiskMaintain TAswDiskMaintain;


struct _TReqSnapshot
{
	TCmdHead head;
	BYTE ChanNum;
}__PACKED__;
typedef struct _TReqSnapshot TReqSnapshot;

struct _TAswSnapshot
{
	TCmdHead head;
	int nResult;
	BYTE ChanNum;
	DWORD dwFileSize;
	// Server answer data

	int nFileID;
}__PACKED__;
typedef struct _TAswSnapshot TAswSnapshot;


/*��ȡ�澯��Ϣ*/
struct _TReqAlarmInfo
{
	TCmdHead head;
}__PACKED__;
typedef struct _TReqAlarmInfo TReqAlarmInfo;

struct _TAswAlarmInfo
{
	TCmdHead head;
	int nResult;
}__PACKED__;
typedef struct _TAswAlarmInfo TAswAlarmInfo;


/*IP����*/
struct _TReqGetIpFilterInfo
{
	TCmdHead head;
}__PACKED__;
typedef struct _TReqGetIpFilterInfo TReqGetIpFilterInfo;

struct _TAswGetIpFilterInfo
{
	TCmdHead head;
	int nResult;
	// Server answer data
	TIpFilterSet stIpFilterCfg;

}__PACKED__;
typedef struct _TAswGetIpFilterInfo TAswGetIpFilterInfo;

struct _TReqSetIpFilterInfo
{
	TCmdHead head;
	TIpFilterSet stIpFilterCfg;
}__PACKED__;
typedef struct _TReqSetIpFilterInfo TReqSetIpFilterInfo;

struct _TAswSetIpFilterInfo
{
	TCmdHead head;
	int nResult;
	// Server answer data
	TIpFilterSet stIpFilterCfg;

}__PACKED__;
typedef struct _TAswSetIpFilterInfo TAswSetIpFilterInfo;


/*��ʱץ��*/
struct _TTimingSnapSet
{
 	BOOL bSnapFlag;	/*�Ƿ���Ҫץ��*/
	BYTE chSnapInterval;	/*ץ�ļ��*/
	BOOL bSendToFTP;/*�Ƿ���Ҫ���͵�FTP*/
	BOOL bSendToEmail;/*�Ƿ���Ҫ���͵�Email*/
	TTimingPlanDaySet stTimingSnapPlanCfg[WEEK_MAX_DAY];
	// Reserved bytes, for future extension
	BYTE Reserved[4];
}__PACKED__; 
typedef struct _TTimingSnapSet T_TimingSnapSet;

struct _TPictureSet
{
	enVideoResolution ePicRes;/*ͼƬ�ֱ���*/
	BYTE bPictureQuality;/*ͼƬ����*/
	T_SnapPictureSet stManualAlarmSnapCfg;	/*�����ֶ���������ץ�����ò���*/
	T_TimingSnapSet  stTimingSnapCfg;/*���Ӷ�ʱץ�����ò���*/

	// Reserved bytes, for future extension
	BYTE Reserved[4];
}__PACKED__; 
typedef struct _TPictureSet TPictureSet;

struct _TReqGetTimingSnapInfo
{
	TCmdHead head;
	BYTE ChanNum;
}__PACKED__;
typedef struct _TReqGetTimingSnapInfo TReqGetTimingSnapInfo;

struct _TAswGetTimingSnapInfo
{
	TCmdHead head;
	int nResult;
	BYTE ChanNum;
	// Server answer data
	T_TimingSnapSet stTimingSnapCfg;
//	TWorkPlanItem stWorkPlan;

}__PACKED__;
typedef struct _TAswGetTimingSnapInfo TAswGetTimingSnapInfo;

struct _TReqSetTimingSnapInfo
{
	TCmdHead head;
	BYTE ChanNum;
	T_TimingSnapSet stTimingSnaCfg;
//	TWorkPlanItem stWorkPlan;
}__PACKED__;
typedef struct _TReqSetTimingSnapInfo TReqSetTimingSnapInfo;

struct _TAswSetTimingSnapInfo
{
	TCmdHead head;
	int nResult;
	BYTE ChanNum;
	// Server answer data
	T_TimingSnapSet stTimingSnapCfg;

}__PACKED__;
typedef struct _TAswSetTimingSnapInfo TAswSetTimingSnapInfo;


/*¼�����*/
struct _TReqGetRecParamInfo
{
	TCmdHead head;
	BYTE ChanNum;
}__PACKED__;
typedef struct _TReqGetRecParamInfo TReqGetRecParamInfo;

struct _TAswGetRecParamInfo
{
	TCmdHead head;
	int nResult;
	BYTE ChanNum;
	// Server answer data
	TRecParamSet stRecParamCfg;

}__PACKED__;
typedef struct _TAswGetRecParamInfo TAswGetRecParamInfo;


/*��ʱ¼��*/
struct _TReqSetRecParamInfo
{
	TCmdHead head;
	BYTE ChanNum;
	TRecParamSet stRecParamCfg;
}__PACKED__;
typedef struct _TReqSetRecParamInfo TReqSetRecParamInfo;

struct _TAswSetRecParamInfo
{
	TCmdHead head;
	int nResult;
	BYTE ChanNum;
	// Server answer data
	TRecParamSet stRecParamCfg;
}__PACKED__;
typedef struct _TAswSetRecParamInfo TAswSetRecParamInfo;

struct _TReqGetNormalRecInfo
{
	TCmdHead head;
	BYTE ChanNum;
}__PACKED__;
typedef struct _TReqGetNormalRecInfo TReqGetNormalRecInfo;

struct _TAswGetNormalRecInfo
{
	TCmdHead head;
	int nResult;
	BYTE ChanNum;
	// Server answer data
	TNormalRecordSet stTRecParamCfg;

}__PACKED__;
typedef struct _TAswGetNormalRecInfo TAswGetNormalRecInfo;

struct _TReqSetNormalRecInfo
{
	TCmdHead head;
	BYTE ChanNum;
	TNormalRecordSet stNormalRecordCfg;
}__PACKED__;
typedef struct _TReqSetNormalRecInfo TReqSetNormalRecInfo;

struct _TAswSetNormalRecInfo
{
	TCmdHead head;
	int nResult;
	BYTE ChanNum;
	// Server answer data
	TNormalRecordSet stNormalRecCfg;

}__PACKED__;
typedef struct _TAswSetNormalRecInfo TAswSetNormalRecInfo;


/*OSD�ַ�����*/
struct _TReqGetOverlayRegionSet       
{
	TCmdHead head;
	BYTE ChanNum;
}__PACKED__;
typedef struct _TReqGetOverlayRegionSet TReqGetOverlayRegionSet;

struct _TAswGetOverlayRegionSet
{
	TCmdHead head;
	int nResult;
	BYTE ChanNum;
	// Server answer data

	TOverlayRegionSet stOverlayRegionCfg[MAX_VIDEO_OVERLAY_REGION];
}__PACKED__;
typedef struct _TAswGetOverlayRegionSet TAswGetOverlayRegionSet;


struct _TReqSetOverlayRegionSet
{
	TCmdHead head;
	BYTE ChanNum;
	TOverlayRegionSet stOverlayRegionCfg[MAX_VIDEO_OVERLAY_REGION];
}__PACKED__;
typedef struct _TReqSetOverlayRegionSet TReqSetOverlayRegionSet;

struct _TAswSetOverlayRegionSet
{
	TCmdHead head;
	int nResult;
	BYTE ChanNum;
	// Client original request parameters
	TOverlayRegionSet stOverlayRegionCfg[MAX_VIDEO_OVERLAY_REGION];

	// Server answer data

}__PACKED__;
typedef struct _TAswSetOverlayRegionSet TAswSetOverlayRegionSet;



/*�ڵ���������*/
struct _TReqGetCoverRegionSet       
{
	TCmdHead head;
	BYTE ChanNum;
}__PACKED__;
typedef struct _TReqGetCoverRegionSet TReqGetCoverRegionSet;

struct _TAswGetCoverRegionSet
{
	TCmdHead head;
	int nResult;
	BYTE ChanNum;
	// Server answer data

	TCoverRegionSet stCoverRegionCfg[MAX_VIDEO_COVER_REGION];
}__PACKED__;
typedef struct _TAswGetCoverRegionSet TAswGetCoverRegionSet;


struct _TReqSetCoverRegionSet
{
	TCmdHead head;
	BYTE ChanNum;
	TCoverRegionSet stCoverRegionCfg[ MAX_VIDEO_COVER_REGION];
}__PACKED__;
typedef struct _TReqSetCoverRegionSet TReqSetCoverRegionSet;

struct _TAswSetCoverRegionSet
{
	TCmdHead head;
	int nResult;
	BYTE ChanNum;
	// Client original request parameters
	TCoverRegionSet stCoverRegionCfg[MAX_VIDEO_COVER_REGION];

	// Server answer data

}__PACKED__;
typedef struct _TAswSetCoverRegionSet TAswSetCoverRegionSet;



/*ͼƬ����*/
struct _TReqGetPictureParamSet       
{
	TCmdHead head;
	BYTE ChanNum;
}__PACKED__;
typedef struct _TReqGetPictureParamSet TReqGetPictureParamSet;

struct _TAswGetPictureParamSet
{
	TCmdHead head;
	int nResult;
	BYTE ChanNum;
	// Server answer data

	enVideoResolution ePicRes;/*ͼƬ�ֱ���*/
	BYTE bPictureQuality;/*ͼƬ����*/
}__PACKED__;
typedef struct _TAswGetPictureParamSet TAswGetPictureParamSet;


struct _TReqSetPictureParamSet
{
	TCmdHead head;
	BYTE ChanNum;
	enVideoResolution ePicRes;/*ͼƬ�ֱ���*/
	BYTE bPictureQuality;/*ͼƬ����*/
}__PACKED__;
typedef struct _TReqSetPictureParamSet TReqSetPictureParamSet;

struct _TAswSetPictureParamSet
{
	TCmdHead head;
	int nResult;
	BYTE ChanNum;
	// Client original request parameters
	enVideoResolution ePicRes;/*ͼƬ�ֱ���*/
	BYTE bPictureQuality;/*ͼƬ����*/
	// Server answer data

}__PACKED__;
typedef struct _TAswSetPictureParamSet TAswSetPictureParamSet;


/*��˽�ڵ��澯*/
struct _TReqGetHideAlarm       
{
	TCmdHead head;
}__PACKED__;
typedef struct _TReqGetHideAlarm  TReqGetHideAlarm;

struct _TAswGetHideAlarm
{
	TCmdHead head;
	int nResult;
	THideAlarmSet stCfg;
}__PACKED__;
typedef struct _TAswGetHideAlarm TAswGetHideAlarm;


struct _TReqSetHideAlarm
{
	TCmdHead head;
	THideAlarmSet stCfg;
}__PACKED__;
typedef struct _TReqSetHideAlarm TReqSetHideAlarm;

struct _TAswSetHideAlarm
{
	TCmdHead head;
	int nResult;
	// Client original request parameters
	THideAlarmSet stCfg;
	// Server answer data

}__PACKED__;
typedef struct _TAswSetHideAlarm TAswSetHideAlarm;


/*�ƶ����*/
struct _TReqGetMotionDetectSet       
{
	TCmdHead head;
	BYTE ChanNum;
}__PACKED__;
typedef struct _TReqGetMotionDetectSet TReqGetMotionDetectSet;

struct _TAswGetMotionDetectSet
{
	TCmdHead head;
	int nResult;
	BYTE ChanNum;
	// Server answer data

	TMotionDetectionSet stMotionDetectionCfg;
	
}__PACKED__;
typedef struct _TAswGetMotionDetectSet TAswGetMotionDetectSet;


struct _TReqSetMotionDetectSet
{
	TCmdHead head;
	BYTE ChanNum;
	TMotionDetectionSet stMotionDetectionCfg;

}__PACKED__;
typedef struct _TReqSetMotionDetectSet TReqSetMotionDetectSet;


struct _TAswSetMotionDetectSet
{
	TCmdHead head;
	int nResult;
	BYTE ChanNum;
	// Client original request parameters
	TMotionDetectionSet stMotionDetectionCfg;
	
	// Server answer data

}__PACKED__;
typedef struct _TAswSetMotionDetectSet TAswSetMotionDetectSet;



/*IO����*/
struct _TReqGetProbeDetectSet       
{
	TCmdHead head;
	BYTE chProbeAlarmInChn;/* ����ͨ��*///qxs 2013.3.6
}__PACKED__;
typedef struct _TReqGetProbeDetectSet TReqGetProbeDetectSet;

struct _TAswGetProbeDetectSet
{
	TCmdHead head;
	int nResult;
	// Server answer data

	TProbeDetectionSet stProbeDetectionCfg;
	
}__PACKED__;
typedef struct _TAswGetProbeDetectSet TAswGetProbeDetectSet;


struct _TReqSetProbeDetectSet
{
	TCmdHead head;

	TProbeDetectionSet stProbeDetectionCfg;
	
}__PACKED__;
typedef struct _TReqSetProbeDetectSet TReqSetProbeDetectSet;

struct _TAswSetProbeDetectSet
{
	TCmdHead head;
	int nResult;
	// Client original request parameters
	TProbeDetectionSet stProbeDetectionCfg;
	
	// Server answer data

}__PACKED__;
typedef struct _TAswSetProbeDetectSet TAswSetProbeDetectSet;


/*added by zengqingfeng 20120721*/
/*SD������*/
struct _TReqGetSDSet       
{
	TCmdHead head;
}__PACKED__;
typedef struct _TReqGetSDSet TReqGetSDSet;

struct _TAswGetSDSet
{
	TCmdHead head;
	// Server answer data
	int nResult;
	TSDSet stSDCfg;
}__PACKED__;
typedef struct _TAswGetSDSet TAswGetSDSet;


struct _TReqSetSDSet
{
	TCmdHead head;
	TSDSet stSDCfg;
}__PACKED__;
typedef struct _TReqSetSDSet TReqSetSDSet;

struct _TAswSetSDSet
{
	TCmdHead head;
	int nResult;
	// Client original request parameters
	TSDSet stSDCfg;
	// Server answer data

}__PACKED__;
typedef struct _TAswSetSDSet TAswSetSDSet;


/*�Զ���������*/
struct _TReqGetAutoRebootSet       
{
	TCmdHead head;
}__PACKED__;
typedef struct _TReqGetAutoRebootSet TReqGetAutoRebootSet;

struct _TAswGetAutoRebootSet
{
	TCmdHead head;
	// Server answer data
	int nResult;
	TAutoRebootSet stAutoRebootCfg;
}__PACKED__;
typedef struct _TAswGetAutoRebootSet TAswGetAutoRebootSet;


struct _TReqSetAutoRebootSet
{
	TCmdHead head;
	TAutoRebootSet stAutoRebootCfg;
}__PACKED__;
typedef struct _TReqSetAutoRebootSet TReqSetAutoRebootSet;

struct _TAswSetAutoRebootSet
{
	TCmdHead head;
	int nResult;
	// Client original request parameters
	TAutoRebootSet stAutoRebootCfg;
	// Server answer data

}__PACKED__;
typedef struct _TAswSetAutoRebootSet TAswSetAutoRebootSet;



/***************************************/ //begin lee
/*��������--FTP����*/
struct _TReqSetNetFtpCfg
{
	TCmdHead head;
	TNetFtpSet NetFtp;
}__PACKED__;
typedef struct _TReqSetNetFtpCfg TReqSetNetFtpCfg;

struct _TAswSetNetFtpCfg
{
		TCmdHead head;
		int nResult;
		TNetFtpSet NetFtp;

}__PACKED__;
typedef struct _TAswSetNetFtpCfg TAswSetNetFtpCfg;


struct _TReqGetNetFtpCfg
{
	TCmdHead head;
}__PACKED__;
typedef struct _TReqGetNetFtpCfg TReqGetNetFtpCfg;

struct _TAswGetNetFtpCfg
{
		TCmdHead head;
		int nResult;
		TNetFtpSet NetFtp;
}__PACKED__;
typedef struct _TAswGetNetFtpCfg TAswGetNetFtpCfg;


/*��������--�ʼ�*/
struct _TReqSetNetSmtpCfg
{
	TCmdHead head;
	TNetSmtpSet NetSmtp;
}__PACKED__;
typedef struct _TReqSetNetSmtpCfg TReqSetNetSmtpCfg;

struct _TAswSetNetSmtpCfg
{
		TCmdHead head;
		int nResult;
		TNetSmtpSet NetSmtp;
}__PACKED__;
typedef struct _TAswSetNetSmtpCfg TAswSetNetSmtpCfg;

struct _TReqGetNetSmtpCfg
{
	TCmdHead head;
}__PACKED__;
typedef struct _TReqGetNetSmtpCfg TReqGetNetSmtpCfg;

struct _TAswGetNetSmtpCfg
{
		TCmdHead head;
		int nResult;
		TNetSmtpSet NetSmtp;
}__PACKED__;
typedef struct _TAswGetNetSmtpCfg TAswGetNetSmtpCfg;



/*��������--DDNS����*/
struct _TReqSetNetDdnsCfg
{
	TCmdHead head;
	TNetDdnsSet stNetDdns;
}__PACKED__;
typedef struct _TReqSetNetDdnsCfg TReqSetNetDdnsCfg;

struct _TAswSetNetDdnsCfg
{
		TCmdHead head;
		int nResult;
		TNetDdnsSet stNetDdns;

}__PACKED__;
typedef struct _TAswSetNetDdnsCfg TAswSetNetDdnsCfg;

struct _TReqGetNetDdnsCfg
{
	TCmdHead head;
}__PACKED__;
typedef struct _TReqGetNetDdnsCfg TReqGetNetDdnsCfg;

struct _TAswGetNetDdnsCfg
{
		TCmdHead head;
		int nResult;
		TNetDdnsSet stNetDdns;
}__PACKED__;
typedef struct _TAswGetNetDdnsCfg TAswGetNetDdnsCfg;



/*��������--PPPOE ����*/
struct _TReqSetNetPppoeCfg
{
	TCmdHead head;
	TNetPppoeSet stNetPppoe;
}__PACKED__;
typedef struct _TReqSetNetPppoeCfg TReqSetNetPppoeCfg;

struct _TAswSetNetPppoeCfg
{
		TCmdHead head;
		int nResult;
		TNetPppoeSet stNetPppoe;

}__PACKED__;
typedef struct _TAswSetNetPppoeCfg TAswSetNetPppoeCfg;


struct _TReqGetNetPppoeCfg
{
	TCmdHead head;
}__PACKED__;
typedef struct _TReqGetNetPppoeCfg TReqGetNetPppoeCfg;

struct _TAswGetNetPppoeCfg
{
		TCmdHead head;
		int nResult;
		TNetPppoeSet stNetPppoe;
}__PACKED__;
typedef struct _TAswGetNetPppoeCfg TAswGetNetPppoeCfg;


/*ϵͳ����--ʱ������*/
struct _TReqSetSysTimeSet
{
	TCmdHead head;
	TTimeSet TimeSet;
}__PACKED__;
typedef struct _TReqSetSysTimeSet TReqSetSysTimeSet;

struct _TAswSetSysTimeSet
{
	TCmdHead head;
	// Server answer data
	int nResult;
}__PACKED__;
typedef struct _TAswSetSysTimeSet TAswSetSysTimeSet;


struct _TReqGetSysTimeSet
{
	TCmdHead head;
}__PACKED__;
typedef struct _TReqGetSysTimeSet TReqGetSysTimeSet;

struct _TAswGetSysTimeSet
{
	TCmdHead head;
	// Server answer data
	int nResult;
	TTimeSet TimeSet;
}__PACKED__;
typedef struct _TAswGetSysTimeSet TAswGetSysTimeSet;


/*��Ƶ����*/
struct _TReqSetAudioPara
{
	TCmdHead head;
	TAudioPara	AudioPara;
}__PACKED__;
typedef struct _TReqSetAudioPara TReqSetAudioPara;

struct _TAswSetAudioPara
{
	TCmdHead head;
	// Server answer data
	int nResult;
}__PACKED__;
typedef struct _TAswSetAudioPara TAswSetAudioPara;


struct _TReqGetAudioPara
{
	TCmdHead head;
}__PACKED__;
typedef struct _TReqGetAudioPara TReqGetAudioPara;

struct _TAswGetAudioPara
{
	TCmdHead head;
	// Server answer data
	int nResult;
	TAudioPara AudioPara;
}__PACKED__;
typedef struct _TAswGetAudioPara TAswGetAudioPara;


/*���ڲ���*/
struct _TReqSetComPara
{
	TCmdHead head;
	BYTE	ComNum;//0:COM1;Ŀǰֻ�õ�COM1
	TComPara ComPara;
}__PACKED__;
typedef struct _TReqSetComPara TReqSetComPara;

struct _TAswSetComPara
{
	TCmdHead head;
	// Server answer data
	int nResult;
	BYTE ComNum;
}__PACKED__;
typedef struct _TAswSetComPara TAswSetComPara;


struct _TReqGetComPara
{
	TCmdHead head;
	BYTE	ComNum;//0:COM1;Ŀǰֻ�õ�COM1
}__PACKED__;
typedef struct _TReqGetComPara TReqGetComPara;

struct _TAswGetComPara
{
	TCmdHead head;
	// Server answer data
	int nResult;
	BYTE ComNum;
	TComPara ComPara;
}__PACKED__;
typedef struct _TAswGetComPara TAswGetComPara;


//������������	qxs 2013.3.6
struct _TReqSetComLinkage
{
	TCmdHead head;
	BYTE byComNum;//0:COM1;Ŀǰֻ�õ�COM1
	TComLinkage ComLinkage;
}__PACKED__;
typedef struct _TReqSetComLinkage TReqSetComLinkage;

struct _TAswSetComLinkage
{
	TCmdHead head;
	// Server answer data
	int nResult;
	BYTE byComNum;
}__PACKED__;
typedef struct _TAswSetComLinkage TAswSetComLinkage;

struct _TReqGetComLinkage
{
	TCmdHead head;
	BYTE	byComNum;//0:COM1;Ŀǰֻ�õ�COM1
}__PACKED__;
typedef struct _TReqGetComLinkage TReqGetComLinkage;

struct _TAswGetComLinkage
{
	TCmdHead head;
	// Server answer data
	int nResult;
	BYTE byComNum;
	TComLinkage ComLinkage;
}__PACKED__;
typedef struct _TAswGetComLinkage TAswGetComLinkage;


/*��������--�����������*/
struct _TReqSetWiredNetPara
{
	TCmdHead head;
	TWiredNetPara WiredNetPara;
}__PACKED__;
typedef struct _TReqSetWiredNetPara TReqSetWiredNetPara;

struct _TAswSetWiredNetPara
{
	TCmdHead head;
	int nResult;
}__PACKED__;
typedef struct _TAswSetWiredNetPara TAswSetWiredNetPara;

struct _TReqGetWiredNetPara
{
	TCmdHead head;
}__PACKED__;
typedef struct _TReqGetWiredNetPara TReqGetWiredNetPara;

struct _TAswGetWiredNetPara
{
	TCmdHead head;
	int nResult;
	TWiredNetPara WiredNetPara;	
}__PACKED__;
typedef struct _TAswGetWiredNetPara TAswGetWiredNetPara;


/*��������--��������*/
struct _TReqSetNetBasePara
{
	TCmdHead head;
	TNetBasePara NetBasePara;
}__PACKED__;
typedef struct _TReqSetNetBasePara TReqSetNetBasePara;

struct _TAswSetNetBasePara
{
	TCmdHead head;
	int nResult;
	BOOL bNeedRebootToApplay;//�Ƿ���Ҫ����
}__PACKED__;
typedef struct _TAswSetNetBasePara TAswSetNetBasePara;

struct _TReqGetNetBasePara
{
	TCmdHead head;
}__PACKED__;
typedef struct _TReqGetNetBasePara TReqGetNetBasePara;

struct _TAswGetNetBasePara
{
	TCmdHead head;
	int nResult;
	TNetBasePara NetBasePara;	
}__PACKED__;
typedef struct _TAswGetNetBasePara TAswGetNetBasePara;


/*�¼�����--�쳣����*/
struct _TReqSetMisAlarmPara
{
	TCmdHead head;
	TMisAlarmPara MisAlarmPara;
}__PACKED__;
typedef struct _TReqSetMisAlarmPara TReqSetMisAlarmPara;

struct _TAswSetMisAlarmPara
{
	TCmdHead head;
	int nResult;
}__PACKED__;
typedef struct _TAswSetMisAlarmPara TAswSetMisAlarmPara;

struct _TReqGetMisAlarmPara
{
	TCmdHead head;
}__PACKED__;
typedef struct _TReqGetMisAlarmPara TReqGetMisAlarmPara;

struct _TAswGetMisAlarmPara
{
	TCmdHead head;
	int nResult;
	TMisAlarmPara MisAlarmPara;
}__PACKED__;
typedef struct _TAswGetMisAlarmPara TAswGetMisAlarmPara;


/*ϵͳ����--��������*/
struct _TReqSetSysBasePara
{
	TCmdHead head;
	TSysBasePara SysBasePara;
}__PACKED__;
typedef struct _TReqSetSysBasePara TReqSetSysBasePara;

struct _TAswSetSysBasePara
{
	TCmdHead head;
	int nResult;
	BOOL bNeedRebootToApplay;//�Ƿ���Ҫ����
}__PACKED__;
typedef struct _TAswSetSysBasePara TAswSetSysBasePara;

struct _TReqGetSysBasePara
{
	TCmdHead head;
}__PACKED__;
typedef struct _TReqGetSysBasePara TReqGetSysBasePara;

struct _TAswGetSysBasePara
{
	TCmdHead head;
	int nResult;
	TSysBasePara SysBasePara;
}__PACKED__;
typedef struct _TAswGetSysBasePara TAswGetSysBasePara;


/*���ϵͳ��־*/
struct _TReqDelSysLog
{
	TCmdHead head;
	BYTE Reserve[60];
}__PACKED__;
typedef struct _TReqDelSysLog TReqDelSysLog;

struct _TAswDelSysLog
{
	TCmdHead head;
	int nResult;
}__PACKED__;
typedef struct _TAswDelSysLog TAswDelSysLog;
/***************************************/ //end lee


/*�ָ�Ĭ��ֵ*/
struct _TReqSetDefaultParam
{
	TCmdHead head;
	BYTE ChanNum;//ͨ����
	enDefaultParamType eDefaultParamCfg;
}__PACKED__;
typedef struct _TReqSetDefaultParam TReqSetDefaultParam;

struct _TAswSetDefaultParam
{
	TCmdHead head;
	int nResult;
	BYTE ChanNum;
	enDefaultParamType eDefaultParamCfg;
	BOOL bNeedRebootToApplay;//�Ƿ���Ҫ����
}__PACKED__;
typedef struct _TAswSetDefaultParam TAswSetDefaultParam;
/*added by zengqingfeng 20120815*/


/*��ȡ�����û��б�*/
struct _TReqGetOnlineUserList
{
    TCmdHead head;
}__PACKED__;
typedef struct _TReqGetOnlineUserList TReqGetOnlineUserList;

struct _TAswGetOnlineUserList     //Ӧ��ṹ��
{
	TCmdHead  head;
    int nResult;
    TOnlineUserList  OnlineUserList;
	
}__PACKED__;
typedef struct _TAswGetOnlineUserList TAswGetOnlineUserList;

/***********added by zengqingfeng 20121013*************/
struct _TReqDownloadFile
{
	TCmdHead head;
	char FilePath[MAX_DOWNLOAD_FILE_PATH+1];
}__PACKED__;
typedef struct _TReqDownloadFile TReqDownloadFile;

struct _TAswDownloadFile
{
	TCmdHead head;
	int nResult;
	// Client original request parameters
	char FilePath[MAX_DOWNLOAD_FILE_PATH+1];
	// Server answer data

	int nDownloadFileID;
}__PACKED__;
typedef struct _TAswDownloadFile TAswDownloadFile;
/***********added by zengqingfeng 20121013*************/


/*��ȡϵͳ״̬*/
struct _TReqGetSystemStatus
{
	TCmdHead head;
}__PACKED__;
typedef struct _TReqGetSystemStatus TReqGetSystemStatus;

struct _TAswGetSystemStatus
{
	TCmdHead head;
	int nResult;
}__PACKED__;
typedef struct _TAswGetSystemStatus TAswGetSystemStatus;


/*����ptz����*/
struct _TReqSetPtzPara
{
	TCmdHead head;
	BYTE bDeviceType;/*�豸����*/
	BYTE bParamNum;/*������Ŀ*/
	BYTE bPtzParamType;/*0:Ԥ�õ㣬1��ɨ�裬2��Ѳ����3���켣*/
	TPtzParam stPtzParam;
}__PACKED__;
typedef struct _TReqSetPtzPara TReqSetPtzPara;

struct _TAswSetPtzPara
{
	TCmdHead head;
	int nResult;
	BYTE bDeviceType;/*�豸����*/
	BYTE bParamNum;/*������Ŀ*/

}__PACKED__;
typedef struct _TAswSetPtzPara TAswSetPtzPara;


/*����28181����*/
struct _TReqSetGB28181Set	//qxs 2013.3.11
{
	TCmdHead head;
	BYTE byXmlStr[1];
}__PACKED__;
typedef struct _TReqSetGB28181Set TReqSetGB28181Set;

struct _TAswSetGB28181Set	//qxs 2013.3.11
{
	TCmdHead head;
	int nResult;
	BYTE byXmlStr[1];
}__PACKED__;
typedef struct _TAswSetGB28181Set TAswSetGB28181Set;

struct _TReqGetGB28181Set	//qxs 2013.3.11
{
	TCmdHead head;
	BYTE byXmlStr[1];
}__PACKED__;
typedef struct _TReqGetGB28181Set TReqGetGB28181Set;

struct _TAswGetGB28181Set	//qxs 2013.3.11
{
	TCmdHead head;
	int nResult;
	BYTE byXmlStr[1];
}__PACKED__;
typedef struct _TAswGetGB28181Set TAswGetGB28181Set;


/*�����豸*/
struct _TReqFindDev		//qxs 2013.3.21
{
	TCmdHead head;
}__PACKED__;
typedef struct _TReqFindDev TReqFindDev;

struct _TAswFindDev	//qxs 2013.3.11
{
	TCmdHead head;
	int nResult;
	TNetDiscoverPack stNetDisPack;
}__PACKED__;
typedef struct _TAswFindDev TAswFindDev;


/*�����������*/
struct _TReqSetDevNet	//qxs 2013.3.21
{
	TCmdHead head;
	TNetDiscoverSetPack    NetDiscoverSetPack;
}__PACKED__;
typedef struct _TReqSetDevNet TReqSetDevNet;

struct _TAswSetDevNet	//qxs 2013.3.11
{
	TCmdHead head;
	int nResult;
	char NetMAC[NET_MAC_LEN+1];
}__PACKED__;
typedef struct _TAswSetDevNet TAswSetDevNet;


/*��������*/
struct _TReqTestCmd		//qxs 2013.4.27
{
	TCmdHead head;
	char byXmlStr[0];
}__PACKED__;
typedef struct _TReqTestCmd TReqTestCmd;

struct _TAswTestCmd		//qxs 2013.4.27
{
	TCmdHead head;
	int nResult;
	char byXmlStr[0];
}__PACKED__;
typedef struct _TAswTestCmd TAswTestCmd;


struct _TAswGetBallMachineCfg
{
	TCmdHead head;
	int nResult;// 4.19�޸�Э�������
	BYTE bDevType;/*�豸����*/
	char chData[256];
}__PACKED__;
typedef struct _TAswGetBallMachineCfg TAswGetBallMachineCfg;

struct _TAswGetIPdomeCfg
{
	TCmdHead head;
	int nResult;// 4.19�޸�Э�������
	BYTE bDevType;/*�豸����*/
	char chData[0];
}__PACKED__;
typedef struct _TAswGetIPdomeCfg TAswGetIPdomeCfg;


struct _TAswMonSub
{
	TCmdHead head;
	int nResult;
	// Client original request parameters
	BYTE ChanNum;
	BYTE bOpen;
	// Server answer data

}__PACKED__;
typedef struct _TAswMonSub TAswMonSub;


typedef enum
{
	SNAP_TYPE_AUTO	= 1,	/*�Զ�*/
	SNAP_TYPE_MANUAL	= 0,	/*�ֶ�*/
	SNAP_YPE_ONESHOT = 2	/*һ��*/
} SNAP_OP_TYPE_E;

struct _TSnapOrSetSnapSet
{
	BYTE 		ucOperFlag;/*0�������������ȡ��1������ץ�ģ�2��ץ�Ŀ��ǲ���*/
	BOOL 		bSnapFlag;	/*���� 0�رգ�1��������Ĭ��1*/
	BYTE		ucManualFlag;/*0:��ץ�ģ�1���ֶ�����ץ�� Ĭ��0*/
	BYTE		ucAutoGainMode;/*�Զ�����ģʽ0�رգ�1���� Ĭ��1*/
	BYTE  	ucAutoGainVal;/*�Զ���������[0-36] Ĭ��16dB*/
	BYTE  	ucManualGainVal;/*�ֶ���������[0-36] Ĭ��16dB*/
	SNAP_OP_TYPE_E		eExposureMode;/*�Զ��ع�0���ر�  1���� Ĭ��1����*/
	UINT 		uiManualSpeed;/*�ֶ��ع�ʱ��[0-80000] ��λ1us Ĭ��40000*/
	UINT 		uiAutoSpeed;/*�Զ��ع�����[0-80000]��λ1usĬ��40000*/
	BYTE		ucFlashEnable;/*�����ʹ�� 0�ر� 1���� Ĭ��1����*/
	unsigned short	usFlashDaley;/*����Ʋ�����ʱ[0-65535] Ĭ��0  Na�룿*/
	BYTE		ucConFramCount;/*����ץ��֡��[1-3] Ĭ��1*/
	BYTE		ucIntvFramCount;/*ץ�ļ��֡��*/
	BYTE		ucDealFlag;/*0��������1:��ʾ��ǰץ�����ܷ������*/
	BOOL 		bSendToFTP;/*�Ƿ���Ҫ���͵�FTP*/
	BOOL 		bSendToEmail;/*�Ƿ���Ҫ���͵�Email*/
	BOOL 		bSaveToSD;/*�Ƿ���Ҫ���浽SD��*/
	BOOL 		bSendToCenter;/*�Ƿ���Ҫ���͵�����ͨ������*/
	UINT		uiCoilDistance;/*��Ȧ����*///FIX ME zhangyt add 2012-12-21
	BYTE 		Reserved[21-4];//FIX ME zhangyt update 2012-12-21

}__PACKED__; //��64���ֽ�
typedef struct _TSnapOrSetSnapSet TSnapOrSetSnapSet; 

struct _TReqGetSnapOrSetSnapSet
{
	TCmdHead head;
	BYTE ChanNum;
}__PACKED__;
typedef struct _TReqGetSnapOrSetSnapSet TReqGetSnapOrSetSnapCfg;

struct _TReqSnapOrSetSnapSet
{
	TCmdHead head;
	BYTE ChanNum;
	TSnapOrSetSnapSet stSnapOrSetSnapCfg;
}__PACKED__;
typedef struct _TReqSnapOrSetSnapSet TReqSnapOrSetSnapCfg;

struct _TAswSnapOrSetSnapSet
{
	TCmdHead head;
	int nResult;
	TSnapOrSetSnapSet stSnapOrSetSnapCfg;

}__PACKED__;
typedef struct _TAswSnapOrSetSnapSet TAswSnapOrSetSnapSet; 

struct _TAswGetSpecialSnapSet
{
	TCmdHead head;
	int nResult;
	TSnapOrSetSnapSet stSnapOrSetSnapCfg;
}__PACKED__;
typedef struct _TAswGetSpecialSnapSet TAswGetSpecialSnapSet;



/********************************************
*********         ��ǿ��ʵ        **********
*********************************************/

/*Yoto add 2014-08-28  for ��ǿ��ʵ����У׼*/
struct _TReqCorrectPos
{
	TCmdHead 	head;
	int			nOperType;
}__PACKED__;
typedef struct _TReqCorrectPos TReqCorrectPos;

struct _TAswCorrectPos
{
	TCmdHead head;
	int nResult;
}__PACKED__;
typedef struct _TAswCorrectPos TAswCorrectPos;

/*��ǿ��ʵsei��Ϣ*/
struct _TReqSetXml
{
	TCmdHead head;
	BYTE byXmlStr[1];
}__PACKED__;
typedef struct _TReqSetXml TReqSetXml;

struct _TAswSetXml
{
	TCmdHead head;
	int nResult;
	BYTE byXmlStr[1];
}__PACKED__;
typedef struct _TAswSetXml TAswSetXml;

/*�ı�����Э��*/
struct _TReqSetIni
{
	TCmdHead head;
	DWORD 	  dwOper;// 1���� 2��ȡ
	DWORD    dwFileId;// 1����2 �澯3 ����������4 �ٶ� 5Ѳ���ű� 6 ��Ʒ����
	BYTE byIniStr[1];
}__PACKED__;
typedef struct _TReqSetIni TReqSetIni;

struct _TAswSetIni
{
	TCmdHead head;
	DWORD 	  dwOper;// 1���� 2��ȡ
	DWORD    dwFileId;//  1����2 �澯3 ����������4 �ٶ� 5Ѳ���ű� 6 ��Ʒ����
	int nResult;
	BYTE byIniStr[1];
}__PACKED__;
typedef struct _TAswSetIni TAswSetIni;
/********************************************
***********        4G�豸        ***********
*********************************************/

/*4G���߲������úͻ�ȡ*/
struct _TWirelessCfg
{	
	int          nEnable;	//��������ģ���ܿ���
	int          nStreamType; //������
	char 	     chApn[32];//APN�����
	unsigned char  ucConnetMode;//����ģʽ
	unsigned char  ucConnetorder;//����˳��
	char        chCenterIP[17];//���ķ�����IP
	int         nServerPort; // ���ķ������˿�
	int        nCheck;  // У�鷽ʽ
}__PACKED__;
typedef struct _TWirelessCfg TWirelessCfg;

struct _TReqSetWirelessCfg
{
	TCmdHead head;
	TWirelessCfg stWirelessCfg;
}__PACKED__;
typedef struct _TReqSetWirelessCfg TReqSetWirelessCfg;

struct _TAswSetWirelessCfg
{
	TCmdHead head;
	int nResult;
}__PACKED__;
typedef struct _TAswSetWirelessCfg TAswSetWirelessCfg;

struct _TReqGetWirelessCfg
{
	TCmdHead head;
}__PACKED__;
typedef struct _TReqSetWirelessCfg TReqSetirelessCfg;

struct _TAswGetWirelessCfg
{
	TCmdHead head;
	int nResult;
	TWirelessCfg stWirelessCfg;
	char chWirelessIP[17];
}__PACKED__;
typedef struct _TAswGetWirelessCfg TAswGetWirelessCfg;


/********************************************
***********        �����豸        *********
*********************************************/

/*������λ��������*/
struct _TBdLocationInfo
{
	char chCenterName[33];//���ĵر�����
	BYTE byEW;//1������2����
	BYTE bySN;// 1��γ��2��γ
	UINT unLongitude;//���� ��λ�ȣ�ʵ������*1000000
	UINT unLatitude;//γ�� ��λ�ȣ�ʵ������*1000000
	BYTE byReserved[21];//�����ֽ�
}__PACKED__;

typedef struct _TBdLocationInfo TBdLocationInfo;

struct _TReqGetBdParam
{
	TCmdHead head;
}__PACKED__;
typedef struct _TReqGetBdParam TReqGetBdParam;

struct _TAswGetBdParam
{
	TCmdHead head;
	int nResult;
	TBdLocationInfo stBdParam;
}__PACKED__;
typedef struct _TAswGetBdParam TAswGetBdParam;


struct _TReqSetBdParam
{
	TCmdHead head;
	TBdLocationInfo stBdParam;
}__PACKED__;
typedef struct _TReqSetBdParam TReqSetBdParam;

struct _TAswSetBdParam
{
	TCmdHead head;
	int nResult;
}__PACKED__;
typedef struct _TAswSetBdParam TAswSetBdParam;




/********************************************
***********       �����豸       ***********
*********************************************/

/*����ʶ����������ȡ*/
struct _TReqTrafficPlateCodeSet
{
	TCmdHead head;
	BYTE byOperateType;
	char acText[10];
}__PACKED__;
typedef struct _TReqTrafficPlateCodeSet TReqTrafficPlateCodeSet;

struct _TAswTrafficPlateCodeSet     
{
	TCmdHead head;
	int nResult;
}__PACKED__;
typedef struct _TAswTrafficPlateCodeSet TAswTrafficPlateCodeSet; 

struct _TReqTrafficPlateCodeGet
{
	TCmdHead head;
}__PACKED__;
typedef struct _TReqTrafficPlateCodeGet TReqTrafficPlateCodeGet;

struct _TAswTrafficPlateCodeGet
{
	TCmdHead head;
	int nResult;
	WORD nNum;
	char pData[0];
}__PACKED__;
typedef struct _TAswTrafficPlateCodeGet TAswTrafficPlateCodeGet;


/*ץ�ļ�¼��ѯ*/
struct _TReqSnapRecordGet
{
	TCmdHead head;
	BYTE           bySnapFlag;          //ͼƬץ�ı�־��0��ʾֹͣ��ѯ��1��ʾ��ʼ��ѯ 
	long long      nStartTime;          //ͼƬץ�Ŀ�ʼʱ�䣬��λ��
	long long      nStopTime;           //ͼƬץ�Ľ���ʱ�䣬��λ��
	BYTE           bySnapType;          //ͼƬץ�����ͣ�0��ʾ��ͨͼƬ��1��ʾ����ʶ��
	BYTE           SnapContext[128];    //����ͼƬץ�Ĳ�ͬ�����в�ͬ������
}__PACKED__;
typedef struct _TReqSnapRecordGet TReqSnapRecordGet;

struct _TAswSnapRecordGet
{
	TCmdHead head;
	int nResult;
	int nRecordTotelNum;//��ѯ����ͼƬץ�ļ�¼������ 
}__PACKED__;
typedef struct _TAswSnapRecordGet TAswSnapRecordGet;

struct _TReqSnapStorageGet
{
	TCmdHead head;
	unsigned int   sec;                 //ץ��ʱ�� ��λ��
	unsigned int   usec;                //ץ��ʱ�� ��λ΢��
	BYTE           bySnapType;          //ͼƬץ�����ͣ�0��ʾ��ͨͼƬ��1��ʾ����ʶ��
}__PACKED__;
typedef struct _TReqSnapStorageGet TReqSnapStorageGet;

struct _TAswSnapStorageGet
{
	TCmdHead head;
	int nResult;
	int nSnapTotelNum;//�ļ��ܰ���
}__PACKED__;
typedef struct _TAswSnapStorageGet TAswSnapStorageGet;



/********************************************
***********       P2PС��        ***********
*********************************************/

/*����С��wifi�����Ļ�ȡ������*/
struct _TWIFISet
{
	BYTE 	bEnable;/*0�����ã�1������*/
	char    chRouterName [33];
	char	chPassword[33];/* */
	int		nConnectStatus;
	int		nSignalStrength;
	int  	nIPMode;/* */
	char  	chIPAdr[17];/* */
	char	chIPMask[17];
	char	chGateWay[17];
}__PACKED__; //��130���ֽ�
typedef struct _TWIFISet TWIFISet;

struct _TReqWIFISet
{
	TCmdHead head;
	TWIFISet stWIFICfg;
}__PACKED__;
typedef struct _TReqWIFISet TReqSetWIFICfg;

struct _TAswWIFISet      
{
	TCmdHead head;
	int nResult;
	TWIFISet stWIFICfg;
}__PACKED__;
typedef struct _TAswWIFISet TAswWIFISet;

/*·�����б�Ļ�ȡ*/
struct _TRouterList
{
	char chRouterName[33];
	enEncryMode eEncryMode;
	int nSignalStrength;
}__PACKED__;
typedef struct _TRouterList TRouterList;


struct _TAswGetRouterList
{
	TCmdHead  head;
	int nResult;
	BYTE  nListNum;/*�б�������*/
	BYTE  byRouterData[0];
}__PACKED__;
typedef struct _TAswGetRouterList TAswGetRouterList;


/*�ƻ�¼���������*/
struct _TRecPlanSet
{
	BYTE 	bEnable;/*0�����ã�1������*/
	BYTE	chRecTime[42];/*ÿ6���ֽڴ���1��*/
}__PACKED__; //��43���ֽ�
typedef struct _TRecPlanSet TRecPlanSet; 

struct _TReqRecPlanSet
{
	TCmdHead head;
	TRecPlanSet stRecPlanCfg;
}__PACKED__;
typedef struct _TReqRecPlanSet TReqRecPlanSet;

struct _TAswRecPlanSet
{
	TCmdHead head;
	int nResult;
	TRecPlanSet stRecPlanCfg;
}__PACKED__;
typedef struct _TAswRecPlanSet TAswRecPlanSet;


/********************************************
***********       Ͳ���豸       ***********
*********************************************/
struct _TLensParam
{
	TCmdHead head;
	BYTE bType;//���ò������ͣ�1��ʾ���þ�ͷ��ʼ����2��ʾ����һ���۽�
	BYTE Reserved[63];
}__PACKED__;
typedef struct _TLensParam TLensParam;

/****************************************************************************************/
/***********************                                       **************************/
/***********************         Post Packet Structs           **************************/
/***********************                                       **************************/
/****************************************************************************************/

#define PACKET_DATA_PART_LEN(pack)    ((pack).head.wSize - sizeof((pack)) + 1)
//add lee,20120724
struct _TPostSysLog
{
	TCmdHead head;
	int nResult;
	BYTE PackNum;	//��ǰ�����
	BYTE bLastPack;//�Ƿ����һ��
	int nSysLogNum;//Ӧ�������־��Ŀ
	BYTE SysLogData[1];//���ݰ���"_TSysLog"��ʽ�洢
}__PACKED__;
typedef struct _TPostSysLog TPostSysLog;
typedef struct _TPostSysLog *TPostSysLogPtr;


struct _TPostMonData
{
	TCmdHead head;
	//bit0:1��ʾ֡�����һ��;
	//bit1-3:000��ʾI֡��001��ʾP֡��100��ʾ��Ƶ
	//bit[7:4]������Ĭ��Ϊ0
	BYTE byFlag;	
	BYTE MonBlockType; // enMonBlockType
	WORD VidFrmNum;    // Video frame number that this packet is related to
	DWORD secCapTime;//�ɼ�ʱ�� ���벿��
	DWORD usecCapTime;//�ɼ�ʱ�� ��΢�벿��

	BYTE MonData[1];   // Monitor video data, length = PACKET_DATA_PART_LEN()
}__PACKED__;

typedef struct _TPostMonData TPostMonData;
typedef struct _TPostMonData *TPostMonDataPtr;


//add lee alarminfo
struct _TPostAlarmInfo
{
	TCmdHead head;
	BYTE ChanNum;
	BYTE AlarmInNum;
	enAlarmType eAlarmType;
	TTime	Time;
	// Reserved bytes, for future extension
	BYTE Reserved[26];
}__PACKED__;
typedef struct _TPostAlarmInfo TPostAlarmInfo;


struct _TPostFileData
{
	TCmdHead head;
	int nFileID;
	BYTE FileData[1];   // File data, length = PACKET_DATA_PART_LEN()
}__PACKED__;
typedef struct _TPostFileData TPostFileData;
typedef struct _TPostFileData *TPostFileDataPtr;

struct _TPostSrchSDFile
{
	TCmdHead head;
	int nFileCnt;/*�ܵĸ���*/
	int nCurrentCnt;/*��ǰ�����һ����¼�����*/
	TRecFileInfo FileList[1];
}__PACKED__;
typedef struct _TPostSrchSDFile TPostSrchSDFile;
typedef struct _TPostSrchSDFile *TPostSearchSDFilePtr;

struct _TPostPbData
{
	TCmdHead head;
	int nPbID;
	DWORD dwVidFrmNum;  // Video frame number that this packet is related to
	BYTE PbData[1];   // Playback data, length = PACKET_DATA_PART_LEN()
}__PACKED__;
typedef struct _TPostPbData TPostPbData;
typedef struct _TPostPbData *TPostPbDataPtr;

struct _TPostPbProg
{
	TCmdHead head;
	int nPbID;
	int nPlayingTime; // Current Playing Time, Unit: second
	int nProgress; // Playing Progress: From 0 ~ 1000
}__PACKED__;
typedef struct _TPostPbProg TPostPbProg;
typedef struct _TPostPbProg *TPostPbProgPtr;

struct _TPostVoiceUpData
{
	TCmdHead head;
	BYTE VoiceData[1];   // Talkback voice data, length = PACKET_DATA_PART_LEN()
}__PACKED__;
typedef struct _TPostVoiceUpData TPostVoiceUpData;

struct _TPostVoiceDownData
{
	TCmdHead head;
	BYTE VoiceData[1];   // Talkback voice data, length = PACKET_DATA_PART_LEN()
}__PACKED__;
typedef struct _TPostVoiceDownData TPostVoiceDownData;
typedef struct _TPostVoiceDownData *TPostVoiceDownDataPtr;


struct _TPostDynChangeSet
{
	TCmdHead head;
	BYTE ChanNum;
	TDynChangeSet DynChangeSet;
}__PACKED__;
typedef struct _TPostDynChangeSet TPostDynChangeSet;


struct _TPostSystemStatus
{
	TCmdHead head;
	TSystemStatus tStatus;
}__PACKED__;
typedef struct _TPostSystemStatus TPostSystemStatus;


/***********added by zengqingfeng 20121013*************/
struct _TPostDownloadFileData
{
	TCmdHead head;
	int nDownloadFileID;/*�����ļ���ID*/
	char FilePath[MAX_DOWNLOAD_FILE_PATH+1];/*�����ļ�������*/
	BYTE bPackNum;	/*��ǰ�����*/
	BYTE bTotalPack;/*�ܵİ���*/
	BYTE DownloadFileData[1];   // Playback data, length = PACKET_DATA_PART_LEN()
}__PACKED__;
typedef struct _TPostDownloadFileData TPostDownloadFileData;
typedef struct _TPostDownloadFileData *TPostDownloadFileDataPtr;
/***********added by zengqingfeng 20121013*************/

struct _TPostIntelligentanalysisInfo
{
	TCmdHead head;
	unsigned char Data[MAX_ANALY_SYSINFO_LEN];
}__PACKED__;
typedef struct _TPostIntelligentanalysisInfo TPostIntelligentanalysisInfo;//FIX ME zhangyt add 2012-12-19


struct _TPostStreamHeartbeat
{
	TCmdHead head;
	int nCmdSockID;				//����SOCKET��ID����½�豸ʱ����
}__PACKED__;
typedef struct _TPostStreamHeartbeat TPostStreamHeartbeat;

/***********start added by zhangyt 2014-05-21********************/
struct _TClientDevInfo
{
	BYTE	ucCSQType;//15:3G  17:4G
	BYTE	ucCSQValue;
	BYTE 	ucConStatus;// 1:δע��2:������;3:�������� ��Ϊ��������״̬ ���Ǻ����ĵ�ͨ��״̬
	BYTE 	ucModeStatus;// 0�ɹ� 1ʧ��
	char		cDevSerial[32];

}__PACKED__;
typedef struct _TClientDevInfo TClientDevInfo;

struct _TPostClientDevInfo
{
	TCmdHead head;
	TClientDevInfo stClientDevInfo;
}__PACKED__;
typedef struct _TPostClientDevInfo TPostClientDevInfo;
/***********end added by zhangyt 2014-05-21********************/


/*4G����״̬����*/
struct _TWirelessStatus
{
	int nSingnalType;
	int nSingnalSize;
	int nConnetStatus;
	char chreserver[16];
}__PACKED__;
typedef struct _TWirelessStatus TWirelessStatus;

struct _TPostWirelessStatus
{
	TCmdHead head;
	TWirelessStatus stStatus;
}__PACKED__;
typedef struct _TPostWirelessStatus TPostWirelessStatus;


/*gps�������ͽṹ��*/
struct _TGpsInfoUpSend
{
	BYTE  byValid;//��λ��־:0��Ч,1��Ч
	BYTE  byEW;//1������2����
	BYTE  bySN;// 1��γ��2��γ
	UINT  unLongitude;//���� ��λ�ȣ�ʵ������*1000000
	UINT  unLatitude;//γ�� ��λ�ȣ�ʵ������*1000000
	int   nASL;//����	��λ�ף�ʵ������*100
	UINT  unSpeed;//�ٶ�	��λkm/h��ʵ������*1000
	TTime sTime; //ʱ��
	BYTE byReserved[38];//�����ֽ�
}__PACKED__;
typedef struct _TGpsInfoUpSend TGpsInfoUpSend;

struct _TPostGpsInfo
{
	TCmdHead head;
	TGpsInfoUpSend	tInfo;
}__PACKED__;
typedef struct _TPostGpsInfo TPostGpsInfo;


/*ץ��ʱ������*/
struct _TPostSnapContextBase
{
	unsigned int sec;               //ץ��ʱ�� ��λ��
	unsigned int usec;              //ץ��ʱ�� ��λ΢��
}__PACKED__;
typedef struct _TPostSnapContextBase  TPostSnapContextBase;

struct _TPostSnapContextPlate
{
	unsigned int sec;               //ץ��ʱ�� ��λ��
	unsigned int usec;              //ץ��ʱ�� ��λ΢��
    BYTE    nPlateNum;              //������
	BYTE    acPlateCode[3][10];     //���ƺ���
}__PACKED__;
typedef struct _TPostSnapContextPlate  TPostSnapContextPlate;
typedef struct _TPostSnapContextPlate *TPostSnapContextPlatePtr;
	
struct _TPostSnapData
{
	TCmdHead head;
	int nSnapType;          //�ļ�����   0��ʾ��ͨͼƬ 1��ʾ����ͼƬ 2...
	int nSnapSuffix;        //�ļ���׺�� 1��ʾjpeg 2��ʾpng 3...
	int nSnapTotelNum;      //�ļ��ܰ���
	int nSnapCurNum;        //�ļ���ǰ����
	BYTE SnapContext[128];  //���ݲ�ͬ�����в�ͬ������
	BYTE SnapData[0];       // File data
}__PACKED__;
typedef struct _TPostSnapData TPostSnapData;

/*wifi״̬����*/
struct _TPostWIFIStatus
{
	TCmdHead head;
	int nSignalStrength;//�ź�ǿ��
	int nConnectStatus;//����״̬
	BYTE Reserved[16];//����
}__PACKED__;
typedef struct _TPostWIFIStatus TPostWIFIStatus;

#if defined(WIN32)
	#pragma pack()
#endif
struct _TSetDetectArea
{
	TCmdHead head;
	TEventMotiondetection detectArea;
	int nDetectMin ;
	int nDetectMax ;
}__PACKED__;
typedef struct _TSetDetectArea TSetDetectArea;

struct _TGetDetectArea
{
	TCmdHead head;
	int   nResult;
	TEventMotiondetection detectArea;
	int nDetectMin ;
	int nDetectMax ;

}__PACKED__; // Total 512 bytes
typedef struct _TGetDetectArea TGetDetectArea;

// Telnet ����״̬   2015.7.7
struct _TSetTelnetStatus
{
	TCmdHead head;
	BYTE   byopen;              // 0:�ر�  1:����
	BYTE   byReserved[3];
}__PACKED__;
typedef struct _TSetTelnetStatus TSetTelnetStatus;

struct _TGetTelnetStatus
{
	TCmdHead head;
	int   nResult;
	BYTE   byopen;
	BYTE   byReserved[3];
}__PACKED__; 
typedef struct _TGetTelnetStatus TGetTelnetStatus;


struct _TGetCenterServer
{
	TCmdHead head;
	char DeviceSerial[DEVICE_SERIAL_LEN+1];//���кţ�DEVICE_SERIAL_LEN=16
	char IpAddr[IP_ADDR_LEN+1];//IP_ADDR_LEN=15
    int  IpPort;
	BYTE reserved[100];
}__PACKED__;
typedef struct _TGetCenterServer TGetCenterServer;

struct _TSetCenterServer
{
	TCmdHead head;
	char DeviceSerial[DEVICE_SERIAL_LEN+1];//���кţ�DEVICE_SERIAL_LEN=16
	char IpAddr[IP_ADDR_LEN+1];//IP_ADDR_LEN=15
    int  IpPort;
	BYTE reserved[100];
}__PACKED__;
typedef struct _TSetCenterServer TSetCenterServer;

struct _TSetAISwitchEnable
{
    TCmdHead head;
    unsigned char bFDEnable; //������⿪��
    BYTE reserved[100];
}__PACKED__;
typedef struct _TSetAISwitchEnable TSetAISwitchEnable;



//���á���ȡ������Ѳ��·������
struct _TReqRobotRouteDetailSet
{
	TCmdHead head;
	unsigned int u8RouteID; //��Χ0�� 3
	unsigned int unXunBiaoID[50];
	unsigned int u32NearChargingPointID;
	unsigned int u32ChargingPointID;
}__PACKED__;
typedef struct _TReqRobotRouteDetailSet TReqRobotRouteDetailSet;

//���������Ѳ��·������ṹ��
struct _TReqRobotRouteDetailGet
{
	TCmdHead head;
	unsigned int u8RouteID; //��Χ0�� 3
}__PACKED__;
typedef struct _TReqRobotRouteDetailGet TReqRobotRouteDetailGet;

struct _TAswRobotRouteDetailGet
{
	TCmdHead head;
	int   nResult;
	unsigned int u8RouteID; //��Χ0�� 3
	unsigned int unXunBiaoID[50];
	unsigned int u32NearChargingPointID;
	unsigned int u32ChargingPointID;
}__PACKED__;
typedef struct _TAswRobotRouteDetailGet TAswRobotRouteDetailGet;

struct _TPostXinBiaoArrival
{
	TCmdHead head;
	char szData[100];
	unsigned char u8Flag; // 1-���룻0-�뿪
}__PACKED__;
typedef struct _TPostXinBiaoArrival TPostXinBiaoArrival;

struct _TGuomaiDeviceInfo
{
	char deviceID[32];   // �豸ID
	char password[32];    // ע��ƽ̨������(̫��ƽ̨�Ŀ���Ա6λ�����)
	char name[128];			// ���Ƴ���
	char deviceName[256]; // �豸����
	char serialNumber[256]; // �豸����
}__PACKED__;
typedef struct _TGuomaiDeviceInfo TGuomaiDeviceInfo;

struct _TPostGuomaiDeviceInfo
{
	TCmdHead head;
	TGuomaiDeviceInfo devinfo;
}__PACKED__;
typedef struct _TPostGuomaiDeviceInfo TPostGuomaiDeviceInfo;

struct _TGuomaiGps
{
	char deviceID[32];   // �豸ID
	char time[64];         // GPS����ʱ��
	char divisionEW[64];   // E-������,W-������
	char longitude[64];    // ����
	char divisionNS[64];   // N-������,S-�ϰ���
	char latitude[64];     // γ��
	char direction[64];    // ����
	char speed[64];        // �ٶ�
	int radius;           //��������
	int battery;          //�������ٷֱȣ�1-100����
	int signal;           //�ź�ǿ�ȣ�1-100��
}__PACKED__;
typedef struct _TGuomaiGps TGuomaiGps;

struct _TPostGuomaiGps
{
	TCmdHead head;
	TGuomaiGps gps;
}__PACKED__;
typedef struct _TPostGuomaiGps TPostGuomaiGps;


typedef struct _TGuomaiSOS
{
	int nPicType;//0:BMP  1:JPEG
	int nPicSize;
	char cData[0];//预留1M空间
}__PACKED__;
typedef struct _TGuomaiSOS TGuomaiSOS;
struct _TPostGuomaiSOS
{
	TCmdHead head;
	TGuomaiSOS SOS;
}__PACKED__;

typedef struct _TPostGuomaiSOS TPostGuomaiSOS;


struct _TGuomaiDevStateInfo
{	
	int nOperator;			//��Ӫ��1:�ƶ� 2:��ͨ 3:����	
	int nNetType;			//0-1 ��;  2:2G  3:3G�� 4:4G	
	int nSignal;			//�ź�ǿ�� 0-100    0���ź� 100���
	int nBattery;			//������Ϣ �ٷֱ�0-100
}__PACKED__;
typedef struct _TGuomaiDevStateInfo TGuomaiDevStateInfo;

struct _TPostGuomaiDevStateInfo
{
	TCmdHead head;
	TGuomaiDevStateInfo DevStateInfo;
}__PACKED__;

typedef struct _TPostGuomaiDevStateInfo TPostGuomaiDevStateInfo;
struct _TGetAIServerStatus
{
    TCmdHead head;
    int nVidStream; //��Ƶ��״̬: 0���� 1�쳣
    int nCenterLink; //��������״̬: 0���� 1�쳣
    BYTE reserved[100];
}__PACKED__;
typedef struct _TGetAIServerStatus TGetAIServerStatus;
struct _TReqRobotParamSetGet
{
	TCmdHead 		head;
	int				nSn;	//�����Ӧ���
	char			creserved[12];//Ԥ���ֶ�
	unsigned int 	unRobotCmd;//�������������ID
	char			cData[0];//�����˶�Ӧ����ؽṹ��
}__PACKED__;
typedef struct _TReqRobotParamSetGet TReqRobotParamSetGet;


struct _TAswRobotParamSetGet
{
	TCmdHead 		head;
	int				nResult;//Ӧ���־
	int				nSn;	//�����Ӧ���
	char			creserved[12];//Ԥ���ֶ�
	unsigned int 	unRobotCmd;//�������������ID
	char			cData[0];//�����˶�Ӧ����ؽṹ��
}__PACKED__;
typedef struct _TAswRobotParamSetGet TAswRobotParamSetGet;

struct _TPushOnRobotInfo //��������
{
	TCmdHead 		head;
	unsigned int 	unRobotCmd;//�������������ID
	char			cData[0];//�����˶�Ӧ����ؽṹ��
}__PACKED__;
typedef struct _TPushOnRobotInfo TPushOnRobotInfo;


struct _TPushDownRobotInfo //�����·�
{
	TCmdHead 		head;
	unsigned int 	unRobotCmd;//�������������ID
	char			cData[0];//�����˶�Ӧ����ؽṹ��
}__PACKED__;
typedef struct _TPushDownRobotInfo TPushDownRobotInfo;




struct _TReqWifiConnStatus
{
    TCmdHead head;
    unsigned char status; // 0��ʾ�Ͽ��� 1��ʾ����
    BYTE reserved[100];
}__PACKED__;
typedef struct _TReqWifiConnStatus TReqWifiConnStatus;
//#ifdef __cplusplus
//} // End of extern "C" block
//#endif // __cplusplus



struct _TPosSerialCmd
{
    TCmdHead head;
    BYTE buf[0];
}__PACKED__;
typedef struct _TPosSerialCmd TPosSerialCmd;


#endif //__NET_PROTOCOL_H__
