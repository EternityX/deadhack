#include "includes.h"

void Misc::bunnyhop( CUserCmd *cmd ) {
	if( !g_cl.m_local )
		return;

	uint8_t move_type = g_cl.m_local->get_move_type();
	if( move_type == MOVETYPE_LADDER || move_type == MOVETYPE_NOCLIP )
		return;

	static bool last_jumped = false, should_fake = false;
	if ( !last_jumped && should_fake ) {
		should_fake = false;
		cmd->m_buttons |= IN_JUMP;
	}
	else if ( cmd->m_buttons & IN_JUMP ) {
		if ( g_cl.m_local->get_flags() & FL_ONGROUND ) {
			last_jumped = true;
			should_fake = true;
		}
		else {
			cmd->m_buttons &= ~IN_JUMP;
			last_jumped = false;
		}
	}
	else {
		last_jumped = false;
		should_fake = false;
	}
}

void Misc::air_strafe( CUserCmd *cmd, Vec3_t &original ) {
	if( g_cl.m_local->get_flags() & FL_ONGROUND )
		return;

	if( !g_cl.m_local->get_velocity().length() )
		cmd->m_forwardmove = 450.f;

	if( cmd->m_mousedx > 1 || cmd->m_mousedx < -1 ) {
		cmd->m_forwardmove = cmd->m_mousedx < 0.f ? -450.f : 450.f;
	}
	else {
		float air_accelerate = g_csgo.m_convar->FindVar( "sv_airaccelerate" )->GetFloat();
		float max_speed = g_csgo.m_convar->FindVar( "sv_maxspeed" )->GetFloat();
	}
}

void Misc::auto_zeus() {
	C_BaseCombatWeapon *weapon = g_cl.m_local->get_active_weapon();
	if( !weapon )
		return;

	WeaponInfo_t *weapon_info = weapon->get_weapon_info();

	// distance to hit is between 183 and 230.
}

void Misc::clan_tag() {
	static std::string tag = "deadcell   ";

	if( m_tag_changed != g_cvar.m_misc.clantag->bValue ) {
		if( !g_cvar.m_misc.clantag->bValue ) {
			CSGO_Util::set_clan_tag( "" );
			return;
		}

		m_tag_changed = g_cvar.m_misc.clantag->bValue;
	}

	if( g_cvar.m_misc.clantag->bValue ) {
		static size_t last_time = 0;
		ulong_t tick_count = GetTickCount();

		if( tick_count > last_time ) {
			tag += tag.at( 0 );
			tag.erase( 0, 1 );

			CSGO_Util::set_clan_tag( tag );

			last_time = tick_count + 400;
		}
	}
}

void Misc::reveal_ranks() {
	using ServerRankRevealAll_t = char(__cdecl *)( int * );
	static ServerRankRevealAll_t ServerRankRevealAll = nullptr;

	if( !ServerRankRevealAll )
		ServerRankRevealAll = (ServerRankRevealAll_t)g_offsets.m_ServerRankRevealAll;

	int v[ 3 ] = { 0, 0, 0 };

	ServerRankRevealAll( v );
}

void Misc::automatic_fire( C_BaseCombatWeapon *active_weapon, CUserCmd *cmd ) {
	if( !active_weapon || !cmd )
		return;

	WeaponInfo_t *wep_info = active_weapon->get_weapon_info();

	if( wep_info->m_bFullAuto || !active_weapon->is_pistol() ) 
		return;

	static auto firing = false;
	if( cmd->m_buttons & IN_ATTACK ) {
		if( firing ) {
			cmd->m_buttons &= ~IN_ATTACK;
		}
	}

	firing = cmd->m_buttons & IN_ATTACK ? true : false;
}

bool Misc::get_spread( C_CSPlayer *target, CUserCmd *cmd, int chance ) {
	int traces_hit = 0;

	Vec3_t forward, right, up;
	Math::angle_to_vectors( cmd->m_viewangles + g_cl.m_local->get_punch_angle() * 2.f, &forward, &right, &up );

	C_BaseCombatWeapon *weapon = g_cl.m_local->get_active_weapon();
	if( !weapon )
		return false;

	auto get_bullet_location = [ weapon ]( int seed ) {
		static RandomFloat_t RandomFloat = (RandomFloat_t)GetProcAddress( GetModuleHandleA( "vstdlib" ), "RandomFloat" );
		static RandomSeed_t RandomSeed = (RandomSeed_t)GetProcAddress( GetModuleHandleA( "vstdlib" ), "RandomSeed" );

		RandomSeed( seed + 1 & 255 );

		weapon->update_accuracy_penalty();

		float a = RandomFloat( 0.f, Math::pi_2 );
		float b = RandomFloat( 0.f, Math::pi_2 );
		float c = RandomFloat( 0.f, weapon->get_inaccuracy() );
		float d = RandomFloat( 0.f, weapon->get_spread() );

		float x = cos( a ) * c + cos( b ) * d;
		float y = sin( a ) * c + sin( b ) * d;

		return Vec3_t( x, y, 0.f );
	};

	Vec3_t local_eye_position = g_cl.m_local->get_eye_position();

	for( int i = 0; i < 255; i++ ) {
		Vec3_t bullet_location = get_bullet_location( i );

		Vec3_t direction = forward + bullet_location * right + bullet_location * up;
		direction.normalize_in_place();

		Ray_t ray;
		ray.init( local_eye_position, local_eye_position + direction * weapon->get_weapon_info()->m_flRange );

		CGameTrace trace;
		g_csgo.m_engine_trace->ClipRayToEntity( ray, MASK_SHOT, target, &trace );

		if (trace.hit_entity == target)
			++traces_hit;

		if( traces_hit >= chance )
			return true;
	}

	return false;
}