#pragma once

class model_t;

struct mstudiobbox_t {
	int       m_bone_index;
	int       m_group;
	Vec3_t    bb_min;
	Vec3_t    bb_max;
	int       m_hitbox_name_index;
	int       pad01[ 3 ];
	float     m_radius;
	int       pad02[ 4 ];

	const char *hitbox_name() const {
		if( m_hitbox_name_index == 0 )
			return "";

		return (const char *)this + m_hitbox_name_index;
	}
};

struct mstudiohitboxset_t {
	int m_name_index;

	const char* get_name() const {
		return (char *)this + m_name_index;
	}

	int m_num_hitboxes;
	int m_hitbox_index;

	mstudiobbox_t *hitbox( int i ) const {
		return (mstudiobbox_t *)( (unsigned char *)this + m_hitbox_index ) + i;
	}
};

struct mstudiobone_t {
	int            m_name_index;

	const char *get_name() const {
		return (const char *)this + m_name_index;
	}

	int            m_parent;
	int            m_bonecontroller [ 6 ];
	Vec3_t         m_pos;
	float          m_quat[ 4 ];
	Vec3_t         m_rot;
	Vec3_t         m_pos_scale;
	Vec3_t         m_rot_scale;

	matrix3x4_t    m_pose_to_bone;
	float          m_alignment[ 4 ];
	int            m_flags;
	int            m_proc_type;
	int            m_proc_index;
	mutable int    m_physics_bone;

	void *get_procedure() const {
		if( m_proc_index == 0 )
			return nullptr;

		return (void *)( (unsigned char *)this + m_proc_index );
	}

	int            m_surface_prop_idx;

	const char *get_surface_props() const {
		return (char *)this + m_surface_prop_idx;
	}

	int            m_contents;
	int            m_unused[ 8 ];
};

struct studiohdr_t {
	int					m_id;
	int					m_version;
	long				m_checksum;
	char				m_name[64];
	int					m_length;
	Vec3_t				m_eye_position;
	Vec3_t				m_illum_position;
	Vec3_t				m_hull_min;
	Vec3_t				m_hull_max;
	Vec3_t				m_view_bbmin;
	Vec3_t				m_view_bbmax;
	int					m_flags;
	int					m_num_bones;
	int					m_bone_index;

	mstudiobone_t* bone( int i ) const {
		return (mstudiobone_t *)( (unsigned char *)this + m_bone_index ) + i;
	}

	int					m_num_bone_controllers;
	int					m_bone_controller_index;
	int					m_num_hitbox_sets;
	int					m_hitbox_set_index;

	mstudiohitboxset_t *hitbox_set( int i ) const {
		return (mstudiohitboxset_t *)( (unsigned char *)this + m_hitbox_set_index ) + i;
	}

	mstudiobbox_t *hitbox( int i, int set ) const {
		mstudiohitboxset_t const *s = hitbox_set( set );
		if( !s ) return nullptr;

		return s->hitbox( i );
	}

	int	hitbox_count( int set ) const {
		mstudiohitboxset_t const *s = hitbox_set(set);
		if( !s ) return 0;

		return s->m_num_hitboxes;
	}

	int m_num_anim;
	int m_anim_desc_index;
	void *anim_desc( int i ) const {
		return (byte *)this + m_anim_desc_index + i;
	}

	int m_num_anim_group;
	int m_anim_group_index;

	void *anim_group( int i ) const {
		return (byte *)this + m_anim_group_index + i;
	}

	int m_num_bone_desc;
	int m_bone_desc_index;

	void *bone_desc( int i ) const {
		return (byte *)this + m_bone_desc_index + i;
	}

	int m_num_seq;
	int m_seq_index;
	int m_sequences_indexed;
	int m_num_seq_groups;
	int m_seq_group_index;

	void *seq_group( int i ) const {
		return (byte *)this + m_seq_group_index + i;
	}

	int m_num_textures;
	int m_texture_index;

	void *texture( int i ) const {
		return (byte *)this + m_texture_index + i;
	}

	// implement the rest if needed...
};

class IVModelInfo {
public:
	const model_t *GetModel( int modelindex ) {
		return Utils::get_method< model_t *( __thiscall *)( decltype( this ), int )>( this, 1 )( this, modelindex );
	}

	const char *GetModelName( const model_t *model ) {
		return Utils::get_method< const char *( __thiscall *)( decltype( this ), const model_t * )>( this, 3 )( this, model );
	}

	studiohdr_t *GetStudioModel( const model_t *mod ) {
		return Utils::get_method< studiohdr_t *( __thiscall *)( decltype( this ), const model_t * )>( this, 30 )( this, mod );
	}
};