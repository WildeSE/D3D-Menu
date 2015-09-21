#ifndef  _STDAFX_H_
#define _STDAFX_H_

#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN

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
#include <Winsock2.h>
#include <winioctl.h>
#include <type_traits>

#define D3DparamX		, UINT paramx
#define D3DparamvalX	, paramx

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "WinMM.Lib")

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
#define VK_CAPS             0x14

#define CText (DT_CENTER|DT_NOCLIP)
#define LText (DT_LEFT|DT_NOCLIP) 
#define RText (DT_RIGHT|DT_NOCLIP)
#endif