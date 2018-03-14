#pragma once

class Offsets {
private:
public:
	size_t m_PushNotification;
	size_t m_InitKeyValues;
	size_t m_LoadFromBuffer;
	size_t m_LoadNamedSky;
	size_t m_SetClanTag;
	size_t m_ServerRankRevealAll;
	size_t m_OverridePostProcessingDisable;
	size_t m_LineGoesThruSmoke;
	size_t m_GlowObjectManager;
	size_t m_UTILClipTraceToPlayers;

	size_t m_iHealth;
    size_t m_flSimulationTime;
	size_t m_bGunGameImmunity;
	size_t m_bHasHelmet;
	size_t m_bHasDefuser;
	size_t m_bIsDefusing;
	size_t m_iShotsFired;
	size_t m_nHitboxSet;

	size_t m_iTeamNum;
	size_t m_CollisionGroup;
	size_t m_rgflCoordinateFrame;
	size_t m_vecOrigin;
	size_t m_hOwnerEntity;

	size_t m_iAccount;
	size_t m_ArmorValue;
	size_t m_bIsScoped;
	size_t m_hActiveWeapon;
	size_t m_iClip1;
	size_t m_BombTimer;
	size_t m_iItemDefinitionIndex;

	size_t m_bBombTicking;
	size_t m_bBombDefused;
	size_t m_flC4Blow;
	size_t m_flDefuseCountDown;

	size_t m_nMaterial;
	size_t m_vecViewOffset;
	size_t m_nTickBase;
	size_t m_fFlags;
	size_t m_flPoseParameter;
	size_t m_hObserverTarget;
	size_t m_flThrowStrength;
	size_t m_bPinPulled;
	size_t m_vecVelocity;
	size_t m_bSpotted;
	size_t m_aimPunchAngle;
	size_t m_flFlashMaxAlpha;
	size_t m_flFlashDuration;
	size_t m_flNextAttack;

	bool init() {
		m_PushNotification = SigScan::find( CT_HASH32( "engine.dll" ), "55 8B EC 81 EC ? ? ? ? 80 3D ? ? ? ? ? 56 8B 35" );
		if( !m_PushNotification )
			return false;

		m_InitKeyValues = SigScan::find( CT_HASH32( "client.dll" ), "68 ? ? ? ? 8B C8 E8 ? ? ? ? 89 45 FC EB 07 C7 45 ? ? ? ? ? 8B 03 56" ) + 7;
		if( !m_InitKeyValues )
			return false;

		m_LoadFromBuffer = SigScan::find( CT_HASH32( "client.dll" ), "55 8B EC 83 E4 F8 83 EC 34 53 8B 5D 0C 89 4C 24 04" );
		if( !m_LoadFromBuffer )
			return false;

		m_LoadNamedSky = SigScan::find( CT_HASH32( "engine.dll" ), "55 8B EC 81 EC ? ? ? ? 56 57 8B F9 C7 45" );
		if( !m_LoadNamedSky )
			return false;

		m_SetClanTag = SigScan::find( CT_HASH32( "engine.dll" ), "53 56 57 8B DA 8B F9 FF 15" );
		if( !m_SetClanTag )
			return false;

		m_ServerRankRevealAll = SigScan::find( CT_HASH32( "client.dll" ), "55 8B EC 8B 0D ? ? ? ? 68" );
		if( !m_ServerRankRevealAll )
			return false;

		m_OverridePostProcessingDisable = *(ulong_t *)( SigScan::find( CT_HASH32( "client.dll" ), "80 3D ? ? ? ? ? 53 56 57 0F 85" ) + 2 );
		if( !m_OverridePostProcessingDisable )
			return false;

		m_LineGoesThruSmoke = SigScan::find( CT_HASH32( "client.dll" ), "55 8B EC 83 EC 08 8B 15 ? ? ? ? 0F 57 C0" );
		if( !m_LineGoesThruSmoke )
			return false;

		m_GlowObjectManager = SigScan::find( CT_HASH32( "client.dll" ), "0F 11 05 ? ? ? ? 83 C8 01" );
		if( !m_GlowObjectManager )
			return false;
		m_GlowObjectManager += 3;

		m_UTILClipTraceToPlayers = SigScan::find( CT_HASH32( "client.dll" ), "53 8B DC 83 EC 08 83 E4 F0 83 C4 04 55 8B 6B 04 89 6C 24 04 8B EC 81 EC ? ? ? ? 8B 43 10" );
		if( !m_UTILClipTraceToPlayers )
			return false;

		m_iHealth          = g_netvars.get( CT_HASH32( "DT_BasePlayer" ), CT_HASH32( "m_iHealth" ) );
        m_flSimulationTime = g_netvars.get( CT_HASH32( "DT_BasePlayer" ), CT_HASH32( "m_flSimulationTime" ) );
		m_vecViewOffset    = g_netvars.get( CT_HASH32( "DT_BasePlayer" ), CT_HASH32( "m_vecViewOffset[0]" ) );
		m_nTickBase        = g_netvars.get( CT_HASH32( "DT_BasePlayer" ), CT_HASH32( "m_nTickBase" ) );
		m_fFlags           = g_netvars.get( CT_HASH32( "DT_BasePlayer" ), CT_HASH32( "m_fFlags" ) );
		m_hObserverTarget  = g_netvars.get( CT_HASH32( "DT_BasePlayer" ), CT_HASH32( "m_hObserverTarget" ) );
		m_vecVelocity      = g_netvars.get( CT_HASH32( "DT_BasePlayer" ), CT_HASH32( "m_vecVelocity[0]" ) );
		m_aimPunchAngle    = g_netvars.get( CT_HASH32( "DT_BasePlayer" ), CT_HASH32( "m_aimPunchAngle" ) );

		m_bGunGameImmunity = g_netvars.get( CT_HASH32( "DT_CSPlayer" ), CT_HASH32( "m_bGunGameImmunity" ) );
		m_bHasHelmet       = g_netvars.get( CT_HASH32( "DT_CSPlayer" ), CT_HASH32( "m_bHasHelmet" ) );
		m_bHasDefuser      = g_netvars.get( CT_HASH32( "DT_CSPlayer" ), CT_HASH32( "m_bHasDefuser" ) );
		m_iAccount         = g_netvars.get( CT_HASH32( "DT_CSPlayer" ), CT_HASH32( "m_iAccount" ) );
		m_ArmorValue       = g_netvars.get( CT_HASH32( "DT_CSPlayer" ), CT_HASH32( "m_ArmorValue" ) );
		m_bIsScoped        = g_netvars.get( CT_HASH32( "DT_CSPlayer" ), CT_HASH32( "m_bIsScoped" ) );
		m_bIsDefusing      = g_netvars.get( CT_HASH32( "DT_CSPlayer" ), CT_HASH32( "m_bIsDefusing" ) );
		m_flFlashMaxAlpha  = g_netvars.get( CT_HASH32( "DT_CSPlayer" ), CT_HASH32( "m_flFlashMaxAlpha" ) );
		m_flFlashDuration  = g_netvars.get( CT_HASH32( "DT_CSPlayer" ), CT_HASH32( "m_flFlashDuration" ) );
		m_iShotsFired      = g_netvars.get( CT_HASH32( "DT_CSPlayer" ), CT_HASH32( "m_iShotsFired" ) );

		m_iTeamNum            = g_netvars.get( CT_HASH32( "DT_BaseEntity" ), CT_HASH32( "m_iTeamNum" ) );
		m_CollisionGroup      = g_netvars.get( CT_HASH32( "DT_BaseEntity" ), CT_HASH32( "m_CollisionGroup" ) );
		m_rgflCoordinateFrame = m_CollisionGroup - 0x30;
		m_vecOrigin           = g_netvars.get( CT_HASH32( "DT_BaseEntity" ), CT_HASH32( "m_vecOrigin" ) );
		m_hOwnerEntity        = g_netvars.get( CT_HASH32( "DT_BaseEntity" ), CT_HASH32( "m_hOwnerEntity" ) );
		m_bSpotted            = g_netvars.get( CT_HASH32( "DT_BaseEntity" ), CT_HASH32( "m_bSpotted" ) );

		m_hActiveWeapon = g_netvars.get( CT_HASH32( "DT_BaseCombatCharacter" ), CT_HASH32( "m_hActiveWeapon" ) );
		m_flNextAttack = g_netvars.get( CT_HASH32( "DT_BaseCombatCharacter" ), CT_HASH32( "m_flNextAttack" ) );

		m_iClip1    = g_netvars.get( CT_HASH32( "DT_BaseCombatWeapon" ), CT_HASH32( "m_iClip1" ) );
		m_BombTimer = g_netvars.get( CT_HASH32( "DT_BaseCombatWeapon" ), CT_HASH32( "m_BombTimer" ) );
		m_iItemDefinitionIndex = g_netvars.get( CT_HASH32( "DT_BaseCombatWeapon" ), CT_HASH32( "m_iItemDefinitionIndex" ) );

		m_bBombTicking      = g_netvars.get( CT_HASH32( "DT_PlantedC4" ), CT_HASH32( "m_bBombTicking" ) );
		m_bBombDefused      = g_netvars.get( CT_HASH32( "DT_PlantedC4" ), CT_HASH32( "m_bBombDefused" ) );
		m_flC4Blow          = g_netvars.get( CT_HASH32( "DT_PlantedC4" ), CT_HASH32( "m_flC4Blow" ) );
		m_flDefuseCountDown = g_netvars.get( CT_HASH32( "DT_PlantedC4" ), CT_HASH32( "m_flDefuseCountDown" ) );

		m_nMaterial = g_netvars.get( CT_HASH32( "DT_Sun" ), CT_HASH32( "m_nMaterial" ) );

		m_flPoseParameter = g_netvars.get( CT_HASH32( "DT_BaseAnimating" ), CT_HASH32( "m_flPoseParameter" ) );
		m_nHitboxSet = g_netvars.get( CT_HASH32( "DT_BaseAnimating" ), CT_HASH32( "m_nHitboxSet" ) );

		m_flThrowStrength = g_netvars.get( CT_HASH32( "DT_BaseCSGrenade" ), CT_HASH32( "m_flThrowStrength" ) );
		m_bPinPulled = g_netvars.get( CT_HASH32( "DT_BaseCSGrenade" ), CT_HASH32( "m_bPinPulled" ) );

		return true;
	}
};

extern Offsets g_offsets;