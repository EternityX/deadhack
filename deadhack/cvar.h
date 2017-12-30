#pragma once

class CVar {
private:
public:
	struct {
		config_manager::CVar::cvar_s *watermark;
	} m_misc;
};

extern CVar g_cvar;