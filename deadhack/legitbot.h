#pragma once

enum TargetHitgroups {
	TARGET_HEAD,
	TARGET_CHEST,
	TARGET_UPPER,
	TARGET_ALL
};

class Legitbot {
private:
	// trigger
	Timer m_timer;

public:
	struct Config {
		int history_aim;
		bool trigger_enabled;
		int trigger_key;
		int trigger_hitgroup;
		bool trigger_ignoreair;
		int trigger_hitchance;
		int trigger_delay;
		bool trigger_teammate;
		bool trigger_ignoresmoke;
		bool trigger_ignoreflash;
	} m_cfg;

	void setup_group_config( C_BaseCombatWeapon *local_weapon );
	void history_aim( CUserCmd *cmd );
	void triggerbot( C_BaseCombatWeapon *local_weapon, CUserCmd *cmd );
};

extern Legitbot g_legitbot;