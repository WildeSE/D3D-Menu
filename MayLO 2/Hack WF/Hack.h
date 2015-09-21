#include <Psapi.h>

#pragma warning(disable: 4102)
BOOL  bCompare(const BYTE* pData, const BYTE* bMask, const char* szMask)
{
for(;*szMask;++szMask,++pData,++bMask)
if(*szMask=='x' && *pData!=*bMask) 
return false;
return (*szMask) == NULL;
}
DWORD  FindPattern(DWORD dwAddress,DWORD dwLen,BYTE *bMask,char * szMask)
{
	for(DWORD i=0; i < dwLen; i++)
		if( bCompare((BYTE*)(dwAddress+i),bMask,szMask))
			return (DWORD)(dwAddress+i);
	return 0;
}

void MEMwrite(void *adr, void *ptr, int size)
{
	DWORD OldProtection;
	VirtualProtect(adr,size,PAGE_EXECUTE_READWRITE, &OldProtection);
	memcpy(adr,ptr,size);
	VirtualProtect(adr,size,OldProtection, &OldProtection);
}

DWORD* FindDevice(DWORD Base)
{
	for(long i= 0,n = 0; i < 0x128000; i++ )
	{
        if(*(BYTE *)(Base+i+0x00)==0xC7)n++;
	    if(*(BYTE *)(Base+i+0x01)==0x06)n++;
	    if(*(BYTE *)(Base+i+0x06)==0x89)n++;
	    if(*(BYTE *)(Base+i+0x07)==0x86)n++;	
        if(*(BYTE *)(Base+i+0x0C)==0x89)n++;
	    if(*(BYTE *)(Base+i+0x0D)==0x86)n++;

	    if(n == 6) return (DWORD*)
			(Base + i + 2);n = 0;
	}
	return(0);
}

void* DetourFunction(BYTE* src, const BYTE* dest) 
{ 
 PBYTE jump = (PBYTE)malloc(10); 

 DWORD dwVirtualProtectBackup; 
 VirtualProtect(src, 5, PAGE_READWRITE, &dwVirtualProtectBackup); 

 memcpy(jump, src, 5); 
 jump += 5; 

 jump[0] = 0xE9; 
 *(PDWORD)(jump + 1) = (DWORD)(src + 5 - jump) - 5; 

 src[0] = 0xE9; 
 *(PDWORD)(src + 1) = (DWORD)(dest - src) - 5; 

 VirtualProtect(src, 5, dwVirtualProtectBackup, &dwVirtualProtectBackup); 

 return jump - 5; 
}

void *DetourCreate(BYTE *src, const BYTE *dst, const int len)
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

#ifndef _Hide    
void  EraseHeaders(HINSTANCE hModule1)
{
	PIMAGE_DOS_HEADER pDoH; 
	PIMAGE_NT_HEADERS pNtH;
	DWORD i, ersize, protect;
	if (!hModule1) return;
	pDoH = (PIMAGE_DOS_HEADER)(hModule1);
	pNtH = (PIMAGE_NT_HEADERS)((LONG)hModule1 + ((PIMAGE_DOS_HEADER)hModule1)->e_lfanew);
	ersize = sizeof(IMAGE_DOS_HEADER);
	if ( VirtualProtect(pDoH, ersize, PAGE_READWRITE, &protect) )
	{
		for ( i=0; i < ersize; i++ )
				*(BYTE*)((BYTE*)pDoH + i) = 0;
	}
	ersize = sizeof(IMAGE_NT_HEADERS);
	if ( pNtH && VirtualProtect(pNtH, ersize, PAGE_READWRITE, &protect) )
	{
		for ( i=0; i < ersize; i++ )
				*(BYTE*)((BYTE*)pNtH + i) = 0;
	}
	return;
}

typedef struct _UNICODE_STRING 
{
	USHORT Length;
	USHORT MaximumLength;
	PWSTR Buffer;
} UNICODE_STRING, *PUNICODE_STRING;

typedef struct _ModuleInfoNode
{
	LIST_ENTRY LoadOrder;
	LIST_ENTRY InitOrder;
	LIST_ENTRY MemoryOrder;
	HMODULE baseAddress;
	unsigned long entryPoint;
	unsigned int size;
	UNICODE_STRING fullPath;
	UNICODE_STRING name;
	unsigned long flags;
	unsigned short LoadCount;
	unsigned short TlsIndex;
	LIST_ENTRY HashTable;
	unsigned long timestamp;
} ModuleInfoNode, *pModuleInfoNode;

typedef struct _ProcessModuleInfo
{
	unsigned int size;
	unsigned int initialized;
	HANDLE SsHandle;
	LIST_ENTRY LoadOrder;
	LIST_ENTRY InitOrder;
	LIST_ENTRY MemoryOrder;
} ProcessModuleInfo, *pProcessModuleInfo;

#define UNLINK(x) (x).Blink->Flink = (x).Flink; \
	(x).Flink->Blink = (x).Blink;

void* CreateHook(DWORD srce, const BYTE *dst, const int len)
{
	BYTE *jmp;
	DWORD dwback;
	DWORD jumpto, newjump;
	BYTE* src = (BYTE*)srce;

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
#endif