
//-----------------------------------------------------------------------------
// Exam: Font("Arial",15,FW_NORMAL,pDevice);
// Desc: Опции шрифта
// Сonc: Menu
//-----------------------------------------------------------------------------

void Font(CHAR* FontName, int HFont, DWORD Stile, IDirect3DDevice9* pDevice)
{
	D3DXCreateFont(pDevice, HFont, 0, Stile, 1, 0, RUSSIAN_CHARSET, OUT_DEVICE_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_DONTCARE, FontName, &pFont);
}
void DrawBox(FLOAT x, FLOAT y, FLOAT w, FLOAT h, D3DCOLOR Color, LPDIRECT3DDEVICE9 pDevice)
{
	D3DRECT rec = { x, y - h, x + w, y };
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pDevice->Clear(1, &rec, D3DCLEAR_TARGET, Color, 0, 0);
}

void DrawBorder(int x, int y, int w, int h, int o, D3DCOLOR color, LPDIRECT3DDEVICE9 pDevice)
{
	DrawBox(x, y, w, 2, color, pDevice);
	DrawBox(x - 1, y, 2, h, color, pDevice);
	DrawBox(x - 1, y - h, w + 2 + 1, 2, color, pDevice);
	DrawBox(x + w, y, 2, h, color, pDevice);
}

void Draw_ESP_Border(int X, int Y, float Distance_Player, DWORD Color, LPDIRECT3DDEVICE9 pDevice)
{
	float drawW = 600 / Distance_Player;
	float drawH = 1400 / Distance_Player;

	DrawBorder(X - drawW / 2, Y, drawW, drawH, 2, Color, pDevice);
}
LPD3DXLINE S_Line;
void DrawLine(float StartX, float StartY, float EndX, float EndY, int Width, D3DCOLOR dColor)
{
	S_Line[0].SetWidth(Width);
	S_Line[0].SetGLLines(0);
	S_Line[0].SetAntialias(1);
	D3DXVECTOR2 v2Line[2];
	v2Line[0].x = StartX;
	v2Line[0].y = StartY;
	v2Line[1].x = EndX;
	v2Line[1].y = EndY;
	S_Line[0].Begin();
	S_Line[0].Draw(v2Line, 2, dColor);
	S_Line[0].End();
}
void Draw_ESP3D_Border(int HeadX, int HeadY, int bottomX, int bottomY, float Distance_Player, DWORD Color)
{
	float drawW = 400 / Distance_Player;
	float drawW2 = 200 / Distance_Player;
	float drawW3 = 100 / Distance_Player;
	DrawLine(bottomX - drawW / 2, bottomY, bottomX + drawW, drawW, 2, Color);
	DrawLine(bottomX - drawW, bottomY, bottomX + drawW, bottomY, 1, Color);
	DrawLine(HeadX - drawW, HeadY, HeadX + drawW, HeadY, 1, Color);
	DrawLine(HeadX - drawW, HeadY, bottomX - drawW, bottomY, 1, Color);
	DrawLine(HeadX + drawW, HeadY, bottomX + drawW, bottomY, 1, Color);
	DrawLine(HeadX - drawW2, HeadY - drawW3, bottomX - drawW2, bottomY - drawW3, 1, Color);
	DrawLine(bottomX - drawW, bottomY, bottomX - drawW2, bottomY - drawW3, 1, Color);
	DrawLine(HeadX - drawW, HeadY, HeadX - drawW2, HeadY - drawW3, 1, Color);
	DrawLine((HeadX + drawW) + drawW2, HeadY - drawW3, (bottomX + drawW) + drawW2, bottomY - drawW3, 1, Color);
	DrawLine(bottomX + drawW, bottomY, (bottomX + drawW) + drawW2, bottomY - drawW3, 1, Color);
	DrawLine(HeadX + drawW, HeadY, (HeadX + drawW) + drawW2, HeadY - drawW3, 1, Color);
	DrawLine(HeadX - drawW2, HeadY - drawW3, (HeadX + drawW) + drawW2, HeadY - drawW3, 1, Color);
	DrawLine(bottomX - drawW2, bottomY - drawW3, (bottomX + drawW) + drawW2, bottomY - drawW3, 1, Color);
}
void DrawString(float x, float y, DWORD color, const char *fmt, ...)
{
	RECT FontPos = { x, y, x + 20, y + 10 };
	char buf[1024] = { '\0' };
	va_list va_alist;
	va_start(va_alist, fmt);
	vsprintf(buf, fmt, va_alist);
	va_end(va_alist);
	pFont->DrawText(NULL, buf, -1, &FontPos, DT_NOCLIP, color);
}
void  Text(LPSTR text, int x, int y, DWORD color, DWORD ST)
{
	RECT rect, rect2;
	SetRect(&rect, x, y, x, y);
	SetRect(&rect2, x - 0.1, y + 0.2, x - 0.1, y + 0.);
	pFont->DrawTextA(NULL, text, -1, &rect2, ST, 0x00000000);
	pFont->DrawTextA(NULL, text, -1, &rect, ST, color);
}
void  Text1(LPSTR text, int x, int y, DWORD color, DWORD ST)
{
	RECT rect, rect2;
	SetRect(&rect, x, y, x, y);
	SetRect(&rect2, x - 0.1, y + 0.2, x - 0.1, y + 0.);
	pFont->DrawTextA(NULL, text, -1, &rect2, ST, DARK14);
	pFont->DrawTextA(NULL, text, -1, &rect, ST, DARK14);
}

void  Box(int x, int y, int w, int h, D3DCOLOR Color, LPDIRECT3DDEVICE9 pD3D9)
{
	struct Vertex
	{
		float x, y, z, ht;
		DWORD Color;
	}
	V[4] = { {x, y + h, 0.0f, 0.0f, Color}, { x, y, 0.0f, 0.0f, Color }, { x + w, y + h, 0.0f, 0.0f, Color }, { x + w, y, 0.0f, 0.0f, Color } };

	pD3D9->SetTexture(0, NULL);
	pD3D9->SetPixelShader(0);
	pD3D9->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
	pD3D9->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	pD3D9->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pD3D9->SetRenderState(D3DRS_ZENABLE, FALSE);
	pD3D9->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	pD3D9->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, V, sizeof(Vertex));
	return;
}

void Border(int x, int y, int w, int h, int s, D3DCOLOR Color, LPDIRECT3DDEVICE9 pD3D9)
{
	Box(x - s, y, s, h, Color, pD3D9);
	Box(x - s, y + h, w + s * 2, s, Color, pD3D9);
	Box(x - s, y - s, w + s * 2, s, Color, pD3D9);
	Box(x + w, y, s, h + s, Color, pD3D9);
}

void Circle(int X, int Y, int radius, int numSides, DWORD Color, LPDIRECT3DDEVICE9 pDevice)
{
	D3DXVECTOR2 Line[128];
	float Step = PI * 2.0 / numSides;
	int Count = 0;
	for (float a = 0; a < PI * 2.0; a += Step)
	{
		float X1 = radius * cos(a) + X;
		float Y1 = radius * sin(a) + Y;
		float X2 = radius * cos(a + Step) + X;
		float Y2 = radius * sin(a + Step) + Y;
		Line[Count].x = X1;
		Line[Count].y = Y1;
		Line[Count + 1].x = X2;
		Line[Count + 1].y = Y2;
		Count += 2;
	}
	pLine->Begin();
	pLine->Draw(Line, Count, Color);
	pLine->End();
}

//-----------------------------------------------------------------------------
// Компоненты ColorCircle
//-----------------------------------------------------------------------------

HRESULT GenerateTexture(IDirect3DDevice9 *pD3Ddev, IDirect3DTexture9 **ppD3Dtex, DWORD colour32)
{
	if (FAILED(pD3Ddev->CreateTexture(8, 8, 1, 0, D3DFMT_A4R4G4B4, D3DPOOL_MANAGED, ppD3Dtex, NULL)))
		return E_FAIL;

	WORD colour16 = ((WORD) ((colour32 >> 28) & 0xF) << 12)
		| (WORD) (((colour32 >> 20) & 0xF) << 8)
		| (WORD) (((colour32 >> 12) & 0xF) << 4)
		| (WORD) (((colour32 >> 4) & 0xF) << 0);

	D3DLOCKED_RECT d3dlr;
	(*ppD3Dtex)->LockRect(0, &d3dlr, 0, 0);
	WORD *pDst16 = (WORD*) d3dlr.pBits;

	for (int xy = 0; xy < 8 * 8; xy++)
		*pDst16++ = colour16;

	(*ppD3Dtex)->UnlockRect(0);

	return S_OK;
}
struct D3DTLVERTEX{ float fX; float fY; float fZ; float fRHW;	D3DCOLOR Color;	float fU;	float fV; };
D3DTLVERTEX Vtex[400];
D3DTLVERTEX CreateD3DTLVERTEX(float X, float Y, float Z, float RHW, D3DCOLOR color, float U, float V)
{
	D3DTLVERTEX v;
	v.fX = X; v.fY = Y; v.fZ = Z;
	v.fRHW = RHW; v.Color = color;
	v.fU = U; v.fV = V;
	return v;
}

//-----------------------------------------------------------------------------
// Exam: ColorCircle(x,y,10,10,Colorit,pDevice);
// Desc: ЦветнойКруг
// Сonc: Menu
//-----------------------------------------------------------------------------

void ColorCircle(int x, int y, int radius, DWORD Colorit, IDirect3DDevice9* pDevice)
{
	float xPos = (float) x;
	float yPos = (float) y;
	LPDIRECT3DTEXTURE9 Col_ = NULL;
	GenerateTexture(pDevice, &Col_, Colorit);
	D3DCOLOR Color = D3DCOLOR_ARGB(255, 255, 255, 255);
	pDevice->SetTexture(0, Col_);
	float x1 = xPos;
	float y1 = yPos;
	for (int i = 0; i <= 363; i += 3)
	{
		float angle = (i / 57.3f);
		float x2 = xPos + (radius * sin(angle));
		float y2 = yPos + (radius * cos(angle));
		Vtex[i] = CreateD3DTLVERTEX(xPos, yPos, 0, 1, Color, 0, 0);
		Vtex[i + 1] = CreateD3DTLVERTEX(x1, y1, 0, 1, Color, 0, 0);
		Vtex[i + 2] = CreateD3DTLVERTEX(x2, y2, 0, 1, Color, 0, 0);

		y1 = y2;
		x1 = x2;
	}
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 363, Vtex, sizeof(D3DTLVERTEX));
}

//-----------------------------------------------------------------------------
// Exam: Xhair(Size,Width,Color,10,pDevice);
// Desc: Перехрестие в центре екрана (Прицел в шутерах , CrossHair)
// Сonc: Menu
//-----------------------------------------------------------------------------

VOID Xhair(int Size, int Width, D3DCOLOR Color, IDirect3DDevice9* pDevice)
{
	D3DVIEWPORT9 cViewport;
	pDevice->GetViewport(&cViewport);
	int x = cViewport.Width / 2;
	int y = cViewport.Height / 2;

	D3DRECT rec = { x - Size, y, x + Size, y + Width };
	D3DRECT rec2 = { x, y - Size, x + Width, y + Size };
	pDevice->Clear(1, &rec, D3DCLEAR_TARGET, Color, 0, 0);
	pDevice->Clear(1, &rec2, D3DCLEAR_TARGET, Color, 0, 0);
}

//-----------------------------------------------------------------------------
// Exam: D3D9ScreenShot(pDevice);
// Desc: СкринШот
// Сonc: Menu
//-----------------------------------------------------------------------------

void D3D9ScreenShot(IDirect3DDevice9* pDevice)
{
	sprintf(FileName, "NewScreenShot %d.jpg", I);
	pDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &surf);
	D3DXSaveSurfaceToFile(FileName, D3DXIFF_JPG, surf, NULL, NULL);
	I++;
	Beep(1000, 100);
}

//-----------------------------------------------------------------------------
// Exam: IsInBox(x,y,w,h);
// Desc: Наведение
// Сonc: Components
//-----------------------------------------------------------------------------

BOOL  IsInBox(int x, int y, int w, int h)
{
	POINT MousePosition;
	GetCursorPos(&MousePosition);
	ScreenToClient(GetForegroundWindow(), &MousePosition);
	return(MousePosition.x >= x && MousePosition.x <= x + w && MousePosition.y >= y && MousePosition.y <= y + h);
}

//-----------------------------------------------------------------------------
// Exam: ButtonBorder(Size,Width,Color,10,pDevice);
// Desc: Перехрестие в центре екрана (Прицел в шутерах , CrossHair)
// Сonc: Menu
//-----------------------------------------------------------------------------

void ButtonBorder(int x, int y, LPDIRECT3DDEVICE9 pD3D9)
{
	Box(x, y - 1, 100, 1, DARK27, pD3D9);
	Box(x + 1, y - 1, 98, 1, DARK17, pD3D9);

	Box(x, y + 20, 100, 1, DARK27, pD3D9);
	Box(x + 1, y + 20, 98, 1, DARK17, pD3D9);

	Box(x - 1, y, 1, 20, DARK27, pD3D9);
	Box(x - 1, y + 1, 1, 18, DARK17, pD3D9);

	Box(x + 100, y, 1, 20, DARK27, pD3D9);
	Box(x + 100, y + 1, 1, 18, DARK17, pD3D9);
	Border(x, y, 99, 19, 1, DARK37, pD3D9);

}