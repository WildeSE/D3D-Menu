#include "cDraw.h"
#include "cVar.h"

cDraw::cDraw(void)
{
	Show = true;
	Varm.Menu0 = true;
}
void  cDraw::InitFont(CHAR* szFontFamily,int W,DWORD Stile,IDirect3DDevice9* mDevice)
{
	D3DXCreateFont(mDevice, W, 0, Stile, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, FF_MODERN, szFontFamily, &pFonts);
}
void  cDraw::InitFontA(CHAR* szFontFamily,int W,DWORD Stile,IDirect3DDevice9* mDevice)
{
	D3DXCreateFont(mDevice, W, 0, Stile, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, FF_MODERN, szFontFamily, &pFont);
}
/* Бокс */
void  cDraw::DrawBox(int x, int y, int w, int h,   D3DCOLOR Color,IDirect3DDevice9* mDevice)
{
	D3DRECT rec;
	rec.x1 = x;
	rec.x2 = x + w;
	rec.y1 = y;
	rec.y2 = y + h;
	mDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1); 
	mDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,true);
	mDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);   
	mDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,	D3DPT_TRIANGLESTRIP);
	mDevice->Clear( 1, &rec, D3DCLEAR_TARGET, Color, 1, 1 );
}
void  cDraw::Draw_Box(int x, int y, int w, int h, D3DCOLOR color, LPDIRECT3DDEVICE9 mDevice)
{
	struct Vertex
	{
		float x, y, z, ht;
		DWORD Color;
	}
	V[4] = { { x, y + h, 0.0f, 0.0f, color }, { x, y, 0.0f, 0.0f, color }, { x + w, y + h, 0.0f, 0.0f, color }, { x + w, y, 0.0f, 0.0f, color } };
	mDevice->SetTexture(0, NULL);
	mDevice->SetPixelShader(0);
	mDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
	mDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	mDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	mDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	mDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	mDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, V, sizeof(Vertex));
	return;
}
/* Обводка */
void  cDraw::DrawBorder(int x, int y, int w, int h, D3DCOLOR Color,IDirect3DDevice9* mDevice)
{
	DrawBox(x, y, 2, h, Color, mDevice);
	DrawBox(x, y + h, w, 2, Color, mDevice);
	DrawBox(x, y, w, 2, Color, mDevice);
	DrawBox(x + w, y, 2, h + 2, Color, mDevice);
}
void  cDraw::Draw_Border(int x, int y, int w, int h, int s, D3DCOLOR Color, IDirect3DDevice9* mDevice)
{
	Draw_Box(x, y, s, h, Color, mDevice);
	Draw_Box(x, y + h, w, s, Color, mDevice);
	Draw_Box(x, y, w, s, Color, mDevice);
	Draw_Box(x + w, y, s, h + s, Color, mDevice);
}
void cDraw::String(int x, int y, DWORD Color, DWORD Style, const char *Format, ...)
{
	RECT rect;
	SetRect(&rect, x, y, x, y);
	char Buffer[1024] = { '\0' };
	va_list va_alist;
	va_start(va_alist, Format);
	vsprintf_s(Buffer, Format, va_alist);
	va_end(va_alist);
	pFont->DrawTextA(NULL, Buffer, -1, &rect, Style, Color);

	return;
}
/* Определение позиции мыши */
BOOL  cDraw::IsInBox(int x,int y,int w,int h)
{
	POINT MousePosition; 
	GetCursorPos(&MousePosition); 
	ScreenToClient(GetForegroundWindow(),&MousePosition);
	return(MousePosition.x >= x && MousePosition.x <= x + w && MousePosition.y >= y && MousePosition.y <= y + h);
}
void  cDraw::Line(float x, float y, float x2, float y2, float width, DWORD color)
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
/* Текст */
void  cDraw::Draw_Text(int x, int y, DWORD Color, const char *Format, DWORD Style)
{
	RECT rect;
	SetRect(&rect, x, y, x, y);
	char Buffer[1024] = { '\0' };
	va_list va_alist;
	va_start(va_alist, Format);
	vsprintf_s(Buffer, Format, va_alist);
	va_end(va_alist);
	pFont->DrawTextA(NULL, Buffer, -1, &rect, Style, Color);
	return;
}

/* Кнопка активации меню */
void  cDraw::KeyMenu(DWORD KEY,LPDIRECT3DDEVICE9  pDevice)
{
	if( pFont == NULL )
		pFont->OnLostDevice();
	else
	{
		if(GetAsyncKeyState(KEY)&1)Show=!Show;
		if(Show)SHOW_MENU(pDevice);
	}
}
/* Строим наше меню */
void cDraw::Studio_Menu(int x, int y, LPSTR text, LPDIRECT3DDEVICE9  pDevice)
{
	DrawBox(x, y, 400, 229, DARK3, pDevice);//Основной бокс на котором строится все меню
	Draw_Text(x + 10, x + 7, AliceBlue, text, L_Text);//Заголовок меню находящийся на его шапке

	Draw_Border(x, y, 400, 28, 2, ForestGreen, pDevice);//обводка шапки меню
	Draw_Border(x, y + 28, 400, 199, 2, ForestGreen, pDevice);//обводка пространства под функции, чекбоксы и тп.
	Draw_Border(x, y + 28, 130, 199, 2, ForestGreen, pDevice);//обводка пространства под разделы меню
}
void  cDraw::Engine_Button(int x, int y, int &Var, LPSTR text, IDirect3DDevice9* pDevice)
{
	if (IsInBox(x, y, 130, 25))
	{
		DrawBox(x + 3, y + 3, 120, 21, ForestGreen, pDevice);
		if (State_Key(VK_LBUTTON, 1000))
		{
			Varm.Menu0 = Varm.Menu1 = Varm.Menu2 = Varm.Menu3 = Varm.Menu4 = Varm.cvet = 0;
			Var = !Var;
		}
	}

	if (Var)
		DrawBox(x + 3, y + 3, 120, 21, ForestGreen, pDevice);

	Draw_Border(x, y, 124, 25, 2, ForestGreen, pDevice);
	Draw_Text(x + 64, y + 5, AliceBlue, text, C_Text);
}
void cDraw::Engine_CheckBox(int x, int y, int &Var, LPSTR text, IDirect3DDevice9* pDevice)
{
	Draw_Text(x + 135, y + 2, AliceBlue, text, L_Text);
	Draw_Border(x + 374, y + 2, 18, 15, 2, ForestGreen, pDevice);

	if (IsInBox(x + 128, y, 266, 20))
		Draw_Border(x + 130, y, 265, 20, 1, ForestGreen, pDevice);

	if (IsInBox(x + 374, y + 2, 18, 15))
	if (State_Key(VK_LBUTTON, 1000))
		Var = !Var;

	if (Var)
		DrawBox(x + 377, y + 5, 14, 11, ForestGreen, pDevice);
}
void cDraw::Engine_Scroll(int x, int y, int  &studio, char **typ, int max, LPSTR text, IDirect3DDevice9* pDevice)
{
	if (IsInBox(x + 128, y, 266, 20))
		Draw_Border(x + 130, y, 265, 20, 1, ForestGreen, pDevice);

	Draw_Border(x + 303, y + 2, 18, 15, 2, ForestGreen, pDevice);
	Draw_Box(x + 306, y + 5, 14, 11, ForestGreen, pDevice);
	Draw_Text(x + 314, y + 3, AliceBlue, "<", C_Text);

	Draw_Border(x + 374, y + 2, 18, 15, 2, ForestGreen, pDevice);
	Draw_Box(x + 377, y + 5, 14, 11, ForestGreen, pDevice);
	Draw_Text(x + 385, y + 3, AliceBlue, ">", C_Text);

	if (IsInBox(x + 374, y + 2, 18, 15) && (State_Key(VK_LBUTTON, 1000)))
	{
		if (studio >= 0 && studio<max)
		{
			studio++;
		}
	}

	if (IsInBox(x + 306, y + 2, 18, 15) && (State_Key(VK_LBUTTON, 1000)))
	{
		if (studio != 0)
		{
			studio--;
		}
	}
	Draw_Text(x + 350, y + 3, AliceBlue, typ[studio], C_Text);
	Draw_Text(x + 135, y + 2, AliceBlue, text, L_Text);
}
void  cDraw::Box(int x, int y, int w, int h, D3DCOLOR Color, LPDIRECT3DDEVICE9 pDevice)
{
	D3DRECT rec;
	rec.x1 = x;
	rec.x2 = x + w;
	rec.y1 = y;
	rec.y2 = y + h;
	pDevice->Clear(1, &rec, D3DCLEAR_TARGET, Color, 0, 0);
	return;
}
void  cDraw::Border(int x, int y, int w, int h, int s, DWORD color, LPDIRECT3DDEVICE9 pDevice)
{
	Box(x, y, w, s, color, pDevice);
	Box(x, y, s, h, color, pDevice);
	Box(x, y + h - s, w, s, color, pDevice);
	Box(x + w - s, y, s, h, color, pDevice);
}

BOOL  cDraw::State_Key(int Key, DWORD dwTimeOut)
{
	if (HIWORD(GetKeyState(Key)))
	{
		if (!kPressingKey[Key].bPressed || (kPressingKey[Key].dwStartTime && (kPressingKey[Key].dwStartTime + dwTimeOut) <= GetTickCount()))
		{
			kPressingKey[Key].bPressed = TRUE;
			if (dwTimeOut > NULL)kPressingKey[Key].dwStartTime = GetTickCount();
			return TRUE;
		}
	}
	else
		kPressingKey[Key].bPressed = FALSE;
	return FALSE;
}


/* Настройка цвета */
void  cDraw::M1Chams(int x, int y, char *Text, int &Var, DWORD CoLoR1, DWORD CoLoR2, DWORD CoLoR3, DWORD CoLoR4, DWORD CoLoR5, DWORD CoLoR6, DWORD CoLoR7, DWORD CoLoR8, DWORD CoLoR9, DWORD CoLoR10, IDirect3DDevice9* mDevice)
{
	DWORD CoL;
	DWORD R_COL = WHITE;
	DWORD Color = WHITE;
	if (IsInBox(x + 374, y + 2, 18, 15))
	{
		R_COL = ForestGreen;
		Color = ForestGreen;
		if (State_Key(VK_LBUTTON, 1000))
		{
			if (Var >= 0){ Var++; }
		}
		if (State_Key(VK_LBUTTON, 1000))
		{
			if (Var != 0) { Var--; }
		}
	}
	switch (Var)
	{
	case 1: CoL = CoLoR1;      break;
	case 2: CoL = CoLoR2;      break;
	case 3: CoL = CoLoR3;      break;
	case 4: CoL = CoLoR4;      break;
	case 5: CoL = CoLoR5;      break;
	case 6: CoL = CoLoR6;      break;
	case 7: CoL = CoLoR7;      break;
	case 8: CoL = CoLoR8;      break;
	case 9: CoL = CoLoR9;      break;
	case 10: CoL = CoLoR10;      break;
	case 11:                Var = 0;    break;
	}
	if (Var>0)
	{
		DrawBox(x + 377, y + 5, 14, 11, CoL, mDevice);
		Color = ForestGreen;
	}
	
	DrawBorder(x + 374, y + 2, 18, 15, ForestGreen, mDevice);
	Draw_Text(x + 135, y + 2, AliceBlue, Text, L_Text);
}

