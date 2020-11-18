#pragma once

#include "ARCL.h"

#include <stdio.h>
#include <string.h>

#include "System.h"

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

/*��־����:�����ɸߵ��ͣ�LFATAL��ߣ�LDEBUG���*/
#define LFATAL  5
#define LERROR  4
#define LWARN   3
#define LINFO   2
#define LDEBUG  1

/*�ļ�������ʽ*/
#define WREWIND  1		//�ؾ�
#define WCREATE  2		//�½�

/*��־�����ʽ������̨���ļ�*/
#define MCONSOLE   1	//����̨
#define MFILE      2	//�ļ�

/*�����붨��*/
#define ERROR_LOGLIBRARY_OPER_SUCCESS 3000 
#define ERROR_LOGLIBRARY_START (3000+4000)
#define ERROR_LOGLIBRARY_DIR_NOT_EXIST		(ERROR_LOGLIBRARY_START + 1) //·������
#define ERROR_LOGLIBRARY_FILE_NOT_OPEN		(ERROR_LOGLIBRARY_START + 2) //�ļ�û�д�
#define ERROR_LOGLIBRARY_FILESIZE_ILLEGAL	(ERROR_LOGLIBRARY_START + 3) //��С�Ƿ�
#define ERROR_LOGLIBRARY_FILEWAY_ILLEGAL	(ERROR_LOGLIBRARY_START + 4) //�ļ��������ԷǷ�
#define ERROR_LOGLIBRARY_LOGLEVEL_ILLEGAL	(ERROR_LOGLIBRARY_START + 5) //��־�ȼ��Ƿ�
#define ERROR_LOGLIBRARY_LOGMEDIUM_ILLEGAL	(ERROR_LOGLIBRARY_START + 6) //��־������ʷǷ�
#define ERROR_LOGLIBRARY_MSGSIZE_ILLEGAL	(ERROR_LOGLIBRARY_START + 7) //��־��Ϣ��С�Ƿ�
#define ERROR_LOGLIBRARY_STRING_ILLEGAL		(ERROR_LOGLIBRARY_START + 8) //�ַ�����С�Ƿ�
#define ERROR_LOGLIBRARY_MKDIR_FAIl			(ERROR_LOGLIBRARY_START + 9) //�����ļ���ʧ��
#define ERROR_LOGLIBRARY_DISK_ERROR         (ERROR_LOGLIBRARY_START + 10)//���̴���
//#include "ILogLibrary.h"

#define LOG_MAX_SIZE				2*1024*1024		//��־��С
#define LOG_MEDIUM_NUM				2				//��־ý����Ŀ������̨���ļ���
#define LOG_LEVEL_NUM				10				//��־�ȼ���Ŀ
#define LOG_DIR_NAME_NUM			512				//·����󳤶�
#define LOG_DOCUMENT_NAME_NUM		32				//��־�ļ�������󳤶�
#define LOG_FILE_NAME_NUM			64				//��־�ļ�����󳤶�
#define LOG_EX_NAME_NUM				32				//��־�ļ���չ��
class ARCL_CLASS GMLogLibrary/*:public ILogLibrary*/
{
public:
	GMLogLibrary(void);
	virtual ~GMLogLibrary(void);

public:

	/*��ý�ʶ�Ӧ�ȼ���Ϣ*/
	typedef struct 
	{
		unsigned int uiMedium;//ý��
		int bFlag;//�Ƿ���Ч
		unsigned int uiLevel;//��Ӧ�ȼ�
	}StruLogWay;

private:
	FILE *m_pfLog;//��־�ļ����
	FILE *m_pfile;

	char m_strDir[LOG_DIR_NAME_NUM];//��־·��,���û��趨
	char m_strDocu[LOG_DOCUMENT_NAME_NUM];//��ǰ��־�����ļ��У��Ǹ��ݵ�ǰ�����Զ�����,����"log2010_12_31"
	char m_strFileName[LOG_FILE_NAME_NUM];//��־�ļ���
	char m_strFileEx[LOG_EX_NAME_NUM];	 //��־�ļ���չ��
    char m_strWholeName[1024];//��־ȫ·��

	unsigned long long m_uiLogSize;//��־��С
	unsigned long long m_uiCurSize; // ��־��ǰ��С
	unsigned int m_uiWay;//�ļ����ԣ��ؾ���½�
	StruLogWay m_stLogWay[LOG_MEDIUM_NUM];//��¼��־���������ʽ����صȼ���Ϣ
	GLock m_Mutex;//����֧�ֶ��߳�
	int bDiskReady;// ����׼���ñ�־
public:

	int  SetLogDir(const char *pszDir,const char *pszExtName);//������־·��
	int  SetLogSize(unsigned int uiWay,unsigned int uiSize);// ������־��С���Ƿ�ؾ�
	int  SetLogLevel(unsigned int uiMedium,unsigned int uiLevel);//������־�����ʽ������̨���ļ�������Ӧ��־����
	int  Log(unsigned int uiLevel,char *pszPrefix,char  *pszFormat,...);//֧�ֱ䳤
private:
	int GenerateLogDir(const char *pszDir);
	int WriteToFile(const char *pszMsg);
	int GetTimeStr(char *pbuf);
	int CreatLogDir(char *pszDir);
	int CountDiskFreeSpace(const char *pDir,unsigned long long &uiTotalFreeSize);// ��ȡ���̿���ʣ��ռ�

};
