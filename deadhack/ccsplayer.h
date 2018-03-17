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

	void __forceinline C_CSPlayer::UpdateClientSideAnimation() {
		Utils::get_method< void( __thiscall *)( decltype( this ) )>( this, 218 )( this );
	}

	__forceinline bool C_CSPlayer::is_valid_player( bool check_protected, bool check_dormant ) {
		bool ret = false;

		if ( /*this->GetClientClass()->m_ClassID == CCSPLAYER
			 &&*/ get_health() > 0 )
			ret = true;

		if( check_dormant && this->IsDormant() )
			ret = false;

		if( check_protected && this->is_protected() )
			ret = false;

		return ret;
	}

	__forceinline bool C_CSPlayer::is_visible( C_CSPlayer *entity, const Vec3_t &start, const Vec3_t &end, int mask, C_BaseEntity *ignore ) {
		try {
			if( !entity || !ignore )
				return false;

			Ray_t ray;
			CTraceFilter filter;
			filter.m_skip = ignore;
			CGameTrace trace;

			ray.init( start, end );

			g_csgo.m_engine_trace->TraceRay( ray, mask, &filter, &trace );

			return trace.fraction == 1 || trace.hit_entity == entity;
		}
		catch( ... ) {
			return false;
		}
	}

	__forceinline bool C_CSPlayer::is_visible( const Vec3_t &end ) {
		try {
			Ray_t ray;
			CTraceFilter filter;
			filter.m_skip = this;
			CGameTrace trace;

			ray.init( this->get_eye_position(), end );

			g_csgo.m_engine_trace->TraceRay( ray, MASK_SHOT, &filter, &trace );

			if( trace.fraction == 1 /*|| trace.hit_entity == entity*/ )
				return true;

			return false;
		}
		catch( ... ) {
			return false;
		}
	}

	__forceinline float get_server_time() {
		return (float)this->get_tickbase() * g_csgo.m_global_vars->m_interval_per_tick;
	}

	//__forceinline bool C_CSPlayer::can_shoot( C_BaseCombatWeapon *weapon ) {
	//	float server_time = this->get_tickbase();

	//	if( weapon->is_valid( false ) ) {
	//		if( weapon->get_clip_1() <= 0 )
	//			return false;

	//		if( this->get_next_attack() > server_time )
	//			return false;

	//		/*int index = weapon->get_item_definition_index( );
	//		if( ( index == WEAPON_FAMAS || index == WEAPON_GLOCK ) && weapon->is_burst_mode() && weapon->get_burst_shots_remaining() > 0 )
	//			return true;*/

	//		if ( weapon->get_next_primary_attack() > server_time )
	//			return false;
	//	}
	//	else
	//	{
	//		if ( this->get_next_attack( ) > server_time )
	//			return false;

	//		if ( weapon->get_next_primary_attack( ) > server_time )
	//			return false;
	//	}

	//	return true;
	//}

	__forceinline float get_next_attack( ) {
		return *(float *)( (uintptr_t)this + g_offsets.m_flNextAttack );
	}

	__forceinline int get_health() {
		return *(int *)( (uintptr_t)this + g_offsets.m_iHealth );
	}

    __forceinline float &get_simtime() {
		return *(float *)( (uintptr_t)this + g_offsets.m_flSimulationTime );
	}

	__forceinline bool is_protected() {
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

	__forceinline C_BaseCombatWeapon *C_CSPlayer::get_active_weapon() {
		return (C_BaseCombatWeapon *)g_csgo.m_entity_list->GetClientEntityFromHandle( get_field_value< CHandle< C_BaseCombatWeapon > >( this, g_offsets.m_hActiveWeapon ) );
	}

	__forceinline matrix3x4_t &C_CSPlayer::get_coordinate_frame() {
		return *(matrix3x4_t *)( (uintptr_t)this + g_offsets.m_rgflCoordinateFrame );
	}

	__forceinline int C_CSPlayer::get_num_anim_overlays() {
		return *(int *)( (uintptr_t)this + 0x297C );
	}

	__forceinline AnimationLayer_t *C_CSPlayer::get_anim_overlays() {
		return *(AnimationLayer_t **)( (uintptr_t)this + 0x2970 );
	}

	__forceinline AnimationLayer_t *C_CSPlayer::get_anim_overlay( int i ) {
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

	__forceinline Vec3_t &C_CSPlayer::get_view_offset() {
		return *(Vec3_t *)( (uintptr_t)this + g_offsets.m_vecViewOffset );
	}

	__forceinline Vec3_t &C_CSPlayer::get_origin() {
		return *(Vec3_t *)( (uintptr_t)this + g_offsets.m_vecOrigin );
	}

	__forceinline Vec3_t C_CSPlayer::get_eye_position() {
		return get_origin() + get_view_offset();
	}

	__forceinline Vec3_t C_CSPlayer::get_bone_position( std::array< matrix3x4_t, 128 > matrix, int bone_index ) {
		return Vec3_t( matrix.at( bone_index ).m_mat_val[ 0 ][ 3 ], matrix.at( bone_index ).m_mat_val[ 1 ][ 3 ], matrix.at( bone_index ).m_mat_val[ 2 ][ 3 ] );
	}

	__forceinline int &C_CSPlayer::get_tickbase(){
		return *(int *)( (uintptr_t)this + g_offsets.m_nTickBase );
	}

	__forceinline int &C_CSPlayer::get_flags(){
		return *(int *)( (uintptr_t)this + g_offsets.m_fFlags );
	}

	__forceinline std::array< float, 24 > &C_CSPlayer::get_pose_parameter() {
		return *(std::array< float, 24 > *)( (uintptr_t)this + g_offsets.m_flPoseParameter );
	}

	__forceinline void C_CSPlayer::SetAbsOrigin( Vec3_t vec ) {
		using SetAbsOrigin_t = void(__thiscall *)( void *, const Vec3_t &origin );
		static SetAbsOrigin_t SetAbsOrigin;

		if ( !SetAbsOrigin )
			SetAbsOrigin = (SetAbsOrigin_t)SigScan::find( CT_HASH32( "client.dll" ), "55 8B EC 83 E4 F8 51 53 56 57 8B F1 E8" );

		SetAbsOrigin( this, vec );
	}

	__forceinline uint8_t &C_CSPlayer::get_move_type() {
		return *(uint8_t *)( (uintptr_t)this + 0x258 );
	}

	__forceinline uint32_t C_CSPlayer::get_observer_target_handle() {
		return *(uint32_t *)( (uintptr_t)this + g_offsets.m_hObserverTarget );
	}

	__forceinline Vec3_t &C_CSPlayer::get_velocity() {
		return *(Vec3_t *)( (uintptr_t)this + g_offsets.m_vecVelocity );
	}

	__forceinline bool &C_CSPlayer::get_spotted() {
		return *(bool *)( (uintptr_t)this + g_offsets.m_bSpotted );
	}

	__forceinline Vec3_t &C_CSPlayer::get_punch_angle() {
		return *(Vec3_t *) ( (uintptr_t)this + g_offsets.m_aimPunchAngle );
	}

	__forceinline float &C_CSPlayer::get_flash_max_alpha() {
		return *(float *)( (uintptr_t)this + g_offsets.m_flFlashMaxAlpha );
	}

	__forceinline float &C_CSPlayer::get_flash_duration() {
		return *(float *)( (uintptr_t)this + g_offsets.m_flFlashDuration );
	}

	__forceinline int C_CSPlayer::get_shots_fired() {
		return *(int *)( (uintptr_t)this + g_offsets.m_iShotsFired );
	}

	__forceinline int C_CSPlayer::get_hitbox_set() {
		return *(int *)( (uintptr_t)this + g_offsets.m_nHitboxSet );
	}

	__forceinline float C_CSPlayer::get_flashed() {
		return *(float *)( (uintptr_t)this + ( g_offsets.m_flFlashDuration - 12 ) );
	}
};
