#pragma once

class C_BaseEntity : public IClientEntity {
private:
	
public:
	__forceinline bool C_BaseEntity::is_valid_world( bool check_dormant ) {
		bool ret = true;

		if ( check_dormant && this->IsDormant() )
			ret = false;

		return ret;
	}

	__forceinline ulong_t C_BaseEntity::get_owner_entity_handle() {
		return *(ulong_t *)( (uintptr_t)this + g_offsets.m_hOwnerEntity );
	}

	__forceinline float C_BaseEntity::get_c4_blow() {
		return  *(float *)( (uintptr_t)this + g_offsets.m_flC4Blow );
	}

	__forceinline bool C_BaseEntity::is_bomb_ticking() {
		return *(bool *)( (uintptr_t)this + g_offsets.m_bBombTicking );
	}

	__forceinline bool C_BaseEntity::is_bomb_defused() {
		return *(bool *)( (uintptr_t)this + g_offsets.m_bBombDefused );
	}

	__forceinline float C_BaseEntity::get_defuse_length() {
		float defuse_countdown = *(float *)( (uintptr_t)this + g_offsets.m_flDefuseCountDown );
		float return_value = defuse_countdown - g_csgo.m_global_vars->m_cur_time;
		return return_value < 0 ? 0.f : return_value;
	}

	__forceinline IMaterial* &C_BaseEntity::get_sun_enabled() {
		return *(IMaterial **)( (uintptr_t)this + g_offsets.m_nMaterial );
	}
};