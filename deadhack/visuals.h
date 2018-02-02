#pragma once

class Visuals {
private:
	float m_defuse_time;
	bool m_scopedirt;

	void player( C_CSPlayer *entity );
	void world( C_BaseEntity *entity );
	void draw_player_weapon( C_CSPlayer *entity, int x, int y, int w, int h );
	void grenade_prediction( C_CSPlayer *local, C_BaseCombatWeapon *weapon );
	void draw_box( OSHColor color, float x, float y, float w, float h );
	void draw_healthbar( float x, float y, float h, int health );
	void draw_bomb_timer( float time_left );
	void draw_defuse_timer( float time_left );
	void nightmode();
	void remove_scopedirt();
	void draw_scope();

public:
	bool m_nightmode;
	int m_cur_index;
	bool m_enabled = true;
	float m_player_alpha[ 64 ];

	bool world_to_screen( const Vec3_t &origin, Vec3_t &screen );
	void sort( C_CSPlayer *entity );
	void work();
	void activation_type();
	void player_chams();
};

extern Visuals g_visuals;