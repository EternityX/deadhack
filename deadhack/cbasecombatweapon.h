#pragma once

class C_BaseCombatWeapon : public C_BaseEntity {
public:
	int get_item_definition_index() {
		return 0;
		//return *(int *)( (ulong_t)this + offset::weapon::m_iItemDefinitionIndex );
	}

	/*int get_clip_1() {
		return *(int *)( (ulong_t)this + offset::weapon::m_iClip1 );
	}*/

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
