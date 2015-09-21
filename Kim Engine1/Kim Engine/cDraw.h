#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "Colors.h"

#define C_Text (DT_CENTER|DT_NOCLIP)
#define L_Text (DT_LEFT|DT_NOCLIP)
#define R_Text (DT_RIGHT|DT_NOCLIP)
#define DT_SHADOW           0x0040
static struct _Keys 
{
	bool        bPressed;
	DWORD       dwStartTime;
}
kPressingKeys[256];

class cDraw
{
public:
	cDraw(void);
	bool Show;

	ID3DXFont* pFont;
	LPD3DXLINE pLine;
	BOOL  IsInBox(int x,int y,int w,int h);
	BOOL  State_Key(int Key,DWORD dwTimeOut);
	void _fastcall  InitFont(CHAR* szFontFamily ,int W ,DWORD Stile ,IDirect3DDevice9* mDevice);
	void _fastcall  Engine_Text(int x, int y, DWORD color, LPSTR text, DWORD ST);
	void _fastcall  Engine_Line(long Xa ,long Ya ,long Xb ,long Yb ,int Width ,D3DCOLOR Color);
	void _fastcall  Engine_Box( int x, int y, int w, int h,   D3DCOLOR Color, LPDIRECT3DDEVICE9 m_pD3Ddev);
	void _fastcall  Engine_Border(int x, int y, int w, int h,int s, D3DCOLOR Color, LPDIRECT3DDEVICE9 m_pD3Ddev);
	void _fastcall  SHOW_MENU(LPDIRECT3DDEVICE9  pDevice);
	void _fastcall  KeyMenu(DWORD KEY ,LPDIRECT3DDEVICE9  pDevice);
	void _fastcall  Engine_Menu(int x, int y, LPDIRECT3DDEVICE9  pDevice);
	void _fastcall  Engine_Button(int x, int y, bool &idreem, LPSTR text, IDirect3DDevice9* pDevice);
	void _fastcall  Engine_Check(int x, int y, bool &idreem, LPSTR text, IDirect3DDevice9* pDevice);
	void _fastcall  Engine_Scroll(int x, int y, int &idreem, char **typ, int max, LPSTR text, IDirect3DDevice9* pDevice);
	void _fastcall  Engine_ColorCheck(int x, int y, int &idreem, LPSTR text,DWORD *Sel_color,int SizeArr, IDirect3DDevice9 * pDevice);
	void _fastcall  Engine_TextSpace(int x, int y, LPSTR text,LPSTR butText, IDirect3DDevice9* pDevice);
	void _fastcall  String(int x, int y, DWORD Color, DWORD Style, const char *Format, ...);
	int ViewportInfo(int iCode, LPDIRECT3DDEVICE9 pDevice);
	VOID  Xhair(int Size,int Width,D3DCOLOR Color,IDirect3DDevice9* pDevice );
	void _fastcall Circle(int X, int Y, int radius, int numSides, DWORD Color);
	char* FPS(void);
};