#pragma once

class Misc {
private:
	bool m_tag_changed;

	using RandomFloat_t = float(__cdecl *)( float, float );
	using RandomSeed_t = void(__cdecl *)( int );
public:
	void bunnyhop( CUserCmd *cmd );
	void air_strafe( CUserCmd *cmd, Vec3_t &original );
	void auto_zeus();
	void clan_tag();
	void reveal_ranks();
	void automatic_fire( C_BaseCombatWeapon *active_weapon, CUserCmd *cmd );
	bool get_spread( C_CSPlayer *target, CUserCmd *cmd, int chance );
};

extern Misc g_misc;