#pragma once

class C_BaseEntity : public IClientEntity {
private:
	
public:
	__forceinline bool is_valid_world( bool check_dormant ) {
		bool ret = true;

		if ( check_dormant && this->IsDormant() )
			ret = false;

		return ret;
	}

	__forceinline ulong_t get_owner_entity_handle() {
		return *(ulong_t *)( (uintptr_t)this + g_offsets.m_hOwnerEntity );
	}

	__forceinline float get_c4_blow() {
		return  *(float *)( (uintptr_t)this + g_offsets.m_flC4Blow );
	}

	__forceinline bool is_bomb_ticking() {
		return *(bool *)( (uintptr_t)this + g_offsets.m_bBombTicking );
	}

	__forceinline bool is_bomb_defused() {
		return *(bool *)( (uintptr_t)this + g_offsets.m_bBombDefused );
	}

	__forceinline float get_defuse_length() {
		float defuse_countdown = *(float *)( (uintptr_t)this + g_offsets.m_flDefuseCountDown );
		float return_value = defuse_countdown - g_csgo.m_global_vars->m_cur_time;
		return return_value < 0 ? 0.f : return_value;
	}

	Vec3_t get_mins() {
		return *(Vec3_t *)( (uint32_t)this + g_offsets.m_vecMins );
	}

	Vec3_t get_maxs() {
		return *(Vec3_t *)( (uint32_t)this + g_offsets.m_vecMaxs );
	}

	__forceinline matrix3x4_t &get_coordinate_frame() {
		return *(matrix3x4_t *)( (uintptr_t)this + g_offsets.m_rgflCoordinateFrame );
	}
};