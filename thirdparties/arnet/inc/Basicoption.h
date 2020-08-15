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
	char DeviceSerial[BAS_DEVICE_SERIAL_LEN];//���кţ�BAS_DEVICE_SERIAL_LEN=20

	char NetMAC[BAS_NET_MAC_LEN];//BAS_NET_MAC_LEN=20
	char IpAddr[BAS_IP_ADDR_LEN];//BAS_IP_ADDR_LEN=16
	char NetMask[BAS_IP_ADDR_LEN];//��������
	char GateWayIp[BAS_IP_ADDR_LEN];//����
	char DnsSvrIpFirst[BAS_IP_ADDR_LEN];//��ѡDNS
	char DnsSvrIpSecond[BAS_IP_ADDR_LEN];//����DNS
}TBASDeviceInfo;

/********************************************************
/** ������BSC_Init
/** ���ܣ�����������ʼ��
/** ��������
/** ���أ�TRUE ��ʼ���ɹ�
/**			FALSE ʧ��
**********************************************************/
BASICOPTION_API BOOL BSC_Init();

/********************************************************
/** ������BSC_DeInit
/** ���ܣ���������ȥ��ʼ��
/** ��������
/** ���أ���
**********************************************************/
BASICOPTION_API BOOL BSC_DeInit();

/********************************************************
/** ������BSC_GetNum
/** ���ܣ���ȡ��ǰ�����豸�ĸ���
/** ��������
/** ���أ���ǰ�����豸�ĸ���
**********************************************************/
BASICOPTION_API int BSC_GetNum();

/********************************************************
/** ������BSC_GetDevInfo
/** ���ܣ���ȡ�����豸��Ϣ
/** ������pstAswFindDev �洢�����豸��Ϣ������ָ��
/**		   pnNum [in] ����pstAswFindDev���鳤��
/**				  [out] ʵ�ʴ洢�������豸��
/** ���أ�TRUE �ɹ�
/**			FALSE ʧ��
**********************************************************/
BASICOPTION_API BOOL BSC_GetDevInfo(TBASDeviceInfo *pstDevInfo, int *pnNum);
#endif