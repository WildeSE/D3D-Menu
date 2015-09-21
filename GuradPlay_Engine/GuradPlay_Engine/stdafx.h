#ifndef  _STDAFX_H_
#define _STDAFX_H_

#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN
#define D3DparamX		, UINT paramx
#define D3DparamvalX	, paramx
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#include <windows.h>
#include <time.h>
#include <stdio.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <d3dx9core.h>
#include "d3dx9math.inl"
#include <math.h>
#include <DbgHelp.h>
#include <Mmsystem.h>
#include <ShellAPI.h>
#include <fstream>
#include <iostream>
#include <iosfwd>
#include <TlHelp32.h>
#include <fcntl.h>
#include <Io.h>
#include <locale.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <type_traits>
#include <urlmon.h>
#include <process.h>

#define VK_0				0x30
#define VK_1				0x31
#define VK_2				0x32
#define VK_3				0x33
#define VK_4				0x34
#define VK_5				0x35
#define VK_6				0x36
#define VK_7				0x37
#define VK_8				0x38
#define VK_9				0x39
#define VK_A				0x41
#define VK_B				0x42
#define VK_C				0x43
#define VK_D				0x44
#define VK_E				0x45
#define VK_F				0x46
#define VK_G				0x47
#define VK_H				0x48
#define VK_I				0x49
#define VK_J				0x4A
#define VK_K				0x4B
#define VK_L				0x4C
#define VK_M				0x4D
#define VK_N				0x4E
#define VK_O				0x4F
#define VK_P				0x50
#define VK_Q				0x51
#define VK_R				0x52
#define VK_S				0x53
#define VK_T				0x54
#define VK_U				0x55
#define VK_V				0x56
#define VK_W				0x57
#define VK_X				0x58
#define VK_Y				0x59
#define VK_Z				0x5A
#define VK_LSHIFT			0xA0
#define VK_RSHIFT			0xA1
#define VK_LCONTROL			0xA2
#define VK_RCONTROL			0xA3
#define VK_LMENU			0xA4
#define VK_RMENU			0xA5

#define PI					3.14159265

HMODULE hInputDx		= GetModuleHandle( "i3inputdx.dll" ),
	hPointBlank			= GetModuleHandle( "PointBlank.exe" ),
	hSceneDx			= GetModuleHandle( "i3SceneDx.dll" );


DWORD g_pGameFramework		=		0x00C458C4;//0x00B3149C
DWORD g_pViewer				=		g_pGameFramework + 0x4;
DWORD g_pCameraManager		=		g_pGameFramework + 0x8;
DWORD g_pPlayer				=		g_pGameFramework + 0xC;
DWORD g_pCharaManager		=		g_pGameFramework + 0x10;
DWORD g_pWeaponManager		=		g_pGameFramework + 0x14;
DWORD g_pGameContext		=		g_pGameFramework + 0x44;
DWORD g_pStageBattle		=		g_pGameFramework + 0x98;



DWORD dword_Framework		=		*(DWORD*)g_pGameFramework;
DWORD dword_Viewer			=		*(DWORD*)g_pViewer;
DWORD dword_CameraManager	=		*(DWORD*)g_pCameraManager;
DWORD dword_Player			=		*(DWORD*)g_pPlayer;
DWORD dword_CharaManager	=		*(DWORD*)g_pCharaManager;
DWORD dword_WeaponManager	=		*(DWORD*)g_pWeaponManager;
DWORD dword_GameContext		=		*(DWORD*)g_pGameContext;
DWORD dword_StageBattle		=		*(DWORD*)g_pStageBattle;

#define MaxPlayer			16
#define T					0
#define CT					1
#define All					0
#define Enemies				1



bool bBone,bW2S,bDrawBone,bDrawSkeleton,bEsp;
#endif