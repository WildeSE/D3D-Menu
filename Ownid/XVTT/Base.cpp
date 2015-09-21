#pragma once
#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN
#include <windows.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <d3dx9core.h>
#include <math.h>
#include <DbgHelp.h>
#include <Mmsystem.h>
#include <ShellAPI.h>
#include <fstream>
#include <iostream>
#include <iosfwd>
#include "detours.h"
#include <vector>
#include <algorithm>
#include <process.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "WinMM.Lib")
#pragma comment(lib, "detours.Lib")

using namespace std;


#include "Sprite.h"
#include "D3DColor.h"
#include "Tools.h"
#include "Variables.h"
#include "DrawPrimitives.h"
#include "OtherDraw.h"
#include "Menu.h"
#include "GameClass.h"
#include "Func.h"


cFun Fun;

#pragma region D3D9_Interface_Hook

bool hooked = false;
#define HOOK(func,addy) p##func = (o##func)DetourFunction((PBYTE)addy,(PBYTE)my##func) 
#define UNHOOK(func,addy) p##func = (o##func)DetourFunction((PBYTE)addy,(PBYTE)p##func) 

typedef HRESULT(WINAPI* oEndScene)(LPDIRECT3DDEVICE9 pDevice);
oEndScene pEndScene = NULL;





void MemoryWrite(void *adr, void *ptr, int size)
{
	DWORD OldProtection;
	VirtualProtect(adr, size, PAGE_EXECUTE_READWRITE, &OldProtection);
	memcpy(adr, ptr, size);
	VirtualProtect(adr, size, OldProtection, &OldProtection);
}






HRESULT APIENTRY myEndScene(LPDIRECT3DDEVICE9 pDevice)
{
	while (!pDevice) { pDevice = pDevice; }

	if (!Create)
	{
	//	D3DXCreateFont(pDevice, 13, 0, FW_BOLD, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, (LPCSTR)"Fixed Sys", &rFont);
		D3DXCreateLine(pDevice, &pLine);
		Font("System", 15, FW_MEDIUM, pDevice);
		D3DXCreateSprite(pDevice, &pSprite);
		Create = true;
	}
	if (!pFont || !pLine)
	{
		pFont->OnLostDevice();
		pLine->OnLostDevice();
	}
	else
	{
		if (GetAsyncKeyState(VK_HOME) & 1) Show = (!Show);
		if (Show) WF_XVTT(pDevice);
		pFont->OnLostDevice();
		pFont->OnResetDevice();
		pLine->OnLostDevice();
		pLine->OnResetDevice();
	}
	return pEndScene(pDevice);
}


LPDIRECT3DDEVICE9 nm_pD3Ddev;
PBYTE HookVTable(PDWORD* dwVTable, PBYTE dwHook, INT Index)
{
	DWORD dwOld = 0;
	VirtualProtect((void*)((*dwVTable) + (Index * 4)), 4, PAGE_EXECUTE_READWRITE, &dwOld);
	PBYTE pOrig = ((PBYTE)(*dwVTable)[Index]);
	(*dwVTable)[Index] = (DWORD)dwHook;
	VirtualProtect((void*)((*dwVTable) + (Index * 4)), 4, dwOld, &dwOld);

	return pOrig;
}
LRESULT CALLBACK MsgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam){ return DefWindowProc(hwnd, uMsg, wParam, lParam); }
void DX_Init(DWORD* table)
{
	WNDCLASSEXA wc = { sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L, GetModuleHandleA(NULL), NULL, NULL, NULL, NULL, "DX", NULL };
	RegisterClassExA(&wc);
	HWND hWnd = CreateWindowA("DX", NULL, WS_OVERLAPPEDWINDOW, 100, 100, 300, 300, GetDesktopWindow(), NULL, wc.hInstance, NULL);
	LPDIRECT3D9 pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	LPDIRECT3DDEVICE9 pd3dDevice;
	pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &pd3dDevice);

	DWORD* pVTable = (DWORD*)pd3dDevice;
	pVTable = (DWORD*)pVTable[0];

	table[0] = pVTable[42];

	DestroyWindow(hWnd);
}

unsigned __stdcall VMT_Patching(LPVOID  Param)
{
	while (1)
	{
		Sleep(100);
		HookVTable((PDWORD*)nm_pD3Ddev, (PBYTE)myEndScene, 42);
	}
	return 1;
}
unsigned __stdcall LoopFunction(LPVOID  Param)
{
	if (hooked == false)
	{
		DWORD VTable[3] = { 0 };
		while (GetModuleHandleA("d3d9.dll") == NULL)
		{
			Sleep(250);
		}
		DX_Init(VTable);
		HOOK(EndScene, VTable[0]);
		while (!nm_pD3Ddev)
		{
			Sleep(50);
		}
		UNHOOK(EndScene, VTable[0]);
		*(PDWORD)&pEndScene = VTable[0];
		_beginthreadex(NULL, 0, VMT_Patching, NULL, 0, 0);
		hooked = true;
	}
	return TRUE;
}

bool bExitThread;
unsigned __stdcall HookRender(LPVOID  Param)
{
	while (1)
	{
		//if(*(DWORD*)0x00B61F88 == 1)
		//{
		_beginthreadex(NULL, NULL, LoopFunction, NULL, NULL, NULL);
		return FALSE;
		//	}
		//Sleep(400);
	}
}
#pragma endregion

void _HideModule(HINSTANCE hModule)
{
	DWORD dwPEB_LDR_DATA = 0;
	_asm
	{
		pushad;
		pushfd;
		mov eax, fs:[30h]
			mov eax, [eax + 0Ch]
			mov dwPEB_LDR_DATA, eax
		InLoadOrderModuleList :
		mov esi, [eax + 0Ch]
			mov edx, [eax + 10h]
		LoopInLoadOrderModuleList :
								  lodsd
								  mov esi, eax
								  mov ecx, [eax + 18h]
								  cmp ecx, hModule
								  jne SkipA
								  mov ebx, [eax]
								  mov ecx, [eax + 4]
								  mov[ecx], ebx
								  mov[ebx + 4], ecx
								  jmp InMemoryOrderModuleList
							  SkipA :
		cmp edx, esi
			jne LoopInLoadOrderModuleList
		InMemoryOrderModuleList :
		mov eax, dwPEB_LDR_DATA
			mov esi, [eax + 14h]
			mov edx, [eax + 18h]
		LoopInMemoryOrderModuleList :
									lodsd
									mov esi, eax
									mov ecx, [eax + 10h]
									cmp ecx, hModule
									jne SkipB
									mov ebx, [eax]
									mov ecx, [eax + 4]
									mov[ecx], ebx
									mov[ebx + 4], ecx
									jmp InInitializationOrderModuleList
								SkipB :
		cmp edx, esi
			jne LoopInMemoryOrderModuleList
		InInitializationOrderModuleList :
		mov eax, dwPEB_LDR_DATA
			mov esi, [eax + 1Ch]
			mov edx, [eax + 20h]
		LoopInInitializationOrderModuleList :
											lodsd
											mov esi, eax
											mov ecx, [eax + 08h]
											cmp ecx, hModule
											jne SkipC
											mov ebx, [eax]
											mov ecx, [eax + 4]
											mov[ecx], ebx
											mov[ebx + 4], ecx
											jmp Finished
										SkipC :
		cmp edx, esi
			jne LoopInInitializationOrderModuleList
		Finished :
		popfd;
		popad;
	}
}

void DisableLibraryView(HMODULE hModule)
{
	_HideModule(hModule);
}

void DeleteHeaders(HINSTANCE hModule)
{
	PIMAGE_DOS_HEADER pDoH;
	PIMAGE_NT_HEADERS pNtH;
	DWORD i, ersize, protect;

	if (!hModule) return;
	pDoH = (PIMAGE_DOS_HEADER)(hModule);
	pNtH = (PIMAGE_NT_HEADERS)((LONG)hModule + ((PIMAGE_DOS_HEADER)hModule)->e_lfanew);
	ersize = sizeof(IMAGE_DOS_HEADER);
	if (VirtualProtect(pDoH, ersize, PAGE_READWRITE, &protect))
		for (i = 0; i < ersize; i++)
			*(BYTE*)((BYTE*)pDoH + i) = 0;

	ersize = sizeof(IMAGE_NT_HEADERS);
	if (pNtH && VirtualProtect(pNtH, ersize, PAGE_READWRITE, &protect))
		for (i = 0; i < ersize; i++)
			*(BYTE*)((BYTE*)pNtH + i) = 0;
}
bool HideThread(HANDLE hThread)
{
	typedef unsigned long (NTAPI *pNtSetInformationThread)
		(HANDLE, UINT, PVOID, ULONG);
	unsigned long Status;

	pNtSetInformationThread NtSIT = (pNtSetInformationThread)GetProcAddress(GetModuleHandle(TEXT("ntdll.dll")), "NtSetInformationThread");

	if (NtSIT == NULL)
		return false;

	if (hThread == NULL)
		Status = NtSIT(GetCurrentThread(), 0x11, 0, 0);
	else
		Status = NtSIT(hThread, 0x11, 0, 0);

	if (Status != 0x00000000)
		return false;
	else
		return true;
}

BOOL WINAPI DllMain(HMODULE hDll, DWORD dwReason, LPVOID)
{

	HANDLE hThread = NULL, h_Thread = OpenThread(THREAD_ALL_ACCESS, NULL, GetCurrentThreadId());
	DisableThreadLibraryCalls(hDll);
	DeleteHeaders(hDll);
	DisableLibraryView(hDll);
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		HANDLE iModuleThread = (HANDLE)_beginthreadex(0, 0, HookRender, 0, 0, 0);
		HideThread(iModuleThread);
		_HideModule(hDll);
		CloseHandle(hThread);
		return TRUE;
	}
	return TRUE;
}
