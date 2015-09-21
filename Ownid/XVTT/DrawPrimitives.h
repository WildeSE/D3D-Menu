
void Font(CHAR* FontName, int HFont, DWORD Stile, IDirect3DDevice9* pDevice)
{
	D3DXCreateFont(pDevice, 15, 0, Stile, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, FF_MODERN, "Fixedsys", &pFont);
}

void Line(float x, float y, float x2, float y2, float width, DWORD color)
{
	D3DXVECTOR2 vLine[2];
	pLine->SetWidth(width);
	pLine->SetAntialias(false);
	pLine->SetGLLines(true);
	vLine[0].x = x;
	vLine[0].y = y;
	vLine[1].x = x2;
	vLine[1].y = y2;
	pLine->Begin();
	pLine->Draw(vLine, 2, color);
	pLine->End();

	return;
}

int ViewportInfo(int iCode, LPDIRECT3DDEVICE9 pDevice)
{
	D3DVIEWPORT9 pViewport;
	pDevice->GetViewport(&pViewport);
	int iResult = 0;

	if (iCode == 0)
		iResult = (int)pViewport.X;
	else if (iCode == 1)
		iResult = (int)pViewport.Y;
	else if (iCode == 2)
		iResult = (int)pViewport.Width;
	else if (iCode == 3)
		iResult = (int)pViewport.Height;
	else if (iCode == 4)
		iResult = (int)pViewport.MinZ;
	else if (iCode == 5)
		iResult = (int)pViewport.MaxZ;

	return iResult;
}

void draw_RString(float x, float y, DWORD color, const char *fmt, ...)
{
	RECT FontPos = { x, y, x + 20, y + 10 };
	char buf[1024] = { '\0' };
	va_list va_alist;
	va_start(va_alist, fmt);
	vsprintf_s(buf, fmt, va_alist);
	va_end(va_alist);
	pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	rFont->DrawText(pSprite, buf, -1, &FontPos, DT_CENTER | DT_NOCLIP, color);
	pSprite->End();
}
void  Text(LPSTR text, int x, int y, DWORD color, DWORD ST)
{
	RECT rect, rect2;
	SetRect(&rect, x, y, x, y);
	SetRect(&rect2, x - 0.1, y + 0.2, x - 0.1, y + 0.);
	pFont->DrawTextA(NULL, text, -1, &rect2, ST, 0x00000000);
	pFont->DrawTextA(NULL, text, -1, &rect, ST, color);
}

void ControlESP(D3DVECTOR &vScreen, int i)
{
	int nForce;
	if (rScreenX[i] != vScreen.x)
	{
		if (rScreenX[i] > vScreen.x)
		{
			nForce = (int)((rScreenX[i] - vScreen.x) / 2);
			rScreenX[i] -= nForce;
		}
		else if (rScreenX[i] < vScreen.x)
		{
			nForce = (int)((vScreen.x - rScreenX[i]) / 2);
			rScreenX[i] += nForce;
		}
	}

	if (rScreenY[i] != vScreen.y)
	{
		if (rScreenY[i] > vScreen.y)
		{
			nForce = (int)((rScreenY[i] - vScreen.y) / 2);
			rScreenY[i] -= nForce;
		}
		else if (rScreenY[i] < vScreen.y)
		{
			nForce = (int)((vScreen.y - rScreenY[i]) / 2);
			rScreenY[i] += nForce;
		}
	}
}
void  Box(int x, int y, int w, int h, D3DCOLOR Color, LPDIRECT3DDEVICE9 pDevice)
{
	struct Vertex
	{
		float x, y, z, ht;
		DWORD Color;
	}
	V[4] = { { x, y + h, 0.0f, 0.0f, Color }, { x, y, 0.0f, 0.0f, Color }, { x + w, y + h, 0.0f, 0.0f, Color }, { x + w, y, 0.0f, 0.0f, Color } };

	pDevice->SetTexture(0, NULL);
	pDevice->SetPixelShader(0);
	pDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, V, sizeof(Vertex));
	return;
}

void Border(int x, int y, int w, int h, int s, D3DCOLOR Color, LPDIRECT3DDEVICE9 pDevice)
{
	Box(x - s, y, s, h, Color, pDevice);
	Box(x - s, y + h, w + s * 2, s, Color, pDevice);
	Box(x - s, y - s, w + s * 2, s, Color, pDevice);
	Box(x + w, y, s, h + s, Color, pDevice);
}



BOOL  IsInBox(int x, int y, int w, int h)
{
	POINT MousePosition;
	GetCursorPos(&MousePosition);
	ScreenToClient(GetForegroundWindow(), &MousePosition);
	return(MousePosition.x >= x && MousePosition.x <= x + w && MousePosition.y >= y && MousePosition.y <= y + h);
}


void DrawGrad(int x, int y, int w, int h, DWORD one, DWORD two, LPDIRECT3DDEVICE9 pDevice)
{
	struct D3DVERTEX
	{
		float x, y, z, rhw;
		DWORD color;
	};

	D3DVERTEX   vertices[4] =
	{
		{ x, y, w, h, one },
		{ x, y, w, h, one },
		{ x, y, w, h, one },
		{ x, y, w, h, one }
	};

	vertices[0].x = x;
	vertices[0].y = y;
	vertices[0].rhw = 1.0f;
	vertices[0].color = one;

	vertices[1].x = x + w;
	vertices[1].y = y;
	vertices[1].rhw = 1.0f;
	vertices[1].color = one;

	vertices[2].x = x;
	vertices[2].y = y + h;
	vertices[2].rhw = 1.0f;
	vertices[2].color = two;

	vertices[3].x = x + w;
	vertices[3].y = y + h;
	vertices[3].rhw = 1.0f;
	vertices[3].color = two;


	pDevice->SetTexture(0, NULL);
	pDevice->SetPixelShader(0);
	pDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vertices, sizeof(D3DVERTEX));


}