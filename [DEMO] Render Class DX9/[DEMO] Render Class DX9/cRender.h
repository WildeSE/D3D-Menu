#pragma once
#include <Windows.h>
#include <stdio.h>
#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"d3d9.lib")


#include "cFont.h"
class cRender
{
public:
	HRESULT FontRestore();
	HRESULT FontReset(void);

	bool  Initialize(IDirect3DDevice9* m_pDevice, const TCHAR* strFontName, DWORD dwFontHeight);

	void   render_String(float x, float y, DWORD color, DWORD Flag, const char *fmt, ...);
	void   render_Box(float x, float y, float w, float h, DWORD color);
	void   render_Border(float x, float y, float w, float h, float s, DWORD color);



protected:
	IDirect3DDevice9* m_pDevice;
	const TCHAR* strFontName;
	DWORD dwFontHeight;
	cFont *m_pFont;
};
extern cRender Render;
