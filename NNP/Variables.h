typedef HRESULT(WINAPI* oDrawIndexedPrimitive)(LPDIRECT3DDEVICE9 pDevice, D3DPRIMITIVETYPE Type, INT BaseVertexIndex, UINT MinVertexIndex, UINT NumVertices, UINT startIndex, UINT primCount);
typedef HRESULT(WINAPI* oPresent)(LPDIRECT3DDEVICE9 pDevice, CONST RECT* pSourceRect, CONST RECT* pDestRect, HWND hDestWindowOverride, CONST RGNDATA* pDirtyRegion);
typedef HRESULT(WINAPI* oReset)(LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters);
typedef HRESULT(WINAPI* oQuery)(LPDIRECT3DDEVICE9 pDevice, D3DQUERYTYPE Type, IDirect3DQuery9** ppQuery);
typedef HRESULT(WINAPI* oEndScene)(LPDIRECT3DDEVICE9 pDevice);

oQuery pQuery;
oReset pReset;
oPresent pPresent;
oDrawIndexedPrimitive pDrawIndexedPrimitive;
oEndScene pEndScene;
D3DCOLOR EColOn; //Цвет елементов  [Вкл]
bool Color = true;
BOOL Create;      //Создаем все содержимое
bool hExitThread; //Выключаем сеанс
bool Show = true;//Показ меню
int x, y, w, h;      //Координаты для элементов
POINT  mofs;      //Мышка			
POINT  mpos;      //Мышка
int	lm /*Левая Кнопка одно нажатие*/, rm/*Правая Кнопка одно нажатие*/,
	flm/*Левая Кнопка быстр. нажатие*/, frm/*Правая Кнопка быстр. нажатие*/;
LPDIRECT3DDEVICE9 pD3D9;    //D3D9 Девайс pD3D9
IDirect3DDevice9* pDevice;  //D3D9 Девайс pDevice
ID3DXFont*  pFont;          //D3D9 Девайс pFont
LPD3DXLINE  pLine;          //D3D9 Девайс pLine
D3DVIEWPORT9 viewP;         //D3D9 Девайс viewP
LPDIRECT3DTEXTURE9 White, Red, Green, Blue, Purple, Yellow;
char FileName[1024];
LPDIRECT3DSURFACE9 surf;   //D3D9 Девайс 
int I;
#define CText (DT_CENTER|DT_NOCLIP)//Текст "Центр"
#define LText (DT_LEFT|DT_NOCLIP) //Текст "Лего"
#define RText (DT_RIGHT|DT_NOCLIP)//Текст "Праго"
#define PI 3.14159265//Число ПИ
float A1, A2, A3, A4;   //Анимация
float Aero;          //Прозрачность

//========== Переменные волуе ==========//
char *volue [] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "23", "24", "25", "26", "27", "28", "29", "30", "31", "32", "33", "34", "35", "36", "37", "38", "39", "40","41","42","43","44","45","46","47","48","49","50","51" };
char *antime [] = { "0.1", "0.2", "0.3", "0.4", "0.5", "0.6", "0.7", "0.8", "0.9", "1" };



//========== Переменные функций ==========//

class cFun
{
public:
	int Test1, Test2, Test3, Test4, Test5, Test6, Test7, Test8, Test9, Test10, Haks, esp, Player;
	int Fun1, Fun2, Fun3, Fun4, Fun5, Fun6, Fun7, Fun8, Fun9, Fun10, Fun11, Fun12, Fun13, Fun14, Fun15, FPS1;
	int отдача, гравитация, нож, откл_нож, проход, карта, верт_стрельба, мин_прицел, кросхаир, maxbeg, maxsmena, offperezed;//мемхаки
	int кубик, дистанция, линии, противник, свои, все, цветблаквуд, цветварфейс, кубик3д;
	int Test11, Test12, цветбв, цветф,tests;
	int Smena, Knife;
	int SmenaOn, KnifeOn,EspGM,WallShoot,AntiKick,kupon110xp,resp,jump,prizok,GM,reload,AO,Aim;           
	int Color1, Color2, Color3, Color4, Color5, Color6;   
	

};
extern cFun Fun;   