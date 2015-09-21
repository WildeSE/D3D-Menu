#include <Windows.h>
#pragma comment(lib, "detours.lib")
#include "detours.h"
#include <d3d9.h>
#include <d3dx9.h>
#include <stdio.h>
#define D3DparamX		, UINT paramx
#define D3DparamvalX	, paramx
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#include "STherad.h"
SThread* pSmartThread = new SThread;
typedef HRESULT	(WINAPI* oEndScene)(LPDIRECT3DDEVICE9 pDevice);
oEndScene pEndScene = NULL;
bool Create;
#include "cDraw.h";
cDraw Draw;
#include "MyMenu.h"
#include "Memory.h"
cMemory *cMem;
#include "cProtect.h"
cProtect *Protect;