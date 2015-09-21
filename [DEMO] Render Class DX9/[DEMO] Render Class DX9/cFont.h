#pragma once

#include <tchar.h>
#include <D3DX9.h>
#include <cstdio>
#define D3DFONT_BOLD        0x0001
#define D3DFONT_ITALIC      0x0002
#define D3DFONT_ZENABLE     0x0004
#define D3DFONT_CENTERED    0x0001
#define D3DFONT_TWOSIDED    0x0002
#define D3DFONT_FILTERED    0x0004
#define DT_SHADOW           0x0040   
#define MAX_NUM_VERTICES    50*6


#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=NULL; } }
#define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p)=NULL; } }

class cFont
{
	static const int MAX_CHAR_INDEX = 255;
	TCHAR   strFontName[80];
	DWORD   dwFontHeight;
	DWORD   dwFontFlags;
	LPDIRECT3DDEVICE9       m_pDevice; 
	LPDIRECT3DTEXTURE9      m_pTexture;   
	LPDIRECT3DVERTEXBUFFER9 m_pVB;       
	DWORD   dwWidth;                 
	DWORD   dwHeight;
	FLOAT   m_fTextScale;
	FLOAT   m_fTexCoords[MAX_CHAR_INDEX + 1 - 32][4];
	LPDIRECT3DSTATEBLOCK9 m_pStateBlockSaved;
	LPDIRECT3DSTATEBLOCK9 m_pStateBlockDrawText;
private:
	bool CheckChar(unsigned char c) { return c < 32 || c > MAX_CHAR_INDEX; }
	D3DVIEWPORT9 m_ViewPort;
public:
	cFont(const TCHAR* strFontName, DWORD dwHeight, DWORD dwFlags = 0L);
	~cFont();

	HRESULT DrawText(FLOAT sx, FLOAT sy, DWORD dwColor, const char* strText, DWORD dwFlags);
	//HRESULT DrawTextScrolling(INT y, INT speed, DWORD dwColor, DWORD dwFlags, const char *fmt, ...);

	HRESULT InitDeviceObjects(LPDIRECT3DDEVICE9 pDevice);
	HRESULT RestoreDeviceObjects();

	HRESULT InvalidateDeviceObjects();
	HRESULT DeleteDeviceObjects();

	HRESULT  GetTextExtent(const char* strText, SIZE* pSize);

	INT GetTextLength(char* text)
	{
		SIZE Size = { 0, 0 };
		if (GetTextExtent(text, &Size) == S_OK)
			return Size.cx;
		return 0;
	}
};

struct FONT2DVERTEX { D3DXVECTOR4 p;   DWORD color;     FLOAT tu, tv; };
struct FONT3DVERTEX { D3DXVECTOR3 p;   D3DXVECTOR3 n;   FLOAT tu, tv; };

#define D3DFVF_FONT2DVERTEX (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)
#define D3DFVF_FONT3DVERTEX (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX1)

inline FONT2DVERTEX InitFont2DVertex(const D3DXVECTOR4& p, D3DCOLOR color,FLOAT tu, FLOAT tv)
{
	FONT2DVERTEX v;   v.p = p;   v.color = color;   v.tu = tu;   v.tv = tv;
	return v;
}
inline FONT3DVERTEX InitFont3DVertex(const D3DXVECTOR3& p, const D3DXVECTOR3& n,FLOAT tu, FLOAT tv)
{
	FONT3DVERTEX v;   v.p = p;   v.n = n;   v.tu = tu;   v.tv = tv;
	return v;
}
