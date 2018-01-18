#pragma once

class C_CSPlayer : public C_BaseEntity {
private:
	template < class T > static T get_field_value( C_CSPlayer *player, int offset ) {
		return *(T *)( (uint32_t)player + offset );
	}

public:
	static C_CSPlayer* get_local() {
		return (C_CSPlayer *)g_csgo.m_entity_list->GetClientEntity( g_csgo.m_engine->GetLocalPlayer() );
	}

	bool C_CSPlayer::is_valid_player( bool check_protected, bool check_dormant ) {
		bool ret = false;

		if ( /*this->GetClientClass()->m_ClassID == CCSPLAYER
			 &&*/ get_health( ) > 0 )
			ret = true;

		if ( check_dormant && this->IsDormant( ) )
			ret = false;

		if ( check_protected && this->is_protected( ) )
			ret = false;

		return ret;
	}

	int C_CSPlayer::get_health() {
		return *(int *)( (ulong_t)this + g_offsets.m_iHealth );
	}

	bool C_CSPlayer::is_protected() {
		return *(bool *)( (ulong_t)this + g_offsets.m_bGunGameImmunity );
	}

	bool C_CSPlayer::has_helmet() {
		return *(bool *)( (ulong_t)this + g_offsets.m_bHasHelmet );
	}

	bool C_CSPlayer::has_defuser() {
		return *(bool *)( (ulong_t)this + g_offsets.m_bHasDefuser );
	}

	int C_CSPlayer::get_team_index() {
		return *(int *)( (ulong_t)this + g_offsets.m_iTeamNum );
	}

	int C_CSPlayer::get_account() {
		return *(int *)( (ulong_t)this + g_offsets.m_iAccount );
	}

	C_BaseCombatWeapon *C_CSPlayer::get_active_weapon() {
		return (C_BaseCombatWeapon *)g_csgo.m_entity_list->GetClientEntityFromHandle( get_field_value< CHandle< C_BaseCombatWeapon > >( this, g_offsets.m_hActiveWeapon ) );
	}
};
