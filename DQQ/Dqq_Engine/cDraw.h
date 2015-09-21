#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "cFont.h"
#include "colors.h"

#define C_Text (DT_CENTER|DT_NOCLIP)
#define L_Text (DT_LEFT|DT_NOCLIP)
#define R_Text (DT_RIGHT|DT_NOCLIP)

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
	bool Show, Create;
	CD3DFont *m_pFont;
	LPD3DXLINE pLine;

	enum gr_orientation	{ horizontal, vertical };

	BOOL  IsInBox(int x, int y, int w, int h);
	BOOL  State_Key(int Key, DWORD dwTimeOut);
	void  PreReset(void);
	void  PostReset(IDirect3DDevice9* mDevice);
	void  Draw_Text(int x, int y, DWORD color, LPSTR text, DWORD ST);
	void  Draw_Line(long Xa, long Ya, long Xb, long Yb, int Width, D3DCOLOR Color);
	void  Draw_Box(int x, int y, int w, int h, D3DCOLOR Color, LPDIRECT3DDEVICE9 m_pD3Ddev);
	void  Draw_Border(int x, int y, int w, int h,int s, D3DCOLOR Color, LPDIRECT3DDEVICE9 m_pD3Ddev);
	void  SHOW_MENU(LPDIRECT3DDEVICE9  pDevice);
	void  Initialize_Menu(DWORD KEY, IDirect3DDevice9* m_pD3Ddev);
	void  Draw_Gradient_Box(float x, float y, float width, float height, DWORD startCol, DWORD endCol, gr_orientation orientation, IDirect3DDevice9* mDevice);
	void  DrawBox(int x, int y, int w, int h, D3DCOLOR Color, LPDIRECT3DDEVICE9 pD3D9);
	void  Draw_Menu(int x, int y, IDirect3DDevice9* pDevice);
	void  Draw_Triangle(int x, int y,D3DCOLOR Color, IDirect3DDevice9* mDevice);
	void  Draw_Button(int x, int y, bool &var, LPSTR text, IDirect3DDevice9* mDevice);
	void  Draw_Button_Check(int x, int y, bool &var, LPSTR text, IDirect3DDevice9* mDevice);
	void  Draw_Button_Scroll(int x, int y, int &var, char **typ, int max, LPSTR text, IDirect3DDevice9* mDevice);
	void  Draw_Space(int y, IDirect3DDevice9* mDevice);
};