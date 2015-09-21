#include "cFont.h"


cFont::cFont(const TCHAR* strFontName, DWORD dwHeight, DWORD dwFlags)
{
	_tcsncpy(this->strFontName, strFontName, sizeof(this->strFontName) / sizeof(TCHAR));
	this->strFontName[sizeof(this->strFontName) / sizeof(TCHAR)-1] = _T('\0');
	this->dwFontHeight = dwHeight;
	this->dwFontFlags = dwFlags;

	this->m_pDevice = NULL;
	this->m_pTexture = NULL;
	this->m_pVB = NULL;

	this->m_pStateBlockSaved = NULL;
	this->m_pStateBlockDrawText = NULL;
}

HRESULT cFont::InitDeviceObjects(LPDIRECT3DDEVICE9 pDevice)
{
	HRESULT hr;
	this->m_pDevice= pDevice;
	m_fTextScale = 1.0f; 

	if (dwFontHeight > 40)dwWidth = dwHeight = 1024;
	else 
	if (dwFontHeight > 20)dwWidth = dwHeight = 512;
	else
		dwWidth = dwHeight = 256;


	D3DCAPS9 d3dCaps;
	pDevice->GetDeviceCaps(&d3dCaps);

	if (dwWidth > d3dCaps.MaxTextureWidth)
	{
		m_fTextScale = (FLOAT)d3dCaps.MaxTextureWidth / (FLOAT)dwWidth;
		dwWidth =dwHeight = d3dCaps.MaxTextureWidth;
	}

	
	hr = pDevice->CreateTexture(dwWidth, dwHeight, 1,0, D3DFMT_A4R4G4B4,D3DPOOL_MANAGED, &m_pTexture, 0);
	if (FAILED(hr))return hr;

	DWORD*      pBitmapBits;
	BITMAPINFO bmi;
	ZeroMemory(&bmi.bmiHeader, sizeof(BITMAPINFOHEADER));
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = (int)dwWidth;
	bmi.bmiHeader.biHeight = -(int)dwHeight;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biCompression = BI_RGB;
	bmi.bmiHeader.biBitCount = 32;


	HDC     hDC = CreateCompatibleDC(NULL);
	HBITMAP hbmBitmap = CreateDIBSection(hDC, &bmi, DIB_RGB_COLORS, (void**)&pBitmapBits, NULL, 0);
	SetMapMode(hDC, MM_TEXT);

	INT nHeight = -MulDiv(dwFontHeight, (INT)(GetDeviceCaps(hDC, LOGPIXELSY) * m_fTextScale), 72);

	DWORD dwBold =   (dwFontFlags & D3DFONT_BOLD)   ? FW_EXTRABOLD : FW_NORMAL;
	DWORD dwItalic = (dwFontFlags & D3DFONT_ITALIC) ? TRUE         : FALSE;

	HFONT hFont = CreateFont(nHeight, 0, 0, 0, dwBold, dwItalic,
		FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY,
		VARIABLE_PITCH, strFontName);
	if (NULL == hFont)
		return E_FAIL;

	HGDIOBJ hPrevBitmap = SelectObject(hDC, hbmBitmap);
	HGDIOBJ hPrevFont = SelectObject(hDC, hFont);
	SetTextColor(hDC, RGB(255, 255, 255));
	SetBkColor(hDC, 0x00000000);
	SetTextAlign(hDC, TA_TOP);
	DWORD x = 0;
	DWORD y = 0;
	char str[2] = "x";
	SIZE size;

	for (int c = 32; c <= MAX_CHAR_INDEX; c++)
	{
		str[0] = c;
		GetTextExtentPoint32A(hDC, str, 1, &size);

		if ((DWORD)(x + size.cx + 1) > dwWidth)
		{
			x = 0;
			y += size.cy + 1;
		}

		ExtTextOutA(hDC, x + 0, y + 0, ETO_OPAQUE, NULL, str, 1, NULL);

		m_fTexCoords[c - 32][0] = ((FLOAT)(x + 0)) / dwWidth;
		m_fTexCoords[c - 32][1] = ((FLOAT)(y + 0)) / dwWidth;
		m_fTexCoords[c - 32][2] = ((FLOAT)(x + 0 + size.cx)) / dwWidth;
		m_fTexCoords[c - 32][3] = ((FLOAT)(y + 0 + size.cy)) / dwWidth;

		x += size.cx + 1;
	}


	D3DLOCKED_RECT d3dlr;
	m_pTexture->LockRect(0, &d3dlr, 0, 0);
	BYTE* pDstRow = (BYTE*)d3dlr.pBits;
	WORD* pDst16;
	BYTE bAlpha; 

	for (y = 0; y < dwHeight; y++)
	{
		pDst16 = (WORD*)pDstRow;
		for (x = 0; x < dwWidth; x++)
		{
			bAlpha = (BYTE)((pBitmapBits[dwWidth*y + x] & 0xff) >> 4);
			if (bAlpha > 0)
			{
				*pDst16++ = (bAlpha << 12) | 0x0fff;
			}
			else
			{
				*pDst16++ = 0x0000;
			}
		}
		pDstRow += d3dlr.Pitch;
	}
	m_pTexture->UnlockRect(0);

	
	SelectObject(hDC, hPrevBitmap);
	SelectObject(hDC, hPrevFont);

	DeleteObject(hbmBitmap);
	DeleteDC(hDC);
	DeleteObject(hFont);

	return S_OK;
}

HRESULT cFont::RestoreDeviceObjects()
{
	HRESULT hr;

	int vertexSize = max(sizeof(FONT2DVERTEX), sizeof(FONT3DVERTEX));
	if (FAILED(hr = this->m_pDevice->CreateVertexBuffer(MAX_NUM_VERTICES * vertexSize,D3DUSAGE_WRITEONLY | D3DUSAGE_DYNAMIC, 0,D3DPOOL_DEFAULT, &m_pVB, 0)))
	{return hr;}


	for (UINT which = 0; which<2; which++)
	{
		this->m_pDevice->BeginStateBlock();
		this->m_pDevice->SetTexture(0, m_pTexture);

		if (D3DFONT_ZENABLE & dwFontFlags)
			this->m_pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
		else
			this->m_pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);

		this->m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		this->m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		this->m_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		this->m_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		this->m_pDevice->SetRenderState(D3DRS_ALPHAREF, 0x08);
		this->m_pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);
		this->m_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
		this->m_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
		this->m_pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);
		this->m_pDevice->SetRenderState(D3DRS_CLIPPING, TRUE);
		this->m_pDevice->SetRenderState(D3DRS_CLIPPLANEENABLE, FALSE);
		this->m_pDevice->SetRenderState(D3DRS_VERTEXBLEND, D3DVBF_DISABLE);
		this->m_pDevice->SetRenderState(D3DRS_INDEXEDVERTEXBLENDENABLE, FALSE);
		this->m_pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);
		this->m_pDevice->SetRenderState(D3DRS_COLORWRITEENABLE,
			D3DCOLORWRITEENABLE_RED | D3DCOLORWRITEENABLE_GREEN |
			D3DCOLORWRITEENABLE_BLUE | D3DCOLORWRITEENABLE_ALPHA);
		this->m_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
		this->m_pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		this->m_pDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
		this->m_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
		this->m_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
		this->m_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
		this->m_pDevice->SetTextureStageState(0, D3DTSS_TEXCOORDINDEX, 0);
		this->m_pDevice->SetTextureStageState(0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_DISABLE);
		this->m_pDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
		this->m_pDevice->SetTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
		this->m_pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);
		this->m_pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
		this->m_pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_NONE);

		if (which == 0)
			this->m_pDevice->EndStateBlock(&m_pStateBlockSaved);
		else
			this->m_pDevice->EndStateBlock(&m_pStateBlockDrawText);
	}

	return S_OK;
}
HRESULT cFont::InvalidateDeviceObjects()
{
	SAFE_RELEASE(m_pVB);
	SAFE_RELEASE(m_pStateBlockSaved);
	SAFE_RELEASE(m_pStateBlockDrawText);

	return S_OK;
}
HRESULT cFont::DeleteDeviceObjects()
{
	SAFE_RELEASE(m_pTexture);
	this->m_pDevice = NULL;

	return S_OK;
}

HRESULT cFont::GetTextExtent(const char* strText, SIZE* pSize)
{
	if (NULL == strText || NULL == pSize)
		return E_FAIL;

	FLOAT fRowWidth = 0.0f;
	FLOAT fRowHeight = (m_fTexCoords[0][3] - m_fTexCoords[0][1])*dwHeight;
	FLOAT fWidth = 0.0f;
	FLOAT fHeight = fRowHeight;

	while (*strText)
	{
		unsigned char c = *strText++;

		if (c == '\n')
		{
			fRowWidth = 0.0f;
			fHeight += fRowHeight;
		}

		if (CheckChar(c))
			continue;

		FLOAT tx1 = m_fTexCoords[c - 32][0];
		FLOAT tx2 = m_fTexCoords[c - 32][2];

		fRowWidth += (tx2 - tx1)*dwWidth;

		if (fRowWidth > fWidth)
			fWidth = fRowWidth;
	}

	pSize->cx = (int)fWidth;
	pSize->cy = (int)fHeight;

	return S_OK;
}

HRESULT cFont::DrawText(FLOAT sx, FLOAT sy, DWORD dwColor, const char* strText, DWORD dwFlags)
{
	if (this->m_pDevice == NULL)return E_FAIL;
	m_pStateBlockSaved->Capture();
	m_pStateBlockDrawText->Apply();
	this->m_pDevice->SetFVF(D3DFVF_FONT2DVERTEX);
	this->m_pDevice->SetPixelShader(NULL);
	this->m_pDevice->SetStreamSource(0, m_pVB, 0, sizeof(FONT2DVERTEX));
	if (dwFlags & D3DFONT_FILTERED)
	{
		this->m_pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
		this->m_pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	}
	if (dwFlags & DT_RIGHT)
	{
		SIZE sz;
		GetTextExtent(strText, &sz); sx -= (FLOAT)sz.cx;
	}
	if (dwFlags & DT_CENTER)
	{
		SIZE sz;
		GetTextExtent(strText, &sz); sx -= (FLOAT)(sz.cx / 2.0);
	}
	FLOAT fStartX = sx;
	FONT2DVERTEX* pVertices = NULL;
	DWORD         dwNumTriangles = 0;
	m_pVB->Lock(0, 0, (void**)&pVertices, D3DLOCK_DISCARD);
	while (*strText)
	{
		unsigned char c = *strText++;
		if (c == '\n')
		{
			sx = fStartX;
			sy += (m_fTexCoords[0][3] - m_fTexCoords[0][1])*dwHeight;
		}
		if (CheckChar(c))
			continue;
		FLOAT tx1 = m_fTexCoords[c - 32][0];
		FLOAT ty1 = m_fTexCoords[c - 32][1];
		FLOAT tx2 = m_fTexCoords[c - 32][2];
		FLOAT ty2 = m_fTexCoords[c - 32][3];

		FLOAT w = (tx2 - tx1) *  dwWidth / m_fTextScale;
		FLOAT h = (ty2 - ty1) * dwHeight / m_fTextScale;

		if (c != ' ')
		{
			if (dwFlags & DT_SHADOW)
			{
				float sxa, sya;
				sxa = sx;
				sya = sy;
				sxa = sx + 1.0f;
				*pVertices++ = InitFont2DVertex(D3DXVECTOR4(sxa + 0 - 0.5f, sy + h - 0.5f, 0.9f, 1.0f), 0xff000000, tx1, ty2);
				*pVertices++ = InitFont2DVertex(D3DXVECTOR4(sxa + 0 - 0.5f, sy + 0 - 0.5f, 0.9f, 1.0f), 0xff000000, tx1, ty1);
				*pVertices++ = InitFont2DVertex(D3DXVECTOR4(sxa + w - 0.5f, sy + h - 0.5f, 0.9f, 1.0f), 0xff000000, tx2, ty2);
				*pVertices++ = InitFont2DVertex(D3DXVECTOR4(sxa + w - 0.5f, sy + 0 - 0.5f, 0.9f, 1.0f), 0xff000000, tx2, ty1);
				*pVertices++ = InitFont2DVertex(D3DXVECTOR4(sxa + w - 0.5f, sy + h - 0.5f, 0.9f, 1.0f), 0xff000000, tx2, ty2);
				*pVertices++ = InitFont2DVertex(D3DXVECTOR4(sxa + 0 - 0.5f, sy + 0 - 0.5f, 0.9f, 1.0f), 0xff000000, tx1, ty1);

				sxa = sx - 1.0f;
				*pVertices++ = InitFont2DVertex(D3DXVECTOR4(sxa + 0 - 0.5f, sy + h - 0.5f, 0.9f, 1.0f), 0xff000000, tx1, ty2);
				*pVertices++ = InitFont2DVertex(D3DXVECTOR4(sxa + 0 - 0.5f, sy + 0 - 0.5f, 0.9f, 1.0f), 0xff000000, tx1, ty1);
				*pVertices++ = InitFont2DVertex(D3DXVECTOR4(sxa + w - 0.5f, sy + h - 0.5f, 0.9f, 1.0f), 0xff000000, tx2, ty2);
				*pVertices++ = InitFont2DVertex(D3DXVECTOR4(sxa + w - 0.5f, sy + 0 - 0.5f, 0.9f, 1.0f), 0xff000000, tx2, ty1);
				*pVertices++ = InitFont2DVertex(D3DXVECTOR4(sxa + w - 0.5f, sy + h - 0.5f, 0.9f, 1.0f), 0xff000000, tx2, ty2);
				*pVertices++ = InitFont2DVertex(D3DXVECTOR4(sxa + 0 - 0.5f, sy + 0 - 0.5f, 0.9f, 1.0f), 0xff000000, tx1, ty1);

				sya = sy - 1.0f;
				*pVertices++ = InitFont2DVertex(D3DXVECTOR4(sx + 0 - 0.5f, sya + h - 0.5f, 0.9f, 1.0f), 0xff000000, tx1, ty2);
				*pVertices++ = InitFont2DVertex(D3DXVECTOR4(sx + 0 - 0.5f, sya + 0 - 0.5f, 0.9f, 1.0f), 0xff000000, tx1, ty1);
				*pVertices++ = InitFont2DVertex(D3DXVECTOR4(sx + w - 0.5f, sya + h - 0.5f, 0.9f, 1.0f), 0xff000000, tx2, ty2);
				*pVertices++ = InitFont2DVertex(D3DXVECTOR4(sx + w - 0.5f, sya + 0 - 0.5f, 0.9f, 1.0f), 0xff000000, tx2, ty1);
				*pVertices++ = InitFont2DVertex(D3DXVECTOR4(sx + w - 0.5f, sya + h - 0.5f, 0.9f, 1.0f), 0xff000000, tx2, ty2);
				*pVertices++ = InitFont2DVertex(D3DXVECTOR4(sx + 0 - 0.5f, sya + 0 - 0.5f, 0.9f, 1.0f), 0xff000000, tx1, ty1);
				sya = sy + 1.0f;
				*pVertices++ = InitFont2DVertex(D3DXVECTOR4(sx + 0 - 0.5f, sya + h - 0.5f, 0.9f, 1.0f), 0xff000000, tx1, ty2);
				*pVertices++ = InitFont2DVertex(D3DXVECTOR4(sx + 0 - 0.5f, sya + 0 - 0.5f, 0.9f, 1.0f), 0xff000000, tx1, ty1);
				*pVertices++ = InitFont2DVertex(D3DXVECTOR4(sx + w - 0.5f, sya + h - 0.5f, 0.9f, 1.0f), 0xff000000, tx2, ty2);
				*pVertices++ = InitFont2DVertex(D3DXVECTOR4(sx + w - 0.5f, sya + 0 - 0.5f, 0.9f, 1.0f), 0xff000000, tx2, ty1);
				*pVertices++ = InitFont2DVertex(D3DXVECTOR4(sx + w - 0.5f, sya + h - 0.5f, 0.9f, 1.0f), 0xff000000, tx2, ty2);
				*pVertices++ = InitFont2DVertex(D3DXVECTOR4(sx + 0 - 0.5f, sya + 0 - 0.5f, 0.9f, 1.0f), 0xff000000, tx1, ty1);
				dwNumTriangles += 8;
			}
			*pVertices++ = InitFont2DVertex(D3DXVECTOR4(sx + 0 - 0.5f, sy + h - 0.5f, 0.9f, 1.0f), dwColor, tx1, ty2);
			*pVertices++ = InitFont2DVertex(D3DXVECTOR4(sx + 0 - 0.5f, sy + 0 - 0.5f, 0.9f, 1.0f), dwColor, tx1, ty1);
			*pVertices++ = InitFont2DVertex(D3DXVECTOR4(sx + w - 0.5f, sy + h - 0.5f, 0.9f, 1.0f), dwColor, tx2, ty2);
			*pVertices++ = InitFont2DVertex(D3DXVECTOR4(sx + w - 0.5f, sy + 0 - 0.5f, 0.9f, 1.0f), dwColor, tx2, ty1);
			*pVertices++ = InitFont2DVertex(D3DXVECTOR4(sx + w - 0.5f, sy + h - 0.5f, 0.9f, 1.0f), dwColor, tx2, ty2);
			*pVertices++ = InitFont2DVertex(D3DXVECTOR4(sx + 0 - 0.5f, sy + 0 - 0.5f, 0.9f, 1.0f), dwColor, tx1, ty1);
			dwNumTriangles += 2;
			if (dwNumTriangles * 3 > (MAX_NUM_VERTICES - 6))
			{
				this->m_pVB->Unlock();
				this->m_pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, dwNumTriangles);
				pVertices = NULL;
				this->m_pVB->Lock(0, 0, (void**)&pVertices, D3DLOCK_DISCARD);
				dwNumTriangles = 0L;
			}
		}
		sx += w;
	}
	this->m_pVB->Unlock();
	if (dwNumTriangles > 0)
		this->m_pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, dwNumTriangles);
	m_pStateBlockSaved->Apply();

	return S_OK;
}



cFont::~cFont()
{
	InvalidateDeviceObjects();
	DeleteDeviceObjects();
}



