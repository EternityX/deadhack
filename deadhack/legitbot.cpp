#include "includes.h"

void Legitbot::setup_group_config( C_BaseCombatWeapon *local_weapon ) {
	if( !g_cl.m_local || !local_weapon )
		return;

	switch( local_weapon->get_weapon_type() ) {
		case WEAPON_TYPE_PISTOLS:
			m_cfg.history_aim = g_cvar.m_legit.pistol_historyaim->iValue;
			m_cfg.trigger_enabled = g_cvar.m_legit.pistol_trigger->bValue;
			m_cfg.trigger_key = g_cvar.m_legit.pistol_trigger_key->iValue;
			m_cfg.trigger_hitgroup = g_cvar.m_legit.pistol_trigger_hitgroup->iValue;
			m_cfg.trigger_ignoreair = g_cvar.m_legit.pistol_trigger_ignoreair->bValue;
			m_cfg.trigger_hitchance = g_cvar.m_legit.pistol_trigger_hitchance->iValue;
			m_cfg.trigger_delay = g_cvar.m_legit.pistol_trigger_delay->iValue;
			m_cfg.trigger_teammate = g_cvar.m_legit.pistol_trigger_team->bValue;
			m_cfg.trigger_ignoresmoke = g_cvar.m_legit.pistol_trigger_ignoresmoke->bValue;
			break;
		case WEAPON_TYPE_SMG:
			m_cfg.history_aim = g_cvar.m_legit.smg_historyaim->iValue;
			m_cfg.trigger_enabled = g_cvar.m_legit.smg_trigger->bValue;
			m_cfg.trigger_key = g_cvar.m_legit.smg_trigger_key->iValue;
			m_cfg.trigger_hitgroup = g_cvar.m_legit.smg_trigger_hitgroup->iValue;
			m_cfg.trigger_ignoreair = g_cvar.m_legit.smg_trigger_ignoreair->bValue;
			m_cfg.trigger_hitchance = g_cvar.m_legit.smg_trigger_hitchance->iValue;
			m_cfg.trigger_delay = g_cvar.m_legit.smg_trigger_delay->iValue;
			m_cfg.trigger_teammate = g_cvar.m_legit.smg_trigger_team->bValue;
			m_cfg.trigger_ignoresmoke = g_cvar.m_legit.smg_trigger_ignoresmoke->bValue;
			break;
		case WEAPON_TYPE_RIFLE: 
		case WEAPON_TYPE_MG:
			m_cfg.history_aim = g_cvar.m_legit.rifle_historyaim->iValue;
			m_cfg.trigger_enabled = g_cvar.m_legit.rifle_trigger->bValue;
			m_cfg.trigger_key = g_cvar.m_legit.rifle_trigger_key->iValue;
			m_cfg.trigger_hitgroup = g_cvar.m_legit.rifle_trigger_hitgroup->iValue;
			m_cfg.trigger_ignoreair = g_cvar.m_legit.rifle_trigger_ignoreair->bValue;
			m_cfg.trigger_hitchance = g_cvar.m_legit.rifle_trigger_hitchance->iValue;
			m_cfg.trigger_delay = g_cvar.m_legit.rifle_trigger_delay->iValue;
			m_cfg.trigger_teammate = g_cvar.m_legit.rifle_trigger_team->bValue;
			m_cfg.trigger_ignoresmoke = g_cvar.m_legit.rifle_trigger_ignoresmoke->bValue;
			break;
		case WEAPON_TYPE_SHOTGUN:
			m_cfg.history_aim = g_cvar.m_legit.shotgun_historyaim->iValue;
			m_cfg.trigger_enabled = g_cvar.m_legit.shotgun_trigger->bValue;
			m_cfg.trigger_key = g_cvar.m_legit.shotgun_trigger_key->iValue;
			m_cfg.trigger_hitgroup = g_cvar.m_legit.shotgun_trigger_hitgroup->iValue;
			m_cfg.trigger_ignoreair = g_cvar.m_legit.shotgun_trigger_ignoreair->bValue;
			m_cfg.trigger_hitchance = g_cvar.m_legit.shotgun_trigger_hitchance->iValue;
			m_cfg.trigger_delay = g_cvar.m_legit.shotgun_trigger_delay->iValue;
			m_cfg.trigger_teammate = g_cvar.m_legit.shotgun_trigger_team->bValue;
			m_cfg.trigger_ignoresmoke = g_cvar.m_legit.shotgun_trigger_ignoresmoke->bValue;
			break;
		case WEAPON_TYPE_SNIPER:
			m_cfg.history_aim = g_cvar.m_legit.sniper_historyaim->iValue;
			m_cfg.trigger_enabled = g_cvar.m_legit.sniper_trigger->bValue;
			m_cfg.trigger_key = g_cvar.m_legit.sniper_trigger_key->iValue;
			m_cfg.trigger_hitgroup = g_cvar.m_legit.sniper_trigger_hitgroup->iValue;
			m_cfg.trigger_ignoreair = g_cvar.m_legit.sniper_trigger_ignoreair->bValue;
			m_cfg.trigger_hitchance = g_cvar.m_legit.sniper_trigger_hitchance->iValue;
			m_cfg.trigger_delay = g_cvar.m_legit.sniper_trigger_delay->iValue;
			m_cfg.trigger_teammate = g_cvar.m_legit.sniper_trigger_team->bValue;
			m_cfg.trigger_ignoresmoke = g_cvar.m_legit.sniper_trigger_ignoresmoke->bValue;
			break;
		default: 
			m_cfg.history_aim = 0;
		break;
	}
}

void Legitbot::history_aim( CUserCmd *cmd ) {
	float best_distance = std::numeric_limits< float >::max();
	float best_simtime = -1.f;

	try {
		for( int i = 1; i <= g_csgo.m_global_vars->m_max_clients; i++ ) {
			C_CSPlayer *ent = (C_CSPlayer *)g_csgo.m_entity_list->GetClientEntity( i );
			if( !ent || !g_cl.m_local || ent == g_cl.m_local )
				continue;

			if( !ent->is_valid_player( true, true ) )
				continue;

			// get record entry.
			PlayerRecord_t *entry = &g_lagcomp.m_players[ i - 1 ];
			if( entry->m_records.empty() )
				continue;

			Vec3_t dir;
			Math::angle_to_vector( cmd->m_viewangles, dir );

			studiohdr_t *studio_hdr = g_csgo.m_model_info->GetStudioModel( ent->GetModel() );
			if( !studio_hdr )
				continue;

			// iterate through records.
			for( auto record = entry->m_records.begin(); record != entry->m_records.end(); ++record ) {
				if( !record->is_valid_record() )
					continue;
			
				for( int bone_index = 0; bone_index < studio_hdr->numbones; bone_index++ ) {
					mstudiobone_t *studio_bone = studio_hdr->pBone( bone_index );		
					if( !studio_bone || !( studio_bone->flags & 0x100 ) || studio_bone->parent == -1 )
						continue;
			
					Vec3_t parent_position;
					Math::matrix_position( record->m_bones.at( bone_index ), parent_position );
			
					// get distance to bone.
					auto distance_point_to_line = [ ]( Vec3_t point, Vec3_t origin, Vec3_t end ) {
						if( !point.is_valid() || !origin.is_valid() || !end.is_valid() )
							return std::numeric_limits< float >::max();
			
						Vec3_t point_dir = point - origin;
			
						float temp = point_dir.dot( end ) / ( end.x * end.x + end.y * end.y + end.z * end.z );
						if( temp < 0.000001f )
							return std::numeric_limits< float >::max();
			
						return ( point - ( origin + end * temp ) ).length();
					};
			
					float distance = distance_point_to_line( parent_position, g_cl.m_local->get_eye_position(), dir );
					if( best_distance > distance ) {
						best_distance = distance;
						best_simtime = record->m_simtime;
					}
				}
			}
		}
	}
	catch( ... ) {
		CSGO_Util::push_notification( Color::Red(), "Exception caught [68]" );
	}

	if( best_simtime > 0 && cmd->m_buttons & IN_ATTACK )
		cmd->m_tick_count = TIME_TO_TICKS( best_simtime );
}

void Legitbot::triggerbot( C_BaseCombatWeapon *local_weapon, CUserCmd *cmd ) {
	if( !g_cl.m_local || !local_weapon )
		return;

	if( !g_input.m_key_pressed[ m_cfg.trigger_key ] ) {
		m_timer.reset();
		return;
	}

	if( m_cfg.trigger_ignoreair && !( g_cl.m_local->get_flags() & FL_ONGROUND ) )
		return;

	if( m_cfg.trigger_ignoreflash && g_cl.m_local->get_flashed() > 140.f )
		return;

	if( m_timer.elapsed() < m_cfg.trigger_delay/*Utils::get_random_int_range( m_cfg.trigger_delay, m_cfg.trigger_delay + 25 )*/ )
		return;

	Vec3_t forward;
	Math::angle_to_vector( cmd->m_viewangles + g_cl.m_local->get_punch_angle() * 2.f, forward );
	forward *= local_weapon->get_weapon_info()->m_flRange;

	Vec3_t eye_pos = g_cl.m_local->get_eye_position();

	CTraceFilter filter;
	filter.m_skip = g_cl.m_local;

	Ray_t ray;
	ray.init( eye_pos, eye_pos + forward );

	CGameTrace trace;
	g_csgo.m_engine_trace->TraceRay( ray, MASK_SHOT, &filter, &trace );

	Vec3_t current_delta_position = trace.endpos - eye_pos;
	Math::normalize_vector( current_delta_position );

	Vec3_t end = forward + current_delta_position * 40.f;
	CSGO_Util::clip_trace_to_player( eye_pos, end, MASK_SHOT, &filter, &trace );

	auto is_valid_hitgroup = [ &trace ]( int hitgroup ) {
		switch( hitgroup ) {
			case TARGET_HEAD: {
				if( trace.hitgroup == HITGROUP_HEAD )
					return true;

				break;
			}
			case TARGET_CHEST: {
				if( trace.hitgroup == HITGROUP_CHEST || trace.hitgroup == HITGROUP_STOMACH )
					return true;

				break;
			}
			case TARGET_UPPER: {
				if( trace.hitgroup == HITGROUP_CHEST || trace.hitgroup == HITGROUP_STOMACH || trace.hitgroup == HITGROUP_HEAD )
					return true;

				break;
			}
			case TARGET_ALL: {
				if( trace.hitgroup <= HITGROUP_RIGHTLEG && trace.hitgroup > HITGROUP_GENERIC )
					return true;

				break;
			}
			default: break;
		}

		return false;
	};

	for( int i = 1; i <= g_csgo.m_global_vars->m_max_clients; i++ ) {
		C_CSPlayer *player = (C_CSPlayer *)g_csgo.m_entity_list->GetClientEntity( i );
		if( !player || player == g_cl.m_local )
			continue;

		if( !m_cfg.trigger_teammate && g_cl.m_local->get_team_index() == player->get_team_index() )
			continue;

		if( m_cfg.trigger_ignoresmoke && CSGO_Util::line_goes_thru_smoke( eye_pos, player->GetAbsOrigin() ) )
			continue;

		if( trace.hit_entity != player ) {
			m_timer.reset();
			continue;
		}

		if( !is_valid_hitgroup( m_cfg.trigger_hitgroup ) ) {
			m_timer.reset();
			continue;
		}

		if( m_cfg.trigger_hitchance > 0 && !g_misc.get_spread( player, cmd, m_cfg.trigger_hitchance ) )
			continue;

		cmd->m_buttons |= IN_ATTACK;	
	}
}