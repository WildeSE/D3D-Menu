class CDeathPlayer;
class CLocalPlayerID;
class CRenderData;
class CRenderContext;
class CGameBase;
class CBonesContext;
class CBone;
class CPlayer;
class CPlayer2;
class GetCurrentHP;
class sESPTools;



class GetCurrentHP
{
public:
float GetCurHP;
};

class CPlayer2
{
public:
BYTE Dead_player;
char _0x0000[99];
float CrosshairX;
float CrosshairY;
D3DXVECTOR3 position;
};
class CDeathPlayer
{
public:
	BYTE Death[16];
};

class CLocalPlayerID
{
public:
	BYTE ID;
};

class CRenderData
{
public:
	CRenderContext* RenderData;
};

class CRenderContext
{
public:
	
	char unknown[0x8BF];
	D3DXMATRIX ViewMatrix;
	D3DXMATRIX ProjectMatrix;
	D3DXMATRIX WorldMatrix;
};

class CGameBase
{
public:
	char pad[0x158];
	CBonesContext* Bones;
};

class CBonesContext
{
public:
	char pad[0xE8];
	CBone* BoneData;
};

class CBone
{
public:
	D3DXMATRIX BoneMatrix;
};

class CGame
{
public:
	BYTE unknown1[0x14];
	CGameBase *GameBase[16];
};
class CPlayer
{
public:
	BYTE        IsLife;
	char        Unk[99];
	D3DXVECTOR2 Cross;
	D3DXVECTOR3 Pos;
};
DWORD GameBase = *(DWORD *)0xAFF0C4;
CGame *Game = (CGame *)(GameBase);