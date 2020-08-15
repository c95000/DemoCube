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
	unsigned int uiStreamType;//0：裸流，1：ps流
	unsigned int w;//分辨率宽
	unsigned int h;//分辨率高
	float framerate;//帧率
}stVideoParam;

/*typedef VOID (CALLBACK* fSEICBFun)(int handle,
								  unsigned char  *pXML,
								  LONG  nSize,
								  LONG  pUser
								  );*///增强现实信息回调函数
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
/** 函数：	RECORD_PlayFiles
/** 功能：	播放指定的录像文件，单个文件或者多个文件
/** 参数：	argc	录像文件个数
/**			*argv[]	录像文件指针数组
			hWnd	播放窗口句柄
			ARLableCBFun	增强现实信息处理回调函数
			pUser1			增强现实信息处理回调函数参数
			fARParamCBFun	增强现实参数处理回调函数
			pUser2			增强现实参数处理回调函数参数
/** 返回：TRUE 成功
/**		 FALSE 失败
**********************************************************/
RECORD_API BOOL RECORD_PlayFiles(int argc, char *argv[],int hWnd, fARLableExCBFun ARLableCBFun, void* pUser1, fARParamCBFun ARParamCBFun, void* pUser2) ;
RECORD_API BOOL RECORD_PlayFiles_EX(int argc, char *pFilePath,int hWnd, fARLableExCBFun ARLableCBFun, void* pUser1, fARParamCBFun ARParamCBFun, void* pUser2) ;
#endif