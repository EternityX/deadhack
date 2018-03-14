#include "includes.h"

bool Visuals::world_to_screen( const Vec3_t &draw_modelin, Vec3_t &screen ) {
	// going to use the outdated matrix for now...
	const D3DMATRIX &matrix = g_csgo.m_engine->world_to_screen_matrix();

	float width = matrix.m[ 3 ][ 0 ] * draw_modelin.x + matrix.m[ 3 ][ 1 ] * draw_modelin.y + matrix.m[ 3 ][ 2 ] * draw_modelin.z + matrix.m[ 3 ][ 3 ];
	if ( width > 0.01f ) {
		float inverse = 1.0f / width;

		static OSHGui::Drawing::SizeF display_size = g_custom_renderer.m_instance->GetRenderer().GetDisplaySize();

		screen.x = (float)( display_size.Width / 2 + ( 0.5 * ( ( matrix.m[ 0 ][ 0 ] * draw_modelin.x + matrix.m[ 0 ][ 1 ] * draw_modelin.y + matrix.m[ 0 ][ 2 ] * draw_modelin.z + matrix.m[ 0 ][ 3 ] ) * inverse ) * display_size.Width + 0.5 ) );
		screen.y = (float)( display_size.Height / 2 - ( 0.5 * ( ( matrix.m[ 1 ][ 0 ] * draw_modelin.x + matrix.m[ 1 ][ 1 ] * draw_modelin.y + matrix.m[ 1 ][ 2 ] * draw_modelin.z + matrix.m[ 1 ][ 3 ] ) * inverse ) * display_size.Height + 0.5 ) );
		screen.z = 0.0f;

		return true;
	}

	return false;
}

void Visuals::sort( C_CSPlayer *entity ) {
	float distance = entity->GetAbsOrigin().length() - g_cl.m_local->GetAbsOrigin().length();
	// todo: sort closest to farthest and draw closest entity first.
}

void Visuals::work() {
	try {
#ifdef CHEAT_DBG
		g_cl.c4_timer = g_csgo.m_convar->FindVar( "mp_c4timer" );
#endif
		if( !g_cl.m_local )
			return;

		nightmode();
		remove_scopedirt();
		remove_smoke();
		g_events.m_inferno_start_burn->draw();

		for( int i = 1; i <= g_csgo.m_entity_list->GetHighestEntityIndex(); i++ ) {
			C_CSPlayer *entity = (C_CSPlayer *) g_csgo.m_entity_list->GetClientEntity( i );
			if( !entity )
				continue;

			m_cur_index = i;

			player( entity );
			world( entity );
		}

		C_BaseCombatWeapon *weapon = g_cl.m_local->get_active_weapon();
		if( !weapon )
			return;

		if( g_cvar.m_visuals.remove_scope->bValue )
			draw_scope();

		if( g_cvar.m_visuals.grenade_trajectory->bValue )
			g_visuals.grenade_prediction( g_cl.m_local, weapon );

		if( g_cvar.m_visuals.inaccuracy->bValue )
			draw_crosshair( weapon );
		
		if( g_cvar.m_visuals.hitmarker->bValue )
			draw_hitmarker();
	}
	catch( ... ) {
		CSGO_Util::push_notification( Color::Red(), "Exception caught [59]" );
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

void Visuals::player( C_CSPlayer *entity ) {
	if( !entity->is_valid_player( false, false ) )
		return;

	player_info_s player_info;
	if( !g_csgo.m_engine->GetPlayerInfo( m_cur_index, &player_info ) )
		return;

	if( g_cvar.m_misc.radar->bValue )
		entity->get_spotted() = true;

	activation_type();
	if( !m_enabled )
		return;

	if( entity == g_cl.m_local )
		return;

	if( !g_cvar.m_visuals.teammates->bValue && g_cl.m_local->get_team_index() == entity->get_team_index() )
		return;

	if( g_cvar.m_visuals.visible_only->bValue ) {
		if( !g_cl.m_local->is_visible( entity, g_cl.m_local->get_eye_position(), entity->get_eye_position(), MASK_SHOT, g_cl.m_local ) || g_cl.m_local->get_flashed() > 140.f )
			return;
	}

	if( g_cvar.m_visuals.disable_thru_smoke->bValue ) {
		if( CSGO_Util::line_goes_thru_smoke( g_cl.m_local->get_eye_position(), entity->GetAbsOrigin() ) )
			return;
	}

	if( g_cvar.m_visuals.lagrecord->bValue )
		draw_records( entity );

	// esp dormancy fade.
	if( entity->IsDormant() && m_player_alpha[ m_cur_index ] > 0.f )
		m_player_alpha[ m_cur_index ] -= 1.f / 2.5f * g_csgo.m_global_vars->m_frametime;
	else if ( m_player_alpha[ m_cur_index ] < 1.f && !entity->IsDormant() )
		m_player_alpha[ m_cur_index ] = 1.f;
	if( entity->IsDormant() && m_player_alpha[ m_cur_index ] == 1.f )
		m_player_alpha[ m_cur_index ] = 0.f;

	if( entity->is_protected() && !entity->IsDormant() )
		m_player_alpha[ m_cur_index ] = 0.5f;

	if( g_cvar.m_visuals.objectives->bValue ) {
		if( m_defuse_time > 0.f && entity->is_defusing() )
			draw_defuse_timer( m_defuse_time );
	}

	if( g_cvar.m_visuals.skeleton->bValue )
		skeleton( entity );

	Vec3_t abs_origin = entity->GetAbsOrigin();
	Vec3_t head = abs_origin + Vec3_t( 0, 0, entity->get_collideable()->OBBMaxs().z );

	Vec3_t w2s_head, w2s_feet;
	if( !world_to_screen( head, w2s_head ) || !world_to_screen( abs_origin, w2s_feet ) )
		return;

	int h = std::fabsf( w2s_head.y - w2s_feet.y ) + 5;
	int w = h / 2.f;
	int x = w2s_feet.x - w / 2;
	int y = w2s_head.y + 1;

	if( g_cvar.m_visuals.bbox->bValue )
		draw_box( Config::string_to_color( m_player_alpha[ m_cur_index ] * 0.72f, g_cvar.m_colors.box_color->szValue ), x, y, w, h );

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

		if( entity->get_flashed() > 140.f )
			g_custom_renderer.ansi_text( g_custom_renderer.m_fonts[ FONT_04B03_6PX ], 
										 OSHColor::FromARGB( m_player_alpha[ m_cur_index ] * 200, 255, 255, 255 ), 
										 OSHColor::FromARGB( m_player_alpha[ m_cur_index ] * 130, 10, 10, 10 ), 
										 x + w + 3, y + flag_count++ * 8, OUTLINED, "F" );

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
		
		if( !g_cvar.m_visuals.weapon->bValue && entity->is_scoped() )
			g_custom_renderer.ansi_text( g_custom_renderer.m_fonts[ FONT_04B03_6PX ], 
										 OSHColor::FromARGB( m_player_alpha[ m_cur_index ] * 200, 255, 255, 0 ), 
										 OSHColor::FromARGB( m_player_alpha[ m_cur_index ] * 130, 10, 10, 10 ), 
										 x + w + 3, y + flag_count++ * 8, OUTLINED, "Z" );
	}

	if( g_cvar.m_visuals.defuser->bValue && entity->has_defuser() )
		g_custom_renderer.ansi_text( g_custom_renderer.m_fonts[ FONT_04B03_6PX ], 
									 OSHColor::FromARGB( m_player_alpha[ m_cur_index ] * 200, 255, 255, 255 ), 
									 OSHColor::FromARGB( m_player_alpha[ m_cur_index ] * 130, 10, 10, 10 ), 
									 x + w + 3, y + flag_count++ * 8, OUTLINED, "D" );
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

			if( weapon_name.compare( 0, 1, "C" ) != std::string::npos )
				weapon_name.erase( 0, 1 );
			if( weapon_name.compare( 0, 6, "Weapon" ) != std::string::npos )
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
			if( g_cl.m_local->get_team_index() == 3 )
				text += "DEFUSE ";
			else if( g_cl.m_local->get_team_index() == 2 )
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
										 x + w * 0.5f, y - 5.f, CENTERED_X | OUTLINED, "BOMB" );
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

	if( g_cvar.m_visuals.chicken->bValue && !owner && client_class->m_ClassID == CChicken ) {
		g_custom_renderer.ansi_text( g_custom_renderer.m_fonts[ FONT_04B03_6PX ],
									 OSHColor::FromARGB( 200, 255, 255, 100 ),
									 OSHColor::FromARGB( 200, 10, 10, 10 ),
									 x + w * 0.5f, y - 5.f, CENTERED_X | OUTLINED, "CHICKEN" );
	}

	if( g_cvar.m_visuals.grenade_projectiles->bValue ) {
		std::string model_name = g_csgo.m_model_info->GetModelName( entity->GetModel() );
		if( !model_name.empty() ) {
			if( client_class->m_ClassID == CBaseCSGrenadeProjectile ) {
				if( model_name.find( "fraggrenade" ) != std::string::npos )
					g_custom_renderer.ansi_text( g_custom_renderer.m_fonts[ FONT_04B03_6PX ], OSHColor::FromARGB( 200, 255, 255, 255 ), OSHColor::FromARGB( 200, 10, 10, 10 ), x, y - 15.f, CENTERED_X | OUTLINED, "HEGRENADE" );
				else if( model_name.find( "flashbang" ) != std::string::npos )
					g_custom_renderer.ansi_text( g_custom_renderer.m_fonts[ FONT_04B03_6PX ], OSHColor::FromARGB( 200, 255, 255, 255 ), OSHColor::FromARGB( 200, 10, 10, 10 ), x, y - 15.f, CENTERED_X | OUTLINED, "FLASHBANG" );
			}

			if( client_class->m_ClassID == CMolotovProjectile ) {
				if( model_name.find( "molotov" ) != std::string::npos )
					g_custom_renderer.ansi_text( g_custom_renderer.m_fonts[ FONT_04B03_6PX ], OSHColor::FromARGB( 200, 255, 255, 255 ), OSHColor::FromARGB( 200, 10, 10, 10 ), x, y - 15.f, CENTERED_X | OUTLINED, "MOLOTOV" );
				else if( model_name.find( "incendiary" ) != std::string::npos )
					g_custom_renderer.ansi_text( g_custom_renderer.m_fonts[ FONT_04B03_6PX ], OSHColor::FromARGB( 200, 255, 255, 255 ), OSHColor::FromARGB( 200, 10, 10, 10 ), x, y - 15.f, CENTERED_X | OUTLINED, "INCENDIARY" );
			}

			if( client_class->m_ClassID == CSmokeGrenadeProjectile )
				g_custom_renderer.ansi_text( g_custom_renderer.m_fonts[ FONT_04B03_6PX ], OSHColor::FromARGB( 200, 255, 255, 255 ), OSHColor::FromARGB( 200, 10, 10, 10 ), x, y - 15.f, CENTERED_X | OUTLINED, "SMOKE" );
		}
	}
}

void Visuals::draw_player_weapon( C_CSPlayer *entity, int x, int y, int w, int h ) {
	C_BaseCombatWeapon *weapon = entity->get_active_weapon();
	if( weapon ) {
		const WeaponInfo_t *weapon_info = g_csgo.m_weapon_system->GetWpnData( weapon->get_item_definition_index() );
		if( !weapon_info )
			return;
		//WeaponInfo_t *weapon_info = weapon->get_weapon_info();

		std::string weapon_name = weapon->GetClientClass()->m_pNetworkName;
		if( weapon_name.empty() )
			return;

		if( weapon_name.compare( 0, 1, "C" ) != std::string::npos )
			weapon_name.erase( 0, 1 );
		if( weapon_name.compare( 0, 6, "Weapon" ) != std::string::npos )
			weapon_name.erase( 0, 6 );

		std::transform( weapon_name.begin(), weapon_name.end(), weapon_name.begin(), ::toupper );

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


		AnimationLayer_t *anim_layer = entity->get_anim_overlay( 1 );
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
	static bool once{ false };
	if( !once ) {
		m_materials[ 0 ] = CSGO_Util::create_material( true, false, false ); // material.
		m_materials[ 1 ] = CSGO_Util::create_material( false, false, false ); // flat.
		m_materials[ 2 ] = CSGO_Util::create_rim_mat( true, false, false );
		m_materials[ 3 ] = g_csgo.m_material_system->GetMaterial( "debug/debugtranslucentmodelhulls", nullptr );
		m_materials[ 4 ] = g_csgo.m_material_system->GetMaterial( "models/inventory_items/dogtags/dogtags_outline", nullptr );
		m_materials[ 5 ] = g_csgo.m_material_system->GetMaterial( "models/inventory_items/trophy_majors/gold", nullptr );
		m_materials[ 6 ] = g_csgo.m_material_system->GetMaterial( "models/inventory_items/wildfire_gold/wildfire_gold_detail", nullptr );
		//m_materials[ 7 ] = g_csgo.m_material_system->GetMaterial( "models/weapons/v_models/arms/glove_sporty/glove_sporty_left", nullptr );
		m_materials[ 50 ] = CSGO_Util::create_rim_mat( true, true, true ); // outline.
		once = true;
	}

	activation_type();
	if( !m_enabled )
		return;

	if( !g_cl.m_local || !g_cvar.m_visuals.player_chams->bValue || g_cvar.m_visuals.cham_lagrecords->iValue )
		return;

	if( g_cl.m_local->get_health() <= 0 )
		return;

	for( int i = 1; i <= 64; i++ ) {
		C_CSPlayer *player = (C_CSPlayer *)g_csgo.m_entity_list->GetClientEntity( i );

		if ( !player || player == g_cl.m_local || !player->is_valid_player( false, true ) )
			continue;

		if( !g_cvar.m_visuals.teammates->bValue && g_cl.m_local->get_team_index() == player->get_team_index() )
			continue;

		OSHGui::Drawing::Color twopass_color = Config::string_to_color( 255, g_cvar.m_colors.ignorez_color->szValue );
		OSHGui::Drawing::Color cham_color = Config::string_to_color( 255, g_cvar.m_colors.cham_color->szValue );

		// 0.18f, 0.47f, 0.92f
		float color2[ 3 ];
		color2[ 0 ] = twopass_color.GetRed();
		color2[ 1 ] = twopass_color.GetGreen();
		color2[ 2 ] = twopass_color.GetBlue();

		// 0.58f, 0.8f, 0.1f 
		float color3[ 3 ];
		color3[ 0 ] = cham_color.GetRed();
		color3[ 1 ] = cham_color.GetGreen();
		color3[ 2 ] = cham_color.GetBlue();

		if( CSGO_Util::line_goes_thru_smoke( g_cl.m_local->get_eye_position(), player->GetAbsOrigin() ) ) {
			if( g_cvar.m_visuals.disable_thru_smoke->bValue )
				continue;
			
			if( g_cvar.m_visuals.player_chams_ignorez->bValue ) {
				color3[ 0 ] = color2[ 0 ];
				color3[ 1 ] = color2[ 1 ];
				color3[ 2 ] = color2[ 2 ];
			} else {
				continue;
			}
		}
		
		// NOTE: more system intensive than the other method but isn't affected by model occlusion...
		//// start lag compensation.
		//g_lagcomp.think();
		//
		//PlayerRecord_t *entry = &g_lagcomp.m_players[ i - 1 ];

		//// save backup records.
		//PlayerRecord_t *backup_record = entry;
		//if ( !entry->m_records.size() || !backup_record->m_records.size() )
		//	continue;

		//// iterate through available records.
		//for( auto record = entry->m_records.begin(); record != entry->m_records.end(); ++record ) {
		//	if( !record->is_valid_record() )
		//		continue;

		//	g_csgo.m_model_render->ForcedMaterialOverride( m_materials[ g_cvar.m_visuals.cham_type->iValue ] );

		//	const float color3[ 3 ] = { 1.f, 1.f, 1.f };
		//	g_csgo.m_render_view->SetColorModulation( color3 );
		//	g_csgo.m_render_view->SetBlend( 0.2f );

		//	// adjust player back to an old record.
		//	record->adjust_position( player );

		//	player->DrawModel( 1, 255 );
		//}

		//// restore records.
		//entry->m_records = backup_record->m_records;

		if( g_cvar.m_visuals.cham_outline->bValue ) {
			g_csgo.m_model_render->ForcedMaterialOverride( m_materials[ 50 ] );

			static const float color[ 3 ] = { 1.f, 1.f, 1.f };
			g_csgo.m_render_view->SetColorModulation( color );
			g_csgo.m_render_view->SetBlend( player->is_protected() ? 0.3f : 1.f );

			player->DrawModel( 1, 255 );
		}

		if( g_cvar.m_visuals.player_chams_ignorez->bValue ) {
			m_materials[ g_cvar.m_visuals.cham_twopass_type->iValue ]->SetVarFlag( MATERIAL_VAR_IGNOREZ, true );
			g_csgo.m_model_render->ForcedMaterialOverride( m_materials[ g_cvar.m_visuals.cham_twopass_type->iValue ] );

			g_csgo.m_render_view->SetColorModulation( color2 );
			g_csgo.m_render_view->SetBlend( player->is_protected() ? 0.3f : 1.f );

			player->DrawModel( 1, 255 );
		}

		m_materials[ g_cvar.m_visuals.cham_type->iValue ]->SetVarFlag( MATERIAL_VAR_IGNOREZ, false );
		g_csgo.m_model_render->ForcedMaterialOverride( m_materials[ g_cvar.m_visuals.cham_type->iValue ] );

		g_csgo.m_render_view->SetColorModulation( color3 );
		g_csgo.m_render_view->SetBlend( player->is_protected() ? 0.3f : 1.f );

		player->DrawModel( 1, 255 );
	}
}

bool Visuals::world_chams( Hooks::DrawModel_t orig, uintptr_t ecx, uintptr_t results, DrawModelInfo_t &info, matrix3x4_t *pBoneToWorld, float *pFlexWeights, float *pFlexDelayedWeights, Vec3_t &draw_modelin, int drawFlags ) {
	DrawModelParams draw_model = DrawModelParams{ orig, ecx, results, info, pBoneToWorld, pFlexWeights, pFlexDelayedWeights, draw_modelin, drawFlags };
	
	static IMaterial *mat[ 4 ];

	static bool once{ false };
	if( !once ) {
		mat[ 0 ] = CSGO_Util::create_material( true, false, false ); // material.
		mat[ 1 ] = CSGO_Util::create_material( false, false, false ); // flat.
		mat[ 2 ] = CSGO_Util::create_material( true, false, true ); // material zignore.
		mat[ 3 ] = CSGO_Util::create_material( false, false, true ); // flat zignore.
		once = true;
	}

	C_CSPlayer *entity = (C_CSPlayer *)( (ulong_t)info.m_pClientEntity - 4 );
	studiohdr_t *hdr = info.m_pStudioHdr;

	if( !entity || !hdr || !g_cl.m_local )
		return false;

	std::string model_name = hdr->name;
	if( model_name.find( "shadow" ) != std::string::npos )
		return false;

	activation_type();

	if( g_cvar.m_visuals.cham_lagrecords->iValue && g_cvar.m_visuals.player_chams->bValue && ( model_name.find( "player" ) != std::string::npos && entity->GetClientClass()->m_ClassID == CCSPLAYER && m_enabled ) ) {
		if( !g_cvar.m_visuals.teammates->bValue && g_cl.m_local->get_team_index() == entity->get_team_index() )
			return false;

		PlayerRecord_t *entry = &g_lagcomp.m_players[ entity->GetIndex() - 1 ];
		if( entry->m_records.empty() )
			return false;

		OSHGui::Drawing::Color twopass_color = Config::string_to_color( 255, g_cvar.m_colors.ignorez_color->szValue );
		OSHGui::Drawing::Color cham_color = Config::string_to_color( 255, g_cvar.m_colors.cham_color->szValue );
		OSHGui::Drawing::Color record_color = Config::string_to_color( 255, g_cvar.m_colors.lag_record_color->szValue );

		if( g_cvar.m_visuals.cham_lagrecords->iValue == 1 ) {
			for( auto record = entry->m_records.begin(); record != entry->m_records.end(); ++record ) {
				if( !record->is_valid_record() )
					continue;

				if( g_cvar.m_visuals.player_chams_ignorez->bValue ) {
					mat[ 2 ]->SetColor( record_color.GetRed(), record_color.GetGreen(), record_color.GetBlue() );
					mat[ 2 ]->SetAlpha( 0.4f );
					g_csgo.m_model_render->ForcedMaterialOverride( mat[ 2 ] );
				}
				else {
					mat[ 0 ]->SetColor( record_color.GetRed(), record_color.GetGreen(), record_color.GetBlue() );
					mat[ 0 ]->SetAlpha( 0.4f );
					g_csgo.m_model_render->ForcedMaterialOverride( mat[ 0 ] );
				}

				draw_model.original( draw_model.ecx, draw_model.results, draw_model.info, record->m_bones.data(), draw_model.p_flex_weights, draw_model.pFlexDelayedWeights, record->m_origin, draw_model.draw_flags );
				
				if( g_cvar.m_visuals.player_chams_ignorez->bValue ) {
					mat[ 2 ]->SetColor( twopass_color.GetRed(), twopass_color.GetGreen(), twopass_color.GetBlue() );
					mat[ 2 ]->SetAlpha( entity->is_protected() ? 0.3f : 1.f );

					g_csgo.m_model_render->ForcedMaterialOverride( mat[ 2 ] );

					draw_model.original( draw_model.ecx, draw_model.results, draw_model.info, draw_model.p_bone_to_world, draw_model.p_flex_weights, draw_model.pFlexDelayedWeights, draw_model.origin, draw_model.draw_flags );
				}

				mat[ 0 ]->SetColor( cham_color.GetRed(), cham_color.GetGreen(), cham_color.GetBlue() );
				mat[ 0 ]->SetAlpha( entity->is_protected() ? 0.3f : 1.f );

				g_csgo.m_model_render->ForcedMaterialOverride( mat[ 0 ] );

				draw_model.original( draw_model.ecx, draw_model.results, draw_model.info, draw_model.p_bone_to_world, draw_model.p_flex_weights, draw_model.pFlexDelayedWeights, draw_model.origin, draw_model.draw_flags );
			}
		}
		else {
			if( entry->m_records.back().is_valid_record() ) {
				if( g_cvar.m_visuals.player_chams_ignorez->bValue ) {
					mat[ 2 ]->SetColor( record_color.GetRed(), record_color.GetGreen(), record_color.GetBlue() );
					mat[ 2 ]->SetAlpha( 0.4f );
					g_csgo.m_model_render->ForcedMaterialOverride( mat[ 2 ] );
				}
				else {
					mat[ 0 ]->SetColor( record_color.GetRed(), record_color.GetGreen(), record_color.GetBlue() );
					mat[ 0 ]->SetAlpha( 0.4f );
					g_csgo.m_model_render->ForcedMaterialOverride( mat[ 0 ] );
				}

				draw_model.original( draw_model.ecx, draw_model.results, draw_model.info, entry->m_records.back().m_bones.data(), draw_model.p_flex_weights, draw_model.pFlexDelayedWeights, entry->m_records.back().m_origin, draw_model.draw_flags );
			}
		}

		if( g_cvar.m_visuals.player_chams_ignorez->bValue ) {
			mat[ 2 ]->SetColor( twopass_color.GetRed(), twopass_color.GetGreen(), twopass_color.GetBlue() );
			mat[ 2 ]->SetAlpha( entity->is_protected() ? 0.3f : 1.f );

			g_csgo.m_model_render->ForcedMaterialOverride( mat[ 2 ] );

			draw_model.original( draw_model.ecx, draw_model.results, draw_model.info, draw_model.p_bone_to_world, draw_model.p_flex_weights, draw_model.pFlexDelayedWeights, draw_model.origin, draw_model.draw_flags );
		}

		mat[ 0 ]->SetColor( cham_color.GetRed(), cham_color.GetGreen(), cham_color.GetBlue() );
		mat[ 0 ]->SetAlpha( entity->is_protected() ? 0.3f : 1.f );

		g_csgo.m_model_render->ForcedMaterialOverride( mat[ 0 ] );

		draw_model.original( draw_model.ecx, draw_model.results, draw_model.info, draw_model.p_bone_to_world, draw_model.p_flex_weights, draw_model.pFlexDelayedWeights, draw_model.origin, draw_model.draw_flags );

		return true;
	}

	if( g_cvar.m_visuals.cham_arms->bValue && ( model_name.find( "v_glove" ) != std::string::npos || model_name.find( "arms" ) != std::string::npos ) ) {
		OSHGui::Drawing::Color hand_color = Config::string_to_color( 255, g_cvar.m_colors.arms_color->szValue );

		mat[ 2 ]->SetColor( hand_color.GetRed(), hand_color.GetGreen(), hand_color.GetBlue() );
		mat[ 2 ]->SetAlpha( 1.f );
		mat[ 2 ]->SetVarFlag( MATERIAL_VAR_WIREFRAME, true );

		g_csgo.m_model_render->ForcedMaterialOverride( mat[ 2 ] );

		draw_model.original( draw_model.ecx, draw_model.results, draw_model.info, draw_model.p_bone_to_world, draw_model.p_flex_weights, draw_model.pFlexDelayedWeights, draw_model.origin, draw_model.draw_flags );

		mat[ 0 ]->SetColor( hand_color.GetRed(), hand_color.GetGreen(), hand_color.GetBlue() );
		mat[ 0 ]->SetAlpha( 1.f );

		g_csgo.m_model_render->ForcedMaterialOverride( mat[ 0 ] );

		draw_model.original( draw_model.ecx, draw_model.results, draw_model.info, draw_model.p_bone_to_world, draw_model.p_flex_weights, draw_model.pFlexDelayedWeights, draw_model.origin, draw_model.draw_flags );

		return true;
	}

	if( g_cvar.m_visuals.cham_weapon->bValue && ( model_name.find( "weapon" ) != std::string::npos && model_name.find( "arms" ) == std::string::npos && model_name.find( "w_" ) == std::string::npos ) ) {
		OSHGui::Drawing::Color weapon_color = Config::string_to_color( 255, g_cvar.m_colors.weapon_cham_color->szValue );
		
		mat[ 2 ]->SetColor( weapon_color.GetRed(), weapon_color.GetGreen(), weapon_color.GetBlue() );
		mat[ 2 ]->SetAlpha( 1.f );
		mat[ 2 ]->SetVarFlag( MATERIAL_VAR_WIREFRAME, true );

		g_csgo.m_model_render->ForcedMaterialOverride( mat[ 2 ] );

		draw_model.original( draw_model.ecx, draw_model.results, draw_model.info, draw_model.p_bone_to_world, draw_model.p_flex_weights, draw_model.pFlexDelayedWeights, draw_model.origin, draw_model.draw_flags );

		mat[ 0 ]->SetColor( weapon_color.GetRed(), weapon_color.GetGreen(), weapon_color.GetBlue() );
		mat[ 0 ]->SetAlpha( 1.f );

		g_csgo.m_model_render->ForcedMaterialOverride( mat[ 0 ] );

		draw_model.original( draw_model.ecx, draw_model.results, draw_model.info, draw_model.p_bone_to_world, draw_model.p_flex_weights, draw_model.pFlexDelayedWeights, draw_model.origin, draw_model.draw_flags );

		return true;
	}

	//if( g_cvar.m_visuals.champlayer_weapon->bValue ) {
	//	if ( model_name.find( "w_c4" ) != std::string::npos 
	//		 || model_name.find( "w_knife" ) != std::string::npos
	//		 || model_name.find( "w_mach" ) != std::string::npos
	//		 || model_name.find( "w_pist" ) != std::string::npos
	//		 || model_name.find( "w_rif" ) != std::string::npos
	//		 || model_name.find( "w_shot" ) != std::string::npos
	//		 || model_name.find( "w_smg" ) != std::string::npos
	//		 || model_name.find( "w_snip" ) != std::string::npos) {
	//			hand_mat[ 0 ]->SetColor( 1.f, 0.f, 1.f );
	//			hand_mat[ 0 ]->SetAlpha( 1.f );

	//			g_csgo.m_model_render->ForcedMaterialOverride( hand_mat[ 0 ] );

	//			p.oDrawModel( p._this, p.results, p.info, p.pBoneToWorld, p.pFlexWeights, p.pFlexDelayedWeights, p.draw_modelin, p.drawFlags );

	//			return true;
	//	}
	//}

	return false;
}

// credits: n0xius.
void Visuals::grenade_prediction( C_CSPlayer *local, C_BaseCombatWeapon *weapon ) {
	if( !weapon->is_grenade() || !g_cl.m_cmd )
		return;

	if( weapon->get_pin_pulled() ) {
		auto get_grenade_detonate_time = [ ]( int item ) {
			switch( item ) {
			case WEAPON_FLASH:
			case WEAPON_HE:
				return 1.5f;
				break;
			case WEAPON_INC:
			case WEAPON_MOLOTOV:
				return g_csgo.m_convar->FindVar( "molotov_throw_detonate_time" )->GetFloat( );
				break;
			default:
				break;
			}

			return 3.f;
		};

		auto physics_clip_velocity = [ ]( const Vec3_t &in, const Vec3_t &normal, Vec3_t &out, float overbounce ) {
			int blocked = 0;

			float angle = normal[ 2 ];

			if( angle > 0 )
				blocked |= 1; // floor.

			if( !angle )
				blocked |= 2; // step.

			float backoff = in.dot( normal ) * overbounce;

			for( int i = 0; i < 3; i++ ) {
				float change = normal[ i ] * backoff;
				out[ i ] = in[ i ] - change;

				if( out[ i ] > -0.1f && out[ i ] < 0.1f )
					out[ i ] = 0;
			}

			return blocked;
		};

		auto draw_line = [ ]( Vec3_t start, Vec3_t end ) {
			Vec3_t start_w2s, end_w2s;
			if( !g_visuals.world_to_screen( start, start_w2s ) || !g_visuals.world_to_screen( end, end_w2s ) )
				return;

			g_custom_renderer.line( Config::string_to_color( 255, g_cvar.m_colors.trajectory_color->szValue ), start_w2s.x, start_w2s.y, end_w2s.x, end_w2s.y );
		};

		player_info_t player_info;
		int item_index = weapon->get_item_definition_index();
		const WeaponInfo_t *weapon_info = g_csgo.m_weapon_system->GetWpnData( weapon->get_item_definition_index() );
		//WeaponInfo_t *weapon_info = weapon->get_weapon_info();

		Vec3_t ang_throw, forward;

		g_csgo.m_engine->GetViewAngles( ang_throw );

		if( ang_throw.x <= 90.f ) {
			if( ang_throw.x < -90.f )
				ang_throw.x += 360.f;
		}
		else {
			ang_throw.x -= 360.f;
		}

		ang_throw.x -= ( 90.f - std::abs( ang_throw.x ) ) * 0.11111111f;

		Math::angle_to_vector( ang_throw, forward );

		float throw_strengh = weapon->get_grenade_throw_strength();
		float throw_velocity = std::fmin( std::fmax( weapon_info->m_flThrowVelocity * 0.9f, 15.f ), 750.f );

		float throw_height = throw_strengh * 12.f - 12.f;
		float v68 = throw_velocity * ( 0.7f * throw_strengh + 0.3f );

		Vec3_t start_pos = g_cl.m_local->get_eye_position() + Vec3_t( 0, 0, throw_height ), end_pos = start_pos + forward * 22.f;

		CTraceFilter filter;
		filter.m_skip = g_cl.m_local;
		CGameTrace trace;

		g_csgo.m_engine_trace->TraceRay( Ray_t( start_pos, end_pos, Vec3_t( -2.f, -2.f, -2.f ), Vec3_t( 2.f, 2.f, 2.f ) ), 0x200400B, &filter, &trace );

		end_pos = trace.endpos - forward * 6.f;
		Vec3_t throw_pos = g_cl.m_local->get_velocity() * 1.25f + forward * v68;

		float gravity = g_csgo.m_convar->FindVar( "sv_gravity" )->GetFloat() * 0.4f;

		for( int ticks = TIME_TO_TICKS( get_grenade_detonate_time( item_index ) ); ticks >= 0; --ticks ) {
			Vec3_t throw_dir = Vec3_t( throw_pos.x, throw_pos.y, ( throw_pos.z + ( throw_pos.z - gravity * g_csgo.m_global_vars->m_interval_per_tick ) ) * 0.5f );
			Vec3_t temp = throw_dir * g_csgo.m_global_vars->m_interval_per_tick;

			throw_pos.z -= gravity * g_csgo.m_global_vars->m_interval_per_tick;

			Vec3_t src = end_pos, end = end_pos + temp;

			g_csgo.m_engine_trace->TraceRay( Ray_t( src, end, Vec3_t( -2.f, -2.f, -2.f ), Vec3_t( 2.f, 2.f, 2.f ) ), 0x200400B, &filter, &trace );

			if( trace.allsolid )
				throw_pos = Vec3_t( 0, 0, 0 );

			end_pos = trace.endpos;
			draw_line( src, end_pos );

			if( trace.fraction != 1.f ) {
				float surface_elasticity = 1.f;

				Vec3_t throw_pos2;

				physics_clip_velocity( throw_pos, trace.plane.m_normal, throw_pos2, 2.f );

				if( trace.hit_entity && g_csgo.m_engine->GetPlayerInfo( trace.hit_entity->GetIndex( ), &player_info ) )
					surface_elasticity = 0.3f;

				throw_pos2 *= Utils::clamp( surface_elasticity * 0.45f, 0.f, 0.9f );

				end = end_pos + throw_pos2 * ( ( 1.f - trace.fraction ) * g_csgo.m_global_vars->m_interval_per_tick );

				if( item_index == WEAPON_MOLOTOV || item_index == WEAPON_INC ) {
					if( trace.plane.m_normal.z >= std::cos( Math::deg_to_rad( g_csgo.m_convar->FindVar( "weapon_molotov_maxdetonateslope" )->GetFloat() ) ) ) {
						draw_3d_dotted_circle( end_pos, 100, 150, OSHColor::FromARGB( 255, 255, 255, 255 ) );
						return;
					}
				}

				g_csgo.m_engine_trace->TraceRay( Ray_t( end_pos, end, Vec3_t( -2.f, -2.f, -2.f ), Vec3_t( 2.f, 2.f, 2.f ) ), 0x200400B, &filter, &trace );

				draw_line( end_pos, end );

				Vec3_t angles;
				Math::angle_to_vector( trace.endpos - trace.startpos, angles );

				Vec3_t end_pos_w2s;
				if( g_visuals.world_to_screen( end_pos, end_pos_w2s ) )
					g_custom_renderer.rect( OSHColor::FromARGB( 255, 255, 255, 255 ), end_pos_w2s.x - 3, end_pos_w2s.y - 3, 5, 5 );

				//draw_cube( 1.f, angles, end_pos );

				end_pos = trace.endpos;			
				throw_pos = throw_pos2;
			}
		}
	}
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

void Visuals::draw_cube( float scalar, Vec3_t angles, Vec3_t middle_origin ) {
	Vec3_t forward, right, up;
	Math::angle_to_vectors( angles, &forward, &right, &up );

	Vec3_t points[ 8 ];
	points[ 0 ] = middle_origin - right * scalar + up * scalar - forward * scalar;
	points[ 1 ] = middle_origin + right * scalar + up * scalar - forward * scalar;
	points[ 2 ] = middle_origin - right * scalar - up * scalar - forward * scalar;
	points[ 3 ] = middle_origin + right * scalar - up * scalar - forward * scalar;
		      
	points[ 4 ] = middle_origin - right * scalar + up * scalar + forward * scalar;
	points[ 5 ] = middle_origin + right * scalar + up * scalar + forward * scalar;
	points[ 6 ] = middle_origin - right * scalar - up * scalar + forward * scalar;
	points[ 7 ] = middle_origin + right * scalar - up * scalar + forward * scalar;

	Vec3_t points_screen[ 8 ];
	for (int i = 0; i < 8; i++)
		if( !world_to_screen( points[ i ], points_screen[ i ] ) )
			return;

	g_custom_renderer.line( OSHColor::White(), points_screen[ 0 ].x, points_screen[ 0 ].y, points_screen[ 1 ].x, points_screen[ 1 ].y );
	g_custom_renderer.line( OSHColor::White(), points_screen[ 0 ].x, points_screen[ 0 ].y, points_screen[ 2 ].x, points_screen[ 2 ].y );
	g_custom_renderer.line( OSHColor::White(), points_screen[ 3 ].x, points_screen[ 3 ].y, points_screen[ 1 ].x, points_screen[ 1 ].y );
	g_custom_renderer.line( OSHColor::White(), points_screen[ 3 ].x, points_screen[ 3 ].y, points_screen[ 2 ].x, points_screen[ 2 ].y );

	g_custom_renderer.line( OSHColor::White(), points_screen[ 0 ].x, points_screen[ 0 ].y, points_screen[ 4 ].x, points_screen[ 4 ].y );
	g_custom_renderer.line( OSHColor::White(), points_screen[ 1 ].x, points_screen[ 1 ].y, points_screen[ 5 ].x, points_screen[ 5 ].y );
	g_custom_renderer.line( OSHColor::White(), points_screen[ 2 ].x, points_screen[ 2 ].y, points_screen[ 6 ].x, points_screen[ 6 ].y );
	g_custom_renderer.line( OSHColor::White(), points_screen[ 3 ].x, points_screen[ 3 ].y, points_screen[ 7 ].x, points_screen[ 7 ].y );

	g_custom_renderer.line( OSHColor::White(), points_screen[ 4 ].x, points_screen[ 4 ].y, points_screen[ 5 ].x, points_screen[ 5 ].y );
	g_custom_renderer.line( OSHColor::White(), points_screen[ 4 ].x, points_screen[ 4 ].y, points_screen[ 6 ].x, points_screen[ 6 ].y );
	g_custom_renderer.line( OSHColor::White(), points_screen[ 7 ].x, points_screen[ 7 ].y, points_screen[ 5 ].x, points_screen[ 5 ].y );
	g_custom_renderer.line( OSHColor::White(), points_screen[ 7 ].x, points_screen[ 7 ].y, points_screen[ 6 ].x, points_screen[ 6 ].y );
}

void Visuals::draw_3d_dotted_circle( Vec3_t position, float points, float radius, OSHColor color ) {
	float step = Math::pi * 2.0f / points;

	for( float a = 0; a < Math::pi * 2.0f; a += step ) {
		Vec3_t start( radius * cosf( a ) + position.x, radius * sinf( a ) + position.y, position.z );

		Vec3_t start2d;
		if( world_to_screen( start, start2d ) )
			g_custom_renderer.line( color, start2d.x, start2d.y, start2d.x + 1, start2d.y + 1 );
	}
}

void Visuals::nightmode() {
	//if( m_nightmode != g_cvar.m_visuals.nightmode->bValue ) {
	//	// change sky.
	//	if( g_cvar.m_visuals.nightmode->bValue )
	//		CSGO_Util::change_sky( "sky_csgo_night02b" );
	//	else
	//		CSGO_Util::change_sky( "nukeblank" ); // todo: need to backup old sky.

	//	static ConVar *r_drawspecificstaticprop = g_csgo.m_convar->FindVar( "r_drawspecificstaticprop" );
	//	r_drawspecificstaticprop->SetValue( 0 );

	//	for( int i = g_csgo.m_material_system->FirstMaterial(); i != g_csgo.m_material_system->InvalidMaterial(); i = g_csgo.m_material_system->NextMaterial( i ) ) {
	//		IMaterial *material = g_csgo.m_material_system->FindMaterial( i );

	//		if ( !material || material->IsErrorMaterial() )
	//			continue;

	//		if( std::strstr( material->GetTextureGroupName(), "Model" ) 
	//			|| std::strstr( material->GetTextureGroupName(), "StaticProp" )
	//			|| std::strstr( material->GetName(), "sky_csgo_night02b" ) ) {
	//			static float r, g, b;

	//			static bool once{ false };
	//			if( !once ) {
	//				material->GetColorModulation( &r, &g, &b );
	//				once = true;
	//			}

	//			if( g_cvar.m_visuals.nightmode->bValue )
	//				material->SetColor( 0.30f, 0.30f, 0.30f );
	//			else
	//				material->SetColor( r, g, b );
	//		}

	//		if( std::strstr( material->GetTextureGroupName(), "World" ) ) {
	//			static float r, g, b;

	//			static bool once{ false };
	//			if( !once ) {
	//				material->GetColorModulation( &r, &g, &b );
	//				once = true;
	//			}

	//			if( g_cvar.m_visuals.nightmode->bValue )
	//				material->SetColor( 0.03f, 0.03f, 0.03f );
	//			else
	//				material->SetColor( r, g, b );
	//		}

	//		/*if( std::strstr( material->GetName(), "glass" )
	//			|| std::strstr( material->GetName(), "decals" )
	//			|| std::strstr( material->GetName(), "door" )
	//			|| std::strstr( material->GetName(), "dust" )
	//			|| std::strstr( material->GetName(), "mirage" )
	//			|| std::strstr( material->GetName(), "brick" )
	//			|| std::strstr( material->GetName(), "plywood" ) ) {
	//			static float r, g, b;

	//			static bool once{ false };
	//			if( !once ) {
	//				material->GetColorModulation( &r, &g, &b );
	//				once = true;
	//			}

	//			if( g_cvar.m_visuals.nightmode->bValue )
	//				material->SetColor( 0.20f, 0.20f, 0.20f );
	//			else
	//				material->SetColor( r, g, b );
	//		}*/

	//		// remove the sun (some maps have the sun on the skybox).
	//		if( g_cvar.m_visuals.nightmode->bValue ) {
	//			if( std::strstr( material->GetName(), "light_glow02" ) )
	//				material->SetVarFlag( MATERIAL_VAR_NO_DRAW, true );
	//		}
	//		else {
	//			if( std::strstr( material->GetName(), "light_glow02" ) )
	//				material->SetVarFlag( MATERIAL_VAR_NO_DRAW, false );		
	//		}
	//	}

	//	m_nightmode = g_cvar.m_visuals.nightmode->bValue;
	//}
}

void Visuals::remove_scopedirt() {
	try {
		if( m_scopedirt != g_cvar.m_visuals.remove_scopedirt->bValue ) {
			for( int i = g_csgo.m_material_system->FirstMaterial(); i != g_csgo.m_material_system->InvalidMaterial(); i = g_csgo.m_material_system->NextMaterial( i ) ) {
				IMaterial *material = g_csgo.m_material_system->FindMaterial( i );

				if( !material || material->IsErrorMaterial() || !g_csgo.m_engine->IsInGame() )
					continue;

				if( g_cvar.m_visuals.remove_scopedirt->bValue ) {
					if( std::strstr( material->GetName(), "lens" ) )
						material->SetVarFlag( MATERIAL_VAR_NO_DRAW, true );
					if( std::strstr( material->GetName(), "scope_bluroverlay" ) )
						material->SetVarFlag( MATERIAL_VAR_NO_DRAW, true );
				} 
				else {
					if( std::strstr( material->GetName(), "lens" ) )
						material->SetVarFlag( MATERIAL_VAR_NO_DRAW, false );
					if( std::strstr( material->GetName(), "scope_bluroverlay" ) )
						material->SetVarFlag( MATERIAL_VAR_NO_DRAW, false );
				}

			}

			m_scopedirt = g_cvar.m_visuals.remove_scopedirt->bValue;
		}
	} 
	catch( ... ) {
		
	}
}

void Visuals::remove_smoke() {
	if( m_smoke != g_cvar.m_visuals.remove_smoke->bValue ) {
		ClientClass *get_class = g_csgo.m_client->GetAllClasses();

		while( get_class ) {
			if( !std::strcmp( get_class->m_pRecvTable->m_pNetTableName, "DT_SmokeGrenadeProjectile" ) ) {
				for( int i = 0; i < get_class->m_pRecvTable->m_nProps; ++i ) {
					RecvProp *prop = &get_class->m_pRecvTable->m_pProps[ i ];
					const char *prop_name = prop->m_pVarName;

					if( !std::strcmp( prop_name, "m_nSmokeEffectTickBegin" ) ) {
						auto no_smoke_proxy_int = []( const RecvProxyData *data, void *_struct, void *out ) {
							int begin = data->m_Value.m_Int;

							if( g_cvar.m_visuals.remove_smoke->bValue ) {
								begin = 0;
								*(int *)out = begin;
							}
							else if( !g_cvar.m_visuals.remove_smoke->bValue ) {
								*(int *)out = begin;
							}
						};

						prop->m_ProxyFn = no_smoke_proxy_int;
					}
						
					if( !std::strcmp( prop_name, "m_bDidSmokeEffect" ) ) {
						auto no_smoke_proxy_bool = []( const RecvProxyData *data, void *_struct, void *out ) {
							int begin = data->m_Value.m_Int;

							if( g_cvar.m_visuals.remove_smoke->bValue ) {
								static ulong_t smoke_count = *(ulong_t *)( g_offsets.m_LineGoesThruSmoke + 8 );
								*(char *)smoke_count = 0;
								*(int *)out = 0;
							}
							else if( !g_cvar.m_visuals.remove_smoke->bValue ) {
								*(int *)out = begin;
							}
						};

						prop->m_ProxyFn = no_smoke_proxy_bool;
					}
				}
			}

			get_class = get_class->m_pNext;
		}

		m_smoke = g_cvar.m_visuals.remove_smoke->bValue;
	}
}

void Visuals::draw_scope() {
	if ( !g_cl.m_local->is_scoped() || !g_cl.m_local->get_active_weapon()->is_sniper() )
		return;

	OSHGui::Drawing::SizeF display_size = g_custom_renderer.m_instance->GetRenderer().GetDisplaySize();

	g_custom_renderer.filled_rect( OSHColor::Black(), 0, display_size.Height * 0.5f, display_size.Width, 1 );
	g_custom_renderer.filled_rect( OSHColor::Black(), display_size.Width * 0.5f, 0, 1, display_size.Height );
}

void Visuals::draw_records( C_CSPlayer *entity ) {
	if( !entity->is_valid_player( false, true ) || g_cl.m_local->get_health() <= 0 )
		return;

	try {
		PlayerRecord_t *entry = &g_lagcomp.m_players[ entity->GetIndex() - 1 ];
		if( entry->m_records.empty() )
			return;

		for( size_t i = 0; i < g_lagcomp.m_max_records - 1; i++ ) {
			if( !entry->m_records.at( i ).is_valid_record() )
				return;

			Vec3_t bone_screen;
			if( !world_to_screen( entity->get_bone_position( entry->m_records.at( i ).m_bones, 8 ), bone_screen ) )
				return;

			g_custom_renderer.filled_rect( Config::string_to_color( 255, g_cvar.m_colors.lag_record_color->szValue ), bone_screen.x, bone_screen.y, 2, 2 );
		}
	}
	catch( ... ) {
		/*std::string str = e.what();
		str += "\n";
		CSGO_Util::push_notification( Color::Red(), str.c_str() );*/
	}
}

void Visuals::skeleton( C_CSPlayer *player ) {
	const model_t *model = player->GetModel();
	if( !model )
		return;

	studiohdr_t* studio_hdr = g_csgo.m_model_info->GetStudioModel( model );
	if( !studio_hdr )
		return;

	std::array<matrix3x4_t, 128> matrix;
	if( !player->SetupBones( matrix.data(), matrix.size(), 0x100, player->get_simtime() ) )
		return;

	for( int i = 0; i < studio_hdr->numbones; i++ ) {
		mstudiobone_t* bone = studio_hdr->pBone( i );

		if( !bone || !( bone->flags & 0x100 ) || bone->parent == -1 )
			continue;

		Vec3_t bone_position, parent_position;
		Vec3_t bone_screen, parent_screen;

		Math::matrix_position( matrix.at( i ), bone_position );
		Math::matrix_position( matrix.at( bone->parent ), parent_position );

		if( !world_to_screen( bone_position, bone_screen ) || !world_to_screen( parent_position, parent_screen ) )
			continue;

		g_custom_renderer.line( Config::string_to_color( g_visuals.m_player_alpha[ player->GetIndex() ], g_cvar.m_colors.skeleton_color->szValue ), bone_screen.x, bone_screen.y, parent_screen.x, parent_screen.y );
	}
}

void Visuals::draw_spectators() {
	int spec_count = 0;

	for( int i = 1; i <= g_csgo.m_global_vars->m_max_clients; i++ ) {
		C_CSPlayer *entity = (C_CSPlayer *)g_csgo.m_entity_list->GetClientEntity( i );
		if( !entity || entity->get_health() > 0 || !g_cl.m_local || entity == g_cl.m_local )
			continue;

		C_CSPlayer *spectator = (C_CSPlayer *)g_csgo.m_entity_list->GetClientEntityFromHandle( entity->get_observer_target_handle() );
		if( !spectator )
			continue;

		/*if( spectator->get_health() > 0 )
			continue;*/

		player_info_s player_info_spec;
		if( !g_csgo.m_engine->GetPlayerInfo( i, &player_info_spec ) )
			continue;

		if( player_info_spec.m_szPlayerName == "GOTV" /*|| player_info_spec.m_bIsFakePlayer*/ )
			continue;

		if( spectator != g_cl.m_local )
			continue;

		OSHGui::Drawing::SizeF display_size = g_custom_renderer.m_instance->GetRenderer().GetDisplaySize();
		g_custom_renderer.ansi_text( g_custom_renderer.m_fonts[ FONT_VERDANA_BOLD_7PX ], OSHColor::FromARGB( 200, 255, 255, 255 ), OSHColor::FromARGB( 200, 10, 10, 10 ), 
									 display_size.Width - 150, display_size.Height / 2 + 10 * spec_count - 240, DROPSHADOW, "%s", player_info_spec.m_szPlayerName );

		spec_count++;
	}
}

void Visuals::draw_glow() {
	activation_type();
	if( !m_enabled )
		return;

	static CGlowObjectManager *glow_object_manager = (CGlowObjectManager *)*(ulong_t *)g_offsets.m_GlowObjectManager;
	if( !glow_object_manager )
		return;

	for( int i = 0; i < glow_object_manager->m_size; i++ ) {
		if( glow_object_manager->m_glow_object_definitions[ i ].is_unused() || !glow_object_manager->m_glow_object_definitions[ i ].get_entity() )
			continue;

		CGlowObjectManager::GlowObjectDefinition_t* glow_object_definition = &glow_object_manager->m_glow_object_definitions[ i ];
		if( !glow_object_definition )
			continue;

		C_CSPlayer *entity = (C_CSPlayer *)glow_object_definition->get_entity();
		if( !entity || entity == g_cl.m_local )
			continue;

		ClientClass *client_class = entity->GetClientClass();
		if( !client_class )
			continue;

		OSHGui::Drawing::Color color = Config::string_to_color( 190, g_cvar.m_colors.glow_color->szValue );

		if( !g_cvar.m_visuals.teammates->bValue && g_cl.m_local->get_team_index() == entity->get_team_index() )
			continue;

		if( g_cvar.m_visuals.visible_only->bValue && (!g_cl.m_local->is_visible( entity, g_cl.m_local->get_eye_position(), entity->get_eye_position(), MASK_SHOT, g_cl.m_local ) || g_cl.m_local->get_flashed() > 140.f ) )
			continue;

		if( g_cvar.m_visuals.disable_thru_smoke->bValue && CSGO_Util::line_goes_thru_smoke( g_cl.m_local->get_eye_position(), entity->GetAbsOrigin() ) )
			continue;

		switch( client_class->m_ClassID ) {
			case CCSPLAYER: {
				float flash_alpha = entity->get_flashed();
				flash_alpha > 50.f ? glow_object_definition->set( 1.f, 1.f, 1.f, flash_alpha / 255.f, g_cvar.m_visuals.glow_type->iValue ) : glow_object_definition->set( color.GetRed(), color.GetGreen(), color.GetBlue(), 0.65f, g_cvar.m_visuals.glow_type->iValue );
				break;
			}
			default: break;
		}
	}
}

void Visuals::watermark() {
	OSHGui::Drawing::SizeF display_size = g_custom_renderer.m_instance->GetRenderer().GetDisplaySize();
	
	bool connected = g_csgo.m_engine->IsConnected();

	g_custom_renderer.filled_rect( OSHColor::FromARGB( 160, 208, 115, 137 ), display_size.Width - 270, display_size.Height - display_size.Height + 20, 250, 15 );

	time_t t = std::time( nullptr );
	tm tm = *std::localtime( &t );

	std::ostringstream oss;
	oss << std::put_time(&tm, "%I:%M%p");
	auto time = oss.str();

	if( connected )
		g_custom_renderer.ansi_text( g_custom_renderer.m_fonts[ FONT_VERDANA_7PX ], OSHColor( 0.8f, 1.f, 1.f, 1.f ),
		                             OSHColor( 0.f, 0.f, 0.f, 0.f ), display_size.Width - 268, display_size.Height - display_size.Height + 22, 0,
		                             "deadcell.cc | %s | out %ims | rtt %ims", time.c_str(), g_cl.m_ping, g_cl.m_rtt );
	else
		g_custom_renderer.ansi_text( g_custom_renderer.m_fonts[ FONT_VERDANA_7PX ], OSHColor( 0.8f, 1.f, 1.f, 1.f ),
		                             OSHColor( 0.f, 0.f, 0.f, 0.f ), display_size.Width - 268, display_size.Height - display_size.Height + 22, 0,
									 "deadcell.cc | unconnected | %s", time.c_str() );
}

void Visuals::draw_out_of_fov( const Vec3_t &delta, float *rot ) {

}

void Visuals::draw_hitmarker() {
	OSHGui::Drawing::SizeF display_size = g_custom_renderer.m_instance->GetRenderer().GetDisplaySize();
	
	if( g_events.m_player_hurt->m_hitmarker_alpha > 0.f ) {
		g_custom_renderer.line( OSHColor( g_events.m_player_hurt->m_hitmarker_alpha, 1.f, 1.f, 1.f ), display_size.Width / 2.f - 8.f, display_size.Height / 2.f - 8.f, display_size.Width / 2.f - 3.f, display_size.Height / 2.f - 3.f );
		g_custom_renderer.line( OSHColor( g_events.m_player_hurt->m_hitmarker_alpha, 1.f, 1.f, 1.f ), display_size.Width / 2.f - 8.f, display_size.Height / 2.f + 8.f, display_size.Width / 2.f - 3.f, display_size.Height / 2.f + 3.f );
		g_custom_renderer.line( OSHColor( g_events.m_player_hurt->m_hitmarker_alpha, 1.f, 1.f, 1.f ), display_size.Width / 2.f + 8.f, display_size.Height / 2.f - 8.f, display_size.Width / 2.f + 3.f, display_size.Height / 2.f - 3.f );
		g_custom_renderer.line( OSHColor( g_events.m_player_hurt->m_hitmarker_alpha, 1.f, 1.f, 1.f ), display_size.Width / 2.f + 8.f, display_size.Height / 2.f + 8.f, display_size.Width / 2.f + 3.f, display_size.Height / 2.f + 3.f );

		g_events.m_player_hurt->m_hitmarker_alpha -= 1.f / 0.5f * g_csgo.m_global_vars->m_frametime;
	}
}

void Visuals::draw_crosshair( C_BaseCombatWeapon *weapon ) {
	OSHGui::Drawing::SizeF display_size = g_custom_renderer.m_instance->GetRenderer().GetDisplaySize();

	float spread_distance = ( weapon->get_inaccuracy() + weapon->get_spread() ) * 320.f / std::tan( Math::deg_to_rad( g_cvar.m_visuals.override_fov->iValue ) * 0.5f );
	float spread_radius = display_size.Height * 2 * 0.002083 * spread_distance;

	g_custom_renderer.circle( Config::string_to_color( 0.2f, g_cvar.m_colors.inaccuracy_color->szValue ), display_size.Width / 2, display_size.Height / 2, spread_radius );
}