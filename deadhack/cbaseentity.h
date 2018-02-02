#pragma once

class C_BaseEntity : public IClientEntity {
private:
	
public:
	bool C_BaseEntity::is_valid_world( bool check_dormant ) {
		bool ret = true;

		if ( check_dormant && this->IsDormant() )
			ret = false;

		return ret;
	}

	ulong_t C_BaseEntity::get_owner_entity_handle() {
		return *(ulong_t *)( (ulong_t)this + g_offsets.m_hOwnerEntity );
	}

	float C_BaseEntity::get_c4_blow() {
		return  *(float *)( (ulong_t)this + g_offsets.m_flC4Blow );
	}

	bool C_BaseEntity::is_bomb_ticking() {
		return *(bool *)( (ulong_t)this + g_offsets.m_bBombTicking );
	}

	bool C_BaseEntity::is_bomb_defused() {
		return *(bool *)( (ulong_t)this + g_offsets.m_bBombDefused );
	}

	float C_BaseEntity::get_defuse_length() {
		float defuse_countdown = *(float *)( (ulong_t)this + g_offsets.m_flDefuseCountDown );
		float return_value = defuse_countdown - g_csgo.m_global_vars->m_cur_time;
		return return_value < 0 ? 0.f : return_value;
	}

	IMaterial* &C_BaseEntity::get_sun_enabled() {
		return *(IMaterial **)( (ulong_t)this + g_offsets.m_nMaterial );
	}
};