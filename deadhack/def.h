#pragma once

#define   DISPSURF_FLAG_SURFACE           (1<<0)
#define   DISPSURF_FLAG_WALKABLE          (1<<1)
#define   DISPSURF_FLAG_BUILDABLE         (1<<2)
#define   DISPSURF_FLAG_SURFPROP1         (1<<3)
#define   DISPSURF_FLAG_SURFPROP2         (1<<4)

#define   CONTENTS_EMPTY                0

#define   CONTENTS_SOLID                0x1
#define   CONTENTS_WINDOW               0x2
#define   CONTENTS_AUX                  0x4
#define   CONTENTS_GRATE                0x8
#define   CONTENTS_SLIME                0x10
#define   CONTENTS_WATER                0x20
#define   CONTENTS_BLOCKLOS             0x40
#define   CONTENTS_OPAQUE               0x80
#define   LAST_VISIBLE_CONTENTS         CONTENTS_OPAQUE

#define   ALL_VISIBLE_CONTENTS            (LAST_VISIBLE_CONTENTS | (LAST_VISIBLE_CONTENTS-1))

#define   CONTENTS_TESTFOGVOLUME        0x100
#define   CONTENTS_UNUSED               0x200
#define   CONTENTS_BLOCKLIGHT           0x400
#define   CONTENTS_TEAM1                0x800
#define   CONTENTS_TEAM2                0x1000
#define   CONTENTS_IGNORE_NODRAW_OPAQUE 0x2000
#define   CONTENTS_MOVEABLE             0x4000
#define   CONTENTS_AREAPORTAL           0x8000
#define   CONTENTS_PLAYERCLIP           0x10000
#define   CONTENTS_MONSTERCLIP          0x20000
#define   CONTENTS_CURRENT_0            0x40000
#define   CONTENTS_CURRENT_90           0x80000
#define   CONTENTS_CURRENT_180          0x100000
#define   CONTENTS_CURRENT_270          0x200000
#define   CONTENTS_CURRENT_UP           0x400000
#define   CONTENTS_CURRENT_DOWN         0x800000

#define   CONTENTS_ORIGIN               0x1000000

#define   CONTENTS_MONSTER              0x2000000
#define   CONTENTS_DEBRIS               0x4000000
#define   CONTENTS_DETAIL               0x8000000
#define   CONTENTS_TRANSLUCENT          0x10000000
#define   CONTENTS_LADDER               0x20000000
#define   CONTENTS_HITBOX               0x40000000

#define   SURF_LIGHT                    0x0001
#define   SURF_SKY2D                    0x0002
#define   SURF_SKY                      0x0004
#define   SURF_WARP                     0x0008
#define   SURF_TRANS                    0x0010
#define   SURF_NOPORTAL                 0x0020
#define   SURF_TRIGGER                  0x0040
#define   SURF_NODRAW                   0x0080

#define   SURF_HINT                     0x0100

#define   SURF_SKIP                     0x0200
#define   SURF_NOLIGHT                  0x0400
#define   SURF_BUMPLIGHT                0x0800
#define   SURF_NOSHADOWS                0x1000
#define   SURF_NODECALS                 0x2000
#define   SURF_NOPAINT                  SURF_NODECALS
#define   SURF_NOCHOP                   0x4000
#define   SURF_HITBOX                   0x8000

// -----------------------------------------------------
// spatial content masks - used for spatial queries (traceline,etc.)
// -----------------------------------------------------
#define   MASK_ALL                      (0xFFFFFFFF)
#define   MASK_SOLID                    (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_MONSTER|CONTENTS_GRATE)
#define   MASK_PLAYERSOLID              (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_PLAYERCLIP|CONTENTS_WINDOW|CONTENTS_MONSTER|CONTENTS_GRATE)
#define   MASK_NPCSOLID                 (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTERCLIP|CONTENTS_WINDOW|CONTENTS_MONSTER|CONTENTS_GRATE)
#define   MASK_NPCFLUID                 (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTERCLIP|CONTENTS_WINDOW|CONTENTS_MONSTER)
#define   MASK_WATER                    (CONTENTS_WATER|CONTENTS_MOVEABLE|CONTENTS_SLIME)
#define   MASK_OPAQUE                   (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_OPAQUE)
#define   MASK_OPAQUE_AND_NPCS          (MASK_OPAQUE|CONTENTS_MONSTER)
#define   MASK_BLOCKLOS                 (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_BLOCKLOS)
#define   MASK_BLOCKLOS_AND_NPCS        (MASK_BLOCKLOS|CONTENTS_MONSTER)
#define   MASK_VISIBLE                  (MASK_OPAQUE|CONTENTS_IGNORE_NODRAW_OPAQUE)
#define   MASK_VISIBLE_AND_NPCS         (MASK_OPAQUE_AND_NPCS|CONTENTS_IGNORE_NODRAW_OPAQUE)
#define   MASK_SHOT                     (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTER|CONTENTS_WINDOW|CONTENTS_DEBRIS|CONTENTS_HITBOX)
#define   MASK_SHOT_BRUSHONLY           (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_DEBRIS)
#define   MASK_SHOT_HULL                (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTER|CONTENTS_WINDOW|CONTENTS_DEBRIS|CONTENTS_GRATE)
#define   MASK_SHOT_PORTAL              (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_MONSTER)
#define   MASK_SOLID_BRUSHONLY          (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_GRATE)
#define   MASK_PLAYERSOLID_BRUSHONLY    (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_PLAYERCLIP|CONTENTS_GRATE)
#define   MASK_NPCSOLID_BRUSHONLY       (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_MONSTERCLIP|CONTENTS_GRATE)
#define   MASK_NPCWORLDSTATIC           (CONTENTS_SOLID|CONTENTS_WINDOW|CONTENTS_MONSTERCLIP|CONTENTS_GRATE)
#define   MASK_NPCWORLDSTATIC_FLUID     (CONTENTS_SOLID|CONTENTS_WINDOW|CONTENTS_MONSTERCLIP)
#define   MASK_SPLITAREAPORTAL          (CONTENTS_WATER|CONTENTS_SLIME)
#define   MASK_CURRENT                  (CONTENTS_CURRENT_0|CONTENTS_CURRENT_90|CONTENTS_CURRENT_180|CONTENTS_CURRENT_270|CONTENTS_CURRENT_UP|CONTENTS_CURRENT_DOWN)
#define   MASK_DEADSOLID                (CONTENTS_SOLID|CONTENTS_PLAYERCLIP|CONTENTS_WINDOW|CONTENTS_GRATE)

#define TEXTURE_GROUP_LIGHTMAP						( "Lightmaps" )
#define TEXTURE_GROUP_WORLD							( "World textures" )
#define TEXTURE_GROUP_MODEL							( "Model textures" )
#define TEXTURE_GROUP_VGUI							( "VGUI textures" )
#define TEXTURE_GROUP_PARTICLE						( "Particle textures" )
#define TEXTURE_GROUP_DECAL							( "Decal textures" )
#define TEXTURE_GROUP_SKYBOX						( "SkyBox textures" )
#define TEXTURE_GROUP_CLIENT_EFFECTS				( "ClientEffect textures" )
#define TEXTURE_GROUP_OTHER							( "Other textures" )
#define TEXTURE_GROUP_PRECACHED						( "Precached" )
#define TEXTURE_GROUP_CUBE_MAP						( "CubeMap textures" )
#define TEXTURE_GROUP_RENDER_TARGET					( "RenderTargets" )
#define TEXTURE_GROUP_UNACCOUNTED					( "Unaccounted textures" )
#define TEXTURE_GROUP_STATIC_INDEX_BUFFER			( "Static Indices" )
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_DISP		( "Displacement Verts" )
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_COLOR	( "Lighting Verts" )
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_WORLD	( "World Verts" )
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_MODELS	( "Model Verts" )
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_OTHER	( "Other Verts" )
#define TEXTURE_GROUP_DYNAMIC_INDEX_BUFFER			( "Dynamic Indices" )
#define TEXTURE_GROUP_DYNAMIC_VERTEX_BUFFER			( "Dynamic Verts" )
#define TEXTURE_GROUP_DEPTH_BUFFER					( "DepthBuffer" )
#define TEXTURE_GROUP_VIEW_MODEL					( "ViewModel" )
#define TEXTURE_GROUP_PIXEL_SHADERS					( "Pixel Shaders" )
#define TEXTURE_GROUP_VERTEX_SHADERS				( "Vertex Shaders" )
#define TEXTURE_GROUP_RENDER_TARGET_SURFACE			( "RenderTarget Surfaces" )
#define TEXTURE_GROUP_MORPH_TARGETS					( "Morph Targets" )

#define TIME_TO_TICKS( dt )		( (int)( 0.5f + (float)( dt ) / g_csgo.m_global_vars->m_interval_per_tick ) )
#define TICKS_TO_TIME( dt )		( g_csgo.m_global_vars->m_interval_per_tick * (float)( dt ) )

#define FLOW_OUTGOING	0
#define FLOW_INCOMING	1
#define MAX_FLOWS		2		// in & out

class model_t;

struct mstudiobbox_t {
	int bone_index;
	int m_iGroup;
	Vec3_t bb_min;
	Vec3_t bb_max;
	int m_iHitboxNameIndex;
	int m_iPad01 [ 3 ];
	float m_flRadius;
	int m_iPad02 [ 4 ];

	const char *pszHitboxName() const {
		if( m_iHitboxNameIndex == 0 )
			return "";

		return ( reinterpret_cast< const char * >(this) + m_iHitboxNameIndex );
	}
};

struct mstudiohitboxset_t {
	int nameindex;

	const char *get_name() const {
		return ( (char *)this ) + nameindex;
	}

	int numhitboxes;
	int hitboxindex;

	mstudiobbox_t *pHitbox( int i ) const {
		return reinterpret_cast< mstudiobbox_t * >(( (unsigned char *)this ) + hitboxindex) + i;
	};
};

struct mstudiobone_t {
	int nameIndex;

	const char *get_name() const {
		return ( reinterpret_cast< const char * >(this) ) + nameIndex;
	}

	int parent;
	int bonecontroller [ 6 ];

	Vec3_t pos;
	float quat [ 4 ];
	Vec3_t rot;
	Vec3_t posscale;
	Vec3_t rotscale;

	matrix3x4_t poseToBone;
	float alignment [ 4 ];
	int flags;
	int proctype;
	int procindex;
	mutable int physicsbone;

	void *GetProcedure() const {
		if( procindex == 0 )
			return nullptr;
		return static_cast< void * >((unsigned char *)this + procindex);
	};
	int surfacepropidx;

	const char *get_surface_props() const {
		return ( (char *)this ) + surfacepropidx;
	}

	int contents;

	int unused [ 8 ];
};

struct studiohdr_t {
	int id;
	int version;
	int checksum;
	char name [ 64 ];
	int length;
	Vec3_t eyeposition;
	Vec3_t illumposition;
	Vec3_t hull_min;
	Vec3_t hull_max;
	Vec3_t view_bbmin;
	Vec3_t view_bbmax;
	int flags;
	int numbones;
	int boneindex;

	mstudiobone_t *pBone( int i ) const {
		return reinterpret_cast< mstudiobone_t * >((unsigned char *)this + boneindex) + i;
	};

	int numbonecontrollers;
	int bonecontrollerindex;
	int numhitboxsets;
	int hitboxsetindex;

	mstudiohitboxset_t *pHitboxSet( int i ) const {
		return reinterpret_cast< mstudiohitboxset_t * >(( (unsigned char *)this ) + hitboxsetindex) + i;
	}

	mstudiobbox_t *pHitbox( int i, int set ) const {
		const mstudiohitboxset_t *s = pHitboxSet( set );
		if( !s )
			return nullptr;

		return s->pHitbox( i );
	}

	int GetHitboxCount( int set ) const {
		const mstudiohitboxset_t *s = pHitboxSet( set );
		if( !s )
			return 0;

		return s->numhitboxes;
	}

	int numlocalanim;
	int localanimindex;
	int numlocalseq;
	int localseqindex;
	mutable int activitylistversion;
	mutable int eventsindexed;
	int numtextures;
	int textureindex;
	int numcdtextures;
	int cdtextureindex;
	int numskinref;
	int numskinfamilies;
	int skinindex;
	int numbodyparts;
	int bodypartindex;
	int numlocalattachments;
	int localattachmentindex;
	int numlocalnodes;
	int localnodeindex;
	int localnodenameindex;
	int numflexdesc;
	int flexdescindex;
	int numflexcontrollers;
	int flexcontrollerindex;
	int numflexrules;
	int flexruleindex;
	int numikchains;
	int ikchainindex;
	int nummouths;
	int mouthindex;
	int numlocalposeparameters;
	int localposeparamindex;
	int surfacepropindex;
	int keyvalueindex;
	int keyvaluesize;
	int numlocalikautoplaylocks;
	int localikautoplaylockindex;
	float mass;
	int contents;
	int numincludemodels;
	int includemodelindex;
	mutable void *virtualModel;
	int szanimblocknameindex;
	int numanimblocks;
	int animblockindex;
	mutable void *animblockModel;
	int bonetablebynameindex;
	void *pVertexBase;
	void *pIndexBase;
	unsigned char constdirectionallightdot;
	unsigned char rootLOD;
	unsigned char numAllowedRootLODs;
	PAD( 0x5 );
	int numflexcontrollerui;
	int flexcontrolleruiindex;
	float flVertAnimFixedPointScale;
	PAD( 0x4 );
	int studiohdr2index;
	PAD( 0x4 );
};

enum class TraceType_t {
	TRACE_EVERYTHING = 0,
	TRACE_WORLD_ONLY,
	TRACE_ENTITIES_ONLY,
	TRACE_EVERYTHING_FILTER_PROPS,
};

enum OverrideType_t {
	OVERRIDE_NORMAL = 0,
	OVERRIDE_BUILD_SHADOWS,
	OVERRIDE_DEPTH_WRITE,
};

enum LightType_t {
	MATERIAL_LIGHT_DISABLE = 0,
	MATERIAL_LIGHT_POINT,
	MATERIAL_LIGHT_DIRECTIONAL,
	MATERIAL_LIGHT_SPOT,
};

struct LightDesc_t {
	LightType_t m_Type; //< MATERIAL_LIGHT_xxx
	Vec3_t m_Color; //< color+intensity 
	Vec3_t m_Position; //< light source center position
	Vec3_t m_Direction; //< for SPOT, direction it is pointing
	float m_Range; //< distance range for light.0=infinite
	float m_Falloff; //< angular falloff exponent for spot lights
	float m_Attenuation0; //< constant distance falloff term
	float m_Attenuation1; //< linear term of falloff
	float m_Attenuation2; //< quadatic term of falloff
	float m_Theta; //< inner cone angle. no angular falloff 
	//< within this cone
	float m_Phi; //< outer cone angle

	// the values below are derived from the above settings for optimizations
	// These aren't used by DX8. . used for software lighting.
	float m_ThetaDot;
	float m_PhiDot;
	unsigned int m_Flags;
protected:
	float OneOver_ThetaDot_Minus_PhiDot;
	float m_RangeSquared;
public:
};

struct DrawModelInfo_t {
	studiohdr_t *m_pStudioHdr;
	void *m_pHardwareData;
	void *m_Decals;
	int m_Skin;
	int m_Body;
	int m_HitboxSet;
	DWORD *m_pClientEntity;
	int m_Lod;
	void *m_pColorMeshes;
	bool m_bStaticLighting;
	Vec3_t m_vecAmbientCube[6]; // ambient, and lights that aren't in locallight[]
	int m_nLocalLightCount;
	LightDesc_t m_LocalLightDescs[4];
};

struct cplane_t {
	Vec3_t m_normal;
	float m_dist;
	BYTE m_type;
	BYTE m_sign_bits;
	BYTE m_pad[ 2 ];
};

struct csurface_t {
	const char *m_name;
	short m_surface_props;
	unsigned short m_flags;
};

//-----------------------------------------------------------------------------
// DrawModel flags
//-----------------------------------------------------------------------------
enum {
	STUDIORENDER_DRAW_ENTIRE_MODEL = 0,
	STUDIORENDER_DRAW_OPAQUE_ONLY = 0x01,
	STUDIORENDER_DRAW_TRANSLUCENT_ONLY = 0x02,
	STUDIORENDER_DRAW_GROUP_MASK = 0x03,

	STUDIORENDER_DRAW_NO_FLEXES = 0x04,
	STUDIORENDER_DRAW_STATIC_LIGHTING = 0x08,

	STUDIORENDER_DRAW_ACCURATETIME = 0x10, // Use accurate timing when drawing the model.
	STUDIORENDER_DRAW_NO_SHADOWS = 0x20,
	STUDIORENDER_DRAW_GET_PERF_STATS = 0x40,

	STUDIORENDER_DRAW_WIREFRAME = 0x80,

	STUDIORENDER_DRAW_ITEM_BLINK = 0x100,

	STUDIORENDER_SHADOWDEPTHTEXTURE = 0x200,

	STUDIORENDER_SSAODEPTHTEXTURE = 0x1000,

	STUDIORENDER_GENERATE_STATS = 0x8000,
};

enum Flag {
	FL_ONGROUND = ( 1 << 0 ),
	FL_DUCKING = ( 1 << 1 ),
	FL_WATERJUMP = ( 1 << 2 ),
	FL_ONTRAIN = ( 1 << 3 ),
	FL_INRAIN = ( 1 << 4 ),
	FL_FROZEN = ( 1 << 5 ),
	FL_ATCONTROLS = ( 1 << 6 ),
	FL_CLIENT = ( 1 << 7 ),
	FL_FAKECLIENT = ( 1 << 8 ),
};

enum Hitboxes {
	HITBOX_INVALID = -1,
	HITBOX_HEAD,
	HITBOX_NECK,
	HITBOX_LOWER_NECK,
	HITBOX_PELVIS,
	HITBOX_BODY,
	HITBOX_THORAX,
	HITBOX_CHEST,
	HITBOX_UPPER_CHEST,
	HITBOX_RIGHT_THIGH,
	HITBOX_LEFT_THIGH,
	HITBOX_RIGHT_CALF,
	HITBOX_LEFT_CALF,
	HITBOX_RIGHT_FOOT,
	HITBOX_LEFT_FOOT,
	HITBOX_RIGHT_HAND,
	HITBOX_LEFT_HAND,
	HITBOX_RIGHT_UPPER_ARM,
	HITBOX_RIGHT_FOREARM,
	HITBOX_LEFT_UPPER_ARM,
	HITBOX_LEFT_FOREARM,
	HITBOX_MAX
};

enum WeaponType {
	WEAPON_TYPE_INVALID = -1,
	WEAPON_TYPE_PISTOLS,
	WEAPON_TYPE_TASER,
	WEAPON_TYPE_SHOTGUN,
	WEAPON_TYPE_SMG,
	WEAPON_TYPE_RIFLE,
	WEAPON_TYPE_MG,
	WEAPON_TYPE_SNIPER,
	WEAPON_TYPE_GRENADE,
	WEAPON_TYPE_KNIFE,
};

enum Weapon {
	ITEM_NONE = 0,
	WEAPON_DEAGLE = 1,
	WEAPON_DUALS = 2,
	WEAPON_FIVE7 = 3,
	WEAPON_GLOCK = 4,
	WEAPON_AK47 = 7,
	WEAPON_AUG = 8,
	WEAPON_AWP = 9,
	WEAPON_FAMAS = 10,
	WEAPON_G3SG1 = 11,
	WEAPON_GALIL = 13,
	WEAPON_M249 = 14,
	WEAPON_M4A1 = 16,
	WEAPON_MAC10 = 17,
	WEAPON_P90 = 19,
	WEAPON_UMP45 = 24,
	WEAPON_XM1014 = 25,
	WEAPON_BIZON = 26,
	WEAPON_MAG7 = 27,
	WEAPON_NEGEV = 28,
	WEAPON_SAWEDOFF = 29,
	WEAPON_TEC9 = 30,
	WEAPON_TASER = 31,
	WEAPON_P2000 = 32,
	WEAPON_MP7 = 33,
	WEAPON_MP9 = 34,
	WEAPON_NOVA = 35,
	WEAPON_P250 = 36,
	WEAPON_SCAR20 = 38,
	WEAPON_SG553 = 39,
	WEAPON_SCOUT = 40,
	WEAPON_KNIFE_T = 42,
	WEAPON_FLASH = 43,
	WEAPON_HE = 44,
	WEAPON_SMOKE = 45,
	WEAPON_MOLOTOV = 46,
	WEAPON_DECOY = 47,
	WEAPON_INC = 48,
	WEAPON_C4 = 49,
	WEAPON_KNIFE_CT = 59,
	WEAPON_M4A1S = 60,
	WEAPON_USPS = 61,
	WEAPON_CZ75 = 63,
	WEAPON_REVOLVER = 64,
	WEAPON_KNIFE_BAYONET = 500,
	WEAPON_KNIFE_FLIP = 505,
	WEAPON_KNIFE_GUT = 506,
	WEAPON_KNIFE_KARAMBIT = 507,
	WEAPON_KNIFE_M9_BAYONET = 508,
	WEAPON_KNIFE_TACTICAL = 509,
	WEAPON_KNIFE_FALCHION = 512,
	WEAPON_KNIFE_SURVIVAL_BOWIE = 514,
	WEAPON_KNIFE_BUTTERFLY = 515,
	WEAPON_KNIFE_PUSH = 516,
	GLOVE_STUDDED_BLOODHOUND = 5027,
	GLOVE_T_SIDE = 5028,
	GLOVE_CT_SIDE = 5029,
	GLOVE_SPORTY = 5030,
	GLOVE_SLICK = 5031,
	GLOVE_LEATHER_WRAP = 5032,
	GLOVE_MOTORCYCLE = 5033,
	GLOVE_SPECIALIST = 5034
};

enum MoveTypes {
	MOVETYPE_NONE = 0, // never moves
	MOVETYPE_ISOMETRIC, // For players -- in TF2 commander view, etc.
	MOVETYPE_WALK, // player only - moving on the ground
	MOVETYPE_STEP, // gravity, special edge handling -- monsters use this
	MOVETYPE_FLY, // No gravity, but still collides with stuff
	MOVETYPE_FLYGRAVITY, // flies through the air + is affected by gravity
	MOVETYPE_VPHYSICS, // uses VPHYSICS for simulation
	MOVETYPE_PUSH, // no clip to world, push and crush
	MOVETYPE_NOCLIP, // No gravity, no collisions, still do velocity/avelocity
	MOVETYPE_LADDER, // Used by players only when going onto a ladder
	MOVETYPE_OBSERVER, // Observer movement, depends on player's observer mode
	MOVETYPE_CUSTOM, // Allows the entity to describe its own physics
	MOVETYPE_LAST = MOVETYPE_CUSTOM, // should always be defined as the last item in the list
	MOVETYPE_MAX_BITS = 4
};

enum Hitgroups {
	HITGROUP_INVALID = -1,
	HITGROUP_GENERIC,
	HITGROUP_HEAD,
	HITGROUP_CHEST,
	HITGROUP_STOMACH,
	HITGROUP_LEFTARM,
	HITGROUP_RIGHTARM,
	HITGROUP_LEFTLEG,
	HITGROUP_RIGHTLEG,
	HITGROUP_GEAR = 10
};

enum ClassID {
	CAI_BaseNPC,
	CAK47,
	CBaseAnimating,
	CBaseAnimatingOverlay,
	CBaseAttributableItem,
	CBaseButton,
	CBaseCombatCharacter,
	CBaseCombatWeapon,
	CBaseCSGrenade,
	CBaseCSGrenadeProjectile,
	CBaseDoor,
	CBaseEntity,
	CBaseFlex,
	CBaseGrenade,
	CBaseParticleEntity,
	CBasePlayer,
	CBasePropDoor,
	CBaseTeamObjectiveResource,
	CBaseTempEntity,
	CBaseToggle,
	CBaseTrigger,
	CBaseViewModel,
	CBaseVPhysicsTrigger,
	CBaseWeaponWorldModel,
	CBeam,
	CBeamSpotlight,
	CBoneFollower,
	CBreakableProp,
	CBreakableSurface,
	CC4,
	CCascadeLight,
	CChicken,
	CColorCorrection,
	CColorCorrectionVolume,
	CCSGameRulesProxy,
	CCSPLAYER,
	CCSPlayerResource,
	CCSRagdoll,
	CCSTeam,
	CDEagle,
	CDecoyGrenade,
	CDecoyProjectile,
	CDynamicLight,
	CDynamicProp,
	CEconEntity,
	CEconWearable,
	CEmbers,
	CEntityDissolve,
	CEntityFlame,
	CEntityFreezing,
	CEntityParticleTrail,
	CEnvAmbientLight,
	CEnvDetailController,
	CEnvDOFController,
	CEnvParticleScript,
	CEnvProjectedTexture,
	CEnvQuadraticBeam,
	CEnvScreenEffect,
	CEnvScreenOverlay,
	CEnvTonemapController,
	CEnvWind,
	CFEPlayerDecal,
	CFireCrackerBlast,
	CFireSmoke,
	CFireTrail,
	CFish,
	CFlashbang,
	CFogController,
	CFootstepControl,
	CFunc_Dust,
	CFunc_LOD,
	CFuncAreaPortalWindow,
	CFuncBrush,
	CFuncConveyor,
	CFuncLadder,
	CFuncMonitor,
	CFuncMoveLinear,
	CFuncOccluder,
	CFuncReflectiveGlass,
	CFuncRotating,
	CFuncSmokeVolume,
	CFuncTrackTrain,
	CGameRulesProxy,
	CHandleTest,
	CHEGrenade,
	CHostage,
	CHostageCarriableProp,
	CIncendiaryGrenade,
	CInferno,
	CInfoLadderDismount,
	CInfoOverlayAccessor,
	CItem_Healthshot,
	CItemDogtags,
	CKnife,
	CKnifeGG,
	CLightGlow,
	CMaterialModifyControl,
	CMolotovGrenade,
	CMolotovProjectile,
	CMovieDisplay,
	CParticleFire,
	CParticlePerformanceMonitor,
	CParticleSystem,
	CPhysBox,
	CPhysBoxMultiplayer,
	CPhysicsProp,
	CPhysicsPropMultiplayer,
	CPhysMagnet,
	CPlantedC4,
	CPlasma,
	CPlayerResource,
	CPointCamera,
	CPointCommentaryNode,
	CPointWorldText,
	CPoseController,
	CPostProcessController,
	CPrecipitation,
	CPrecipitationBlocker,
	CPredictedViewModel,
	CProp_Hallucination,
	CPropDoorRotating,
	CPropJeep,
	CPropVehicleDriveable,
	CRagdollManager,
	CRagdollProp,
	CRagdollPropAttached,
	CRopeKeyframe,
	CSCAR17,
	CSceneEntity,
	CSensorGrenade,
	CSensorGrenadeProjectile,
	CShadowControl,
	CSlideshowDisplay,
	CSmokeGrenade,
	CSmokeGrenadeProjectile,
	CSmokeStack,
	CSpatialEntity,
	CSpotlightEnd,
	CSprite,
	CSpriteOriented,
	CSpriteTrail,
	CStatueProp,
	CSteamJet,
	CSun,
	CSunlightShadowControl,
	CTeam,
	CTeamplayRoundBasedRulesProxy,
	CTEArmorRicochet,
	CTEBaseBeam,
	CTEBeamEntPoint,
	CTEBeamEnts,
	CTEBeamFollow,
	CTEBeamLaser,
	CTEBeamPoints,
	CTEBeamRing,
	CTEBeamRingPoint,
	CTEBeamSpline,
	CTEBloodSprite,
	CTEBloodStream,
	CTEBreakModel,
	CTEBSPDecal,
	CTEBubbles,
	CTEBubbleTrail,
	CTEClientProjectile,
	CTEDecal,
	CTEDust,
	CTEDynamicLight,
	CTEEffectDispatch,
	CTEEnergySplash,
	CTEExplosion,
	CTEFireBullets,
	CTEFizz,
	CTEFootprintDecal,
	CTEFoundryHelpers,
	CTEGaussExplosion,
	CTEGlowSprite,
	CTEImpact,
	CTEKillPlayerAttachments,
	CTELargeFunnel,
	CTEMetalSparks,
	CTEMuzzleFlash,
	CTEParticleSystem,
	CTEPhysicsProp,
	CTEPlantBomb,
	CTEPlayerAnimEvent,
	CTEPlayerDecal,
	CTEProjectedDecal,
	CTERadioIcon,
	CTEShatterSurface,
	CTEShowLine,
	CTesla,
	CTESmoke,
	CTESparks,
	CTESprite,
	CTESpriteSpray,
	CTest_ProxyToggle_Networkable,
	CTestTraceline,
	CTEWorldDecal,
	CTriggerPlayerMovement,
	CTriggerSoundOperator,
	CVGuiScreen,
	CVoteController,
	CWaterBullet,
	CWaterLODControl,
	CWeaponAug,
	CWeaponAWP,
	CWeaponBaseItem,
	CWeaponBizon,
	CWeaponCSBase,
	CWeaponCSBaseGun,
	CWeaponCycler,
	CWeaponElite,
	CWeaponFamas,
	CWeaponFiveSeven,
	CWeaponG3SG1,
	CWeaponGalil,
	CWeaponGalilAR,
	CWeaponGlock,
	CWeaponHKP2000,
	CWeaponM249,
	CWeaponM3,
	CWeaponM4A1,
	CWeaponMAC10,
	CWeaponMag7,
	CWeaponMP5Navy,
	CWeaponMP7,
	CWeaponMP9,
	CWeaponNegev,
	CWeaponNOVA,
	CWeaponP228,
	CWeaponP250,
	CWeaponP90,
	CWeaponSawedoff,
	CWeaponSCAR20,
	CWeaponScout,
	CWeaponSG550,
	CWeaponSG552,
	CWeaponSG556,
	CWeaponSSG08,
	CWeaponTaser,
	CWeaponTec9,
	CWeaponTMP,
	CWeaponUMP45,
	CWeaponUSP,
	CWeaponXM1014,
	CWorld,
	DustTrail,
	MovieExplosion,
	ParticleSmokeGrenade,
	RocketTrail,
	SmokeTrail,
	SporeExplosion,
	SporeTrail
};

enum MaterialFlags_t {
	MATERIAL_VAR_DEBUG = 1,
	MATERIAL_VAR_NO_DEBUG_OVERRIDE = 2,
	MATERIAL_VAR_NO_DRAW = 4,
	MATERIAL_VAR_USE_IN_FILLRATE_MODE = 8,
	MATERIAL_VAR_VERTEXCOLOR = 16,
	MATERIAL_VAR_VERTEXALPHA = 32,
	MATERIAL_VAR_SELFILLUM = 64,
	MATERIAL_VAR_ADDITIVE = 128,
	MATERIAL_VAR_ALPHATEST = 256,
	// MATERIAL_VAR_UNUSED = 512,
	MATERIAL_VAR_ZNEARER = 1024,
	MATERIAL_VAR_MODEL = 2048,
	MATERIAL_VAR_FLAT = 4096,
	MATERIAL_VAR_NOCULL = 8192,
	MATERIAL_VAR_NOFOG = 16384,
	MATERIAL_VAR_IGNOREZ = 32768,
	MATERIAL_VAR_DECAL = 65536,
	MATERIAL_VAR_ENVMAPSPHERE = 131072, // OBSOLETE
	// MATERIAL_VAR_UNUSED = 262144,
	MATERIAL_VAR_ENVMAPCAMERASPACE = 524288, // OBSOLETE
	MATERIAL_VAR_BASEALPHAENVMAPMASK = 1048576,
	MATERIAL_VAR_TRANSLUCENT = 2097152,
	MATERIAL_VAR_NORMALMAPALPHAENVMAPMASK = 4194304,
	MATERIAL_VAR_NEEDS_SOFTWARE_SKINNING = 8388608, // OBSOLETE
	MATERIAL_VAR_OPAQUETEXTURE = 16777216,
	MATERIAL_VAR_ENVMAPMODE = 33554432, // OBSOLETE
	MATERIAL_VAR_SUPPRESS_DECALS = 67108864,
	MATERIAL_VAR_HALFLAMBERT = 134217728,
	MATERIAL_VAR_WIREFRAME = 268435456,
	MATERIAL_VAR_ALLOWALPHATOCOVERAGE = 536870912,
	MATERIAL_VAR_ALPHA_MODIFIED_BY_PROXY = 1073741824,
	// MATERIAL_VAR_VERTEXFOG = -2147483648,
};

struct ModelRenderInfo_t {
	Vec3_t m_origin;
	Vec3_t m_angles;
	void *m_renderable;
	const void *m_model;
	const matrix3x4_t *m_model_to_world;
	const matrix3x4_t *m_lighting_offset;
	const Vec3_t *m_lighting_origin;
	int m_flags;
	int m_entity_index;
	int m_skin;
	int m_body;
	int m_hitboxset;
	unsigned short m_instance;
};

class CFlashLightEffect {
public:
	bool m_bIsOn; //0x0000 
	char pad_0x0001[0x3]; //0x0001
	int m_nEntIndex; //0x0004 
	WORD m_FlashLightHandle; //0x0008 
	char pad_0x000A[0x2]; //0x000A
	float m_flMuzzleFlashBrightness; //0x000C 
	float m_flFov; //0x0010 
	float m_flFarZ; //0x0014 
	float m_flLinearAtten; //0x0018 
	bool m_bCastsShadows; //0x001C 
	char pad_0x001D[0x3]; //0x001D
	float m_flCurrentPullBackDist; //0x0020 
	DWORD m_MuzzleFlashTexture; //0x0024 
	DWORD m_FlashLightTexture; //0x0028 
	char m_szTextureName[64]; //0x1559888 
}; //Size=0x006C

class KeyValues {
public:
	PAD( 32 )
};

class AnimationLayer_t {
public:
	PAD( 20 )
	uint32_t m_nOrder;
	uint32_t m_nSequence;
	float m_flPrevCycle;
	float m_flWeight;
	float m_flWeightDeltaRate;
	float m_flPlaybackRate;
	float m_flCycle;
	void *m_pOwner;
	char pad_0038[ 4 ];
};

struct MaterialVideoMode_t {
	int m_Width;
	int m_Height;
	int m_Format;
	int m_RefreshRate;
};

struct MaterialSystem_Config_t {
	MaterialVideoMode_t m_VideoMode;
	float m_fMonitorGamma;
	float m_fGammaTVRangeMin;
	float m_fGammaTVRangeMax;
	float m_fGammaTVExponent;
	bool m_bGammaTVEnabled;
	bool m_bTripleBuffered;
	int m_nAASamples;
	int m_nForceAnisotropicLevel;
	int m_nSkipMipLevels;
	int m_nDxSupportLevel;
	int m_nFlags;
	bool m_bEditMode;
	char m_nProxiesTestMode;
	bool m_bCompressedTextures;
	bool m_bFilterLightmaps;
	bool m_bFilterTextures;
	bool m_bReverseDepth;
	bool m_bBufferPrimitives;
	bool m_bDrawFlat;
	bool m_bMeasureFillRate;
	bool m_bVisualizeFillRate;
	bool m_bNoTransparency;
	bool m_bSoftwareLighting;
	bool m_bAllowCheats;
	char m_nShowMipLevels;
	bool m_bShowLowResImage;
	bool m_bShowNormalMap;
	bool m_bMipMapTextures;
	char m_nFullbright;
	bool m_bFastNoBump;
	bool m_bSuppressRendering;
	bool m_bDrawGray;
	bool m_bShowSpecular;
	bool m_bShowDiffuse;
	int m_nWindowedSizeLimitWidth;
	int m_nWindowedSizeLimitHeight;
	int m_nAAQuality;
	bool m_bShadowDepthTexture;
	bool m_bMotionBlur;
	bool m_bSupportFlashlight;
	bool m_bPaintEnabled;
	PAD( 12 )
};
