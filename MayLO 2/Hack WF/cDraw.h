#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "cVar.h" 

#define C_Text (DT_CENTER|DT_NOCLIP)
#define L_Text (DT_LEFT|DT_NOCLIP)
#define R_Text (DT_RIGHT|DT_NOCLIP)

static struct _Keys
{
	bool        bPressed;
	DWORD       dwStartTime;
}
kPressingKey[256];

class cDraw
{
public:
	cDraw(void);
	bool Show;
	ID3DXFont* pFont;
	ID3DXFont* pFonts;
	LPD3DXLINE pLine;

	void Engine_Button(int x, int y, int &Var, LPSTR text, IDirect3DDevice9* pDevice);
	void Studio_Menu(int x, int y, LPSTR text, LPDIRECT3DDEVICE9  pDevice);
	void __fastcall String(int x, int y, DWORD Color, DWORD Style, const char *Format, ...);
	void __fastcall Line(float x, float y, float x2, float y2, float width, DWORD color);
	void Draw_Box(int x, int y, int w, int h, D3DCOLOR color, LPDIRECT3DDEVICE9 mDevice);
	void  Draw_Border(int x, int y, int w, int h, int s, D3DCOLOR Color, IDirect3DDevice9* mDevice);
	void __fastcall Box(int x, int y, int w, int h, D3DCOLOR Color, LPDIRECT3DDEVICE9 pDevice);
	void __fastcall Border(int x, int y, int w, int h, int s, DWORD color, LPDIRECT3DDEVICE9 pDevice);
	void  InitFontA(CHAR* szFontFamily, int W, DWORD Stile, IDirect3DDevice9* mDevice);
	void  InitFont(CHAR* szFontFamily, int W, DWORD Stile, IDirect3DDevice9* mDevice);
	void  DrawBox(int x, int y, int w, int h, D3DCOLOR Color, IDirect3DDevice9* mDevice);
	void  DrawBorder(int x, int y, int w, int h, D3DCOLOR Color, IDirect3DDevice9* mDevice);
	BOOL  IsInBox(int x, int y, int w, int h);
	void  Draw_Text(int x, int y, DWORD Color, const char *Format, DWORD Style);
	BOOL  State_Key(int Key, DWORD dwTimeOut);
	void _stdcall SHOW_MENU(LPDIRECT3DDEVICE9  pDevice);
	void  KeyMenu(DWORD KEY, LPDIRECT3DDEVICE9  pDevice);
	void Engine_CheckBox(int x, int y, int &Var, LPSTR text, IDirect3DDevice9* pDevice);
	void M1Chams(int x, int y, char *Text, int &Var, DWORD CoLoR1, DWORD CoLoR2, DWORD CoLoR3, DWORD CoLoR4, DWORD CoLoR5, DWORD CoLoR6, DWORD CoLoR7, DWORD CoLoR8, DWORD CoLoR9, DWORD CoLoR10, LPDIRECT3DDEVICE9 pDevice);
	void cDraw::Engine_Scroll(int x, int y, int  &studio, char **typ, int max, LPSTR text, IDirect3DDevice9* pDevice);

private:
};

