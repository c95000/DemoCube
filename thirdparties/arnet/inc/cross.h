#ifndef _SUPPORT_CROSS
#define _SUPPORT_CROSS

#ifdef WIN32
#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
#include <windows.h>
#include <MMSystem.h>
//#include <WINSOCK2.H>
//#include <Ws2tcpip.h>
#include <process.h>
#include <sys\timeb.h>
#include <io.h>
#include <direct.h>
#include <sys\stat.h>
#include "Psapi.h"
#include "crtdefs.h"
#endif

#ifdef __GNUC__
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/sysinfo.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <stdlib.h>
#include <semaphore.h>
#include <signal.h>
#include <netdb.h>
#include <pthread.h>
#include <errno.h>
#include <exception>
#include <stdint.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <stdio.h>

typedef unsigned long long UINT64;

typedef void *PVOID;
typedef void *LPVOID;
typedef const char* LPCSTR;
typedef char  TCHAR;
typedef char* LPSTR;
typedef char* LPTSTR;
typedef const char* LPCTSTR;
typedef unsigned int UINT;
typedef unsigned int DWORD;
//typedef int                 BOOL;
typedef unsigned char       BYTE;
typedef unsigned short      WORD;
typedef unsigned int        *PUINT;

#ifndef NULL
#define NULL 0
#endif
#ifndef TRUE
#define TRUE true
#endif
#ifndef FALSE
#define FALSE false
#endif

#ifndef BOOL
#define BOOL int
#endif // 


#define CALLBACK 

#endif

#include <time.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>
#include <fcntl.h>

////////////////////////////////////////////////////////
#if defined(_DEBUG) || defined(_DBG)
#define PRINTF printf
#else
#define PRINTF
#endif

#endif
