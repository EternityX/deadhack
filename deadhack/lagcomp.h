#pragma once

#include "legitbot.h"

class LagRecord_t {
public:
    float                           m_simtime;
    std::array< matrix3x4_t, 128 >  m_bones;
	Vec3_t                          m_origin;
	Vec3_t                          m_angles;

	explicit __forceinline LagRecord_t( C_CSPlayer *player ) {
        m_simtime = player->get_simtime();
        player->SetupBones( m_bones.data(), 128, 0x100, m_simtime );
		m_origin = player->GetAbsOrigin();
		m_angles = player->GetAbsAngles();
    }

	__forceinline bool is_valid_record() const {
		INetChannelInfo *channel_info = g_csgo.m_engine->GetNetChannelInfo();
		if( !channel_info )
			return false;

		auto get_lerp_time = []() {
			int ud_rate = g_csgo.m_convar->FindVar( "cl_updaterate" )->GetInt();

			ConVar *min_ud_rate = g_csgo.m_convar->FindVar( "sv_minupdaterate" );
			ConVar *max_ud_rate = g_csgo.m_convar->FindVar( "sv_maxupdaterate" );

			if( min_ud_rate && max_ud_rate )
				ud_rate = max_ud_rate->GetInt();

			float ratio = g_csgo.m_convar->FindVar( "cl_interp_ratio" )->GetFloat();
			if( !ratio )
				ratio = 1.f;

			float lerp = g_csgo.m_convar->FindVar( "cl_interp" )->GetFloat();
			ConVar *c_min_ratio = g_csgo.m_convar->FindVar( "sv_client_min_interp_ratio" );
			ConVar *c_max_ratio = g_csgo.m_convar->FindVar( "sv_client_max_interp_ratio" );

			if( c_min_ratio && c_max_ratio && c_min_ratio->GetFloat() != 1 )
				ratio = Utils::clamp( ratio, c_min_ratio->GetFloat(), c_max_ratio->GetFloat() );

			return std::max( lerp, ratio / ud_rate );
		};

		// predict cur time.
		float curtime = TICKS_TO_TIME( g_cl.m_local->get_tickbase() );
		
		// correct for latency and lerp time.
		float correct = channel_info->GetAverageLatency( FLOW_OUTGOING ) + channel_info->GetAverageLatency( FLOW_INCOMING ) + get_lerp_time();
		Math::clamp( correct, 0.f, 1.f /*sv_maxunlag*/ );

		// get difference between tick sent by player and the latency tick.
		return std::abs( correct - ( curtime - m_simtime ) ) < 0.19f;
	}
};

class PlayerRecord_t {
public:
    C_CSPlayer                   *m_player;
    std::deque< LagRecord_t >    m_records;
};

class LagCompensation {
public:
    std::array< PlayerRecord_t, 64 > m_players;
	size_t m_max_records{ 128 };

    void think() {
		switch( g_legitbot.m_cfg.history_aim ) {
			case 1: m_max_records = 4; break;
			case 2: m_max_records = 8; break;
			case 3: m_max_records = 12; break;
			//case 4: m_max_records = 25; break;
			default: break;
		}

        for( int i = 1; i < g_csgo.m_global_vars->m_max_clients; i++ ) {
			C_CSPlayer *ent = (C_CSPlayer *)g_csgo.m_entity_list->GetClientEntity( i );
            if( !ent || !g_cl.m_local || ent == g_cl.m_local )
                continue;

			if( !ent->is_valid_player( true, true ) )
				continue;
            
            // get player record entry.
	        PlayerRecord_t *entry = &m_players[ i - 1 ];

            entry->m_player = ent;

            // we have no records or we received a player update from the server, make a new entry.
            if( entry->m_records.empty() || ent->get_simtime() > entry->m_records.front().m_simtime ) {
	            LagRecord_t lag_record = LagRecord_t( ent );

				// only push valid records.
				if( lag_record.is_valid_record() )
					entry->m_records.push_front( lag_record );

	            size_t size = entry->m_records.size( );

				// too many records...
				if( size > m_max_records ) {
					for( size_t s = 0; s < size - m_max_records; s++ )
						entry->m_records.pop_back();
				}
            }
        }
    }
};

extern LagCompensation g_lagcomp;