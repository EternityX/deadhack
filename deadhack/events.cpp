#include "includes.h"

/*
 *
 * ITEM PURCHASE
 *
 */
void Events::ItemPurchaseEvent::FireGameEvent( IGameEvent *event ) {
	if( !g_cvar.m_misc.buy_log->bValue )
		return;

	int user_id = event->GetInt( "userid" );
	if( !user_id )
		return;

	int get_player_id = g_csgo.m_engine->GetPlayerForUserID( user_id );
	if( get_player_id == g_csgo.m_engine->GetLocalPlayer() )
		return;

	player_info_t player_info;
	if( !g_csgo.m_engine->GetPlayerInfo( get_player_id, &player_info ) )
		return;

	std::stringstream ss;
	ss << player_info.m_szPlayerName << " purchased " << event->GetString( "weapon" ) << "\n";
	CSGO_Util::push_notification( Color::White(), ss.str().c_str() );
}

int Events::ItemPurchaseEvent::GetEventDebugID() {
	return EVENT_DEBUG_ID_INIT;
}

void Events::ItemPurchaseEvent::RegisterSelf() {
	g_csgo.m_game_event->AddListener( this, "item_purchase", false );
}

void Events::ItemPurchaseEvent::UnregisterSelf() {
	g_csgo.m_game_event->RemoveListener( this );
}

/*
*
* PLAYER HURT
*
*/
void Events::PlayerHurtEvent::FireGameEvent( IGameEvent *event ) {
	int user_id = event->GetInt( "userid" );
	if( !user_id )
		return;

	int attacker = event->GetInt( "attacker" );
	if( !attacker )
		return;

	int get_player_id = g_csgo.m_engine->GetPlayerForUserID( user_id );
	int attacker_id = g_csgo.m_engine->GetPlayerForUserID( attacker );

	if( attacker_id == g_csgo.m_engine->GetLocalPlayer() ) {
		std::stringstream ss;

		player_info_s player_info;
		g_csgo.m_engine->GetPlayerInfo( get_player_id, &player_info );

		int hitgroup = event->GetInt( "hitgroup" );

		ss << "Hit " << player_info.m_szPlayerName << " in the ";
		switch ( hitgroup ) {
			case 1: ss << "head"; break;
			case 2: ss << "upper torso"; break;
			case 3: ss << "lower torso"; break;
			case 4: ss << "left arm"; break;
			case 5: ss << "right arm"; break;
			case 6: ss << "left leg"; break;
			case 7: ss << "right leg"; break;
			default: ss << "body"; break; // usually fired when being hurt by grenades.
		}

		ss << " for " << event->GetInt( "dmg_health" ) << " damage\n";

		if( g_cvar.m_misc.hurt_log->bValue )
			CSGO_Util::push_notification( Color::White(), ss.str().c_str() );

		if( g_cvar.m_misc.hitsound->bValue )
			g_csgo.m_engine->ClientCmd_Unrestricted( "play buttons/arena_switch_press_02" ); // todo: don't do this.

		m_hitmarker_alpha = 1.f;
	}
}

int Events::PlayerHurtEvent::GetEventDebugID() {
	return EVENT_DEBUG_ID_INIT;
}

void Events::PlayerHurtEvent::RegisterSelf() {
	g_csgo.m_game_event->AddListener( this, "player_hurt", false );
}

void Events::PlayerHurtEvent::UnregisterSelf() {
	g_csgo.m_game_event->RemoveListener( this );
}

/*
*
* BULLET IMPACT
*
*/
void Events::BulletImpactEvent::FireGameEvent( IGameEvent *event ) {
	int user_id = event->GetInt( "userid" );
	if( !user_id )
		return;

	if( !g_cl.m_local )
		return;

	C_CSPlayer *ent = (C_CSPlayer *)g_csgo.m_entity_list->GetClientEntity( g_csgo.m_engine->GetPlayerForUserID( user_id ) );
	if( g_cl.m_local == ent ) {
		Vec3_t position{ event->GetFloat( "x" ), event->GetFloat( "y" ), event->GetFloat( "z" ) };
		if( g_cvar.m_visuals.bullet_tracer->bValue ) {
			OSHGui::Drawing::Color color = Config::string_to_color( 255, g_cvar.m_colors.tracer_color->szValue );

			BeamInfo_t beam_info;
			beam_info.m_nType = TE_BEAMPOINTS;
			beam_info.m_pszModelName = "sprites/physbeam.vmt";
			beam_info.m_nModelIndex = -1;
			beam_info.m_flHaloScale = 0.f;
			beam_info.m_flLife = 2.f;
			beam_info.m_flWidth = 2.f;
			beam_info.m_flEndWidth = 2.f;
			beam_info.m_flFadeLength = 0.1f;
			beam_info.m_flAmplitude = 2.f;
			beam_info.m_flBrightness = 70.f;
			beam_info.m_flSpeed = 0.2f;
			beam_info.m_nStartFrame = 0;
			beam_info.m_flFrameRate = 0.f;
			beam_info.m_flRed = color.GetRed() * 255.f;
			beam_info.m_flGreen = color.GetGreen() * 255.f;
			beam_info.m_flBlue = color.GetBlue() * 255.f;
			beam_info.m_nSegments = 2;
			beam_info.m_bRenderable = true;
			beam_info.m_nFlags = FBEAM_ONLYNOISEONCE | FBEAM_NOTILE | FBEAM_HALOBEAM;

			// create beam backwards because it looks nicer.
			beam_info.m_vecStart = position;
			beam_info.m_vecEnd = g_cl.m_local->get_eye_position();

			Beam_t *beam = g_csgo.m_render_beams->CreateBeamPoints( beam_info );
			if( beam )
				g_csgo.m_render_beams->DrawBeam( beam );
		}
	}
}

int Events::BulletImpactEvent::GetEventDebugID() {
	return EVENT_DEBUG_ID_INIT;
}

void Events::BulletImpactEvent::RegisterSelf() {
	g_csgo.m_game_event->AddListener( this, "bullet_impact", false );
}

void Events::BulletImpactEvent::UnregisterSelf() {
	g_csgo.m_game_event->RemoveListener( this );
}

/*
*
* FOOTSTEP
*
*/
void Events::FootStepEvent::FireGameEvent( IGameEvent *event ) {
	int user_id = event->GetInt( "userid" );
	if( !user_id || !g_cl.m_local )
		return;

	C_CSPlayer *ent = (C_CSPlayer *)g_csgo.m_entity_list->GetClientEntity( g_csgo.m_engine->GetPlayerForUserID( user_id ) );
	if( !ent || g_cl.m_local == ent )
		return;

	g_visuals.activation_type();
	if( !g_visuals.m_enabled )
		return;

	if( !g_cvar.m_visuals.teammates->bValue && g_cl.m_local->get_team_index() == ent->get_team_index() )
		return;
}

int Events::FootStepEvent::GetEventDebugID() {
	return EVENT_DEBUG_ID_INIT;
}

void Events::FootStepEvent::RegisterSelf() {
	g_csgo.m_game_event->AddListener( this, "player_footstep", false );
}

void Events::FootStepEvent::UnregisterSelf() {
	g_csgo.m_game_event->RemoveListener( this );
}

/*
*
* MOLOTOV
*
*/
void Events::InfernoStartBurnEvent::FireGameEvent( IGameEvent *event ) {
	int entity_id = event->GetInt( "entityid" );
	if( !entity_id )
		return;

	Vec3_t position{ event->GetFloat( "x" ), event->GetFloat( "y" ), event->GetFloat( "z" ) };

	int user_id = g_csgo.m_engine->GetPlayerForUserID( entity_id );
	C_CSPlayer *ent = (C_CSPlayer *)g_csgo.m_entity_list->GetClientEntity( user_id );

	// 7 seconds for both molotov and inc
	m_inferno.push_back( { g_csgo.m_global_vars->m_cur_time + 7.f, position, ent } );
}

int Events::InfernoStartBurnEvent::GetEventDebugID() {
	return EVENT_DEBUG_ID_INIT;
}

void Events::InfernoStartBurnEvent::RegisterSelf() {
	g_csgo.m_game_event->AddListener( this, "inferno_startburn", false );
}

void Events::InfernoStartBurnEvent::UnregisterSelf() {
	g_csgo.m_game_event->RemoveListener( this );
}

void Events::InfernoStartBurnEvent::draw() {
	for( size_t i = 0; i < m_inferno.size(); i++ ) {
		float diff = m_inferno[ i ].m_expiration - g_csgo.m_global_vars->m_cur_time;

		if( diff < 0.f ) {
			m_inferno.erase( m_inferno.begin() + i );
			continue;
		}

		float alpha = diff / 3.0f * 2.0f;

		if( g_cvar.m_visuals.grenade_projectiles->bValue ) {
			Vec3_t screen;
			if( g_visuals.world_to_screen( m_inferno[ i ].m_position, screen ) ) {
				g_custom_renderer.ansi_text( g_custom_renderer.m_fonts[ FONT_04B03_6PX ], OSHColor( alpha - 0.3f, 1.f, 1.f, 0.f ), OSHColor( alpha - 0.5f, 0.03f, 0.03f, 0.03f ), screen.x, screen.y, OUTLINED, "FIRE" );
				g_custom_renderer.ansi_text( g_custom_renderer.m_fonts[ FONT_04B03_6PX ], OSHColor( alpha - 0.3f, 1.f, 1.f, 1.f ), OSHColor( alpha - 0.5f, 0.03f, 0.03f, 0.03f ), screen.x + 3, screen.y + 9, OUTLINED, "%2.1f", diff );
			}
		}
	}
}

void Events::RoundEndEvent::FireGameEvent( IGameEvent *event ) {
	for ( int i = 1; i <= g_csgo.m_global_vars->m_max_clients; i++ ) {
		g_visuals.m_player_alpha[ i ] = 0;
	}
}

int Events::RoundEndEvent::GetEventDebugID() {
	return EVENT_DEBUG_ID_INIT;
}

void Events::RoundEndEvent::RegisterSelf() {
	g_csgo.m_game_event->AddListener( this, "round_end", false );
}

void Events::RoundEndEvent::UnregisterSelf() {
	g_csgo.m_game_event->RemoveListener( this );
}
