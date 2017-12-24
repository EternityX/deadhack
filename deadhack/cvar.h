#pragma once

class CVar {
private:
public:
	struct {
		bool watermark;
	} m_misc;
};

extern CVar g_cvar;