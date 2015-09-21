int X,Y;
void ChangeCoordFunc(int &X,int &Y,int w)
{
			GetCursorPos(&mpos);
			ScreenToClient(GetForegroundWindow(), &mpos);
			X = (((X <= mpos.x) && (X >= mpos.x)) || ((X >= mpos.x) && (X <= mpos.x))) ? (X = mpos.x) : (X += ((mpos.x - X)));
			Y = (((Y <= mpos.y ) && (Y >= mpos.y)) || ((Y >= mpos.y) && (Y <= mpos.y))) ? (Y = mpos.y) : (Y += ((mpos.y - Y)));
}

BOOL  State_Key(int Key, DWORD dwTimeOut)
{
	if (HIWORD(GetKeyState(Key)))
	{
		if (!kPressingKeys[Key].bPressed || (kPressingKeys[Key].dwStartTime && (kPressingKeys[Key].dwStartTime + dwTimeOut) <= GetTickCount()))
		{
			kPressingKeys[Key].bPressed = TRUE;
			if (dwTimeOut > NULL)
				kPressingKeys[Key].dwStartTime = GetTickCount();
			return TRUE;
		}
	}
	else
		kPressingKeys[Key].bPressed = FALSE;
	return FALSE;
}

void DrawMenu(int x,int y,int w,int h,char*MenuTitle,LPDIRECT3DDEVICE9 pDevice)
{
	DrawGrad(X+x, Y+y+10, w, h, WHITE, DarkWhite, pDevice);
	DrawGrad(X+x, Y+y, w, 20, DarkGrey, DarkGrey2, pDevice);
	Border(X+x, Y+y, w, h+10, 1, DarkGrey2, pDevice);
	Text(MenuTitle, X+x + 5, Y+y + 2, DarkWhite, LText);
}

char*Titled;
bool Nope;
void AddFolder_Button(int x, int y, char*Title,int w, bool &Var, LPDIRECT3DDEVICE9 pDevice)
{
	D3DCOLOR BoxCol = D3DCOLOR_ARGB(0, 0, 0, 0), OneColor = D3DCOLOR_ARGB(255, 37, 37, 37), TwoColor = D3DCOLOR_ARGB(255, 15, 15, 15);
	if (IsInBox(x, y, 140, 20))
	{
		BoxCol = D3DCOLOR_ARGB(255, 44, 44, 44);
		if (State_Key(VK_LBUTTON, 300))
		{
			//	Aim = Player = Nope = false;
			Var = !Var;
		}
	}
	Border(x, y, w, 20, 1, BLACK, pDevice);
	Box(x, y, w, 20, BoxCol, pDevice);
	Text(Title, x + 5, y + 2, DarkWhite, LText);
}
bool forum, sf, lf;
void ActiveWindow(LPSTR Acitve)
{
	if (Aim == false && Player == false){ "Статус выбранного окна : None"; }
	if (Aim == true && Player == true || Player == true){ Acitve = "Статус выбранного окна : MEM Folder "; }
	else if(Aim == true){ Acitve = "Статус выбранного окна : Aim Folder "; }
	else Acitve = "Статус выбранного окна : None";
	Text(Acitve, 10, 10, DarkWhite, LText);
}
struct NameOfCombo{ LPSTR Title1; }NOC;
void TitleOnCombobox()
{
	if (Choose)
	{
		if (Aim == false && Player == false || Nope == false){ NOC.Title1 = "Choose Folder"; }
		if (Aim == true && Player == true || Player == true   ){ NOC.Title1 = "ESP Folder"; }
		else  if (Aim == true && Player == true || Aim == true ){ NOC.Title1 = "Aim Folder"; }
		if (Nope){ Aim = 0; Player = 0; Nope = 0;  NOC.Title1 = "Choose Folder"; }
	}
	else if (Aim == true && Player == true || Player == true ){ NOC.Title1 = "ESP Folder"; }
	else  if (Aim == true && Player == true || Aim == true ){ NOC.Title1 = "Aim Folder"; }
	else if (Aim == true && Player == true || Aim == true || Nope == false){ NOC.Title1 = "Choose Folder"; }
	 
}
void  ButtonText(LPSTR text, int x, int y, DWORD color, DWORD ST)
{
	RECT rect, rect2;
	SetRect(&rect, x, y, x, y);
	SetRect(&rect2, x - 0.1, y + 0.2, x - 0.1, y + 0.);
	pFont->DrawTextA(NULL, text, -1, &rect2, ST, 0x00000000);
	pFont->DrawTextA(NULL, text, -1, &rect, ST, color);
}
void ButtonBorder(int x, int y, int w, int h, int s, D3DCOLOR Color, LPDIRECT3DDEVICE9 pD3D9)
{
	Box(x - s, y, s, h, Color, pD3D9);
	Box(x - s, y + h, w + s * 2, s, Color, pD3D9);
	Box(x - s, y - s, w + s * 2, s, Color, pD3D9);
	Box(x + w, y, s, h + s, Color, pD3D9);
}
void FolderButton(LPSTR ComboTitle,int x, int y, int num,bool &Var,int w, LPDIRECT3DDEVICE9 pDevice)
{
	D3DCOLOR BoxCol = D3DCOLOR_ARGB(0, 0, 0, 0) , 
		OneColor = D3DCOLOR_ARGB(255, 37, 37, 37), 
		TwoColor = D3DCOLOR_ARGB(255, 15, 15, 15);
	int h=20;
	TitleOnCombobox();
	ActiveWindow(0);
	if (IsInBox(x, y, 140, 20))
	{
		BoxCol= D3DCOLOR_ARGB(255, 44, 44, 44);
		if (State_Key(VK_LBUTTON, 300))
		{			
			Var = !Var;
		}
	}
	if (Var == true){ h = 21 * num + 20;  }
	DrawGrad(x, y, w, h, OneColor, TwoColor, pDevice);
	Border(x, y, w,h, 1, BLACK, pDevice);
	Box(x, y, w, 20, BoxCol, pDevice);
	Text(ComboTitle, x + 5, y + 2, DarkWhite, LText);
}



LPDIRECT3DTEXTURE9 Logo;
LPD3DXSPRITE sLogo;


void Pircture(int x, int y, LPDIRECT3DDEVICE9 pDevice)
{
	D3DXVECTOR3 pHeaderP;
	pHeaderP.x = x; pHeaderP.y = y + 10;

	if (Logo == NULL)D3DXCreateTextureFromFileInMemoryEx(pDevice, &Logotype, sizeof(Logotype), 150, 200, D3DX_DEFAULT,
		0, D3DFMT_UNKNOWN
		, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL,
		&Logo);
	if (sLogo == NULL)D3DXCreateSprite(pDevice, &sLogo);
	sLogo->Begin(D3DXSPRITE_ALPHABLEND);
	sLogo->Draw(Logo, NULL, NULL, &pHeaderP, 0xFFFFFFFF);
	sLogo->End();
}



LPDIRECT3DTEXTURE9 txHeader;
LPD3DXSPRITE spHeader;


#define Select_Col_Box 0xFF282828  //Box
#define Select_Col_Bord 0xFF00ff00  //Обводка
#define Select_Col_Tex 0xFFBBBABA  //Текст


struct MyColor
{
	int R, G, B;
	MyColor(int R, int G, int B)
	{
		this->R = R;
		this->G = G;
		this->B = B;
	}

};

bool CCESP;
MyColor  Select_Color(int x, int y, int &Var, LPDIRECT3DDEVICE9 pDevice, int &R, int &G, int &B, bool &ResetColor)
{
	int xred;
	int xgreen;
	int xblue;
	DWORD  retColor;
	D3DCOLOR gol_n = Select_Col_Tex;
	char* _OnOFF[] = { "OFF", "ON" };
	POINT pos;
	GetCursorPos(&pos);
	D3DXVECTOR3 pHeader;
	pHeader.x = x; pHeader.y = y + 20;


	if (IsInBox(x + 10, y + 2, 30, 20))
	{
		gol_n = Select_Col_Bord;
		if (lm)
		{
			Var = !Var;
		}
	}
	if (CCESP){
		/*
		if (txHeader == NULL)D3DXCreateTextureFromFileInMemoryEx(pDevice, &Logotype123, sizeof(Logotype123), 150, 150, D3DX_DEFAULT,
		0, D3DFMT_UNKNOWN
		, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL,
		&txHeader);
		*/
	if (spHeader == NULL)D3DXCreateSprite(pDevice, &spHeader);
	spHeader->Begin(D3DXSPRITE_ALPHABLEND);
	spHeader->Draw(txHeader, NULL, NULL, &pHeader, 0xFFFFFFFF);
	spHeader->End();
	}
	if (IsInBox(x, y, 150, 170))
	{
		if (GetAsyncKeyState(VK_LBUTTON)<0)
		{
			HDC hScreenDC = GetDC(NULL);
			COLORREF ColorsS = GetPixel(hScreenDC, pos.x, pos.y);
			ReleaseDC(NULL, hScreenDC);
			xred = GetRValue(ColorsS);
			xgreen = GetGValue(ColorsS);
			xblue = GetBValue(ColorsS);
			R = xred;
			G = xgreen;
			B = xblue;

		}
	}
	retColor = D3DCOLOR_XRGB(R, G, B);
	if (CCESP)
	{
		Box(x + 150, y + 20, 15, 150, retColor, pDevice);
		Border(x, y + 20, 150, 150, 2, BLACK, pDevice);
		Border(x + 150, y + 20, 15, 150, 2, BLACK, pDevice);
	}

	MyColor ret = MyColor(R, G, B);
	return ret;
}
#define  BLUEMAZAY        D3DCOLOR_ARGB(255, 11,  46,  118)
#define	 ORANGE	          D3DCOLOR_ARGB(255,255,125,0)
#define	 YELLOW           D3DCOLOR_ARGB(255,255,255,0)
#define	 GREY             D3DCOLOR_ARGB(255,128,128,128)
#define	 PURPLE           D3DCOLOR_ARGB(255,125,0,255)
#define	 WHITE		      D3DCOLOR_ARGB(255, 255, 255, 255)
#define	 RED			  D3DCOLOR_ARGB(255, 255, 000, 000)
#define	 GREEN		      D3DCOLOR_ARGB(255, 000, 255, 000)
#define	 BLUE		  	  D3DCOLOR_ARGB(255, 000, 000, 255)
#define	 BLACK		      D3DCOLOR_ARGB(255, 000, 000, 000)
#define  DARK1            D3DCOLOR_ARGB(255, 10, 10, 10)
#define  DARK2            D3DCOLOR_ARGB(255, 15, 15, 15)
#define  DARK3            D3DCOLOR_ARGB(255, 20, 20, 20)
#define  DARK4            D3DCOLOR_ARGB(255, 25, 25, 25)
#define  DARK5            D3DCOLOR_ARGB(255, 30, 30, 30)
#define  DARK6            D3DCOLOR_ARGB(255, 35, 35, 35)
#define  DARK7            D3DCOLOR_ARGB(255, 40, 40, 40)
#define  DARK8            D3DCOLOR_ARGB(255, 45, 45, 45)
#define  DARK9            D3DCOLOR_ARGB(255, 50, 50, 50)
#define  DARK10           D3DCOLOR_ARGB(255, 60, 60, 60)
#define  DARK11           D3DCOLOR_ARGB(255, 65, 65, 65)
#define  DARK12           D3DCOLOR_ARGB(255, 70, 70, 70)
#define  DARK13           D3DCOLOR_ARGB(255, 75, 75, 75)
#define  DARK14           D3DCOLOR_ARGB(255, 80, 80, 80)
#define  DARK15           D3DCOLOR_ARGB(255, 85, 85, 85)
#define  DARK16           D3DCOLOR_ARGB(255, 90, 90, 90)
#define  DARK18           D3DCOLOR_ARGB(255, 180, 180, 180)
#define  DARK20           D3DCOLOR_ARGB(255, 150, 150, 150)
#define  WINDOWS          D3DCOLOR_ARGB(255, 176 ,  30 ,  58 )
#define  WINDOWS2         D3DCOLOR_ARGB(255, 176 ,  20 ,  48 )
void Check(int x, int y, char *BText, int &Var, LPDIRECT3DDEVICE9 pDevice)
{
	DWORD Col1, Col2, Col3;
	Col1 = DARK5;
	Col2 = DARK4;
	Col3 = DARK5;
	if (Var == 1)
	{
		Col1 = DARK14;
		Col2 = DARK4;
		Col3 = DARK5;

		Box(x + 3, y + 3, 7, 7, DARK5, pDevice);

	}
	if (IsInBox(x, y, 80, 14))
	{
		Col2 = DARK4;
		Col3 = DARK5;
		if (lm)
		{
			Var = !Var;
		}
	}
	ButtonBorder(x, y, 13, 13, 2, Col2, pDevice);
	ButtonText(BText, x + 25, y, DARK5, DT_LEFT | DT_NOCLIP);
}

