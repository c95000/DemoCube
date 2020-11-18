#ifndef BASICOPTION_DEF_H
#define BASICOPTION_DEF_H


#ifdef BASICOPTION_EXPORTS
#define BASICOPTION_API  extern "C" __declspec(dllexport) 

#else
#define BASICOPTION_API  extern "C" __declspec(dllimport)
#endif

#define BAS_SERVER_NAME_LEN 36
#define BAS_PRODUCT_MODEL_LEN 36
#define BAS_DEVICE_SERIAL_LEN 20
#define BAS_NET_MAC_LEN 20
#define BAS_IP_ADDR_LEN 16

typedef struct
{
	char DeviceName[BAS_SERVER_NAME_LEN];//BAS_SERVER_NAME_LEN=36
	char ProductModel[BAS_PRODUCT_MODEL_LEN];//BAS_PRODUCT_MODEL_LEN=36
	char DeviceSerial[BAS_DEVICE_SERIAL_LEN];//序列号，BAS_DEVICE_SERIAL_LEN=20

	char NetMAC[BAS_NET_MAC_LEN];//BAS_NET_MAC_LEN=20
	char IpAddr[BAS_IP_ADDR_LEN];//BAS_IP_ADDR_LEN=16
	char NetMask[BAS_IP_ADDR_LEN];//子网掩码
	char GateWayIp[BAS_IP_ADDR_LEN];//网关
	char DnsSvrIpFirst[BAS_IP_ADDR_LEN];//首选DNS
	char DnsSvrIpSecond[BAS_IP_ADDR_LEN];//备用DNS
}TBASDeviceInfo;

/********************************************************
/** 函数：BSC_Init
/** 功能：基本操作初始化
/** 参数：无
/** 返回：TRUE 初始化成功
/**			FALSE 失败
**********************************************************/
BASICOPTION_API BOOL BSC_Init();

/********************************************************
/** 函数：BSC_DeInit
/** 功能：基本操作去初始化
/** 参数：无
/** 返回：无
**********************************************************/
BASICOPTION_API BOOL BSC_DeInit();

/********************************************************
/** 函数：BSC_GetNum
/** 功能：获取当前在线设备的个数
/** 参数：无
/** 返回：当前在线设备的个数
**********************************************************/
BASICOPTION_API int BSC_GetNum();

/********************************************************
/** 函数：BSC_GetDevInfo
/** 功能：获取在线设备信息
/** 参数：pstAswFindDev 存储在线设备信息的数组指针
/**		   pnNum [in] 传进pstAswFindDev数组长度
/**				  [out] 实际存储的在线设备量
/** 返回：TRUE 成功
/**			FALSE 失败
**********************************************************/
BASICOPTION_API BOOL BSC_GetDevInfo(TBASDeviceInfo *pstDevInfo, int *pnNum);
#endif