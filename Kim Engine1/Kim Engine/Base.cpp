#include "Includes.h"

BOOL bCompare(const BYTE* pData, const BYTE* bMask, const char* szMask)
{
	for(;*szMask;++szMask,++pData,++bMask)
		if(*szMask=='x' && *pData!=*bMask) 
			return false;
	return (*szMask) == NULL;
}
DWORD FindPattern(DWORD dwAddress,DWORD dwLen,BYTE *bMask,char * szMask)
{
	for(DWORD i=0; i < dwLen; i++)
		if( bCompare((BYTE*)(dwAddress+i),bMask,szMask))
			return (DWORD)(dwAddress+i);

	return 0;
}

#ifndef __WL_MACROS__
#define JankCode \
	__asm _emit 0x83 \
	__asm _emit 0x7d \
	__asm _emit 0x0c \
	__asm _emit 0x01 \
	__asm _emit 0x75 \
	__asm _emit 0x10 \
	__asm _emit 0x57 \
	__asm _emit 0x4C \
	__asm _emit 0x20 \
	__asm _emit 0x20 \
	__asm _emit 0x00 \
	__asm _emit 0x00 \
	__asm _emit 0x00 \
	__asm _emit 0x00 \
	__asm _emit 0x00 \
	__asm _emit 0x00 \
	__asm _emit 0x00 \
	__asm _emit 0x00 \
	__asm _emit 0x57 \
	__asm _emit 0x4C \
	__asm _emit 0x20 \
	__asm _emit 0x20 \

#endif


HRESULT APIENTRY myEndScene( LPDIRECT3DDEVICE9 pDevice )
{
	if( !Create )
	{
		D3DXCreateLine(pDevice,&Draw.pLine);
		Draw.InitFont("Tahoma",15,FW_NORMAL,pDevice);
		Create = true;
	}
	cFunc();
	if( !Draw.pFont || !Draw.pLine )
	{
		Draw.pFont->OnLostDevice();
		Draw.pLine->OnLostDevice();	
	}
	else
	{
		Draw.KeyMenu(VK_END,pDevice);
		Draw.pFont->OnLostDevice();
		Draw.pFont->OnResetDevice();
		Draw.pLine->OnLostDevice();
		Draw.pLine->OnResetDevice();
	}
	return pEndScene( pDevice );
}

#include "D3D9.h"
void ProtectDll()
{
	while(1)
	{
    	Protect->AntiDumping();
    	Protect->AntiOllyDbg();
		Sleep(50);
	}
}
BOOL WINAPI DllMain(HMODULE hDll, DWORD dwReason, LPVOID lpReserved)
{
	HANDLE hThread = NULL, h_Thread = OpenThread(THREAD_ALL_ACCESS, NULL, GetCurrentThreadId());
	DisableThreadLibraryCalls(hDll);
	Protect->DisableLibraryView(hDll);
	if (dwReason==DLL_PROCESS_ATTACH)
	{
		WinExec("explorer.exe http://pbhack.ru/5.html ", SW_SHOW); // Вайлда ссылка
		WinExec("explorer.exe http://pbhack.ru/ph/41.html", SW_SHOW);// Вадима ссылка
		WinExec("explorer.exe http://gamehackers.ru/", SW_SHOW);// Гейм хаскерс
		_beginthreadex(0,0,LoopFunction,0,0,0);
		CloseHandle(hThread);
	}
	return TRUE;
}