#pragma once

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

enum OverrideType {
	OVERRIDE_NORMAL = 0,
	OVERRIDE_BUILD_SHADOWS = 1,
	OVERRIDE_DEPTH_WRITE = 2,
	OVERRIDE_WHATEVER = 3
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
	Vec3_t               m_origin;
	Vec3_t               m_angles;
	void                 *m_renderable;
	const void           *m_model;
	const matrix3x4_t    *m_model_to_world;
	const matrix3x4_t    *m_lighting_offset;
	const Vec3_t         *m_lighting_origin;
	int                  m_flags;
	int                  m_entity_index;
	int                  m_skin;
	int                  m_body;
	int                  m_hitboxset;
	unsigned short       m_instance;
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

class AnimationLayer {
public:
	PAD( 20 )
	uint32_t    m_nOrder;
	uint32_t    m_nSequence;
	float       m_flPrevCycle;
	float       m_flWeight;
	float       m_flWeightDeltaRate;
	float       m_flPlaybackRate;
	float       m_flCycle;
	void        *m_pOwner;
	char        pad_0038[ 4 ];
};

struct MaterialVideoMode_t  {
	int    m_Width;
	int    m_Height;
	int    m_Format;
	int    m_RefreshRate;
};

struct MaterialSystem_Config_t  {
	MaterialVideoMode_t    m_VideoMode;
	float                  m_fMonitorGamma;
	float                  m_fGammaTVRangeMin;
	float                  m_fGammaTVRangeMax;
	float                  m_fGammaTVExponent;
	bool                   m_bGammaTVEnabled;
	bool                   m_bTripleBuffered;
	int                    m_nAASamples;
	int                    m_nForceAnisotropicLevel;
	int                    m_nSkipMipLevels;
	int                    m_nDxSupportLevel;
	int                    m_nFlags;
	bool                   m_bEditMode;
	char                   m_nProxiesTestMode;
	bool                   m_bCompressedTextures;
	bool                   m_bFilterLightmaps;
	bool                   m_bFilterTextures;
	bool                   m_bReverseDepth;
	bool                   m_bBufferPrimitives;
	bool                   m_bDrawFlat;
	bool                   m_bMeasureFillRate;
	bool                   m_bVisualizeFillRate;
	bool                   m_bNoTransparency;
	bool                   m_bSoftwareLighting;
	bool                   m_bAllowCheats;
	char                   m_nShowMipLevels;
	bool                   m_bShowLowResImage;
	bool                   m_bShowNormalMap;
	bool                   m_bMipMapTextures;
	char                   m_nFullbright;
	bool                   m_bFastNoBump;
	bool                   m_bSuppressRendering;
	bool                   m_bDrawGray;
	bool                   m_bShowSpecular;
	bool                   m_bShowDiffuse;
	int                    m_nWindowedSizeLimitWidth;
	int                    m_nWindowedSizeLimitHeight;
	int                    m_nAAQuality;
	bool                   m_bShadowDepthTexture;
	bool                   m_bMotionBlur;
	bool                   m_bSupportFlashlight;
	bool                   m_bPaintEnabled;
	PAD( 12 )
};