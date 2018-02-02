#include "includes.h"

bool Visuals::world_to_screen( const Vec3_t &origin, Vec3_t &screen ) {
	// going to use the outdated matrix for now...
	const D3DMATRIX &matrix = g_csgo.m_engine->world_to_screen_matrix();

	float width = matrix.m[ 3 ][ 0 ] * origin.x + matrix.m[ 3 ][ 1 ] * origin.y + matrix.m[ 3 ][ 2 ] * origin.z + matrix.m[ 3 ][ 3 ];
	if ( width > 0.01f ) {
		float inverse = 1.0f / width;

		static OSHGui::Drawing::SizeF display_size = g_custom_renderer.m_instance->GetRenderer().GetDisplaySize();

		screen.x = (float)( display_size.Width / 2 + ( 0.5 * ( ( matrix.m[ 0 ][ 0 ] * origin.x + matrix.m[ 0 ][ 1 ] * origin.y + matrix.m[ 0 ][ 2 ] * origin.z + matrix.m[ 0 ][ 3 ] ) * inverse ) * display_size.Width + 0.5 ) );
		screen.y = (float)( display_size.Height / 2 - ( 0.5 * ( ( matrix.m[ 1 ][ 0 ] * origin.x + matrix.m[ 1 ][ 1 ] * origin.y + matrix.m[ 1 ][ 2 ] * origin.z + matrix.m[ 1 ][ 3 ] ) * inverse ) * display_size.Height + 0.5 ) );
		screen.z = 0.0f;

		return true;
	}

	return false;
}

void Visuals::sort( C_CSPlayer *entity ) {
	float distance = entity->GetAbsOrigin().length() - g_client.m_local->GetAbsOrigin().length();
	// todo: sort closest to farthest and draw closest entity first.
}

void Visuals::work() {
#ifdef CHEAT_DBG
	g_client.m_local = C_CSPlayer::get_local();
	g_client.c4_timer = g_csgo.m_convar->FindVar( "mp_c4timer" );
#endif
	if( !g_client.m_local )
		return;

	nightmode();
	remove_scopedirt();

	for( int i = 1; i <= g_csgo.m_entity_list->GetHighestEntityIndex(); i++ ) {
		C_CSPlayer *entity = (C_CSPlayer *)g_csgo.m_entity_list->GetClientEntity( i );
		if( !entity )
			continue;

		m_cur_index = i;

		player( entity );
		world( entity );
	}

	if( g_cvar.m_visuals.remove_scope->bValue )
		draw_scope();
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

void Visuals::player( C_CSPlayer *entity ) {
	activation_type();
	if( !m_enabled )
		return;

	if( !entity->is_valid_player( false, false ) )
		return;

	player_info_s player_info;
	if( !g_csgo.m_engine->GetPlayerInfo( m_cur_index, &player_info ) )
		return;

	if( entity == g_client.m_local )
		return;

	if( !g_cvar.m_visuals.teammates->bValue && g_client.m_local->get_team_index() == entity->get_team_index() )
		return;

	// esp dormancy fade.
	if ( entity->IsDormant() && m_player_alpha[ m_cur_index ] > 0.f )
		m_player_alpha[ m_cur_index ] -= 1.f / 2.5f * g_csgo.m_global_vars->m_frametime;
	else if ( m_player_alpha[ m_cur_index ] < 1.f && !entity->IsDormant() )
		m_player_alpha[ m_cur_index ] = 1.f;

	if( g_cvar.m_visuals.objectives->bValue ) {
		if( m_defuse_time > 0.f && entity->is_defusing() )
			draw_defuse_timer( m_defuse_time );
	}

	Vec3_t abs_origin = entity->GetAbsOrigin( );
	Vec3_t head = abs_origin + Vec3_t( 0, 0, entity->get_collideable()->OBBMaxs().z );

	Vec3_t w2s_head, w2s_feet;
	if( !world_to_screen( head, w2s_head ) || !world_to_screen( abs_origin, w2s_feet ) )
		return;

	int h = std::fabsf( w2s_head.y - w2s_feet.y ) + 5;
	int w = h / 2.f;
	int x = w2s_feet.x - w / 2;
	int y = w2s_head.y + 1;

	if( g_cvar.m_visuals.bbox->bValue )
		draw_box( OSHColor::FromARGB( m_player_alpha[ m_cur_index ] * 185, 125, 185, 255 ), x, y, w, h );

	if( g_cvar.m_visuals.healthbar->bValue )
		draw_healthbar( x, y, h, entity->get_health() );

	if( g_cvar.m_visuals.weapon->bValue )
		draw_player_weapon( entity, x, y, w, h );

	if( g_cvar.m_visuals.name->bValue )
		g_custom_renderer.ansi_text( g_custom_renderer.m_fonts[ FONT_VERDANA_BOLD_7PX ], 
									 OSHColor::FromARGB( m_player_alpha[ m_cur_index ] * 220, 255, 255, 255 ), 
									 OSHColor::FromARGB( m_player_alpha[ m_cur_index ] * 130, 10, 10, 10 ), 
									 x + w * 0.5f, y - 12, CENTERED_X | DROPSHADOW, player_info.m_szPlayerName );

	int flag_count = 0;
	if( g_cvar.m_visuals.money->bValue )
		g_custom_renderer.ansi_text( g_custom_renderer.m_fonts[ FONT_04B03_6PX ], 
									 OSHColor::FromARGB( m_player_alpha[ m_cur_index ] * 200, 149, 184, 6 ), 
									 OSHColor::FromARGB( m_player_alpha[ m_cur_index ] * 130, 10, 10, 10 ), 
									 x + w + 3, y + flag_count++ * 8, OUTLINED, "$%i", entity->get_account() );

	if( g_cvar.m_visuals.flags->bValue ) {
		int armor = entity->get_armor_value();

		if( entity->has_helmet() )
			g_custom_renderer.ansi_text( g_custom_renderer.m_fonts[ FONT_04B03_6PX ], 
										 OSHColor::FromARGB( m_player_alpha[ m_cur_index ] * 200, 255, 255, 255 ), 
										 OSHColor::FromARGB( m_player_alpha[ m_cur_index ] * 130, 10, 10, 10 ), 
										 x + w + 3, y + flag_count++ * 8, OUTLINED, "H" );

		if( armor > 0 )
			g_custom_renderer.ansi_text( g_custom_renderer.m_fonts[ FONT_04B03_6PX ], 
										OSHColor::FromARGB( m_player_alpha[ m_cur_index ] * 200, 255, 255, 255 ), 
										OSHColor::FromARGB( m_player_alpha[ m_cur_index ] * 130, 10, 10, 10 ), 
										x + w + 3, y + flag_count++ * 8, OUTLINED, "K" );

		if( entity->has_defuser() )
			g_custom_renderer.ansi_text( g_custom_renderer.m_fonts[ FONT_04B03_6PX ], 
										 OSHColor::FromARGB( m_player_alpha[ m_cur_index ] * 200, 255, 255, 255 ), 
										 OSHColor::FromARGB( m_player_alpha[ m_cur_index ] * 130, 10, 10, 10 ), 
										 x + w + 3, y + flag_count++ * 8, OUTLINED, "D" );
		
		if( !g_cvar.m_visuals.weapon->bValue && entity->is_scoped() )
			g_custom_renderer.ansi_text( g_custom_renderer.m_fonts[ FONT_04B03_6PX ], 
										 OSHColor::FromARGB( m_player_alpha[ m_cur_index ] * 200, 255, 255, 0 ), 
										 OSHColor::FromARGB( m_player_alpha[ m_cur_index ] * 130, 10, 10, 10 ), 
										 x + w + 3, y + flag_count++ * 8, OUTLINED, "Z" );
		
		
	}
}

void Visuals::world( C_BaseEntity *entity ) {
	if( !entity->is_valid_world( true ) )
		return;

	ClientClass *client_class = entity->GetClientClass( );
	if ( !client_class )
		return;

	if( g_cvar.m_visuals.objectives->bValue ) {
		if( client_class->m_ClassID == CPlantedC4 && entity->is_bomb_ticking() && !entity->is_bomb_defused() ) {
			m_defuse_time = entity->get_defuse_length();

			float bomb_duration = entity->get_c4_blow() - g_csgo.m_global_vars->m_cur_time;

			if( bomb_duration > 0.f )
				draw_bomb_timer( bomb_duration );
		}
	}

	Vec3_t bottom = entity->GetAbsOrigin();
	Vec3_t top = bottom + Vec3_t( 0, 0, 2.f );

	Vec3_t w2s_top, w2s_bottom;
	if( !world_to_screen( top, w2s_top ) || !world_to_screen( bottom, w2s_bottom ) )
		return;

	int h = std::fabsf( w2s_top.y - w2s_bottom.y );
	int w = h * 2;
	int x = w2s_bottom.x - w / 2;
	int y = w2s_top.y;

	C_BaseEntity *owner = (C_BaseEntity *) g_csgo.m_entity_list->GetClientEntityFromHandle( entity->get_owner_entity_handle() );

	if( g_cvar.m_visuals.dropped_weapons->bValue ) {
		if( !owner && ( client_class->m_ClassID != CBaseWeaponWorldModel && ( std::strstr( client_class->m_pNetworkName, "Weapon" )
			|| client_class->m_ClassID == CDEagle || client_class->m_ClassID == CAK47 ) ) ) {
			std::string weapon_name = client_class->m_pNetworkName;
			if( weapon_name.empty() )
				return;

			if( !std::strncmp( weapon_name.c_str(), "C", 1 ) )
				weapon_name.erase( 0, 1 );
			if( !std::strncmp( weapon_name.c_str(), "Weapon", 6 ) )
				weapon_name.erase( 0, 6 );

			std::transform( weapon_name.begin(), weapon_name.end(), weapon_name.begin(), std::toupper );

			C_BaseCombatWeapon *weapon = (C_BaseCombatWeapon *)entity;
			if( !weapon )
				return;

			g_custom_renderer.ansi_text( g_custom_renderer.m_fonts[ FONT_04B03_6PX ],
										 OSHColor::FromARGB( 200, 255, 255, 255 ),
										 OSHColor::FromARGB( 130, 10, 10, 10 ),
										 x + w * 0.5f, y - 5.f, CENTERED_X | OUTLINED, weapon_name );
		}
	}

	if( g_cvar.m_visuals.objectives->bValue ) {
		if( client_class->m_ClassID == CPlantedC4 && entity->is_bomb_ticking() && !entity->is_bomb_defused() ) {
			std::string text;
			if( g_client.m_local->get_team_index() == 3 )
				text += "DEFUSE ";
			else if( g_client.m_local->get_team_index() == 2 )
				text += "DEFEND ";
			text += "BOMB";

			g_custom_renderer.ansi_text( g_custom_renderer.m_fonts[ FONT_04B03_6PX ],
										 OSHColor::FromARGB( 240, 79, 130, 180 ),
										 OSHColor::FromARGB( 200, 10, 10, 10 ),
										 x + w * 0.5f, y - 15.f, CENTERED_X | OUTLINED, text );

			float bomb_duration = entity->get_c4_blow() - g_csgo.m_global_vars->m_cur_time;
			if( bomb_duration > 0.f ) {
				g_custom_renderer.ansi_text( g_custom_renderer.m_fonts[ FONT_04B03_6PX ],
											 OSHColor::FromARGB( 240, 255, 255, 255 ),
											 OSHColor::FromARGB( 200, 10, 10, 10 ),
											 x + w * 0.5f, y - 5.f, CENTERED_X | OUTLINED, "%2.1f", bomb_duration );
			}
		}

		if( !owner && client_class->m_ClassID == CC4 ) {
			g_custom_renderer.ansi_text( g_custom_renderer.m_fonts[ FONT_04B03_6PX ],
										 OSHColor::FromARGB( 240, 255, 255, 255 ),
										 OSHColor::FromARGB( 200, 10, 10, 10 ),
										 x + w * 0.5f, y - 5.f, OUTLINED, "BOMB" );
		}

		/*if( !owner && client_class->m_ClassID == CHostage ) {
			std::string text;
			if( g_client.m_local->get_team_index() == 3 )
				text += "GRAB ";
			else if( g_client.m_local->get_team_index() == 2 )
				text += "DEFEND ";
			text += "HOSTAGE";

			g_custom_renderer.ansi_text( g_custom_renderer.m_fonts[ FONT_04B03_6PX ],
										 OSHColor::FromARGB( 200, 79, 130, 180 ),
										 OSHColor::FromARGB( 170, 10, 10, 10 ),
										 x + w * 0.5f, y - 15.f, CENTERED_X | OUTLINED, text );
		}*/

		if( owner && client_class->m_ClassID == CHostageCarriableProp ) {
			g_custom_renderer.ansi_text( g_custom_renderer.m_fonts[ FONT_04B03_6PX ],
										 OSHColor::FromARGB( 240, 180, 130, 79 ),
										 OSHColor::FromARGB( 200, 10, 10, 10 ),
										 x + w * 0.5f, y - 15.f, CENTERED_X | OUTLINED, "HOSTAGE" );
		}
	}
}

void Visuals::draw_player_weapon( C_CSPlayer *entity, int x, int y, int w, int h ) {
	C_BaseCombatWeapon *weapon = entity->get_active_weapon();
	if( weapon ) {
		WeaponInfo_t *weapon_info = weapon->get_weapon_info();

		std::string weapon_name = weapon->GetClientClass()->m_pNetworkName;
		if( weapon_name.empty() )
			return;

		if ( !std::strncmp( weapon_name.c_str(), "C", 1 ) )
			weapon_name.erase( 0, 1 );
		if ( !std::strncmp( weapon_name.c_str(), "Weapon", 6 ) )
			weapon_name.erase( 0, 6 );

		std::transform( weapon_name.begin(), weapon_name.end(), weapon_name.begin(), std::toupper );

		OSHColor text = OSHColor::FromARGB( m_player_alpha[ m_cur_index ] * 220, 255, 255, 255 );
		if( entity->is_scoped() )
			text = OSHColor::FromARGB( m_player_alpha[ m_cur_index ] * 220, 255, 255, 0 );

		int push_weapon_text = 0;

		int clip = weapon->get_clip_1();
		int clip_max = weapon_info->m_iMaxClip1;

		if( g_cvar.m_visuals.ammo->iValue == 1 && clip > -1 && clip_max > -1 )
			push_weapon_text = 5;

		g_custom_renderer.ansi_text( g_custom_renderer.m_fonts[ FONT_04B03_6PX ], text, 
									 OSHColor::FromARGB( m_player_alpha[ m_cur_index ] * 130, 10, 10, 10 ), 
									 x + w * 0.5f, y + h + 2 + push_weapon_text, CENTERED_X | OUTLINED, weapon_name.c_str() );


		AnimationLayer *anim_layer = entity->get_anim_overlay( 1 );
		if( !anim_layer->m_pOwner )
			return;

		bool reloading = false;
		int activity = entity->get_sequence_act( anim_layer->m_nSequence );

		float width;
		if( activity == 967 && anim_layer->m_flWeight != 0.f ) {
			reloading = true;
			float cycle = anim_layer->m_flCycle;
			width = w * cycle / 1.f;
		}
		else {
			width = w * clip / clip_max;
		}

		if( g_cvar.m_visuals.ammo->iValue == 1 ) { 
			if( clip > -1 && clip_max > -1 ) {
				g_custom_renderer.filled_rect( OSHColor::FromARGB( m_player_alpha[ m_cur_index ] * 135, 10, 10, 10 ), x - 1, y + h + 2, w + 2, 4 );
				g_custom_renderer.rect( OSHColor::FromARGB( m_player_alpha[ m_cur_index ] * 220, 79, 130, 180 ), x, y + h + 3, width, 2 );
			}
		}
		else if( g_cvar.m_visuals.ammo->iValue == 2 ) {
			std::string ammo_text = std::to_string( clip ) + "/" + std::to_string( clip_max );
			if( reloading )
				ammo_text = "RELOADING";

			if ( clip > -1 && clip_max > -1 )
				g_custom_renderer.ansi_text( g_custom_renderer.m_fonts[ FONT_04B03_6PX ], text, 
											 OSHColor::FromARGB( m_player_alpha[ m_cur_index ] * 130, 10, 10, 10 ), 
											 x + w * 0.5f, y + h + 9, CENTERED_X | OUTLINED, ammo_text );
		}		
	}
}

void Visuals::player_chams() {
	static IMaterial *materials[ 6 ];

	static bool once{ false };
	if( !once ) {
		materials[ 0 ] = CSGO_Util::create_material( true, false, false ); // material.
		materials[ 1 ] = CSGO_Util::create_material( false, false, false ); // flat.
		materials[ 2 ] = CSGO_Util::create_material( true, false, true ); // material zignore.
		materials[ 3 ] = CSGO_Util::create_material( false, false, true ); // flat zignore.
		materials[ 4 ] = CSGO_Util::create_material( false, true, true ); // outline.
		once = true;
	}

	activation_type();
	if( !m_enabled )
		return;

	if( !g_client.m_local || !g_cvar.m_visuals.player_chams->bValue )
		return;

	for( int i = 1; i <= 64; i++ ) {
		C_CSPlayer *player = (C_CSPlayer *)g_csgo.m_entity_list->GetClientEntity( i );

		if ( !player || player == g_client.m_local || !player->is_valid_player( false, true ) )
			continue;

		if( !g_cvar.m_visuals.teammates->bValue && g_client.m_local->get_team_index() == player->get_team_index() )
			continue;

		if( g_cvar.m_visuals.cham_outline->bValue ) {
			g_csgo.m_model_render->SetForcedMaterialOverride( materials[ 4 ] );

			static const float color[ 3 ] = { 1.0f, 1.0f, 1.0f };
			g_csgo.m_render_view->SetColorModulation( color );

			player->DrawModel( 1, 255 );
		}

		if( g_cvar.m_visuals.player_chams_ignorez->bValue ) {
			if( g_cvar.m_visuals.cham_type->iValue == 0 )
				g_csgo.m_model_render->SetForcedMaterialOverride( materials[ 2 ] );

			if( g_cvar.m_visuals.cham_type->iValue == 1 )
				g_csgo.m_model_render->SetForcedMaterialOverride( materials[ 3 ] );

			const float color2[ 3 ] = { 0.18f, 0.47f, 0.92f };
			g_csgo.m_render_view->SetColorModulation( color2 );

			player->DrawModel( 1, 255 );
		}

		g_csgo.m_model_render->SetForcedMaterialOverride( materials[ g_cvar.m_visuals.cham_type->iValue ] );

		const float color3[ 3 ] = { 0.58f, 0.8f, 0.1f };
		g_csgo.m_render_view->SetColorModulation( color3 );

		player->DrawModel( 1, 255 );
	}
}

void Visuals::grenade_prediction( C_CSPlayer *local, C_BaseCombatWeapon *weapon ) {
	if( !weapon->is_grenade() )
		return;

	ConVar *fire_throw_detonate_time = g_csgo.m_convar->FindVar( "molotov_throw_detonate_time" );

	auto get_grenade_detonate_time = []( int item, ConVar *fire_throw_detonate_time ) {
		switch( item ) {
		case WEAPON_FLASH:
		case WEAPON_HE:
			return 1.5f;
			break;
		case WEAPON_INC:
		case WEAPON_MOLOTOV:
			return fire_throw_detonate_time->GetFloat();
			break;
		default:
			break;
		}

		return 3.f;
	};

	auto physics_clip_velocity = []( const Vec3_t &in, const Vec3_t &normal, Vec3_t &out, float overbounce ) {
		int blocked = 0;

		float angle = normal[ 2 ];

		if ( angle > 0 )
			blocked |= 1; // floor.

		if ( !angle )
			blocked |= 2; // step.

		float backoff = in.dot( normal ) * overbounce;

		for ( int i = 0; i < 3; i++ ) {
			float change = normal[ i ] * backoff;
			out[ i ] = in[ i ] - change;

			if ( out[ i ] > -0.1f && out[ i ] < 0.1f )
				out[ i ] = 0;
		}

		return blocked;
	};

	// todo: finish.
}

void Visuals::draw_box( OSHColor color, float x, float y, float w, float h ) {
	g_custom_renderer.rect( OSHColor::FromARGB( m_player_alpha[ m_cur_index ] * 135, 10, 10, 10 ), x - 1, y - 1, w + 2, h + 2 );
	g_custom_renderer.rect( OSHColor::FromARGB( m_player_alpha[ m_cur_index ] * 135, 10, 10, 10 ), x + 1, y + 1, w - 2, h - 2 );
	g_custom_renderer.rect( color, x, y, w, h );
}

void Visuals::draw_healthbar( float x, float y, float h, int value ) {
	int hp = Utils::clamp( value, 0, 100 );
	OSHColor health_color = OSHColor::FromARGB( m_player_alpha[ m_cur_index ] * 255, 255 - hp * 2.55, hp * 2.55, 0 );

	int height = hp * (int)h / 100;

	g_custom_renderer.filled_rect( OSHColor::FromARGB( m_player_alpha[ m_cur_index ] * 135, 10, 10, 10 ), x - 6, y - 1, 4, h + 2 );
	g_custom_renderer.filled_rect( health_color, x - 5, y + h - height, 2, height );

	if ( hp >= 90 || hp <= 10 )
		return; 

	g_custom_renderer.ansi_text( g_custom_renderer.m_fonts[ FONT_04B03_6PX ], OSHColor::FromARGB( m_player_alpha[ m_cur_index ] * 220, 255, 255, 255 ), OSHColor::FromARGB( m_player_alpha[ m_cur_index ] * 130, 10, 10, 10 ), x - 8, y + h - height - 6,  OUTLINED, "%i", hp );
}

void Visuals::draw_bomb_timer( float time_left ) {
	OSHGui::Drawing::SizeF display_size = g_custom_renderer.m_instance->GetRenderer().GetDisplaySize();

	ConVar *max_c4_timer = g_csgo.m_convar->FindVar( "mp_c4timer" );
	float x = time_left * display_size.Width / max_c4_timer->GetFloat();

	g_custom_renderer.filled_rect( OSHColor::FromARGB( 145, 24, 24, 32 ), 0, 0, display_size.Width, 3 );
	g_custom_renderer.filled_rect( OSHColor::FromARGB( 255, 206, 115, 136 ), x, 0, time_left * -display_size.Width / max_c4_timer->GetFloat(), 3 );
	//g_custom_renderer.ansi_text( g_custom_renderer.m_fonts[ FONT_04B03_6PX ], OSHColor::White(), OSHColor::Black(), x - 1, -1, DROPSHADOW, "%2.1f", time_left );
}

void Visuals::draw_defuse_timer( float time_left ) {
	OSHGui::Drawing::SizeF display_size = g_custom_renderer.m_instance->GetRenderer().GetDisplaySize();

	float max_defuse_length = 10.f;
	float x = time_left * display_size.Width / max_defuse_length;

	g_custom_renderer.filled_rect( OSHColor::FromARGB( 145, 24, 24, 32 ), 0, 3, display_size.Width, 3 );
	g_custom_renderer.filled_rect( OSHColor::FromARGB( 255, 225, 225, 225 ), x, 3, time_left * -display_size.Width / max_defuse_length, 3 );
}

void Visuals::nightmode() {
	if( m_nightmode != g_cvar.m_visuals.nightmode->bValue ) {
		// change sky.
		if( g_cvar.m_visuals.nightmode->bValue )
			CSGO_Util::change_sky( "sky_csgo_night02b" );
		else
			CSGO_Util::change_sky( "nukeblank" ); // todo: need to backup old sky.

		static ConVar *r_drawspecificstaticprop = g_csgo.m_convar->FindVar( "r_drawspecificstaticprop" );
		r_drawspecificstaticprop->SetValue( 0 );

		for( int i = g_csgo.m_material_system->FirstMaterial(); i != g_csgo.m_material_system->InvalidMaterial(); i = g_csgo.m_material_system->NextMaterial( i ) ) {
			IMaterial *material = g_csgo.m_material_system->FindMaterial( i );

			if ( !material || material->IsErrorMaterial() )
				continue;

			if( std::strstr( material->GetTextureGroupName(), "Model" ) 
				|| std::strstr( material->GetTextureGroupName(), "StaticProp" )
				|| std::strstr( material->GetName(), "sky_csgo_night02b" ) ) {
				static float r, g, b;

				static bool once{ false };
				if( !once ) {
					material->GetColorModulation( &r, &g, &b );
					once = true;
				}

				if( g_cvar.m_visuals.nightmode->bValue )
					material->SetColor( 0.30f, 0.30f, 0.30f );
				else
					material->SetColor( r, g, b );
			}

			if( std::strstr( material->GetTextureGroupName(), "World" ) ) {
				static float r, g, b;

				static bool once{ false };
				if( !once ) {
					material->GetColorModulation( &r, &g, &b );
					once = true;
				}

				if( g_cvar.m_visuals.nightmode->bValue )
					material->SetColor( 0.03f, 0.03f, 0.03f );
				else
					material->SetColor( r, g, b );
			}

			/*if( std::strstr( material->GetName(), "glass" )
				|| std::strstr( material->GetName(), "decals" )
				|| std::strstr( material->GetName(), "door" )
				|| std::strstr( material->GetName(), "dust" )
				|| std::strstr( material->GetName(), "mirage" )
				|| std::strstr( material->GetName(), "brick" )
				|| std::strstr( material->GetName(), "plywood" ) ) {
				static float r, g, b;

				static bool once{ false };
				if( !once ) {
					material->GetColorModulation( &r, &g, &b );
					once = true;
				}

				if( g_cvar.m_visuals.nightmode->bValue )
					material->SetColor( 0.20f, 0.20f, 0.20f );
				else
					material->SetColor( r, g, b );
			}*/

			// remove the sun (some maps have the sun on the skybox).
			if( g_cvar.m_visuals.nightmode->bValue ) {
				if( std::strstr( material->GetName(), "light_glow02" ) )
					material->SetVarFlag( MATERIAL_VAR_NO_DRAW, true );
			}
			else {
				if( std::strstr( material->GetName(), "light_glow02" ) )
					material->SetVarFlag( MATERIAL_VAR_NO_DRAW, false );		
			}
		}

		m_nightmode = g_cvar.m_visuals.nightmode->bValue;
	}
}

void Visuals::remove_scopedirt() {
	if( m_scopedirt != g_cvar.m_visuals.remove_scopedirt->bValue ) {
		for( int i = g_csgo.m_material_system->FirstMaterial(); i != g_csgo.m_material_system->InvalidMaterial(); i = g_csgo.m_material_system->NextMaterial( i ) ) {
			IMaterial *material = g_csgo.m_material_system->FindMaterial( i );

			if( !material || material->IsErrorMaterial() )
				continue;

			if( g_cvar.m_visuals.remove_scopedirt->bValue ) {
				if( std::strstr( material->GetName(), "lens" ) )
					material->SetVarFlag( MATERIAL_VAR_NO_DRAW, true );
			}
			else {
				if( std::strstr( material->GetName(), "lens" ) )
					material->SetVarFlag( MATERIAL_VAR_NO_DRAW, false );
			}

		}

		m_scopedirt = g_cvar.m_visuals.remove_scopedirt->bValue;
	}
}

void Visuals::draw_scope() {
	if ( !g_client.m_local->is_scoped() )
		return;

	OSHGui::Drawing::SizeF display_size = g_custom_renderer.m_instance->GetRenderer().GetDisplaySize();

	g_custom_renderer.filled_rect( OSHColor::Black(), 0, display_size.Height * 0.5f, display_size.Width, 1 );
	g_custom_renderer.filled_rect( OSHColor::Black(), display_size.Width * 0.5f, 0, 1, display_size.Height );
}