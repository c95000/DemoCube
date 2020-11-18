// System.h: interface for the System class.
//
//////////////////////////////////////////////////////////////////////
#if !defined(AFX_SYSTEM_H__CB297B79_BC4F_4E4F_A93D_BACE271F623A__INCLUDED_)
#define AFX_SYSTEM_H__CB297B79_BC4F_4E4F_A93D_BACE271F623A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ARCL.h"
#include "cross.h"

#ifdef __cplusplus
extern "C" {
#endif 

ARCL_API void System_Sleep(unsigned long Msec);
ARCL_API unsigned int System_GetSecond();
ARCL_API unsigned int System_GetMSecond();


/////////////////////////////////////////////////////////////////////////
struct _GThread
{
	void* m_Data;
	BOOL m_Active;
	char m_strName[256];
	void* m_func;

#ifdef WIN32
	unsigned long m_ThreadID;
	HANDLE m_hThread;
#else
	pthread_t m_hThread;
#endif // WIN32
};
typedef struct _GThread GThread;

typedef DWORD (*FUNC)(GThread*);

ARCL_API int GThread_Start(GThread * pth,FUNC func,void* Data,const char* szName);
ARCL_API BOOL GThread_Stop(GThread *pThread);


///////////////////////////////////////////////////////////////////////////
typedef struct GLock  
{	

#ifdef WIN32
	CRITICAL_SECTION CS;
#else	
	pthread_mutex_t Mutex;
#endif

}GLock;


ARCL_API int GLock_Init(GLock *plock);
ARCL_API BOOL GLock_Deinit(GLock *plock);
ARCL_API void GLock_Lock(GLock *plock);
ARCL_API void GLock_Unlock(GLock *plock);

#ifdef __cplusplus
}
#endif 

#endif // !defined(AFX_SYSTEM_H__CB297B79_BC4F_4E4F_A93D_BACE271F623A__INCLUDED_)
