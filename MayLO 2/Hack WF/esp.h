#include <fcntl.h>
#include <stdio.h>
#include <io.h>
#include <iostream> 
#include <Windows.h>
#include "Khiriliza.h"
#include "Classes.h"
void  CryCreateCriticalSectionInplace(void*){}
void  CryDeleteCriticalSectionInplace(void*){}
using namespace std;
typedef std::string Str;
typedef std::wstring WStr;

class SSystemGlobalEnvironment
{
public:
	char _0x0028[40];
	IEntitySystem* pEntitySystem; //0x0028 
	IPhysicalWorld* pPhysicalWorld; //0x002C
	char _0x0054[36];
	IRenderer* pIRenderer; //0x0054 
	char _0x00A0[72];
	IGame* GetIGame; //0x00A0
};


SSystemGlobalEnvironment* GetSSystemGlobalEnvironment()
{
	DWORD A_SSystemGlobalEnvironment = *(DWORD*)0x165C988;
	SSystemGlobalEnvironment* m_SSystemGlobalEnvironment = NULL;
	if (A_SSystemGlobalEnvironment)
		m_SSystemGlobalEnvironment = (SSystemGlobalEnvironment*)(A_SSystemGlobalEnvironment);
	return m_SSystemGlobalEnvironment;
}


IActorSystem* GetIActorSystem()
{
	IActorSystem* m_IActorSystem = NULL;
	if (GetSSystemGlobalEnvironment()->GetIGame->getIGameFramework->GetIActorSystem())
		m_IActorSystem = GetSSystemGlobalEnvironment()->GetIGame->getIGameFramework->GetIActorSystem();
	return m_IActorSystem;
}

IActor* MyActor()
{
	IActor* Player;
	bool MPlayer = NULL;
	if (GetSSystemGlobalEnvironment()->GetIGame->getIGameFramework->GetClientActor(&Player))
		MPlayer = GetSSystemGlobalEnvironment()->GetIGame->getIGameFramework->GetClientActor(&Player);
	return Player;
}


IGameRules* GetGameRules()
{
	IGameRules* m_IGameRules = NULL;
	IGameFramework* pGameFramework = NULL;
	pGameFramework = GetSSystemGlobalEnvironment()->GetIGame->getIGameFramework;
	if (!pGameFramework) return 0;
	m_IGameRules = pGameFramework->GetCurrentGameRules();
	if (m_IGameRules)    return m_IGameRules;
	else                return 0;
}

int R, G, B;
int R1, G1, B1;
int R2, G2, B2;
int R3, G3, B3;

void __fastcall Line(float x, float y, float x2, float y2, float width, DWORD color)
{
	D3DXVECTOR2 vLine[2];
	Draw.pLine->SetWidth(width);
	Draw.pLine->SetAntialias(false);
	Draw.pLine->SetGLLines(true);
	vLine[0].x = x;
	vLine[0].y = y;
	vLine[1].x = x2;
	vLine[1].y = y2;
	Draw.pLine->Begin();
	Draw.pLine->Draw(vLine, 2, color);
	Draw.pLine->End();

	return;
}
void  Draw_Line(float x, float y, float x2, float y2, int Width, D3DCOLOR Color)
{
	D3DXVECTOR2 vLine[2];
	Draw.pLine->SetWidth(Width);
	Draw.pLine->SetAntialias(false);
	Draw.pLine->SetGLLines(true);
	vLine[0].x = x;
	vLine[0].y = y;
	vLine[1].x = x2;
	vLine[1].y = y2;
	Draw.pLine->Begin();
	Draw.pLine->Draw(vLine, 2, Color);
	Draw.pLine->End();
}
void __fastcall String(int x, int y, DWORD Color, DWORD Style, const char *Format, ...)
{
	RECT rect;
	SetRect(&rect, x, y, x, y);
	char Buffer[1024] = { '\0' };
	va_list va_alist;
	va_start(va_alist, Format);
	vsprintf_s(Buffer, Format, va_alist);
	va_end(va_alist);
	Draw.pFont->DrawTextA(NULL, Buffer, -1, &rect, Style, Color);

	return;
}
class cTool
{
public:
	void Box3D(IEntity* m_IEntity, DWORD Color)
	{
		Vec3 Min, Max, vVec1, vVec2, vVec3, vVec4, vVec5, vVec6, vVec7, vVec8;
		AABB1 bBox;
		m_IEntity->GetWorldBounds(bBox);
		Max = bBox.max;
		Min = bBox.min;

		vVec3 = Min;
		vVec3.x = Max.x;
		vVec4 = Min;
		vVec4.y = Max.y;
		vVec5 = Min;
		vVec5.z = Max.z;
		vVec6 = Max;
		vVec6.x = Min.x;
		vVec7 = Max;
		vVec7.y = Min.y;
		vVec8 = Max;
		vVec8.z = Min.z;

		if (!WorldToScreen(Min, vVec1))
			return;
		if (!WorldToScreen(Max, vVec2))
			return;
		if (!WorldToScreen(vVec3, vVec3))
			return;
		if (!WorldToScreen(vVec4, vVec4))
			return;
		if (!WorldToScreen(vVec5, vVec5))
			return;
		if (!WorldToScreen(vVec6, vVec6))
			return;
		if (!WorldToScreen(vVec7, vVec7))
			return;
		if (!WorldToScreen(vVec8, vVec8))
			return;
		Line(vVec1.x, vVec1.y, vVec5.x, vVec5.y, 1, Color);
		Line(vVec2.x, vVec2.y, vVec8.x, vVec8.y, 1, Color);
		Line(vVec3.x, vVec3.y, vVec7.x, vVec7.y, 1, Color);
		Line(vVec4.x, vVec4.y, vVec6.x, vVec6.y, 1, Color);
		Line(vVec1.x, vVec1.y, vVec3.x, vVec3.y, 1, Color);
		Line(vVec1.x, vVec1.y, vVec4.x, vVec4.y, 1, Color);
		Line(vVec8.x, vVec8.y, vVec3.x, vVec3.y, 1, Color);
		Line(vVec8.x, vVec8.y, vVec4.x, vVec4.y, 1, Color);
		Line(vVec2.x, vVec2.y, vVec6.x, vVec6.y, 1, Color);
		Line(vVec2.x, vVec2.y, vVec7.x, vVec7.y, 1, Color);
		Line(vVec5.x, vVec5.y, vVec6.x, vVec6.y, 1, Color);
		Line(vVec5.x, vVec5.y, vVec7.x, vVec7.y, 1, Color);
	}
	int GetTeam(IActor* ItActor)
	{
		SSystemGlobalEnvironment* Global = GetSSystemGlobalEnvironment();
		IGameFramework* frame = Global->GetIGame->getIGameFramework;
		if (ItActor)
			return frame->GetCurrentGameRules()->GetTeam(ItActor->GetEntity()->GetRawId());
	}
	/*	void Magnit(IActor* Player, const Vec3 &pos, Ang3 anle)
	{
	SSystemGlobalEnvironment* m_SSystemGlobalEnvironment = GetSSystemGlobalEnvironment();
	IGameFramework* m_GetGameFramework = GetSSystemGlobalEnvironment()->GetIGame->getIGameFramework;
	if (Player && GetGameRules())
	{
	return GetGameRules()->MovePlayer(Player, pos, anle);
	}
	}*/
	float Distance(Vec3 VecA, Vec3 VecB)
	{
		return sqrt(((VecA.x - VecB.x) * (VecA.x - VecB.x)) +
			((VecA.y - VecB.y) * (VecA.y - VecB.y)) +
			((VecA.z - VecB.z) * (VecA.z - VecB.z)));
	}

	int  HProjectToScreen(IRenderer* pIRenderer, float sx, float sy, float sz, float* ox, float* oy, float* oz)
	{
		VecToScreen pVecToScreen;
		pVecToScreen.toX = sx;
		pVecToScreen.toY = sy;
		pVecToScreen.toZ = sz;
		pVecToScreen.outX = ox;
		pVecToScreen.outY = oy;
		pVecToScreen.outZ = oz;
		return  pIRenderer->ProjectToScreen(&pVecToScreen);
	}


	bool WorldToScreen(Vec3 vEntPos, Vec3 &vOut)
	{
		SSystemGlobalEnvironment* m_SSystemGlobalEnvironment = GetSSystemGlobalEnvironment();
		IRenderer* Renderer = m_SSystemGlobalEnvironment->pIRenderer;

		HProjectToScreen(Renderer, vEntPos.x, vEntPos.y, vEntPos.z, &vOut.x, &vOut.y, &vOut.z);

		vOut.x *= (Renderer->GetWidth() / 100.0f);
		vOut.y *= (Renderer->GetHeight() / 100.0f);
		vOut.z *= 1.0f;

		return ((vOut.z < 1.0f) && (vOut.x > 0) && (vOut.x < (float)Renderer->GetWidth()) && (vOut.y > 0) && (vOut.y < (float)Renderer->GetHeight()));
	}
	D3DXVECTOR3 Inverse(D3DXVECTOR3 Inv, float x, float y, float z)
	{
		float x1 = Inv.x + x;
		float y1 = Inv.y + y;
		float z1 = Inv.z + z;
		return D3DXVECTOR3(x1, y1, z1);
	}
	Vec3 GetBonePositionByID(IEntity* pEnt, int BoneID)
	{
		char* getBoneName;
		Vec3 vNULL;
		ICharacterInstance *pCharacterInstance = pEnt->GetCharacter(0);
		if (!pCharacterInstance)
			return vNULL;
		ISkeletonPose *pSkeletonPose = pCharacterInstance->GetISkeletonPose();
		if (!pSkeletonPose)
			return vNULL;
		int sBoneID = BoneID;
		if (sBoneID == -1)
			return vNULL;
		Matrix34 World = pEnt->GetWorldTM();
		Matrix34 SkeletonAbs = Matrix34(pSkeletonPose->GetAbsJointByID(sBoneID));
		Matrix34 matWorld = World;
		float m03, m13, m23;
		m03 = (World.m00*SkeletonAbs.m03) + (World.m01*SkeletonAbs.m13) + (World.m02*SkeletonAbs.m23) + World.m03;
		matWorld.m03 = m03;
		m13 = (World.m10*SkeletonAbs.m03) + (World.m11*SkeletonAbs.m13) + (World.m12*SkeletonAbs.m23) + World.m13;
		matWorld.m13 = m13;
		m23 = (World.m20*SkeletonAbs.m03) + (World.m21*SkeletonAbs.m13) + (World.m22*SkeletonAbs.m23) + World.m23;
		matWorld.m23 = m23;

		return matWorld.GetTranslation();
	}
	void __fastcall Circle(int X, int Y, int radius, int numSides, DWORD Color)
	{
		D3DXVECTOR2 Line[128];
		float Step = (float)(D3DX_PI * 2.0 / numSides);
		int Count = 0;
		for (float a = 0; a < D3DX_PI*2.0; a += Step)//2.0 = 0
		{
			float X1 = radius * cos(a) + X;
			float Y1 = radius * sin(a) + Y;
			float X2 = radius * cos(a + Step) + X;
			float Y2 = radius * sin(a + Step) + Y;
			Line[Count].x = X1;
			Line[Count].y = Y1;
			Line[Count + 1].x = X2;
			Line[Count + 1].y = Y2;
			Count += 2;
		}
		Draw.pLine->Begin();
		Draw.pLine->Draw(Line, Count, Color);
		Draw.pLine->End();
	}

	void __fastcall BoneLine(int bone_1, int bone_2, IEntity* pEnt, DWORD color)
	{
		Vec3 bone1 = GetBonePositionByID(pEnt, bone_1), bone2 = GetBonePositionByID(pEnt, bone_2);
		Vec3 outbone_1, outbone_2;
		WorldToScreen(bone1, outbone_1); WorldToScreen(bone2, outbone_2);
		Line(outbone_1.x, outbone_1.y, outbone_2.x, outbone_2.y, 1, color);
	}
	void __fastcall HeadDraw(int bone_1, int bone_2, IEntity* pEnt, DWORD color)
	{
		Vec3 bone1 = GetBonePositionByID(pEnt, bone_1), bone2 = GetBonePositionByID(pEnt, bone_2);
		Vec3 outbone_1, outbone_2;
		WorldToScreen(bone1, outbone_1); WorldToScreen(bone2, outbone_2);
		Circle(outbone_2.x, outbone_2.y, 4, 15, color);

	}
	void __fastcall DrawHed(IEntity* pEnt, DWORD color)
	{

		HeadDraw(9, 16, pEnt, YELLOW);

	}
	void __fastcall DrawSkeleton(IEntity* pEnt, DWORD color)
	{

		BoneLine(3, 4, pEnt, color);
		BoneLine(3, 5, pEnt, color);
		BoneLine(3, 8, pEnt, color);
		BoneLine(8, 9, pEnt, color);
		BoneLine(9, 13, pEnt, color);
		BoneLine(13, 47, pEnt, color);
		BoneLine(13, 24, pEnt, color);
		BoneLine(47, 68, pEnt, color); // локти право
		BoneLine(24, 27, pEnt, color); // локти левое
		BoneLine(68, 57, pEnt, color);
		BoneLine(27, 34, pEnt, color);
		BoneLine(4, 70, pEnt, color);
		BoneLine(70, 71, pEnt, color);
		BoneLine(5, 77, pEnt, color);
		BoneLine(77, 78, pEnt, color);
		HeadDraw(9, 16, pEnt, YELLOW);
		BoneLine(69, 49, pEnt, color);//пальци
		BoneLine(49, 52, pEnt, color);
		BoneLine(52, 60, pEnt, color);
		BoneLine(60, 61, pEnt, color);
		BoneLine(49, 53, pEnt, color);
		BoneLine(53, 62, pEnt, color);
		BoneLine(62, 63, pEnt, color);
		BoneLine(49, 54, pEnt, color);
		BoneLine(54, 64, pEnt, color);
		BoneLine(64, 65, pEnt, color);
		BoneLine(49, 55, pEnt, color);
		BoneLine(55, 66, pEnt, color);
		BoneLine(66, 67, pEnt, color);
		BoneLine(49, 51, pEnt, color);
		BoneLine(51, 58, pEnt, color);
		BoneLine(58, 59, pEnt, color);
		BoneLine(47, 15, pEnt, color);
		BoneLine(24, 14, pEnt, color);
		BoneLine(14, 15, pEnt, color);
		BoneLine(24, 25, pEnt, color);
		BoneLine(25, 26, pEnt, color);
		BoneLine(26, 27, pEnt, color);
		//DrawBone(13,21,pEnt,color); DrawBone(21,16,pEnt,color); DrawBone(21,17,pEnt,color);
		BoneLine(1, 3, pEnt, color);//Pelvis - Spine++
		BoneLine(3, 8, pEnt, color);//Pelvis - Spine1++
		BoneLine(8, 9, pEnt, color);//Spine1 - Spine2++
		BoneLine(9, 10, pEnt, color);//Spine2 - Spine3++
		BoneLine(10, 12, pEnt, color);//Spine3 - Neck(ше€)++
		BoneLine(12, 13, pEnt, color);//Neck(ше€) - Head++
		BoneLine(5, 1, pEnt, color);//L Thingh - Pelvis++
		BoneLine(4, 1, pEnt, color);//R Thingh -Pelvis++
		BoneLine(4, 70, pEnt, color);//правое бедро - нога++
		BoneLine(70, 71, pEnt, color);//правое нога - ступн€++
		BoneLine(72, 73, pEnt, color);//правое ступн€ - п€тка++
		BoneLine(71, 73, pEnt, color);//правое нога - п€тка++
		BoneLine(72, 75, pEnt, color);//права€ п€тка - пальци++
		BoneLine(5, 77, pEnt, color);//лева€ бедро - нога++
		BoneLine(77, 78, pEnt, color);//лева€ нога - ступн€++
		BoneLine(78, 80, pEnt, color);//++
		BoneLine(79, 80, pEnt, color);//лева€ нога - п€тка++
		BoneLine(79, 82, pEnt, color);//лева€ п€тка - пальци++
	}
	enum EWstrToUTF8Constants
	{
		eWTUC_MASKBITS = 0x3F,
		eWTUC_MASKBYTE = 0x80,
		eWTUC_MASK2BYTES = 0xC0,
		eWTUC_MASK3BYTES = 0xE0,

		eUTWC_MASKBYTE = 0x80,
		eUTWC_MASKBITS = 0x3F,
		eUTWC_MASKIDBITS = 0xE0,
		eUTWC_MASK2BYTES = 0xC0,
		eUTWC_MASK3BYTES = 0xE0,
	};
	void __fastcall UTF8ToWStr(const char* str, WStr& dstr)
	{
		WStr tmp;

		const size_t length = strlen(str);
		tmp.resize(length);
		tmp.clear();

		const unsigned char* const src = (unsigned char*)str;

		for (size_t i = 0; i < length;)
		{
			if (src[i] < 0x80) // < 128
			{
				tmp.append(1, (wchar_t)src[i]);
				++i;
			}
			else if ((src[i] & eUTWC_MASKIDBITS) == eUTWC_MASK2BYTES)
			{
				wchar_t d = (wchar_t)(src[i] & ~eUTWC_MASKIDBITS) << 6;
				wchar_t e = (wchar_t)(src[i + 1] & eUTWC_MASKBITS);
				wchar_t f = d | e;
				tmp.append(1, f);
				i += 2;
			}
			else
			{
				wchar_t d = (wchar_t)(src[i] & ~eUTWC_MASKIDBITS) << 12;
				wchar_t e = (wchar_t)(src[i + 1] & eUTWC_MASKBITS) << 6;
				wchar_t f = (wchar_t)(src[i + 2] & eUTWC_MASKBITS);
				wchar_t g = d | e | f;
				tmp.append(1, g);
				i += 3;
			}
		}

		dstr.assign(tmp.data(), tmp.length());
	}

	Vec3 GetPlayerPos(IEntity* pEntit)
	{
		Vec3 vOffset = Vec3();
		Matrix34 pWorld = pEntit->GetWorldTM();
		vOffset = pWorld.GetTranslation();
		return vOffset;
	}
	void __fastcall Names(const char *name, Vec3 coors, DWORD Color)
	{
		using namespace std;
		WStr names_2;
		char* tst[40];
		int size = strlen(name);
		UTF8ToWStr(name, names_2);
		for (size_t i = 0; i < names_2.length(); i++)
		{
			int fuck = names_2[i];
			for (int w = 0; w < 76; w++)
			if (fuck == kiriliza_kod[w])
			{
				tst[i] = alf[w];
			}

			Draw.String((coors.x - 35) + 7.7*i, coors.y + 15, Color, DT_LEFT | DT_NOCLIP, "%s", tst[i]);
		}
	}
	void Aim(IActor* MyActor, IEntity* pEnt, float dist)
	{
		IEntity* Local = MyActor->GetEntity();
		if ((pEnt == NULL) && (Local == NULL))return;
		Vec3 xTarget = GetPlayerPos(pEnt);
		Vec3 xLocal = GetPlayerPos(Local);
		Vec3 Out, tOut;
		int BONEKOST;
		if (Varm.bon == 0)
		{
			BONEKOST = 13;
		}
		if (Varm.bon == 1)
		{
			BONEKOST = 8;
		}
		Out = Tool->GetBonePositionByID(pEnt, BONEKOST);
		tOut = Tool->GetBonePositionByID(Local, 18);
		Vec3 Aim;
		Aim.x = Out.x - tOut.x;
		Aim.y = Out.y - tOut.y;
		Aim.z = Out.z - tOut.z;
		Quat Heading = Quat::CreateRotationVDir(Aim.normalize());
		if (dist>0){ MyActor->SetViewRotation(Heading); }
		else if (dist>10){ MyActor->SetViewRotation(Heading); }
		else if (dist>20){ MyActor->SetViewRotation(Heading); }
		else if (dist>30){ MyActor->SetViewRotation(Heading); }
		else if (dist>40){ MyActor->SetViewRotation(Heading); }
		else if (dist>50){ MyActor->SetViewRotation(Heading); }
		else if (dist>60){ MyActor->SetViewRotation(Heading); }
		else if (dist>70){ MyActor->SetViewRotation(Heading); }
		else if (dist>80){ MyActor->SetViewRotation(Heading); }
		else if (dist>90){ MyActor->SetViewRotation(Heading); }

	}
	int isVisible(Vec3 EnemyPos, Vec3 MyPos)
	{
		Vec3 vTemp;
		ray_hit tmpHit;
		vTemp.x = EnemyPos.x - MyPos.x;
		vTemp.y = EnemyPos.y - MyPos.y;
		vTemp.z = EnemyPos.z - MyPos.z;
		return !GetSSystemGlobalEnvironment()->pPhysicalWorld->RayWorldIntersection(MyPos, vTemp, 0x100 | 1, 0x0F | 0x400, &tmpHit, 1);
	}
}*Tool;

void ESP_Line(long Xa, long Ya, long Xb, long Yb, DWORD dwWidth)
{
	Draw_Line(Xa, Ya, Xb, Yb, dwWidth, BLUE);
}

bool GetDeadPlayer(IActor* Player)
{
	if (Player->IsDead()) return true;
	else return false;
}
bool M1Team(IActor* MePlayer, IActor* LocPlayer)
{
	int mTeam = Tool->GetTeam(MePlayer);
	int pTeam = Tool->GetTeam(LocPlayer);

	if ((mTeam != pTeam || pTeam == 0))
		return true;
	else
		return false;
}
void Min()
{
	SSystemGlobalEnvironment* m_SSystemGlobalEnvironment = GetSSystemGlobalEnvironment();
	IGameFramework* pIGameFramework = m_SSystemGlobalEnvironment->GetIGame->getIGameFramework;
	IRenderer* Renderer = m_SSystemGlobalEnvironment->pIRenderer;
	if (pIGameFramework)
	{
		IActor* MePlayer;
		if (pIGameFramework->GetClientActor(&MePlayer))
		{
			IActorSystem* pActorSystem = pIGameFramework->GetIActorSystem();
			IEntityIt* pEntityIt = m_SSystemGlobalEnvironment->pEntitySystem->GetEntityIterator();
			if (MePlayer && pEntityIt)
			{
				for (; IEntity* pEntity = pEntityIt->Next();)
				{
					IEntity* pExp = pEntity;
					IEntity* mEntity = MePlayer->m_pEntity;
					if (pExp)
					{
						Vec3 mine = Tool->GetPlayerPos(pExp);
						Vec3 Outs;
						DWORD ColorHidden1, ColorHidden2;
						switch (Varm.ColorHiden1)
						{
						case 1:  ColorHidden1 = LIME; break;
						case 2:  ColorHidden1 = GREEN; break;
						case 3:  ColorHidden1 = BLUE; break;
						case 4:  ColorHidden1 = Aqua; break;
						case 5:  ColorHidden1 = CHOCOLATE2; break;
						case 6:  ColorHidden1 = RED; break;
						case 7:  ColorHidden1 = ORANGE; break;
						case 8:  ColorHidden1 = PURPLE; break;
						case 9:  ColorHidden1 = GREY; break;
						case 10:  ColorHidden1 = GOLD2; break;
						}
						switch (Varm.ColorHiden2)
						{
						case 1: ColorHidden2 = LIME; break;
						case 2: ColorHidden2 = GREEN; break;
						case 3: ColorHidden2 = BLUE; break;
						case 4: ColorHidden2 = Aqua; break;
						case 5: ColorHidden2 = CHOCOLATE2; break;
						case 6: ColorHidden2 = RED; break;
						case 7: ColorHidden2 = ORANGE; break;
						case 8: ColorHidden2 = PURPLE; break;
						case 9: ColorHidden2 = GREY; break;
						case 10: ColorHidden2 = GOLD2; break;
						}
						if (Tool->WorldToScreen(mine, Outs))
						{
							if ((strstr(pExp->GetName(), "@")))
							{
								if (Varm.wp)
								{
									Tool->Box3D(pExp, ColorHidden1);
								}
							}
							if ((strstr(pExp->GetName(), "ammo")))
							{
								if (Varm.vzryv)
								{
									Tool->Box3D(pExp, ColorHidden2);
								}
							}
						}
					}
				}
			}
		}
	}
}
void HackTools()
{
	SSystemGlobalEnvironment* m_SSystemGlobalEnvironment = GetSSystemGlobalEnvironment();
	IGameFramework* pIGameFramework = m_SSystemGlobalEnvironment->GetIGame->getIGameFramework;
	IRenderer* Renderer = m_SSystemGlobalEnvironment->pIRenderer;
	if (pIGameFramework)
	{
		float ScreenCenterX = (Renderer->GetWidth() / 2.0f);
		float ScreenCenterY = (Renderer->GetHeight() / 2.0f);
		float ScreenBottomY = (Renderer->GetHeight());
		IActor* MePlayer;
		if (pIGameFramework->GetClientActor(&MePlayer))
		{
			IActorSystem* pActorSystem = pIGameFramework->GetIActorSystem();
			IEntityIt* pEntityIt = m_SSystemGlobalEnvironment->pEntitySystem->GetEntityIterator();
			if (MePlayer && pEntityIt)
			{
				for (; IEntity* pEntity = pEntityIt->Next();)
				{
					if (IActor* LocPlayer = pActorSystem->GetActor(pEntity->m_pEntityId))
					{
						IEntity* mEntity = MePlayer->m_pEntity;
						Vec3 EnemyPos = Tool->GetPlayerPos(pEntity);
						Vec3 Head = Tool->GetBonePositionByID(pEntity, 13), Head2;
						Vec3 pHead = Tool->GetBonePositionByID(pEntity, 18);
						Vec3 mHead = Tool->GetBonePositionByID(MePlayer->GetEntity(), 18);
						Vec3 Mpos = Tool->GetPlayerPos(mEntity);
						Vec3 setscale, Screen;
						float Distancion = Tool->Distance(Tool->GetPlayerPos(mEntity), Tool->GetPlayerPos(pEntity));

						int fm = Tool->GetTeam(MePlayer);
						int tm = Tool->GetTeam(LocPlayer);

						if (Varm.tm)
						{
							fm != 1;
						}
						DWORD ColorVisible, ColorHidden;
						switch (Varm.ColorVisible)
						{
						case 1: ColorVisible = RED; break;
						case 2: ColorVisible = GREEN; break;
						case 3: ColorVisible = BLUE; break;
						case 4: ColorVisible = Aqua; break;
						case 5: ColorVisible = CHOCOLATE2; break;
						case 6: ColorVisible = WHITE; break;
						case 7: ColorVisible = ORANGE; break;
						case 8: ColorVisible = PURPLE; break;
						case 9: ColorVisible = GREY; break;
						case 10: ColorVisible = GOLD2; break;
						}

						switch (Varm.ColorHiden)
						{
						case 1: ColorHidden = RED; break;
						case 2: ColorHidden = GREEN; break;
						case 3: ColorHidden = BLUE; break;
						case 4: ColorHidden = Aqua; break;
						case 5: ColorHidden = CHOCOLATE2; break;
						case 6: ColorHidden = WHITE; break;
						case 7: ColorHidden = ORANGE; break;
						case 8: ColorHidden = PURPLE; break;
						case 9: ColorHidden = GREY; break;
						case 10: ColorHidden = GOLD2; break;
						}
						Vec3 Mpos2 = { 0, 0, 0 };
						float x_1, y_1, z_1;
						switch (Varm._fMagX)
						{
						case 0: x_1 = 0.0f; break;
						case 1: x_1 = 0.2f; break;
						case 2: x_1 = 0.5f; break;
						case 3: x_1 = 1.0f; break;
						case 4: x_1 = 2.0f; break;
						case 5: x_1 = 3.0f; break;
						case 6: x_1 = 4.0f; break;
						case 7: x_1 = 5.0f; break;
						case 8: x_1 = 6.0f; break;
						case 9: x_1 = 7.0f; break;
						case 10: x_1 = 8.0f; break;
						case 11: x_1 = 9.0f; break;
						case 12: x_1 = 10.0f; break;
						case 13: x_1 = 11.0f; break;
						case 14: x_1 = 12.0f; break;
						case 15: x_1 = 13.0f; break;
						case 16: x_1 = 14.0f; break;
						case 17: x_1 = 15.0f; break;
						}
						switch (Varm._fMagY)
						{
						case 0: y_1 = 0.0f; break;
						case 1: y_1 = 0.2f; break;
						case 2: y_1 = 0.5f; break;
						case 3: y_1 = 1.0f; break;
						case 4: y_1 = 2.0f; break;
						case 5: y_1 = 3.0f; break;
						case 6: y_1 = 4.0f; break;
						case 7: y_1 = 5.0f; break;
						case 8: y_1 = 6.0f; break;
						case 9: y_1 = 7.0f; break;
						case 10: y_1 = 8.0f; break;
						case 11: y_1 = 9.0f; break;
						case 12: y_1 = 10.0f; break;
						case 13: y_1 = 11.0f; break;
						case 14: y_1 = 12.0f; break;
						case 15: y_1 = 13.0f; break;
						case 16: y_1 = 14.0f; break;
						case 17: y_1 = 15.0f; break;
						}
						switch (Varm._fMagZ)
						{
						case 0: z_1 = 0.0f; break;
						case 1: z_1 = 0.2f; break;
						case 2: z_1 = 0.5f; break;
						case 3: z_1 = 1.0f; break;
						case 4: z_1 = 2.0f; break;
						case 5: z_1 = 3.0f; break;
						case 6: z_1 = 4.0f; break;
						case 7: z_1 = 5.0f; break;
						case 8: z_1 = 6.0f; break;
						case 9: z_1 = 7.0f; break;
						case 10: z_1 = 8.0f; break;
						case 11: z_1 = 9.0f; break;
						case 12: z_1 = 10.0f; break;
						case 13: z_1 = 11.0f; break;
						case 14: z_1 = 12.0f; break;
						case 15: z_1 = 13.0f; break;
						case 16: z_1 = 14.0f; break;
						case 17: z_1 = 15.0f; break;
						}
						if (Varm.vzlet)
						{
							if (GetAsyncKeyState(VK_V)){ setscale.x = 100; setscale.y = 100; setscale.z = 20; }
							else{ setscale.x = 1; setscale.y = 1; setscale.z = 1; }
							MePlayer->GetEntity()->SetScale(setscale);
						}
						if (Varm.Kasper)
						{
							if (GetAsyncKeyState(VK_Q)){ setscale.x = 100; setscale.y = 100; setscale.z = 1; }
							else{ setscale.x = setscale.y = setscale.z = 1; }
							MePlayer->GetEntity()->SetScale(setscale);
						}
						if (Varm.sped)
						{
							if (GetAsyncKeyState(VK_SHIFT))
							{
								MePlayer->SpeedHack = 1.4;
							}
							else
							{
								MePlayer->SpeedHack = 1;
							}
						}
							if (MePlayer != LocPlayer)
							if (M1Team(MePlayer, LocPlayer) && (!GetDeadPlayer(LocPlayer)))
							{
								if (Varm._fMag)
								{
									if (GetKeyState(VK_CAPS) & 1)
									{
										Mpos2.x = Mpos.x + x_1;
										Mpos2.y = Mpos.y + y_1;
										Mpos2.z = Mpos.z + z_1;
										pEntity->SetPos(Mpos2);
									}
								}
								if ((Tool->WorldToScreen(EnemyPos, Screen) && tm != fm != Varm.tm && (!GetDeadPlayer(LocPlayer))))
								{
									if (Varm.Line == 1)
									{
										Draw_Line(ScreenCenterX, ScreenCenterY, Screen.x, Screen.y, 1, Tool->isVisible(pHead, mHead) ? ColorVisible : ColorHidden);
									}
									if (Varm.ESP_Dist == 1)
									{
										String(Screen.x, Screen.y, Red, CText, "[ƒистанци€: %0.1f]", Distancion);
									}
									if (Varm.ESPName == 1)
									{
										Tool->Names(pEntity->GetName(), Screen, Blue);
									}
									if (Varm.ESPSkel == 1)
									{
										Tool->DrawSkeleton(pEntity, Tool->isVisible(pHead, mHead) ? ColorVisible : ColorHidden);
									}
									if (Varm.ESP_3D == 1)
									{
										Tool->Box3D(pEntity, Tool->isVisible(pHead, mHead) ? ColorVisible : ColorHidden);
									}
									if (Varm.NoAim)
									{
										(!(strstr(pEntity->GetName(), "IronMan") || !strstr(pEntity->GetName(), "Helicopter") || !strstr(pEntity->GetName(), "mech") || !strstr(pEntity->GetName(), "ShieldBearer")));
									}
									if (Varm.NoMG)
									{
										(!(strstr(pEntity->GetName(), "IronMan") || !strstr(pEntity->GetName(), "Helicopter") || !strstr(pEntity->GetName(), "mech") || !strstr(pEntity->GetName(), "ShieldBearer")));
									}
									if (Tool->WorldToScreen(Head, Head2) && (Tool->isVisible(pHead, mHead)) && (M1Team(MePlayer, LocPlayer) && (!GetDeadPlayer(LocPlayer))))
									{
										if (Varm.OnAim)
										{
											DWORD AimKey;
											switch (Varm.AimKey)
											{
											case 0: AimKey = VK_LBUTTON; break;
											case 1: AimKey = VK_E; break;
											case 2: AimKey = VK_LMENU; break;
											}
											if (GetAsyncKeyState(AimKey))
												Tool->Aim(MePlayer, pEntity, Distancion);
										}
									}
								}

							}
						}
					}
				}
			}
		}
	}