#include "cRender.h"
cRender Render;

bool     cRender::Initialize(IDirect3DDevice9* m_pDevice, const TCHAR* strFontName, DWORD dwFontHeight)
{
	if (!m_pDevice) return false;
	this->m_pDevice = m_pDevice;
	this->strFontName = strFontName;
	this->dwFontHeight = dwFontHeight;
	return true;
}
HRESULT  cRender::FontRestore()
{
	this->m_pFont = new cFont(this->strFontName, this->dwFontHeight/*, D3DFONT_BOLD*/);
	this->m_pFont->InitDeviceObjects(this->m_pDevice);
	this->m_pFont->RestoreDeviceObjects();
	return S_OK;
}
HRESULT  cRender::FontReset(void)
{
	this->m_pFont->InvalidateDeviceObjects();
	this->m_pFont->DeleteDeviceObjects();
	delete m_pFont;
	this->m_pFont = NULL;
	return S_OK;
}

void  cRender::render_String(float x, float y, DWORD color, DWORD Flag, const char *fmt, ...)
{
	char buf[1024] = { '\0' };
	va_list va_alist;
	va_start(va_alist, fmt);
	vsprintf(buf, fmt, va_alist);
	va_end(va_alist);
	m_pFont->DrawText(x, y, color, buf, Flag | DT_SHADOW);
}
void  cRender::render_Box(float x, float y, float w, float h, DWORD color)
{
	D3DRECT rec;
	rec.x1 = x;
	rec.x2 = x + w;
	rec.y1 = y;
	rec.y2 = y + h;
	this->m_pDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);
	this->m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	this->m_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	this->m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, D3DPT_TRIANGLESTRIP);
	this->m_pDevice->Clear(1, &rec, D3DCLEAR_TARGET, color, 1, 1);
}
void  cRender::render_Border(float x, float y, float w, float h, float s, DWORD color)
{
	render_Box(x, y, s, h, color);
	render_Box(x, y + h, w, s, color);
	render_Box(x, y, w, s, color);
	render_Box(x + w, y, s, h + s, color);
}



