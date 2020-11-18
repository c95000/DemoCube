#ifndef __NET_PROTOCOL_ROBOT_H__
#define __NET_PROTOCOL_ROBOT_H__

#if !defined(WIN32)
#define __PACKED__        __attribute__ ((__packed__))
#else
#define __PACKED__ 
#pragma pack(1)
#endif

/*****************************************************************
  Function:	enRobotCmdö��
  Description:	�ϲ��·����²��豸����������������ȡ���� �������·�����ҪӦ�������
  			Ϊnet_protocol.h�еĶ�������ö��CMD_ReqRobotParamSetGet
  			
  			SDKͨ��CMD_ReqRobotParamSetGet�·����豸
  DataFlow:	SDK ->IPC; SDK->H3; SDK ->BSM	
******************************************************************/
typedef enum
{			 		 
	RC_RobotMove_Ctl    		= 0,//��������,����Ϊ TRobotMove_Ctl,�޷�������	
	RC_RobotTopo_Get			= 1,//�񾭽�����ͼ��ȡ������Ϊ�գ���������Ϊ TRobotTopo_Get
	
	RC_RobotEnvConfig_Get		= 4,//�������û�ȡ������TRobotEnvCfg_SetGet
	RC_RobotEnvConfig_Set		= 5,//�����������ã�����TRobotEnvCfg_SetGet �޷�������
	RC_RobotEnvValue_Get		= 6,//��������������TRobotEnvValue_Get
	RC_RobotPowerValue_Get		= 7,//�������Ϣ��ȡ������TRobotPowerValue_Get
	RC_RobotNavigationMode_Get	= 8,//����ģʽ��ȡ������TRobotNavigation_SetGet
	RC_RobotNavigationMode_Set	= 9,//����ģʽ���ã�����TRobotNavigation_SetGet  �޷�������
	RC_RobotCtrlMode_Get		= 10,//Ѳ��ģʽ��ȡ������TRobotCtrlMode_SetGet
	RC_RobotCtrlMode_Set		= 11,//Ѳ��ģʽ���ã�����TRobotCtrlMode_SetGet �޷�������

	RC_RobotEnable_Get			= 12,//ʹ�ܻ�ȡ������TRobot_EnableSetGet
	RC_RobotEnable_Set			= 13,//ʹ�����ã�����TRobot_EnableSetGet �޷�������
	RC_PostOn_Pos_Get			= 14,//��ȡ��ǰλ�ã�����TRobotLocalPos_Info
	RC_PostOn_Compass_Get		= 15,//��ȡ��ǰ��λ������TRobotCompass_Info
	RC_PostOn_WifiInfo			= 16,//wifi̽����Ϣ������

	RC_PostFtpUrlGetResponse	= 18,//ƽ̨����ftp��ַ������TRobotRecFtpUrlGetResponse
	RC_PostRecUpFileMsgResponse	= 19,//ƽ̨Ӧ�������֪ͨ�ϴ��ɹ�������TRobotRecUpFileMsgResponse

	RC_Robot_Ctrl				= 20,//�������� ������TRobot_Ctrl �޷�������
	RC_IA_PARAM_Set            	= 266,//���ܷ����������ã���Ӧ����Ϊ TIAHead
	RC_CAPTURE_IMGAE            = 300, //ץͼ������Ϊ


	RC_ReqRobotUpdataAllow	= 100,// ��������������ΪTReqRobotNBUpdataAllow���޷�������
	RC_ReqRobotUpdataInfo	= 101,// ������Ϣ���ͣ�����ΪTReqRobotUpdataAllow���޷�������
	RC_ReqRobotUpdataData	= 102,// �������ݷ��ͣ�����ΪTReqRobotNBUpdataData���޷�������

	RC_RobotPushDownSnap	= 9001,// ֪ͨIPCץ�ģ�����ΪTRobotPushDownSnap���޷�������
	RC_RobotPushDownAudio	= 9002,// �·���Ƶ����wav������ΪTRobotPushDownAudio���޷�������

	RC_RobotPushDownText	= 0x10000,//ƽ̨�·�xmlЭ��͸��

	RC_PushDown_GuoMaiData	= 0x10001,//�����ͻ�����ִ�����豸���͵�͸�����ݣ����ݸ�ʽ�ɹ������豸����ͨ������
	
}enRobotCmd;

/*****************************************************************
  Function:	enPushOnCmdö��
  Description:	�ײ��豸�������͸��ϲ�ʱ��
  			Ϊnet_protocol.h�еĶ�������ö�ٶ�Ӧ��һ������Ϊ CMD_PushOnRobotInfo		    = 5000
  			SDKͨ��PostMessage�ص���ȥ
  DataFlow:	IPC->SDK ; H3->SDK; BSM->SDK 	
******************************************************************/
typedef enum
{
	PC_PostMsg_JsonData		= 256,			// �ı����ͣ�����Ϊjson�ַ���
	PC_PostMsg_TransData 	= 257,      // �ı����ͣ�����Ϊxml�ַ���
	PC_PostMsg_PushAlarm	= 258,		//Alarm �ṹ����Ϣ, ����ΪTRobotEnvAlarm_Info  ���������ץ��Ҫ��ץ��ͼƬ��UUID ͼƬ�͵�http
	RC_PostFtpUrlGet		= 259,		//��������ƽ̨��ȡftp��ַ������TRobotRecFtpUrlGet
	RC_PostRecUpFileMsg		= 260,		//������֪ͨƽ̨һ���ļ��ϴ��ɹ�������TRobotRecUpFileMsg
	PC_PostMsg_PushSnap		= 261,		//ץ����Ϣ, ����ΪTRobotSnap_Info���������ץ��Ҫ��ץ��ͼƬ��UUID ͼƬ�͵�http
	RC_PostMsg_IA_Data  	= 266,		//�������͵����ܷ������ݣ���Ӧ����Ϊ TIAHead

	RC_RobotPushOnImageAi	= 301,		//��������ͼ�����,3516A ���͸�SDK����ΪTReqRobotPushOnImageAi
	RC_RobotPushOnPicture	= 302,		//��������ץ��ͼƬ,3516A ���͸�SDK����ΪTRobotPushOnPicture
	RC_RobotPushOnAIFace	= 303,		//��������ͼ�����,����ΪTRobotPushAI
	RC_RobotPushOnAudio		= 304,		//�������ͶϾ���Ƶ,TRobotPushAudio
	RC_RobotPushOnPos		= 305,		//�������͵�ǰλ��TRobotPushPos
	

	PC_PostOn_GuoMaiData 	= 400,      // ����͸����Ϣ���ͣ����ݸ�ʽ�ɹ������豸����ͨ������
	//PC_PostOn_GuomaiDeviceInfo = 401, // ��Ӧ����Ϊ TGuomaiDeviceInfo
	//PC_PostOn_GuomaiGps = 402,       // ��Ӧ����Ϊ TGuomaiGps
	PC_PostOn_GuomaiSOS = 403,        // ��Ӧ����Ϊ TGuomaiSOS
	//PC_PostOn_GuomaiDevStateInfo = 404,        // ��Ӧ����Ϊ TGuomaiDevStateInfo
}enPushOnCmd;//ǰ���豸�������͸�����ƽ̨SDK����Ϣ

/*****************************************************************
  Function:	enPushDownCmdö��
  Description:	�����·����ݸ��ײ��豸
  			Ϊnet_protocol.h�еĶ�������ö�ٶ�Ӧ��һ������Ϊ CMD_PushDownRobotInfo		    = 6000
  DataFlow:	SDK->ִ����   ƽ̨SDK	->SDK
******************************************************************/
typedef enum
{			 		 
	PC_PostDown_GuoMaiData 	= 400,      // ƽ̨�����·� ����ҪӦ��

}enPushDownCmd;//ǰ���豸�������͸�����ƽ̨SDK����Ϣ

/*****************************************************************
  Function:	һ����������̨����Э��
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
	CAR_PTZ_CONTROL_3D_MOVE_STOP = 13,/*�ƶ�ֹͣ*/
	CAR_PTZ_CONTROL_3D_ZOOM_STOP = 14,/*�䱶ֹͣ*/
	CAR_PTZ_CONTROL_FOCUS_NEAR = 15,/*�۽���*/
	CAR_PTZ_CONTROL_FOCUS_FAR = 16,/*�۽�Զ*/
	CAR_PTZ_CONTROL_IRIS_OPEN = 17,/*��Ȧ��*/
	CAR_PTZ_CONTROL_IRIS_CLOSE = 18,/*��ȦС*/

	CAR_PTZ_CONTROL_EXT_PRESET_SET = 255,//ucValue ��ʾ���õ�Ԥ��λID
} CAR_PTZ_CONTROL_EXT_E;




typedef enum
{			 		 
	ROBOT_ALARM_TYPE_TEMP_TOP 				= 201,  // �¶����޸澯    
	ROBOT_ALARM_TYPE_TEMP_LOW				= 200,	// �¶����޸澯	
	ROBOT_ALARM_TYPE_HUMI_TOP 				= 203,  // ʪ�����޸澯
	ROBOT_ALARM_TYPE_HUMI_LOW				= 202,	// ʪ�����޸澯
	ROBOT_ALARM_TYPE_PM25					= 204,	// PM2.5 �澯
	ROBOT_ALARM_TYPE_TUMB					= 205,  // ˤ�� �澯
	ROBOT_ALARM_TYPE_HANG					= 206,	// ���� �澯
	ROBOT_ALARM_TYPE_POWER_LOW				= 207,  //��� �澯
	ROBOT_ALARM_TYPE_XBPOWER_LOW			= 208,	//�ű�����͸澯
	ROBOT_ALARM_TYPE_RAILSOUT				= 209,	//�ѹ�澯
	ROBOT_ALARM_TYPE_STOP					= 210,	//�赲�澯
	ROBOT_ALARM_TYPE_NOISE					= 211,	//�쳣�澯
	ROBOT_ALARM_TYPE_PM10					= 212,	// PM1.0 �澯
	ROBOT_ALARM_TYPE_LOWNET					= 213,  //�������߸澯
	ROBOT_ALARM_TYPE_MANUAL					= 214,	//һ���澯
	ROBOT_ALARM_TYPE_POWER_COUNT_LIM		= 215,	//��� ��ŵ�����澯
	ROBOT_ALARM_TYPE_LINK0					= 216,	//link0�澯
	ROBOT_ALARM_TYPE_LINK1					= 217,	//link1�澯
	ROBOT_ALARM_TYPE_IPCLASH 				= 218,	//IP ��ͻ�澯
	ROBOT_ALARM_TYPE_RAINING 				= 219,	//����
	ROBOT_ALARM_TYPE_POISONGAS				= 220,	//�����澯  PoisonGas
	ROBOT_ALARM_TYPE_HUMANBODY				= 102,	//�����֪�澯
}enRobotAlarmType;


//���͸澯ʱ������
struct _TRobotAlarmTime_Info
{
	char			cAlarmEnable;	//0 �رո澯 1�����澯
	unsigned char	ucStartHour;	//��ʼСʱ	
	unsigned char	ucStartMinute;	//��ʼ����
	unsigned char	ucStartSecond;	//��ʼ��

	unsigned char	ucEndHour;		//��ʼСʱ	
	unsigned char	ucEndMinute;	//��ʼ����
	unsigned char	ucEndSecond;	//��ʼ��
}__PACKED__;
typedef struct _TRobotAlarmTime_Info TRobotAlarmTime_Info;
//
//struct _TRobotCtrlValue_SetGet
//{
//	unsigned int unCtrlValue;	//1��λ
//}__PACKED__; 
//typedef struct _TRobotCtrlValue_SetGet TRobotCtrlValue_SetGet;


/*****************************************************************
IPC->SDK �������͸��ϲ���ؽṹ��
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
	MARK_SENDING			= 0,		// �м��
	MARK_START				= 1,		//��ʼ
	MARK_END				= 0x8000,  //����

}enMark;

struct _TRobotSnapInfo
{
	int					nChnNum;		//6������ͷ��ţ�1~6
	char				cDevSerial[34];
	char				cTime[16];		//20160727165912
	unsigned int 		unHappenNum;	//�������
	int 				nTouchType;		//��������1 �澯m_Alarm��2Ѳ��ץ��m_Pos;3�Խ����߲���
	int 				nCapNum;		//ץ�ı��1��ʾ��һ��
	union
	{
		struct
		{
			unsigned short		usPatrolID;		//Ѳ��·��ID
			unsigned short		usPointID;		//�ű�ID
			unsigned short		usPointState;	//�ű�״̬ 1��� 2 �м�� 3 �յ�
			unsigned short		usNailNum;		//ÿ�����ڵĴŶ���Ŵ�1��ʼ
		}m_Pos;
		struct
		{
			enRobotAlarmType	eAlarmType;		//�澯����
			unsigned short		usAlarmNum;		//�澯���
			unsigned short		usNailNum;		//ÿ�����ڵĴŶ���Ŵ�1��ʼ
		}m_Alarm;
		struct
		{
			short nlastPicture; //��ǰͼƬ�Ƿ������һ�ţ���ʾ�˾�������Ƿ����
			short nZoomValue;	//�۽����Խ��ZOOMֵ
			short nFocusValue;	//�۽����Խ��Focusֵ
			short nDistanceValue;//�۽����Խ��Distanceֵ
		}m_FocusTest;
		char buf[32];
	}INFO_UN;
	char cdata[2];
	
}__PACKED__;
typedef struct _TRobotSnapInfo TRobotSnapInfo;

/*****************************************************************
  Description:	H3: �¹�ipc3615A ��������ͼ��ʶ����Ϣ��H3,��H3ͨ������ת�����񾭽�manage��
  DataFlow:	3516A->(SDK)H3->(Com)Manage
******************************************************************/
struct _TReqRobotPushOnImageAi
{
	int				nChnNum;		//6������ͷ��ţ�1~6
	int 			nFlag;			//0 ��Ч 1��Ч
	int 			nangle;			//�Ƕ�
	int 			ndis;			//����,��λmm
	int 			nID;			//����
	int	 			nx;				//Բ��x����
	int				ny;				//Բ��y����
}__PACKED__; 
typedef struct _TReqRobotPushOnImageAi TReqRobotPushOnImageAi;

/*****************************************************************
  Description:	H3: �¹�3516A  ��������ץ��ͼƬ��Ϣ��SDK
  DataFlow:	3516A->(SDK)H3->SDK(BSM/DAS)
  			368->SDK(BSM/DAS)
******************************************************************/
struct _TRobotPushOnPicture
{
	TRobotSnapInfo	stPicInfo;	//ͼƬ��������TRobotSnapInfo���ŵ�ץ�Ķ�Ӧ�ŵ������Ϣ���澯��Ӧ�澯�����Ϣ
	
	enPicType		ePicType;		//ͼƬ����
	enMark			eMark;			//������
	unsigned int	unLocalSize;	//��ǰ����С
	char			cData[0];

}__PACKED__;
typedef struct _TRobotPushOnPicture TRobotPushOnPicture;

/*****************************************************************
  Description:	H3: �¹�TK1 ������������AR��Ϣ��SDK
  			�������ͼ�⵽������Ϣ��
  			cData:xml(BASE64)+bin(2��������)
  DataFlow:	TK1->(SDK)H3->SDK(BSM/DAS)
  			TK1->(SDK)368->SDK(BSM/DAS)
******************************************************************/
struct _TRobotPushAI
{
	int				nChnNum;		//6������ͷ��ţ�1~6
	char			cDataInfo[32];
	enPicType		ePicType;		//���ܷ�������
	enMark			eMark;			//������
	unsigned int	unTotalSize;	//������Ҫ�������ݵĴ�С
	unsigned int	unLocalSize;	//��ǰ����С
	char			cData[0];

}__PACKED__; 
typedef struct _TRobotPushAI TRobotPushAI;


typedef enum
{			 		 
	AUDIO_TYPE_G711A		=1,
	AUDIO_TYPE_G711U		=2,
	AUDIO_TYPE_WAV_FILE		=3,
	AUDIO_TYPE_RAW			=4,//pcm������
}enAudioType;
/*****************************************************************
  Description:	3516A���Ͼ��ϴ���H3
  			�������ͶϾ���Ƶ���ϲ�
  			cData:g711A/PCM
  DataFlow:	3516A->SDK(H3)->SDK(BSM)->SDK
******************************************************************/
struct _TRobotPushAudio
{
	int				nChnNum;		//6������ͷ��ţ�1~6
	enAudioType		eAudioType;		//��Ƶ����
	enMark			eMark;			//������
	unsigned int	unTotalSize;	//������Ҫ�������ݵĴ�С
	unsigned int	unLocalSize;	//��ǰ����С
	char			cData[0];

}__PACKED__; 
typedef struct _TRobotPushAudio TRobotPushAudio;

/*****************************************************************
  Description:	H3���������Ļ�ȡ�ϴ�¼���FTP URL
			H3Ҫ�ϴ�¼��������ƽ̨��ȡ���ļ����ϴ���ַ
  DataFlow:	SDK(H3)->SDK(BSM)->SDK
******************************************************************/
struct _TRobotRecFtpUrlGet
{
	int				nChnNum;		//6������ͷ��ţ�1~6
	char			cFileName[64];
	unsigned int	unFileSize;		//BYTE
	char			cRecTime[16];	//20160727165912

}__PACKED__; 
typedef struct _TRobotRecFtpUrlGet TRobotRecFtpUrlGet;

/*****************************************************************
  Description:	H3��������¼���ϴ��ɹ����
			H3��¼���ϴ��ɹ���֪ͨƽ̨
  DataFlow:	SDK(H3)->SDK(BSM)->SDK
******************************************************************/
struct _TRobotRecUpFileMsg
{
	int				nChnNum;		//6������ͷ��ţ�1~6
	char			cFtpUrl[128];
	int				nFlag;//1��ʾ�ϴ��ɹ�  0��ʾʧ��
	char			cRecStartTime[16];//20160727165912
	char			cRecEndTime[16];//20160727165912
	unsigned int	unFileSize;//BYTE

}__PACKED__; 
typedef struct _TRobotRecUpFileMsg TRobotRecUpFileMsg;
/*****************************************************************
*****************************************************************/
////�����澯��Ϣ
/*struct _TRobotEnvAlarm_Info 
{
	int					nAlarmType;			//��Ӧö��enRobotAlarmType
	short				sNum;				//��� �漰��ͬ��澯��ͬ��ŵ��ô��ֶ�
	unsigned char		ucFlag;				//0 �޸澯 1�澯
	char				cUUID[128];			//���û��ͼƬ������Ϊ��
	char				cdata[121];			//Ԥ���ֶ�
}__PACKED__; 
typedef struct _TRobotEnvAlarm_Info TRobotEnvAlarm_Info;*/

struct _TRobotSnap_Info 
{
	TRobotSnapInfo		stSnapInfo;
	char				cUUID[128];			//���û��ͼƬ������Ϊ��
	char				cdata[121];			//Ԥ���ֶ�
}__PACKED__; 
typedef struct _TRobotSnap_Info TRobotSnap_Info;
/******************************************************************************************************************/

/*****************************************************************
SDK ->IPC �ϲ�����\��ȡ\����\�����·�\ ����Ϣ�·���ؽṹ��
*****************************************************************/

/*****************************************************************
  Description:	H3֪ͨ3516A ץ��
  			�����·�ץ�������3516A 
  			stSnapInfo:ץ����Ϣ(ץ��ԭ������¼�)
  DataFlow:	SDK(H3)->3516A
******************************************************************/
struct _TRobotPushDownSnap
{
	TRobotSnapInfo	stSnapInfo;
}__PACKED__; 
typedef struct _TRobotPushDownSnap TRobotPushDownSnap;


/*****************************************************************
  Description:	ƽ̨�·���Ƶ���ݸ��²��豸
  			ƽ̨�����·���Ƶ���ݸ�SDK->H3
  DataFlow:	SDK->(H3)
******************************************************************/
struct _TRobotPushDownAudio
{
	int				nChnNum;		//6������ͷ��ţ�1~6 ��ʱ��ֻ��H3����
	enAudioType		eAudioType;		//��Ƶ����
	enMark			eMark;			//������
	unsigned int	unTotalSize;	//������Ҫ�������ݵĴ�С
	unsigned int	unLocalSize;	//��ǰ����С
	char			cData[0];
}__PACKED__;
typedef struct _TRobotPushDownAudio TRobotPushDownAudio;

/*****************************************************************
  Description:	ƽ̨���صײ��豸��ȡftp��ַ
  			ƽ̨����¼���ϴ�ftp��ַSDK->H3
  DataFlow:	SDK->BSM->(H3)
******************************************************************/
struct _TRobotRecFtpUrlGetResponse
{
	char			cFileName[64];
	char			cFtpUrl[128];

}__PACKED__; 
typedef struct _TRobotRecFtpUrlGetResponse TRobotRecFtpUrlGetResponse;

/*****************************************************************
  Description:	ƽ̨Ӧ��H3�ϴ�¼��ɹ�֪ͨ
  			ƽ̨���H3֪ͨ�ϴ�¼��ɹ�����Ӧ��SDK->H3
  DataFlow:	SDK->BSM->(H3)
******************************************************************/
struct _TRobotRecUpFileMsgResponse
{
	char			cFileName[64];
	int				nFlag;//1��ʾ�ϴ��ɹ�  0��ʾʧ��

}__PACKED__; 
typedef struct _TRobotRecUpFileMsgResponse TRobotRecUpFileMsgResponse;
/*****************************************************************
*****************************************************************/

struct _TRobotPushPos
{
	unsigned short 	usPosID;
	int				nState;//0 ���� 1�뿪

}__PACKED__;
typedef struct _TRobotPushPos TRobotPushPos;

struct _TIAHead
{
	int nXmlLen;
	int nBinLen;
	char Reserved[128];
	char cXmlData[0]; //xml���ݣ��������ڶ���������ǰ��
	//bindata����������
};
typedef struct _TIAHead TIAHead;

struct _TReqCaptureImage
{
	int nImageType; // 0��ʾĬ�ϣ� 1:jpg
	int nQuality; //ͼ������ 1-100��0��ʾĬ�ϣ� 1��ʾ�� 100��ʾ���
	int nWidth;   //ץͼ��ȣ�0��ʾĬ��
	int nHeight; // ץͼ�߶ȣ�0��ʾĬ��
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
	unsigned char ucImageData[0];//ͼ������
};
typedef struct _TAswCaptureImage TAswCaptureImage;

#if defined(WIN32)
#pragma pack()
#endif

/*************************************************************************************/
//end __NET_PROTOCOL_ROBOT_H__
#endif