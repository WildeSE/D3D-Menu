int ViewportInfo(int iCode, LPDIRECT3DDEVICE9 pDevice)
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
float VectorDistance( D3DVECTOR vPlayer, D3DVECTOR vMe )
{
	D3DVECTOR vSave;
	float rResult;
	vSave.x = vPlayer.x - vMe.x;
	vSave.y = vPlayer.y - vMe.y;
	vSave.z = vPlayer.z - vMe.z;
	rResult = ( vSave.x* vSave.x+ vSave.y* vSave.y+ vSave.z* vSave.z );
	return sqrt( rResult );
}

float rScreenX[16];
float rScreenY[16];
void ControlESP(D3DVECTOR &vScreen, int i)
{
	int nForce;
	if ( rScreenX[i] != vScreen.x )
	{
		if ( rScreenX[i] > vScreen.x )
		{
			nForce= (int)(( rScreenX[i] - vScreen.x ) / 2);
			rScreenX[i]-= nForce;
		} 
		else if ( rScreenX[i] < vScreen.x )
		{
			nForce= (int)(( vScreen.x - rScreenX[i] ) / 2);
			rScreenX[i]+= nForce;
		}
	}

	if ( rScreenY[i] != vScreen.y )
	{
		if ( rScreenY[i] > vScreen.y )
		{
			nForce= (int)(( rScreenY[i] - vScreen.y ) / 2);
			rScreenY[i]-= nForce;
		} 
		else if ( rScreenY[i] < vScreen.y ) 
		{
			nForce= (int)(( vScreen.y - rScreenY[i] ) / 2);
			rScreenY[i]+= nForce;
		}
	}
}


DWORD GetSizeofCode( const char* szModuleName )
{
	HMODULE hModule = GetModuleHandle( szModuleName );
	if ( !hModule )	return NULL;
	PIMAGE_DOS_HEADER pDosHeader = PIMAGE_DOS_HEADER( hModule );
	if( !pDosHeader ) return NULL;
	PIMAGE_NT_HEADERS pNTHeader = PIMAGE_NT_HEADERS( (LONG)hModule + pDosHeader->e_lfanew );
	if( !pNTHeader ) return NULL;
	PIMAGE_OPTIONAL_HEADER pOptionalHeader = &pNTHeader->OptionalHeader;
	if( !pOptionalHeader ) return NULL;
	return pOptionalHeader->SizeOfCode;
}
#define ESP_Center	DT_CENTER | DT_VCENTER
#define ESP_Left	DT_LEFT | DT_NOCLIP

void EspString(int x, int y, int w, int h,DWORD Color, DWORD Style, const char *Format, ...)
{
	RECT FontPos1 = { x-1, y, x+w-1, y+h };
	RECT FontPos2 = { x+1, y, x+w+1, y+h };
	RECT FontPos3 = { x, y-1, x+w, y+h-1 };
	RECT FontPos4 = { x, y+1, x+w, y+h+1 };
	RECT FontPos = { x, y, x+w, y+h };
	char Buffer[1024] = {'\0'};


	va_list va_alist;
	va_start(va_alist, Format);
	vsprintf_s(Buffer, Format, va_alist);
	va_end(va_alist);

	Draw.pFont->DrawTextA(0, Buffer, -1, &FontPos, Style ,Color);
	Draw.pFont->DrawTextA(0, Buffer, -1, &FontPos1, Style ,0xFF000000);
	Draw.pFont->DrawTextA(0, Buffer, -1, &FontPos2, Style ,0xFF000000);
	Draw.pFont->DrawTextA(0, Buffer, -1, &FontPos3, Style ,0xFF000000);
	Draw.pFont->DrawTextA(0, Buffer, -1, &FontPos4, Style ,0xFF000000);
	Draw.pFont->DrawTextA(0, Buffer, -1, &FontPos, Style ,Color);
}

void Box(int x, int y, int w, int h, DWORD Color, LPDIRECT3DDEVICE9 pDevice)
{
	D3DRECT rec = { x, y, x + w, y + h };
	pDevice->Clear( 1, &rec, D3DCLEAR_TARGET, Color, 0, 0 );
	return;
}

void Border( int x, int y, int w, int h, int px, D3DCOLOR BorderColor, LPDIRECT3DDEVICE9 pDevice)
{
	Box( x, (y + h - px), w, px, BorderColor,pDevice);//лева€
	Box( (x + w - px), y, px, h, BorderColor,pDevice);//права€
	Box( x, y, px, h, BorderColor,pDevice);//нижн€€
	Box( x, y, w, px, BorderColor,pDevice); //верхн€€		
} 

void Esp2DBox( int x, int y, int w, int h, D3DCOLOR BorderColor, LPDIRECT3DDEVICE9 pDevice)
{
	Border( x, y, w, h, 2, BorderColor, pDevice);
}

void Line(float x, float y, float x2, float y2, float width, DWORD color)
{
	D3DXVECTOR2 vLine[2];
	Draw.pLine->SetWidth( width );
	Draw.pLine->SetAntialias( false );
	Draw.pLine->SetGLLines( true );
	vLine[0].x = x;
	vLine[0].y = y;
	vLine[1].x = x2;
	vLine[1].y = y2;
	Draw.pLine->Begin();
	Draw.pLine->Draw( vLine, 2, color );
	Draw.pLine->End();
	return;
}

#define	 HP_RED			D3DCOLOR_ARGB(255, 255, 000, 000)
#define	 HP_SCARLET		D3DCOLOR_ARGB(255, 255, 33, 000)
#define	 HP_CINNABAR	D3DCOLOR_ARGB(255, 255, 33, 000)
#define	 HP_MIDORANGE	D3DCOLOR_ARGB(255, 255, 90, 000)
#define	 HP_PUMPKIN		D3DCOLOR_ARGB(255, 255, 110, 000)
#define	 HP_MANDARIN	D3DCOLOR_ARGB(255, 255, 135, 000)
#define	 HP_SIGORANGE	D3DCOLOR_ARGB(255, 255, 155, 000)
#define	 HP_ORANGE		D3DCOLOR_ARGB(255, 255, 170, 000)
#define	 HP_OTBYELLOW	D3DCOLOR_ARGB(255, 255, 185, 000)
#define	 HP_YANDEX		D3DCOLOR_ARGB(255, 255, 200, 000)
#define	 HP_CHILD		D3DCOLOR_ARGB(255, 255, 200, 000)
#define	 HP_YELLOW		D3DCOLOR_ARGB(255, 255, 255, 000)
#define	 HP_LIME		D3DCOLOR_ARGB(255, 204, 255, 000)
#define	 HP_YELGREEN	D3DCOLOR_ARGB(255, 173, 255, 47)
#define	 HP_DEEPGREEN	D3DCOLOR_ARGB(255, 10, 255, 145)
#define	 HP_LGREEN		D3DCOLOR_ARGB(255, 102, 255, 000)
#define	 HP_GREEN		D3DCOLOR_ARGB(255, 000, 255, 000)
void EspHealthBar(int x, int y, int w, int h, float HP, LPDIRECT3DDEVICE9 pDevice)
{
	DWORD HPcol = HP_GREEN;
	if (HP < 100 )HPcol = HP_GREEN;
	if (HP < 95 )HPcol = HP_GREEN;
	if (HP < 90 )HPcol = HP_LGREEN;
	if (HP < 85 )HPcol = HP_DEEPGREEN;
	if (HP < 80 )HPcol = HP_YELGREEN;
	if (HP < 75 )HPcol = HP_LIME;
	if (HP < 70 )HPcol = HP_YELLOW;
	if (HP < 65 )HPcol = HP_CHILD;
	if (HP < 60 )HPcol = HP_YANDEX;
	if (HP < 55 )HPcol = HP_OTBYELLOW;
	if (HP < 50 )HPcol = HP_ORANGE;
	if (HP < 45 )HPcol = HP_SIGORANGE;
	if (HP < 40 )HPcol = HP_MANDARIN;
	if (HP < 35 )HPcol = HP_PUMPKIN;
	if (HP < 30 )HPcol = HP_MIDORANGE;
	if (HP < 25 )HPcol = HP_MIDORANGE;
	if (HP < 20 )HPcol = HP_CINNABAR;
	if (HP < 15 )HPcol = HP_SCARLET;
	if (HP < 10) HPcol = HP_RED;

	Box(x,y+4,w,h,0xff000000,pDevice);//22
	Box(x+1,y+5,(int)(((w-2)/100.f)*HP),h-2,HPcol,pDevice);
}