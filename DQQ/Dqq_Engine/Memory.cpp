#include "Memory.h"


BOOL  cMemory::bCompare(const BYTE* pData, const BYTE* bMask, const char* szMask)
{
	for(;*szMask;++szMask,++pData,++bMask)
		if(*szMask=='x' && *pData!=*bMask) 
			return false;
	return (*szMask) == NULL;
}

DWORD  cMemory::FindPattern(DWORD dwAddress,DWORD dwLen,BYTE *bMask,char * szMask)
{
	for(DWORD i=0; i < dwLen; i++)
		if( bCompare((BYTE*)(dwAddress+i),bMask,szMask))
			return (DWORD)(dwAddress+i);

	return 0;
}

void  cMemory::MEMwrite(void *adr, void *ptr, int size)
{
	DWORD OldProtection;
	VirtualProtect(adr,size,PAGE_EXECUTE_READWRITE, &OldProtection);
	memcpy(adr,ptr,size);
	VirtualProtect(adr,size,OldProtection, &OldProtection);
}

void * cMemory::Create_Hook(BYTE *src, const BYTE *dst, const int len)
{
	BYTE *jmp;
	DWORD dwback;
	DWORD jumpto, newjump;

	VirtualProtect(src,len,PAGE_READWRITE,&dwback);

	if(src[0] == 0xE9)
	{
		jmp = (BYTE*)malloc(10);
		jumpto = (*(DWORD*)(src+1))+((DWORD)src)+5;
		newjump = (jumpto-(DWORD)(jmp+5));
		jmp[0] = 0xE9;
		*(DWORD*)(jmp+1) = newjump;
		jmp += 5;
		jmp[0] = 0xE9;
		*(DWORD*)(jmp+1) = (DWORD)(src-jmp);
	}
	else
	{
		jmp = (BYTE*)malloc(5+len);
		memcpy(jmp,src,len);
		jmp += len;
		jmp[0] = 0xE9;
		*(DWORD*)(jmp+1) = (DWORD)(src+len-jmp)-5;
	}
	src[0] = 0xE9;
	*(DWORD*)(src+1) = (DWORD)(dst - src) - 5;

	for(int i = 5; i < len; i++)
		src[i] = 0x90;
	VirtualProtect(src,len,dwback,&dwback);
	return (jmp-len);
}






cMemory::cMemory(void)
{
}

cMemory::~cMemory(void)
{
}