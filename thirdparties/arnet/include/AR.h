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
// Description:创建一个通道
// Return:返回零表示失败，其他值为通道句柄
AR_API ARHANDLE AR_VideoOpen();

//Description:设置增强现实标签回调函数
// Parameters:
// [in] handle:通道句柄
// [in] ARLableCBFun: 标签回调函数
// [in] nUser：用户数据
// Return：返回0表示成功; 其他值表示错误码
AR_API int AR_SetARLableExCallBack(ARHANDLE handle,fARLableExCBFun ARLableCBFun,void* pUser);

//Description:设置增强现实参数回调函数
// Parameters:
// [in] handle:通道句柄
// [in] ARParamCBFun: 参数回调函数
// [in] nUser：用户数据
// Return：返回0表示成功; 其他值表示错误码
AR_API int AR_SetARParamCallBack(ARHANDLE handle,fARParamCBFun ARParamCBFun,void* pUser);

//Description:设置增强现实图片回调函数
// Parameters:
// [in] handle:通道句柄
// [in] CBFun: 图片回调函数
// [in] pUser：用户数据
// Return：返回0表示成功; 其他值表示错误码
AR_API int AR_SetARPictureCallBack(ARHANDLE handle,fARPictureCBFun CBFun,void* pUser);

//Description:设置人脸检测对象回调函数
// Parameters:
// [in] handle:通道句柄
// [in] CBFun: 对象回调函数
// [in] pUser：用户数据
// Return：返回0表示成功; 其他值表示错误码
AR_API int AR_SetARFaceDetectCallBack(ARHANDLE handle, fARFaceDetectCBFun CBFun, void* pUser);

//Description: 设备主动上送信息回调设置
//Parameters:
//[in] lLoginID:通道句柄
//[in] fPostMsgCallBack:信息回调函数
//[in] pUser：回调函数用户数据
//Return: 返回0表示成功; 其他值表示错误码    
AR_API int AR_SetPostMsgCallBack(ARHANDLE handle, fARPostMsgCallBack fPostMsgCallBack, void *pUser);

//Description:设置增强现实原始数据回调函数
// Parameters:
// [in] handle:通道句柄
// [in] CBFun: 回调函数
// [in] pUser：用户数据
// Return：返回0表示成功; 其他值表示错误码
AR_API int AR_SetARRawDataCallBack(ARHANDLE handle,fARRawDataCBFun CBFun,void* pUser);

// Description:输入一帧数据到解码库（目前必须一帧一帧输入数据，
//不允许输入不完整的帧或者一次输入多于一帧的数据）
// Parameters:
//	[in] handle: 通道句柄
//	[in] pBuf：流数据首地址
//	[in] nLen: 流数据长度
// Return: 返回0表示成功; 其他值表示错误码
AR_API int AR_VideoInputAFrame(ARHANDLE handle,unsigned char *pBuf,int nLen);

// Description:关闭解码句柄
// Parameters:
//	[in] handle: 通道句柄
// Return:返回0表示成功; 其他值表示错误码
AR_API int AR_VideoClose(ARHANDLE handle);

// 描述：获取一个空闲的标签ID,用于添加标签
// 参数：
// [in] handle: 通道号
// 返回值：返回0表示成功; 其他值表示错误码
AR_API int AR_GetFreeID(ARHANDLE handle, int *pID);

// Description：是否处理增强现实信息
// Parameters：
// [in] handle: 通道号
// [in] bEnable: 1表示处理，0表示不处理
// Return：返回0表示成功; 其他值表示错误码
AR_API int AR_EnableAR(ARHANDLE handle,int bEnable);

// Description：增强现实标签回调模式
// Parameters：
// [in] handle: 通道号
// [in] Mode: 表示标签回调模式，0表示标签数量、位置或者内容有变化时回调；1表示每次I帧来了都会回调。默认为模式1。
// Return：返回0表示成功; 其他值表示错误码
AR_API int AR_SetARLableCBMode(ARHANDLE handle,int Mode);

//功能：查询标签列表
//参数说明
// handle：通道句柄
// [out] pSei：用于存储获取到的列表
// [in/out] pNum：输入表示pSei能存储的个数，输出表示获得的个数
// Return：返回0表示成功; 其他值表示错误码
AR_API int AR_LableEx_Query(ARHANDLE handle, AR_LableEx *pSei, int *pNum);

//功能：查询设备标签数量
//参数说明
//handle：通道句柄
//pDeviceMaxCount：用于获取设备支持的最大标签个数
//pCount：用于获取已经创建的标签个数
// Return：返回0表示成功; 其他值表示错误码
AR_API int AR_Lable_QueryCount(ARHANDLE handle, int *pDeviceMaxCount,int *pCount);

// Description:获取标签居中XML字符串
// Parameters:
//	[in] handle: 通道句柄
//  [out] pXML: 获取XML命令的缓冲(sdk外部分配），用来往设备发送
//  [in][out] pnLenXML: 输入表示pXML缓冲的大小，输出表示pXML字符串长度
// Return:返回0表示成功; 其他值表示错误码
AR_API int AR_Lable_Center(ARHANDLE handle,int nLableID, char *pXML,int *pnLenXML);

///////////////////////////////////全局接口///////////////////////////////////////
//功能：计算某个点是否出现在屏幕中，以及在屏幕中的位置
//参数说明：
//DestX,DestY:用于返回目标点在当前屏幕中的位置，以1920*1080大小的屏幕为基准，返回（-1，-1）表示不再屏幕中
//CurP, CurT, CurAngleH分别为设备当前的P,T,水平张角
// p,t 分别为目标点的P,T值
AR_API int AR_GetXY(int &DestX, int &DestY, double p, double t, double CurP, double CurT, double CurAngleH);

//功能：计算某个点是否出现在屏幕中，以及在屏幕中的位置
//参数说明：
//DestPt:用于返回目标点在当前屏幕中的位置，以1920*1080大小的屏幕为基准，返回（-1，-1）表示不再屏幕中
//CurP, CurT, CurAngleH分别为设备当前的P,T,水平张角
// p,t 分别为目标点的P,T值
//CurAngleV 竖直视场角，用于和水平视场角计算画面比例
AR_API int AR_GetXYEx(int &DestX, int &DestY, double p, double t, double CurP, double CurT, double CurAngleH, double CurAngleV);

//功能：计算屏幕中的某个点在设备的P,T值
//参数说明
//DestP，DestT:分别用于返回目标点在设备的P,T值
//x,y表示目标点在屏幕中的坐标，以1920*1080大小的屏幕为基准，不是这个值的屏幕要换算成这个值
// CurP,CurT 分别为屏幕中心点在设备的P,T值
AR_API int AR_GetPT(double &DestP, double &DestT, double x, double y, double CurP, double CurT, double CurAngleH);

//功能：计算屏幕中的某个点在设备的P,T值
//参数说明
//DestP，DestT:分别用于返回目标点在设备的P,T值
//x,y表示目标点在屏幕中的坐标，以1920*1080大小的屏幕为基准，不是这个值的屏幕要换算成这个值
// CurP,CurT 分别为屏幕中心点在设备的P,T值
//CurAngleH,CurAngleV 水平和垂直视场角
AR_API int AR_GetPTEx(double &DestP, double &DestT, double x, double y, double CurP, double CurT, double CurAngleH, double CurAngleV);

AR_API int AR_EncodeAudio(char *pucAudioIn,int nAudioInLen,char *pucBinIn,int nBinLen,char *pucAudioOut,int *nAudioOutLen);
#endif