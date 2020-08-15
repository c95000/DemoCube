#ifndef __NET_PROTOCOL_ROBOT_H__
#define __NET_PROTOCOL_ROBOT_H__

#if !defined(WIN32)
#define __PACKED__        __attribute__ ((__packed__))
#else
#define __PACKED__ 
#pragma pack(1)
#endif

/*****************************************************************
  Function:	enRobotCmd枚举
  Description:	上层下发给下层设备控制命令，设置命令，获取命令 及主动下发不需要应答的命令
  			为net_protocol.h中的二级命令枚举CMD_ReqRobotParamSetGet
  			
  			SDK通过CMD_ReqRobotParamSetGet下发给设备
  DataFlow:	SDK ->IPC; SDK->H3; SDK ->BSM	
******************************************************************/
typedef enum
{			 		 
	RC_RobotMove_Ctl    		= 0,//动力控制,参数为 TRobotMove_Ctl,无返回数据	
	RC_RobotTopo_Get			= 1,//神经节拓扑图获取，参数为空，返回数据为 TRobotTopo_Get
	
	RC_RobotEnvConfig_Get		= 4,//环境配置获取，参数TRobotEnvCfg_SetGet
	RC_RobotEnvConfig_Set		= 5,//环境配置设置，参数TRobotEnvCfg_SetGet 无返回数据
	RC_RobotEnvValue_Get		= 6,//环境参数，参数TRobotEnvValue_Get
	RC_RobotPowerValue_Get		= 7,//电池组信息获取，参数TRobotPowerValue_Get
	RC_RobotNavigationMode_Get	= 8,//导航模式获取，参数TRobotNavigation_SetGet
	RC_RobotNavigationMode_Set	= 9,//导航模式设置，参数TRobotNavigation_SetGet  无返回数据
	RC_RobotCtrlMode_Get		= 10,//巡逻模式获取，参数TRobotCtrlMode_SetGet
	RC_RobotCtrlMode_Set		= 11,//巡逻模式设置，参数TRobotCtrlMode_SetGet 无返回数据

	RC_RobotEnable_Get			= 12,//使能获取，参数TRobot_EnableSetGet
	RC_RobotEnable_Set			= 13,//使能设置，参数TRobot_EnableSetGet 无返回数据
	RC_PostOn_Pos_Get			= 14,//获取当前位置，参数TRobotLocalPos_Info
	RC_PostOn_Compass_Get		= 15,//获取当前方位，参数TRobotCompass_Info
	RC_PostOn_WifiInfo			= 16,//wifi探测信息，参数

	RC_PostFtpUrlGetResponse	= 18,//平台返回ftp地址，参数TRobotRecFtpUrlGetResponse
	RC_PostRecUpFileMsgResponse	= 19,//平台应答机器人通知上传成功，参数TRobotRecUpFileMsgResponse

	RC_Robot_Ctrl				= 20,//控制命令 ，参数TRobot_Ctrl 无返回数据
	RC_IA_PARAM_Set            	= 266,//智能分析参数设置，对应数据为 TIAHead
	RC_CAPTURE_IMGAE            = 300, //抓图，参数为


	RC_ReqRobotUpdataAllow	= 100,// 请求升级，参数为TReqRobotNBUpdataAllow，无返回数据
	RC_ReqRobotUpdataInfo	= 101,// 升级信息发送，参数为TReqRobotUpdataAllow，无返回数据
	RC_ReqRobotUpdataData	= 102,// 升级数据发送，参数为TReqRobotNBUpdataData，无返回数据

	RC_RobotPushDownSnap	= 9001,// 通知IPC抓拍，参数为TRobotPushDownSnap，无返回数据
	RC_RobotPushDownAudio	= 9002,// 下发音频数据wav，参数为TRobotPushDownAudio，无返回数据

	RC_RobotPushDownText	= 0x10000,//平台下发xml协议透传

	RC_PushDown_GuoMaiData	= 0x10001,//国迈客户端往执法仪设备发送的透传数据，内容格式由国迈和设备厂商通铭定义
	
}enRobotCmd;

/*****************************************************************
  Function:	enPushOnCmd枚举
  Description:	底层设备主动上送给上层时用
  			为net_protocol.h中的二级命令枚举对应的一级命令为 CMD_PushOnRobotInfo		    = 5000
  			SDK通过PostMessage回调出去
  DataFlow:	IPC->SDK ; H3->SDK; BSM->SDK 	
******************************************************************/
typedef enum
{
	PC_PostMsg_JsonData		= 256,			// 文本上送，参数为json字符串
	PC_PostMsg_TransData 	= 257,      // 文本上送，参数为xml字符串
	PC_PostMsg_PushAlarm	= 258,		//Alarm 结构体信息, 参数为TRobotEnvAlarm_Info  如果有联动抓拍要送抓拍图片的UUID 图片送到http
	RC_PostFtpUrlGet		= 259,		//机器人向平台获取ftp地址，参数TRobotRecFtpUrlGet
	RC_PostRecUpFileMsg		= 260,		//机器人通知平台一个文件上传成功，参数TRobotRecUpFileMsg
	PC_PostMsg_PushSnap		= 261,		//抓拍信息, 参数为TRobotSnap_Info如果有联动抓拍要送抓拍图片的UUID 图片送到http
	RC_PostMsg_IA_Data  	= 266,		//主动上送的智能分析数据，对应数据为 TIAHead

	RC_RobotPushOnImageAi	= 301,		//主动上送图像分析,3516A 上送给SDK参数为TReqRobotPushOnImageAi
	RC_RobotPushOnPicture	= 302,		//主动上送抓拍图片,3516A 上送给SDK参数为TRobotPushOnPicture
	RC_RobotPushOnAIFace	= 303,		//主动上送图像分析,参数为TRobotPushAI
	RC_RobotPushOnAudio		= 304,		//主动上送断句音频,TRobotPushAudio
	RC_RobotPushOnPos		= 305,		//主动上送当前位置TRobotPushPos
	

	PC_PostOn_GuoMaiData 	= 400,      // 国迈透传消息上送，内容格式由国迈和设备厂商通铭定义
	//PC_PostOn_GuomaiDeviceInfo = 401, // 对应数据为 TGuomaiDeviceInfo
	//PC_PostOn_GuomaiGps = 402,       // 对应数据为 TGuomaiGps
	PC_PostOn_GuomaiSOS = 403,        // 对应数据为 TGuomaiSOS
	//PC_PostOn_GuomaiDevStateInfo = 404,        // 对应数据为 TGuomaiDevStateInfo
}enPushOnCmd;//前端设备主动上送给中心平台SDK的信息

/*****************************************************************
  Function:	enPushDownCmd枚举
  Description:	中心下发数据给底层设备
  			为net_protocol.h中的二级命令枚举对应的一级命令为 CMD_PushDownRobotInfo		    = 6000
  DataFlow:	SDK->执法仪   平台SDK	->SDK
******************************************************************/
typedef enum
{			 		 
	PC_PostDown_GuoMaiData 	= 400,      // 平台数据下发 不需要应答

}enPushDownCmd;//前端设备主动上送给中心平台SDK的信息

/*****************************************************************
  Function:	一代机器人云台控制协议
  Description:	
  DataFlow:	SDK->IPC ; 	
******************************************************************/
typedef enum
{
	CAR_PTZ_CONTROL_EXT_CMD_STOP = 0,
	CAR_PTZ_CONTROL_EXT_CMD_UP = 1,
	CAR_PTZ_CONTROL_EXT_CMD_RIGHTUP = 2,
	CAR_PTZ_CONTROL_EXT_CMD_RIGHT = 3,
	CAR_PTZ_CONTROL_EXT_CMD_RIGHTDOWN = 4,
	CAR_PTZ_CONTROL_EXT_CMD_DOWN = 5,
	CAR_PTZ_CONTROL_EXT_CMD_LEFTDOWN = 6,
	CAR_PTZ_CONTROL_EXT_CMD_LEFT = 7,
	CAR_PTZ_CONTROL_EXT_CMD_LEFTUP = 8,
	CAR_PTZ_CONTROL_EXT_CMD_ZOOMIN = 9,
	CAR_PTZ_CONTROL_EXT_CMD_ZOOMOUT = 10,
	CAR_PTZ_CONTROL_EXT_PRESET_GOHOME = 11,
	CAR_PTZ_CONTROL_EXT_PRESET_GOTO = 12,
	CAR_PTZ_CONTROL_3D_MOVE_STOP = 13,/*移动停止*/
	CAR_PTZ_CONTROL_3D_ZOOM_STOP = 14,/*变倍停止*/
	CAR_PTZ_CONTROL_FOCUS_NEAR = 15,/*聚焦近*/
	CAR_PTZ_CONTROL_FOCUS_FAR = 16,/*聚焦远*/
	CAR_PTZ_CONTROL_IRIS_OPEN = 17,/*光圈大*/
	CAR_PTZ_CONTROL_IRIS_CLOSE = 18,/*光圈小*/

	CAR_PTZ_CONTROL_EXT_PRESET_SET = 255,//ucValue 表示设置的预置位ID
} CAR_PTZ_CONTROL_EXT_E;




typedef enum
{			 		 
	ROBOT_ALARM_TYPE_TEMP_TOP 				= 201,  // 温度上限告警    
	ROBOT_ALARM_TYPE_TEMP_LOW				= 200,	// 温度下限告警	
	ROBOT_ALARM_TYPE_HUMI_TOP 				= 203,  // 湿度上限告警
	ROBOT_ALARM_TYPE_HUMI_LOW				= 202,	// 湿度下限告警
	ROBOT_ALARM_TYPE_PM25					= 204,	// PM2.5 告警
	ROBOT_ALARM_TYPE_TUMB					= 205,  // 摔倒 告警
	ROBOT_ALARM_TYPE_HANG					= 206,	// 悬挂 告警
	ROBOT_ALARM_TYPE_POWER_LOW				= 207,  //电池 告警
	ROBOT_ALARM_TYPE_XBPOWER_LOW			= 208,	//信标电量低告警
	ROBOT_ALARM_TYPE_RAILSOUT				= 209,	//脱轨告警
	ROBOT_ALARM_TYPE_STOP					= 210,	//阻挡告警
	ROBOT_ALARM_TYPE_NOISE					= 211,	//异常告警
	ROBOT_ALARM_TYPE_PM10					= 212,	// PM1.0 告警
	ROBOT_ALARM_TYPE_LOWNET					= 213,  //低速无线告警
	ROBOT_ALARM_TYPE_MANUAL					= 214,	//一键告警
	ROBOT_ALARM_TYPE_POWER_COUNT_LIM		= 215,	//电池 充放电次数告警
	ROBOT_ALARM_TYPE_LINK0					= 216,	//link0告警
	ROBOT_ALARM_TYPE_LINK1					= 217,	//link1告警
	ROBOT_ALARM_TYPE_IPCLASH 				= 218,	//IP 冲突告警
	ROBOT_ALARM_TYPE_RAINING 				= 219,	//下雨
	ROBOT_ALARM_TYPE_POISONGAS				= 220,	//毒气告警  PoisonGas
	ROBOT_ALARM_TYPE_HUMANBODY				= 102,	//人体感知告警
}enRobotAlarmType;


//上送告警时间设置
struct _TRobotAlarmTime_Info
{
	char			cAlarmEnable;	//0 关闭告警 1开启告警
	unsigned char	ucStartHour;	//开始小时	
	unsigned char	ucStartMinute;	//开始分钟
	unsigned char	ucStartSecond;	//开始秒

	unsigned char	ucEndHour;		//开始小时	
	unsigned char	ucEndMinute;	//开始分钟
	unsigned char	ucEndSecond;	//开始秒
}__PACKED__;
typedef struct _TRobotAlarmTime_Info TRobotAlarmTime_Info;
//
//struct _TRobotCtrlValue_SetGet
//{
//	unsigned int unCtrlValue;	//1归位
//}__PACKED__; 
//typedef struct _TRobotCtrlValue_SetGet TRobotCtrlValue_SetGet;


/*****************************************************************
IPC->SDK 主动上送给上层相关结构体
*****************************************************************/
typedef enum
{			 		 
	PIC_TYPE_JPG			= 1,	// jpeg
	PIC_TYPE_BMP24			= 2,	//bmp 24
	PIC_TYPE_YUV			= 8,	//yuv 422sp
	PIC_TYPE_AI				= 15,	//yuv 422sp
}enPicType;

typedef enum
{			 		 
	MARK_SENDING			= 0,		// 中间包
	MARK_START				= 1,		//开始
	MARK_END				= 0x8000,  //最后包

}enMark;

struct _TRobotSnapInfo
{
	int					nChnNum;		//6个摄像头序号，1~6
	char				cDevSerial[34];
	char				cTime[16];		//20160727165912
	unsigned int 		unHappenNum;	//发生编号
	int 				nTouchType;		//触发类型1 告警m_Alarm；2巡逻抓拍m_Pos;3对焦曲线测试
	int 				nCapNum;		//抓拍编号1表示第一张
	union
	{
		struct
		{
			unsigned short		usPatrolID;		//巡逻路线ID
			unsigned short		usPointID;		//信标ID
			unsigned short		usPointState;	//信标状态 1起点 2 中间点 3 终点
			unsigned short		usNailNum;		//每个点内的磁钉编号从1开始
		}m_Pos;
		struct
		{
			enRobotAlarmType	eAlarmType;		//告警类型
			unsigned short		usAlarmNum;		//告警编号
			unsigned short		usNailNum;		//每个点内的磁钉编号从1开始
		}m_Alarm;
		struct
		{
			short nlastPicture; //当前图片是否是最后一张，表示此距离测试是否完毕
			short nZoomValue;	//聚焦测试结果ZOOM值
			short nFocusValue;	//聚焦测试结果Focus值
			short nDistanceValue;//聚焦测试结果Distance值
		}m_FocusTest;
		char buf[32];
	}INFO_UN;
	char cdata[2];
	
}__PACKED__;
typedef struct _TRobotSnapInfo TRobotSnapInfo;

/*****************************************************************
  Description:	H3: 下挂ipc3615A 主动上送图标识别信息给H3,由H3通过串口转发给神经节manage板
  DataFlow:	3516A->(SDK)H3->(Com)Manage
******************************************************************/
struct _TReqRobotPushOnImageAi
{
	int				nChnNum;		//6个摄像头序号，1~6
	int 			nFlag;			//0 无效 1有效
	int 			nangle;			//角度
	int 			ndis;			//距离,单位mm
	int 			nID;			//编码
	int	 			nx;				//圆心x坐标
	int				ny;				//圆心y坐标
}__PACKED__; 
typedef struct _TReqRobotPushOnImageAi TReqRobotPushOnImageAi;

/*****************************************************************
  Description:	H3: 下挂3516A  主动上送抓拍图片信息给SDK
  DataFlow:	3516A->(SDK)H3->SDK(BSM/DAS)
  			368->SDK(BSM/DAS)
******************************************************************/
struct _TRobotPushOnPicture
{
	TRobotSnapInfo	stPicInfo;	//图片属性描述TRobotSnapInfo；磁导抓拍对应磁导相关信息；告警对应告警相关信息
	
	enPicType		ePicType;		//图片属性
	enMark			eMark;			//包属性
	unsigned int	unLocalSize;	//当前包大小
	char			cData[0];

}__PACKED__;
typedef struct _TRobotPushOnPicture TRobotPushOnPicture;

/*****************************************************************
  Description:	H3: 下挂TK1 主动上送人脸AR信息给SDK
  			主动上送检测到人脸信息包
  			cData:xml(BASE64)+bin(2进制数据)
  DataFlow:	TK1->(SDK)H3->SDK(BSM/DAS)
  			TK1->(SDK)368->SDK(BSM/DAS)
******************************************************************/
struct _TRobotPushAI
{
	int				nChnNum;		//6个摄像头序号，1~6
	char			cDataInfo[32];
	enPicType		ePicType;		//智能分析数据
	enMark			eMark;			//包属性
	unsigned int	unTotalSize;	//整个需要传输数据的大小
	unsigned int	unLocalSize;	//当前包大小
	char			cData[0];

}__PACKED__; 
typedef struct _TRobotPushAI TRobotPushAI;


typedef enum
{			 		 
	AUDIO_TYPE_G711A		=1,
	AUDIO_TYPE_G711U		=2,
	AUDIO_TYPE_WAV_FILE		=3,
	AUDIO_TYPE_RAW			=4,//pcm裸数据
}enAudioType;
/*****************************************************************
  Description:	3516A将断句上传给H3
  			主动上送断句音频给上层
  			cData:g711A/PCM
  DataFlow:	3516A->SDK(H3)->SDK(BSM)->SDK
******************************************************************/
struct _TRobotPushAudio
{
	int				nChnNum;		//6个摄像头序号，1~6
	enAudioType		eAudioType;		//音频属性
	enMark			eMark;			//包属性
	unsigned int	unTotalSize;	//整个需要传输数据的大小
	unsigned int	unLocalSize;	//当前包大小
	char			cData[0];

}__PACKED__; 
typedef struct _TRobotPushAudio TRobotPushAudio;

/*****************************************************************
  Description:	H3主动向中心获取上传录像的FTP URL
			H3要上传录像首先向平台获取该文件的上传地址
  DataFlow:	SDK(H3)->SDK(BSM)->SDK
******************************************************************/
struct _TRobotRecFtpUrlGet
{
	int				nChnNum;		//6个摄像头序号，1~6
	char			cFileName[64];
	unsigned int	unFileSize;		//BYTE
	char			cRecTime[16];	//20160727165912

}__PACKED__; 
typedef struct _TRobotRecFtpUrlGet TRobotRecFtpUrlGet;

/*****************************************************************
  Description:	H3主动上送录像上传成功与否
			H3将录像上传成功后通知平台
  DataFlow:	SDK(H3)->SDK(BSM)->SDK
******************************************************************/
struct _TRobotRecUpFileMsg
{
	int				nChnNum;		//6个摄像头序号，1~6
	char			cFtpUrl[128];
	int				nFlag;//1表示上传成功  0表示失败
	char			cRecStartTime[16];//20160727165912
	char			cRecEndTime[16];//20160727165912
	unsigned int	unFileSize;//BYTE

}__PACKED__; 
typedef struct _TRobotRecUpFileMsg TRobotRecUpFileMsg;
/*****************************************************************
*****************************************************************/
////环境告警信息
/*struct _TRobotEnvAlarm_Info 
{
	int					nAlarmType;			//对应枚举enRobotAlarmType
	short				sNum;				//编号 涉及到同类告警不同编号的用此字段
	unsigned char		ucFlag;				//0 无告警 1告警
	char				cUUID[128];			//如果没有图片就设置为空
	char				cdata[121];			//预留字段
}__PACKED__; 
typedef struct _TRobotEnvAlarm_Info TRobotEnvAlarm_Info;*/

struct _TRobotSnap_Info 
{
	TRobotSnapInfo		stSnapInfo;
	char				cUUID[128];			//如果没有图片就设置为空
	char				cdata[121];			//预留字段
}__PACKED__; 
typedef struct _TRobotSnap_Info TRobotSnap_Info;
/******************************************************************************************************************/

/*****************************************************************
SDK ->IPC 上层设置\获取\控制\主动下发\ 等信息下发相关结构体
*****************************************************************/

/*****************************************************************
  Description:	H3通知3516A 抓拍
  			主动下发抓拍命令给3516A 
  			stSnapInfo:抓拍信息(抓拍原因及相关事件)
  DataFlow:	SDK(H3)->3516A
******************************************************************/
struct _TRobotPushDownSnap
{
	TRobotSnapInfo	stSnapInfo;
}__PACKED__; 
typedef struct _TRobotPushDownSnap TRobotPushDownSnap;


/*****************************************************************
  Description:	平台下发音频数据给下层设备
  			平台主动下发音频数据给SDK->H3
  DataFlow:	SDK->(H3)
******************************************************************/
struct _TRobotPushDownAudio
{
	int				nChnNum;		//6个摄像头序号，1~6 暂时是只有H3处理
	enAudioType		eAudioType;		//音频属性
	enMark			eMark;			//包属性
	unsigned int	unTotalSize;	//整个需要传输数据的大小
	unsigned int	unLocalSize;	//当前包大小
	char			cData[0];
}__PACKED__;
typedef struct _TRobotPushDownAudio TRobotPushDownAudio;

/*****************************************************************
  Description:	平台返回底层设备获取ftp地址
  			平台返回录像上传ftp地址SDK->H3
  DataFlow:	SDK->BSM->(H3)
******************************************************************/
struct _TRobotRecFtpUrlGetResponse
{
	char			cFileName[64];
	char			cFtpUrl[128];

}__PACKED__; 
typedef struct _TRobotRecFtpUrlGetResponse TRobotRecFtpUrlGetResponse;

/*****************************************************************
  Description:	平台应答H3上传录像成功通知
  			平台真对H3通知上传录像成功与否的应答SDK->H3
  DataFlow:	SDK->BSM->(H3)
******************************************************************/
struct _TRobotRecUpFileMsgResponse
{
	char			cFileName[64];
	int				nFlag;//1表示上传成功  0表示失败

}__PACKED__; 
typedef struct _TRobotRecUpFileMsgResponse TRobotRecUpFileMsgResponse;
/*****************************************************************
*****************************************************************/

struct _TRobotPushPos
{
	unsigned short 	usPosID;
	int				nState;//0 进入 1离开

}__PACKED__;
typedef struct _TRobotPushPos TRobotPushPos;

struct _TIAHead
{
	int nXmlLen;
	int nBinLen;
	char Reserved[128];
	char cXmlData[0]; //xml数据，它必须在二进制数据前面
	//bindata二进制数据
};
typedef struct _TIAHead TIAHead;

struct _TReqCaptureImage
{
	int nImageType; // 0表示默认， 1:jpg
	int nQuality; //图像质量 1-100；0表示默认， 1表示最差， 100表示最好
	int nWidth;   //抓图宽度，0表示默认
	int nHeight; // 抓图高度，0表示默认
	char Reserved[28];
};
typedef struct _TReqCaptureImage TReqCaptureImage;

struct _TAswCaptureImage
{
	int nImageType;
	int nQuality;
	int nWidth;
	int nHeight;
	int nSize;
	char Reserved[28];
	unsigned char ucImageData[0];//图像数据
};
typedef struct _TAswCaptureImage TAswCaptureImage;

#if defined(WIN32)
#pragma pack()
#endif

/*************************************************************************************/
//end __NET_PROTOCOL_ROBOT_H__
#endif