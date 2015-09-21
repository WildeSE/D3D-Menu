#include "Includes.h"
#include "Color.h"
#include "Tools.h"
#include "Asma.h"
#include "Functions.h"




#include "Variables.h"
#include "Draw.h"
#include "Sound.h"
#include "Components.h"
#include "Menu.h"
#include "save_load.h"

#define VK_E 0x45

int boxi;// функция с меню
int WallShoot;
int tochnost;


cFun Fun;
class CDeathPlayer;
class CLocalPlayerID;
class CRenderData;
class CRenderContext;
class CGameBase;
class CBonesContext;
class CBone;
class CPlayer;
class CPlayer2;
class GetCurrentHP;
class sESPTools;



class GetCurrentHP
{
public:
float GetCurHP;
};

class CPlayer2
{
public:
BYTE Dead_player;
char _0x0000[99];
float CrosshairX;
float CrosshairY;
D3DXVECTOR3 position;
};
class CDeathPlayer
{
public:
	BYTE Death[16];
};

class CLocalPlayerID
{
public:
	BYTE ID;
};

class CRenderData
{
public:
	CRenderContext* RenderData;
};

class CRenderContext
{
public:
	
	char unknown[2272];
	D3DXMATRIX ViewMatrix;
	D3DXMATRIX ProjectMatrix;
	D3DXMATRIX WorldMatrix;
};

class CGameBase
{
public:
	char pad[1372];
	CBonesContext* Bones;
};

class CBonesContext
{
public:
	char pad[0x0C4];
	CBone* BoneData;
};

class CBone
{
public:
	D3DXMATRIX BoneMatrix;
};

class CGame
{
public:
	BYTE unknown1[0x14];
	CGameBase *GameBase[16];
};
class CPlayer
{
public:
	BYTE        IsLife;
	char        Unk[99];
	D3DXVECTOR2 Cross;
	D3DXVECTOR3 Pos;
};
DWORD GameBase = *(DWORD *)0xAFF0C4;
CGame *Game = (CGame *)(GameBase);
bool WorldToScreen(D3DXVECTOR3 inpos, D3DXVECTOR3 &outpos, LPDIRECT3DDEVICE9 pDevice)
{       
	DWORD dwRenderData = (DWORD)GetModuleHandleA("i3GfxDx.dll") + 0x1AD2F0;
	CRenderData* RenderData = (CRenderData*)(dwRenderData);

	D3DXVECTOR3 vScreen;
	D3DVIEWPORT9 g_ViewPort;

	pDevice->GetViewport(&g_ViewPort);
	g_ViewPort.X = g_ViewPort.Y = 0;
	g_ViewPort.MinZ = 0;
	g_ViewPort.MaxZ = 1;
	D3DXVec3Project(&vScreen, &inpos, &g_ViewPort,
		&RenderData->RenderData->ProjectMatrix,
		&RenderData->RenderData->ViewMatrix,
		&RenderData->RenderData->WorldMatrix);

	if (vScreen.z < 1.0f && vScreen.x > 0.0f && vScreen.y > 0.0f && vScreen.x < g_ViewPort.Width && vScreen.y < g_ViewPort.Height)
	{
		outpos.x = vScreen.x;
		outpos.y = vScreen.y;
		outpos.z = vScreen.z;

		return true;
	}

	return false;
}

int GetCharaIndex()
{
	DWORD InfBase = *(DWORD *)0xAFF0FC;
	CLocalPlayerID *LocID = (CLocalPlayerID *) (InfBase + 0x48744);
	return LocID->ID;
}

BYTE GetUserLife(int index)
{
	DWORD InfBase = *(DWORD *)0xAFF0FC;
	CDeathPlayer *Life = (CDeathPlayer *) (InfBase + 0x48794);
	
	return Life->Death[index];
	
}

bool GetUserBone(D3DXVECTOR3 &Out, int index, int BoneIndex)
{
	 DWORD dwGameBase = *(DWORD*)0xAFF0C4;	
	 if(dwGameBase)
	 {
		CGameBase* GameBase = (CGameBase*) (*(DWORD*)(dwGameBase + 0x14 + (0x4 * index) ));
		if (GameBase && GameBase->Bones)
		{
			Out.x = GameBase->Bones->BoneData[BoneIndex].BoneMatrix._41;
			Out.y = GameBase->Bones->BoneData[BoneIndex].BoneMatrix._42;
			Out.z = GameBase->Bones->BoneData[BoneIndex].BoneMatrix._43;
			return true;
		}
	 }
	return false;
}

float CalcDistance(D3DXVECTOR3 VecA, D3DXVECTOR3 VecB)
{
	return sqrt( (( VecA.x - VecB.x) * ( VecA.x - VecB.x)) +
		         (( VecA.y - VecB.y) * ( VecA.y - VecB.y)) +
		         (( VecA.z - VecB.z) * ( VecA.z - VecB.z)));
}

int GetPriorityTarget()
{
	int Result = -1;
	float fMaxDistance = 100.0f;
	D3DXVECTOR3 PlayerEnd, LocPlayer;
	for (int index = 0; index < 16; index++)
	{
		if (!GetUserLife(index) && GetCharaIndex() != index)
		{
			if (GetCharaIndex() %2 != index % 2)
			{
				GetUserBone(LocPlayer, GetCharaIndex(), 7);
				GetUserBone(PlayerEnd, index, 7);
				if (CalcDistance(LocPlayer, PlayerEnd) < fMaxDistance)
				{
					fMaxDistance = CalcDistance(PlayerEnd, LocPlayer);
					Result = index;
				}
			}
		}
	}
	return Result;
}

DWORD dwEnd = 0x4E967D;
DWORD dwReturnEnd = 0x4E9684;
float fX = 10.0f, fY = 10.0f, fZ = 10.0f;
bool EndEnable;
DWORD dwTempEcx, dwTempEbx;
_declspec( naked ) void End( )
{
	if ( EndEnable )
	{
		_asm
		{
			mov     [dwTempEcx], ecx;
			mov     [dwTempEbx], ebx;

			mov     ecx, [ebp+0x0C];

			mov     ebx, [fX];
			mov     [ecx], ebx;

			mov     ebx, [fY];
			mov     [ecx+0x04], ebx;

			mov     ebx, [fZ];
			mov     [ecx+0x08], ebx;

			mov     ecx, [dwTempEcx];
			mov     ebx, [dwTempEbx];
		}
	}

	_asm
	{
		mov     eax, [ebp+0x08];
		push    eax;
		mov     ecx, [ebp-0x38];

		jmp     dwReturnEnd;
	}
}

void AimBot()
{
	if(Fun.Aim)
	{
		DWORD Base = *(DWORD *)0xAFF0C0;
		if(Base != 0x000000)
		{
			int Priority = GetPriorityTarget();
			if(Priority != -1)
			{
				EndEnable = true;
				D3DXVECTOR3 Out, Screen;
				GetUserBone(Out, Priority, 7);

				 fX = Out.x;
				 fY = Out.y;
				 fZ = Out.z;
				
				DetourCreate((PBYTE)dwEnd, (PBYTE)End, 7);
			}
		}
	}
	else
	{
		EndEnable = false;
		DetourCreate((PBYTE)dwEnd, (PBYTE)End, 7);
	}
}

HRESULT WINAPI myReset (LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters)
{
	if(pFont)pFont->OnLostDevice();
	if(pLine)pLine->OnLostDevice();
	HRESULT hRet = pReset( pDevice, pPresentationParameters );
	if(SUCCEEDED(hRet))
	{
		if(pFont)pFont->OnResetDevice();
		if(pLine)pLine->OnResetDevice();
	}
	return hRet;
}

HRESULT APIENTRY myEndScene(LPDIRECT3DDEVICE9 pDevice)
{
	if (!Create)
	{
		D3DXCreateLine(pDevice, &pLine);
		Font("Georgia", 14, FW_NORMAL, pDevice);
		Create = true;
	}
	if (pFont == NULL)pFont->OnLostDevice();
	else
	{
	   if (GetAsyncKeyState(VK_HOME) & 1)Show = (!Show);
	   if (Show){ GoldBase(pDevice); }
	}
	if (GetAsyncKeyState(VK_F3) & 1)D3D9ScreenShot(pDevice);
	AimBot();

	return pEndScene(pDevice);   
}

HRESULT WINAPI myDrawIndexedPrimitive(LPDIRECT3DDEVICE9 pDevice, D3DPRIMITIVETYPE Type, INT BaseVertexIndex, UINT MinVertexIndex, UINT NumVertices, UINT startIndex, UINT primCount)
{
	if (Color)
	{
		GenerateTexture(pDevice, &White, WHITE);
		GenerateTexture(pDevice, &Red, RED);
		GenerateTexture(pDevice, &Green, GREEN);
		GenerateTexture(pDevice, &Blue, BLUE);
		Color = false;
	}
	return pDrawIndexedPrimitive(pDevice, Type, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
}





int HookpDevice(void)
{
	DWORD*vtbl=0;
	DWORD hD3D9=(DWORD)LoadLibraryA("d3d9.dll");
	DWORD table=FindPattern(hD3D9,0x128000,(PBYTE)"\xC7\x06\x00\x00\x00\x00\x89\x86\x00\x00\x00\x00\x89\x86","xx????xx????xx");
	memcpy(&vtbl,(void*)(table+2),4);
	pEndScene = (oEndScene)DetourCreate((PBYTE)vtbl[42],(PBYTE)myEndScene,5);\
	pDrawIndexedPrimitive=(oDrawIndexedPrimitive)DetourCreate((PBYTE)vtbl[82],(PBYTE)myDrawIndexedPrimitive,5);
	//pReset					=   (oReset)				DetourCreate((PBYTE)vtbl[16],	(PBYTE)myReset,     12);
	return 0;
}



BOOL WINAPI DllMain(HMODULE hDll, DWORD dwReason, LPVOID lpReserved)
{
	DisableThreadLibraryCalls(hDll);
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		if(GetModuleHandleA("PBlackout.exe")|| GetModuleHandleA("PBlackout.exe")|| GetModuleHandleA("D3D Test.exe")||  GetModuleHandleA("D3DTES~1.EXE"))  

		StartLogModule(hDll);
		
		StartRoutine(HookpDevice);
		Fun.Color1 = 1;
	}
	return TRUE;
}
   