#pragma once

struct WeaponInfo_t {
	char		m_pad_0x0000[ 4 ];			// 0x0000
	char*		m_consoleName;			// 0x0004
	char		m_pad_0008[ 12 ];			// 0x0008
	int			m_iMaxClip1;				// 0x0014
	int			m_iMaxClip2;				// 0x0018
	int			m_iDefaultClip1;			// 0x001C
	int			m_iDefaultClip2;			// 0x0020
	char		m_pad_0024[ 8 ];			// 0x0024
	char*		m_szWorldModel;			// 0x002C
	char*		m_szViewModel;			// 0x0030
	char*		m_szDroppedModel;			// 0x0034
	char		m_pad_0038[ 4 ];			// 0x0038
	char*		m_N0000023E;				// 0x003C
	char		m_pad_0040[ 56 ];			// 0x0040
	char*		m_szEmptySound;			// 0x0078
	char		m_pad_007C[ 4 ];			// 0x007C
	char*		m_szBulletType;			// 0x0080
	char		m_pad_0084[ 4 ];			// 0x0084
	char*		m_szHudName;				// 0x0088
	char*		m_szWeaponName;			// 0x008C
	char		m_pad_0090[ 56 ];			// 0x0090
	int 		m_WeaponType;				// 0x00C8
	int			m_iWeaponPrice;			// 0x00CC
	int			m_iKillAward;				// 0x00D0
	char*		m_szAnimationPrefix;		// 0x00D4
	float		m_flCycleTime;			// 0x00D8
	float		m_flCycleTimeAlt;			// 0x00DC
	float		m_flTimeToIdle;			// 0x00E0
	float		m_flIdleInterval;			// 0x00E4
	bool		m_bFullAuto;				// 0x00E8
	char		m_pad_0x00E5[ 3 ];			// 0x00E9
	int			m_iDamage;				// 0x00EC
	float		m_flArmorRatio;			// 0x00F0
	int			m_iBullets;				// 0x00F4
	float		m_flPenetration;			// 0x00F8
	float		m_flFlinchVelocityModifierLarge;	// 0x00FC
	float		m_flFlinchVelocityModifierSmall;	// 0x0100
	float		m_flRange;				// 0x0104
	float		m_flRangeModifier;		// 0x0108
	float		m_flThrowVelocity;		// 0x010C
	char		m_pad_0x010C[ 12 ];			// 0x0110
	bool		m_bHasSilencer;			// 0x011C
	char		m_pad_0x0119[ 3 ];			// 0x011D
	char*		m_pSilencerModel;			// 0x0120
	int			m_iCrosshairMinDistance;	// 0x0124
	int			m_iCrosshairDeltaDistance;// 0x0128 - iTeam?
	float		m_flMaxPlayerSpeed;		// 0x012C
	float		m_flMaxPlayerSpeedAlt;	// 0x0130
	float		m_flSpread;				// 0x0134
	float		m_flSpreadAlt;			// 0x0138
	float		m_flInaccuracyCrouch;		// 0x013C
	float		m_flInaccuracyCrouchAlt;	// 0x0140
	float		m_flInaccuracyStand;		// 0x0144
	float		m_flInaccuracyStandAlt;	// 0x0148
	float		m_flInaccuracyJumpInitial;// 0x014C
	float		m_flInaccuracyJump;		// 0x0150
	float		m_flInaccuracyJumpAlt;	// 0x0154
	float		m_flInaccuracyLand;		// 0x0158
	float		m_flInaccuracyLandAlt;	// 0x015C
	float		m_flInaccuracyLadder;		// 0x0160
	float		m_flInaccuracyLadderAlt;	// 0x0164
	float		m_flInaccuracyFire;		// 0x0168
	float		m_flInaccuracyFireAlt;	// 0x016C
	float		m_flInaccuracyMove;		// 0x0170
	float		m_flInaccuracyMoveAlt;	// 0x0174
	float		m_flInaccuracyReload;		// 0x0178
	int			m_iRecoilSeed;			// 0x017C
	float		m_flRecoilAngle;			// 0x0180
	float		m_flRecoilAngleAlt;		// 0x0184
	float		m_flRecoilAngleVariance;	// 0x0188
	float		m_flRecoilAngleVarianceAlt;	// 0x018C
	float		m_flRecoilMagnitude;		// 0x0190
	float		m_flRecoilMagnitudeAlt;	// 0x0194
	float		m_flRecoilMagnitudeVariance;	// 0x0198
	float		m_flRecoilMagnitudeVarianceAlt;	// 0x019C
	float		m_flRecoveryTimeCrouch;	// 0x01A0
	float		m_flRecoveryTimeStand;	// 0x01A4
	float		m_flRecoveryTimeCrouchFinal;	// 0x01A8
	float		m_flRecoveryTimeStandFinal;	// 0x01AC
	int			m_iRecoveryTransitionStartBullet;// 0x01B0 
	int			m_iRecoveryTransitionEndBullet;	// 0x01B4
	bool		m_bUnzoomAfterShot;		// 0x01B8
	bool		m_bHideViewModelZoomed;	// 0x01B9
										//char		m_pad_0x01B5[2];			// 0x01BA
	float		m_recoilTable[ 2 ][ 128 ];
	short		m_iZoomLevels;
	int			m_iZoomFOV[ 2 ];			// 0x01C0
	float		m_fZoomTime[ 3 ];			// 0x01C4
	char*		m_szWeaponClass;			// 0x01D4
	float		m_flAddonScale;			// 0x01D8
	char		m_pad_0x01DC[ 4 ];			// 0x01DC
	char*		m_szEjectBrassEffect;		// 0x01E0
	char*		m_szTracerEffect;			// 0x01E4
	int			m_iTracerFrequency;		// 0x01E8
	int			m_iTracerFrequencyAlt;	// 0x01EC
	char*		m_szMuzzleFlashEffect_1stPerson; // 0x01F0
	char		m_pad_0x01F4[ 4 ];			 // 0x01F4
	char*		m_szMuzzleFlashEffect_3rdPerson; // 0x01F8
	char		m_pad_0x01FC[ 4 ];			// 0x01FC
	char*		m_szMuzzleSmokeEffect;	// 0x0200
	float		m_flHeatPerShot;			// 0x0204
	char*		m_szZoomInSound;			// 0x0208
	char*		m_szZoomOutSound;			// 0x020C
	float		m_flInaccuracyPitchShift;	// 0x0210
	float		m_flInaccuracySoundThreshold;	// 0x0214
	float		m_flBotAudibleRange;		// 0x0218
	BYTE		m_pad_0x0218[ 8 ];			// 0x0220
	char*		m_pWrongTeamMsg;			// 0x0224
	bool		m_bHasBurstMode;			// 0x0228
	BYTE		m_pad_0x0225[ 3 ];			// 0x0229
	bool		m_bIsRevolver;			// 0x022C
	bool		m_bCannotShootUnderwater;	// 0x0230
};

class C_BaseCombatWeapon : public C_BaseEntity {
public:
	int get_item_definition_index() {
		return 0;
		//return *(int *)( (ulong_t)this + offset::weapon::m_iItemDefinitionIndex );
	}

	int get_clip_1() {
		return *(int *)( (ulong_t)this + g_offsets.m_iClip1 );
	}

	WeaponInfo_t *get_weapon_info() {
		return Utils::get_method< WeaponInfo_t *( __thiscall *)( decltype( this ) )>( this, 446 )( this );
	}

	int get_weapon_type() {
		switch( this->get_item_definition_index() ) {
		case WEAPON_DEAGLE:
			return WEAPON_TYPE_PISTOLS;
		case WEAPON_DUALS:
			return WEAPON_TYPE_PISTOLS;
		case WEAPON_FIVE7:
			return WEAPON_TYPE_PISTOLS;
		case WEAPON_GLOCK:
			return WEAPON_TYPE_PISTOLS;
		case WEAPON_AK47:
			return WEAPON_TYPE_RIFLE;
		case WEAPON_AUG:
			return WEAPON_TYPE_RIFLE;
		case WEAPON_AWP:
			return WEAPON_TYPE_SNIPER;
		case WEAPON_FAMAS:
			return WEAPON_TYPE_RIFLE;
		case WEAPON_G3SG1:
			return WEAPON_TYPE_SNIPER;
		case WEAPON_GALIL:
			return WEAPON_TYPE_RIFLE;
		case WEAPON_M249:
			return WEAPON_TYPE_MG;
		case WEAPON_M4A1:
			return WEAPON_TYPE_RIFLE;
		case WEAPON_MAC10:
			return WEAPON_TYPE_SMG;
		case WEAPON_P90:
			return WEAPON_TYPE_SMG;
		case WEAPON_UMP45:
			return WEAPON_TYPE_SMG;
		case WEAPON_XM1014:
			return WEAPON_TYPE_SHOTGUN;
		case WEAPON_BIZON:
			return WEAPON_TYPE_SMG;
		case WEAPON_MAG7:
			return WEAPON_TYPE_SHOTGUN;
		case WEAPON_NEGEV:
			return WEAPON_TYPE_MG;
		case WEAPON_SAWEDOFF:
			return WEAPON_TYPE_SHOTGUN;
		case WEAPON_TEC9:
			return WEAPON_TYPE_PISTOLS;
		case WEAPON_TASER:
			return WEAPON_TYPE_TASER;
		case WEAPON_P2000:
			return WEAPON_TYPE_PISTOLS;
		case WEAPON_MP7:
			return WEAPON_TYPE_SMG;
		case WEAPON_MP9:
			return WEAPON_TYPE_SMG;
		case WEAPON_NOVA:
			return WEAPON_TYPE_SHOTGUN;
		case WEAPON_P250:
			return WEAPON_TYPE_PISTOLS;
		case WEAPON_SCAR20:
			return WEAPON_TYPE_SNIPER;
		case WEAPON_SG553:
			return WEAPON_TYPE_RIFLE;
		case WEAPON_SCOUT:
			return WEAPON_TYPE_SNIPER;
		case WEAPON_KNIFE_T:
			return WEAPON_TYPE_KNIFE;
		case WEAPON_FLASH:
			return WEAPON_TYPE_GRENADE;
		case WEAPON_HE:
			return WEAPON_TYPE_GRENADE;
		case WEAPON_SMOKE:
			return WEAPON_TYPE_GRENADE;
		case WEAPON_MOLOTOV:
			return WEAPON_TYPE_GRENADE;
		case WEAPON_DECOY:
			return WEAPON_TYPE_GRENADE;
		case WEAPON_INC:
			return WEAPON_TYPE_GRENADE;
		case WEAPON_C4:
			return WEAPON_TYPE_GRENADE;
		case WEAPON_KNIFE_CT:
			return WEAPON_TYPE_KNIFE;
		case WEAPON_M4A1S:
			return WEAPON_TYPE_RIFLE;
		case WEAPON_USPS:
			return WEAPON_TYPE_PISTOLS;
		case WEAPON_CZ75:
			return WEAPON_TYPE_PISTOLS;
		case WEAPON_REVOLVER:
			return WEAPON_TYPE_PISTOLS;
		case WEAPON_KNIFE_BAYONET:
			return WEAPON_TYPE_KNIFE;
		case WEAPON_KNIFE_FLIP:
			return WEAPON_TYPE_KNIFE;
		case WEAPON_KNIFE_GUT:
			return WEAPON_TYPE_KNIFE;
		case WEAPON_KNIFE_KARAMBIT:
			return WEAPON_TYPE_KNIFE;
		case WEAPON_KNIFE_M9_BAYONET:
			return WEAPON_TYPE_KNIFE;
		case WEAPON_KNIFE_FALCHION:
			return WEAPON_TYPE_KNIFE;
		case WEAPON_KNIFE_TACTICAL:
			return WEAPON_TYPE_KNIFE;
		case WEAPON_KNIFE_SURVIVAL_BOWIE:
			return WEAPON_TYPE_KNIFE;
		case WEAPON_KNIFE_BUTTERFLY:
			return WEAPON_TYPE_KNIFE;
		case WEAPON_KNIFE_PUSH:
			return WEAPON_TYPE_KNIFE;
		default:
			break;
		}

		return WEAPON_TYPE_INVALID;
	}

	bool is_pistol() {
		return this->get_weapon_type() == WEAPON_TYPE_PISTOLS ? true : false;
	}

	bool is_taser() {
		return this->get_weapon_type() == WEAPON_TYPE_TASER ? true : false;
	}

	bool is_shotgun() {
		return this->get_weapon_type() == WEAPON_TYPE_SHOTGUN ? true : false;
	}

	bool is_smg() {
		return this->get_weapon_type() == WEAPON_TYPE_SMG ? true : false;
	}

	bool is_rifle() {
		return this->get_weapon_type() == WEAPON_TYPE_RIFLE ? true : false;
	}

	bool has_scope() {
		int weapon_index = this->get_item_definition_index();
		return weapon_index == WEAPON_G3SG1
			|| weapon_index == WEAPON_SCAR20
			|| weapon_index == WEAPON_AWP
			|| weapon_index == WEAPON_AUG
			|| weapon_index == WEAPON_SG553
			|| weapon_index == WEAPON_SCOUT;
	}

	bool is_mg() {
		return this->get_weapon_type() == WEAPON_TYPE_MG ? true : false;
	}

	bool is_sniper() {
		return this->get_weapon_type() == WEAPON_TYPE_SNIPER ? true : false;
	}

	bool is_grenade() {
		return this->get_weapon_type() == WEAPON_TYPE_GRENADE ? true : false;
	}

	bool is_knife() {
		return this->get_weapon_type() == WEAPON_TYPE_KNIFE ? true : false;
	}

	/*bool is_valid( bool check_clip = true ) {
		switch( this->get_weapon_type() ) {
		case WEAPON_TYPE_PISTOLS:
			break;
		case WEAPON_TYPE_SHOTGUN:
			break;
		case WEAPON_TYPE_SMG:
			break;
		case WEAPON_TYPE_RIFLE:
			break;
		case WEAPON_TYPE_MG:
			break;
		case WEAPON_TYPE_SNIPER:
			break;
		default:
			return false;
		}

		return check_clip ? this->get_clip_1() > 0 : true;
	}*/
};
