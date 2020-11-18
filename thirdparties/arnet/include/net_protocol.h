//////////////////////////////////////////////////////////////////////////////////////////
/*******************************   NETWORK PROTOCOL    **********************************/
//////////////////////////////////////////////////////////////////////////////////////////


/******************************* 说明 **********************************************
  1)  客户端发给服务端的每一个请求命令，服务端都会返回一个应答结果，除了注销命令以外。
  2)  没有正常登录而向服务端发送命令，服务端不会返回任何应答，除了请求登录及查询设备
      信息命令以外。
  3)  服务端返回的应答结果中包含了客户端的请求命令参数与及处理结果。
***********************************************************************************/

/******************************* 缩略词 ********************************************
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
#define MAX_TRANSPACK_SIZE         	(8192*128) //网络包最大长度 8192*4
#define SERVER_TCP_PORT            	36666        //TCP连接端口
#define SERVER_STREAM_TCP_PORT  36667        //码流TCP连接端口
#define CLIENT_UDP_PORT            	36668        //客户端UDP端口
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
#define MAX_AlARMTYPE_NUM			4//报警类型的数量			

#define MAX_VIDEO_OVERLAY_REGION  8  /*最大的视频OSD叠加区域added by zengqingfeng 20120607*/
#define MAX_VIDEO_COVER_REGION  8	/*最大的视频遮挡区域added by zengqingfeng 20120607*/
#define MAX_MOTION_DETECT_REGION  8	/*最大的移动侦测区域added by zengqingfeng 20120612*/
#define MAX_IP_FILTER_LIST   20/*最大ip时段added by zengqingfeng 20120704*/
#define ALLOW_ACCESS		1	/*允许当前ip访问设备*/
#define NOT_ALLOW_ACCESS		0	/*不允许当前ip访问设备*/
#define MAX_SNAP_PLAN_PER_DAY	6	/*最大定时抓拍时段为6个added by zengqingfeng 2012706*/
#define MAX_RECORD_PLAN_PER_DAY	6	/*最大定时录像时段为6个added by zengqingfeng 20120706*/
#define MAX_DIGITAL_WATERMASK_CONTENT_LEN		16/*数字水印字符长度added by zengqingfeng 20120801*/
#define SYS_LOG_MSG_LEN_MAX		70 /*系统日志 信息长度add lee,syslog*/
#define MAX_COM_NUM				1/*串口数量*/
//#define CLIENT_CONNECT_NUM_MAX	10/*客户端最大连接数*/
#define ALARM_REC_TIME_MIN		20/*告警联动录像最小时间*/
#define ALARM_REC_TIME_MAX		300/*告警联动录像最大时间*/
#define ALARM_OUTPUT_TIME_MIN		10/*告警联动输出最小时间*/
#define ALARM_OUTPUT_TIME_MAX		300/*告警联动输出最大时间*/
#define ALARM_SNAP_INTERVAL_MIN		1/*告警联动抓拍最小间隔*/
#define ALARM_SNAP_INTERVAL_MAX		5/*告警联动抓拍最大间隔*/
#define ALARM_SNAP_CNT_MIN		1/*告警联动抓拍最小张数*/
#define ALARM_SNAP_CNT_MAX		10/*告警联动抓拍最大张数*/
#define ALARM_DEBOUNCE_TIME_MIN		1/*告警去抖动最小时间*/
#define ALARM_DEBOUNCE_TIME_MAX		100/*告警去抖动最大时间*/
#define PRE_POINT_NAME_LEN		32/*预置点名称长度*/
#define PRE_POINT_NUM_MAX		256/*预置点数目*/
#define NET_MAC_LEN				17/*MAC 00:26:C5:01:02:03*/
#define NTP_SERVER_ADD_LEN		32/*NTP服务器地址长度*/
#define NTP_SERVER_PORT_DEFAULT	123/*NTP服务器默认端口 123*/
#define FTP_SERVER_PORT_DEFAULT	21/*FTP服务器默认端口 21*/
#define SMTP_SERVER_PORT_DEFAULT	25/*SMTP服务器默认端口 25*/
#define MVDDNS_DDNS_SERVER_PORT_DEFAULT		30000/*mvddns.net DDNS服务器默认端口 30000*/
#define PUBYUN_DDNS_SERVER_PORT_DEFAULT		80/*pubyun.com DDNS服务器默认端口 80*/
#define MAX_ONLINE_NUM	                     10 /*最大在线用户数量*/
#define MAX_DOWNLOAD_FILE_PATH          64/*最大下载文件的路径长度*/
#define MAX_ANALY_SYSINFO_LEN  128 //FIX ME zhangyt add 2012-12-19

#define MAX_OPERATION_NAME_LEN 16
#define MAX_TWO_SCAN	3
#define MAX_TRAJECTORY		4
#define MAX_CRUISE	4

//公共错误码
typedef enum		
{
	STATUS_SUCCESS_WAIT_RESULT=  2,//请求成功，等待操作结果
	STATUS_SUCCESS_REBOOT     =  1,//操作成功，设备正在重启
	ERR_SUCCESS               =  0,//操作成功，即刻生效。
	ERR_UNKNOWN               = -1,//未知错误
	ERR_REACH_MAX_CLIENT_CNN  = -2,//达到最大客户端连接数
	ERR_INVALID_USER          = -3,//无效用户
	ERR_INVALID_PSWD          = -4,//无效密码
	ERR_NO_POWER              = -5,//没有权限
	ERR_INVALID_CHAN_NUM      = -6,//无效通道号
	ERR_USER_LIST_FULL        = -7,//达到最大用户数
	ERR_USER_IS_EXISTENT      = -8,//用户已存在
	ERR_USER_IS_NOT_EXISTENT  = -9,//用户不存在
	ERR_INVALID_PARAMETER     = -10,//无效参数
	ERR_REACH_MAX_DOWNLOAD    = -11,//达到最大下载数
	ERR_OPEN_FILE_FAILED      = -12,//打开文件错误
	ERR_EXCLUSIVE_BY_USER     = -13,//已被其他用户占用
	ERR_CHAN_IS_NOT_OPEN      = -14,//通道没有打开
	ERR_FILE_SIZE_OVERFLOW    = -15,//文件过大
	ERR_INVALID_FILE_TYPE     = -16,//非法文件类型
	ERR_NOT_SUPPORT_STORAGE   = -17,//不支持存储
	ERR_NOT_PLUG_STORAGE      = -18,//未找到存储设备
	ERR_RESOURCE_INSUFFICIENT = -19,//资源不足
	ERR_INVALID_FILE_SIZE     = -20,//无效文件长度
	ERR_INVALID_FILE_HEAD     = -21,//无效文件头
	ERR_USER_ALREADY_LOGIN    = -22,//用户已登录
	ERR_NOT_ENOUGH_MEMORY     = -23,//存储空间不足
	ERR_INVALID_UPDATE_TYPE   = -24,//无效更新类型
	ERR_INVALID_PRODUCT_MODEL = -25,//无效产品型号
	ERR_INVALID_SW_VERSION    = -26,//无效软件版本
	ERR_CONNECT_TIMEOUT       = -27,//连接超时
	ERR_INVALID_USER_OR_PSWD  = -28,//用户名或密码错误
	ERR_OPERATION_IS_BUSY     = -29,//操作太频繁
	ERR_INVALID_FILE_PATH     = -30,//无效文件路径
	ERR_OSD_CAN_NOT_OVERLAY   = -31,//OSD无法叠加
	ERR_NOT_ALLOW_ACCESS      = -32,//不允许访问
	ERR_OSD_OVERLAY_FAILED    = -33,//OSD叠加失败
	ERR_DELETE_USER_ONLINE    = -34,//无法删除在线用户
	ERR_COVER_REGION_FAILED   = -35,//遮挡区域错误
	ERR_FORMAT_SD_FAILED	=-36,//格式化SD卡失败
	ERR_CMD_OUT_TIME  =-37,//控制命令超时
	ERR_IN_UPDATE = -38 ,//正在升级
	ERR_UPDATE_FALSE = -39,//升级失败
	ERR_OPERATION_FALSE = -40,//操作失败
	ERR_INVALID_IP_ADDR = -41,//IP地址不合法
	ERR_INVALID_NET_MASK = -42,//子网掩码不合法
	ERR_INVALID_GATEWAY = -43,//默认网关不合法
	ERR_INVALID_DNS_FIRST = -44,//首选DNS不合法
	ERR_INVALID_DNS_SECOND = -45,//备用DNS不合法
	ERR_NOT_IN_SAME_NET = -46,//IP地址、默认网关不在同一网段
	ERR_OPERATION_AFTER_REBOOT_DEV = -47,//重启设备后，再进行操作
	ERR_OVER_MAX = -48,//超出最大设置个数
	ERR_NOT_SUPPORT = -49,//命令不合法
	ERR_INVALID_LoginID = -50,//无效的登录ID
	ERR_NO_ELECBOARD = -51,//与电控板断开连接
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
	AUDENC_G711A,        /* G.711 A率*/
    AUDENC_G711Mu,       /* G.711 Mu率*/
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
	ALMTYPE_LOST          = 0x01,/*视频丢失*/
	ALMTYPE_MOTION        = 0x02,/*移动侦测告警*/
	ALMTYPE_PROBE         = 0x04, /*IO告警*/
	ALMTYPE_MANUAL        = 0x08, /*手动报警*/

	//add lee,alarminfo 
	ALMTYPE_NET_DOWN	  = 0X0010,//网络断开
	ALMTYPE_IP_CLASH	  = 0X0020,//IP地址冲突
	ALMTYPE_SD_NON		  = 0X0040,//无SD卡
	ALMTYPE_SD_LACK_SPACE = 0X0080,//SD卡空间不足
	ALMTYPE_SD_ERR		  = 0X0100,//SD卡故障

	ALMTYPE_HIDEALARM	  = 0X0200,//遮挡告警

	ALMTYPE_PANCHK_FAIL	  = 0X0400,//球机水平自检告警
	ALMTYPE_TILTCHK_FAIL  = 0X0800,//球机垂直自检告警

	ALMTYPE_RECONN_SUCC     = 0X1000,//重连成功
	ALMTYPE_RECONN_FAIL     = 0X2000,//重连失败

	ALMTYPE_MODCOMM_ERR	  = 0X4000,//机芯通信失败
	ALMTYPE_TRAFFIC       = 0x8000,//智能交通
	ALMTYPE_PLATE         = 0x10000,//车牌识别
}enAlarmType;

typedef enum
{
	FILE_TYPE_PICTURE          = 0x01,/*抓拍图片文件*/
	FILE_TYPE_RECORD        = 0x02,/*录像文件*/
	
}enFileType;

typedef enum
{
	FILE_SUBTYPE_ALARM        = 0x01,/*告警联动抓拍或者录像文件*/
	FILE_SUBTYPE_TIMING	=0X02,/*定时录像或者定时抓拍文件*/	
	FILE_SUBTYPE_MANUAL          = 0x04,/*手动抓拍或者录像文件*/
	
}enFileSubType;

typedef enum
{
	BITRATE_CONSTANT,
	BITRATE_VARIABLE
}enBitRateMode;

typedef enum
{
	VR_1   = 0x01,	//第一种分辨率
	VR_2   = 0x02,	//第二种分辨率
	VR_3   = 0x04,	//第三种分辨率
	VR_4   = 0x08,	//第四种分辨率
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
	WPT_TIMING_SNAP 	= 0X80,/*增加定时抓拍added by zengqingfeng 20120629*/
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
	PTZ_ZOOM_WIDE_START,//视角变宽，也就是变倍小
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
	PTZ_AUTO_SCAN_PRESET,   //预置位自动巡视

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
	SP_FOCUS = 1,/*聚焦*/
	SP_HR = 2,/*水平镜向*/
	SP_BRIGHT = 3,/*亮度*/
	SP_SATUATION = 4,/*饱和度*/
	SP_SHARPNESS = 5,/*锐度*/
	SP_BACKLIGHT_COMPENRATION_VALUE = 6,/*背光补偿值*/
	SP_WHITEBALANCE_AEMODE = 7,/*白平衡模式*/
	SP_WHITEBALANCE_RGAIN = 8,/*R增益*/
	SP_WHITEBALANCE_BGAIN = 9 , /*B增益*/
	SP_ZOOM = 10,/*变倍*/
	SP_ZOOM_SPEED = 11,/*变倍速度*/
	SP_BACKLIGHT_COMPENRATION = 12,/*背光补偿*/
	SP_DAY_NIGHT_CHANGE = 13,/*日夜切换模式*/
	SP_WIDEDYNAMIC = 14, /*宽动态*/

	SP_SHUTTER_MODEL= 15,/*曝光模式*/
	SP_ELECTRONIC_SHUTTER = 16,/*电子快慢门*/
	SP_IRIS_VALUE = 17,/*光圈值*/

	SP_AUTO_GAIN = 20,/*自动增益*/
	SP_FREEZE_FRAME = 21,/*图像冻结*/
	SP_HORIZONTAL_SCAN = 22,/*水平扫描*/
	SP_HORIZONTAL_SCAN_SPEED = 23,/*水平扫描速度*/
	SP_RESET = 24,/*球机重启*/
	SP_INFRARED_CTL = 25,/*红外灯控制*/
	SP_5DEGREE_VERTICAL_NEGATIVE = 26,/*垂直负5度*/
	SP_DAY_NIGHT_CHANGE_SENSITIVITY = 27,/*日夜切换灵敏度*/
	SP_ZC_RESET = 28,/*机芯复位*/
	SP_KEEP_WATCH_WAITTIME = 29,/*守望*/
	SP_KEEP_WATCH_TYPE = 30,/*守望类型设置*/
	SP_KEEP_WATCH_START = 31,/*守望开始 停止*/

	SP_TWO_SCANING_START = 32,/*两点线扫-运行*/
	SP_TWO_SCANING_ORIGIN= 33,/*两点线扫-起点*/
	SP_TWO_SCANING_TERMINAL = 34,/*两点线扫-终点*/
	SP_TWO_SCANING_SPEED = 35,/*两点线扫-速度保存*/
	SP_TWO_SCANING_READ = 36,/*两点线扫-读取*/
	SP_TWO_SCANING_DEL = 37,/*两点线扫-删除*/
	SP_ALL_DEFAULT = 38,/*恢复出厂默认参数*/
	SP_AUTO_SCAN_PRESET = 39,   /*扫面16个预置点*/
	SP_TRAJECTORY_START_TRANSCRIBE = 40,/*轨迹-开始录制*/
	SP_TRAJECTORY_STOP_TRANSCRIBE = 41,/*轨迹-停止录制*/
	SP_TRAJECTORY_START = 42,/*轨迹-开始运行*/
	SP_TRAJECTORY_STOP = 43,/*轨迹-停止运行*/
	SP_TRAJECTORY_DELETE = 44,/*轨迹-删除*/
	SP_TRAJECTORY_READ= 45,/*轨迹-读取*/
	SP_CRUISE_READ_NUM = 46,/*巡航扫描-读取条数*/
	SP_CRUISE_READ_CONTENT = 47,/*巡航扫描-读取某条的内容*/
	SP_POWER_OFF_MEMORY_ONOFF = 48,/*断电记忆-打开/关闭*/
	SP_READ_POINT_PARAM = 49,/*读取预置点设置信息*/

	SP_SHUTTER_TYPE = 50,/*慢快门*/
	SP_SHUTTER_SPEED = 51,/*快门速度*/
	SP_APERTURE_VALUE = 52,/*光圈值*/
	SP_MANUAL_CRLSPEED = 53,/*手动控制最高速度*/
	SP_POWERON_ACTION = 54,/*上电动作*/
	SP_AUTOFLIP = 55,/*自动翻转*/
	SP_FOCUS_NEARLIMIT = 56,/*聚焦近限*/
	SP_UPDATEPACK_INFO = 57,/*设计包信息*/
	SP_UPDATEPACK_DATA = 58,/*设计包数据*/
	SP_VERTICAL_FLIP = 59,/*垂直镜像*/
	SP_3DPTZ = 60,// 3D定位
	SP_FOCUS_POSITON = 61,/*聚焦位置*/

	SP_VIDEO_FORMAT = 62,/*视频格式*/
	SP_OSD_OPERATION = 63,/*OSD操作*/
	SP_SWITCH_HIDE = 64,/*隐私遮挡开关*/
	SP_EDIT_HIDE = 65,/*隐私遮挡编辑*/
	SP_CHANGE_HIDE = 66,/*隐私遮挡大小改变*/
	SP_RECSTATUS_TRAJECTORY = 67,/*轨迹记录状态*/
	SP_TITLE_DISPLAY = 68,/*标题显示信息*/
	SP_EXTERNAL_485_ADDRESS = 69,/*外部485参数地址*/
	SP_EXTERNAL_485_BAUDRATE = 70,/*外部485参数波特率*/
	SP_EXTERNAL_485_PROTOCOL = 72,/*外部485参数协议*/

	SP_CRUISE_READ_SEND_DATA = 71,/*巡航扫描-准备发送数据*/
	SP_CRUISE_SEND_DATA = 73,/*巡航扫描-发送数据*/
	SP_CRUISE_STOP_SEND_DATA = 75,/*巡航扫描-结束发送数据*/
	SP_CRUISE_DELETE = 77,/*巡航扫描-删除*/
	SP_CRUISE_START = 79,/*巡航扫描-开始*/
	SP_CRUISE_STOP = 81,/*巡航扫描-停止*/

	SP_CHROMA = 80,/*色度*/
	SP_DELFOG = 86,/*透雾*/
	SP_DELFOGCLASS = 87,/*透雾等级*/
	SP_FLICKER = 88,/*防闪烁*/
	SP_NIGHTVIEWING = 89,/*夜视*/
	SP_DNR = 90,/*降噪*/
	SP_DEBUG = 91,/*调试*/
	SP_AD_VALUE = 92,/*光敏AD读取*/	
	SP_CONTRAST = 93,/*对比度*/
	SP_EXP_COMP = 94,/*曝光补偿开关*/ 
	SP_EXP_COMP_VALUE = 95,/*曝光补偿值*/ 
	SP_GAMMA = 96,/*gamma值*/ 
	SP_NORTH_ADJUST = 97,/*正北校准*/	
	SP_XY_ZOOM_STATUS = 98,/*坐标变倍设置状态*/
	SP_TIME_TASK = 99,/*定时任务*/ 
	SP_UP = 110,
	SP_DOWN = 111,
	SP_LEFT = 112,
	SP_RIGHT = 113,
	SP_LEFT_UP = 114,
	SP_RIGHT_UP = 115,
	SP_LEFT_DOWN = 116,
	SP_RIGHT_DOWN = 117,
	SP_ZOOM_TELE = 118,/*变倍短*/
	SP_ZOOM_WIDE = 119,/*变倍长*/

	SP_FOCUS_NEAR = 120,/*聚焦近*/
	SP_FOCUS_FAR = 121,/*聚焦远*/
	SP_IRIS_OPEN = 122,/*光圈小*/
	SP_IRIS_CLOSE = 123,/*光圈大*/

	SP_LIGHT_STOP = 124,/*灯光关*/
	SP_LIGHT_START = 125,/*灯光开*/
	SP_GOTO_POINT = 126,/*转至预置点*/
	SP_SET_POINT = 127,	/*设置预置点*/
	SP_CLEAR_POINT = 128,/*删除预置点*/
	SP_PTZ_STOP = 129,/*停止*/
	PTZ_SP_PRESET_MANUL_FOCUS = 141, //预置点强制手动聚焦
	PTZ_SP_CRUISE_SET_GB28181 = 142,//28181设置巡航新增协议
	PTZ_SP_Get_Roll_Azimuth = 143,
	PTZ_IO_TEST 			= 144,//IO生产测试
	PTZ_SP_3DNR = 145,/*3D降噪*/
	PTZ_SIX_AXIS = 146,
	PTZ_TRACE_POS = 147,
	PTZ_SP_3D_STOP = 148,//仅用于
	PTZ_SP_WIPER = 149,/*雨刷   Parma1取值， 1:开 2: 关*/
	PTZ_SP_RAIN_LEAVEL = 150,/*雨感灵敏度级别*/
	PTZ_SP_DEBUG_INFO = 152,/*电控板调试信息*/
	PTZ_SP_MAN_HEAT = 153,/*手动加热开关*/
	PTZ_SP_LIFE_TIME = 154,/*球机寿命*/
	PTZ_SP_STATE = 155, /*球机状态*/
	PTZ_MOVE_ANGLE = 156,	/*球机运行角度*/	
		
}enSPAction;/*球机控制动作*/


typedef enum
{
	ZCT_NONE           = 0,
	ZCT_HITACHI_SC110  = 1,   //日立机芯
	ZCT_SCM2231P       = 2,   //三星机芯
	ZCT_FCBCX490DP     = 3,   //索尼机芯
	
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
	OSD_TYPE_TIME,	/*时间*/
	OSD_TYPE_CHANNAME,	/*通道名称内容*/
	OSD_TYPE_FRAMERATE,		/*帧率*/
	OSD_TYPE_BITRATE,	/*码率*/
	OSD_TYPE_IFRAME,	/*I帧*/
	OSD_TYPE_TITLE,		/*云台标题*/
	OSD_TYPE_COORDINATE,	/*坐标*/
	//OSD_TYPE_ZOOM,		/*变倍*/
	OSD_TYPE_TEXT1,		/*文本内容*/
	OSD_TYPE_TEXT2,		/*文本内容*/
	OSD_TYPE_TEXT3,		/*文本内容*/
	OSD_TYPE_TEXT4,		/*文本内容*/
	OSD_TYPE_TEXT5,		/*文本内容*/
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
	IP_LIST_TYPE_BLACK,	/*黑名单*/
	IP_LIST_TYPE_WHITE,	/*白名单*/
	IP_LIST_TYPE_BLACK_AND_WHITE,	/*黑+白名单*/
	NOT_USE_IP_LIST,

}enIpListTpye;/*added by zengqingfeng 20120704*/

typedef enum
{
	REC_CONTROL_AUTO,/*超过录像时长后自动切换到下一个录像文件*/
	REC_CONTROL_CLOSE,/*超过录像时长后关闭录像文件*/

}enRecControlType;/*added by zengqingfeng 20120704*/

typedef enum
{
	NEVER,/*不自动重启*/
	REBOOT_EVERY_DAY,/*每天自动重启*/
	REBOOT_EVERY_WEEK,/*每周自动重启*/
	REBOOT_EVERY_MONTH,/*每月自动重启*/
}enAutoReboot;/*added by zengqingfeng 20120725*/

/*added by zengqingfeng start 20120801*/
typedef enum
{
	GAIN_MODE_AUTO,/*自动增益*/
	GAIN_MODE_MANUAL,/*手动增益*/
	
}enGainMode;/*增益模式*/

typedef enum
{
	EXPOSURE_MODE_AUTO,/*自动曝光*/
	EXPOSURE_MODE_MANUAL,/*手动曝光*/
	
}enExposureMode;/*曝光模式*/

typedef enum
{
	SCENARIO_MODE_AUTO,/*自动*/
	SCENARIO_MODE_SUNNY_DAY,/*晴天*/
	SCENARIO_MODE_CLOUDY_DAY,/*阴天*/
	SCENARIO_MODE_NIGHT_DAY,/*夜间*/
	SCENARIO_MODE_INDOOR_DAY,/*室内*/
	SCENARIO_MODE_OUTDOOR_DAY,/*室外，add test*/
	
}enScenarioMode;/*情景模式*/

typedef enum
{
	NIGHT_MODE_DAY,/*白天*/
	NIGHT_MODE_NIGHT,/*夜间*/	
	NIGHT_MODE_AUTO,/*自动*/	
	
}enNightMode;/*日夜模式*/

typedef enum
{
	CODE_FORMAT_H264,/*h.264*/
	CODE_FORMAT_MJPEG,/*m-jpge*/	
	CODE_FORMAT_MPEG4,//FIX ME zhangyt add 2012-12-19
	CODE_FORMAT_RAW,//FIX ME zhangyt add 2012-12-19
	CODE_FORMAT_H265,/*h.265*/
}enCodeFormat;/*编码格式*/

typedef enum
{
	STREAM_TYPE_MANUAL,/*普通*/
	STREAM_TYPE_MOTION_ALARM,/*移动侦测*/	
	STREAM_TYPE_PROBE_ALARM,/*报警*/
	
}enStreamType;/*码流类型*/

/*added by zengqingfeng end 20120801*/

//码流类型定义:用于图片、音视频、回放、移动侦测实时流源数据的类型
typedef enum gsVIDEO_STREAM_TYPE_E
{	    
    //没有
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
	ALL_OPEN,/*常开*/
	ALL_CLOSE,/*常闭*/
}enTransducerType;/*传感器类型*/

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
}enDefaultParamType;/*默认参数*/


/***************************************/ //begin lee
typedef enum
{
	DATE_MODE_CROSSBAND,	//年-月-日
	DATE_MODE_SLASH,		//年/月/日
	DATE_MODE_MAX
}enDateMode;//日期格式

typedef enum
{
	TIME_MODE_24,		//24小时制
	TIME_MODE_12,		//12小时制
	TIME_MODE_MAX
}enTimeMode;//时间格式

typedef enum
{
	GMT_W1200,//西12区
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
	GMT_E0100,//东1区
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
}enTimeZone;//时区

typedef enum
{
	DST_TYPE_DATE,//日期格式:月，日，时，分
	DST_TYPE_WEEK,//周格式:月,月的第几周，星期几，时，分
	DST_TYPE_MAX
}enDSTType;//夏令时时间格式


typedef enum
{
	MESSAGE_TYPE_ALL 			= 0xff,			//全部类型
	MESSAGE_TYPE_SYS 			= (1<<0),		//系统操作
	MESSAGE_TYPE_USER			= (1<<1),		//用户操作
	MESSAGE_TYPE_ALARM			= (1<<2),		//报警事件
}enMessageType;//日志事件类型定义

typedef enum
{
	AUDIO_IN_TYPE_MIC,
	AUDIO_IN_TYPE_MAX	
}enAudInType;//音频输入类型

typedef enum
{
	AUD_SAMPLE_RATE_DEFAULT, // Default : RATE_8KBPS
	AUD_SAMPLE_RATE_8KBPS,
	AUD_SAMPLE_RATE_16KBPS,
	AUD_SAMPLE_RATE_32KBPS,
	AUD_SAMPLE_RATE_44KBPS,//44.1
	AUD_SAMPLE_RATE_48KBPS,
	AUD_SAMPLE_RATE_MAX,
}enAudSampleRate;//音频采样率

typedef enum
{
	COM_USE_TYPE_PTZ, // 云台
	COM_USE_TYPE_TRANS,//透传
	COM_USE_TYPE_MAX
}enComUseType;//串口用途

typedef enum
{
	PTZ_PROTOCOL_PELCO_D,
	PTZ_PROTOCOL_PELCO_P,
	LDS_VEHICLE_DETECTION_SENSORS,		//LDS车检器		qxs 2013.3.7
	VOCATION_SPEED_MEASURING_RADAR,		//文康测速雷达	qxs 2013.3.7
	DOME_PROTOCOL_GXX,
	PTZ_PROTOCOL_MAX
}enPTZProtocol;//云台协议

typedef enum
{
	IP_MODE_STATIC,//静态
	IP_MODE_DYNAMIC,//动态
	IP_MODE_MAX
}enIPMode;//IP模式

typedef enum
{
	IP_VER_4,
	IP_VER_6,
	IP_VER_MAX
}enIPVer;//IP版本

typedef enum
{
	TRANS_QOS_QUALLITY_FST,//画质优先
	TRANS_QOS_TRANS_FST,//流畅传输优先
	TRANS_QOS_MAX
}enTransQoS;//传输服务质量

typedef enum
{
	LANGUAGE_CHINESE,//中文
	LANGUAGE_ENGLISH,//英文
	LANGUAGE_MAX
}enLanguage;//语言

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
	STATUS_SD,		//SD卡状态
	STATUS_LOGIN,   	//登陆状态
	STATUS_UPDATE,	//设备网络升级状态
	STATUS_FORMAT_DISK,/*格式化磁盘*/
	STATUS_CPU_MEM_INFO,/*cpu和内存信息*/
	STATUS_PTZ_TRAJECTORY_INFO,/*轨迹记录状态*/
	STATUS_RECORD_DOWN,/*录像下载状态*/
	STATUS_REBOOT,//设备重启
	STATUS_REPAIR_DISK_FS,/*修复磁盘文件系统*/
	STATUS_PTZ_XYZOOM_SET,/*坐标变倍设置状态*/
	STATUS_PTZ_ANGLE_INFO,/*球机倾斜状态*/
	STATUS_PASSAGE_MODE_INFO,/*走廊模式状态*/
	STATUS_DOT1X_AUTHENTICATION,/*802.1x认证状态*/
	STATUS_MECHROUTE_TEST_OK,//机械行程测试成功
}enStatusType;
/***************************************///added by wjq 2012-9-13

typedef enum
{
	DEVICE_TYPE_GOSUNCN =0,			/*高新兴设备*/
	DEVICE_TYPE_DDT	=1				/*迪迪特设备*/
}enBallDeviceType;

/*****************************FIX ME 2012-11-13 抓拍机相关参数 */
typedef enum
{
	WB_VIDEO_MODEL_Manual,	//手动模式
	WB_VIDEO_MODEL_AUTO,	//自动模式
	WB_VIDEO_MODEL_AUTO_TRCK,	//自动跟踪模式
	WB_VIDEO_MODEL_ONE,	//一次白平衡
	WB_VIDEO_MODEL_IN,	//室内
	WB_VIDEO_MODEL_OUT,	//室外
	WB_VIDEO_MODEL_NIGHT,	//夜间
	WB_VIDEO_MODEL_EVENING,	//傍晚
	WB_VIDEO_MODEL_SUNNY,	//晴天
	WB_VIDEO_MODEL_CLOUDY,	//阴天
	WB_VIDEO_MODEL_SHADY,	//背阴
	WB_VIDEO_MODEL_LAMP,	//白炽灯
	WB_VIDEO_MODEL_FLUO_LAMP,	//荧光灯
	WB_VIDEO_MODEL_FLASH_LAMP,	//闪光灯
	WB_VIDEO_MODEL_OTHER,	//其他
}WHITE_BALANCE_VIDEO_MODE_E;


typedef enum
{
	// Wide dynamic
	WD_MODE_OPEN,//开启
	WD_MODE_CLOSE,//关闭
	WD_MODE_2,// 模式2
	WD_MODE_3,// 模式3
	WD_MODE_4,// 模式4
	WD_MODE_5,// 模式5
} WIDE_DYNAMIC_MODE_E;


typedef enum
{
	IL_MODE_AUTO,/*自动*/
	IL_MODE_MANAUL_OPEN,/*手动开*/
	IL_MODE_MANAUL_CLOSE,/*手动关*/
	IL_MODE_FAR_OPEN,/*远灯开*/
	IL_MODE_CLOSETO_OPEN,/*近灯开*/

}INFRARED_LIGHT_MODE_E;
/*****************************FIX ME 2012-11-13 抓拍机相关参数 end*/

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

//校准数据类型
typedef enum
{
	E_CORRECT_TYPE_VIEW,//视场角
	E_CORRECT_TYPE_RETURN_DIFF,//回程差
	E_CORRECT_TYPE_FOCUSCURVE,//聚焦曲线
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
	CMD_ReqStorageData	   = 20001028,//请求本地存储数据
	CMD_AswStorageData	   = 20002028,//响应本地存储数据
	CMD_ReqSnapshot        = 30001035,
	CMD_AswSnapshot        = 30002035,
	CMD_ReqUpdateFile      = 30001008,
	CMD_AswUpdateFile      = 30002008,
	CMD_ReqDownloadFile	   = 30001096,/*请求下载文件*/
	CMD_AswDownloadFile	   = 30002096,/*应答下载文件*/
	CMD_ReqSysLog          = 30001013,
	CMD_AswSysLog          = 30002013,
	CMD_ReqSrchSDFile      = 30001022,
	CMD_AswSrchSDFile      = 30002022,
	//CMD_ReqGetAllPrePointName = 30001088,/*预置点名称*/
	CMD_AswGetAllPrePointName = 30002088,/*预置点名称*/

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
	CMD_ReqGetOverlayRegionSet       = 40001049,/*OSD参数*/
	CMD_ReqSetOverlayRegionSet       = 40001050,
	CMD_ReqGetCoverRegionSet       = 40001051,/*隐私遮挡*/
	CMD_ReqSetCoverRegionSet       = 40001052,
	CMD_ReqGetPictureParamSet       = 40001053,/*图片参数*/
	CMD_ReqSetPictureParamSet       = 40001054,
	CMD_ReqGetTimingSnapInfo     = 40001055,/*增加读取定时抓拍参数added by zengqingfeng 20120704*/
	CMD_ReqSetTimingSnapInfo     = 40001056,/*增加配置定时抓拍参数added by zengqingfeng 20120704*/
	CMD_ReqGetNormalRecInfo     = 40001057,/*增加读取定时录像参数added by zengqingfeng 20120721*/
	CMD_ReqSetNormalRecInfo     = 40001058,/*增加配置定时录像参数added by zengqingfeng 20120721*/
	CMD_ReqGetRecParamInfo     = 40001059,/*增加读取录像参数added by zengqingfeng 20120721*/
	CMD_ReqSetRecParamInfo     = 40001060,/*增加配置录像参数added by zengqingfeng 20120721*/
	CMD_ReqGetIpFilterInfo     = 40001061,/*增加读取ip过滤配置added by zengqingfeng 20120704*/
	CMD_ReqSetIpFilterInfo     = 40001062,/*增加配置ip过滤added by zengqingfeng 20120704*/
	CMD_ReqGetMotionDetectSet  = 40001063,/*移动侦测*/
	CMD_ReqSetMotionDetectSet  = 40001064,
	CMD_ReqSetSysTimeSet   = 40001065,/*add lee, 20120723*/
	CMD_ReqGetSysTimeSet   = 40001066,
	CMD_ReqAlarmInfo       = 40001067,//add lee, alarminfo
	CMD_ReqGetProbeDetectSet= 40001068,/*IO告警参数*/
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
	CMD_ReqGetSDSet	       = 40001080,/*SD卡*/
	CMD_ReqSetSDSet		   = 40001081,
	CMD_ReqSetSysBasePara  = 40001082,
	CMD_ReqGetSysBasePara  = 40001083,
	CMD_ReqGetAutoRebootSet	= 40001084,/*自动重启*/
	CMD_ReqSetAutoRebootSet	= 40001085,
	CMD_ReqSetManualRebootSet	= 40001086,/*手动重启*/
	CMD_ReqGetVideoParam = 40001089,/*获取视频参数*/
	CMD_ReqSetVideoParam = 40001090,/*设置视频参数*/
	CMD_ReqGetCodeParam = 40001091,/*获取编码参数*/
	CMD_ReqSetCodeParam = 40001092,/*设置编码参数*/
	CMD_ReqSetDefaultParam = 40001093,/*设置默认参数*/
	CMD_ReqDelSysLog		= 40001094,/*清除系统日志*/
    CMD_ReqGetOnlineUserList= 40001095,/*获取在线用户列表*/
	CMD_ReqSetNetDdnsCfg	= 40001097,/*DDNS 参数, add lee,20121019*/
	CMD_ReqGetNetDdnsCfg	= 40001098,/*DDNS 参数, add lee,20121019*/
	CMD_ReqSetNetPppoeCfg	= 40001099,/*PPPOE 参数, add lee,20121019*/
	CMD_ReqGetNetPppoeCfg	= 40001100,/*PPPOE 参数, add lee,20121019*/
	CMD_ReqSetSnapOrSetSnapCfg       = 40001101,//FIX ME zhangyt update 2012-12-19
	CMD_ReqGetSnapOrSetSnapCfg       = 40001102,//FIX ME zhangyt update 2012-12-19
	CMD_ReqGetSystemStatus		    = 40001103,
	//CMD_ReqSetExposure	= 40001104,	//曝光设置
	//CMD_ReqGetExposure	= 40001105,	//曝光获取
	//CMD_ReqControlDO	= 40001106,	//控制DO
	CMD_ReqSetBallMachineParam	= 40001107,/*请求控制球机added by zengqingfeng 20130129*/
	CMD_ReqGetBallMachineParam 	= 40001108,/*请求读取球机added by zengqingfeng 20130129*/
	CMD_ReqSendTransData     = 40001109,/*请求透传数据added by zengqingfeng 20130129*/
	CMD_ReqSetPtzPara       = 40001110,/*请求设置单个预置点/扫描/轨迹名称added by zengqingfeng 20130129*/
	CMD_ReqSetHideAlarm		= 40001111,//遮挡告警设置
	CMD_ReqGetHideAlarm		= 40001112,//遮挡告警获取
	CMD_ReqSetComLinkage	= 40001113,//设置串口联动	qxs	2013.3.6
	CMD_ReqGetComLinkage	= 40001114,//获取串口联动	qxs	2013.3.6
	CMD_ReqSetGB28181Set	= 40001115,//设置GB28181XML		qxs	2013.3.11
	CMD_ReqGetGB28181Set	= 40001116,//获取GB28181XML		qxs	2013.3.11
	CMD_ReqFindDev			= 40001117,//UDP发现设备协议		 qxs	2013.3.21
	CMD_ReqSetDevNet		= 40001118,//UDP修改设备网络参数     qxs	2013.3.21
	CMD_ReqTestCmd			= 40001119,//测试协议				 qxs	2013.4.27
	CMD_ReqSetEventProperty	= 40001120,//设置事件属性				 qxs	2013.6.8
	CMD_ReqGetEventProperty	= 40001121,//读取事件属性				 qxs	2013.6.8
	CMD_ReqSetLinkage       = 40001122,//设置联动规则qxs	2013.6.8
	CMD_ReqGetLinkage       = 40001123,//读取联动规则qxs	2013.6.8
	CMD_ReqStorageCfgSet	= 40001124,//请求本地存储配置设置
	CMD_ReqStorageCfgGet	= 40001125,//请求本地存储配置获取
	CMD_ReqWirelessCfgSet	= 40001126,//请求无线网络参数配置设置
	CMD_ReqWirelessCfgGet	= 40001127,//请求无线网络参数配置获取
	CMD_ReqSetARInfo		= 40001130,//设置增强显示参数
	CMD_ReqBdParamSet   	= 40001131,//请求北斗定位参数配置
	CMD_ReqBdParamGet	    = 40001132,//请求北斗定位参数获取
	CMD_ReqWifiCfgSet		= 40001133,//请求wifi参数配置
	CMD_ReqWifiCfgGet		= 40001134,//请求wifi参数获取
	CMD_ReqRouterListGet	= 40001135,//请求路由器列表
	CMD_ReqCorrectPos		= 40001136,//请求校准位置
	CMD_ReqTrafficPlateCodeSet = 40001137,//请求操作车牌号码库记录
	CMD_ReqTrafficPlateCodeGet = 40001138,//请求获取车牌号码库记录
	CMD_ReqSnapRecordGet	= 40001139,//请求获取图片抓拍记录
	CMD_ReqSnapStorageGet	= 40001140,//请求获取图片抓拍数据
	CMD_ReqRecPlanSet		= 40001141,//请求计划录像参数设置
	CMD_ReqRecPlanGet		= 40001142,//请求计划录像参数获取
	CMD_ReqOpticAxisSet		= 40001143,//请求光轴校准点设置
	CMD_ReqLensParamSet		= 40001144,//请求筒机镜头参数设置
	CMD_ReqStorageManualCtrlSet	= 40001145,//请求手动录像控制
	CMD_ReqStorageManualCtrlGet	= 40001146,//请求手动录像控制信息
	CMD_ReqIniSet					=40001200,//ini配置及获取
	CMD_SetFaceDetect = 40001201,//设置人脸识别区域				 lyj 2015.3.11
	CMD_GetFaceDetect = 40001202,//读取人脸识别区域				 lyj 2015.3.11
	CMD_ReqTelnetStatusSet = 40001203,//请求设置设备Telnet功能状态				 cjh 2015.7.7
	CMD_ReqTelnetStatusGet = 40001204,//请求获取设备Telnet功能状态				 cjh 2015.7.7
	CMD_ReqCorrectParamSet	= 40001205,//IPC校准数据下发
	CMD_ReqCorrectParamGet	= 40001206,//IPC校准数据上传
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
	CMD_AswGetOverlayRegionSet	= 40002049,/*OSD字符叠加*/
	CMD_AswSetOverlayRegionSet	= 40002050,
	CMD_AswGetCoverRegionSet	= 40002051,/*隐私遮挡*/
	CMD_AswSetCoverRegionSet	= 40002052,
	CMD_AswGetPictureParamSet	= 40002053,/*图片参数*/
	CMD_AswSetPictureParamSet	= 40002054,	
	CMD_AswGetTimingSnapInfo	= 40002055,/*增加读取定时抓拍参数added by zengqingfeng 20120704*/
	CMD_AswSetTimingSnapInfo	= 40002056,/*增加配置定时抓拍参数added by zengqingfeng 20120704*/
	CMD_AswGetNormalRecInfo	= 40002057,/*增加读取定时录像参数added by zengqingfeng 20120721*/
	CMD_AswSetNormalRecInfo	= 40002058,/*增加配置定时录像参数added by zengqingfeng 20120721*/
	CMD_AswGetRecParamInfo	= 40002059,/*增加读取录像参数added by zengqingfeng 20120721*/
	CMD_AswSetRecParamInfo	= 40002060,/*增加配置录像参数added by zengqingfeng 20120721*/
	CMD_AswGetIpFilterInfo	= 40002061,/*增加配置ip过滤added by zengqingfeng 20120704*/
	CMD_AswSetIpFilterInfo	= 40002062,/*增加配置ip过滤added by zengqingfeng 20120704*/
	CMD_AswGetMotionDetectSet	= 40002063,/*移动侦测*/
	CMD_AswSetMotionDetectSet	= 40002064,
	CMD_AswSetSysTimeSet   = 40002065,/*add lee, 20120723*/
	CMD_AswGetSysTimeSet   = 40002066,
	CMD_AswAlarmInfo       = 40002067,//add lee, alarminfo
	CMD_AswGetProbeDetectSet= 40002068,/*IO告警*/
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
	CMD_AswGetSDSet		= 40002080,/*SD卡*/
	CMD_AswSetSDSet		= 40002081,
	CMD_AswSetSysBasePara  = 40002082,
	CMD_AswGetSysBasePara  = 40002083,
	CMD_AswGetAutoRebootSet		= 40002084,/*自动重启*/
	CMD_AswSetAutoRebootSet		= 40002085,
	CMD_AswSetManualRebootSet	= 40002086,/*手动重启*/
	CMD_AswGetVideoParam = 40002089,/*视频参数*/
	CMD_AswSetVideoParam = 40002090,/*视频参数*/
	CMD_AswGetCodeParam = 40002091,/*编码参数*/
	CMD_AswSetCodeParam = 40002092,/*编码参数*/
	CMD_AswSetDefaultParam = 40002093,/*默认参数*/
	CMD_AswDelSysLog		= 40002094,/*清除系统日志*/
    CMD_AswGetOnlineUserList = 40002095,/*  应答获取在线用户数 */
	CMD_AswSetNetDdnsCfg	= 40002097,/*DDNS 参数, add lee,20121019*/
	CMD_AswGetNetDdnsCfg	= 40002098,/*DDNS 参数, add lee,20121019*/
	CMD_AswSetNetPppoeCfg	= 40002099,/*PPPOE 参数, add lee,20121019*/
	CMD_AswGetNetPppoeCfg	= 40002100,/*PPPOE 参数, add lee,20121019*/
	CMD_AswSetSnapOrSetSnapCfg  = 40002101,
	CMD_AswGetSnapOrSetSnapCfg  = 40002102,
	CMD_AswGetSystemStatus      = 40002103,
	//CMD_AswSetExposure	= 40002104,	//曝光设置
	//CMD_AswGetExposure	= 40002105,	//曝光获取
	//CMD_AswControlDO	= 40002106,	//控制DO
	CMD_AswSetBallMachineParam 	= 40002107,/*应答控制球机 added by zengqingfeng 20130129*/
	CMD_AswGetBallMachineParam 	= 40002108,/*应答读取球机 added by zengqingfeng 20130129*/
	CMD_AswSendTransData    = 40002109,/*应答透传数据 added by zengqingfeng 20130129*/
	CMD_AswSetPtzPara       = 40002110,/*应答设置单个预置点/轨迹/扫描名称 added by zengqingfeng 20130129*/
	CMD_AswSetHideAlarm     = 40002111,//遮挡告警设置应答
	CMD_AswGetHideAlarm		= 40002112,//遮挡告警获取应答
	CMD_AswSetComLinkage	= 40002113,//设置串口联动应答	qxs	2013.3.6
	CMD_AswGetComLinkage	= 40002114,//获取串口联动应答	qxs	2013.3.6
	CMD_AswSetGB28181Set	= 40002115,//设置GB28181XML		qxs	2013.3.11
	CMD_AswGetGB28181Set	= 40002116,//获取GB28181XML		qxs	2013.3.11
	CMD_AswFindDev			= 40002117,//UDP发现设备协议		 qxs	2013.3.21
	CMD_AswSetDevNet		= 40002118,//UDP修改设备网络参数     qxs	2013.3.21
	CMD_AswTestCmd			= 40002119,//测试协议			     qxs	2013.4.27
	CMD_AswSetEventProperty	= 40002120,//设置事件属性				 qxs	2013.6.8
	CMD_AswGetEventProperty = 40002121,//读取事件属性				 qxs	2013.6.8
	CMD_AswSetLinkage       = 40002122,//设置联动规则qxs	2013.6.8
	CMD_AswGetLinkage       = 40002123,//读取联动规则qxs	2013.6.8
	CMD_AswStorageCfgSet	= 40002124,//响应本地存储配置设置
	CMD_AswStorageCfgGet	= 40002125,//响应本地存储配置获取
	CMD_AswWirelessCfgSet	= 40002126,//响应无线网络参数配置设置
	CMD_AswWirelessCfgGet	= 40002127,//响应无线网络参数配置获取
	CMD_AswSetARInfo		= 40002130,//响应设置增强显示参数
	CMD_AswBdParamSet		= 40002131,//应答北斗定位参数设置
	CMD_AswBdParamGet		= 40002132,//应答北斗定位参数读取
	CMD_AswWifiCfgSet		= 40002133,//响应wifi参数配置
	CMD_AswWifiCfgGet		= 40002134,//响应wifi参数获取
	CMD_AswRouterListGet	= 40002135,//响应路由器列表获取
	CMD_AswCorrectPos		= 40002136,//应答校准位置
	CMD_AswTrafficPlateCodeSet	= 40002137,//响应操作车牌号码库记录
	CMD_AswTrafficPlateCodeGet	= 40002138,//响应获取车牌号码库记录
	CMD_AswSnapRecordGet	= 40002139,//响应获取图片抓拍记录
	CMD_AswSnapStorageGet	= 40002140,//响应获取图片抓拍数据
	CMD_AswRecPlanSet		= 40002141,//响应计划录像参数设置
	CMD_AswRecPlanGet		= 40002142,//响应计划录像参数获取
	CMD_AswOpticAxisSet		= 40002143,//响应光轴校准点设置
	CMD_AswLensParamSet		= 40002144,//响应筒机镜头参数设置
	CMD_AswStorageManualCtrlSet	= 40002145,//响应手动录像控制
	CMD_AswStorageManualCtrlGet	= 40002146,//响应手动录像控制信息
	CMD_AswIniSet					=40002200,//ini配置及获取
	CMD_AswSetFaceDetect = 40002201,//设置人脸识别区域应答				 lyj 2015.3.11	
	CMD_AswGetFaceDetect = 40002202,//读取人脸识别区域应答				 lyj 2015.3.11		
	CMD_AswTelnetStatusSet = 40002203,//响应设置设备Telnet功能状态				 cjh 2015.7.7
	CMD_AswTelnetStatusGet = 40002204,//响应获取设备Telnet功能状态			     cjh 2015.7.7
	CMD_AswCorrectParamSet	= 40002205,//响应IPC校准数据下发
	CMD_AswCorrectParamGet	= 40002206,//响应IPC校准数据上传

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
	//CMD_PostPrePointName = 3017,/*预置点名称*/
	CMD_PostSystemStatus   = 3018,/*获取系统状态*/
	CMD_PostDownloadFileData    = 3019,/*主动上送下载文件*/
	CMD_PostIntelligentanalysisInfo= 3020, // 主动上送智能分析数据信息
	CMD_PostStreamHeartbeat        = 3021, // 媒体流链路心跳
	CMD_PostClientDevInfo		= 3022,//上送作为client端设备的信息心跳
	CMD_PostWirelessStatus         = 3100, //上传无线网络状态
	CMD_PostGpsInfo        = 3101, // 上送GPS数据
	CMD_PostWifiStatus			= 3102,//wifi连接状态信息上送
	CMD_PostSnapRecord                  = 3103, // 设备本地图片记录
	CMD_PostSnapStorage                 = 3104, // 设备本地图片数据
	CMD_PostXinBiaoArrival              = 3110, // 信标到达
	
	CMD_PostGuomaiDeviceInfo            = 3220,  // 国迈设备信息
	CMD_PostGuomaiGps                  = 3221,  // 国迈设备GPS 
	CMD_PostGuomaiSos                  = 3222,  // 国迈设备SOS 
	CMD_PostGuomaiDevState             = 3223,  // 国迈设备状态信息

	CMD_ReqCenterServerGet = 60001000,//TK1请求获取中心服务器地址信息
	CMD_AswCenterServerGet = 60002000,//TK1响应获取中心服务器地址信息
	CMD_ReqCenterServerSet = 60001001,//TK1请求设置中心服务器地址信息
	CMD_AswCenterServerSet = 60002001,//TK1响应设置中心服务器地址信息
	CMD_ReqAIEnableSwitchGet = 60001002,//请求获取智能分析算法使能开关	
	CMD_AswAIEnableSwitchGet = 60002002,//响应获取智能分析算法使能开关
	CMD_ReqAIEnableSwitchSet = 60001003,//请求设置智能分析算法使能开关	
	CMD_AswAIEnableSwitchSet = 60002003,//响应设置智能分析算法使能开关
	CMD_ReqAIServerStatusGet	= 60001004,//请求获取智能服务器状态 		 
	CMD_AswAIServerStatusGet	= 60002004,//响应获取智能服务器状态 
	CMD_PosSerialCmd	= 60003005,//上送串口信息 

	CMD_ReqWifiConnStatusSet = 70001000, // 告诉DM368 WIFI重新连接了
	CMD_AswWifiConnStatusSet = 70002000, // 回应DM368 WIFI重新连接了， 使用通用结构体回复
	
	CMD_ReqSetRobotRouteDetail = 40001601, //机器人请求设置路线
	CMD_AswSetRobotRouteDetail = 40002601, //机器人请求设置路线应答
	CMD_ReqGetRobotRouteDetail = 40001602, //机器人请示获取路线
	CMD_AswGetRobotRouteDetail = 40002602, //机器人请示获取路线应答

	CMD_ReqRobotParamSetGet		=50001500,//二代机器人参数设置和获取
	CMD_AswRobotParamSetGet		=50002500,//二代机器人参数设置和获取返回
	CMD_PushOnRobotInfo		    = 5000,//二代机器人主动上送
	CMD_PushDownRobotInfo		= 6000,//二代机器人中心主动下发


}enNetCmd;

//typedef enum
//{
//	RC_RobotPushOnImageAi	= 301,//主动上送图像分析,参数为TReqRobotPushOnImageAi
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
/*协议头结构体*/
struct _TCmdHead
{
	DWORD dwMagicCode; // Always be NETWORK_MAGIC_CODE
	DWORD  wSize;       // Total packet size, including TCmdHead & Cmd Data
	DWORD  wCmdId;      // command id
}__PACKED__;
typedef struct _TCmdHead TCmdHead;


/**************************************************/
/************      平台接口开始      **************/
/**************************************************/

struct _TReqGetCorrectInfo
{
	TCmdHead 		head;
	enCorrectType   type;			//校正数据类型
}__PACKED__;
typedef struct _TReqGetCorrectInfo TReqGetCorrectInfo;

struct _TAswGetCorrectInfo
{
	TCmdHead 		head;
	int				nResult;
	enCorrectType   type;			//校正数据类型
	unsigned int    dataLen;		//校正数据大小
	char			cData[0];	//校正数据
}__PACKED__;
typedef struct _TAswGetCorrectInfo TAswGetCorrectInfo;

struct _TVideoParam
{
	// Color Adjust 
	BYTE Luminance;								//亮度[0-100]
	BYTE Contrast;								//对比度[0-100]
	BYTE Saturation;							//饱和度[0-100]
	BYTE Hue;									//锐度[0-100]

	// Invert image horizontal & vertical
	BYTE bHorzInvert;							//水平镜像
	BYTE bVertInvert;							//垂直镜像

	enGainMode eGainMode;						/*增益模式*/
	BYTE bGainModeMax;							/*增益上限*/
	enExposureMode eExposureMode;				/*曝光模式*/
	BYTE bMExposureValue;						/*手动曝光值*/
	BYTE bAutoIris;								/*自动光圈*/
	BYTE bLightInhibition;						/*强光抑制*/
	BYTE bBacklightCompensation;				/*背光补偿*/
	enScenarioMode eScenarioMode;				/*情景模式*/
	enNightMode eNightMode;						/*日夜模式*/	
	BYTE ucLumNow;								/*当前亮度值,不可配*/
	BYTE ucNightModeLumMax;						/*日夜模式为自动: 亮度小于该值时，切换到黑白模式*/
	BYTE ucDayModeLumMin;						/*日夜模式为自动: 亮度大于该值时，切换到彩色模式。需大于ucNightModeLumMax*/
	BYTE ucDNModeClt;							/*日夜模式为自动: 日夜参考基准 0:光敏控制 1:自动增益*/	
	// Reserved bytes, for future extension

	/*****************************FIX ME 2012-11-13 抓拍机相关参数*/
	BYTE  ucHue;								/*色度[0-100]*/
	unsigned int uiMShutterSpeed;				/*手动曝光时间 
	 											1/1 1/2  1/3  1/4  1/6  1/12  1/25  1/30  1/60 1/90 1/100 1/125 1/180
												1/195 1/215 1/230 1/250 1/350 1/500 1/725 1/1000 1/1500 1/2000 1/3000 1/4000 1/6000 1/10000 1/30000*/
	unsigned int uiAutoShutterLimit;			/*曝光时间最大值 
	 											1/1 1/2  1/3  1/4  1/6  1/12  1/25  1/30  1/60 1/90 1/100 1/125 1/180
												1/195 1/215 1/230 1/250 1/350 1/500 1/725 1/1000 1/1500 1/2000 1/3000 1/4000 1/6000 1/10000 1/30000*/
	BYTE	bAutoIrisMode;						/*自动光圈模式0关闭；1开启*/
	BYTE  	ucManualIris;						/*手动光圈值，0 - 6 F1.6 F2.0 F2.4 F2.8 F3.4 F4.0 F4.8*/
	char 	BExpCPS;							/*曝光补偿[-128-127]*/
	BYTE 	ucExpCPSMode; 						/*曝光补偿模式 0关，1:全局补偿，2:中心区域补偿*/
	WHITE_BALANCE_VIDEO_MODE_E eWBMode;			/*白平衡模式*/
	BYTE  ucRGGain;								/*R/G增益[0-127]*/
	BYTE  ucBGGain;								/*B/G增益[0-127]*/
	BYTE  ucManualGain;							/*手动增益设置[0-100]*/
	BYTE  ucAutoGainLimit;						/*自动增益最大值[0-100]*/

	WIDE_DYNAMIC_MODE_E eWDMode;				/*宽动态模式*/
	unsigned short usBLCPS_X;					/* Backlight compensation  x坐标*/
	unsigned short usBLCPS_Y;					/* Backlight compensation  y坐标*/
	unsigned short usBLCPS_W;					/* Backlight compensation  宽度*/
	unsigned short usBLCPS_H;					/* Backlight compensation  高度*/
	BYTE  ucBacklightCompensation;				/*背光补偿[0-255]*/
	BYTE  ucToNoiseMode;						/*去噪点模式[0-16] 0：关，1：开，2：3D去噪，3：智能去噪*/
	BYTE  ucEShutterClass;						/* 电子慢快门等级 0关，1. 1/1 2. 1/2 3. 1/3 4. 1/4 5. 1/6 6. 1/12 7. 1/25 8. 1/30*/
	BYTE  ucDayToNightChnV;						/* 日夜转换阈值[日->夜] [0-127]*/
	BYTE  ucNightToDayChnV;						/* 日夜转换阈值[夜->日] [0-127]*/
	BYTE  ucNightDayChnSensity;					/* 日夜转换灵敏度 [0-127]*/
	BYTE  ucNightDayChnDaley;					/* 日夜转换延时 [0-127]*/
	BYTE  bLIKInfraredlit;						/*联动红外灯 0关闭  1开启*/
	INFRARED_LIGHT_MODE_E eInfraredlitMode;		/*红外灯模式*/
	BYTE	ucGammaVal;							/*伽马校正值 0:关，1:0级，2:1级，3:2级*/
	BYTE 	ucSensitiveVal;						/*高灵敏度/清晰度模式 [0-127]*/
	BYTE	ucDelFogClass;						/*去雾等级 [0-100]  0 关闭 1 自动 >1 手动强度*/
	BYTE	ucCamCorrection;					/*镜头矫正 [0-127]*/
	BYTE	bShadEnable;						/*Shad 开关0关 1开*/
	BYTE	bFixDeadPix;						/*去坏点开关0关 1开*/
	BYTE	ucAntiFlicker;						/*去闪烁0关 1:50HZ  2:60HZ*/
	//共52字节
	//彩转黑模式	0	1	0	模式，0：彩色 1：黑白
	/*****************************FIX ME 2012-11-13 抓拍机相关参数 end*/
	enSceneMode eSceneMode;						/*用户自定义场景适应*///zhangyongtao add 2015-05-15
	BYTE    bStabilizer;						/*防抖开关 2关 1开*/
	BYTE    ucStabilizerFunc;					/*防抖功能 0:数字变倍模式,1:数字滤波模式,2:自动中心模式*/
	BYTE    ucStabilizerFuncLevel;				/*功能等级 数字变倍模式[0:10%,1:20%,2:30%] 数字滤波模式[0:低,1:中,2:高] 自动中心模式[0:off,1:half,2:full]*/
	BYTE    ucSceneFlag;						//0表示视频参数设置 1表示场景模式设置
	BYTE    ucLocalScene;						//0表示白天 1表示晚上 当前的场景参数一般是表示晚上或者白天
	BYTE    ucStartHour;						//开始时间采用24小时进制
	BYTE    ucEndHour;							//结束时间 如果出现开始时间比结束时间大说明中间跨越了凌晨

	BYTE	bPassageMode;						/*走廊模式: =0 关闭, =其他,开启*/
	BYTE	uc2DNR;	 							/*2D 降噪 0 - 100*/
	BYTE 	uc3DNR; 							/*3D 降噪* 0 - 100*/
	BYTE	ucFocusMode;						/*聚焦模式，0  手动 1 自动 2 一次聚焦*/;
	BYTE 	ucFocusDistanceMin;					/*最小聚焦距离*/	
	BYTE	ucWDRStrength;						/*宽动态强度 0 - 100*/	
	BYTE	ucAutoTimeMin;						/*曝光时间最小值 
												1/1 1/2  1/3  1/4  1/6  1/12  1/25  1/30  1/60 1/90 1/100 1/125 1/180
												1/195 1/215 1/230 1/250 1/350 1/500 1/725 1/1000 1/1500 1/2000 1/3000 1/4000 1/6000 1/10000 1/30000*/
	BYTE 	ucAutoGainMin;						/*增益下限 0 - 100*/
	BYTE	ucAutoIrisMax;						/*光圈最大值 0 - 6 F1.6 F2.0 F2.4 F2.8 F3.4 F4.0 F4.8*/
	BYTE	ucAutoIrisMin;						/*光圈最小值 0 - 6 F1.6 F2.0 F2.4 F2.8 F3.4 F4.0 F4.8*/
	BYTE	ucDefogMode;						//透雾模式，0:关闭，1:自动，2:手动
	BYTE	ucDigitalZoom;						//数字变倍，0:关闭，1:开启
	// Reserved bytes, for future extension
	BYTE    ucOpticalDefog;                      //光学透雾0，表示关闭，1表示开启，2表示自动
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



/*编码参数*/
struct _TMainStreamParam
{
	// Encode
	enStreamType eStreamType;/*码流类型*/
	enCodeFormat eCodeFormat;/*编码格式*/
	DWORD dwVidRes;/*高2字节表示分辨率的宽低2字节表示分辨率的高例如 1900*1080 dwVidRes=0x0780 0438*/
	BYTE FrmRate;//帧率
	enBitRateMode BitRateMode;//码率控制 0:固定码率，1:可变码率
	WORD BitRate;//码率
	BYTE IFrmInterval;//I帧间隔
	BYTE bDigitalWatermark;/*数字水印*/
	BYTE bWatermarkContent[MAX_DIGITAL_WATERMASK_CONTENT_LEN+1];/*水印字*/
	BYTE QuantLevel;//图像质量等级(取值0-5)
	// Reserved bytes, for future extension
	/*****************************FIX ME 2012-11-13 抓拍机相关参数 */
	//BYTE	ucFrameCtrl;/* 码流控制  变码率，定码率，智能码率*/ 
	BYTE 	ucFrameInfo;/* 单P帧，BBP帧?*/
	BYTE	bFrameEncryption;/*码流加密0:关 1:开*/
	//共2个字节
	/*****************************FIX ME 2012-11-13 抓拍机相关参数 end*/


	DWORD dwFps;		/*采样帧率 帧率*1000,如25000=25fps*/
	BYTE  ucPorI	;	/*0:p 表示逐行 1:I 表示隔行*/

	/****add by hy 2017-07-18*****/
	BYTE ucRateSmoothing;/*码流平滑等级1-9*/

	// Reserved bytes, for future extension
	BYTE Reserved[7-6]; //zhangyt 2013-05-29 7->5
}__PACKED__; // Total 48bytes
typedef struct _TMainStreamParam TMainStreamParam;

struct _TSubStreamParam
{
	BYTE bSubSteam;/*是否启用次码流*/
	enStreamType eStreamType;/*码流类型*/
	enCodeFormat eCodeFormat;/*编码格式*/
	DWORD dwVidRes;/*高2字节表示分辨率的宽低2字节表示分辨率的高例如 1900*1080 dwVidRes=0x0780 0438*/
	BYTE FrmRate;//帧率
	enBitRateMode BitRateMode;//码率控制 0:固定码率，1:可变码率
	WORD BitRate;//码率
	BYTE IFrmInterval;//I帧间隔
	BYTE QuantLevel; //图像质量等级(取值0-5)

	// Reserved bytes, for future extension
	/*****************************FIX ME 2012-11-13 抓拍机相关参数 */
	//BYTE	ucFrameCtrl;/* 码流控制  ?变码率，定码率，智能码率*/ 
	BYTE 	ucFrameInfo;/* 单P帧，BBP帧?*/
	BYTE	bFrameEncryption;/*码流加密0:关 1:开*/
	//共3个字节
	/*****************************FIX ME 2012-11-13 抓拍机相关参数 end*/
	DWORD dwFps;		/*采样帧率 帧率*1000,如25000=25fps*/
	BYTE  ucPorI;	/*0:p 表示逐行 1:I 表示隔行*/

	/****add by hy 2017-07-18*****/
	BYTE ucRateSmoothing;/*码流平滑等级1-9*/

	BYTE Reserved[8-6]; //zhangyt 2013-05-29 8->8-5
}__PACKED__; // Total 32bytes
typedef struct _TSubStreamParam TSubStreamParam;

struct _TCodeParam
{
	// Encode
	TMainStreamParam stMainStreamParam;/*主码流参数*/
	TSubStreamParam stSubStramParam;/*次码流参数*/

	BYTE	bROIEnable;/* 0:关 1:开*/ 
	unsigned short usROI_X;/* ROI  x坐标*/
	unsigned short usROI_Y;/* ROI y坐标*/
	unsigned short usROI_W;/* ROI  宽度*/
	unsigned short usROI_H;// ROI	高度*/

	BYTE	bSubROIEnable;/* 0:关 1:开*/ 
	unsigned short usSubROI_X;/* ROI  x坐标*/
	unsigned short usSubROI_Y;/* ROI y坐标*/
	unsigned short usSubROI_W;/* ROI  宽度*/
	unsigned short usSubROI_H;// ROI	高度*/

	TSubStreamParam stThrdStramParam;/*第三码流参数*/
	BYTE	bThrdROIEnable;/* 0:关 1:开*/ 
	unsigned short usThrdROI_X;/* ROI  x坐标*/
	unsigned short usThrdROI_Y;/* ROI y坐标*/
	unsigned short usThrdROI_W;/* ROI  宽度*/
	unsigned short usThrdROI_H;// ROI	高度*/

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



/*手动重启设置*/
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



/*录像设置*/
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

/*手动录像控制及获取*/
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

/*录像查询*/
struct _TReqStorageData		
{
	TCmdHead head;
	char byFlag; // 1:表示开启 0:表示停止
	enMonBlockType eMonBlockType;
	unsigned short dwEventType; //0x0000:表示查询全部事件类型;0x0001:中心断开;0x0002:网络断开;0x0004:IP冲突 		
	long long     nStartTime;
	long long     nStopTime;
}__PACKED__;
typedef struct _TReqStorageData TReqStorageData;

struct _TAswStorageData
{
	TCmdHead head;
	int nResult;
	unsigned long long nDataSize; //请求录像数据大少单位字节
}__PACKED__;
typedef struct _TAswStorageData	 TAswStorageData;

/**************************************************/
/************      平台接口结束      **************/
/**************************************************/




/*motion detection struct*/
struct _TEventMotiondetection
{
	BYTE byEnable;			//	1 bytes	是否启用该事件
	BYTE bySensitivity;		//	1 bytes	灵敏度
	BYTE byThreshold;		//  1 bytes	阈值
	WORD wDebounceTime;	//	2 bytes	去抖动时间
	WORD wRgnX;			//	2 bytes	X坐标
	WORD wRgnY;			//	2 bytes	Y坐标
	WORD wRgnW;			//	2 bytes	宽度
	WORD wRgnH;			//	2 bytes	高度

}__PACKED__;/*13bytes*/
typedef struct _TEventMotiondetection TEventMotiondetection;

/*io detection struct*/
struct _TEventIOetection
{
	BYTE byEnable;				//	1 bytes	是否启用该事件
	WORD wDebounceTime;		//	2 bytes	去抖动时间
	BYTE byTransducerType;	//	1 bytes	传感器类型0：常开；1：常闭

}__PACKED__;/*7bytes*/
typedef struct _TEventIOetection TEventIOetection;

/*sd struct*/
struct _TEventSD
{
	BYTE byEnable;				//	1 bytes	是否启用该事件
	BYTE byLeastSpacePercent;	//	1 bytes	空间报警阀值

}__PACKED__;/*2bytes*/
typedef struct _TEventSD TEventSD;

/*serial struct*/
struct _TEventSerial
{
	BYTE byEnable;				//	1 bytes	是否启用该事件
	BYTE byComUseType;//	1 bytes	串口用途：
	enPTZProtocol yPTZProtocol;	//	4 bytes	云台协议：
}__PACKED__;/*9bytes*/
typedef struct _TEventSerial TEventSerial;

/*common struct*/
struct _TEventCommon
{
	BYTE byEnable;				//	1 bytes	是否启用该事件
}__PACKED__;/*1bytes*/
typedef struct _TEventCommon TEventCommon;

struct _TEvent
{
	BYTE byEventType;	//	1 bytes	事件类型
	BYTE byEventId;			//	1 bytes	事件ID
	BYTE byEventLen;			//	1 bytes	事件内容长度M
	BYTE byEventContent[0];		//	M bytes	事件内容
}__PACKED__;
typedef struct _TEvent TEvent;


/*io rule */
struct _TRuleIO
{
	WORD wRuleDelay;		//	2bytes	延迟
	WORD wRuleDur;			//	2bytes	联动时长，0:表示一直
	BYTE byTransducerType;	//	1 bytes	传感器类型
	WORD wAlmOutIONum;		//	2 bytes	输出IO 编号
	DWORD dwOutInteval;		//	4 bytes	输出间隔ms,0不考虑该属性
	DWORD dwOutCnt;			//	4bytes	输出次数默认1次
}__PACKED__;/*18bytes*/
typedef struct _TRuleIO TRuleIO;

/*snap rule */
struct _TRuleSnap
{
	WORD wRuleDelay;		//	2bytes	延迟
	WORD wRuleDur;			//	2bytes	联动时长，0:表示一直
	DWORD dwSnapInterval	;	// 4 bytes	抓拍间隔
	WORD wSnapCnt;			//	2 bytes	抓拍张数
	WORD wSendBitFlag;			//	2 bytes	图片发送控制bit0:FTP;bit1:Email;bit2:本地保存; bit3:发送到中心;bit4:其他
}__PACKED__;/*12bytes*/
typedef struct _TRuleSnap TRuleSnap;

/*recd rule */
struct _TRuleRecd
{
	WORD wRuleDelay;		//	2bytes	延迟
	WORD wRuleDur;			//	2bytes	联动时长，0:表示一直
	DWORD dwRecordTime;		//	4 bytes	录像时长
	WORD wSendBitFlag;			//	2 bytes	图片发送控制bit0:FTP;bit1:Email;bit2:本地保存; bit3:发送到中心;bit4:其他
}__PACKED__;/*10bytes*/
typedef struct _TRuleRecd TRuleRecd;

/*ptz rule */
struct _TRulePtz
{
	WORD wRuleDelay;		//	2bytes	延迟
	WORD wRuleDur;			//	2bytes	联动时长，0:表示一直
	BYTE byRulePtzType;			//	1 bytes	联动操作类型, 0:预置点，1：扫描，2：巡航，3：轨迹
	BYTE byRulePtzValue;			//	1 bytes	对应预置点号/扫描线ID/巡航ID/轨迹ID

}__PACKED__;/*6bytes*/
typedef struct _TRulePtz TRulePtz;

/*serial rule */
struct _TRuleSerial
{
	WORD wRuleDelay;		//	2bytes	延迟
	WORD wRuleDur;			//	2bytes	联动时长，0:表示一直
	BYTE bySeiralNum;			//	1 bytes	串口号
	BYTE bySerialData[0];			//	 Linkage_Len – 5 bytes	发送给串口的数据
}__PACKED__;/*5bytes*/
typedef struct _TRuleSerial TRuleSerial;

/*osd rule */
struct _TRuleOsd
{
	WORD wRuleDelay;		//	2bytes	延迟
	WORD wRuleDur;			//	2bytes	联动时长，0:表示一直
	BYTE byOverlayType;			//	1bytes	叠加类型
	BYTE byOSDcontent[36];		//	36bytes	叠加内容
	WORD wX;					//	2bytes	叠加区域的X坐标
	WORD wY;					//	2bytes	叠加区域的Y坐标
}__PACKED__;/*48bytes*/
typedef struct _TRuleOsd TRuleOsd;

/*up alarm info  rule */
struct _TRuleUpInfo
{
	WORD wRuleDelay;		//	2bytes	延迟
	WORD wRuleDur;			//	2bytes	联动时长，0:表示一直
	DWORD dwClientBitMap;		//	4 bytes	client索引对应的位图bit0 表示第一个客户端

}__PACKED__;/*8bytes*/
typedef struct _TRuleUpInfo TRuleUpInfo;

/*BNC rule */
struct _TRuleBnc
{
	WORD wRuleDelay;		//	2bytes	延迟
	WORD wRuleDur;			//	2bytes	联动时长，0:表示一直
	BYTE byOpen	;				// 1 bytes	0关闭，1打开

}__PACKED__;/*5bytes*/
typedef struct _TRuleBnc TRuleBnc;

struct _TRule
{
	BYTE byRuleNum;		//	1 bytes	为唯一索引ID 每个事件的规则号为1-8表示对应的本事件的8个规则，添加规则时需要指定使用哪一个规则号。
	BYTE byRuleEnable;		//	1 bytes	联动使能：0：停用；1：启用
	BYTE byRuleType;		//	1 bytes	联动类型
	BYTE byRuleLen;			//	1 bytes	联动内容长度M
	BYTE byRuleContent[0];	//	Mbytes	联动内容

}__PACKED__;
typedef struct _TRule TRule;

struct _TEventRule
{
	BYTE byEventType;	//	1bytes	事件类型
	BYTE byEventId;			//	1 bytes	事件ID
	BYTE byRuleCount;			//	1 bytes	联动规则数目
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


/*扩展OSD叠加区域为4个added by zengqingfeng 20120607*/
struct _TOverlayRegionSet
{
	// OSD
	enOverlayType bOverlayType;/*OSD 类型*/
	char chOsdContent[CHAN_NAME_LEN+1];/*OSD 内容*/
	BYTE bShowFlag;
	WORD usPos_X;
	WORD usPos_Y;
	
	BYTE Reserved[15];
}__PACKED__; 
typedef struct _TOverlayRegionSet TOverlayRegionSet;


/*遮挡区域为4个added by zengqingfeng 20120607*/
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


/*视频参数*/
struct _TVideoSettings
{
	
	TVideoParam stVideoParamCfg;
	TCodeParam stCodeParamCfg;

	// Reserved bytes, for future extension
	BYTE Reserved[102];
}__PACKED__; // Total 128 bytes
typedef struct _TVideoSettings TVideoSettings;


/*为了扩展移动侦测区域为4个added by zengqingfeng 20120612*/
struct _TMotionRegionSet
{
	//移动侦测区域
	BYTE  bShowDetectRegion;/*用于表示当前移动侦测区域是否需要起作用，=0不起作用*/
	WORD usRgnX;/*X坐标*/
	WORD usRgnY; /*Y坐标*/
	WORD usRgnW; /*宽度*/
	WORD usRgnH; /*高度*/

	// Reserved bytes, for future extension
	BYTE Reserved[2];
}__PACKED__; // Total 11 bytes
typedef struct _TMotionRegionSet TMotionRegionSet;

struct _TMotionDetectionSet
{
	BYTE bMotionDetect;/*是否需要检测移动侦测*/
	WORD MotionOutMask;/*输出标识*/
//	WORD wAlmOutDelay;/*输出延时*/
	WORD wAlmOutDur; /*输出时长*/
	BYTE Sensitivity;/*灵敏度*/
	BYTE Threshold;/*阈值*/
	
	TMotionRegionSet stMotionRegionCfg[MAX_MOTION_DETECT_REGION];//移动侦测区域
	WORD wDebounceTime;/*去抖动时间*/

	/*联动抓拍*/
	BOOL bSnapFlag;/*是否需要抓拍*/
	BYTE chSnapInterval;/*抓拍间隔*/
	BYTE chSnapCnt;/*抓拍张数*/
	BYTE bSnapSendToFTP;/*图片是否需要上送到FTP*/
	BYTE bSnapSendToEmail;/*图片是否需要上送到（新增）Email*/
	BYTE bSnapSendToSD;/*图片是否需要上送到SD卡*/

	/*联动录像*/
	BOOL bRecFlag;/*是否需要录像*/
	int nRecordTime;/*录像时长*/
	BYTE bRecSendToFTP;/*录像时间上送到FTP（新增）*/
	BYTE bRecSendToSD;/*录像时间上送到SD（新增）*/
	
	/*联动云台*/
	BYTE bLinkPtzFlag;	/*是否需要联动云台*/
	BYTE bLinkPtzType;	/*联动操作类型, 0:预置点，1：扫描，2：巡航，3：轨迹*/
	BYTE bLinkPtzValue;/*对应预置点号/扫描线ID/巡航ID/轨迹ID（新增）*/

	// Reserved bytes, for future extension
	BYTE Reserved[3];

}__PACKED__; // Total 122 bytes
typedef struct _TMotionDetectionSet TMotionDetectionSet;

//遮挡告警
struct _THideAlarmSet
{
	BYTE bHideAlarm;/*是否需要检测遮挡告警*/
	BOOL bAlmOutFlag;/*是否需要告警输出*/
	WORD wAlmOutDur; /*告警输出时长*/

	BOOL bSnapFlag;	/*是否需要抓拍*/
	char chSnapInterval;	/*抓拍间隔*/
	char chSnapCnt;	/*抓拍张数*/
	BYTE bSnapSendToFTP;/*图片是否需要上送到FTP*/
	BYTE bSnapSendToEmail;/*图片是否需要上送到（新增）Email*/
	BYTE bSnapSendToSD;/*图片是否需要上送到SD卡*/


	/*联动录像*/
	BOOL bRecFlag;	/*是否需要录像*/
	int nRecordTime;/*录像时长*/
	BYTE bRecSendToFTP;/*录像时间上送到FTP（新增）*/
	BYTE bRecSendToSD;/*录像时间上送到SD（新增）*/


	/*联动云台*/
	BYTE bLinkPtzFlag;	/*是否需要联动云台*/
	BYTE bLinkPtzType;	/*联动操作类型, 0:预置点，1：扫描，2：巡航，3：轨迹*/
	BYTE bLinkPtzValue;/*对应预置点号/扫描线ID/巡航ID/轨迹ID（新增）*/

	// Reserved bytes, for future extension
	BYTE Reserved[5]; /*预留3字节变为5字节*/       
}__PACKED__; // Total 122 bytes
typedef struct _THideAlarmSet THideAlarmSet;


/*I0报警*/
struct _TProbeDetectionSet
{
	BYTE bProbeDetect;
	WORD MotionOutMask;/*输出标识*/
//	WORD wAlmOutDelay;/*输出延时*/
	WORD wAlmOutDur;/*输出时长*/
	WORD wDebounceTime;/*去抖动时间*/

	BYTE chProbeAlarmInChn;/* 输入通道*/
	BYTE chProbeAlarmOutChn;/*输出通道*/
	enTransducerType eTransducerType;/*传感器类型*/

	/*联动抓拍*/
	BOOL bSnapFlag;	/*是否需要抓拍*/
	BYTE chSnapInterval;	/*抓拍间隔*/
	BYTE chSnapCnt;	/*抓拍张数*/
	BYTE bSnapSendToFTP;/*图片是否需要上送到FTP*/
	BYTE bSnapSendToEmail;/*图片是否需要上送到Email（新增）*/
	BYTE bSnapSendToSD;/*录像时间上送到SD（新增）*/
	BYTE bSnapSendToCenter;	//联动抓拍上送到中心 qxs 2013.3.7

	/*联动录像*/
	BOOL bRecFlag;	/*是否需要录像*/
	int nRecordTime;/*录像时长*/
	BYTE bRecSendToFTP;/*是否需要上送到FTP*/
	BYTE bRecSendToSD;/*录像时间上送到SD（新增）*/
	
	/*联动云台*/
	BYTE bLinkPtzFlag;	/*是否需要联动云台*/
	BYTE bLinkPtzType;	/*联动操作类型, 0:预置点，1：扫描，2：巡航，3：轨迹*/
	BYTE bLinkPtzValue;/*对应预置点号/扫描线ID/巡航ID/轨迹ID（新增）*/

	// Reserved bytes, for future extension
	BYTE Reserved[4];
}__PACKED__; // Total 40 bytes
typedef struct _TProbeDetectionSet TProbeDetectionSet;


/*增加图片参数设置added by zengqingfeng 20120628*/
 struct _TSnapPictureSet
{
 	BOOL bSnapFlag;	/*是否需要抓拍*/
	BYTE chSnapInterval;	/*抓拍间隔*/
	BYTE chSnapCnt;	/*抓拍张数*/
	BOOL bSendToFTP;/*是否需要上送到FTP*/
	BOOL bSendToEmail;/*是否需要上送到Email*/
}__PACKED__; // Total 64 bytes
typedef struct _TSnapPictureSet T_SnapPictureSet ;	

struct _TTimingPlanPeriodSet
{	
	BYTE bEnable;/*是否启用这个时段*/
	BYTE StartHour;/*开始小时*/
	BYTE StartMinute;/*开始分钟*/
	BYTE StartSecond;/*开始秒*/
	BYTE StopHour;/*结束小时*/
	BYTE StopMinute;/*结束分钟*/
	BYTE StopSecond;/*结束秒*/
	
	// Reserved bytes, for future extension
	BYTE Reserved[3];
}__PACKED__; 
typedef struct _TTimingPlanPeriodSet TTimingPlanPeriodSet;

struct _TTimingPlanDaySet
{	
	BYTE bEnable;/*是否启用这天*/
	TTimingPlanPeriodSet stTimingPlanPeriodCfg[MAX_SNAP_PLAN_PER_DAY];
	
	
	// Reserved bytes, for future extension
	BYTE Reserved[3];
}__PACKED__; 
typedef struct _TTimingPlanDaySet TTimingPlanDaySet;

struct _TNormalRecordSet
{
 	BOOL bEnableFlag;	/*是否需要录像*/
	BOOL bSendToFTP;/*是否需要上送到FTP*/
	BOOL bSendToEmail;/*是否需要上送到Email*/
	TTimingPlanDaySet stNormalRecordPlan[WEEK_MAX_DAY];

	// Reserved bytes, for future extension
	BYTE Reserved[4];
}__PACKED__; 
typedef struct _TNormalRecordSet TNormalRecordSet;

struct _TRecordInfo
{
 	BOOL bEnableFlag;	/*是否需要录像*/
	BOOL bSendToFTP;/*是否需要上送到FTP*/
	BOOL bSendToEmail;/*是否需要上送到Email*/
	int nRecordTime;/*录像时长*/
	int nDelayTime;/*录像延时*/
	// Reserved bytes, for future extension
	BYTE Reserved[4];
}__PACKED__; 

typedef struct _TRecordInfo TRecordInfoSet;

struct _TRecParam
{
	unsigned char ucEnable;/*是否需要预录*/
	unsigned char ucPreRecLen; /*预录时长*/
	int nMaxRecFileTime;/*录像文件时长*/
	enRecControlType eRecControlType;/*录像控制*/
	// Reserved bytes, for future extension
	BYTE Reserved[4];
	
}__PACKED__; 
typedef struct _TRecParam TRecParamSet;

struct _TRecordSet
{
	TRecordInfoSet  stManualAlarmRecordCfg;/*增加手动告警联动录像配置参数*/
	TNormalRecordSet  stNormalRecordCfg;/*增加定时录像配置参数*/

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


/*增加ip过滤的相关参数added by zengqingfeng 20120704*/
struct _TIpListSet
{
 	unsigned int nIpListStart;	/*IP名单中开始的IP*/
	unsigned int nIpListEnd; 	/*IP名单中结束的IP*/
	
	BYTE Reserved[4];
}__PACKED__; 
typedef struct _TIpListSet TIpListSet;

struct _TIpFilterSet
{
 	enIpListTpye  chIpListTpye;	/*IP名单方式*/
	TIpListSet stBlackIpListCfg[MAX_IP_FILTER_LIST]; 	/*IP黑名单*/
	TIpListSet stWhiteIpListCfg[MAX_IP_FILTER_LIST]; 	/*IP白名单*/
	
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
	WORD wAlarmTypeMask;/*告警类型，见enAlarmType*/
	TTime BegTime;/*起始时间*/
	TTime EndTime;/*结束时间*/
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
	BOOL bStorageStrategy;/*是否启用存储策略*/

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
	BYTE bFTPEnable;							//是否打开
	char FTPSvrIp[IP_ADDR_LEN+1];				//FTP服务器IP
	WORD wFTPSvrPort;							//FTP端口
	char FTPSvrUserName[FTP_USER_NAME_LEN+1];	//用户名
	char FTPSvrUserPswd[FTP_USER_PSWD_LEN+1];	//密码
	WORD wFTPFileLen;							//文件大小unit: MByte
	char FTPPath[FTP_PATH_LEN+1];				//文件路径
// Reserved bytes, for future extension
	BYTE Reserved[8];
}__PACKED__; // Total 160 bytes
typedef struct _TNetFtpSet TNetFtpSet;

struct _TNetSmtpSet					
{
	BYTE bSMTPEnable;							//是否打开
	char SMTPIp[DDNS_DOMAIN_NAME_LEN+1];		//SMTP服务器IP,IP_ADDR_LEN->
	WORD wSMTPPort;								//SMTP端口
	char SMTPUserName[SMTP_USER_NAME_LEN+1];	//SMTP用户名33
	char SMTPUserPswd[SMTP_USER_PSWD_LEN+1];	//SMTP密码33
	char SMTPFromAddr[SMTP_EMAIL_ADDR_LEN+1];	//发送地址65
	char SMTPSbuject[SMTP_SUBJECT_LEN+1];		//邮件标题65
	char SMTPToAddr1[SMTP_EMAIL_ADDR_LEN+1];	//接收地址1
	char SMTPToAddr2[SMTP_EMAIL_ADDR_LEN+1];	//接收地址2
	char SMTPToAddr3[SMTP_EMAIL_ADDR_LEN+1];	//接收地址3
	BYTE bSmtpSendAlarmImage;					//是否附上图片
	BYTE bSendSysStatus;						//发送系统状态
	WORD wSendSysStatusTime;					//发送系统状态时间间隔单位:分钟(1~4500)
	// Reserved bytes, for future extension
	BYTE Reserved[20];
}__PACKED__; // Total 680bytes
typedef struct _TNetSmtpSet TNetSmtpSet;

// DDNS Config
struct _TNetDdnsSet					
{
	BYTE bDdnsEnable;							//DDNS服务是否启用
	enDdnsServerType eDdnsServerType;			//DDNS 服务器类型
	char DdnsSvrIp[DDNS_DOMAIN_NAME_LEN+1];		//DDNS 服务器地址
	WORD wDdnsSvrPort;							//DDNS 服务器端口
	char DomainName[DDNS_DOMAIN_NAME_LEN+1];	//设备域名
	char DdnsSvrUserName[DDNS_USER_NAME_LEN+1]; //DDNS 用户名称
	char DdnsSvrUserPswd[DDNS_USER_PSWD_LEN+1]; //DDNS 用户密码

// Reserved bytes, for future extension
	BYTE Reserved[20];
}__PACKED__; // Total 195 bytes
typedef struct _TNetDdnsSet TNetDdnsSet;


// PPPoE
struct _TNetPppoeSet
{
	BYTE bPppoeEnable;							//PPPOE服务是否启用
	char PppoeUserName[PPPOE_USER_NAME_LEN+1];	//PPPOE 用户名称
	char PppoeUserPswd[PPPOE_USER_PSWD_LEN+1];	//PPPOE 用户密码
	char PppoeDevIp[IP_ADDR_LEN+1];				//PPPOE 拨号获取到的设备IP，不可配。
	
// Reserved bytes, for future extension
	BYTE Reserved[20];

}__PACKED__;// Total 101 bytes
typedef struct _TNetPppoeSet TNetPppoeSet;

struct _TNTPSet
{
	BYTE bEnable;									//=0,不启用;=其他,启用.
	char chTimeServerAddr[NTP_SERVER_ADD_LEN+1];	//时间服务器地址,33
	short nTimeServerPort;							//默认就是123.
	short nUpdataTime;								//更新频率，单位：分钟
}__PACKED__;
typedef struct _TNTPSet TNTPSet;

struct _TDSTTime//夏令时时间格式
{
	BYTE	Month;	// 1 ~ 12
	BYTE	Day;	// 1 ~ 31
	BYTE	Hour;	// 0 ~ 23
	BYTE	Minute;	// 0 ~ 59
	BYTE	Week;	// 1 ~ 5 
	BYTE	WDay;	// 1 ~ 7
}__PACKED__;
typedef struct _TDSTTime TDSTTime;

struct _TDSTSet	//DatelightSavingTime 夏令时
{
	BYTE		bEnable;//=0,不启用;=其他,启用.
	enDSTType	DSTType;
	TDSTTime	DSTTimeBegin;
	TDSTTime	DSTTimeEnd;
}__PACKED__;
typedef struct _TDSTSet TDSTSet;

struct _TTimeSet
{
	enDateMode	eDateMode;
	enTimeMode	eTimeMode;
	enTimeZone  eTimeZone;//时区
	TTime 		LocalTime;
	TNTPSet		NTPSet;
	TDSTSet		DSTSet;	//夏令时
	BYTE		reserve[10];
}__PACKED__;
typedef struct _TTimeSet TTimeSet;

//系统日志记录格式
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
	enMessageType eMessageType;//事件类型
}__PACKED__;
typedef struct _TSysLogFilter TSysLogFilter;

/*有线网络参数*/
struct _TWiredNetPara
{
	char	DeviceSerial[DEVICE_SERIAL_LEN+1];//序列号，DEVICE_SERIAL_LEN=16
	enIPMode eIPMode;
	enIPVer eIPVer;
	
	char NetMAC[NET_MAC_LEN+1];//NET_MAC_LEN=17
	char IpAddr[IP_ADDR_LEN+1];//IP_ADDR_LEN=15
	char NetMask[IP_ADDR_LEN+1];
	char GateWayIp[IP_ADDR_LEN+1];
	char DnsSvrIpFirst[IP_ADDR_LEN+1];//首选DNS
	char DnsSvrIpSecond[IP_ADDR_LEN+1];//备用DNS
	
	BYTE reserved[100];
}__PACKED__;
typedef struct _TWiredNetPara TWiredNetPara;

/*网络基本参数*/
struct _TNetBasePara
{
	BYTE	ClientConnectNumMax;//最大连接数
	WORD 	wSvrTCPPort;
	WORD 	wSvrUDPPort;
	WORD 	wSvrHTTPPort;
	WORD 	wSvrRTSPPort;
	enTransQoS eTransQoS;
		
	BYTE reserved[100];
}__PACKED__;
typedef struct _TNetBasePara TNetBasePara;

/*网络断开告警*/
struct _TNetDownAlarm
{
	BYTE bAlarmEnable;/*该告警是否启用*/
	BYTE bAlarmRec;		/*是否启用录像*/
	WORD nRecordTime;/*录像时间*/
	BYTE bAlarmIOOutput;	/*是否启动IO报警输出*/
	WORD nIOOutputTime;/*IO报警输出时间*/
	BYTE reserve[10];
}__PACKED__;
typedef struct _TNetDownAlarm TNetDownAlarm;

/*IP冲突告警*/
struct _TIPClashAlarm
{
	BYTE bAlarmEnable;/*该告警是否启用*/
	BYTE bAlarmRec;		/*是否启用录像*/
	WORD nRecordTime;/*录像时间*/
	BYTE bAlarmIOOutput;	/*是否启动IO报警输出*/
	WORD nIOOutputTime;/*IO报警输出时间*/
	BYTE reserve[10];
}__PACKED__;
typedef struct _TIPClashAlarm TIPClashAlarm;

/*无SD卡告警*/
struct _TNoSDAlarm
{
	BYTE bAlarmEnable;/*该告警是否启用*/
	BYTE bAlarmIOOutput;	/*是否启动IO报警输出*/
	WORD nIOOutputTime;/*IO报警输出时间*/
	BYTE reserve[10];
}__PACKED__;
typedef struct _TNoSDAlarm TNoSDAlarm;

/*SD卡空间不足告警*/
struct _TSDLackSpaceAlarm
{
	BYTE bAlarmEnable;/*该告警是否启用*/
	BYTE LeastSpacePercent;/*空间报警阀值*/
	BYTE bAlarmIOOutput;	/*是否启动IO报警输出*/
	WORD nIOOutputTime;/*IO报警输出时间*/
	BYTE reserve[10];
}__PACKED__;
typedef struct _TSDLackSpaceAlarm TSDLackSpaceAlarm;

/*SD卡故障告警*/
struct _TSDErrAlarm
{
	BYTE bAlarmEnable;/*该告警是否启用*/
	BYTE bAlarmIOOutput;	/*是否启动IO报警输出*/
	WORD nIOOutputTime;/*IO报警输出时间*/
	BYTE reserve[10];
}__PACKED__;
typedef struct _TSDErrAlarm TSDErrAlarm;

/*事件管理--异常处理*/
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

/*系统设置--基本设置*/
struct _TSysBasePara
{
	char DeviceName[SERVER_NAME_LEN+1];//SERVER_NAME_LEN=32
	enLanguage	eLanguage;
	enVidStd eVidStd;

	char DevSerial[SERVER_NAME_LEN+1]; // 设备序列号
	BYTE reserved[67];
}__PACKED__;
typedef struct _TSysBasePara TSysBasePara;

/*add lee, 20120727*/
struct _TAudioPara
{
	BYTE bDisableAudio;
	enAudInType eInType;
	enAudEncType eEncType;
	enAudCodeRate eCodeRate;//码率，不可配置
	enAudSampleRate	eAudSampleRate;//采样率,只支持8K??
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

/*串口联动抓拍	qxs 2013.3.7*/
struct _TComLinkage
{
	BOOL bComLinkage;
	WORD wMotionOutMask;/*输出标识*/
	WORD wAlmOutDur;/*输出时长*/
	BYTE byProbeAlarmOutChn;/*输出通道*/
	enTransducerType eTransducerType;/*传感器类型*/

	/*联动抓拍*/
	BOOL bSnapFlag;	/*是否需要抓拍*/
	BYTE bySnapInterval;	/*抓拍间隔*/
	BYTE bySnapCnt;	/*抓拍张数*/
	BYTE bySnapSendToFTP;/*图片是否需要上送到FTP*/
	BYTE bySnapSendToEmail;/*图片是否需要上送到Email（新增）*/
	BYTE bySnapSendToSD;/*录像时间上送到SD（新增）*/
	BYTE bySnapSendToCenter;	//联动抓拍上送到中心 qxs 2013.3.7

	/*联动录像*/
	BOOL bRecFlag;	/*是否需要录像*/
	int nRecordTime;/*录像时长*/
	BYTE byRecSendToFTP;/*是否需要上送到FTP*/
	BYTE byRecSendToSD;/*录像时间上送到SD（新增）*/

	/*联动云台*/
	BOOL bLinkPtzFlag;	/*是否需要联动云台*/
	BYTE byLinkPtzType;	/*联动操作类型, 0:预置点，1：扫描，2：巡航，3：轨迹*/
	BYTE byLinkPtzValue;/*对应预置点号/扫描线ID/巡航ID/轨迹ID（新增）*/

	BYTE reserved[29];
}__PACKED__;
typedef struct _TComLinkage TComLinkage;

struct _TNetSet
{
	TWiredNetPara 	WiredNetPara;/*有线网络参数*/
	TNetBasePara 	NetBasePara;/*网络基本参数*/
	TNetSmtpSet 	NetSmtpSet;/*邮件*/
	TNetFtpSet		NetFtpSet;/*FTP参数*/
	TNetDdnsSet		NetDdnsSet;/*DDNS参数*/
	TNetPppoeSet	NetPppoeSet;/*PPPOE参数*/
	
}__PACKED__;
typedef struct _TNetSet TNetSet;//网络设置

/*在线用户信息*/
struct _TOnlineUser           
{     
     char Name[USER_NAME_LEN+1];//用户名称
     char  IpAddr[IPADDR_LEN+1];//iP地址
     TTime  loadtime;//用户登录时间
     char Reserved[5];
}__PACKED__; 
typedef struct _TOnlineUser TOnlineUser;

/*在线用户列表*/
struct _TOnlineUserList
{  
   BYTE  OnlineNum;//在线用户数
  TOnlineUser  OnlineUser[MAX_ONLINE_NUM];
}__PACKED__;
typedef struct _TOnlineUserList   TOnlineUserList;

// 0.eStatusType = STATUS_SD时
//dwStatus1:0,SD不存在;1,SD卡存在;2,SD卡未格式化;3,SD卡文件系统错误;4.SD卡只读;5.SD卡格式化中；6.SD卡文件系统修复中; 7. 操作完成，等待设备重启。8.错误，请手动重启
//dwStatus2:已使用空间(MB);dwStatus3:总空(MB)
// 1.eStatusType = STATUS_LOGIN时
//dwStatus1表示当前登录用户数目，dwStatus2表示最大用户数；
// 2.eStatusType = STATUS_UPDATE时
//dwStatus1：0，文件发送中；1，发送文件完成；2、升级结束；dwStatus2：错误码；
//例：升级成功时，eStatusType = STATUS_UPDATE，dwStatus1=2，dwStatus2=0
// 3.eStatusType = STATUS_FORMAT_DISK时
//dwStatus1为true表示格式化成功，flase表示格式化失败；
// 4.eStatusType = STATUS_CPU_MEM_INFO时
//dwStatus1：CPU占用率*1000；dwStatus2：内存占用率*1000；如：555为55.5%
// 5.eStatusType = STATUS_PTZ_TRAJECTORY_INFO
// 6.eStatusType = STATUS_RECORD_DOWN dwStatus1,dwStatus2,dwStatus3都为0，表示下载成功
// 7.eStatusType = STATUS_REBOOT时 
//dwStatus1:重启原因。0,保留;1,手动重启;2,定时重启,3,SD卡恢复;4,SD卡格式化;5,IP修改;6,分辨率修改
// 8.eStatusType = STATUS_REPAIR_DISK_FS时
//dwStatus1为1表示SD卡修复成功，0表示SD卡修复失败；
//10.eStatusType = STATUS_PTZ_ANGLE_INFO时
//dwStatus1 一个浮点值表示目前球机安装的倾斜角度
//dwStatus2 一个浮点值表示目前球机垂直方向和PTZ 的垂直角度的差值也就是校准值
struct  _TSystemStatus
{
	enStatusType enType;	//系统状态类型
	DWORD dwStatus1;     //状态一
	DWORD dwStatus2;     //状态二
	DWORD dwStatus3;     //状态三
	BYTE Reserved[16]; 	//保留字节
}__PACKED__;
typedef struct _TSystemStatus  TSystemStatus;

/*added by zengqingfeng 20130202*/
struct _TPtzParam
{
	BYTE bPtzParamValue;/*预置点0~255,扫描号1-3，轨迹号1-6，巡航号1-7*/
	char chPtzParamName[MAX_OPERATION_NAME_LEN+1];
}__PACKED__;
typedef struct _TPtzParam TPtzParam;

/*added by hy 20140321*/
struct _TNetDiscoverPack
{	
	TWiredNetPara 	WiredNetPara;/*有线网络参数*/

	char		DeviceName[SERVER_NAME_LEN+1];//SERVER_NAME_LEN=32
	char        ProductModel[MAX_PRODUCT_MODEL_LEN+1];//MAX_PRODUCT_MODEL_LEN=32
	WORD        wBiosVer; // BIOS version
	WORD        wNetVer;  // Network protocol version
	WORD		wElecBoardVer;//电控板版本
	BYTE		byGB28181Enable;/*GB28181是否启用,=0:不启用；=其他:启用*/
	BYTE		byStorageEnable;/*SD卡断线录像是否启用,=0:不启用；=其他:启用*/
	BYTE        bySdCardState;//SD卡安装状态
	WORD		wCameraVer;//机芯版本
	WORD		wMainMcuVer; // 主MCU版本
	WORD		wSlaveMcuVer; //从MCU版本
	char		chBuildDate[10];/*编译日期:20180926*/
	BYTE		reserved[176-20];
}__PACKED__;
typedef struct _TNetDiscoverPack TNetDiscoverPack;

struct _TNetDiscoverSetPack
{	
	char          LoginName[USER_NAME_LEN+1];	//设置时需要验证用户名和密码
	char          LoginPsw[USER_PSW_LEN+1];
	TWiredNetPara 	WiredNetPara;/*有线网络参数*/
	char		DeviceName[SERVER_NAME_LEN+1];
	char        ProductModel[MAX_PRODUCT_MODEL_LEN+1];
	WORD        wBiosVer; // BIOS version
	WORD        wNetVer;  // Network protocol version
}__PACKED__;
typedef struct _TNetDiscoverSetPack TNetDiscoverSetPack;


struct _T3DPtz	//坐标需要换算为CIF使用,即X小于等于352，Y小于等于288
{	
	BYTE	byPtzCtrlType;		//云台控制命令类型
	WORD	wStartPoint_X;		//起始点X坐标
	WORD	wStartPoint_Y;		//起始点Y坐标
	WORD	wEndPoint_X;		//结束点X坐标
	WORD	wEndPoint_Y;		//结束点Y坐标
}__PACKED__;
typedef struct _T3DPtz T3DPtz;

typedef enum
{
	RSCMD_PostMonData        = 80003001, //上送媒体流数据
}enRSNetCmd;

struct _TRSCmdHead
{
	DWORD dwMagicCode; // Always be NETWORK_MAGIC_CODE
	DWORD dwSize;       // Total packet size, including TCmdHead & Cmd Data
	DWORD dwCmdId;      // command id
	WORD wRSType;		//RS类型
	WORD wRSCount;		//RS单元数
	WORD wRSUnitLen;	//RS单元长度
	WORD wGuardStrLen;	//安防字串长度
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
	//bit0:1表示帧的最后一包;
	//bit1-3:000表示I帧，001表示P帧，100表示音频
	//bit[7:4]保留，默认为0
	BYTE byFlag;	
	BYTE MonBlockType; // enMonBlockType
	WORD VidFrmNum;    // Video frame number that this packet is related to
	DWORD secCapTime;//采集时间 的秒部分
	DWORD usecCapTime;//采集时间 的微秒部分
	DWORD FrameLen;
}__PACKED__;
typedef struct _TMonCfg TMonCfg;


/*plate detection struct*/
struct _TEventPlatedetection
{
	BYTE byEnable;			    //	1 bytes	是否启用该事件
	WORD wPalateWidthMin;	    //	2 bytes	最小车牌识别宽度
	WORD wPalateWidthAvg;	    //	2 bytes	平均车牌识别宽度
	WORD wPalateWidthMax;	    //  2 bytes	最大车牌识别宽度
	WORD wRgnX;			//	2 bytes	X坐标
	WORD wRgnY;			//	2 bytes	Y坐标
	WORD wRgnW;			//	2 bytes	宽度
	WORD wRgnH;			//	2 bytes	高度

}__PACKED__;/*15bytes*/
typedef struct _TEventPlatedetection TEventPlatedetection;

/****************************************************************************************/
/***********************                                       **************************/
/***********************  Request and Answer Command Structs   **************************/
/***********************                                       **************************/
/****************************************************************************************/

/*请求获取参数 命令通用结构体*/
struct _TReqGetCMD
{
	TCmdHead head;
}__PACKED__;
typedef struct _TReqGetCMD TReqGetCMD;

/*回复设置参数 命令通用结构体*/
struct _TAswSetCMD
{
	TCmdHead head;
	int nResult;
}__PACKED__;
typedef struct _TAswSetCMD TAswSetCMD;





/*请求登录*/
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
	int nDisconnectTime;//断线超时时间，设置为0表示默认值30000毫秒
	BYTE Reserved[66];
}__PACKED__; // Total 128 bytes
typedef struct _TReqLogin TReqLogin;

/*应答登录*/
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
	int			  nSockID;			//命令链路与媒体链路配对ID

	BYTE          Reserved2[104];

}__PACKED__; // Total 512 bytes
typedef struct _TAswLogin TAswLogin;


/*请求注销*/
struct _TReqLogout
{
	TCmdHead head;
}__PACKED__;
typedef struct _TReqLogout TReqLogout;


/*请求流*/
struct _TReqMon
{
	TCmdHead head;
	BYTE ChanNum;
	BYTE bStreamType; //0:主码流1:次码流2:音频3:yuv422 4:RGB
	BYTE bOpen;

	enMonTranMode enTranMode;
	BYTE	IP[4];
	/*用于点流时指定的IP地址 UDP或者组播时 高字节在前低字节在后例如192.168.30.64
	表示为IP[0]=0xC0; IP[1]=0xA8; IP[2]=0x1E; IP[3]=0x40; 
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


/*请求获取用户列表*/
struct _TReqGetUserList
{
	TCmdHead head;
}__PACKED__;
typedef struct _TReqGetUserList TReqGetUserList;


/*获取用户列表应答*/
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


/*请求系统日志*/
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


/*云台控制*/
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


/*手动告警*/
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


/*请求升级*/
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


/*停止发送升级文件*/
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


/*获取设备信息*/
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


/*请求I帧*/
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


/*搜索SD卡文件*/
struct _TReqSrchSDFile
{
	TCmdHead head;
	BYTE ChanNumMask; // Channels to search, 1 bit 1 channel
	BYTE bFileTypeMask; /*0x01:picturr file,0x02:rec file*/
	BYTE bFileSubTypeMask;/*0x01:alarm rec/pictur file,0x02:timing rec/pictur file,0x04:manual rec/pictur file*/
	WORD wAlarmTypeMask;/*告警类型，见enAlarmType*/
	TTime BegTime;/*查询起始时间*/
	TTime EndTime;/*查询接收时间*/
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
	WORD wAlarmTypeMask;/*告警类型，见enAlarmType*/
	TTime BegTime;/*查询起始时间*/
	TTime EndTime;/*查询接收时间*/
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
	/*用于点流时指定的IP地址 UDP或者组播时 高字节在前低字节在后例如192.168.30.64
	表示为IP[0]=0xC0; IP[1]=0xA8; IP[2]=0x1E; IP[3]=0x40; 
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


/*sd卡操作*/
struct _TReqDiskMaintain
{
	TCmdHead head;
	char DiskPath[MAX_REC_FILE_PATH+1];
	BYTE MaintainType;//0：保留；1：格式化2：恢复SD文件系统（仅SD有效）
}__PACKED__;
typedef struct _TReqDiskMaintain TReqDiskMaintain;

struct _TAswDiskMaintain
{
	TCmdHead head;
	int nResult;
	// Client original request parameters
	char DiskPath[MAX_REC_FILE_PATH+1];
	BYTE MaintainType;//0：保留；1：格式化2：恢复SD文件系统（仅SD有效）
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


/*获取告警信息*/
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


/*IP过滤*/
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


/*定时抓拍*/
struct _TTimingSnapSet
{
 	BOOL bSnapFlag;	/*是否需要抓拍*/
	BYTE chSnapInterval;	/*抓拍间隔*/
	BOOL bSendToFTP;/*是否需要上送到FTP*/
	BOOL bSendToEmail;/*是否需要上送到Email*/
	TTimingPlanDaySet stTimingSnapPlanCfg[WEEK_MAX_DAY];
	// Reserved bytes, for future extension
	BYTE Reserved[4];
}__PACKED__; 
typedef struct _TTimingSnapSet T_TimingSnapSet;

struct _TPictureSet
{
	enVideoResolution ePicRes;/*图片分辨率*/
	BYTE bPictureQuality;/*图片质量*/
	T_SnapPictureSet stManualAlarmSnapCfg;	/*增加手动报警联动抓拍配置参数*/
	T_TimingSnapSet  stTimingSnapCfg;/*增加定时抓拍配置参数*/

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


/*录像参数*/
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


/*定时录像*/
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


/*OSD字符叠加*/
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



/*遮挡区域设置*/
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



/*图片参数*/
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

	enVideoResolution ePicRes;/*图片分辨率*/
	BYTE bPictureQuality;/*图片质量*/
}__PACKED__;
typedef struct _TAswGetPictureParamSet TAswGetPictureParamSet;


struct _TReqSetPictureParamSet
{
	TCmdHead head;
	BYTE ChanNum;
	enVideoResolution ePicRes;/*图片分辨率*/
	BYTE bPictureQuality;/*图片质量*/
}__PACKED__;
typedef struct _TReqSetPictureParamSet TReqSetPictureParamSet;

struct _TAswSetPictureParamSet
{
	TCmdHead head;
	int nResult;
	BYTE ChanNum;
	// Client original request parameters
	enVideoResolution ePicRes;/*图片分辨率*/
	BYTE bPictureQuality;/*图片质量*/
	// Server answer data

}__PACKED__;
typedef struct _TAswSetPictureParamSet TAswSetPictureParamSet;


/*隐私遮挡告警*/
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


/*移动侦测*/
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



/*IO报警*/
struct _TReqGetProbeDetectSet       
{
	TCmdHead head;
	BYTE chProbeAlarmInChn;/* 输入通道*///qxs 2013.3.6
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
/*SD卡设置*/
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


/*自动重启设置*/
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
/*网络设置--FTP参数*/
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


/*网络设置--邮件*/
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



/*网络设置--DDNS参数*/
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



/*网络设置--PPPOE 参数*/
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


/*系统设置--时间设置*/
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


/*音频参数*/
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


/*串口参数*/
struct _TReqSetComPara
{
	TCmdHead head;
	BYTE	ComNum;//0:COM1;目前只用到COM1
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
	BYTE	ComNum;//0:COM1;目前只用到COM1
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


//串口联动参数	qxs 2013.3.6
struct _TReqSetComLinkage
{
	TCmdHead head;
	BYTE byComNum;//0:COM1;目前只用到COM1
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
	BYTE	byComNum;//0:COM1;目前只用到COM1
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


/*网络设置--有线网络参数*/
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


/*网络设置--基本参数*/
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
	BOOL bNeedRebootToApplay;//是否需要重启
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


/*事件管理--异常处理*/
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


/*系统设置--基本设置*/
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
	BOOL bNeedRebootToApplay;//是否需要重启
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


/*清除系统日志*/
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


/*恢复默认值*/
struct _TReqSetDefaultParam
{
	TCmdHead head;
	BYTE ChanNum;//通道号
	enDefaultParamType eDefaultParamCfg;
}__PACKED__;
typedef struct _TReqSetDefaultParam TReqSetDefaultParam;

struct _TAswSetDefaultParam
{
	TCmdHead head;
	int nResult;
	BYTE ChanNum;
	enDefaultParamType eDefaultParamCfg;
	BOOL bNeedRebootToApplay;//是否需要重启
}__PACKED__;
typedef struct _TAswSetDefaultParam TAswSetDefaultParam;
/*added by zengqingfeng 20120815*/


/*获取在线用户列表*/
struct _TReqGetOnlineUserList
{
    TCmdHead head;
}__PACKED__;
typedef struct _TReqGetOnlineUserList TReqGetOnlineUserList;

struct _TAswGetOnlineUserList     //应答结构体
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


/*获取系统状态*/
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


/*设置ptz参数*/
struct _TReqSetPtzPara
{
	TCmdHead head;
	BYTE bDeviceType;/*设备类型*/
	BYTE bParamNum;/*参数数目*/
	BYTE bPtzParamType;/*0:预置点，1：扫描，2：巡航，3：轨迹*/
	TPtzParam stPtzParam;
}__PACKED__;
typedef struct _TReqSetPtzPara TReqSetPtzPara;

struct _TAswSetPtzPara
{
	TCmdHead head;
	int nResult;
	BYTE bDeviceType;/*设备类型*/
	BYTE bParamNum;/*参数数目*/

}__PACKED__;
typedef struct _TAswSetPtzPara TAswSetPtzPara;


/*设置28181参数*/
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


/*发现设备*/
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


/*设置网络参数*/
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


/*测试命令*/
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
	int nResult;// 4.19修改协议后增加
	BYTE bDevType;/*设备类型*/
	char chData[256];
}__PACKED__;
typedef struct _TAswGetBallMachineCfg TAswGetBallMachineCfg;

struct _TAswGetIPdomeCfg
{
	TCmdHead head;
	int nResult;// 4.19修改协议后增加
	BYTE bDevType;/*设备类型*/
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
	SNAP_TYPE_AUTO	= 1,	/*自动*/
	SNAP_TYPE_MANUAL	= 0,	/*手动*/
	SNAP_YPE_ONESHOT = 2	/*一次*/
} SNAP_OP_TYPE_E;

struct _TSnapOrSetSnapSet
{
	BYTE 		ucOperFlag;/*0：参数设置与读取；1：仅仅抓拍；2：抓拍考虑参数*/
	BOOL 		bSnapFlag;	/*开关 0关闭；1：开启；默认1*/
	BYTE		ucManualFlag;/*0:不抓拍；1：手动触发抓拍 默认0*/
	BYTE		ucAutoGainMode;/*自动增益模式0关闭；1开启 默认1*/
	BYTE  	ucAutoGainVal;/*自动增益门限[0-36] 默认16dB*/
	BYTE  	ucManualGainVal;/*手动增益设置[0-36] 默认16dB*/
	SNAP_OP_TYPE_E		eExposureMode;/*自动曝光0：关闭  1开启 默认1开启*/
	UINT 		uiManualSpeed;/*手动曝光时间[0-80000] 单位1us 默认40000*/
	UINT 		uiAutoSpeed;/*自动曝光门限[0-80000]单位1us默认40000*/
	BYTE		ucFlashEnable;/*闪光灯使能 0关闭 1开启 默认1开启*/
	unsigned short	usFlashDaley;/*闪光灯补光延时[0-65535] 默认0  Na秒？*/
	BYTE		ucConFramCount;/*连续抓拍帧数[1-3] 默认1*/
	BYTE		ucIntvFramCount;/*抓拍间隔帧数*/
	BYTE		ucDealFlag;/*0：不处理1:显示当前抓拍智能分析结果*/
	BOOL 		bSendToFTP;/*是否需要上送到FTP*/
	BOOL 		bSendToEmail;/*是否需要上送到Email*/
	BOOL 		bSaveToSD;/*是否需要保存到SD卡*/
	BOOL 		bSendToCenter;/*是否需要上送到中心通过网络*/
	UINT		uiCoilDistance;/*线圈距离*///FIX ME zhangyt add 2012-12-21
	BYTE 		Reserved[21-4];//FIX ME zhangyt update 2012-12-21

}__PACKED__; //共64个字节
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
*********         增强现实        **********
*********************************************/

/*Yoto add 2014-08-28  for 增强现实坐标校准*/
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

/*增强现实sei信息*/
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

/*文本配置协议*/
struct _TReqSetIni
{
	TCmdHead head;
	DWORD 	  dwOper;// 1设置 2获取
	DWORD    dwFileId;// 1网络2 告警3 语音灵敏度4 速度 5巡逻信标 6 产品导购
	BYTE byIniStr[1];
}__PACKED__;
typedef struct _TReqSetIni TReqSetIni;

struct _TAswSetIni
{
	TCmdHead head;
	DWORD 	  dwOper;// 1设置 2获取
	DWORD    dwFileId;//  1网络2 告警3 语音灵敏度4 速度 5巡逻信标 6 产品导购
	int nResult;
	BYTE byIniStr[1];
}__PACKED__;
typedef struct _TAswSetIni TAswSetIni;
/********************************************
***********        4G设备        ***********
*********************************************/

/*4G无线参数设置和获取*/
struct _TWirelessCfg
{	
	int          nEnable;	//无线网络模块总开关
	int          nStreamType; //流类型
	char 	     chApn[32];//APN接入点
	unsigned char  ucConnetMode;//连接模式
	unsigned char  ucConnetorder;//连接顺序
	char        chCenterIP[17];//中心服务器IP
	int         nServerPort; // 中心服务器端口
	int        nCheck;  // 校验方式
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
***********        北斗设备        *********
*********************************************/

/*北斗定位参数配置*/
struct _TBdLocationInfo
{
	char chCenterName[33];//中心地标名称
	BYTE byEW;//1西经，2东经
	BYTE bySN;// 1北纬，2南纬
	UINT unLongitude;//经度 单位度，实际数据*1000000
	UINT unLatitude;//纬度 单位度，实际数据*1000000
	BYTE byReserved[21];//保留字节
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
***********       卡口设备       ***********
*********************************************/

/*车牌识别库设置与获取*/
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


/*抓拍记录查询*/
struct _TReqSnapRecordGet
{
	TCmdHead head;
	BYTE           bySnapFlag;          //图片抓拍标志，0表示停止查询；1表示开始查询 
	long long      nStartTime;          //图片抓拍开始时间，单位秒
	long long      nStopTime;           //图片抓拍结束时间，单位秒
	BYTE           bySnapType;          //图片抓拍类型，0表示普通图片，1表示车牌识别
	BYTE           SnapContext[128];    //根据图片抓拍不同类型有不同的内容
}__PACKED__;
typedef struct _TReqSnapRecordGet TReqSnapRecordGet;

struct _TAswSnapRecordGet
{
	TCmdHead head;
	int nResult;
	int nRecordTotelNum;//查询到的图片抓拍记录总条数 
}__PACKED__;
typedef struct _TAswSnapRecordGet TAswSnapRecordGet;

struct _TReqSnapStorageGet
{
	TCmdHead head;
	unsigned int   sec;                 //抓拍时间 单位秒
	unsigned int   usec;                //抓拍时间 单位微秒
	BYTE           bySnapType;          //图片抓拍类型，0表示普通图片，1表示车牌识别
}__PACKED__;
typedef struct _TReqSnapStorageGet TReqSnapStorageGet;

struct _TAswSnapStorageGet
{
	TCmdHead head;
	int nResult;
	int nSnapTotelNum;//文件总包数
}__PACKED__;
typedef struct _TAswSnapStorageGet TAswSnapStorageGet;



/********************************************
***********       P2P小球        ***********
*********************************************/

/*桌面小球wifi参数的获取和设置*/
struct _TWIFISet
{
	BYTE 	bEnable;/*0：禁用；1：启用*/
	char    chRouterName [33];
	char	chPassword[33];/* */
	int		nConnectStatus;
	int		nSignalStrength;
	int  	nIPMode;/* */
	char  	chIPAdr[17];/* */
	char	chIPMask[17];
	char	chGateWay[17];
}__PACKED__; //共130个字节
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

/*路由器列表的获取*/
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
	BYTE  nListNum;/*列表项总数*/
	BYTE  byRouterData[0];
}__PACKED__;
typedef struct _TAswGetRouterList TAswGetRouterList;


/*计划录像参数配置*/
struct _TRecPlanSet
{
	BYTE 	bEnable;/*0：禁用；1：启用*/
	BYTE	chRecTime[42];/*每6个字节代表1天*/
}__PACKED__; //共43个字节
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
***********       筒机设备       ***********
*********************************************/
struct _TLensParam
{
	TCmdHead head;
	BYTE bType;//设置参数类型，1表示设置镜头初始化，2表示设置一键聚焦
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
	BYTE PackNum;	//当前包序号
	BYTE bLastPack;//是否最后一包
	int nSysLogNum;//应答包中日志数目
	BYTE SysLogData[1];//内容按照"_TSysLog"格式存储
}__PACKED__;
typedef struct _TPostSysLog TPostSysLog;
typedef struct _TPostSysLog *TPostSysLogPtr;


struct _TPostMonData
{
	TCmdHead head;
	//bit0:1表示帧的最后一包;
	//bit1-3:000表示I帧，001表示P帧，100表示音频
	//bit[7:4]保留，默认为0
	BYTE byFlag;	
	BYTE MonBlockType; // enMonBlockType
	WORD VidFrmNum;    // Video frame number that this packet is related to
	DWORD secCapTime;//采集时间 的秒部分
	DWORD usecCapTime;//采集时间 的微秒部分

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
	int nFileCnt;/*总的个数*/
	int nCurrentCnt;/*当前包最后一条记录的序号*/
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
	int nDownloadFileID;/*下载文件的ID*/
	char FilePath[MAX_DOWNLOAD_FILE_PATH+1];/*下载文件的名称*/
	BYTE bPackNum;	/*当前包序号*/
	BYTE bTotalPack;/*总的包数*/
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
	int nCmdSockID;				//命令SOCKET的ID，登陆设备时返回
}__PACKED__;
typedef struct _TPostStreamHeartbeat TPostStreamHeartbeat;

/***********start added by zhangyt 2014-05-21********************/
struct _TClientDevInfo
{
	BYTE	ucCSQType;//15:3G  17:4G
	BYTE	ucCSQValue;
	BYTE 	ucConStatus;// 1:未注册2:拨号中;3:连接正常 此为无线连接状态 不是和中心的通信状态
	BYTE 	ucModeStatus;// 0成功 1失败
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


/*4G无线状态上送*/
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


/*gps参数上送结构体*/
struct _TGpsInfoUpSend
{
	BYTE  byValid;//定位标志:0无效,1有效
	BYTE  byEW;//1西经，2东经
	BYTE  bySN;// 1北纬，2南纬
	UINT  unLongitude;//经度 单位度，实际数据*1000000
	UINT  unLatitude;//纬度 单位度，实际数据*1000000
	int   nASL;//海拔	单位米，实际数据*100
	UINT  unSpeed;//速度	单位km/h，实际数据*1000
	TTime sTime; //时间
	BYTE byReserved[38];//保留字节
}__PACKED__;
typedef struct _TGpsInfoUpSend TGpsInfoUpSend;

struct _TPostGpsInfo
{
	TCmdHead head;
	TGpsInfoUpSend	tInfo;
}__PACKED__;
typedef struct _TPostGpsInfo TPostGpsInfo;


/*抓拍时间上送*/
struct _TPostSnapContextBase
{
	unsigned int sec;               //抓拍时间 单位秒
	unsigned int usec;              //抓拍时间 单位微秒
}__PACKED__;
typedef struct _TPostSnapContextBase  TPostSnapContextBase;

struct _TPostSnapContextPlate
{
	unsigned int sec;               //抓拍时间 单位秒
	unsigned int usec;              //抓拍时间 单位微秒
    BYTE    nPlateNum;              //车牌数
	BYTE    acPlateCode[3][10];     //车牌号码
}__PACKED__;
typedef struct _TPostSnapContextPlate  TPostSnapContextPlate;
typedef struct _TPostSnapContextPlate *TPostSnapContextPlatePtr;
	
struct _TPostSnapData
{
	TCmdHead head;
	int nSnapType;          //文件类型   0表示普通图片 1表示车牌图片 2...
	int nSnapSuffix;        //文件后缀名 1表示jpeg 2表示png 3...
	int nSnapTotelNum;      //文件总包数
	int nSnapCurNum;        //文件当前包数
	BYTE SnapContext[128];  //根据不同类型有不同的内容
	BYTE SnapData[0];       // File data
}__PACKED__;
typedef struct _TPostSnapData TPostSnapData;

/*wifi状态上送*/
struct _TPostWIFIStatus
{
	TCmdHead head;
	int nSignalStrength;//信号强度
	int nConnectStatus;//连接状态
	BYTE Reserved[16];//保留
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

// Telnet 功能状态   2015.7.7
struct _TSetTelnetStatus
{
	TCmdHead head;
	BYTE   byopen;              // 0:关闭  1:启动
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
	char DeviceSerial[DEVICE_SERIAL_LEN+1];//序列号，DEVICE_SERIAL_LEN=16
	char IpAddr[IP_ADDR_LEN+1];//IP_ADDR_LEN=15
    int  IpPort;
	BYTE reserved[100];
}__PACKED__;
typedef struct _TGetCenterServer TGetCenterServer;

struct _TSetCenterServer
{
	TCmdHead head;
	char DeviceSerial[DEVICE_SERIAL_LEN+1];//序列号，DEVICE_SERIAL_LEN=16
	char IpAddr[IP_ADDR_LEN+1];//IP_ADDR_LEN=15
    int  IpPort;
	BYTE reserved[100];
}__PACKED__;
typedef struct _TSetCenterServer TSetCenterServer;

struct _TSetAISwitchEnable
{
    TCmdHead head;
    unsigned char bFDEnable; //人脸侦测开关
    BYTE reserved[100];
}__PACKED__;
typedef struct _TSetAISwitchEnable TSetAISwitchEnable;



//设置、获取机器人巡逻路径配置
struct _TReqRobotRouteDetailSet
{
	TCmdHead head;
	unsigned int u8RouteID; //范围0至 3
	unsigned int unXunBiaoID[50];
	unsigned int u32NearChargingPointID;
	unsigned int u32ChargingPointID;
}__PACKED__;
typedef struct _TReqRobotRouteDetailSet TReqRobotRouteDetailSet;

//请求机器人巡逻路径请求结构体
struct _TReqRobotRouteDetailGet
{
	TCmdHead head;
	unsigned int u8RouteID; //范围0至 3
}__PACKED__;
typedef struct _TReqRobotRouteDetailGet TReqRobotRouteDetailGet;

struct _TAswRobotRouteDetailGet
{
	TCmdHead head;
	int   nResult;
	unsigned int u8RouteID; //范围0至 3
	unsigned int unXunBiaoID[50];
	unsigned int u32NearChargingPointID;
	unsigned int u32ChargingPointID;
}__PACKED__;
typedef struct _TAswRobotRouteDetailGet TAswRobotRouteDetailGet;

struct _TPostXinBiaoArrival
{
	TCmdHead head;
	char szData[100];
	unsigned char u8Flag; // 1-进入；0-离开
}__PACKED__;
typedef struct _TPostXinBiaoArrival TPostXinBiaoArrival;

struct _TGuomaiDeviceInfo
{
	char deviceID[32];   // 设备ID
	char password[32];    // 注册平台的密码(太保平台的勘查员6位随机码)
	char name[128];			// 名称长度
	char deviceName[256]; // 设备名称
	char serialNumber[256]; // 设备名称
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
	char deviceID[32];   // 设备ID
	char time[64];         // GPS采样时间
	char divisionEW[64];   // E-东半球,W-西半球
	char longitude[64];    // 经度
	char divisionNS[64];   // N-北半球,S-南半球
	char latitude[64];     // 纬度
	char direction[64];    // 方向
	char speed[64];        // 速度
	int radius;           //卫星数量
	int battery;          //电量（百分比（1-100））
	int signal;           //信号强度（1-100）
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
	char cData[0];//棰勭暀1M绌洪棿
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
	int nOperator;			//运营商1:移动 2:联通 3:电信	
	int nNetType;			//0-1 无;  2:2G  3:3G； 4:4G	
	int nSignal;			//信号强度 0-100    0无信号 100最大
	int nBattery;			//电量信息 百分比0-100
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
    int nVidStream; //视频流状态: 0正常 1异常
    int nCenterLink; //中心链接状态: 0正常 1异常
    BYTE reserved[100];
}__PACKED__;
typedef struct _TGetAIServerStatus TGetAIServerStatus;
struct _TReqRobotParamSetGet
{
	TCmdHead 		head;
	int				nSn;	//命令对应编号
	char			creserved[12];//预留字段
	unsigned int 	unRobotCmd;//机器人相关命令ID
	char			cData[0];//机器人对应的相关结构体
}__PACKED__;
typedef struct _TReqRobotParamSetGet TReqRobotParamSetGet;


struct _TAswRobotParamSetGet
{
	TCmdHead 		head;
	int				nResult;//应答标志
	int				nSn;	//命令对应编号
	char			creserved[12];//预留字段
	unsigned int 	unRobotCmd;//机器人相关命令ID
	char			cData[0];//机器人对应的相关结构体
}__PACKED__;
typedef struct _TAswRobotParamSetGet TAswRobotParamSetGet;

struct _TPushOnRobotInfo //主动上送
{
	TCmdHead 		head;
	unsigned int 	unRobotCmd;//机器人相关命令ID
	char			cData[0];//机器人对应的相关结构体
}__PACKED__;
typedef struct _TPushOnRobotInfo TPushOnRobotInfo;


struct _TPushDownRobotInfo //主动下发
{
	TCmdHead 		head;
	unsigned int 	unRobotCmd;//机器人相关命令ID
	char			cData[0];//机器人对应的相关结构体
}__PACKED__;
typedef struct _TPushDownRobotInfo TPushDownRobotInfo;




struct _TReqWifiConnStatus
{
    TCmdHead head;
    unsigned char status; // 0表示断开， 1表示连接
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
