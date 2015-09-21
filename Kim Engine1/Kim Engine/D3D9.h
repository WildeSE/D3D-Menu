#pragma region D3D9_Interface_Hook
#include <process.h>
bool hooked = false;
#define HOOK(func,addy) p##func = (o##func)DetourFunction((PBYTE)addy,(PBYTE)my##func) 
#define UNHOOK(func,addy) p##func = (o##func)DetourFunction((PBYTE)addy,(PBYTE)p##func) 
LPDIRECT3DDEVICE9 nm_pD3Ddev;
PBYTE HookVTable( PDWORD* dwVTable, PBYTE dwHook, INT Index )
{
	DWORD dwOld = 0;
	VirtualProtect((void*)((*dwVTable) + (Index*4) ), 4, PAGE_EXECUTE_READWRITE, &dwOld);
	PBYTE pOrig = ((PBYTE)(*dwVTable)[Index]);
	(*dwVTable)[Index] = (DWORD)dwHook;
	VirtualProtect((void*)((*dwVTable) + (Index*4)), 4, dwOld, &dwOld);
	return pOrig;
}
LRESULT CALLBACK MsgProc(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam){return DefWindowProc(hwnd, uMsg, wParam, lParam);}
void DX_Init(DWORD* table)
{
	WNDCLASSEXA wc = {sizeof(WNDCLASSEX),CS_CLASSDC,MsgProc,0L,0L,GetModuleHandleA(NULL),NULL,NULL,NULL,NULL,"DX",NULL};
	RegisterClassExA(&wc);
	HWND hWnd = CreateWindowA("DX",NULL,WS_OVERLAPPEDWINDOW,100,100,300,300,GetDesktopWindow(),NULL,wc.hInstance,NULL);
	LPDIRECT3D9 pD3D = Direct3DCreate9( D3D_SDK_VERSION );
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory( &d3dpp, sizeof(d3dpp) );
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	LPDIRECT3DDEVICE9 pd3dDevice;
	pD3D->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,hWnd,D3DCREATE_SOFTWARE_VERTEXPROCESSING,&d3dpp,&pd3dDevice);
	DWORD* pVTable = (DWORD*)pd3dDevice;
	pVTable = (DWORD*)pVTable[0];
	table[0]   = pVTable[42]; 
	DestroyWindow(hWnd);
}

unsigned _stdcall VMT_Patching( LPVOID  Param )
{
	while(1)
	{
		Sleep(100);
		HookVTable((PDWORD*)nm_pD3Ddev, (PBYTE)myEndScene, 42); 
	}
	return 1;
}

unsigned _stdcall LoopFunction(LPVOID)
{
	if(hooked==false) 
	{
		DWORD VTable[3] = {0};
		while(GetModuleHandleA("d3d9.dll")==NULL) 
		{
			Sleep(250);
		}
		DX_Init(VTable);
         HOOK(EndScene,VTable[0]); 
		while(!nm_pD3Ddev) 
		{
			Sleep(50); 
		}
		UNHOOK(EndScene, VTable[0]); 
		*(PDWORD)&pEndScene				= VTable[0];
		_beginthreadex(0,0,VMT_Patching,0,0,0); //Create hooking thread
		hooked = true;
	}
	return hooked;
}
#pragma endregion D3D9_Interface_Hook