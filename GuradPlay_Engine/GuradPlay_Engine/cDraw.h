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
	char* FPS(void);
	ID3DXFont*		pFont;
    ID3DXFont*		mFont;
    ID3DXFont*		rFont;
    ID3DXLine*		pLine;
    ID3DXSprite*	pSprite;

	BOOL  IsInBox(int x,int y,int w,int h);
	BOOL  State_Key(int Key,DWORD dwTimeOut);

	void  InitFont(CHAR* szFontFamily ,int W ,DWORD Stile ,IDirect3DDevice9* mDevice);

	void  Engine_Text(int x, int y, DWORD color, LPSTR text, DWORD ST);
	void  Engine_Line(long Xa ,long Ya ,long Xb ,long Yb ,int Width ,D3DCOLOR Color);
	void  Engine_Box( int x, int y, int w, int h,   D3DCOLOR Color, LPDIRECT3DDEVICE9 m_pD3Ddev);
	void  Engine_Border(int x, int y, int w, int h,int s, D3DCOLOR Color, LPDIRECT3DDEVICE9 m_pD3Ddev);

	void  SHOW_MENU(LPDIRECT3DDEVICE9  pDevice);
	void  KeyMenu(DWORD KEY ,LPDIRECT3DDEVICE9  pDevice);

	void  Engine_MenuTitle(int x, int y, LPSTR MenuText, LPDIRECT3DDEVICE9  pDevice);
	void  Engine_ButtonFloder(int x, int y, int Button_Mass, LPDIRECT3DDEVICE9  pDevice);
	void  Engine_FunctionFloder(int x, int y, int Elemenst_Mass, LPDIRECT3DDEVICE9  pDevice);

	void  Engine_Button(int x, int y, bool &GPengine, LPSTR text, IDirect3DDevice9* pDevice);
	void  Engine_DoubleCheck(int x, int y, bool &GPengine, LPSTR text, IDirect3DDevice9* pDevice);
	void  Engine_CheckBox(int x, int y, bool &GPengine, LPSTR text, IDirect3DDevice9* pDevice);
	void  Engine_Scroll(int x,int y,int &var,char **typ,int max, LPSTR text, IDirect3DDevice9* pDevice);
};