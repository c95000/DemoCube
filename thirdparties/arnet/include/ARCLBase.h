#ifndef __ARCL_BASE_H__
#define __ARCL_BASE_H__

#include "ARCL.h"
#include "cross.h"

class ARCL_CLASS CGObject
{
public:
	CGObject(void);
	~CGObject(void);

	void *operator new(size_t size);
	void operator delete(void *p);
};

class ARCL_CLASS CGBuffer : public CGObject
{
	int m_bIsMyMalloc;
public:
	unsigned int uiDateLen; //数据长度
	unsigned int uiBufLen;	// 缓冲长度
	char *pBuf;	//缓冲首地址

	CGBuffer();
	CGBuffer(unsigned int uiAllocBufLen);
	~CGBuffer();

	int Resize(unsigned int uiNewAllocLen);
};

#endif