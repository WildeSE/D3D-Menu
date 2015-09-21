
class cInstallFont
{
public:
	
	void __fastcall InstallLine(LPDIRECT3DDEVICE9 pDevice)
	{
		D3DXCreateLine(pDevice, &Draw.pLine);
	}

	void __fastcall ResetLine()
	{
		Draw.pLine->OnLostDevice();
		Draw.pLine->OnResetDevice();
	}

	void __fastcall OnLostLine()
	{
		Draw.pLine->OnLostDevice();
	}

	void __fastcall ResetFont()
	{
		Draw.pFont->OnLostDevice();
		Draw.pFont->OnResetDevice();
		Draw.pFonts->OnLostDevice();
		Draw.pFonts->OnResetDevice();
	}

	void __fastcall OnLostFont()
	{
		Draw.pFont->OnLostDevice();
		Draw.pFonts->OnLostDevice();
	}

	BOOL __fastcall CheckFont()
	{
		if (Draw.pFont && Draw.pFonts)
			return FALSE;
		else
			return TRUE;
	}

}*cInstall;