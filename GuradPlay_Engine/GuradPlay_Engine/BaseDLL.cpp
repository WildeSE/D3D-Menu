/*
|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
||||  Source by iDReeM                                                       ||||
||||  Мастурбация перед просмотром проека поможет закрыть глаза на быдлокод. ||||
|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
*/
#include "stdafx.h"
#include "Variables.h"
#include "Menu.h"
#include "cDraw.h"
cDraw Draw;
#include "cProtect.h"
cProtect *Protect;
#include "Memory.h"
cMemory *MemHack;
#include "MemHack.h"
#include "ESP.h"

#define Start_Thread(Function) CreateThread(0,0,(LPTHREAD_START_ROUTINE)Function,0,0,0);

typedef HRESULT	(WINAPI* oEndScene)(LPDIRECT3DDEVICE9 pDevice);
oEndScene pEndScene = NULL;

bool Engine_Create;


HRESULT APIENTRY myEndScene( LPDIRECT3DDEVICE9 pDevice )
{
	if( !Engine_Create )
	{
		D3DXCreateLine(pDevice,&Draw.pLine);
		Draw.InitFont("Tahoma",13,FW_BOLD,pDevice);
		Engine_Create = true;
	}
	Draw.KeyMenu(VK_END,pDevice);
	if( !Draw.pFont || !Draw.pLine )
	{
		Draw.pFont->OnLostDevice();
		Draw.pLine->OnLostDevice();	
	}
	else
	{
		
	
		Draw.pFont->OnLostDevice();
		Draw.pFont->OnResetDevice();
		Draw.pLine->OnLostDevice();
		Draw.pLine->OnResetDevice();
	}
	return pEndScene( pDevice );
}

#include "D3D9Hook.h"

void _stdcall Threads()
{
	
	Start_Thread(LoopFunction);
	
}
BOOL WINAPI DllMain(HMODULE hDll, DWORD dwReason, LPVOID lpReserved)
{
	DisableThreadLibraryCalls(hDll);
	if (dwReason==DLL_PROCESS_ATTACH)
	{
		Protect->_HideModule(hDll);
		Start_Thread(LoopFunction);
	}
	return TRUE;
}