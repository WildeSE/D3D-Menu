
BOOL Create;      //������� ��� ����������
bool Show = true;//����� ����		
POINT  mpos;      //�����
D3DCOLOR EColOn; //���� ���������  [���]
int	lm /*����� ������ ���� �������*/, rm/*������ ������ ���� �������*/,
flm/*����� ������ �����. �������*/, frm/*������ ������ �����. �������*/;
LPDIRECT3DDEVICE9 pD3D9;    //D3D9 ������ pD3D9
IDirect3DDevice9* pDevice;  //D3D9 ������ pDevice
ID3DXFont*  pFont;          //D3D9 ������ pFont
ID3DXLine*  pLine;          //D3D9 ������ pLine
ID3DXFont*		rFont;
ID3DXSprite*	pSprite;


float rScreenX[16];
float rScreenY[16];

#define LText (DT_LEFT|DT_NOCLIP)
int Status;
bool Aim, Player, Test, Dino, weapon, Choose = 0, Choose2 = 0;
  int title;

static struct _Keys
{
	bool        bPressed;
	DWORD       dwStartTime;
}kPressingKeys[256];

struct AllStruct
{
	struct GenrealCoord
	{
		int x = 10, y = 40;
		struct bpos
		{
			int x, y = 110, s1 = 130, s2 = s1 + 20, s3 = s1 + 40;
		}bpos;
	}GC;

	struct ESPCoord
	{
		int x=10, y=300;
		struct bpos
		{
			int x, y; 
		}bpos;
		int Colorx, Colory;

	}ESPC;

	struct AIMCoord
	{
		int x=300, y=300;
		struct bpos
		{ 
			int x, y,		
			x2, y2=110;
		}bpos;
	}AIMC;

	struct MiscCoord
	{
		int x, y;
		struct bpos
		{
			int x, y; 
		}bpos;
	}MC;

}AS;


class cFun
{
public:
	int Test1, Test2, Test3, Test4, Test5, Test6, Test7, Test8, Test9, Test10, Haks, esp, Player;
	int Fun1, Fun2, Fun3, Fun4, Fun5, Fun6, Fun7, Fun8, Fun9, Fun10, Fun11, Fun12, Fun13, Fun14, Fun15, FPS1;
	int ������, ����������, ���, ����_���, ������, �����, ����_��������, ���_������, ��������, maxbeg, maxsmena, offperezed;//�������
	int �����, ���������, �����, ���������, ����, ���, �����������, �����������, �����3�;
	int Test11, Test12, ������, �����, tests;
	int Smena, Knife;
	int SmenaOn, KnifeOn, EspGM, WallShoot, AntiKick, kupon110xp, resp, jump, prizok, GM, reload, AO, Aim, DinoFast, iDinoSpam,SwapWeapon;
	int Color1, Color2, Color3, Color4, Color5, Color6;


};
extern cFun Fun;