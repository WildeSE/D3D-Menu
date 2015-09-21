#pragma once
#include <windows.h>

#define MB(s,t) MessageBox(NULL, s, t, MB_OK);

#define START_ROUTINE(Function) CreateThread(0,0,(LPTHREAD_START_ROUTINE)Function,0,0,0);

class cMemory
{
public:
	cMemory(void);
	~cMemory(void);

	BOOL  bCompare(const BYTE* pData, const BYTE* bMask, const char* szMask);
	DWORD FindPattern(DWORD dwAddress,DWORD dwLen,BYTE *bMask,char * szMask);
	void  MEMwrite(void *adr, void *ptr, int size);
	void *Create_Hook(BYTE *src, const BYTE *dst, const int len);

};
