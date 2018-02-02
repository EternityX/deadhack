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
			 &&*/ get_health() > 0 )
			ret = true;

		if ( check_dormant && this->IsDormant() )
			ret = false;

		if ( check_protected && this->is_protected() )
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

	int C_CSPlayer::get_armor_value() {
		return *(int *)( (ulong_t)this + g_offsets.m_ArmorValue );
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

	bool C_CSPlayer::is_scoped() {
		return *(bool *)( (ulong_t)this + g_offsets.m_bIsScoped );
	}

	Vec3_t &C_CSPlayer::get_vec_origin() {
		return *(Vec3_t *)( (ulong_t)this + g_offsets.m_vecOrigin );
	}

	C_BaseCombatWeapon *C_CSPlayer::get_active_weapon() {
		return (C_BaseCombatWeapon *)g_csgo.m_entity_list->GetClientEntityFromHandle( get_field_value< CHandle< C_BaseCombatWeapon > >( this, g_offsets.m_hActiveWeapon ) );
	}

	matrix3x4_t &C_CSPlayer::get_coordinate_frame() {
		return *(matrix3x4_t *)( (ulong_t)this + g_offsets.m_rgflCoordinateFrame );
	}

	AnimationLayer *C_CSPlayer::get_anim_overlays() {
		return *(AnimationLayer **)( (ulong_t)this + 0x2970 );
	}

	AnimationLayer *C_CSPlayer::get_anim_overlay( int i ) {
		if ( i < 15 ) return &get_anim_overlays()[ i ];
		return nullptr;
	}

	int C_CSPlayer::get_sequence_act( int sequence ) {
		studiohdr_t *hdr = g_csgo.m_model_info->GetStudioModel( (model_t*)this->GetModel() );

		if( !hdr )
			return -1;

		static ulong_t offset = SigScan::find( CT_HASH32( "client.dll" ), "55 8B EC 83 7D 08 FF 56 8B F1 74 3D" );
		static auto get_sequence_activity = ( int(__fastcall *)(void *, studiohdr_t *, int ) )offset;

		return get_sequence_activity( this, hdr, sequence );
	}

	bool C_CSPlayer::is_defusing( ) {
		return *(bool *)( (ulong_t)this + g_offsets.m_bIsDefusing );
	}
};
