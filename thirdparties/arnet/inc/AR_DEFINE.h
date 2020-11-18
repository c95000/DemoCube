#ifndef AR_DEF_H
#define AR_DEF_H

#ifdef WIN32

#else

#define SDK_API 
//typedef unsigned long long UINT64;
//
//typedef void *PVOID;
//typedef void *LPVOID;
//typedef const char* LPCSTR;
//typedef char  TCHAR;
//typedef char* LPSTR;
//typedef char* LPTSTR;
//typedef const char* LPCTSTR;
//typedef unsigned int UINT;
//typedef unsigned int DWORD;
//typedef int      BOOL;
//typedef unsigned char       BYTE;
//typedef unsigned short      WORD;
//typedef unsigned int        *PUINT;
//typedef long        LONG;
//
//#ifndef NULL
//#define NULL 0
//#endif
//#ifndef TRUE
//#define TRUE true
//#endif
//#ifndef FALSE
//#define FALSE false
//#endif
#define CALLBACK  

#endif //WIN32

typedef enum
{
	AR_LABLE_POINT = 0,/*point 点*/
	AR_LABLE_VECTOR = 1,/*多点向量*/
	AR_LABLE_POLYGON = 2,/*多边形*/
	AR_LABLE_LINE = 3,/*线段*/
	AR_LABLE_BINVECTOR = 4,/*双向两点*/
	AR_LABLE_OVAL = 5,/*椭圆*/
	AR_LABLE_DIMENSION = 6	/*3维*/
}AR_Type;/*标签类型*/

typedef enum
{
	AR_OP_ADD,
	AR_OP_DELETE,
	AR_OP_UPDATE,
	AR_OP_POST
}AR_OPERATION;

#define AR_CONTENT_LEN	2048
#define AR_LEN_256		256
#define AR_LEN_32		32
#define AR_LEN_8		8

#define ARRET_LABLECOUNT_TOMAX -1000 //标签数量已达最大值
#define ARRET_WRONG_PARAMETER  -1001 //参数错误
#define ARRET_MALLOC_FAILED  -1002 //内存分配失败
#define ARRET_NULL_POINTER  -2001 //空指针参数错误
#define ARRET_INVALID_SEIPACK  -2002 //无效的sei包
#define ARRET_INVALID_XMLPACK  -2003 //无效的xml包
#define ARRET_INVALID_LABLEID  -2004 //无效的标签id
#define ARRET_BUF_TOOSMALL  -2005 //缓存太小
#define ARRET_NONEXIST_XMLNODE  -2006 //访问不存在的xml node
#define FACE_FEATURE_MAX_AR 320

typedef struct
{
	int	x;
	int	y;
}AR_POS;

/*标签属性结构体*/
typedef struct
{
	AR_Type eType;//目前只支持LABLE_TYPE_POINT
	int nID;
	int nLevel;//所在层数
	AR_POS	stPos;//标签的标点pos
	char chContent[AR_CONTENT_LEN];//一级标签
	char chSubContent[AR_CONTENT_LEN];//二级标签
	char chLink[AR_LEN_256];//链接地址
	char chCmdLine[AR_LEN_256];//命令行
}AR_Lable;

typedef struct
{
	AR_Type eType;//目前只支持LABLE_TYPE_POINT
	int nID;
	int nLevel;//所在层数
	AR_POS	stPos[20];//标签的标点pos数组
	int nPosNum;//实际的标点个数
	char chContent[AR_CONTENT_LEN];//一级标签
	char chSubContent[AR_CONTENT_LEN];//二级标签
	char chLink[AR_LEN_256];//链接地址
	char chCmdLine[AR_LEN_256];//命令行
}AR_LableEx;

typedef struct
{
	int  bAuto;//自动获取传感器数据,仅配置时使用
	float fPan;/*水平角度相对于正北方向逆时针+顺时针-*/
	float fTilt;/*垂直方向角度相对于水平线0度逆时针+顺时针-*/
	float fAngleH;/*水平张角*/
	float fAngleV;/*垂直张角*/
	float fDistance;//测距距离
}AR_PTZ;

typedef struct
{
	float fDeltT;//校准T值
	float fHeight;//计算的球机距地面高度
	float fRadius;//当前参考区域的半径
	float fPan;//当前参考点的P值
	float fTilt;//当前参考点的T值
}AR_Reference;

typedef struct
{
	unsigned short wYear;
	unsigned char byMonth;
	unsigned char byDay;
	unsigned char byHour;
	unsigned char byMin;
	unsigned char bySec;
	unsigned short wMilliSec;
}AR_TIME;

typedef struct
{
	int  bAuto;//自动获取传感器数据,仅配置时使用
	float fLongitude;/*经度值E+; W-*/
	float fLatitude;/*纬度N+; S-*/
	float fAltitude;/*海拔*/
}AR_LOCATION;

typedef enum
{
	DEV_AR_IPC,//增强现实枪机
	DEV_AR_IPCDOME//增强现实球机
}enARDeviceType;

typedef struct
{
	AR_PTZ			stPtz;
	AR_LOCATION	stLocation;
	AR_TIME		stTime;//时间戳
	enARDeviceType	eDeviceType;
	char			chVer[AR_LEN_8];//版本号1.00
	char			chDevModel[AR_LEN_32];//设备型号
}AR_Param;

typedef struct
{
	//AR_PTZ			stPtz;
	unsigned int           dwTime; // 图片生成时间
	int             nX; //图片在视频中的X坐标（坐标范围是1920*1080）
	int             nY;//图片在视频中的Y坐标
	int				nWidth;//图片的宽度
	int				nHeight;//图片的高度
	int           nFrameW;//视频帧的宽度
	int           nFrameH;//视频帧的高度

	unsigned char  nGender;
	unsigned char  nAge;
	unsigned char  nExpression;
	unsigned char  nComplexion;
	unsigned char  nClothes;
	char*           pData; //图片数据地址
	int             nDataLen;//图片数据长度
	int				nFeatureCount;//人脸特征点个数
	char cFaceFeature[FACE_FEATURE_MAX_AR * 10];
}AR_Picture;

typedef struct
{
	double dOriginLongitude; //球机的经度 E+; W-
	double dOriginLatitude; //球机的纬度 N+; S-
	double dTargetLongitude; //目标的经度 E+; W-
	double dTargetLatitude; //目标的纬度 N+; S-
	double dHeight; //相对高度
}AR_GPS_Info;

typedef struct
{
	AR_Picture	stPicture[100];//图片数组
	int nPictureNum;//实际图片个数
}AR_PictureArray;

#define DetFaceNum 256
typedef struct {
	int         id;         /* object ID, NOTE: reserved */
	int         type;       /* object type */
	unsigned int        x;          /* x-position in pixels (top left corner) */
	unsigned int        y;          /* y-position in pixels (top left corner) */
	unsigned int        width;      /* Size in pixels (along x-direction) */
	unsigned int        height;     /* Size in pixels (along y-direction) */
	int         yaw;        /* angle (yaw, 0 ~ 180 degrees) */
	int         tilt;       /* tilt (roll, 0 ~ 180 degrees) */
	int         pitch;      /* pitch (0 ~ 180 degrees) */
	int         nthumbs;    /* Number of thumbnails associated with this object, NOTE: reserved */
	int           life;       /* tracked object life, NOTE: reserved */
	int      nparents;  /* number of parents */
	float           strength;   /* detected object strength */
}IngDetObject;

typedef struct
{
	IngDetObject DetObject[DetFaceNum];
	int DetObjectNum;
	int iTraceId;
}DetectInfo;


//Description:增强现实原始数据回调函数
typedef void (CALLBACK* fARRawDataCBFun)(void* handle, unsigned char *pARRawData, int  nDataSize, void* pUser);

//Description:设置增强现实回调函数
typedef void (CALLBACK* fARCBFun)(void* handle, unsigned char  *pXML, int  nSize, void* pUser);

//Description:增强现实图片回调函数类型
// Parameters:
// [in] handle:视频播放句柄
// [in] pSei:图片信息
// [in] nNum：表示pSei的个数
// [in] nUser: 用户数据
// Return：无
typedef void (CALLBACK* fARPictureCBFun)(void* handle, AR_Picture  *pSei, int nNum, void* pUser);

//Description:	全局的增强现实图片回调函数类型
// Parameters:
// [in] handle:视频播放句柄
// [in] pSei:图片信息
// [in] nNum：表示pSei的个数
// [in] nUser: 用户数据
// Return：无
typedef void (CALLBACK* fGlobalARPictureCBFun)(char *szDeviceID, AR_Picture  *pSei, int nNum, void* pUser);

//Description:设置增强现实标签回调函数
// Parameters:
// [in] handle:视频播放句柄
// [in] ARLableCBFun: 标签回调函数
// [in] nUser：用户数据
// Return：成功返回TRUE; 失败返回FALSE
typedef void (CALLBACK* fARLableCBFun)(void* handle, AR_OPERATION nOperation, AR_Lable  *pSei, int nNum, void* pUser);

//Description:增强现实参数回调函数类型
// Parameters:
// [in] handle:视频播放句柄
// [in] pParam: 参数信息
// [in] nUser: 用户数据
// Return：无
typedef void (CALLBACK* fARParamCBFun)(void* handle, AR_Param  *pLable, void* pUser);

//Description:增强现实标签回调函数类型
// Parameters:
// [in] handle:视频播放句柄
// [in] nOperation: 操作类型
// [in] pSei:标签信息
// [in] nNum：表示pSei的个数
// [in] nUser: 用户数据
// Return：无
typedef void (CALLBACK* fARLableExCBFun)(void* handle, AR_OPERATION nOperation, AR_LableEx  *pSei, int nNum, void* pUser);


//主动上送 温度，湿度，电池电量信息
struct _CAR_POST_BASE_INFO_T
{
	short nTemperature; //温度，实际温度乘以10，例如375表示37.5度
	unsigned short nHumidity;    //湿度，实际湿度乘以10，例如375表示37.5%
	unsigned char u8Battery;     //电池电量 百分比
	unsigned char u8HumidityAlarm;//湿度报警，0表示无，1表示有
	unsigned char u8OutPutPower; //输出功率， 百分比
	unsigned short u16PM25; //PM2.5 单位：ug/m^3
	unsigned short u16PM10; //PM1.0 
};
typedef struct _CAR_POST_BASE_INFO_T CAR_POST_BASE_INFO_T;

//主动上送姿态信息
struct _CAR_POST_POSITION_INFO_T
{
	unsigned short u16CarDirect; //车身朝向 正北为0，顺时针递增，360度
	short s16CarPitch; //小车倾角,-180~180度
	unsigned char au8RoadBlock[6]; //障碍物 每个块对应的字节，填充的是障碍物距离情况，距离情况分4种，0表示无，1表示远，2表示中，3表示近。
	short s16SoundDirect; //音源位置 角度，车身前进方向为0度，顺时针递增，360度，-1表示没有。
	unsigned char u8CurCarMode; //小车当前控制模式 0-自动巡逻;1-手动控制;2-充电模式;3-跟随模式
};
typedef struct _CAR_POST_POSITION_INFO_T CAR_POST_POSITION_INFO_T;

// 自动巡逻状态上送
struct _CAR_POST_AUTOWALK_INFO_T
{
	unsigned char u8RouteID;      //巡逻路线
	unsigned char u8NewRouteId;//表示界面设置的最新的路线ID，
							   //如果RouteId与NewRouteId不一致，表示界面改变了路线，此时界面应当提示："正在切换路线RouteId到NewRouteId，等待机器人返回01点
	unsigned short u16PreXBID;   //上一个信标
	unsigned short u16NowXBID;  //起始信标
	unsigned short u16NextXBID;    //目的信标
	unsigned char u8Status;     //到达状态,30%,取30
};
typedef struct _CAR_POST_AUTOWALK_INFO_T CAR_POST_AUTOWALK_INFO_T;

//报警信息，0表示没有报警，1表示有报警
struct _CAR_ALARM_INFO_T
{
	unsigned char u8TemperatureAlarm; //温度度报警
	unsigned char u8HumidityAlarm; //湿度报警
	unsigned char u8PM25Alarm; //PM2.5报警
	unsigned char u8PM10Alarm; //PM1.0报警
	unsigned char u8HangAlarm; //悬挂报警
	unsigned char u8TumbleAlarm; //跌倒报警	
};
typedef struct _CAR_ALARM_INFO_T CAR_ALARM_INFO_T;

//小车开关量
struct _CAR_SWITCH_T
{
	unsigned char u8LedLightEnable; //耳朵闪光灯
	unsigned char u8SpeechRecognitionEnable; //语音识别
	unsigned char u8HangAlarmEnable; //悬空报警
	unsigned u32SoundSrcEnable; //开启音源定位 1开，0关
	unsigned u32AIEnable; //开启人脸识别
};
typedef struct _CAR_SWITCH_T CAR_SWITCH_T;

struct _CAR_OTHER_T
{
	unsigned char u8CarStatus; //小车状态， 0-正常，1-充电中
};
typedef struct _CAR_OTHER_T CAR_OTHER_T;

typedef enum
{
	AR_PostMsg_BASE = 0,       /*温度，湿度，电池电量信息; 内容为 CAR_POST_BASE_INFO_T */
	AR_PostMsg_POSITION = 1,    /*主动上送姿态信息; 内容为  CAR_POST_POSITION_INFO_T*/
	AR_PostMsg_AUTOWALK = 2,    /*自动巡逻状态上送 内容为 CAR_POST_AUTOWALK_INFO_T */
	AR_PostMsg_PictureAarray = 3, /*智能分析图片数组上送 内容为 AR_PictureArray */
//AR_PostMsg_AI = 4,  /*智能分析信息上送 内容为 AI_INFO_T ,已合并到AR_PostMsg_SWITCH中*/
AR_PostMsg_ALARM = 5,  /*告警信息上送 内容为 CAR_ALARM_INFO_T */
AR_PostMsg_SWITCH = 6,  /*开关信息上送 内容为 CAR_SWITCH_T */
AR_PostMsg_OTHER = 7,  /*其他杂项上送 内容为 CAR_OTHER_T */
AR_PostMsg_Text = 100    /*主动上送的XM透传L数据 内容见 sei设备_用户客户端与设备透传协议说明 */
}AR_PostMsgType; /*主动上送消息类型*/

 /* 主动上送信息回调
 /************************************************************************/
 //Description: POST消息回调函数
 //Parameters:
// [in] handle:通道句柄
 //[in] nMsgType:消息类型
 //[in] pBuf:消息数据，需要根据nMsgType， 转化成对应的结构体来使用
 //[in] unBufSize:消息数据大小
 //[in] pUser：用户数据
 //Return:无
typedef void (CALLBACK *fARPostMsgCallBack)(void* handle, AR_PostMsgType nMsgType, char *pBuf, unsigned int unBufSize, void* pUser);

//Description:	人脸检测回调函数类型
// Parameters:
// [in] handle:通道句柄
// [in] pObj:对象信息
// [in] nNum：表示pObj的个数
// [in] pUser: 用户数据
// Return：无
typedef void (CALLBACK* fARFaceDetectCBFun)(void* handle, DetectInfo *pDetectInfo, void* pUser);

#endif