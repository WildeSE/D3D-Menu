#include "cDraw.h"
#include "Variables.h"
cGPEngine GPEngine;
cDraw::cDraw(void)
{
	Show = true;
	GPEngine.Menu6 = true;
}

void  cDraw::InitFont(CHAR* szFontFamily,int W,DWORD Stile,IDirect3DDevice9* mDevice)
{
	D3DXCreateFont(mDevice, W, 0, Stile, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, FF_MODERN, szFontFamily, &pFont);
}

void  cDraw::Engine_Text(int x,int y,DWORD color,LPSTR text,DWORD ST)
{
	RECT rect, rect2;
	SetRect( &rect, x, y, x, y );
	pFont->DrawTextA(NULL,text,-1,&rect,  ST, color );
	SetRect( &rect, x, y, x, y );
}
void  cDraw::Engine_Box( int x, int y, int w, int h, D3DCOLOR Color, IDirect3DDevice9* mDevice)
{
	struct Vertex 
	{
		float x,y,z,ht;
		DWORD Color;
	}
	V[4] ={{x,y+h, 0.0f, 0.0f, Color}, {x,y, 0.0f, 0.0f, Color},{x+w,y+h, 0.0f, 0.0f, Color},{x+w,y, 0.0f, 0.0f, Color}};
    mDevice->SetTexture(0, NULL);
    mDevice->SetPixelShader( 0 );
    mDevice->SetFVF(D3DFVF_XYZRHW|D3DFVF_DIFFUSE);
    mDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,true);
    mDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);
    mDevice->SetRenderState(D3DRS_ZENABLE , FALSE);
    mDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
    mDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,2,V,sizeof(Vertex));
    return;
}

void  cDraw::Engine_Border(int x, int y, int w, int h,int s, D3DCOLOR Color,IDirect3DDevice9* mDevice)
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
void  cDraw::Engine_Line(long Xa,long Ya,long Xb,long Yb,int Width,D3DCOLOR Color)
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

#define TheColorit        D3DCOLOR_ARGB(255,255,255,255)

void cDraw::Engine_FunctionFloder(int x, int y, int Elemenst_Mass, LPDIRECT3DDEVICE9  pDevice)
{
	Engine_Box(x+150, y+25, 300, 30+22*Elemenst_Mass, Dark5, pDevice);
	Engine_Border(x+150, y+25, 300, 30+22*Elemenst_Mass, 1, Green, pDevice);
}

void cDraw::Engine_MenuTitle(int x, int y, LPSTR MenuText, LPDIRECT3DDEVICE9  pDevice)
{
	Engine_Box(x, y, 450, 25, Dark5, pDevice);
	Engine_Border(x, y, 450, 25, 1, Green, pDevice);

	Engine_Text(x+8, y+5, D3DCOLOR_ARGB(255, 255, 255, 255), MenuText, L_Text);//title
	Engine_Text(x+425, y+5,White,FPS(),L_Text);//fps
}

void cDraw::Engine_ButtonFloder(int x, int y, int Button_Mass, LPDIRECT3DDEVICE9  pDevice)
{
	Engine_Box(x, y+25, 150, 33+30*Button_Mass, Dark5, pDevice);
	Engine_Border(x, y+25, 150, 33+30*Button_Mass, 1, Green, pDevice);
}


void  cDraw::Engine_Button(int x, int y, bool &GPengine, LPSTR text, IDirect3DDevice9* pDevice)
{
	D3DCOLOR TextColor = Grey ,BoxColor = Dark5;

	if(IsInBox(x,y,130,25))
	{
		Engine_Box(x+3, y+3, 135, 19, Grey, pDevice);
		TextColor = White;
		if(State_Key(VK_LBUTTON,1000))
		{
			GPEngine.Menu1 = GPEngine.Menu2 = GPEngine.Menu3 = GPEngine.Menu4 = GPEngine.Menu5 = GPEngine.Menu6 = 0;
			GPengine = !GPengine;
		}
	}

	if(GPengine)
	{
		TextColor = White;//0xFF008B8B
		Engine_Box(x+3, y+3, 135, 19, 0xFF008B8B, pDevice);
	}

	Engine_Box(x, y, 140, 24, Dark5, pDevice);
	Engine_Border(x, y, 140, 24, 1, Green, pDevice);
	Engine_Text(x+70, y+4, TextColor, text, C_Text);
}
void  cDraw::Engine_DoubleCheck(int x, int y, bool &GPengine, LPSTR text, IDirect3DDevice9* pDevice)
{
	D3DCOLOR ColorButton = White, ColorBorder = Grey, ColorText=Grey;
	int Sx = 242;
	if(IsInBox(x,y,350,15))
	{
		ColorText = White,ColorBorder = White;
		Engine_Border(x-2,y-2,295,21,1,0xFF008B8B,pDevice);
		if(State_Key(VK_LBUTTON,1000))
		{
			GPengine =!GPengine;
		}
	}
	if(GPengine==0)
	{
		Engine_Box(x+Sx,y+4,22,10,Green,pDevice);
	}
	else
	{
		ColorText = ColorButton;
		Engine_Box(x+Sx+23,y+4,22,10,Green,pDevice);
	}

	Engine_Border(x+239,y+1,50,15,1,ColorBorder,pDevice);
	Engine_Text(x+4,y,ColorText,text,L_Text);
}

void  cDraw::Engine_CheckBox(int x, int y, bool &GPengine, LPSTR text, IDirect3DDevice9* pDevice)
{
	D3DCOLOR ColorBorder = Grey,ColorText = Grey;
	if(IsInBox(x,y,290,15))
	{
		ColorText,ColorBorder = White;
		Engine_Border(x-2,y-2,295,21,1,0xFF008B8B,pDevice);
		if(State_Key(VK_LBUTTON,1000))
		{
			GPengine = !GPengine;
		}
	}
	if(GPengine)
	{
		Engine_Box(x+272,y+4,15,10,Green,pDevice);
		ColorText = White;
	}
	Engine_Text(x+4,y,ColorText,text,L_Text);
	Engine_Border(x+269,y+1,20,15,1,ColorBorder,pDevice);
}
void cDraw::Engine_Scroll(int x,int y,int &GPengine,char **typ,int max, LPSTR text, IDirect3DDevice9* pDevice)
{
	D3DCOLOR  ColorBorder = Grey, ColorText=Grey;
	if(IsInBox(x,y,290,15))
	{
		Engine_Border(x-2,y-2,295,21,1,0xFF008B8B,pDevice);
		ColorText ,ColorBorder = White;
	}

	Engine_Border(x+220,y+1,20,15,1,ColorBorder,pDevice);
	Engine_Box(x+222,y+3,17,12,Green,pDevice);
	Engine_Text(x+230,y+1,White,"<",C_Text);

	Engine_Border(x+269,y+1,20,15,1,ColorBorder,pDevice);
	Engine_Box(x+271,y+3,17,12,Green,pDevice);
	Engine_Text(x+280,y+1,White,">",C_Text);

	Engine_Border(x+220,y+1,69,15,1,ColorBorder,pDevice);

	if(IsInBox(x+269,y+3,17,12) && (State_Key(VK_LBUTTON,1000)))
	{
		ColorText,ColorBorder = White;
		if(GPengine>=0 && GPengine<max)
		{
			GPengine++;
		}
	}
	
	if(IsInBox(x+222,y+3,17,12) && (State_Key(VK_LBUTTON,1000)))
	{
		if(GPengine!= 0)
		{
			GPengine--;
		}
	}

	if(GPengine != 0)
	{
		ColorText = White;
	}
	
	Engine_Text(x+255,y+2,ColorText,typ[GPengine],C_Text);
	Engine_Text(x+4,y,ColorText,text,L_Text);
}