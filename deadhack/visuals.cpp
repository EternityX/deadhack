#include "includes.h"

bool Visuals::world_to_screen( const Vec3_t &origin, Vec3_t &screen ) {
	// going to use the outdated matrix for now...
	const D3DMATRIX &matrix = g_csgo.m_engine->world_to_screen_matrix( );

	float width = matrix.m[ 3 ][ 0 ] * origin.x + matrix.m[ 3 ][ 1 ] * origin.y + matrix.m[ 3 ][ 2 ] * origin.z + matrix.m[ 3 ][ 3 ];
	if ( width > 0.01f ) {
		float inverse = 1.0f / width;

		OSHGui::Drawing::SizeF display_size = g_custom_renderer.m_instance->GetRenderer().GetDisplaySize();

		screen.x = static_cast<float>( display_size.Width / 2 + ( 0.5f * ( ( matrix.m[ 0 ][ 0 ] * origin.x + matrix.m[ 0 ][ 1 ] * origin.y + matrix.m[ 0 ][ 2 ] * origin.z + matrix.m[ 0 ][ 3 ] ) * inverse ) * display_size.Width + 0.5 ) );
		screen.y = static_cast<float>( display_size.Height / 2 - ( 0.5f * ( ( matrix.m[ 1 ][ 0 ] * origin.x + matrix.m[ 1 ][ 1 ] * origin.y + matrix.m[ 1 ][ 2 ] * origin.z + matrix.m[ 1 ][ 3 ] ) * inverse ) * display_size.Height + 0.5 ) );
		screen.z = 0.0f;

		return true;
	}

	return false;
}

void Visuals::work() {
#ifdef CHEAT_DBG
	g_client.m_local = C_CSPlayer::get_local();
#endif
	if( !g_client.m_local )
		return;

	activation_type();
	if( !m_enabled )
		return;

	for( int i = 1; i <= g_csgo.m_entity_list->GetHighestEntityIndex(); i++ ) {
		C_CSPlayer* entity = (C_CSPlayer *)g_csgo.m_entity_list->GetClientEntity( i );
		if( !entity || entity == g_client.m_local )
			continue;

		m_cur_index = i;

		player( entity );
	}
}

void Visuals::activation_type() {
	static bool is_down = false;
	static bool is_clicked = false;

	// hotkey stuff.
	if( g_cvar.m_visuals.activation_type->iValue == 0 /* always */ ) {
		m_enabled = true;
	}
	else if( g_cvar.m_visuals.activation_type->iValue == 1 /* on-key */ ) {
		if( g_input.m_key_pressed[ g_cvar.m_visuals.activation_key->iValue ] )
			m_enabled = true;
		else
			m_enabled = false;
	}
	else if( g_cvar.m_visuals.activation_type->iValue == 2 /* toggle */ ) {
		if ( g_input.m_key_pressed[ g_cvar.m_visuals.activation_key->iValue ] ) {
			is_clicked = false;
			is_down = true;
		}
		else if ( !g_input.m_key_pressed[ g_cvar.m_visuals.activation_key->iValue ] && is_down ) {
			is_clicked = true;
			is_down = false;
		}
		else {
			is_clicked = false;
			is_down = false;
		}

		if( is_clicked )
			m_enabled = !m_enabled;
	}
}

void Visuals::player( C_CSPlayer* entity ) {
	int flag_count = 0;

	if( !entity->is_valid_player( false, false ) )
		return;

	player_info_s player_info;
	if( !g_csgo.m_engine->GetPlayerInfo( m_cur_index, &player_info ) )
		return;

	if( !g_cvar.m_visuals.teammates->bValue && g_client.m_local->get_team_index() == entity->get_team_index() )
		return;

	// esp dormancy fade.
	if ( entity->IsDormant() && m_player_alpha[ m_cur_index ] > 0.f )
		m_player_alpha[ m_cur_index ] -= 1.f / 2.5f * g_csgo.m_global_vars->m_frametime;
	else if ( m_player_alpha[ m_cur_index ] < 1.f && entity->IsDormant() )
		m_player_alpha[ m_cur_index ] = 1.f;

	Vec3_t abs_origin = entity->GetAbsOrigin( );
	Vec3_t head = abs_origin + Vec3_t( 0, 0, entity->get_collideable()->OBBMaxs().z );

	Vec3_t w2s_head, w2s_feet;
	if( !world_to_screen( head, w2s_head ) || !world_to_screen( abs_origin, w2s_feet ) )
		return;

	float h = std::fabs( w2s_head.y - w2s_feet.y );
	float w = h / 2.f;
	float x = w2s_feet.x - w * 0.5f;
	float y = w2s_feet.y > w2s_head.y ? w2s_head.y : w2s_feet.y;

	if( g_cvar.m_visuals.bbox->bValue )
		draw_box( Color::FromARGB( m_player_alpha[ m_cur_index ] * 185, 125, 185, 255 ), x, y, w, h );

	if( g_cvar.m_visuals.healthbar->bValue )
		draw_healthbar( x, y, h, entity->get_health() );

	if( g_cvar.m_visuals.name->bValue )
		g_custom_renderer.ansi_text( g_custom_renderer.m_fonts[ FONT_VERDANA_BOLD_7PX ], Color::FromARGB( m_player_alpha[ m_cur_index ] * 220, 255, 255, 255 ), Color::FromARGB( m_player_alpha[ m_cur_index ] * 130, 10, 10, 10 ), x + w * 0.5f, y - 12, CENTERED_X | DROPSHADOW, player_info.m_szPlayerName );

	if( g_cvar.m_visuals.money->bValue )
		g_custom_renderer.ansi_text( g_custom_renderer.m_fonts[ FONT_04B03_6PX ], Color::FromARGB( m_player_alpha[ m_cur_index ] * 200, 149, 184, 6 ), Color::FromARGB( m_player_alpha[ m_cur_index ] * 130, 10, 10, 10 ), x + w + 3, y + flag_count++ * 8, OUTLINED, "$%i", entity->get_account() );

	if( g_cvar.m_visuals.flags->bValue ) {
		if( entity->has_helmet() )
			g_custom_renderer.ansi_text( g_custom_renderer.m_fonts[ FONT_04B03_6PX ], Color::FromARGB( m_player_alpha[ m_cur_index ] * 200, 255, 255, 255 ), Color::FromARGB( m_player_alpha[ m_cur_index ] * 130, 10, 10, 10 ), x + w + 3, y + flag_count++ * 8, OUTLINED, "H" );

		if( entity->has_defuser() )
			g_custom_renderer.ansi_text( g_custom_renderer.m_fonts[ FONT_04B03_6PX ], Color::FromARGB( m_player_alpha[ m_cur_index ] * 200, 255, 255, 255 ), Color::FromARGB( m_player_alpha[ m_cur_index ] * 130, 10, 10, 10 ), x + w + 3, y + flag_count++ * 8, OUTLINED, "K" );
	}
}

void Visuals::draw_box( Color color, float x, float y, float w, float h ) {
	g_custom_renderer.rect( Color::FromARGB( m_player_alpha[ m_cur_index ] * 135, 10, 10, 10 ), x - 1, y - 1, w + 2, h + 2 );
	g_custom_renderer.rect( Color::FromARGB( m_player_alpha[ m_cur_index ] * 135, 10, 10, 10 ), x + 1, y + 1, w - 2, h - 2 );
	g_custom_renderer.rect( color, x, y, w, h );
}

void Visuals::draw_healthbar( float x, float y, float h, int value ) {
	int hp = Utils::clamp( value, 0, 100 );
	Color health_color = Color::FromARGB( m_player_alpha[ m_cur_index ] * 255, 255 - hp * 2.55, hp * 2.55, 0 );

	int height = hp * (int)h / 100;

	g_custom_renderer.filled_rect( Color::FromARGB( m_player_alpha[ m_cur_index ] * 135, 10, 10, 10 ), x - 6, y - 1, 4, h + 2 );
	g_custom_renderer.filled_rect( health_color, x - 5, y + h - height, 2, height );

	if ( hp >= 90 || hp <= 10 )
		return; 

	g_custom_renderer.ansi_text( g_custom_renderer.m_fonts[ FONT_04B03_6PX ], Color::FromARGB( m_player_alpha[ m_cur_index ] * 220, 255, 255, 255 ), Color::FromARGB( m_player_alpha[ m_cur_index ] * 130, 10, 10, 10 ), x - 8, y + h - height - 6,  OUTLINED, "%i", hp );
}