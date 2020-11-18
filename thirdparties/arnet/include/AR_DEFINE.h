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
	AR_LABLE_POINT = 0,/*point ��*/
	AR_LABLE_VECTOR = 1,/*�������*/
	AR_LABLE_POLYGON = 2,/*�����*/
	AR_LABLE_LINE = 3,/*�߶�*/
	AR_LABLE_BINVECTOR = 4,/*˫������*/
	AR_LABLE_OVAL = 5,/*��Բ*/
	AR_LABLE_DIMENSION = 6	/*3ά*/
}AR_Type;/*��ǩ����*/

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

#define ARRET_LABLECOUNT_TOMAX -1000 //��ǩ�����Ѵ����ֵ
#define ARRET_WRONG_PARAMETER  -1001 //��������
#define ARRET_MALLOC_FAILED  -1002 //�ڴ����ʧ��
#define ARRET_NULL_POINTER  -2001 //��ָ���������
#define ARRET_INVALID_SEIPACK  -2002 //��Ч��sei��
#define ARRET_INVALID_XMLPACK  -2003 //��Ч��xml��
#define ARRET_INVALID_LABLEID  -2004 //��Ч�ı�ǩid
#define ARRET_BUF_TOOSMALL  -2005 //����̫С
#define ARRET_NONEXIST_XMLNODE  -2006 //���ʲ����ڵ�xml node
#define FACE_FEATURE_MAX_AR 320

typedef struct
{
	int	x;
	int	y;
}AR_POS;

/*��ǩ���Խṹ��*/
typedef struct
{
	AR_Type eType;//Ŀǰֻ֧��LABLE_TYPE_POINT
	int nID;
	int nLevel;//���ڲ���
	AR_POS	stPos;//��ǩ�ı��pos
	char chContent[AR_CONTENT_LEN];//һ����ǩ
	char chSubContent[AR_CONTENT_LEN];//������ǩ
	char chLink[AR_LEN_256];//���ӵ�ַ
	char chCmdLine[AR_LEN_256];//������
}AR_Lable;

typedef struct
{
	AR_Type eType;//Ŀǰֻ֧��LABLE_TYPE_POINT
	int nID;
	int nLevel;//���ڲ���
	AR_POS	stPos[20];//��ǩ�ı��pos����
	int nPosNum;//ʵ�ʵı�����
	char chContent[AR_CONTENT_LEN];//һ����ǩ
	char chSubContent[AR_CONTENT_LEN];//������ǩ
	char chLink[AR_LEN_256];//���ӵ�ַ
	char chCmdLine[AR_LEN_256];//������
}AR_LableEx;

typedef struct
{
	int  bAuto;//�Զ���ȡ����������,������ʱʹ��
	float fPan;/*ˮƽ�Ƕ����������������ʱ��+˳ʱ��-*/
	float fTilt;/*��ֱ����Ƕ������ˮƽ��0����ʱ��+˳ʱ��-*/
	float fAngleH;/*ˮƽ�Ž�*/
	float fAngleV;/*��ֱ�Ž�*/
	float fDistance;//������
}AR_PTZ;

typedef struct
{
	float fDeltT;//У׼Tֵ
	float fHeight;//�������������߶�
	float fRadius;//��ǰ�ο�����İ뾶
	float fPan;//��ǰ�ο����Pֵ
	float fTilt;//��ǰ�ο����Tֵ
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
	int  bAuto;//�Զ���ȡ����������,������ʱʹ��
	float fLongitude;/*����ֵE+; W-*/
	float fLatitude;/*γ��N+; S-*/
	float fAltitude;/*����*/
}AR_LOCATION;

typedef enum
{
	DEV_AR_IPC,//��ǿ��ʵǹ��
	DEV_AR_IPCDOME//��ǿ��ʵ���
}enARDeviceType;

typedef struct
{
	AR_PTZ			stPtz;
	AR_LOCATION	stLocation;
	AR_TIME		stTime;//ʱ���
	enARDeviceType	eDeviceType;
	char			chVer[AR_LEN_8];//�汾��1.00
	char			chDevModel[AR_LEN_32];//�豸�ͺ�
}AR_Param;

typedef struct
{
	//AR_PTZ			stPtz;
	unsigned int           dwTime; // ͼƬ����ʱ��
	int             nX; //ͼƬ����Ƶ�е�X���꣨���귶Χ��1920*1080��
	int             nY;//ͼƬ����Ƶ�е�Y����
	int				nWidth;//ͼƬ�Ŀ��
	int				nHeight;//ͼƬ�ĸ߶�
	int           nFrameW;//��Ƶ֡�Ŀ��
	int           nFrameH;//��Ƶ֡�ĸ߶�

	unsigned char  nGender;
	unsigned char  nAge;
	unsigned char  nExpression;
	unsigned char  nComplexion;
	unsigned char  nClothes;
	char*           pData; //ͼƬ���ݵ�ַ
	int             nDataLen;//ͼƬ���ݳ���
	int				nFeatureCount;//�������������
	char cFaceFeature[FACE_FEATURE_MAX_AR * 10];
}AR_Picture;

typedef struct
{
	double dOriginLongitude; //����ľ��� E+; W-
	double dOriginLatitude; //�����γ�� N+; S-
	double dTargetLongitude; //Ŀ��ľ��� E+; W-
	double dTargetLatitude; //Ŀ���γ�� N+; S-
	double dHeight; //��Ը߶�
}AR_GPS_Info;

typedef struct
{
	AR_Picture	stPicture[100];//ͼƬ����
	int nPictureNum;//ʵ��ͼƬ����
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


//Description:��ǿ��ʵԭʼ���ݻص�����
typedef void (CALLBACK* fARRawDataCBFun)(void* handle, unsigned char *pARRawData, int  nDataSize, void* pUser);

//Description:������ǿ��ʵ�ص�����
typedef void (CALLBACK* fARCBFun)(void* handle, unsigned char  *pXML, int  nSize, void* pUser);

//Description:��ǿ��ʵͼƬ�ص���������
// Parameters:
// [in] handle:��Ƶ���ž��
// [in] pSei:ͼƬ��Ϣ
// [in] nNum����ʾpSei�ĸ���
// [in] nUser: �û�����
// Return����
typedef void (CALLBACK* fARPictureCBFun)(void* handle, AR_Picture  *pSei, int nNum, void* pUser);

//Description:	ȫ�ֵ���ǿ��ʵͼƬ�ص���������
// Parameters:
// [in] handle:��Ƶ���ž��
// [in] pSei:ͼƬ��Ϣ
// [in] nNum����ʾpSei�ĸ���
// [in] nUser: �û�����
// Return����
typedef void (CALLBACK* fGlobalARPictureCBFun)(char *szDeviceID, AR_Picture  *pSei, int nNum, void* pUser);

//Description:������ǿ��ʵ��ǩ�ص�����
// Parameters:
// [in] handle:��Ƶ���ž��
// [in] ARLableCBFun: ��ǩ�ص�����
// [in] nUser���û�����
// Return���ɹ�����TRUE; ʧ�ܷ���FALSE
typedef void (CALLBACK* fARLableCBFun)(void* handle, AR_OPERATION nOperation, AR_Lable  *pSei, int nNum, void* pUser);

//Description:��ǿ��ʵ�����ص���������
// Parameters:
// [in] handle:��Ƶ���ž��
// [in] pParam: ������Ϣ
// [in] nUser: �û�����
// Return����
typedef void (CALLBACK* fARParamCBFun)(void* handle, AR_Param  *pLable, void* pUser);

//Description:��ǿ��ʵ��ǩ�ص���������
// Parameters:
// [in] handle:��Ƶ���ž��
// [in] nOperation: ��������
// [in] pSei:��ǩ��Ϣ
// [in] nNum����ʾpSei�ĸ���
// [in] nUser: �û�����
// Return����
typedef void (CALLBACK* fARLableExCBFun)(void* handle, AR_OPERATION nOperation, AR_LableEx  *pSei, int nNum, void* pUser);


//�������� �¶ȣ�ʪ�ȣ���ص�����Ϣ
struct _CAR_POST_BASE_INFO_T
{
	short nTemperature; //�¶ȣ�ʵ���¶ȳ���10������375��ʾ37.5��
	unsigned short nHumidity;    //ʪ�ȣ�ʵ��ʪ�ȳ���10������375��ʾ37.5%
	unsigned char u8Battery;     //��ص��� �ٷֱ�
	unsigned char u8HumidityAlarm;//ʪ�ȱ�����0��ʾ�ޣ�1��ʾ��
	unsigned char u8OutPutPower; //������ʣ� �ٷֱ�
	unsigned short u16PM25; //PM2.5 ��λ��ug/m^3
	unsigned short u16PM10; //PM1.0 
};
typedef struct _CAR_POST_BASE_INFO_T CAR_POST_BASE_INFO_T;

//����������̬��Ϣ
struct _CAR_POST_POSITION_INFO_T
{
	unsigned short u16CarDirect; //������ ����Ϊ0��˳ʱ�������360��
	short s16CarPitch; //С�����,-180~180��
	unsigned char au8RoadBlock[6]; //�ϰ��� ÿ�����Ӧ���ֽڣ��������ϰ��������������������4�֣�0��ʾ�ޣ�1��ʾԶ��2��ʾ�У�3��ʾ����
	short s16SoundDirect; //��Դλ�� �Ƕȣ�����ǰ������Ϊ0�ȣ�˳ʱ�������360�ȣ�-1��ʾû�С�
	unsigned char u8CurCarMode; //С����ǰ����ģʽ 0-�Զ�Ѳ��;1-�ֶ�����;2-���ģʽ;3-����ģʽ
};
typedef struct _CAR_POST_POSITION_INFO_T CAR_POST_POSITION_INFO_T;

// �Զ�Ѳ��״̬����
struct _CAR_POST_AUTOWALK_INFO_T
{
	unsigned char u8RouteID;      //Ѳ��·��
	unsigned char u8NewRouteId;//��ʾ�������õ����µ�·��ID��
							   //���RouteId��NewRouteId��һ�£���ʾ����ı���·�ߣ���ʱ����Ӧ����ʾ��"�����л�·��RouteId��NewRouteId���ȴ������˷���01��
	unsigned short u16PreXBID;   //��һ���ű�
	unsigned short u16NowXBID;  //��ʼ�ű�
	unsigned short u16NextXBID;    //Ŀ���ű�
	unsigned char u8Status;     //����״̬,30%,ȡ30
};
typedef struct _CAR_POST_AUTOWALK_INFO_T CAR_POST_AUTOWALK_INFO_T;

//������Ϣ��0��ʾû�б�����1��ʾ�б���
struct _CAR_ALARM_INFO_T
{
	unsigned char u8TemperatureAlarm; //�¶ȶȱ���
	unsigned char u8HumidityAlarm; //ʪ�ȱ���
	unsigned char u8PM25Alarm; //PM2.5����
	unsigned char u8PM10Alarm; //PM1.0����
	unsigned char u8HangAlarm; //���ұ���
	unsigned char u8TumbleAlarm; //��������	
};
typedef struct _CAR_ALARM_INFO_T CAR_ALARM_INFO_T;

//С��������
struct _CAR_SWITCH_T
{
	unsigned char u8LedLightEnable; //���������
	unsigned char u8SpeechRecognitionEnable; //����ʶ��
	unsigned char u8HangAlarmEnable; //���ձ���
	unsigned u32SoundSrcEnable; //������Դ��λ 1����0��
	unsigned u32AIEnable; //��������ʶ��
};
typedef struct _CAR_SWITCH_T CAR_SWITCH_T;

struct _CAR_OTHER_T
{
	unsigned char u8CarStatus; //С��״̬�� 0-������1-�����
};
typedef struct _CAR_OTHER_T CAR_OTHER_T;

typedef enum
{
	AR_PostMsg_BASE = 0,       /*�¶ȣ�ʪ�ȣ���ص�����Ϣ; ����Ϊ CAR_POST_BASE_INFO_T */
	AR_PostMsg_POSITION = 1,    /*����������̬��Ϣ; ����Ϊ  CAR_POST_POSITION_INFO_T*/
	AR_PostMsg_AUTOWALK = 2,    /*�Զ�Ѳ��״̬���� ����Ϊ CAR_POST_AUTOWALK_INFO_T */
	AR_PostMsg_PictureAarray = 3, /*���ܷ���ͼƬ�������� ����Ϊ AR_PictureArray */
//AR_PostMsg_AI = 4,  /*���ܷ�����Ϣ���� ����Ϊ AI_INFO_T ,�Ѻϲ���AR_PostMsg_SWITCH��*/
AR_PostMsg_ALARM = 5,  /*�澯��Ϣ���� ����Ϊ CAR_ALARM_INFO_T */
AR_PostMsg_SWITCH = 6,  /*������Ϣ���� ����Ϊ CAR_SWITCH_T */
AR_PostMsg_OTHER = 7,  /*������������ ����Ϊ CAR_OTHER_T */
AR_PostMsg_Text = 100    /*�������͵�XM͸��L���� ���ݼ� sei�豸_�û��ͻ������豸͸��Э��˵�� */
}AR_PostMsgType; /*����������Ϣ����*/

 /* ����������Ϣ�ص�
 /************************************************************************/
 //Description: POST��Ϣ�ص�����
 //Parameters:
// [in] handle:ͨ�����
 //[in] nMsgType:��Ϣ����
 //[in] pBuf:��Ϣ���ݣ���Ҫ����nMsgType�� ת���ɶ�Ӧ�Ľṹ����ʹ��
 //[in] unBufSize:��Ϣ���ݴ�С
 //[in] pUser���û�����
 //Return:��
typedef void (CALLBACK *fARPostMsgCallBack)(void* handle, AR_PostMsgType nMsgType, char *pBuf, unsigned int unBufSize, void* pUser);

//Description:	�������ص���������
// Parameters:
// [in] handle:ͨ�����
// [in] pObj:������Ϣ
// [in] nNum����ʾpObj�ĸ���
// [in] pUser: �û�����
// Return����
typedef void (CALLBACK* fARFaceDetectCBFun)(void* handle, DetectInfo *pDetectInfo, void* pUser);

#endif