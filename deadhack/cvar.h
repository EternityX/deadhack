#pragma once

class CVar {
private:
public:
	struct {
		config_manager::CVar::cvar_s *activation_type;
		config_manager::CVar::cvar_s *activation_key;
		config_manager::CVar::cvar_s *teammates;
		config_manager::CVar::cvar_s *bbox;
		config_manager::CVar::cvar_s *healthbar;
		config_manager::CVar::cvar_s *name;
		config_manager::CVar::cvar_s *flags;
		config_manager::CVar::cvar_s *money;
		config_manager::CVar::cvar_s *watermark;
		config_manager::CVar::cvar_s *override_fov;
	} m_visuals;

	struct {
		
	} m_misc;
};

extern CVar g_cvar;