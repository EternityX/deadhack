#pragma once

class EnginePrediction {
private:
	bool m_should_setup;

	float m_old_cur_time = 0.f;
	float m_old_frame_time = 0.f;

	CMoveData m_move_data;

public:
	void setup() {
		std::memset( &m_move_data, 0, sizeof m_move_data );
		m_should_setup = false;
	}

	void start( CUserCmd *cmd ) {
		if( m_should_setup )
			setup();

		if( !g_cl.m_local )
			return;

		m_old_cur_time = g_csgo.m_global_vars->m_cur_time;
		m_old_frame_time = g_csgo.m_global_vars->m_frametime;

		g_csgo.m_global_vars->m_cur_time = g_cl.m_local->get_tickbase() * g_csgo.m_global_vars->m_interval_per_tick;
		g_csgo.m_global_vars->m_frametime = g_csgo.m_global_vars->m_interval_per_tick;

		g_csgo.m_game_movement->StartTrackPredictionErrors( g_cl.m_local );

		g_csgo.m_movehelper->SetHost( g_cl.m_local );
		g_csgo.m_prediction->SetupMove( g_cl.m_local, cmd, g_csgo.m_movehelper, &m_move_data );
		g_csgo.m_game_movement->ProcessMovement( g_cl.m_local, &m_move_data );
		g_csgo.m_prediction->FinishMove( g_cl.m_local, cmd, &m_move_data );
	}

	void end() {
		if( !g_cl.m_local )
			return;

		g_csgo.m_game_movement->FinishTrackPredictionErrors( g_cl.m_local );
		g_csgo.m_movehelper->SetHost( nullptr );

		g_csgo.m_global_vars->m_cur_time = m_old_cur_time;
		g_csgo.m_global_vars->m_frametime = m_old_frame_time;
	}
};

extern EnginePrediction g_engine_pred;