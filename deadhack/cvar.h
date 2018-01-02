#pragma once

class CVar {
private:
public:
	struct {
		config_manager::CVar::cvar_s *watermark;
		config_manager::CVar::cvar_s *hide_confirmations;
	} m_misc;
};

extern CVar g_cvar;