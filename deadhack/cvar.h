#pragma once

class CVar {
private:
public:
	struct {
		config_manager::CVar::cvar_s *pistol_historyaim;
		config_manager::CVar::cvar_s *smg_historyaim;
		config_manager::CVar::cvar_s *rifle_historyaim;
		config_manager::CVar::cvar_s *shotgun_historyaim;
		config_manager::CVar::cvar_s *sniper_historyaim;

		config_manager::CVar::cvar_s *pistol_trigger;
		config_manager::CVar::cvar_s *smg_trigger;
		config_manager::CVar::cvar_s *rifle_trigger;
		config_manager::CVar::cvar_s *shotgun_trigger;
		config_manager::CVar::cvar_s *sniper_trigger;

		config_manager::CVar::cvar_s *pistol_trigger_key;
		config_manager::CVar::cvar_s *smg_trigger_key;
		config_manager::CVar::cvar_s *rifle_trigger_key;
		config_manager::CVar::cvar_s *shotgun_trigger_key;
		config_manager::CVar::cvar_s *sniper_trigger_key;

		config_manager::CVar::cvar_s *pistol_trigger_hitgroup;
		config_manager::CVar::cvar_s *smg_trigger_hitgroup;
		config_manager::CVar::cvar_s *rifle_trigger_hitgroup;
		config_manager::CVar::cvar_s *shotgun_trigger_hitgroup;
		config_manager::CVar::cvar_s *sniper_trigger_hitgroup;

		config_manager::CVar::cvar_s *pistol_trigger_ignoreair;
		config_manager::CVar::cvar_s *smg_trigger_ignoreair;
		config_manager::CVar::cvar_s *rifle_trigger_ignoreair;
		config_manager::CVar::cvar_s *shotgun_trigger_ignoreair;
		config_manager::CVar::cvar_s *sniper_trigger_ignoreair;

		config_manager::CVar::cvar_s *pistol_trigger_hitchance;
		config_manager::CVar::cvar_s *smg_trigger_hitchance;
		config_manager::CVar::cvar_s *rifle_trigger_hitchance;
		config_manager::CVar::cvar_s *shotgun_trigger_hitchance;
		config_manager::CVar::cvar_s *sniper_trigger_hitchance;

		config_manager::CVar::cvar_s *pistol_trigger_delay;
		config_manager::CVar::cvar_s *smg_trigger_delay;
		config_manager::CVar::cvar_s *rifle_trigger_delay;
		config_manager::CVar::cvar_s *shotgun_trigger_delay;
		config_manager::CVar::cvar_s *sniper_trigger_delay;

		config_manager::CVar::cvar_s *pistol_trigger_team;
		config_manager::CVar::cvar_s *smg_trigger_team;
		config_manager::CVar::cvar_s *rifle_trigger_team;
		config_manager::CVar::cvar_s *shotgun_trigger_team;
		config_manager::CVar::cvar_s *sniper_trigger_team;

		config_manager::CVar::cvar_s *pistol_trigger_ignoresmoke;
		config_manager::CVar::cvar_s *smg_trigger_ignoresmoke;
		config_manager::CVar::cvar_s *rifle_trigger_ignoresmoke;
		config_manager::CVar::cvar_s *shotgun_trigger_ignoresmoke;
		config_manager::CVar::cvar_s *sniper_trigger_ignoresmoke;

		config_manager::CVar::cvar_s *pistol_trigger_ignoreflash;
		config_manager::CVar::cvar_s *smg_trigger_ignoreflash;
		config_manager::CVar::cvar_s *rifle_trigger_ignoreflash;
		config_manager::CVar::cvar_s *shotgun_trigger_ignoreflash;
		config_manager::CVar::cvar_s *sniper_trigger_ignoreflash;
	} m_legit;

	struct {
		// player
		config_manager::CVar::cvar_s *activation_type;
		config_manager::CVar::cvar_s *activation_key;
		config_manager::CVar::cvar_s *visible_only;
		config_manager::CVar::cvar_s *disable_thru_smoke;
		config_manager::CVar::cvar_s *teammates;
		config_manager::CVar::cvar_s *bbox;
		config_manager::CVar::cvar_s *healthbar;
		config_manager::CVar::cvar_s *name;
		config_manager::CVar::cvar_s *flags;
		config_manager::CVar::cvar_s *weapon;
		config_manager::CVar::cvar_s *ammo;
		config_manager::CVar::cvar_s *lagrecord;

		// player models
		config_manager::CVar::cvar_s *player_chams;
		config_manager::CVar::cvar_s *player_chams_ignorez;
		config_manager::CVar::cvar_s *cham_type;
		config_manager::CVar::cvar_s *cham_twopass_type;;
		config_manager::CVar::cvar_s *cham_outline;
		config_manager::CVar::cvar_s *cham_lagrecords;
		config_manager::CVar::cvar_s *cham_arms;
		config_manager::CVar::cvar_s *cham_weapon;
		config_manager::CVar::cvar_s *champlayer_weapon;

		// extra player
		config_manager::CVar::cvar_s *money;
		config_manager::CVar::cvar_s *defuser;
		config_manager::CVar::cvar_s *glow;
		config_manager::CVar::cvar_s *glow_type;
		config_manager::CVar::cvar_s *skeleton;

		// world
		config_manager::CVar::cvar_s *dropped_weapons;
		config_manager::CVar::cvar_s *objectives;
		config_manager::CVar::cvar_s *bullet_tracer;
		config_manager::CVar::cvar_s *grenade_projectiles;
		config_manager::CVar::cvar_s *grenade_trajectory;
		config_manager::CVar::cvar_s *inaccuracy;

		// world extra
		config_manager::CVar::cvar_s *chicken;
		config_manager::CVar::cvar_s *hitmarker;

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
		config_manager::CVar::cvar_s *remove_smoke;
		config_manager::CVar::cvar_s *remove_flash;
		config_manager::CVar::cvar_s *remove_post_processing;
	} m_visuals;

	struct {
		config_manager::CVar::cvar_s *bunnyhop;
		config_manager::CVar::cvar_s *spectators;
		config_manager::CVar::cvar_s *buy_log;
		config_manager::CVar::cvar_s *hurt_log;
		config_manager::CVar::cvar_s *hitsound;
		config_manager::CVar::cvar_s *clantag;
		config_manager::CVar::cvar_s *reveal_ranks;
		config_manager::CVar::cvar_s *radar;
		config_manager::CVar::cvar_s *low_fps_warning;
		config_manager::CVar::cvar_s *autopistol;
	} m_misc;

	struct {
		config_manager::CVar::cvar_s *box_color;
		config_manager::CVar::cvar_s *cham_color;
		config_manager::CVar::cvar_s *ignorez_color;
		config_manager::CVar::cvar_s *lag_record_color;
		config_manager::CVar::cvar_s *trajectory_color;
		config_manager::CVar::cvar_s *tracer_color;
		config_manager::CVar::cvar_s *glow_color;
		config_manager::CVar::cvar_s *skeleton_color;
		config_manager::CVar::cvar_s *inaccuracy_color;
		config_manager::CVar::cvar_s *arms_color;
		config_manager::CVar::cvar_s *weapon_cham_color;
		config_manager::CVar::cvar_s *menu_accent_color;
	} m_colors;
};

extern CVar g_cvar;