#pragma once

class CVar {
private:
public:
	struct {
		// player
		config_manager::CVar::cvar_s *activation_type;
		config_manager::CVar::cvar_s *activation_key;
		config_manager::CVar::cvar_s *teammates;
		config_manager::CVar::cvar_s *bbox;
		config_manager::CVar::cvar_s *healthbar;
		config_manager::CVar::cvar_s *name;
		config_manager::CVar::cvar_s *flags;
		config_manager::CVar::cvar_s *weapon;
		config_manager::CVar::cvar_s *ammo;
		config_manager::CVar::cvar_s *money;

		// player models
		config_manager::CVar::cvar_s *player_chams;
		config_manager::CVar::cvar_s *player_chams_ignorez;
		config_manager::CVar::cvar_s *cham_type;
		config_manager::CVar::cvar_s *cham_outline;

		// world
		config_manager::CVar::cvar_s *dropped_weapons;
		config_manager::CVar::cvar_s *objectives;

		// effects general
		config_manager::CVar::cvar_s *override_fov;
		config_manager::CVar::cvar_s *weapon_fov;
		config_manager::CVar::cvar_s *fullbright;
		//config_manager::CVar::cvar_s *low_res;
		//config_manager::CVar::cvar_s *draw_gray;
		config_manager::CVar::cvar_s *nightmode;

		config_manager::CVar::cvar_s *remove_fog;
		config_manager::CVar::cvar_s *remove_scope;
		config_manager::CVar::cvar_s *remove_scopedirt;
	} m_visuals;

	struct {
		
	} m_misc;
};

extern CVar g_cvar;