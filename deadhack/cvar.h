#pragma once

class CVar {
private:
public:
	struct {
		config_manager::CVar::cvar_s *watermark;
		config_manager::CVar::cvar_s *override_fov;
	} m_misc;
};

extern CVar g_cvar;