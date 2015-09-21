
void Button( int x, int y,char *BText, int &Var, LPDIRECT3DDEVICE9 pDevice)
{
	DWORD Col1=EColOn;
	DWORD Col2=DARK18;
	if (IsInBox(x, y, 80, 20))
	{
		Col1=DARK10;

		if (Var == 0)
		{
		
		}
		if (lm)
		{
			if (Var == 1 && Var != 0){ Var = 0; }
			else if (Var == 0)
			{
				Fun.Haks = Fun.Player = Fun.esp =Fun.Test2= Fun.Test4 = Fun.Test5 = Fun.Test6 = Fun.Test7 = Fun.Test8= Fun.Test9 = Fun.Test10 = 0; 
				Var = 1;
			}
		}
	}
	if (Var == 1)
	{
		Col1=EColOn;
		Col2=DARK2;
		Box(x, y, 80, 20, EColOn, pDevice);
	}
	Box(x, y + 20, 80, 2, Col1, pDevice);
	Text(BText, x + 40, y + 3, Col2, DT_CENTER | DT_NOCLIP);
}

void Check( int x, int y,char *BText, int &Var, LPDIRECT3DDEVICE9 pDevice)
{
	DWORD Col1,Col2,Col3;
	Col1=DARK8;
	Col2=DARK8;
	Col3=DARK13;
	if (Var == 1)
	{
		Col1=DARK14;
		Col2=EColOn;
		Col3=EColOn;

	Box(x + 3, y + 3, 7, 7,EColOn , pDevice); 
	
	}
	if (IsInBox(x, y, 80, 14))
	{
		Col2=EColOn;
		Col3=EColOn;
		if (lm)
		{
			Var = !Var; 
		}
	}
	Border(x, y, 13, 13, 2, Col2, pDevice);
	Text(BText, x + 25, y, Col3, DT_LEFT | DT_NOCLIP);
}

void DoubleCheck( int x, int y,char *BText, int &Var, LPDIRECT3DDEVICE9 pDevice)
{
	DWORD Col1,Col2,Col3;
	Border(x, y, 40, 15, 2, DARK12, pDevice);
	if (IsInBox(x, y, 150, 12))
	{
		if (Var == 0)
		{
		}

		if (lm)
		{
			Var = !Var; 
		}
	}
	if (Var == 1)
	{ 

	}
	Box(x + 1, y + 1, 38, 13, DARK5, pDevice);
	if (Var > 0)
	{
	Box(x+29, y - 2, 13, 19, EColOn, pDevice);
	}
	else
	{
	Box(x - 2, y - 2, 13, 19, EColOn, pDevice);
	}

	Text(BText, x + 50, y + 1,DARK20, DT_LEFT | DT_NOCLIP);
}

void DoubleCheckColor(int x, int y,char *BText, int &Var,LPDIRECT3DDEVICE9 pDevice)
{
	Border(x, y, 40, 15, 2, DARK12, pDevice);
	D3DCOLOR cbutton2 = DARK10;
	if (IsInBox(x, y, 40, 13))
	{
		if (lm)
		{ 
			Var = !Var; 
			Fun.Color1 = Fun.Color2 = Fun.Color3 = Fun.Color4 = Fun.Color5 = Fun.Color6 = 0; Var = 1;
		}
	}
	Box(x + 1, y + 1, 38, 13, DARK10, pDevice);
	if (Var > 0)
	{
		Box(x + 29, y - 2, 13, 19, EColOn, pDevice);
		Border(x+29, y-2, 13, 19,1, BLACK, pDevice);

	}
	else
	{
		Box(x - 2, y - 2, 13, 19, DARK18, pDevice);
		Border(x-2, y-2, 13, 19, 1, BLACK, pDevice);
	}
	Text(BText, x + 50, y + 1, DARK18, DT_LEFT | DT_NOCLIP);
}

void RadioCheck(char *BText, int &Var, D3DCOLOR ctext, D3DCOLOR cisintext, D3DCOLOR ctclick, D3DCOLOR cbutton, D3DCOLOR cisinbox, D3DCOLOR cbclick, IDirect3DDevice9* pDevice, int NumberX, int NumberY)
{
	int x = NumberX * 105 + 30;
	int y = NumberY * 20 + 6;
	if (Var == 1){ cbutton = cbclick; ctext = ctclick; }
	if (IsInBox(x, y, 100, 14))
	{
		if (Var == 0){ cbutton = cisinbox; ctext = cisintext; }
		if (lm){ Var = !Var; }
	}
	ColorCircle(x, y, 10, DARK15, pDevice);
	ColorCircle(x, y, 8, cbutton, pDevice);
	Text(BText, x + 50, y + 1, ctext, DT_LEFT | DT_NOCLIP);
}

void ColorCheck(char *BText, int &Var, D3DCOLOR ctext, D3DCOLOR cisintext, D3DCOLOR ctclick, D3DCOLOR cborder, D3DCOLOR cisinborder, D3DCOLOR cbclick, LPDIRECT3DDEVICE9 pDevice, int NumberX, int NumberY)
{
	int x = NumberX * 105 + 30;
	int y = NumberY * 20 + 6;
	D3DCOLOR cbutton;
	if (IsInBox(x, y, 100, 14))
	{
		if (Var == 0){ cborder = cisinborder; ctext = cisintext; }
		if (lm){ if (Var >= 0){ Var++; } }
		if (rm){ if (Var != 0){ Var--; } }
	}
	switch (Var)
	{
	case 1: cbutton = RED;        break;
	case 2: cbutton = GREEN;      break;
	case 3: cbutton = BLUE;       break;
	case 4: cbutton = ORANGE;     break;
	case 5:                Var = 0; break;
	}
	if (Var > 0){ Box(x + 3, y + 3, 10, 10, cbutton, pDevice); cborder = cbclick; }
	Border(x, y, 14, 14, 2, cborder, pDevice);
	Text(BText, x + 25, y + 1, ctext, DT_LEFT | DT_NOCLIP);
}

void ScrollCheck(char *BText, char **typ, int &Var, D3DCOLOR ctext, D3DCOLOR cbutton, LPDIRECT3DDEVICE9 pDevice, int NumberX, int NumberY, int max)
{
	int x = NumberX * 105 + 30;
	int y = NumberY * 20 + 6;
	D3DCOLOR DopText1, DopText2;
	DopText1 = DARK18; DopText2 = DARK18;
	if (IsInBox(x, y, 14, 14))
	{
		DopText1 = RED;
		if (flm){ if (Var != 0){ Var--; Sleep(50); } }
	}
	Box(x, y, 14, 14, DARK7, pDevice);
	Border(x, y, 14, 14, 1, DARK15, pDevice);
	Text("<", x + 5, y, DopText1, DT_LEFT | DT_NOCLIP);
	if (IsInBox(x + 15, y, 14, 14))
	{
		DopText2 = GREEN;
		if (flm){ if (Var >= 0){ Var++; Sleep(50); }if (Var > max){ Var = max; } }
	}
	Box(x + 14, y, 14, 14, DARK7, pDevice);
	Border(x + 14, y, 14, 14, 1, DARK15, pDevice);
	Text(">", x + 5 + 14, y, DopText2, DT_LEFT | DT_NOCLIP);
	if (IsInBox(x + (14 * 2), y, 100, 14))
	{
		if (frm){ if (Var != 0){ Var--; Sleep(50); } }
		if (flm){ if (Var >= 0){ Var++; Sleep(50); }if (Var > max){ Var = max; } }
	}
	char buf_T[256];
	sprintf(buf_T, "  [%s]  %s", typ[Var], BText);
	Text(buf_T, x + (14 * 2), y - 1, ctext, DT_LEFT | DT_NOCLIP);
}

void ColorBar(char *BText, int &Var, D3DCOLOR ctext, D3DCOLOR cisintext, D3DCOLOR ctclick, D3DCOLOR cborder, D3DCOLOR cisinborder, D3DCOLOR cbclick, LPDIRECT3DDEVICE9 pDevice, int NumberX, int NumberY)
{
	int x = NumberX * 105 + 30;
	int y = NumberY * 20;
	D3DCOLOR cbutton;
	if (IsInBox(x, y, 100, 14))
	{
		if (Var == 0){ cborder = cisinborder; ctext = cisintext; }
		if (lm){ if (Var >= 0){ Var++; } }
		if (rm){ if (Var != 0){ Var--; } }
	}
	switch (Var)
	{
	case 0: cbutton = WINDOWS2;     break;
	case 1: cbutton = DARK10;     break;
	case 2: cbutton = BLUEMAZAY;  break;
	case 3: cbutton = ORANGE;     break;
	case 4: cbutton = YELLOW;     break;
	case 5: cbutton = GREEN;	  break;
	case 6:                Var = 0; break;
	}
	Box(x + 1, y + 1, 98, 10, cbutton, pDevice); cborder = cbclick;
	Border(x, y, 100, 12, 2, cborder, pDevice);
	Text(BText, x + 105, y + 1, ctext, DT_LEFT | DT_NOCLIP);
}

//-----------------------------------------------------------------------------
// Exam: Bar  ("Цветной Чек",Test11  ,TColOff,TColIsIn,TColOn  ,EColOff,EColIsIn,EColOn,  pDevice,0,1);//Готово
// Desc: Check
// Сonc: Menu/Components
//-----------------------------------------------------------------------------

void Bar(char *BText, int x, int y, int w, int h, int s, D3DCOLOR TextHead, D3DCOLOR BoxHead, D3DCOLOR BorderHead, D3DCOLOR BoxOther, D3DCOLOR BorderOther, LPDIRECT3DDEVICE9 pDevice)
{
	Border(x, y, w, 20, s, BorderHead, pDevice);
	Box(x, y, w, 20, BoxHead, pDevice);
	Border(x, y + 22, w, h, s, BorderOther, pDevice);
	Box(x, y + 21, w, h, BoxOther, pDevice);
	Text(BText, x + 5, y + 2, TextHead, DT_LEFT | DT_NOCLIP);
}
int GetTextLen(LPCTSTR szString)
{
    RECT rect = {0,0,0,0};
    pFont->DrawText(NULL, szString, -1, &rect, DT_CALCRECT, 0);
    return rect.right;
} 
void Group_Box(int x,int y,int w,int h,LPCTSTR szString,IDirect3DDevice9* pDevice )
{
	int wht = 1;
	int Tmp_ = GetTextLen(szString);
	if(w>(Tmp_+2))
	{
	 DrawBox(x, y,w,wht,DARK20,  pDevice);
     DrawBox(x, y-h,4,wht,DARK20,  pDevice);
	 DrawBox(x, y,wht,h,DARK20,  pDevice);
	 DrawBox(x+w, y,wht,h+1,DARK20,  pDevice);
	 DrawBox(x+6+Tmp_, y-h,w-6-Tmp_,wht,DARK20,  pDevice);	 
	 Text((LPSTR)szString, x+6,y-h-7, EColOn, DT_LEFT | DT_NOCLIP);
	}
}


void Scroll(int x, int y,char *BText, char **typ,float w, int Num, int &GetCurrent, LPDIRECT3DDEVICE9 pDevice)
{
	POINT mpos;
	GetCursorPos(&mpos);
	ScreenToClient(GetForegroundWindow(), &mpos);
	if (IsInBox(x, y-2.5, w, 15))
	{
		if (flm)
		{
			GetCurrent = mpos.x - (x);
		}
	}
	Box(x, y, w + 10, 10, DARK5, pDevice);
	Border(x , y, w+10, 10, 1, BLACK, pDevice);
	Box(x + GetCurrent, y,h-GetCurrent, 10, EColOn, pDevice);
	Box(x + GetCurrent, y-2.5, 10, 15, EColOn, pDevice);
	Border(x+ GetCurrent, y-2.5, 10, 15, 1, BLACK, pDevice);
 static char test[256];
 sprintf(test, "  [%d] %s", GetCurrent / Num,BText);
 Text(test, x + 10, y - 20, EColOn, DT_LEFT | DT_NOCLIP);

}


void DrawMenu(LPDIRECT3DDEVICE9 pDevice)
{
	Border(20, 20, 320, 230, 1, EColOn, pDevice);
	Box(20, 20, 320, 230, DARK2, pDevice);
	Box(20, 20, 320, 20, EColOn, pDevice);

	if(Fun.Test2==1)
	{
	Border(80, 80,70 , 500, 1, EColOn, pDevice);
	Box(70, 70, 70, 70, DARK2, pDevice);
	Box(70, 70, 70, 70, EColOn, pDevice);
	}
	Text("Editor", 25, 405, BLUE, DT_LEFT | DT_NOCLIP);
	Text("Главное меню", 25, 25, WHITE , DT_LEFT | DT_NOCLIP);
}