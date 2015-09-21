
BOOL Create;      //Создаем все содержимое
bool Show = true;//Показ меню		
POINT  mpos;      //Мышка
D3DCOLOR EColOn; //Цвет елементов  [Вкл]
int	lm /*Левая Кнопка одно нажатие*/, rm/*Правая Кнопка одно нажатие*/,
flm/*Левая Кнопка быстр. нажатие*/, frm/*Правая Кнопка быстр. нажатие*/;
LPDIRECT3DDEVICE9 pD3D9;    //D3D9 Девайс pD3D9
IDirect3DDevice9* pDevice;  //D3D9 Девайс pDevice
ID3DXFont*  pFont;          //D3D9 Девайс pFont
ID3DXLine*  pLine;          //D3D9 Девайс pLine
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
	int отдача, гравитация, нож, откл_нож, проход, карта, верт_стрельба, мин_прицел, кросхаир, maxbeg, maxsmena, offperezed;//мемхаки
	int кубик, дистанция, линии, противник, свои, все, цветблаквуд, цветварфейс, кубик3д;
	int Test11, Test12, цветбв, цветф, tests;
	int Smena, Knife;
	int SmenaOn, KnifeOn, EspGM, WallShoot, AntiKick, kupon110xp, resp, jump, prizok, GM, reload, AO, Aim, DinoFast, iDinoSpam,SwapWeapon;
	int Color1, Color2, Color3, Color4, Color5, Color6;


};
extern cFun Fun;