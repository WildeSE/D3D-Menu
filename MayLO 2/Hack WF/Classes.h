#include "cSDK.h"
#define COLLISION_RAY_PIERCABILITY 10
#define rwi_pierceability_mask  0x0F
struct IEntityIt;
class IEntityClass;
class IGame;
class IGameFramework;
class IGameRulesSystem;
class CGameRules;
class IActorSystem;
struct IActorIterator;
class IActor;
class IEntity;
class ICharacterInstance;
class ISkeletonPose;
class IRenderer;
struct IPhysicalWorld;
struct ray_info;
struct ray_hit;
class HitInfo;
struct IFireMode;
struct IZoomMode;
struct IWeapon;
struct IItem;
class IInventory;
struct SSpreadModParams;
struct SRecoilModParams;
class IItemSystem;
class IWeaponFiringLocator;
class IWeaponEventListener;
struct SProjectileLaunchParams;

struct AABB1
{
	Vec3 min;
	Vec3 max;
};

template <class _I> class _smart_ptr
{
private:
	_I* p;
public:
	_smart_ptr() : p(NULL) {}
#if defined(LINUX64)
	_smart_ptr(typeof(__null)) : p(NULL) {}
#endif
	_smart_ptr(int Null) : p(NULL) {}
	_smart_ptr(_I* p_)
	{
		p = p_;
		if (p)
			p->AddRef();
	}

	_smart_ptr(const _smart_ptr &p_)
	{
		p = p_.p;
		if (p)
			p->AddRef();
	}
	~_smart_ptr()
	{
		if (p)
			p->Release();
	}
	operator _I*() const { return p; }
	_I& operator*() const { return *p; }
	_I* operator->() const { return p; }
	_I* operator+() const { return p; }
	_I* get() const { return p; }
	_smart_ptr&  operator=(_I* newp)
	{
		if (newp)
			newp->AddRef();
		if (p)
			p->Release();
		p = newp;
		return *this;
	}

	void reset()
	{
		_smart_ptr<_I>().swap(*this);
	}

	void reset(_I* p)
	{
		_smart_ptr<_I>(p).swap(*this);
	}

	_smart_ptr&  operator=(const _smart_ptr &newp)
	{
		if (newp.p)
			newp.p->AddRef();
		if (p)
			p->Release();
		p = newp.p;
		return *this;
	}
	bool operator !() const
	{
		return p == NULL;
	};
};

template<typename F, class A> struct Matrix34_tpl;
typedef unsigned int EntityId;
typedef _smart_ptr<IActorIterator> IActorIteratorPtr;

enum   EChatMessageType
{
	eChatToTarget = 0,
	eChatToTeam,
	eChatToAll
};

struct CryMatrix34
{
	float   m00, m01, m02, m03,
	m10, m11, m12, m13,
	m20, m21, m22, m23;
};

struct IPhysicalEntity
{

};

struct ray_hit
{
	float dist;
	IPhysicalEntity *pCollider;
	int ipart;
	int partid;
	short surface_idx;
	short idmatOrg;
	int foreignIdx;
	int iNode;
	D3DXVECTOR3 pt;
	D3DXVECTOR3 n;
	int bTerrain;
	int iPrim;
	ray_hit *next;
};

struct ray_hit_cached : ray_hit
{
	ray_hit_cached() { pCollider = 0; ipart = 0; }
	ray_hit_cached(const ray_hit &hit)
	{
		pCollider = hit.pCollider; ipart = hit.ipart;
		iNode = hit.iNode;
	}
	ray_hit_cached &operator=(const ray_hit &hit)
	{
		pCollider = hit.pCollider; ipart = hit.ipart;
		iNode = hit.iNode; return *this;
	}
};

class HitInfo
{
public:
	int shooterId;//0x00       
	int targetId;//0x04        
	int weaponId;//0x08        
	int projectileId;//0x0C    
	float damage;//0x10          
	float impulse;//0x14         
	float radius;//0x18          
	float angle;//0x1C           
	int material;//0x20        
	int type;//0x24            
	int bulletType;//0x28      
	float damageMin;//0x2C
	float pierce;//0x30
	int partId;//0x34
	D3DXVECTOR3 pos;//0x38             
	D3DXVECTOR3 dir;//0x44             
	D3DXVECTOR3 normal;//0x50          
	BYTE projectileClassId[2];//0x5C 
	BYTE weaponClassId[2];//0x5E
	bool remote;//0x60         
	bool aimed;//0x61           
	bool knocksDown;//0x62      
	bool knocksDownLeg;//0x63   
	bool hitViaProxy;//0x64     
	bool explosion;//0x65       
	bool bUnknown1;//0x66                 
	bool bUnknown2;//0x67                 
	float armorHeating;//0x68    
	int penetrationCount;//0x6C 
};

struct VecToScreen
{
public:
	float toX;
	float toY;
	float toZ;
	float* outX;
	float* outY;
	float* outZ;
};

class GetFirePose;
struct FireCountPos
{
	float X;
	float Y;
	float Z;
};

float fX;
float fY;
float fZ;

class IRenderer
{
public:
	virtual void function0(); //
	virtual void function1(); //
	virtual void function2(); //
	virtual void function3(); //
	virtual void function4(); //
	virtual void function5(); //
	virtual void function6(); //
	virtual void function7(); // 
	virtual void function8(); //
	virtual void function9(); //
	virtual void function10(); //
	virtual void function11(); //
	virtual void function12(); //
	virtual void function13(); //
	virtual void function14(); //
	virtual void function15(); //
	virtual void function16(); //
	virtual void function17(); //
	virtual void function18(); //
	virtual void function19(); //
	virtual void function20(); //
	virtual void function21(); //
	virtual void function22(); //
	virtual void function23(); //
	virtual void function24(); //
	virtual void function25(); //
	virtual void function26(); //
	virtual void function27(); //
	virtual void function28(); //
	virtual void function29(); //
	virtual void function30(); //
	virtual void function31(); //
	virtual void function32(); //
	virtual void function33(); //
	virtual void function34(); //
	virtual void function35(); //
	virtual void function36(); //
	virtual void function37(); //
	virtual void function38(); // 
	virtual void function39(); //
	virtual void function40(); //
	virtual void function41(); //
	virtual void function42(); //
	virtual void function43(); //
	virtual void function44(); //
	virtual void function45(); //
	virtual void function46(); // 
	virtual void function47(); //
	virtual void function48(); //
	virtual void function49(); // 
	virtual void function50(); //
	virtual void function51(); //
	virtual void function52(); //
	virtual void function53(); //
	virtual void function54(); //
	virtual void function55(); //
	virtual void function56(); //
	virtual void function57(); //
	virtual void function58(); //
	virtual void function59(); //
	virtual void function60(); //
	virtual void function61(); //
	virtual void function62(); //
	virtual void function63(); //
	virtual void function64(); //
	virtual void function65(); //
	virtual void function66(); //
	virtual void function67(); //
	virtual void function68(); //
	virtual void function69(); //
	virtual void function70(); //
	virtual void function71(); //
	virtual void function72(); //
	virtual void function73(); //
	virtual void function74(); //
	virtual void function75(); //
	virtual void function76(); //
	virtual void function77(); //
	virtual void function78(); // 
	virtual void function79(); //
	virtual void function80(); //
	virtual void function81(); //
	virtual void function82(); //
	virtual void function83(); // 
	virtual void function84(); //
	virtual int GetWidth(); // virtual void function85(); // 
	virtual int GetHeight(); // virtual void function86(); // 
	virtual void function87(); //
	virtual void function88(); //
	virtual void function89(); // 
	virtual bool ProjectToScreen(VecToScreen* pVecToScreen); // virtual void function90(); // 
	virtual void function91(); // 
	virtual void function92(); // 
	virtual void function93(); //
	virtual void Function94(); //
	virtual void Function95(); //
	virtual void Function96(); // 
	virtual void Function97(); //
	virtual void Function98(); //
	virtual void Function99(); //
	virtual void Function100(); //
	virtual void Function101();
	virtual void Function102();
	virtual void Function103();
	virtual void Function104();
	virtual void Function105();
	virtual void Function106();
	virtual void Function107();
	virtual void Function108();
	virtual void Function109();
	virtual void Function110();
	virtual void Function111();
	virtual void Function112();
	virtual void Function113();
	virtual void Function114();
	virtual void Function115();
	virtual void Function116();
	virtual void Function117();
	virtual void Function118();
	virtual void Function119();
	virtual void Function120();
	virtual void Function121();
	virtual void Function122();
	virtual void Function123();
	virtual void Function124();
	virtual void Function125();
	virtual void Function126();
	virtual void Function127();
	virtual void Function128();
	virtual void Function129();
	virtual void Function130();
	virtual void Function131();
	virtual void Function132();
	virtual void Function133();
	virtual void Function134();
	virtual void Function135();
	virtual void Function136();
	virtual void Function137();
	virtual void Function138();
	virtual void Function139();
	virtual void Function140();
	virtual void Function141();
	virtual void Function142();
	virtual void Function143();
	virtual void Function144();
	virtual void Function145();
	virtual void Function146();
	virtual void Function147();
	virtual void Function148();
	virtual void Function149();
	virtual void Function150();
	virtual void Function151();
	virtual void Function152();
	virtual void Function153();
	virtual void Function154();
	virtual void Function155();
	virtual void Function156();
	virtual void Function157();
	virtual void Function158();
	virtual void Function159();
	virtual void Function160();
	virtual void Function161();
	virtual void Function162();
	virtual void Function163();
	virtual void Function164();
	virtual void Function165();
	virtual void Function166();
	virtual void Function167();
	virtual void Function168();
	virtual void Function169();
	virtual void Function170();
	virtual void Function171();
	virtual void Function172();
	virtual void Function173();
	virtual void Function174();
	virtual void Function175();
	virtual void Function176();
	virtual void Function177();
	virtual void Function178();
	virtual void Function179();
	virtual void Function180();
	virtual void Function181();
	virtual void Function182();
	virtual void Function183();
	virtual void Function184();
	virtual void Function185();
	virtual void Function186();
	virtual void Function187();
	virtual void Function188();
	virtual void Function189();
	virtual void Function190();
	virtual void Function191();
	virtual void Function192();
	virtual void Function193();
	virtual void Function194();
	virtual void Function195();
	virtual void Function196();
	virtual void Function197();
	virtual void Function198();
	virtual void Function199();
	virtual void Function200();
};

struct IPhysicalWorld
{
public:
	virtual void function0(); //
	virtual void function1(); //
	virtual void function2(); //
	virtual void function3(); //
	virtual void function4(); //
	virtual void function5(); //
	virtual void function6(); // 
	virtual void function7(); // 
	virtual void function8(); //
	virtual void function9(); //
	virtual void function10(); //
	virtual void function11(); //
	virtual void function12(); // 
	virtual void function13(); //
	virtual void function14(); //
	virtual void function15(); //
	virtual void function16(); // 
	virtual void function17(); // 
	virtual void function18(); //
	virtual void function19(); //
	virtual void function20(); //
	virtual void function21(); //  
	virtual void function22(); //
	virtual void function23(); //
	virtual void function24(); //  
	virtual void function25(); //
	virtual void function26(); //
	virtual void function27(); //
	virtual void function28(); //
	virtual void function29(); //
	virtual void function30(); //
	virtual void function31(); //
	virtual void function32(); //
	virtual void function33(); //
	virtual void function34(); //
	virtual void function35(); //
	virtual void function36(); //
	virtual void function37(); //
	virtual void function38(); //
	virtual void function39(); //
	virtual void function40(); //
	virtual void function41(); //
	virtual void function42(); //
	virtual void function43(); //
	virtual void function44(); //
	virtual void function45(); //
	virtual void function46(); //
	virtual void function47(); //
	virtual void function48(); //
	virtual void function49(); //
	virtual void function50(); //
	virtual void Function51(); //
	virtual void Function52(); //
	virtual void Function53(); //
	virtual void Function54(); //
	virtual void Function55(); //
	virtual void Function56(); //
	virtual void Function57(); //
	virtual void Function58(); //
	virtual void Function59(); //
	virtual void Function60(); //
	virtual void Function61(); //
	virtual void Function62(); //
	virtual void Function63(); //
	virtual void Function64(); //
	virtual void Function65(); //
	virtual void Function66(); //
	virtual void Function67(); //
	virtual void Function68(); //
	virtual void Function69(); //
	virtual void Function70(); //
	virtual void Function71(); //
	virtual void Function72(); //
	virtual void Function73(); //
	virtual void Function74(); //
	virtual void Function75(); //
	virtual void Function76(); //
	virtual void Function77(); //
	virtual void Function78(); //
	virtual void Function79(); //
	virtual void Function80(); //
	virtual void function81(); //
	virtual void function82(); //
	virtual void function83(); //
	virtual void function84(); //
	virtual void function85(); //
	virtual void function86(); //
	virtual void function87(); //
	virtual void function88(); //
	virtual void function89(); //
	virtual int RayWorldIntersection(const Vec3& org, const Vec3& dir, int objtypes, unsigned int flags, ray_hit *hits, int nMaxHits, IPhysicalEntity **pSkipEnts = 0, int nSkipEnts = 0, void *pForeignData = 0, int iForeignData = 0, const char *pNameTag = "RayWorldIntersection(Game)", ray_hit_cached *phitLast = 0, int iCaller = 4);// virtual void function90(); // 
	virtual void function91(); //
	virtual void function92(); //
	virtual void function93(); //
	virtual void function94(); //
	virtual void function95(); //
	virtual void function96(); //
	virtual void function97(); //
	virtual void function98(); //
	virtual void function99(); //
	virtual void function100(); //
};

class ISkeletonPose
{
public:
	virtual void function0();
	virtual void function1(); // 
	virtual void function2(); //
	virtual void function3(); //
	virtual void function4(); // 
	virtual void function5(); //																	
	virtual void function6(); // 
	virtual void function7(); // 
	virtual void function8(); //
	virtual void function9(); //														
	virtual void function10(); //																
	virtual void function11(); //	 												
	virtual void function12(); //
	virtual void function13(); // 
	virtual void function14(); //
	virtual void function15(); //
	virtual void function16(); // 
	virtual void function17(); //
	virtual void function18(); //
	virtual void function19(); //
	virtual void function20(); //
	virtual void function21(); //
	virtual char* GetJointNameByID(__int32 nJointID) const = 0; //virtual void function22(); //
	virtual void function23(); //
	virtual void function24(); //
	virtual void function25(); //
	virtual void function26(); //
	virtual void function27(); // 
	virtual void function28(); //
	virtual void function29(); //
	virtual void function30(); //
	virtual void function31(); //
	virtual void function32(); //
	virtual void function33(); //
	virtual void function34(); //
	virtual void function35(); //
	virtual void function36(); //
	virtual void function37(); //
	virtual void function38(); //
	virtual void function39(); //
	virtual void function40(); //
	virtual const QuatT& GetAbsJointByID(__int32 nJointID) = 0; // virtual void function41(); //
	virtual void function42(); //
	virtual void function43(); //
	virtual void function44(); //
	virtual void function45(); //
	virtual void function46(); //
	virtual void function47(); //
	virtual void function48(); //
	virtual void function49(); //
	virtual void function50(); // 
	virtual void function51(); //
	virtual void function52(); //
	virtual void function53(); //
	virtual void function54(); //
	virtual void function55(); //
	virtual void function56(); //
	virtual void function57(); //
	virtual void function58(); //
	virtual void function59(); //
	virtual void function60(); //
	virtual void function61(); //
	virtual void function62(); // 
	virtual void function63(); //
	virtual void function64(); //
	virtual void function65(); //
	virtual void function66(); //
	virtual void function67(); //
	virtual void function68(); //
	virtual void function69(); //
	virtual void function70(); //
	virtual void function71(); //
	virtual void function72(); //
	virtual void function73(); // 
	virtual void function74(); // 
	virtual void function75(); //
	virtual void function76(); //
	virtual void function77(); //
	virtual void function78(); //
	virtual void function79(); //
	virtual void functio80(); //
};

enum Bones
{
	Bone_Pelvis = 1, // таз
	Bone_Locomotion, // хз че
	Bone_Spine, // позвоночник
	Bone_L_Thigh, // левое бедро
	Bone_R_Thigh, // правое бедро
	Bone_Groin_Back, // пах
	Bone_Groin_Front, // пах
	Bone_Spine1, // позвоночник1
	Bone_Spine2, // позвоночник2
	Bone_Spine3, // позвоночник3
	Bone_Wep_Law, // 
	Bone_Neck, // Шейка:)
	Bone_Head, // головка
	Bone_L_Clavicle, // 
	Bone_R_Clavicle, // 
	Bone_L_Eye, // левый глаз
	Bone_R_Eye,// правый глаз
	Bone_Camera, // камера
	Bone_L_Eye_01, // 
	Bone_R_Eye_01, // 
	Bone_HNeck, // 
	Bone_Camera_01, // 
	Bone_HNeck_End, // 
};


class ICharacterInstance
{
public:
	virtual void function0(); //
	virtual void function1(); //
	virtual void function2(); // 
	virtual void function3(); //
	virtual void function4(); //
	virtual void function5(); //
	virtual void function6(); //
	virtual void function7(); //
	virtual void function8(); //
	virtual void function9(); //
	virtual void function10(); // 
	virtual void function11(); //
	virtual void function12(); //
	virtual void function13(); //
	virtual void function14(); // 
	virtual void function15(); //
	virtual void function16(); //
	virtual void function17(); //
	virtual void function18(); //
	virtual void function19(); //
	virtual void function20(); //
	virtual void function21(); // 
	virtual void function22(); //
	virtual void function23(); //
	virtual void function24(); //
	virtual void function25(); //
	virtual void function26(); //
	virtual void function27(); //
	virtual void function28(); //
	virtual void function29(); //
	virtual void function30(); //
	virtual void function31(); //
	virtual void function32(); // 
	virtual void function33(); //
	virtual void function34(); //
	virtual void function35(); //
	virtual void function36(); //
	virtual void function37(); //
	virtual void function38(); //
	virtual void function39(); //
	virtual void function40(); //
	virtual void function41(); //
	virtual void function42(); //
	virtual void function43(); //
	virtual void function44(); //
	virtual void function45(); //
	virtual void function46(); //
	virtual void function47(); //
	virtual void function48(); //
	virtual void function49(); //
	virtual void function50(); //
	virtual void function51(); //
	virtual void function52(); //
	virtual void function53(); //
	virtual void function54(); //
	virtual void function55(); //
	virtual void function56(); //
	virtual void function57(); //
	virtual void function58(); //
	virtual void function59(); //
	virtual void function60(); //
	virtual void function61(); //
	virtual void function62(); //
	virtual ISkeletonPose* GetISkeletonPose();// virtual void function63(); //
};

class IEntitySystem
{
public:
	virtual void Function0(); // 
	virtual void Function1(); // 
	virtual void Function2(); // 
	virtual void Function3(); //
	virtual void Function4(); // 
	virtual void Function5(); //
	virtual void Function6(); //
	virtual void Function7(); // 
	virtual void Function8(); //
	virtual void Function9(); // 
	virtual void Function10(); //
	virtual void Function11(); //
	virtual void Function12(); // 
	virtual void Function13(); // 
	virtual void Function14(); // 
	virtual void Function15(); // 
	virtual void Function16(); // 
	virtual void Function17(); // 
	virtual void Function18(); //
	virtual void Function19(); // 
	virtual void Function20(); //
	virtual void Function21(); //
	virtual void Function22(); // 
	virtual void Function23(); //
	virtual void Function24(); // 
	virtual void Function25(); //
	virtual void Function26(); //
	virtual void Function27(); // 
	virtual void Function28(); // 
	virtual void Function29(); // 
	virtual void Function30(); // 
	virtual void Function31(); // 
	virtual void Function32(); // 
	virtual void Function33(); //
	virtual void Function34(); //
	virtual void Function35(); //
	virtual void Function36(); // 
	virtual void Function37(); // 
	virtual IEntityIt* GetEntityIterator(); // virtual void Function38(); //
	virtual void Function39(); //
	virtual void Function40(); //
};

struct IEntityIt
{
public:
	virtual void Function0(); // 
	virtual void Function1(); // 
	virtual void Function2(); // 
	virtual void Function3(); // 
	virtual void Function4(); // 
	virtual IEntity* Next(); // virtual void Function5(); // 
};

class IActorSystem
{
public:
	virtual void function0(); //
	virtual void function1(); //
	virtual void function2(); //
	virtual void function3(); //
	virtual void function4(); //
	virtual void function5(); //
	virtual void function6(); //
	virtual void function7(); //
	virtual void function8(); //
	virtual void function9(); //
	virtual void function10(); //
	virtual void function11(); //
	virtual void function12(); //
	virtual void function13(); //
	virtual void function14(); // 
	virtual IActor *GetActor(EntityId entityId); // virtual void function15(); // 
	virtual void function16(); //
	virtual void function17(); //
};

class IEntity
{
public:
	virtual void function0(); //
	virtual void function1(); //
	virtual void function2(); //
	virtual void function3(); // 
	virtual void function4(); //
	virtual void function5(); //
	virtual void function6(); //
	virtual void function7(); //
	virtual void function8(); // 
	virtual void function9(); //
	virtual void function10(); //
	virtual void function11(); //
	virtual void function12(); //
	virtual void function13(); //
	virtual void function14(); //
	virtual void function15(); //
	virtual void function16(); // 
	virtual void function17(); //
	virtual void function18(); //
	virtual void function19(); //
	virtual int GetRawId() const = 0; // virtual void function20(); //
	virtual void function21(); //
	virtual void function22(); //
	virtual void function23(); //
	virtual void function24(); //
	virtual void function25(); //
	virtual void function26(); //
	virtual void function27(); //
	virtual void function28(); // 
	virtual void function29(); // 
	virtual void GetWorldBounds(AABB1 &bbox) = 0; //virtual void function30(); //
	virtual void function31(); //
	virtual void function32(); // 
	virtual void function33(); // 
	virtual void function34(); //
	virtual const Matrix34& GetWorldTM() const = 0; // virtual void function35(); // 
	virtual void function36(); // 
	virtual void function37(); //
	virtual void function38(); //
	virtual void function39(); //
	virtual void function40(); //
	virtual void function41(); // 
	virtual void function42(); //
	virtual void function43(); // 
	virtual void function44(); //
	virtual void function45(); //
	virtual void function46(); // 
	virtual void function47(); // 
	virtual void function48(); // 
	virtual void function49(); //
	virtual void function50(); //
	virtual void function51(); //
	virtual void function52(); //
	virtual void function53(); //
	virtual void function54(); //
	virtual void function55(); //
	virtual void function56(); // 
	virtual void function57(); // 
	virtual void function58(); //
	virtual void function59(); //
	virtual void function60(); //
	virtual void function61(); //
	virtual void function62(); //
	virtual void function63(); //
	virtual void function64(); // 
	virtual void function65(); //
	virtual void function66(); //
	virtual void function67(); //
	virtual void function68(); // 
	virtual void function69(); // 
	virtual void function70(); //
	virtual void function71(); //
	virtual void function72(); //
	virtual void function73(); // 
	virtual void function74(); //
	virtual void function75(); //
	virtual void function76(); //
	virtual void function77(); // 
	virtual void function78(); // 
	virtual void function79(); // 
	virtual void function80(); //
	virtual void function81(); //
	virtual void function82(); // 
	virtual void function83(); //
	virtual void function84(); // 
	virtual void function85(); //
	virtual void function86(); //
	virtual void function87(); //
	virtual void function88(); // 
	virtual void function89(); //
	virtual void function90(); //
	virtual void function91(); //
	virtual void function92(); //
	virtual void function93(); // 
	virtual void function94(); //
	virtual void function95(); //
	virtual void function96(); // 
	virtual void function97(); //
	virtual void function98(); //
	virtual const char* GetName() const = 0; // virtual void function99(); //
	virtual void function100(); // 
	virtual void SetScale(const Vec3 &vScale, int nWhyFlags = 0) = 0; // virtual void function101(); // 
	virtual void SetPos(const Vec3 &vPos, int nWhyFlag = 10);//virtual void function102(); 
	virtual void function103(); //
	virtual void function104(); //
	virtual void function105(); // 
	virtual void function106(); //
	virtual void function107(); // 
	virtual void SetName(const char* text);//virtual void function108(); // 
	virtual void function109(); // 
	virtual void function110(); //
	virtual void function111(); // 
	virtual ICharacterInstance* GetCharacter(int nSlot) = 0;// virtual void function112(); //
public:
	char _0x0004[12];
	EntityId m_pEntityId; //0x0010 
	char _0x0014[68];
	Vec3 VectorPos; //0x0058
};

struct IGameObjectExtension
{
	IEntity * GetEntity() const { return m_pEntity; }
	char unk[4];
	EntityId GetEntityId() const { return m_entityId; }

public:
	IEntity * m_pEntity;
	char unk2[4];
	EntityId m_entityId;

};

class IActor : public IGameObjectExtension
{
public:
	virtual void function0(); //
	virtual void function1(); //
	virtual void function2(); //
	virtual void function3(); //
	virtual void function4(); //
	virtual void function5(); //
	virtual void function6(); //
	virtual void function7(); // 
	virtual void function8(); // 
	virtual void function9(); //
	virtual void function10(); //
	virtual void function11(); //
	virtual void function12(); // 
	virtual void function13(); //
	virtual void function14(); //
	virtual void function15(); // 
	virtual void function16(); //
	virtual void function17(); // 
	virtual void function18(); // 
	virtual void function19(); // 
	virtual void function20(); //
	virtual void function21(); //
	virtual void function22(); //
	virtual void Function23(); // 
	virtual int IsDead(); // virtual void Function24(); // 
	virtual void Function25(); // 
	virtual void Function26(); //
	virtual void Function27(); // 
	virtual void function28(); //
	virtual void Function29(); // 
	virtual void Function30(); //
	virtual void function31(); //
	virtual void Function32(); // 
	virtual void Function33(); // 
	virtual void function34(); //
	virtual void function35(); //
	virtual void function36(); //
	virtual void function37(); //
	virtual void function38(); // 
	virtual void Function39(); //
	virtual void function40(); //
	virtual void function41(); // 
	virtual void function42(); //
	virtual void function43(); // 
	virtual void function44(); //
	virtual void function45(); //
	virtual void function46(); //
	virtual void function47(); //	
	virtual void function48(); //
	virtual void function49(); //
	virtual void SetViewRotation(const Quat &rotation);  //virtual void function50(); // 
	virtual void function51(); //	
	virtual void function52(); //
	virtual void function53(); //
	virtual void function54(); //
	virtual void function55(); //
	virtual void function56(); //
	virtual void function57(); //
	virtual void function58(); //
	virtual void function59(); //
	virtual void function60(); //
	virtual void function61(); //
	virtual void function62(); //
	virtual void function63(); //
	virtual void function64(); //
	virtual void function65(); //
	virtual void function66(); //
	virtual void function67(); // 
	virtual void function68(); // 
	virtual void function69(); // 
	virtual void function70(); //
	virtual void function71(); //
	virtual void function72(); //
	virtual void function73(); //
	virtual void function74(); //
	virtual void function75(); //
	virtual void function76(); //
	virtual void function77(); //
	virtual void function78(); //
	virtual void function79(); //
	virtual void function80(); //
	virtual void function81(); //
	virtual void function82(); //
	virtual void function83(); //
	virtual void function84(); //
	virtual void function85(); //
	virtual void function86(); //
	virtual void function87(); //
	virtual void function88(); //
	virtual void function89(); //
	virtual void function90(); //
	virtual void function91(); //
	virtual void function92(); // 
	virtual void function93(); // 
	virtual void function94(); //
	virtual void function95(); //
	virtual void function96(); //
	virtual void function97(); //
	virtual void function98(); //
	virtual void function99(); //
	virtual void function100(); //
	virtual void function101(); // 
	virtual void function102(); //
	virtual void function103(); //
	virtual void function104(); //
	virtual void function105(); //
	virtual void function106(); //
	virtual void function107(); //
	virtual void function108(); //
	virtual void function109(); //
	virtual void function110(); //
	virtual void function111(); //
	virtual void function112(); // 
	virtual void function113(); //
	virtual void function114(); //
	virtual void function115(); //
	virtual void function116(); //
	virtual void function117(); //
	virtual void function118(); //
	virtual void function119(); //
	virtual void function120(); //
	virtual void function121(); //
	virtual void function122(); //
	virtual void function123(); //
	virtual void function124(); //
	virtual void function125(); //
	virtual void function126(); //
	virtual void function127(); //
	virtual void function128(); //
	virtual void function129(); //
	virtual void function130(); //
	virtual void function131(); //
	virtual void function132(); //
	virtual void function133(); //
	virtual void function134(); //
	virtual void function135(); //
	virtual void function136(); //
	virtual void function137(); //
	virtual void function138(); //
	virtual void function139(); //
	virtual void function140(); //
	virtual void function141(); //
	virtual void function142(); //
	virtual void function143(); //
	virtual void function144(); //
	virtual void function145(); //
	virtual void function146(); //
	virtual void function147(); //
	virtual void function148(); //
	virtual void function149(); //
	virtual void function150(); //
	virtual void function151(); //
	virtual void function152(); //
	virtual void function153(); //
	virtual void function154(); //
	virtual void function155(); //
	virtual void function156(); //
	virtual void function157(); //
	virtual void function158(); //
	virtual void function159(); //
	virtual void function160(); //
	virtual void function161(); //
	virtual void function162(); //
	virtual void function163(); //
	virtual void function164(); //
	virtual void function165(); //
	virtual void function166(); //
	virtual void function167(); //
	virtual void function168(); //
	virtual void function169(); //
	virtual void function170(); //
	virtual void function171(); //
	virtual void function172(); //
	virtual void function173(); //
	virtual void function174(); //
	virtual void function175(); //
	virtual void function176(); //
	virtual void function177(); //
	virtual void function178(); //
	virtual void function179(); //
	virtual void function180(); //
	virtual void function181(); //
	virtual void function182(); //
	virtual void function183(); //
	virtual void function184(); //
	virtual void function185(); //
	virtual void function186(); //
	virtual void function187(); //
	virtual void function188(); //
	virtual void function189(); //
	virtual void function190(); //
	virtual void function191(); //
	virtual void function192(); //
	virtual void function193(); //
	virtual void function194(); //
	virtual void function195(); //
	virtual void function196(); //
	virtual void function197(); //
	virtual void function198(); //
	virtual void function199(); //
	virtual void function200(); //
	virtual void function201(); //
	virtual void function202(); //
	virtual void function203(); //
	virtual void function204(); //
	virtual void function205(); //
	virtual void function206(); //
	virtual void function207(); //
	virtual void function208(); //
	virtual void function209(); //
	virtual void function210(); //
	virtual void function211(); //
	virtual void function212(); //
	virtual void function213(); //
	virtual void function214(); //
	virtual void function215(); //
	virtual void function216(); //
	virtual void function217(); //
	virtual void function218(); //
	virtual void function219(); //
public:
	char _0x0000[1672];
	float SpeedHack; //0x069C 
	char _0x06A0[1356];
	Vec3 Pos; //0x0BEC 
	char _0x0BF8[340];
	float viewFowScale; //0x0D4C 
	float viewSensivity; //0x0D50 
	char _0x0D54[48];
	float croushSpeed; //0x0D84 
	char _0x0D88[36];
	float jumpHeight; //0x0DAC 
	char _0x0DB0[300];
	float slideDistanceMult; //0x0EDC
};

class IGameRules
{
public:
	virtual void function0(); //
	virtual void function1(); //
	virtual void function2(); //
	virtual void function3(); //
	virtual void function4(); //
	virtual void function5(); //
	virtual void function6(); //
	virtual void function7(); // 
	virtual void function8(); //
	virtual void function9(); //
	virtual void function10(); //
	virtual void function11(); //
	virtual void function12(); //
	virtual void function13(); //
	virtual void function14(); //
	virtual void function15(); //
	virtual void function16(); //
	virtual void function17(); //
	virtual void function18(); //
	virtual void function19(); //
	virtual void function20(); //
	virtual void function21(); //
	virtual void function22(); //
	virtual void function23(); //
	virtual void function24(); //
	virtual void function25(); //
	virtual void function26(); //
	virtual void function27(); //
	virtual void function28(); //
	virtual void function29(); //
	virtual void function30(); //
	virtual void function31(); //
	virtual void function32(); //
	virtual void function33(); //
	virtual void function34(); //
	virtual void function35(); //
	virtual void function36(); //
	virtual void function37(); //
	virtual void function38(); //
	virtual void function39(); //
	virtual void function40(); //
	virtual void function41(); //
	virtual void function42(); //
	virtual void function43(); //
	virtual void function44(); //
	virtual void function45(); // 
	virtual void function46(); //
	virtual void function47(); //
	virtual void function48(); //
	virtual void function49(); //
	virtual void function50(); //
	virtual void function51(); //
	virtual void function52(); //
	virtual void function53(); //
	virtual void function54(); //
	virtual void function55(); //
	virtual void function56(); //
	virtual void function57(); //
	virtual void function58(); //
	virtual void function59(); //
	virtual void function60(); //
	virtual void function61(); //
	virtual void function62(); //
	virtual void function63(); //
	virtual void function64(); //
	virtual void function65(); //
	virtual void function66(); //
	virtual void function67(); //
	virtual void function68(); //
	virtual void function69(); //
	virtual void function70(); //
	virtual void function71(); //
	virtual void function72(); //
	virtual void function73(); //
	virtual void function74(); //
	virtual void function75(); //
	virtual void function76(); //
	virtual void function77(); //
	virtual void MovePlayer(IActor *pActor, const Vec3 &pos, const Quat &orientation); //virtual void function78(); // 
	virtual void RenamePlayer(IActor* pActor, const char* name); //virtual void function79(); // 
	virtual void function80(); // 
	virtual void function81(); // 
	virtual void function82(); // 
	virtual void function83(); // 
	virtual void function84(); // 
	virtual void function85(); //
	virtual void function86(); // 
	virtual void function87(); // 
	virtual void function88(); // 
	virtual void function89(); //
	virtual void function90(); // 
	virtual void function91(); // 
	virtual void function92(); // 
	virtual void function93(); // 
	virtual void function94(); // 
	virtual void function95(); //
	virtual void function96(); //
	virtual void function97(); //
	virtual void function98(); //
	virtual void function99(); //
	virtual void function100(); //
	virtual const char* GetTeamName(int teamId); //virtual void function101(); // 
	virtual void function102(); // 
	virtual void function103(); // 
	virtual void function104(); //
	virtual void function105(); // 
	virtual void function106(); // 
	virtual void function107(); // 
	virtual void function108(); //
	virtual void function109(); // 
	virtual void function110(); // 
	virtual int GetTeam(EntityId entityId) const; // virtual void function111(); // 
	virtual void function112(); // 
	virtual void function113(); //
};

class IGameFramework
{
public:
	virtual void function0(); //
	virtual void function1(); //
	virtual void function2(); //
	virtual void function3(); //
	virtual void function4(); //
	virtual void function5(); //
	virtual void function6(); //
	virtual void function7(); //
	virtual void function8(); //
	virtual void function9(); //
	virtual void function10(); //
	virtual void function11(); //
	virtual void function12(); //
	virtual void function13(); // 
	virtual void function14(); //
	virtual void function15(); //
	virtual void function16(); //
	virtual void function17(); //
	virtual void function18(); //
	virtual void function19(); //
	virtual void function20(); //
	virtual void function21(); //
	virtual void function22(); //
	virtual void function23(); //
	virtual void function24(); //
	virtual void function25(); //
	virtual void function26(); //
	virtual void function27(); //
	virtual void function28(); //
	virtual void function29(); //
	virtual void function30(); //
	virtual void function31(); //	
	virtual void function32(); //
	virtual void function33(); //
	virtual void function34(); //
	virtual void function35(); //
	virtual void function36(); //
	virtual void function37(); //
	virtual void function38(); // 
	virtual void function39(); //
	virtual void function40(); //
	virtual void function41(); //
	virtual void function42(); //
	virtual void function43(); //
	virtual void function44(); //
	virtual void function45(); // 
	virtual void function46(); //
	virtual void function47(); //
	virtual void function48(); //
	virtual void function49(); // 
	virtual void function50(); //
	virtual void function51(); //
	virtual void function52(); //
	virtual void function53(); //
	virtual void function54(); //
	virtual void function55(); //
	virtual void function56(); // 
	virtual void function57(); //
	virtual void function58(); //
	virtual void function59(); //
	virtual void function60(); //
	virtual void function61(); //
	virtual void function62(); //
	virtual void function63(); // 
	virtual void function64(); // 
	virtual void function65(); //
	virtual void function66(); //
	virtual void function67(); //
	virtual bool GetClientActor(IActor** pActor); // virtual void function68(); // 
	virtual void function69(); //
	virtual void function70(); //
	virtual void function71(); //
	virtual void function72(); //
	virtual void function73(); //
	virtual void function74(); //
	virtual void function75(); //
	virtual void function76(); //
	virtual void function77(); //
	virtual void function78(); //
	virtual void function79(); //
	virtual void function80(); // 
	virtual void function81(); //
	virtual void function82(); //
	virtual void function83(); // 
	virtual void function84(); //
	virtual void function85(); //
	virtual void function86(); //
	virtual void function87(); //
	virtual void function88(); // 
	virtual void function89(); // 
	virtual IGameRules *GetCurrentGameRules();// virtual void function90(); //
	virtual void function91(); //
	virtual void function92(); //
	virtual void function93(); //
	virtual void function94(); //
	virtual void function95(); //
	virtual void function96(); //
	virtual void function97(); //
	virtual void function98(); //
	virtual void function99(); //
	virtual void function100(); //
	virtual void function101(); //
	virtual void function102(); //
	virtual void function103(); //
	virtual void function104(); //
	virtual void function105(); //
	virtual void function106(); //
	virtual void function107(); //
	virtual void function108(); //
	virtual void function109(); //
	virtual void function110(); //
	virtual void function111(); //
	virtual void function112(); //
	virtual void function113(); //
	virtual void function114(); //
	virtual void function115(); //
	virtual void function116(); //
	virtual void function117(); //
	virtual void function118(); //
	virtual void function119(); //
	virtual void function120(); //
	virtual void function121(); //
	virtual void function122(); //
	virtual void function123(); //
	virtual void function124(); // 
	virtual void function125(); //
	virtual void function126(); //
	virtual void function127(); //
	virtual void function128(); //
	virtual IActorSystem * GetIActorSystem(); // virtual void function129(); //
	virtual void function130(); //
	virtual void function131(); //
	virtual void function132(); // 
	virtual void function133(); //
	virtual void function134(); //
	virtual void function135(); //
	virtual void function136(); //
	virtual void function137(); //
	virtual void function138(); //
	virtual void function139(); //
	virtual void function140(); // 
};

class IGame
{
public:
	char _0x0000[32];
	IGameFramework* getIGameFramework; //
};