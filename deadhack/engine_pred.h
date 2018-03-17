#pragma once

class EnginePrediction {
private:
	bool m_should_setup = true;

	float m_old_cur_time = 0.f;
	float m_old_frame_time = 0.f;

	char *m_move_data = nullptr;

public:
	void setup() {
		m_move_data = (char *)std::calloc( 1, sizeof CMoveData ); // calloc is generally faster than memset.
		m_should_setup = false;
	}

	void start( CUserCmd *cmd ) {
		if( !g_cl.m_local )
			return;

		if( m_should_setup )
			setup();

		m_old_cur_time = g_csgo.m_global_vars->m_cur_time;
		m_old_frame_time = g_csgo.m_global_vars->m_frametime;

		g_csgo.m_global_vars->m_cur_time = g_cl.m_local->get_tickbase() * g_csgo.m_global_vars->m_interval_per_tick;
		g_csgo.m_global_vars->m_frametime = g_csgo.m_global_vars->m_interval_per_tick;

		g_csgo.m_game_movement->StartTrackPredictionErrors( g_cl.m_local );

		g_csgo.m_movehelper->SetHost( g_cl.m_local );
		g_csgo.m_prediction->SetupMove( g_cl.m_local, cmd, g_csgo.m_movehelper, (CMoveData *)&m_move_data );
		g_csgo.m_game_movement->ProcessMovement( g_cl.m_local, (CMoveData *)&m_move_data );
		g_csgo.m_prediction->FinishMove( g_cl.m_local, cmd, (CMoveData *)&m_move_data );
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