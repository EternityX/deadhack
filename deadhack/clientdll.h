#pragma once

class CHLClient {
public:
	ClientClass *GetAllClasses() {
		return Utils::get_method< ClientClass *(__thiscall *)( decltype( this ) )>( this, 8 )( this );
	}
};

class IEngineClient {
	
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
	Ang_t    m_origin; // need to use vec3_t but it's incomplete.
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