#pragma once

class Visuals {
private:
	std::vector< std::pair< int, float > > m_ents;
	float     m_defuse_time = 0;
	bool      m_scopedirt = false;
	bool      m_smoke = false;
	IMaterial *m_materials[ 6 ];

	struct DrawModelParams {
		Hooks::DrawModel_t original;
		uintptr_t ecx;
		uintptr_t results;
		DrawModelInfo_t &info;
		matrix3x4_t *p_bone_to_world;
		float *p_flex_weights;
		float *pFlexDelayedWeights;
		Vec3_t &origin;
		int draw_flags;
	};

	void player( C_CSPlayer *entity );
	void world( C_BaseEntity *entity );
	void draw_player_weapon( C_CSPlayer *entity, int x, int y, int w, int h );
	
	void draw_box( OSHColor color, float x, float y, float w, float h );
	void draw_healthbar( float x, float y, float h, int health );
	static void draw_bomb_timer( float time_left );
	static void draw_defuse_timer( float time_left );
	void draw_cube( float scalar, Vec3_t angles, Vec3_t middle_origin );
	void draw_3d_dotted_circle( Vec3_t position, float points, float radius, OSHColor color );
	void nightmode();
	void remove_scopedirt();
	void remove_smoke();
	static void draw_scope();
	void draw_records( C_CSPlayer *entity );

public:
	bool doing_chams;
	bool m_nightmode;
	int m_cur_index;
	bool m_enabled = true;
	float m_player_alpha[ 64 ];

	bool world_to_screen( const Vec3_t &origin, Vec3_t &screen );
	void sort( C_CSPlayer *entity );
	void work();
	void activation_type();
	void grenade_prediction( C_CSPlayer *local, C_BaseCombatWeapon *weapon );
	void player_chams();
	bool world_chams( Hooks::DrawModel_t original, uintptr_t ecx, uintptr_t results, DrawModelInfo_t &info, matrix3x4_t *pBoneToWorld, float *pFlexWeights, float *pFlexDelayedWeights, Vec3_t &origin, int drawFlags );
	static void draw_spectators();
	void draw_glow();
	static void watermark();
	void draw_out_of_fov( const Vec3_t &delta, float *rot );
	void draw_hitmarker();
	void draw_crosshair( C_BaseCombatWeapon *weapon );
	void skeleton( C_CSPlayer *player );
};

extern Visuals g_visuals;