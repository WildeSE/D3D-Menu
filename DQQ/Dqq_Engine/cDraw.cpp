#include "cDraw.h"
#include "Structure.h"

cDraw::cDraw(void)
{
	Show = true;
}

void  cDraw::PostReset(IDirect3DDevice9* mDevice)
{
	m_pFont = new CD3DFont("System", 9, D3DFONT_BOLD);
	m_pFont->InitDeviceObjects(mDevice);
	m_pFont->RestoreDeviceObjects();	
}

void  cDraw::PreReset(void)
{
	m_pFont->InvalidateDeviceObjects();
	m_pFont->DeleteDeviceObjects();
	delete m_pFont;
	m_pFont = NULL;
}

void  cDraw::Draw_Text(int x,int y,DWORD color,LPSTR text,DWORD ST)
{
	m_pFont->DrawText(x, y, color, text, ST);
}

void cDraw::Draw_Box(int x, int y, int w, int h, D3DCOLOR Color, IDirect3DDevice9* mDevice)
{
	D3DRECT rec;
	rec.x1 = x;
	rec.x2 = x + w;
	rec.y1 = y;
	rec.y2 = y + h;
	mDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1); 
	mDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	mDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);   
	mDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,	D3DPT_TRIANGLESTRIP);
	mDevice->Clear(1, &rec, D3DCLEAR_TARGET, Color, 1, 1);
}

void  cDraw::DrawBox(int x, int y, int w, int h, D3DCOLOR Color, LPDIRECT3DDEVICE9 pD3D9)
{
	struct Vertex
	{
		float x, y, z, ht;
		DWORD Color;
	}
	
	V[4] = { { x, y + h, 0.0f, 0.0f, Color }, { x, y, 0.0f, 0.0f, Color }, { x + w, y + h, 0.0f, 0.0f, Color }, { x + w, y, 0.0f, 0.0f, Color } };
	
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

void cDraw::Draw_Border(int x, int y, int w, int h,int s, D3DCOLOR Color,IDirect3DDevice9* mDevice)
{
	Draw_Box(x,  y, s,  h, Color, mDevice);
	Draw_Box(x,y+h, w,  s, Color, mDevice);
	Draw_Box(x,  y, w,  s, Color, mDevice);
	Draw_Box(x+w,y, s,h+s, Color, mDevice);
}

BOOL cDraw::IsInBox(int x, int y, int w, int h)
{
	POINT MousePosition; 
	GetCursorPos(&MousePosition); 
	ScreenToClient(GetForegroundWindow(), &MousePosition);
	return(MousePosition.x >= x && MousePosition.x <= x + w && MousePosition.y >= y && MousePosition.y <= y + h);
}

void cDraw::Draw_Line(long Xa, long Ya, long Xb, long Yb, int Width, D3DCOLOR Color)
{	
	D3DXVECTOR2 vLine[ 2 ];
	pLine->SetAntialias( 0 );
	pLine->SetWidth(Width);
	pLine->Begin();
	vLine[ 0 ][ 0 ] = Xa;
	vLine[ 0 ][ 1 ] = Ya;
	vLine[ 1 ][ 0 ] = Xb;
	vLine[ 1 ][ 1 ] = Yb;
	pLine->Draw(vLine, 2, Color);
	pLine->End();
}

BOOL cDraw::State_Key(int Key, DWORD dwTimeOut)
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

void  cDraw::Initialize_Menu(DWORD KEY, IDirect3DDevice9* m_pD3Ddev)
{
	if(!Create)
	{
		D3DXCreateLine(m_pD3Ddev,&pLine);
		Create = true;
	}
	
	PostReset(m_pD3Ddev);
	
	if(!pLine )
		pLine->OnLostDevice();
	else
	{
		if(State_Key(KEY,3000))Show=!Show;
		if(Show)
			{
				SHOW_MENU(m_pD3Ddev);
		    }
		pLine->OnLostDevice();
		pLine->OnResetDevice();
	}
	PreReset();
}

void  cDraw::Draw_Gradient_Box(float x, float y, float width, float height, DWORD startCol, DWORD endCol, gr_orientation orientation, IDirect3DDevice9* mDevice)
{
	static struct D3DVERTEX
	{
		float x, y, z, rhw;
		DWORD color;
	}
	
	vertices[4] = {
		{0,0,0,1.0f,0},
		{0,0,0,1.0f,0},
		{0,0,0,1.0f,0},
		{0,0,0,1.0f,0}};

		vertices[0].x = x;
		vertices[0].y = y;
		vertices[0].color = startCol;

		vertices[1].x = x+width;
		vertices[1].y = y;
		vertices[1].color = orientation == horizontal ? endCol : startCol;

		vertices[2].x = x;
		vertices[2].y = y+height;
		vertices[2].color = orientation == horizontal ? startCol : endCol;

		vertices[3].x = x+width;
		vertices[3].y = y+height;
		vertices[3].color = endCol;

		mDevice->SetTexture(0, NULL);
		mDevice->SetPixelShader( 0 );
		mDevice->SetFVF(D3DFVF_XYZRHW|D3DFVF_DIFFUSE);
		mDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,true);
		mDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);
		mDevice->SetRenderState(D3DRS_ZENABLE , FALSE);
		mDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
		mDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,2,vertices,sizeof(D3DVERTEX));
}

//Треугольник 
void  cDraw::Draw_Triangle(int x, int y,D3DCOLOR Color, IDirect3DDevice9* mDevice)
{
	struct D3DVERTEX
	{
		float x, y, z, rhw;
		DWORD color;
	};
        int z = 10;
	D3DVERTEX   vertices[3];
	vertices[0].x = x;
	vertices[0].y = y;
	vertices[0].z = z;
	vertices[0].rhw = 1.0f;
	vertices[0].color = Color;

	vertices[1].x = x+10;
	vertices[1].y = y+12;
	vertices[1].z = z;
	vertices[1].rhw = 1.0f;
	vertices[1].color = Color;

	vertices[2].x = x;
	vertices[2].y = y+25;
	vertices[2].z = z;
	vertices[2].rhw = 1.0f;
	vertices[2].color = Color;

	
	mDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 3, vertices, sizeof(D3DVERTEX));
}
#define DT_SHADOW           0x0040
void cDraw::Draw_Menu(int x, int y, IDirect3DDevice9* pDevice)
{
	int x_pos = 15, y_pos = 15;

	Draw_Box(x_pos, y_pos, 700, 300, MyFon, pDevice);//fon
	Draw_Border(x_pos-4, y_pos-4, 700, 300, 4, Red, pDevice);//border red
	Draw_Border(x_pos, y_pos, 695, 295, 1, Black, pDevice);//border black(red)
	Draw_Border(x_pos+3, y_pos+3, 686, 286, 4, RedTwo, pDevice);

	//border
	Draw_Border(x_pos+7, y_pos+7, 196, 281, 1, Black, pDevice);
	Draw_Border(x_pos+7+204, y_pos+7, 477, 281, 1, Black, pDevice);

	//Перегародки для навигации.
	Draw_Box(x_pos+3, y_pos+28, 201, 4, RedTwo, pDevice);
	Draw_Box(x_pos+3, y_pos+28+25, 201, 4, RedTwo, pDevice);
	Draw_Box(x_pos+3, y_pos+28+25*2, 201, 4, RedTwo, pDevice);
	Draw_Box(x_pos+3, y_pos+28+25*3, 201, 4, RedTwo, pDevice);
	Draw_Box(x_pos+3, y_pos+28+25*4, 201, 4, RedTwo, pDevice);

	//Копирайт.
	Draw_Text(x_pos + 58, y_pos + 248, Grey, "D", L_Text|DT_SHADOW);
	Draw_Text(x_pos + 68, y_pos + 248, ButtonRedOne, "qq & iDReeM", L_Text|DT_SHADOW);
	Draw_Text(x_pos + 55, y_pos + 265, Grey, "ROUGH", L_Text|DT_SHADOW);
	Draw_Text(x_pos + 105, y_pos + 265, ButtonRedOne, "ENGINE", L_Text|DT_SHADOW);
}

void  cDraw::Draw_Button(int x, int y, bool &var, LPSTR text, IDirect3DDevice9* mDevice)
{
	D3DCOLOR LightsOne = ButtonRedOne, LightsTwo = ButtonRedTwo;
	if(IsInBox(x + 7, y + 7, 196, 20))
	{
		LightsOne = Orange, LightsTwo = Orange;
		if(State_Key(VK_LBUTTON, 1000))
		{
			Var.Player = Var.Weapon = Var.Cupons = Var.Info = Var.Visual = 0;
			var = !var;
		}
	}

	if(var)
	{
		LightsOne = ButtonRedActiv, LightsTwo = ButtonRedActiv;
		Draw_Triangle(x + 210, y + 5, Black, mDevice);
		Draw_Triangle(x + 209, y + 5, RedTwo, mDevice);
	}

	Draw_Box(x + 7, y + 7, 196, 11, ButtonRedOne, mDevice);
	Draw_Box(x + 7, y + 18, 196, 9, ButtonRedTwo, mDevice);

	Draw_Border(x + 7, y + 7, 196, 20, 1, Black, mDevice);
	Draw_Box(x + 14, y + 7, 1, 20, Black, mDevice);
	Draw_Box(x + 196, y + 7, 1, 20, Black, mDevice);
	
	//Индикаторы
	Draw_Box(x + 8, y + 8, 6, 11, LightsOne, mDevice);
	Draw_Box(x + 8, y + 18, 6, 9, LightsTwo, mDevice);
	Draw_Box(x + 197, y + 8, 6, 11, LightsOne, mDevice);
	Draw_Box(x + 197, y + 18, 6, 9, LightsTwo, mDevice);

	Draw_Text(x + 105, y + 9, ButtonText, text, C_Text|DT_SHADOW);
}

void cDraw::Draw_Button_Check(int x, int y, bool &var, LPSTR text, IDirect3DDevice9* mDevice)
{
	D3DCOLOR TextActiv = Grey, ActivTR = Red, ActivTL = Red;
	LPSTR TextA = "OFF";

	if(IsInBox(x + 628, y + 11, 10, 11))
	{
		ActivTL = Orange;
		if(State_Key(VK_LBUTTON,1000))
		{
			var = 0;
		}
	}
	
	if(IsInBox(x + 670, y + 11, 10, 11))
	{
		ActivTR = Orange;
		if(State_Key(VK_LBUTTON,1000))
			var = 1;
	}

	if(var)
	{
		TextActiv = OrangeTwo;
		TextA = "ON";
	}

	Draw_Text(x + 630, y + 9, ActivTL, "<", L_Text|DT_SHADOW);
	Draw_Text(x + 672, y + 9, ActivTR, ">", L_Text|DT_SHADOW);

	Draw_Border(x + 211, y + 7, 477, 20, 1, Black, mDevice);
	Draw_Text(x + 220, y + 9, Grey, text, L_Text|DT_SHADOW);
	Draw_Text(x + 655, y + 9, TextActiv, TextA, C_Text|DT_SHADOW);
}

void cDraw::Draw_Button_Scroll(int x, int y, int &var, char **typ, int max, LPSTR text, IDirect3DDevice9* mDevice)
{
	D3DCOLOR TextActiv = Grey, ActivTR = Red, ActivTL = Red;

	if(IsInBox(x + 628, y + 11, 10, 11))
	{
		ActivTL = Orange;
		if(State_Key(VK_LBUTTON,1000))
		{
			if(var!=0)
			{
				var--;
			}
		}
	}
	
	if(IsInBox(x + 670, y + 11, 10, 11))
	{
		ActivTR = Orange;
		if(State_Key(VK_LBUTTON,1000))
		{
			if(var>=0 && var<max)
			{
				var++;
			}
		}
	}

	if(var != 0)
	{
		TextActiv = OrangeTwo;
	}

	Draw_Text(x + 630, y + 9, ActivTL, "<", L_Text|DT_SHADOW);
	Draw_Text(x + 672, y + 9, ActivTR, ">", L_Text|DT_SHADOW);

	Draw_Border(x + 211, y + 7, 477, 20, 1, Black, mDevice);
	Draw_Text(x + 220, y + 9, Grey, text, L_Text|DT_SHADOW);
	Draw_Text(x + 655, y + 9, TextActiv, typ[var], C_Text|DT_SHADOW);
}
void cDraw::Draw_Space( int y, IDirect3DDevice9* mDevice)
{
	Draw_Box(228, y+20, 475, 3, OrangeThree, mDevice);
	Draw_Border(228, y+20, 475, 3, 1, OrangeFour, mDevice);
}


