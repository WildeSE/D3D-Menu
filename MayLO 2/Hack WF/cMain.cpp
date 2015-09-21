#include "stdafx.h"
#include "Protection.h"
#include "cVar.h"
#include "Menu.h"
#include "cDraw.h"
cDraw Draw;
#include "Hack.h"
#include "Font.h"
#include "esp.h"
cVar Varm;

typedef long (__stdcall *oReset  )( IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters);
typedef IDirect3D9* (__stdcall *DIRECT3DCREATE9)(unsigned int);
typedef HRESULT	(WINAPI* oEndScene)(LPDIRECT3DDEVICE9 pDevice);
oEndScene pEndScene = NULL;

oReset pReset;
DWORD WINAPI FindWin(LPVOID);
BYTE CodeFragmentES[5] = {0, 0, 0, 0, 0};
BYTE CodeFragmentR[5] = {0, 0, 0, 0, 0};
BYTE jmpbES[5] = {0, 0, 0, 0, 0};
BYTE jmpbR[5] = {0, 0, 0, 0, 0};

DWORD oldprotectES = 0;
DWORD oldprotectR = 0;

void NoBan()
{
	MEMwrite((void*)(0x122A621), (int*)(PBYTE)"\xEB\xD4", 2);
	MEMwrite((void*)(0xC61918), (int*)(PBYTE)"\x84\xC0\x90\x90", 4);
	MEMwrite((void*)(0x4F596C), (int*)(PBYTE)"\x59\x4C\xEB\x84", 4);
	MEMwrite((void*)(0x122A610), (int*)(PBYTE)"\x00\xEB\xD4\x90", 4);
}
void MEMFeatures()
{
	DWORD отдача = 0xE38810;
	DWORD точность = 0xC6406C;
	DWORD точность2 = 0xC62D14;
	DWORD np = 0x4839D4;
	DWORD подкат = 0xE6EC56;
	DWORD слепа = 0x9F2A8E;
	DWORD темь = 0x83EF9B;
	DWORD бег = 0xFC1247;
	DWORD темп = 0x1502B0C;
	DWORD зам = 0xE38818;
	DWORD глуш = 0xE387AD;
	DWORD nojl = 0xE36E56;
	DWORD nojk = 0xE36E64;
	DWORD vi3 = 0x1042390;
	DWORD prob = 0x58A5EC;

	if (Varm.Точность)
	{
		MEMwrite((void *)(точность), (int*)(PBYTE)"\x90\x90", 2);
	}
	else
	{
		MEMwrite((void *)(точность), (int*)(PBYTE)"\x33\xFF", 2);
	}
	if (Varm.Точностьь)
	{
		MEMwrite((void *)(точность2), (int*)(PBYTE)"\x00\x85\xC0\xEB", 4);
	}
	else
	{
		MEMwrite((void *)(точность2), (int*)(PBYTE)"\x00\x85\xC0\x76", 4);
	}
	if (Varm.бег)
	{
		MEMwrite((void *)(бег), (int*)(PBYTE)"\x90\x90", 2);
	}
	else
	{
		MEMwrite((void *)(бег), (int*)(PBYTE)"\x75\x06", 2);
	}
	if (Varm.подкат)
	{
		MEMwrite((void *)(подкат), (int*)(PBYTE)"\x90\x90\x90", 3);
	}
	else
	{
		MEMwrite((void *)(подкат), (int*)(PBYTE)"\xD8\x3c\x24", 3);
	}

	if (Varm.Ckoroctrel2 == 0)
	{
		MEMwrite((void *)(темп), (void *)"\x00\x00\x4E", 3);
	}
	if (Varm.Ckoroctrel2 == 1)
	{
		MEMwrite((void *)(темп), (void *)"\x00\x00\x44", 3);
	}
	if (Varm.Ckoroctrel2 == 2)
	{
		MEMwrite((void *)(темп), (void *)"\x00\x00\x3F", 3);
	}
	if (Varm.Ckoroctrel2 == 3)
	{
		MEMwrite((void *)(темп), (void *)"\x00\x00\x3A", 3);
	}
	if (Varm.Ckoroctrel2 == 4)
	{
		MEMwrite((void *)(темп), (void *)"\x00\x00\x1C", 3);
	}
	if (Varm.flash)
	{
		MEMwrite((void *)(слепа), (void *)(PBYTE)"\xEB\x74", 2);
	}
	else
	{
		MEMwrite((void *)(слепа), (void *)(PBYTE)"\xC0\x74\x33\x8B\x74", 5);
	}
	if (Varm.np)
	{
		MEMwrite((void *)(np), (void *)(PBYTE)"\x90\xF3", 2);
	}
	else
	{
		MEMwrite((void *)(np), (void *)(PBYTE)"\x40\xF3", 2);
	}
	if (Varm.зам)
	{
		MEMwrite((void *)(зам), (void *)(PBYTE)"\x90\x90\x90\x90\x90", 5);
	}
	else
	{
		MEMwrite((void *)(зам), (void *)(PBYTE)"\xE8\x73\xA2\xE2\xFF", 5);
	}
	if (Varm.глуш)
	{
		MEMwrite((void *)(глуш), (void *)(PBYTE)"\x0C\xEB", 2);
	}
	else
	{
		MEMwrite((void *)(глуш), (void *)(PBYTE)"\x0C\x74", 2);
	}
	if (Varm.отдача)
	{
		MEMwrite((void *)(отдача), (void *)(PBYTE)"\x90\x90\x90\x90\x90", 5);
	}
	else
	{
		MEMwrite((void *)(отдача), (void *)(PBYTE)"\xE8\xCB\xAB\xE2\xFF", 5);
	}
	if (Varm.темь)
	{
		MEMwrite((void *)(темь), (void *)(PBYTE)"\x90\x90\x90\x90", 4);
	}
	else
	{
		MEMwrite((void *)(темь), (void *)(PBYTE)"\x8B\x54\xAE\x60", 4);
	}
	if (Varm.bnojl)
	{
		MEMwrite((void *)(nojl), (void *)(PBYTE)"\x90\x90", 2);
	}
	else
	{
		MEMwrite((void *)(nojl), (void *)(PBYTE)"\x74\x05", 2);
	}
	if (Varm.bnojk)
	{
		MEMwrite((void *)(nojk), (void *)(PBYTE)"\x90\x90\x90\x90\x90", 5);
	}
	else
	{
		MEMwrite((void *)(nojk), (void *)(PBYTE)"\xBE\x4F\x00\x00\x00", 5);
	}
	if (Varm.vid3)
	if (GetKeyState(VK_F1) & 1)
	{
		MEMwrite((void *)(vi3), (void *)(PBYTE)"\xC0\xB0\x01\xEB", 4);
	}
	else
	{
		MEMwrite((void *)(vi3), (void *)(PBYTE)"\xC0\xB0\x01\x74", 4);
	}
	if (Varm.probiv)
	{
		MEMwrite((void *)(prob), (void *)(PBYTE)"\xC4\x08\x90\x90", 4);
	}
	else
	{
		MEMwrite((void *)(prob), (void *)(PBYTE)"\xC4\x08\x85\xC0", 4);
	}
	if (Varm.jump)
	{
		MEMwrite((void *)(0x112017B), (void *)(PBYTE)"\x77\x8B", 2);
	}
	else
	{
		MEMwrite((void *)(0x112017B), (void *)(PBYTE)"\x74\x8B\x4E", 3);
	}
}

HRESULT WINAPI myReset (LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters)
{
	BYTE* CDR = (BYTE*)pReset;
	CDR[0] = CodeFragmentR[0];
	*((DWORD*)(CDR + 1)) = *((DWORD*)(CodeFragmentR + 1));

	if(Draw.pFont)Draw.pFont->OnLostDevice();
	if(Draw.pLine)Draw.pLine->OnLostDevice();
	HRESULT hRet = pReset( pDevice, pPresentationParameters );
	if(SUCCEEDED(hRet))
	{
		if(Draw.pFont)Draw.pFont->OnResetDevice();
		if(Draw.pLine)Draw.pLine->OnResetDevice();
	}
	CDR[0] = jmpbR[0];
	*((DWORD*)(CDR + 1)) = *((DWORD*)(jmpbR + 1));
	return hRet;
}

void FontReset()
{
Draw.pFont->OnLostDevice();
Draw.pFont->OnResetDevice();
}

bool Create;
HRESULT APIENTRY myEndScene(LPDIRECT3DDEVICE9 pDevice)
{
BYTE* CDES = (BYTE*)pEndScene;
CDES[0] = CodeFragmentES[0];
*((DWORD*)(CDES + 1)) = *((DWORD*)(CodeFragmentES + 1));
	if( !Create )
	{
		D3DXCreateLine(pDevice, &Draw.pLine);
		Draw.InitFont("Tahoma", 13, FW_BOLD, pDevice);
		Draw.InitFontA("Tahoma", 13, FW_BOLD, pDevice);
		Create = true;
	}
	if (!Draw.pFont || !Draw.pFonts)
	cInstall->OnLostFont();
	Draw.KeyMenu(VK_HOME,pDevice);
	FontReset();
	MEMFeatures();
	NoBan();
	Protect();
    HackTools();
	Min();
	Protect();
	DWORD res = pEndScene(pDevice);
 CDES[0] = jmpbES[0];
  *((DWORD*)(CDES + 1)) = *((DWORD*)(jmpbES + 1));
 return res;
}

DWORD endscene;
DWORD reset;
void GetDevice9Methods()
{
	HWND hWnd = CreateWindowA("STATIC", "dummy", 0, 0, 0, 0, 0, 0, 0, 0, 0);
	HMODULE hD3D9 = LoadLibrary("d3d9");
	DIRECT3DCREATE9 Direct3DCreate9 = (DIRECT3DCREATE9)GetProcAddress(hD3D9, "Direct3DCreate9");
	IDirect3D9* d3d = Direct3DCreate9(D3D_SDK_VERSION);
	D3DDISPLAYMODE d3ddm;
	d3d->GetAdapterDisplayMode(0, &d3ddm);
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = d3ddm.Format;
	IDirect3DDevice9* d3dDevice = 0;
	d3d->CreateDevice(0, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &d3dDevice);
	DWORD* vtablePtr = (DWORD*)(*((DWORD*)d3dDevice));
	endscene = vtablePtr[42] - (DWORD)hD3D9;
	reset = vtablePtr[16] - (DWORD)hD3D9;
	d3dDevice->Release();
	d3d->Release();
	FreeLibrary(hD3D9);
	CloseHandle(hWnd);
}

void HookDevice9Methods()
{
	HMODULE hD3D9 = GetModuleHandle("d3d9.dll");
	///////////////////////////////////////////////////////////
	pEndScene = (oEndScene)((DWORD)hD3D9 + endscene);
	jmpbES[0] = 0xE9;
	DWORD addr = (DWORD)myEndScene - (DWORD)pEndScene - 5;
	memcpy(jmpbES + 1, &addr, sizeof(DWORD));
	memcpy(CodeFragmentES, pEndScene, 5);
	VirtualProtect(pEndScene, 8, PAGE_EXECUTE_READWRITE, &oldprotectES);
	memcpy(pEndScene, jmpbES, 5);
	////////////////////////////////////////////////////////////
	pReset = (oReset)((DWORD)hD3D9 + reset);
	jmpbR[0] = 0xE9;
	DWORD addr2 = (DWORD)myReset - (DWORD)pReset - 5;
	memcpy(jmpbR + 1, &addr2, sizeof(DWORD));
	memcpy(CodeFragmentR, pReset, 5);
	VirtualProtect(pReset, 8, PAGE_EXECUTE_READWRITE, &oldprotectR);
	memcpy(pReset, jmpbR, 5);
}
HRESULT APIENTRY Hook()
{
	GetDevice9Methods();
	HookDevice9Methods();
	return 0;
}

BOOL WINAPI DllMain(HMODULE hDll, DWORD dwReason, LPVOID lpReserved)
{     
DisableThreadLibraryCalls(hDll);
AntiHeaders(hDll);
AntiRevers(hDll);
HideModule(hDll);
if (dwReason == DLL_PROCESS_ATTACH)
{
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)Hook, NULL, NULL, NULL);
}
return TRUE;
}