#pragma once

class LagRecord_t {
public:
    float                          m_simtime;
    std::array< matrix3x4_t, 128 > m_bones;

    __forceinline LagRecord_t( C_CSPlayer *player ) {
        m_simtime = player->get_simtime();
        
        player->SetupBones( m_bones.data(), 128, 0x100, m_simtime );
    }

    __forceinline bool is_valid_record() {
        

        return false;
    }
};

class PlayerRecord_t {
public:
    C_CSPlayer                *m_player;
    std::deque< LagRecord_t > m_records;
};

class LagCompensation {
public:
    std::array< PlayerRecord_t, 64 > m_players;

    __forceinline void think() {
        const size_t max_records{ 128 };
        C_CSPlayer   *ent;

        for( int i = 1; i < g_csgo.m_global_vars->m_max_clients; ++i ) {
            ent = (C_CSPlayer *)g_csgo.m_entity_list->GetClientEntity( i );
            if( !ent )
                continue;
            
            // get player record entry.
            auto entry = &m_players[ i - 1 ];

            entry->m_player = ent;

            // we have no records or we received a player update from the server, make a new entry.
            if( entry->m_records.empty() || ent->get_simtime() > entry->m_records.front().m_simtime ) {
                entry->m_records.push_front( LagRecord_t( ent ) );
                
                // too many records...
                if( entry->m_records.size() > max_records )
                    entry->m_records.pop_back();
            }
        }
    }
};

extern LagCompensation g_lagcomp;