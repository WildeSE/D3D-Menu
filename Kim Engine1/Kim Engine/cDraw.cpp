#include "cDraw.h"
#include "Variables.h"

cDraw::cDraw(void)
{
	Show = true;
}

void _fastcall  cDraw::InitFont(CHAR* szFontFamily,int W,DWORD Stile,IDirect3DDevice9* mDevice)
{
	D3DXCreateFont(mDevice, W, 0, FW_BLACK, 0, 0, DEFAULT_CHARSET, OUT_TT_PRECIS, DEFAULT_QUALITY,  DEFAULT_PITCH | FF_DONTCARE, szFontFamily, &pFont);
}

void  cDraw::Engine_Text(int x,int y,DWORD color,LPSTR text,DWORD ST)
{
	RECT rect, rect2;
	SetRect( &rect, x, y, x, y );
	SetRect( &rect2, x - 0.1, y + 0.2, x - 0.1, y + 0. );
	pFont->DrawTextA(NULL,text,-1,&rect2, ST, 0x00000000 );
	pFont->DrawTextA(NULL,text,-1,&rect,  ST, color );
}
void _fastcall  cDraw::Engine_Box(int x, int y, int w, int h,   D3DCOLOR Color,IDirect3DDevice9* mDevice)
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


void _fastcall  cDraw::Engine_Border(int x, int y, int w, int h,int s, D3DCOLOR Color,IDirect3DDevice9* mDevice)
{
	Engine_Box(x,  y, s,  h,Color,mDevice);
	Engine_Box(x,y+h, w,  s,Color,mDevice);
	Engine_Box(x,  y, w,  s,Color,mDevice);
	Engine_Box(x+w,y, s,h+s,Color,mDevice);
}

BOOL  cDraw::IsInBox(int x,int y,int w,int h)
{
	POINT MousePosition; 
	GetCursorPos(&MousePosition); 
	ScreenToClient(GetForegroundWindow(),&MousePosition);
	return(MousePosition.x >= x && MousePosition.x <= x + w && MousePosition.y >= y && MousePosition.y <= y + h);
}

void _fastcall  cDraw::Engine_Line(long Xa,long Ya,long Xb,long Yb,int Width,D3DCOLOR Color)
{	
	D3DXVECTOR2 vLine[ 2 ];
	pLine->SetAntialias( 0 );
	pLine->SetWidth(Width);
	pLine->Begin();
	vLine[ 0 ][ 0 ] = Xa;
	vLine[ 0 ][ 1 ] = Ya;
	vLine[ 1 ][ 0 ] = Xb;
	vLine[ 1 ][ 1 ] = Yb;
	pLine->Draw( vLine, 2, Color );
	pLine->End();
}

BOOL  cDraw::State_Key(int Key,DWORD dwTimeOut)
{
	if(HIWORD(GetKeyState(Key)))
	{
		if(!kPressingKeys[Key].bPressed || (kPressingKeys[Key].dwStartTime && (kPressingKeys[Key].dwStartTime + dwTimeOut) <= GetTickCount()))
		{
			kPressingKeys[Key].bPressed = TRUE;
			if( dwTimeOut > NULL )
				kPressingKeys[Key].dwStartTime = GetTickCount();
			return TRUE;
		}
	}
	else
		kPressingKeys[Key].bPressed = FALSE;
	return FALSE;
}

void _fastcall  cDraw::KeyMenu(DWORD KEY,LPDIRECT3DDEVICE9  pDevice)
{
	if( pFont == NULL )
		pFont->OnLostDevice();
	else
	{
		if(GetAsyncKeyState(KEY)&1)Show=!Show;
		if(Show)SHOW_MENU(pDevice);
	}
}

void _fastcall cDraw::Engine_Menu(int x, int y, LPDIRECT3DDEVICE9  pDevice)
{

}


void _fastcall cDraw::String(int x, int y, DWORD Color, DWORD Style, const char *Format, ...)
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
VOID cDraw::Xhair(int Size,int Width,D3DCOLOR Color,IDirect3DDevice9* pDevice )
{
	D3DVIEWPORT9 cViewport;
	pDevice->GetViewport(&cViewport); 
    int x = cViewport.Width / 2; 
    int y = cViewport.Height / 2;


	D3DRECT rec = { x - Size, y, x +Size, y + Width};
	D3DRECT rec2 = { x, y - Size, x + Width, y + Size}; 
	pDevice->Clear(1,&rec,D3DCLEAR_TARGET,Color,0,0);
	pDevice->Clear(1,&rec2,D3DCLEAR_TARGET,Color,0,0);
}


int cDraw::ViewportInfo(int iCode, LPDIRECT3DDEVICE9 pDevice)
{
	D3DVIEWPORT9 pViewport;
	pDevice->GetViewport(&pViewport);
	int iResult = 0;

	if ( iCode == 0 )
		iResult = (int)pViewport.X;
	else if ( iCode == 1 )
		iResult = (int)pViewport.Y;
	else if ( iCode == 2 )
		iResult = (int)pViewport.Width;
	else if ( iCode == 3 )
		iResult = (int)pViewport.Height;
	else if ( iCode == 4 )
		iResult = (int)pViewport.MinZ;
	else if ( iCode == 5 )
		iResult = (int)pViewport.MaxZ;

	return iResult;
}

void __fastcall cDraw::Circle(int X, int Y, int radius, int numSides, DWORD Color)
{
		D3DXVECTOR2 Line[128];
		float Step = (float)(D3DX_PI * 2.0 / numSides);
		int Count = 0;
		for (float a = 0; a < D3DX_PI*2.0; a += Step)//2.0 = 0
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

char* cDraw::FPS(void)
{
	static int	 FPScounter = 0;
	static float FPSfLastTickCount = 0.0f;
	static float FPSfCurrentTickCount;
	static char  cfps[6] = "";
	
	FPSfCurrentTickCount = clock() * 0.001f;
	FPScounter++;

	if((FPSfCurrentTickCount - FPSfLastTickCount) > 1.0f)
	{
		FPSfLastTickCount = FPSfCurrentTickCount;
		sprintf_s(cfps," %d",FPScounter);
		FPScounter = 0;
	}
return cfps;
}
