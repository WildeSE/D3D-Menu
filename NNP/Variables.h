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
D3DCOLOR EColOn; //���� ���������  [���]
bool Color = true;
BOOL Create;      //������� ��� ����������
bool hExitThread; //��������� �����
bool Show = true;//����� ����
int x, y, w, h;      //���������� ��� ���������
POINT  mofs;      //�����			
POINT  mpos;      //�����
int	lm /*����� ������ ���� �������*/, rm/*������ ������ ���� �������*/,
	flm/*����� ������ �����. �������*/, frm/*������ ������ �����. �������*/;
LPDIRECT3DDEVICE9 pD3D9;    //D3D9 ������ pD3D9
IDirect3DDevice9* pDevice;  //D3D9 ������ pDevice
ID3DXFont*  pFont;          //D3D9 ������ pFont
LPD3DXLINE  pLine;          //D3D9 ������ pLine
D3DVIEWPORT9 viewP;         //D3D9 ������ viewP
LPDIRECT3DTEXTURE9 White, Red, Green, Blue, Purple, Yellow;
char FileName[1024];
LPDIRECT3DSURFACE9 surf;   //D3D9 ������ 
int I;
#define CText (DT_CENTER|DT_NOCLIP)//����� "�����"
#define LText (DT_LEFT|DT_NOCLIP) //����� "����"
#define RText (DT_RIGHT|DT_NOCLIP)//����� "�����"
#define PI 3.14159265//����� ��
float A1, A2, A3, A4;   //��������
float Aero;          //������������

//========== ���������� ����� ==========//
char *volue [] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "23", "24", "25", "26", "27", "28", "29", "30", "31", "32", "33", "34", "35", "36", "37", "38", "39", "40","41","42","43","44","45","46","47","48","49","50","51" };
char *antime [] = { "0.1", "0.2", "0.3", "0.4", "0.5", "0.6", "0.7", "0.8", "0.9", "1" };



//========== ���������� ������� ==========//

class cFun
{
public:
	int Test1, Test2, Test3, Test4, Test5, Test6, Test7, Test8, Test9, Test10, Haks, esp, Player;
	int Fun1, Fun2, Fun3, Fun4, Fun5, Fun6, Fun7, Fun8, Fun9, Fun10, Fun11, Fun12, Fun13, Fun14, Fun15, FPS1;
	int ������, ����������, ���, ����_���, ������, �����, ����_��������, ���_������, ��������, maxbeg, maxsmena, offperezed;//�������
	int �����, ���������, �����, ���������, ����, ���, �����������, �����������, �����3�;
	int Test11, Test12, ������, �����,tests;
	int Smena, Knife;
	int SmenaOn, KnifeOn,EspGM,WallShoot,AntiKick,kupon110xp,resp,jump,prizok,GM,reload,AO,Aim;           
	int Color1, Color2, Color3, Color4, Color5, Color6;   
	

};
extern cFun Fun;   