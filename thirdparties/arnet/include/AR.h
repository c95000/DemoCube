#ifndef _AR_H
#define _AR_H

#include "AR_DEFINE.h"

#ifdef WIN32
	#ifdef AR_EXPORTS
		#define AR_API  extern "C" __declspec(dllexport)
	#else
		#define AR_API  extern "C" __declspec(dllimport)
	#endif
#else
	#define AR_API 
#endif

typedef void* ARHANDLE;
// Description:����һ��ͨ��
// Return:�������ʾʧ�ܣ�����ֵΪͨ�����
AR_API ARHANDLE AR_VideoOpen();

//Description:������ǿ��ʵ��ǩ�ص�����
// Parameters:
// [in] handle:ͨ�����
// [in] ARLableCBFun: ��ǩ�ص�����
// [in] nUser���û�����
// Return������0��ʾ�ɹ�; ����ֵ��ʾ������
AR_API int AR_SetARLableExCallBack(ARHANDLE handle,fARLableExCBFun ARLableCBFun,void* pUser);

//Description:������ǿ��ʵ�����ص�����
// Parameters:
// [in] handle:ͨ�����
// [in] ARParamCBFun: �����ص�����
// [in] nUser���û�����
// Return������0��ʾ�ɹ�; ����ֵ��ʾ������
AR_API int AR_SetARParamCallBack(ARHANDLE handle,fARParamCBFun ARParamCBFun,void* pUser);

//Description:������ǿ��ʵͼƬ�ص�����
// Parameters:
// [in] handle:ͨ�����
// [in] CBFun: ͼƬ�ص�����
// [in] pUser���û�����
// Return������0��ʾ�ɹ�; ����ֵ��ʾ������
AR_API int AR_SetARPictureCallBack(ARHANDLE handle,fARPictureCBFun CBFun,void* pUser);

//Description:��������������ص�����
// Parameters:
// [in] handle:ͨ�����
// [in] CBFun: ����ص�����
// [in] pUser���û�����
// Return������0��ʾ�ɹ�; ����ֵ��ʾ������
AR_API int AR_SetARFaceDetectCallBack(ARHANDLE handle, fARFaceDetectCBFun CBFun, void* pUser);

//Description: �豸����������Ϣ�ص�����
//Parameters:
//[in] lLoginID:ͨ�����
//[in] fPostMsgCallBack:��Ϣ�ص�����
//[in] pUser���ص������û�����
//Return: ����0��ʾ�ɹ�; ����ֵ��ʾ������    
AR_API int AR_SetPostMsgCallBack(ARHANDLE handle, fARPostMsgCallBack fPostMsgCallBack, void *pUser);

//Description:������ǿ��ʵԭʼ���ݻص�����
// Parameters:
// [in] handle:ͨ�����
// [in] CBFun: �ص�����
// [in] pUser���û�����
// Return������0��ʾ�ɹ�; ����ֵ��ʾ������
AR_API int AR_SetARRawDataCallBack(ARHANDLE handle,fARRawDataCBFun CBFun,void* pUser);

// Description:����һ֡���ݵ�����⣨Ŀǰ����һ֡һ֡�������ݣ�
//���������벻������֡����һ���������һ֡�����ݣ�
// Parameters:
//	[in] handle: ͨ�����
//	[in] pBuf���������׵�ַ
//	[in] nLen: �����ݳ���
// Return: ����0��ʾ�ɹ�; ����ֵ��ʾ������
AR_API int AR_VideoInputAFrame(ARHANDLE handle,unsigned char *pBuf,int nLen);

// Description:�رս�����
// Parameters:
//	[in] handle: ͨ�����
// Return:����0��ʾ�ɹ�; ����ֵ��ʾ������
AR_API int AR_VideoClose(ARHANDLE handle);

// ��������ȡһ�����еı�ǩID,������ӱ�ǩ
// ������
// [in] handle: ͨ����
// ����ֵ������0��ʾ�ɹ�; ����ֵ��ʾ������
AR_API int AR_GetFreeID(ARHANDLE handle, int *pID);

// Description���Ƿ�����ǿ��ʵ��Ϣ
// Parameters��
// [in] handle: ͨ����
// [in] bEnable: 1��ʾ����0��ʾ������
// Return������0��ʾ�ɹ�; ����ֵ��ʾ������
AR_API int AR_EnableAR(ARHANDLE handle,int bEnable);

// Description����ǿ��ʵ��ǩ�ص�ģʽ
// Parameters��
// [in] handle: ͨ����
// [in] Mode: ��ʾ��ǩ�ص�ģʽ��0��ʾ��ǩ������λ�û��������б仯ʱ�ص���1��ʾÿ��I֡���˶���ص���Ĭ��Ϊģʽ1��
// Return������0��ʾ�ɹ�; ����ֵ��ʾ������
AR_API int AR_SetARLableCBMode(ARHANDLE handle,int Mode);

//���ܣ���ѯ��ǩ�б�
//����˵��
// handle��ͨ�����
// [out] pSei�����ڴ洢��ȡ�����б�
// [in/out] pNum�������ʾpSei�ܴ洢�ĸ����������ʾ��õĸ���
// Return������0��ʾ�ɹ�; ����ֵ��ʾ������
AR_API int AR_LableEx_Query(ARHANDLE handle, AR_LableEx *pSei, int *pNum);

//���ܣ���ѯ�豸��ǩ����
//����˵��
//handle��ͨ�����
//pDeviceMaxCount�����ڻ�ȡ�豸֧�ֵ�����ǩ����
//pCount�����ڻ�ȡ�Ѿ������ı�ǩ����
// Return������0��ʾ�ɹ�; ����ֵ��ʾ������
AR_API int AR_Lable_QueryCount(ARHANDLE handle, int *pDeviceMaxCount,int *pCount);

// Description:��ȡ��ǩ����XML�ַ���
// Parameters:
//	[in] handle: ͨ�����
//  [out] pXML: ��ȡXML����Ļ���(sdk�ⲿ���䣩���������豸����
//  [in][out] pnLenXML: �����ʾpXML����Ĵ�С�������ʾpXML�ַ�������
// Return:����0��ʾ�ɹ�; ����ֵ��ʾ������
AR_API int AR_Lable_Center(ARHANDLE handle,int nLableID, char *pXML,int *pnLenXML);

///////////////////////////////////ȫ�ֽӿ�///////////////////////////////////////
//���ܣ�����ĳ�����Ƿ��������Ļ�У��Լ�����Ļ�е�λ��
//����˵����
//DestX,DestY:���ڷ���Ŀ����ڵ�ǰ��Ļ�е�λ�ã���1920*1080��С����ĻΪ��׼�����أ�-1��-1����ʾ������Ļ��
//CurP, CurT, CurAngleH�ֱ�Ϊ�豸��ǰ��P,T,ˮƽ�Ž�
// p,t �ֱ�ΪĿ����P,Tֵ
AR_API int AR_GetXY(int &DestX, int &DestY, double p, double t, double CurP, double CurT, double CurAngleH);

//���ܣ�����ĳ�����Ƿ��������Ļ�У��Լ�����Ļ�е�λ��
//����˵����
//DestPt:���ڷ���Ŀ����ڵ�ǰ��Ļ�е�λ�ã���1920*1080��С����ĻΪ��׼�����أ�-1��-1����ʾ������Ļ��
//CurP, CurT, CurAngleH�ֱ�Ϊ�豸��ǰ��P,T,ˮƽ�Ž�
// p,t �ֱ�ΪĿ����P,Tֵ
//CurAngleV ��ֱ�ӳ��ǣ����ں�ˮƽ�ӳ��Ǽ��㻭�����
AR_API int AR_GetXYEx(int &DestX, int &DestY, double p, double t, double CurP, double CurT, double CurAngleH, double CurAngleV);

//���ܣ�������Ļ�е�ĳ�������豸��P,Tֵ
//����˵��
//DestP��DestT:�ֱ����ڷ���Ŀ������豸��P,Tֵ
//x,y��ʾĿ�������Ļ�е����꣬��1920*1080��С����ĻΪ��׼���������ֵ����ĻҪ��������ֵ
// CurP,CurT �ֱ�Ϊ��Ļ���ĵ����豸��P,Tֵ
AR_API int AR_GetPT(double &DestP, double &DestT, double x, double y, double CurP, double CurT, double CurAngleH);

//���ܣ�������Ļ�е�ĳ�������豸��P,Tֵ
//����˵��
//DestP��DestT:�ֱ����ڷ���Ŀ������豸��P,Tֵ
//x,y��ʾĿ�������Ļ�е����꣬��1920*1080��С����ĻΪ��׼���������ֵ����ĻҪ��������ֵ
// CurP,CurT �ֱ�Ϊ��Ļ���ĵ����豸��P,Tֵ
//CurAngleH,CurAngleV ˮƽ�ʹ�ֱ�ӳ���
AR_API int AR_GetPTEx(double &DestP, double &DestT, double x, double y, double CurP, double CurT, double CurAngleH, double CurAngleV);

AR_API int AR_EncodeAudio(char *pucAudioIn,int nAudioInLen,char *pucBinIn,int nBinLen,char *pucAudioOut,int *nAudioOutLen);
#endif