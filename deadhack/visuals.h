#pragma once

class Visuals {
private:
	void player( C_CSPlayer *entity );
	void draw_box( Color color, float x, float y, float w, float h );
	void draw_healthbar( float x, float y, float h, int health );

public:
	int m_cur_index;
	bool m_enabled = true;
	float m_player_alpha[ 64 ];

	bool world_to_screen( const Vec3_t &origin, Vec3_t &screen );
	void work();
	void activation_type();
};

extern Visuals g_visuals;