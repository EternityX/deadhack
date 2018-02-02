#pragma once

class C_CSPlayer : public C_BaseEntity {
private:
	template < class T > static T get_field_value( C_CSPlayer *player, int offset ) {
		return *(T *)( (uint32_t)player + offset );
	}

public:
	static __forceinline C_CSPlayer* get_local() {
		return (C_CSPlayer *)g_csgo.m_entity_list->GetClientEntity( g_csgo.m_engine->GetLocalPlayer() );
	}

	__forceinline bool C_CSPlayer::is_valid_player( bool check_protected, bool check_dormant ) {
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

	__forceinline int C_CSPlayer::get_health() {
		return *(int *)( (uintptr_t)this + g_offsets.m_iHealth );
	}

    __forceinline float C_CSPlayer::get_simtime() {
		return *(float *)( (uintptr_t)this + g_offsets.m_flSimulationTime );
	}

	__forceinline bool C_CSPlayer::is_protected() {
		return *(bool *)( (uintptr_t)this + g_offsets.m_bGunGameImmunity );
	}

	__forceinline bool C_CSPlayer::has_helmet() {
		return *(bool *)( (uintptr_t)this + g_offsets.m_bHasHelmet );
	}

	__forceinline int C_CSPlayer::get_armor_value() {
		return *(int *)( (uintptr_t)this + g_offsets.m_ArmorValue );
	}

	__forceinline bool C_CSPlayer::has_defuser() {
		return *(bool *)( (uintptr_t)this + g_offsets.m_bHasDefuser );
	}

	__forceinline int C_CSPlayer::get_team_index() {
		return *(int *)( (uintptr_t)this + g_offsets.m_iTeamNum );
	}

	__forceinline int C_CSPlayer::get_account() {
		return *(int *)( (uintptr_t)this + g_offsets.m_iAccount );
	}

	__forceinline bool C_CSPlayer::is_scoped() {
		return *(bool *)( (uintptr_t)this + g_offsets.m_bIsScoped );
	}

	__forceinline Vec3_t &C_CSPlayer::get_vec_origin() {
		return *(Vec3_t *)( (uintptr_t)this + g_offsets.m_vecOrigin );
	}

	__forceinline C_BaseCombatWeapon *C_CSPlayer::get_active_weapon() {
		return (C_BaseCombatWeapon *)g_csgo.m_entity_list->GetClientEntityFromHandle( get_field_value< CHandle< C_BaseCombatWeapon > >( this, g_offsets.m_hActiveWeapon ) );
	}

	__forceinline matrix3x4_t &C_CSPlayer::get_coordinate_frame() {
		return *(matrix3x4_t *)( (uintptr_t)this + g_offsets.m_rgflCoordinateFrame );
	}

	__forceinline AnimationLayer *C_CSPlayer::get_anim_overlays() {
		return *(AnimationLayer **)( (uintptr_t)this + 0x2970 );
	}

	__forceinline AnimationLayer *C_CSPlayer::get_anim_overlay( int i ) {
		if ( i < 15 ) return &get_anim_overlays()[ i ];
		return nullptr;
	}

	__forceinline int C_CSPlayer::get_sequence_act( int sequence ) {
        using GetSequenceActivity_t = int (__fastcall *)( void *, studiohdr_t *, int );

		static auto func = (GetSequenceActivity_t)SigScan::find( CT_HASH32( "client.dll" ), "55 8B EC 83 7D 08 FF 56 8B F1 74 3D" );
        
        if( !func )
            return -1;

        studiohdr_t *hdr = g_csgo.m_model_info->GetStudioModel( (model_t*)this->GetModel() );

		if( !hdr )
			return -1;

		return func( this, hdr, sequence );
	}

	__forceinline bool C_CSPlayer::is_defusing( ) {
		return *(bool *)( (uintptr_t)this + g_offsets.m_bIsDefusing );
	}
};
