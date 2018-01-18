#pragma once

class CHLClient {
public:
	ClientClass *GetAllClasses() {
		return Utils::get_method< ClientClass *(__thiscall *)( decltype( this ) )>( this, 8 )( this );
	}
};

typedef struct player_info_s {
	int64_t          __pad0;
	int              xuid_low;
	int              xuid_high;
	char             m_szPlayerName[ 128 ];
	int              m_nUserID;
	char             m_szSteamID[ 33 ];
	unsigned int     m_nSteam3ID;
	char             m_szFriendsName[ 128 ];
	bool             m_bIsFakePlayer;
	bool             m_bIsHLTV;
	unsigned int     m_dwCustomFiles[ 4 ];
	unsigned char    m_FilesDownloaded;
} player_info_t;

class IEngineClient {
public:
	bool GetPlayerInfo( int nClientIndex, player_info_t *pinfo ) {
		return Utils::get_method< bool(__thiscall *)( decltype( this ), int, player_info_t * )>( this, 8 )( this, nClientIndex, pinfo );
	}

	int GetLocalPlayer() {
		return Utils::get_method< int(__thiscall *)( decltype( this ) )>( this, 12 )( this );
	}

	const D3DMATRIX &world_to_screen_matrix() {
		ulong_t function_ptr    = ( *(ulong_t **)this )[ 37 ];
		ulong_t render_ptr      = *(ulong_t *)( function_ptr + 1 );
		ulong_t view_matrix     = *(ulong_t *)( render_ptr + 0xDC ) + 0x3DC;

		return (D3DMATRIX &)*(ulong_t *)view_matrix;
	}
};

struct CViewSetup {
	PAD( 0x10 )
	int      m_x;
	int      m_x_old;
	int      m_y;
	int      m_y_old;
	int      m_width;
	int      m_width_old;
	int      m_height;
	int      m_height_old;
	PAD( 0x80 )
	float    m_fov;
	float    m_fov_viewmodel;
	Vec3_t    m_origin;
	Ang_t    m_angles;
	float    m_znear;
	float    m_zfar;
	float    m_znear_viewmodel;
	float    m_zfar_viewmodel;
	float    m_aspect_ratio;
	float    m_near_blur_depth;
	float    m_near_focus_depth;
	float    m_far_focus_depth;
	float    m_far_blur_depth;
	float    m_near_blur_radius;
	float    m_far_blur_radius;
	float    m_dof_quality;
	int      m_motionblur_mode;
	PAD( 0x44 )
	int      m_edge_blur;
};