#include "MainClass.h"

DWORD dwEnd = 0x4E442D;
DWORD dwReturnEnd = dwEnd + 7;
DWORD dwTempEcx, dwTempEbx;
bool bEnd;
float fX = 10.0f, fY = 10.0f, fZ = 10.0f;

_declspec(naked)int cEnd(void) 
{ 
	if (bEnd) 
	{ 
		_asm mov	[dwTempEcx], ecx
		_asm mov	[dwTempEbx], ebx 
		_asm mov	ecx, [ebp+12]
		_asm mov	ebx, [fX] 
		_asm mov	[ecx], ebx
		_asm mov	ebx, [fY] 
		_asm mov	[ecx+4], ebx
		_asm mov	ebx, [fZ]
		_asm mov	[ecx+8], ebx; 
		_asm mov    ecx, [dwTempEcx]
		_asm mov    ebx, [dwTempEbx] 
	} 
	_asm mov     eax, [ebp+8]
	_asm push    eax 
	_asm mov     ecx, [ebp-56]
	_asm jmp     dwReturnEnd
} 

int getTarget(LPDIRECT3DDEVICE9 pDevice)
{
	int Result = -1;
	float Min = 1000.f; 	
	DWORD sCenterX = tools_ViewportInfo(2, pDevice)/2,
		sCenterY = tools_ViewportInfo(3, pDevice)/2;
	if((getInGame()==3) && (dword_GameContext != 0x00000000) && (dword_CharaManager != 0x00000000))
	{
		for ( int iSlot = 0; iSlot < MaxPlayer; iSlot++ )
		{	
			if ((CGameContext::Singleton()->MyId != iSlot))
			{
				if(IsAlive(iSlot))
				{
					D3DXVECTOR3 Head = getBonePosition(iSlot,head);
					if(Head)
					{
						D3DXVECTOR3 OnScreen;	
						if ( WorldToScreen(Head, OnScreen, pDevice))
						{
							if(OnScreen)
							{
								float X,Y;
								X = (float)sCenterX - OnScreen.x;
								Y = (float)sCenterY - OnScreen.y;
								if(X < 0) X *= -1;
								if(Y < 0) Y *= -1; 

								if(((X+Y)/2) < Min )
								{
									Min = ( X + Y ) / 2;
									Result = iSlot;    
								}
							}	
						}
					}	
				}
			}
		}
	}
	return Result;
}

void _stdcall fastAIM(LPDIRECT3DDEVICE9 pDevice)
{
	int Priority;
	if(( GPEngine.FastAim && getInGame()==3) && (dword_GameContext != 0x00000000) && 
		(dword_CharaManager != 0x00000000))
	{
		Priority = getTarget(pDevice);

		if(Priority != -1)
		{	
			D3DXVECTOR3 OnWorld = getBonePosition(Priority,head);
			if(OnWorld)
			{
				fX = OnWorld.x; 
				fY = OnWorld.y; 
				fZ = OnWorld.z;

				D3DXVECTOR3 OnScreen;
				if ( WorldToScreen(OnWorld, OnScreen, pDevice))
				{
					bEnd = true;	
				}	
			}
			else bEnd = false;			
		}
		else bEnd = false;
	}
	else bEnd = false;
	MemHack->Create_Hook((PBYTE)dwEnd, (PBYTE)cEnd, 7); 
}

HRESULT APIENTRY FastAim(LPDIRECT3DDEVICE9 pDevice)
{
	for (;;)
	{
		fastAIM(pDevice);
		Sleep(50);
	}
}
