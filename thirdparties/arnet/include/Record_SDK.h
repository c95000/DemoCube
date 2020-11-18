#ifndef RECORD_DEF_H
#define RECORD_DEF_H

#ifdef RECORD_SDK_EXPORTS
#define RECORD_API  extern "C" __declspec(dllexport) 

#else
#define RECORD_API  extern "C" __declspec(dllimport)
#endif
typedef enum
{
	RECORD_TYPE_GMF	=0x0,
	RECORD_TYPE_AVI	=0x02,
	RECORD_TYPEMP4	=0x04,
}enRecordType;

typedef struct 
{
	unsigned int uiStreamType;//0��������1��ps��
	unsigned int w;//�ֱ��ʿ�
	unsigned int h;//�ֱ��ʸ�
	float framerate;//֡��
}stVideoParam;

/*typedef VOID (CALLBACK* fSEICBFun)(int handle,
								  unsigned char  *pXML,
								  LONG  nSize,
								  LONG  pUser
								  );*///��ǿ��ʵ��Ϣ�ص�����
RECORD_API int RECORD_Play(char *szIP, char *pPath, int hWnd, fARLableExCBFun ARLableCBFun,void* pUser1,fARParamCBFun ARParamCBFun,void* pUser2);


RECORD_API int RECORD_Stop();
RECORD_API int RECORD_Pause(int nFlag);
RECORD_API int RECORD_SetPos(double dPos);
RECORD_API BOOL RECORD_GetPos(double *pPos);
//RECORD_API int RECORD_Init();
//RECORD_API int RECORD_DeInit();

RECORD_API int RECORD_RecStart(char *szIP, enRecordType eFileFormat, char* pInFilePath);
RECORD_API int RECORD_RecStart_EX(char *szIP, enRecordType eFileFormat, char* pInFilePath, stVideoParam stParam);
RECORD_API int RECORD_RecStop();
RECORD_API int RECORD_RecInputData(char *pBuffer, DWORD dwBufSize);

RECORD_API void RECORD_SetDrawFun(fDrawCBFun DrawCBFun,void* pUser);
RECORD_API void RECORD_SetARPictureCallBack(fARPictureCBFun ARPictureCBFun, void* pUser);
RECORD_API BOOL RECORD_AR_SaveLocReference(AR_Reference *pRef, int nNum, char *chPath, char *szIP, char *chMode);

/********************************************************
/** ������	RECORD_PlayFiles
/** ���ܣ�	����ָ����¼���ļ��������ļ����߶���ļ�
/** ������	argc	¼���ļ�����
/**			*argv[]	¼���ļ�ָ������
			hWnd	���Ŵ��ھ��
			ARLableCBFun	��ǿ��ʵ��Ϣ����ص�����
			pUser1			��ǿ��ʵ��Ϣ����ص���������
			fARParamCBFun	��ǿ��ʵ��������ص�����
			pUser2			��ǿ��ʵ��������ص���������
/** ���أ�TRUE �ɹ�
/**		 FALSE ʧ��
**********************************************************/
RECORD_API BOOL RECORD_PlayFiles(int argc, char *argv[],int hWnd, fARLableExCBFun ARLableCBFun, void* pUser1, fARParamCBFun ARParamCBFun, void* pUser2) ;
RECORD_API BOOL RECORD_PlayFiles_EX(int argc, char *pFilePath,int hWnd, fARLableExCBFun ARLableCBFun, void* pUser1, fARParamCBFun ARParamCBFun, void* pUser2) ;
#endif