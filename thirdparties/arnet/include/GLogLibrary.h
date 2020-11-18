#pragma once

#include "ARCL.h"

#include <stdio.h>
#include <string.h>

#include "System.h"

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

/*日志级别:级别由高到低，LFATAL最高，LDEBUG最低*/
#define LFATAL  5
#define LERROR  4
#define LWARN   3
#define LINFO   2
#define LDEBUG  1

/*文件创建方式*/
#define WREWIND  1		//回卷
#define WCREATE  2		//新建

/*日志输出方式，控制台或文件*/
#define MCONSOLE   1	//控制台
#define MFILE      2	//文件

/*错误码定义*/
#define ERROR_LOGLIBRARY_OPER_SUCCESS 3000 
#define ERROR_LOGLIBRARY_START (3000+4000)
#define ERROR_LOGLIBRARY_DIR_NOT_EXIST		(ERROR_LOGLIBRARY_START + 1) //路径错误
#define ERROR_LOGLIBRARY_FILE_NOT_OPEN		(ERROR_LOGLIBRARY_START + 2) //文件没有打开
#define ERROR_LOGLIBRARY_FILESIZE_ILLEGAL	(ERROR_LOGLIBRARY_START + 3) //大小非法
#define ERROR_LOGLIBRARY_FILEWAY_ILLEGAL	(ERROR_LOGLIBRARY_START + 4) //文件创建策略非法
#define ERROR_LOGLIBRARY_LOGLEVEL_ILLEGAL	(ERROR_LOGLIBRARY_START + 5) //日志等级非法
#define ERROR_LOGLIBRARY_LOGMEDIUM_ILLEGAL	(ERROR_LOGLIBRARY_START + 6) //日志输出介质非法
#define ERROR_LOGLIBRARY_MSGSIZE_ILLEGAL	(ERROR_LOGLIBRARY_START + 7) //日志信息大小非法
#define ERROR_LOGLIBRARY_STRING_ILLEGAL		(ERROR_LOGLIBRARY_START + 8) //字符串大小非法
#define ERROR_LOGLIBRARY_MKDIR_FAIl			(ERROR_LOGLIBRARY_START + 9) //创建文件夹失败
#define ERROR_LOGLIBRARY_DISK_ERROR         (ERROR_LOGLIBRARY_START + 10)//磁盘错误
//#include "ILogLibrary.h"

#define LOG_MAX_SIZE				2*1024*1024		//日志大小
#define LOG_MEDIUM_NUM				2				//日志媒介数目（控制台或文件）
#define LOG_LEVEL_NUM				10				//日志等级数目
#define LOG_DIR_NAME_NUM			512				//路径最大长度
#define LOG_DOCUMENT_NAME_NUM		32				//日志文件夹名最大长度
#define LOG_FILE_NAME_NUM			64				//日志文件名最大长度
#define LOG_EX_NAME_NUM				32				//日志文件扩展名
class ARCL_CLASS GMLogLibrary/*:public ILogLibrary*/
{
public:
	GMLogLibrary(void);
	virtual ~GMLogLibrary(void);

public:

	/*各媒质对应等级信息*/
	typedef struct 
	{
		unsigned int uiMedium;//媒质
		int bFlag;//是否有效
		unsigned int uiLevel;//对应等级
	}StruLogWay;

private:
	FILE *m_pfLog;//日志文件句柄
	FILE *m_pfile;

	char m_strDir[LOG_DIR_NAME_NUM];//日志路径,由用户设定
	char m_strDocu[LOG_DOCUMENT_NAME_NUM];//当前日志所在文件夹，是根据当前日期自动生成,型如"log2010_12_31"
	char m_strFileName[LOG_FILE_NAME_NUM];//日志文件名
	char m_strFileEx[LOG_EX_NAME_NUM];	 //日志文件扩展名
    char m_strWholeName[1024];//日志全路径

	unsigned long long m_uiLogSize;//日志大小
	unsigned long long m_uiCurSize; // 日志当前大小
	unsigned int m_uiWay;//文件策略，回卷和新建
	StruLogWay m_stLogWay[LOG_MEDIUM_NUM];//记录日志各种输出方式及相关等级信息
	GLock m_Mutex;//锁，支持多线程
	int bDiskReady;// 磁盘准备好标志
public:

	int  SetLogDir(const char *pszDir,const char *pszExtName);//设置日志路径
	int  SetLogSize(unsigned int uiWay,unsigned int uiSize);// 设置日志大小及是否回卷
	int  SetLogLevel(unsigned int uiMedium,unsigned int uiLevel);//设置日志输出方式（控制台或文件）及对应日志级别
	int  Log(unsigned int uiLevel,char *pszPrefix,char  *pszFormat,...);//支持变长
private:
	int GenerateLogDir(const char *pszDir);
	int WriteToFile(const char *pszMsg);
	int GetTimeStr(char *pbuf);
	int CreatLogDir(char *pszDir);
	int CountDiskFreeSpace(const char *pDir,unsigned long long &uiTotalFreeSize);// 获取磁盘可用剩余空间

};
