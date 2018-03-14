#include "includes.h"

#include <experimental/filesystem>

// todo - finish this...

#define REGISTER_CVAR( r, n, t, v ) r = cfg_manager.CVar::Add( n, t, v );

void Config::init() {
	if( !cfg_manager.is_ready() )
		return;

	cfg_manager.set_script_directory( m_directory );

	// legit
	REGISTER_CVAR( g_cvar.m_legit.pistol_historyaim, "legit_pistols_historyaim", config_manager::CVar::CVAR_TYPE_INT, "0" );
	REGISTER_CVAR( g_cvar.m_legit.smg_historyaim, "legit_smgs_historyaim", config_manager::CVar::CVAR_TYPE_INT, "0" );
	REGISTER_CVAR( g_cvar.m_legit.rifle_historyaim, "legit_rifles_historyaim", config_manager::CVar::CVAR_TYPE_INT, "0" );
	REGISTER_CVAR( g_cvar.m_legit.shotgun_historyaim, "legit_shotguns_historyaim", config_manager::CVar::CVAR_TYPE_INT, "0" );
	REGISTER_CVAR( g_cvar.m_legit.sniper_historyaim, "legit_snipers_historyaim", config_manager::CVar::CVAR_TYPE_INT, "0" );

	REGISTER_CVAR( g_cvar.m_legit.pistol_trigger, "legit_pistols_trigger", config_manager::CVar::CVAR_TYPE_BOOL, "0" );
	REGISTER_CVAR( g_cvar.m_legit.smg_trigger, "legit_smgs_trigger", config_manager::CVar::CVAR_TYPE_BOOL, "0" );
	REGISTER_CVAR( g_cvar.m_legit.rifle_trigger, "legit_rifles_trigger", config_manager::CVar::CVAR_TYPE_BOOL, "0" );
	REGISTER_CVAR( g_cvar.m_legit.shotgun_trigger, "legit_shotguns_trigger", config_manager::CVar::CVAR_TYPE_BOOL, "0" );
	REGISTER_CVAR( g_cvar.m_legit.sniper_trigger, "legit_snipers_trigger", config_manager::CVar::CVAR_TYPE_BOOL, "0" );

	REGISTER_CVAR( g_cvar.m_legit.pistol_trigger_key, "legit_pistols_trigger_key", config_manager::CVar::CVAR_TYPE_INT, "5" );
	REGISTER_CVAR( g_cvar.m_legit.smg_trigger_key, "legit_smgs_trigger_key", config_manager::CVar::CVAR_TYPE_INT, "5" );
	REGISTER_CVAR( g_cvar.m_legit.rifle_trigger_key, "legit_rifles_trigger_key", config_manager::CVar::CVAR_TYPE_INT, "5" );
	REGISTER_CVAR( g_cvar.m_legit.shotgun_trigger_key, "legit_shotguns_trigger_key", config_manager::CVar::CVAR_TYPE_INT, "5" );
	REGISTER_CVAR( g_cvar.m_legit.sniper_trigger_key, "legit_snipers_trigger_key", config_manager::CVar::CVAR_TYPE_INT, "5" );

	REGISTER_CVAR( g_cvar.m_legit.pistol_trigger_hitgroup, "legit_pistols_trigger_hitgroup", config_manager::CVar::CVAR_TYPE_INT, "0" );
	REGISTER_CVAR( g_cvar.m_legit.smg_trigger_hitgroup, "legit_smgs_trigger_hitgroup", config_manager::CVar::CVAR_TYPE_INT, "0" );
	REGISTER_CVAR( g_cvar.m_legit.rifle_trigger_hitgroup, "legit_rifles_trigger_hitgroup", config_manager::CVar::CVAR_TYPE_INT, "0" );
	REGISTER_CVAR( g_cvar.m_legit.shotgun_trigger_hitgroup, "legit_shotguns_trigger_hitgroup", config_manager::CVar::CVAR_TYPE_INT, "0" );
	REGISTER_CVAR( g_cvar.m_legit.sniper_trigger_hitgroup, "legit_snipers_trigger_hitgroup", config_manager::CVar::CVAR_TYPE_INT, "0" );

	REGISTER_CVAR( g_cvar.m_legit.pistol_trigger_ignoreair, "legit_pistols_trigger_ignoreair", config_manager::CVar::CVAR_TYPE_BOOL, "0" );
	REGISTER_CVAR( g_cvar.m_legit.smg_trigger_ignoreair, "legit_smgs_trigger_ignoreair", config_manager::CVar::CVAR_TYPE_BOOL, "0" );
	REGISTER_CVAR( g_cvar.m_legit.rifle_trigger_ignoreair, "legit_rifles_trigger_ignoreair", config_manager::CVar::CVAR_TYPE_BOOL, "0" );
	REGISTER_CVAR( g_cvar.m_legit.shotgun_trigger_ignoreair, "legit_shotguns_trigger_ignoreair", config_manager::CVar::CVAR_TYPE_BOOL, "0" );
	REGISTER_CVAR( g_cvar.m_legit.sniper_trigger_ignoreair, "legit_snipers_trigger_ignoreair", config_manager::CVar::CVAR_TYPE_BOOL, "0" );

	REGISTER_CVAR( g_cvar.m_legit.pistol_trigger_hitchance, "legit_pistols_trigger_hitchance", config_manager::CVar::CVAR_TYPE_INT, "125" );
	REGISTER_CVAR( g_cvar.m_legit.smg_trigger_hitchance, "legit_smg_trigger_hitchance", config_manager::CVar::CVAR_TYPE_INT, "125" );
	REGISTER_CVAR( g_cvar.m_legit.rifle_trigger_hitchance, "legit_rifles_trigger_hitchance", config_manager::CVar::CVAR_TYPE_INT, "125" );
	REGISTER_CVAR( g_cvar.m_legit.shotgun_trigger_hitchance, "legit_shotguns_trigger_hitchance", config_manager::CVar::CVAR_TYPE_INT, "125" );
	REGISTER_CVAR( g_cvar.m_legit.sniper_trigger_hitchance, "legit_snipers_trigger_hitchance", config_manager::CVar::CVAR_TYPE_INT, "125" );

	REGISTER_CVAR( g_cvar.m_legit.pistol_trigger_delay, "legit_pistols_trigger_delay", config_manager::CVar::CVAR_TYPE_INT, "50" );
	REGISTER_CVAR( g_cvar.m_legit.smg_trigger_delay, "legit_smg_trigger_delay", config_manager::CVar::CVAR_TYPE_INT, "50" );
	REGISTER_CVAR( g_cvar.m_legit.rifle_trigger_delay, "legit_rifles_trigger_delay", config_manager::CVar::CVAR_TYPE_INT, "50" );
	REGISTER_CVAR( g_cvar.m_legit.shotgun_trigger_delay, "legit_shotguns_trigger_delay", config_manager::CVar::CVAR_TYPE_INT, "50" );
	REGISTER_CVAR( g_cvar.m_legit.sniper_trigger_delay, "legit_snipers_trigger_delay", config_manager::CVar::CVAR_TYPE_INT, "50" );

	REGISTER_CVAR( g_cvar.m_legit.pistol_trigger_team, "legit_pistols_trigger_team", config_manager::CVar::CVAR_TYPE_BOOL, "0" );
	REGISTER_CVAR( g_cvar.m_legit.smg_trigger_team, "legit_smgs_trigger_team", config_manager::CVar::CVAR_TYPE_BOOL, "0" );
	REGISTER_CVAR( g_cvar.m_legit.rifle_trigger_team, "legit_rifles_trigger_team", config_manager::CVar::CVAR_TYPE_BOOL, "0" );
	REGISTER_CVAR( g_cvar.m_legit.shotgun_trigger_team, "legit_shotguns_trigger_team", config_manager::CVar::CVAR_TYPE_BOOL, "0" );
	REGISTER_CVAR( g_cvar.m_legit.sniper_trigger_team, "legit_snipers_trigger_team", config_manager::CVar::CVAR_TYPE_BOOL, "0" );

	REGISTER_CVAR( g_cvar.m_legit.pistol_trigger_ignoresmoke, "legit_pistols_trigger_ignoresmoke", config_manager::CVar::CVAR_TYPE_BOOL, "0" );
	REGISTER_CVAR( g_cvar.m_legit.smg_trigger_ignoresmoke, "legit_smgs_trigger_ignoresmoke", config_manager::CVar::CVAR_TYPE_BOOL, "0" );
	REGISTER_CVAR( g_cvar.m_legit.rifle_trigger_ignoresmoke, "legit_rifles_trigger_ignoresmoke", config_manager::CVar::CVAR_TYPE_BOOL, "0" );
	REGISTER_CVAR( g_cvar.m_legit.shotgun_trigger_ignoresmoke, "legit_shotguns_trigger_ignoresmoke", config_manager::CVar::CVAR_TYPE_BOOL, "0" );
	REGISTER_CVAR( g_cvar.m_legit.sniper_trigger_ignoresmoke, "legit_snipers_trigger_ignoresmoke", config_manager::CVar::CVAR_TYPE_BOOL, "0" );

	REGISTER_CVAR( g_cvar.m_legit.pistol_trigger_ignoreflash, "legit_pistols_trigger_ignoreflash", config_manager::CVar::CVAR_TYPE_BOOL, "0" );
	REGISTER_CVAR( g_cvar.m_legit.smg_trigger_ignoreflash, "legit_smgs_trigger_ignoreflash", config_manager::CVar::CVAR_TYPE_BOOL, "0" );
	REGISTER_CVAR( g_cvar.m_legit.rifle_trigger_ignoreflash, "legit_rifles_trigger_ignoreflash", config_manager::CVar::CVAR_TYPE_BOOL, "0" );
	REGISTER_CVAR( g_cvar.m_legit.shotgun_trigger_ignoreflash, "legit_shotguns_trigger_ignoreflash", config_manager::CVar::CVAR_TYPE_BOOL, "0" );
	REGISTER_CVAR( g_cvar.m_legit.sniper_trigger_ignoreflash, "legit_snipers_trigger_ignoreflash", config_manager::CVar::CVAR_TYPE_BOOL, "0" );

	// visuals
	REGISTER_CVAR( g_cvar.m_visuals.activation_type, "esp_activation_type", config_manager::CVar::CVAR_TYPE_INT, "0" );
	REGISTER_CVAR( g_cvar.m_visuals.activation_key, "esp_activation_key", config_manager::CVar::CVAR_TYPE_INT, "6" );
	REGISTER_CVAR( g_cvar.m_visuals.visible_only, "esp_visible_only", config_manager::CVar::CVAR_TYPE_BOOL, "0" );
	REGISTER_CVAR( g_cvar.m_visuals.disable_thru_smoke, "esp_disable_visuals_thru_smoke", config_manager::CVar::CVAR_TYPE_BOOL, "0" );
	REGISTER_CVAR( g_cvar.m_visuals.teammates, "esp_teammates", config_manager::CVar::CVAR_TYPE_BOOL, "0" );
	REGISTER_CVAR( g_cvar.m_visuals.bbox, "esp_bbox", config_manager::CVar::CVAR_TYPE_BOOL, "0" );
	REGISTER_CVAR( g_cvar.m_visuals.healthbar, "esp_healthbar", config_manager::CVar::CVAR_TYPE_BOOL, "0" );
	REGISTER_CVAR( g_cvar.m_visuals.name, "esp_name", config_manager::CVar::CVAR_TYPE_BOOL, "0" );
	REGISTER_CVAR( g_cvar.m_visuals.flags, "esp_flags", config_manager::CVar::CVAR_TYPE_BOOL, "0" );
	REGISTER_CVAR( g_cvar.m_visuals.weapon, "esp_weapon", config_manager::CVar::CVAR_TYPE_BOOL, "0" );
	REGISTER_CVAR( g_cvar.m_visuals.ammo, "esp_ammo", config_manager::CVar::CVAR_TYPE_INT, "0" );
	REGISTER_CVAR( g_cvar.m_visuals.lagrecord, "esp_lagrecord", config_manager::CVar::CVAR_TYPE_BOOL, "0" );

	REGISTER_CVAR( g_cvar.m_visuals.player_chams, "esp_player_chams", config_manager::CVar::CVAR_TYPE_BOOL, "0" );
	REGISTER_CVAR( g_cvar.m_visuals.player_chams_ignorez, "esp_player_chams_ignorez", config_manager::CVar::CVAR_TYPE_BOOL, "0" );
	REGISTER_CVAR( g_cvar.m_visuals.cham_type, "esp_cham_type", config_manager::CVar::CVAR_TYPE_INT, "0" );
	REGISTER_CVAR( g_cvar.m_visuals.cham_twopass_type, "esp_cham_twopass_type", config_manager::CVar::CVAR_TYPE_INT, "0" );
	REGISTER_CVAR( g_cvar.m_visuals.cham_outline, "esp_cham_outline", config_manager::CVar::CVAR_TYPE_BOOL, "0" );
	REGISTER_CVAR( g_cvar.m_visuals.cham_lagrecords, "esp_cham_lagrecords", config_manager::CVar::CVAR_TYPE_INT, "0" );

	REGISTER_CVAR( g_cvar.m_visuals.money, "esp_money", config_manager::CVar::CVAR_TYPE_BOOL, "0" );
	REGISTER_CVAR( g_cvar.m_visuals.defuser, "esp_defuser", config_manager::CVar::CVAR_TYPE_BOOL, "0" );
	REGISTER_CVAR( g_cvar.m_visuals.glow, "esp_glow", config_manager::CVar::CVAR_TYPE_BOOL, "0" );
	REGISTER_CVAR( g_cvar.m_visuals.glow_type, "esp_glow_type", config_manager::CVar::CVAR_TYPE_INT, "0" );
	REGISTER_CVAR( g_cvar.m_visuals.skeleton, "esp_skeleton", config_manager::CVar::CVAR_TYPE_BOOL, "0" );

	REGISTER_CVAR( g_cvar.m_visuals.dropped_weapons, "esp_dropped_weapons", config_manager::CVar::CVAR_TYPE_BOOL, "0" );
	REGISTER_CVAR( g_cvar.m_visuals.objectives, "esp_objectives", config_manager::CVar::CVAR_TYPE_BOOL, "0" );
	REGISTER_CVAR( g_cvar.m_visuals.bullet_tracer, "esp_bullet_tracer", config_manager::CVar::CVAR_TYPE_BOOL, "0" );
	REGISTER_CVAR( g_cvar.m_visuals.grenade_projectiles, "esp_grenade_projectiles", config_manager::CVar::CVAR_TYPE_BOOL, "0" );
	REGISTER_CVAR( g_cvar.m_visuals.grenade_trajectory, "esp_grenade_trajectory", config_manager::CVar::CVAR_TYPE_BOOL, "0" );
	REGISTER_CVAR( g_cvar.m_visuals.inaccuracy, "esp_inaccuracy", config_manager::CVar::CVAR_TYPE_BOOL, "0" );

	REGISTER_CVAR( g_cvar.m_visuals.chicken, "esp_chicken", config_manager::CVar::CVAR_TYPE_BOOL, "0" );
	REGISTER_CVAR( g_cvar.m_visuals.hitmarker, "esp_hitmarker", config_manager::CVar::CVAR_TYPE_BOOL, "0" );

	REGISTER_CVAR( g_cvar.m_visuals.cham_arms, "esp_cham_arms", config_manager::CVar::CVAR_TYPE_BOOL, "0" );
	REGISTER_CVAR( g_cvar.m_visuals.cham_weapon, "esp_cham_weapon", config_manager::CVar::CVAR_TYPE_BOOL, "0" );
	REGISTER_CVAR( g_cvar.m_visuals.champlayer_weapon, "esp_champlayer_weapon", config_manager::CVar::CVAR_TYPE_BOOL, "0" );

	REGISTER_CVAR( g_cvar.m_visuals.override_fov, "esp_override_fov", config_manager::CVar::CVAR_TYPE_INT, "90" );
	REGISTER_CVAR( g_cvar.m_visuals.weapon_fov, "esp_weapon_fov", config_manager::CVar::CVAR_TYPE_INT, "68" ); // this can actually override the weapon fov that the player has set.
	REGISTER_CVAR( g_cvar.m_visuals.fullbright, "esp_fullbright", config_manager::CVar::CVAR_TYPE_BOOL, "0" );
	REGISTER_CVAR( g_cvar.m_visuals.nightmode, "esp_nightmode", config_manager::CVar::CVAR_TYPE_BOOL, "0" );

	REGISTER_CVAR( g_cvar.m_visuals.remove_fog, "esp_remove_fog", config_manager::CVar::CVAR_TYPE_BOOL, "0" );
	REGISTER_CVAR( g_cvar.m_visuals.remove_scope, "esp_remove_scopeoverlay", config_manager::CVar::CVAR_TYPE_BOOL, "0" );
	REGISTER_CVAR( g_cvar.m_visuals.remove_scopedirt, "esp_remove_scopedirt", config_manager::CVar::CVAR_TYPE_BOOL, "0" );
	REGISTER_CVAR( g_cvar.m_visuals.remove_smoke, "esp_remove_smoke", config_manager::CVar::CVAR_TYPE_BOOL, "0" );
	REGISTER_CVAR( g_cvar.m_visuals.remove_post_processing, "esp_remove_post_processing", config_manager::CVar::CVAR_TYPE_BOOL, "0" );
	REGISTER_CVAR( g_cvar.m_visuals.remove_flash, "esp_remove_flash", config_manager::CVar::CVAR_TYPE_BOOL, "0" );

	// misc
	REGISTER_CVAR( g_cvar.m_misc.bunnyhop, "misc_bunnyhop", config_manager::CVar::CVAR_TYPE_BOOL, "0" );
	REGISTER_CVAR( g_cvar.m_misc.spectators, "misc_spectators", config_manager::CVar::CVAR_TYPE_BOOL, "0" );
	REGISTER_CVAR( g_cvar.m_misc.buy_log, "misc_buy_log", config_manager::CVar::CVAR_TYPE_BOOL, "0" );
	REGISTER_CVAR( g_cvar.m_misc.hurt_log, "misc_hurt_log", config_manager::CVar::CVAR_TYPE_BOOL, "0" );
	REGISTER_CVAR( g_cvar.m_misc.hitsound, "misc_hit_sound", config_manager::CVar::CVAR_TYPE_BOOL, "0" );
	REGISTER_CVAR( g_cvar.m_misc.clantag, "misc_clantag", config_manager::CVar::CVAR_TYPE_BOOL, "0" );
	REGISTER_CVAR( g_cvar.m_misc.reveal_ranks, "misc_reveal_ranks", config_manager::CVar::CVAR_TYPE_BOOL, "0" );
	REGISTER_CVAR( g_cvar.m_misc.radar, "misc_radar", config_manager::CVar::CVAR_TYPE_BOOL, "0" );
	REGISTER_CVAR( g_cvar.m_misc.autopistol, "misc_autopistol", config_manager::CVar::CVAR_TYPE_BOOL, "0" );

	REGISTER_CVAR( g_cvar.m_colors.box_color, "color_box", config_manager::CVar::CVAR_TYPE_STRING, "1.0,1.0,1.0" );
	REGISTER_CVAR( g_cvar.m_colors.cham_color, "color_cham", config_manager::CVar::CVAR_TYPE_STRING, "0.58,0.8,0.1" );
	REGISTER_CVAR( g_cvar.m_colors.ignorez_color, "color_twopass", config_manager::CVar::CVAR_TYPE_STRING, "0.18,0.47,0.92" );
	REGISTER_CVAR( g_cvar.m_colors.lag_record_color, "color_lagrecord", config_manager::CVar::CVAR_TYPE_STRING, "1.0,1.0,1.0" );
	REGISTER_CVAR( g_cvar.m_colors.trajectory_color, "color_grenade_trajectory", config_manager::CVar::CVAR_TYPE_STRING, "1.0,0.0,0.0" );
	REGISTER_CVAR( g_cvar.m_colors.tracer_color, "color_tracer", config_manager::CVar::CVAR_TYPE_STRING, "1.0,0.0,0.0" );
	REGISTER_CVAR( g_cvar.m_colors.glow_color, "color_glow", config_manager::CVar::CVAR_TYPE_STRING, "0.58,0.8,0.1" );
	REGISTER_CVAR( g_cvar.m_colors.skeleton_color, "color_skeleton", config_manager::CVar::CVAR_TYPE_STRING, "1.0,1.0,1.0" );
	REGISTER_CVAR( g_cvar.m_colors.arms_color, "color_arms", config_manager::CVar::CVAR_TYPE_STRING, "0.18,0.47,0.92" );
	REGISTER_CVAR( g_cvar.m_colors.weapon_cham_color, "color_cham_weapon", config_manager::CVar::CVAR_TYPE_STRING, "1.0,1.0,1.0" );
	REGISTER_CVAR( g_cvar.m_colors.inaccuracy_color, "color_inaccuracy", config_manager::CVar::CVAR_TYPE_STRING, "0.0,0.0,0.0" );
	REGISTER_CVAR( g_cvar.m_colors.menu_accent_color, "color_menu_accent", config_manager::CVar::CVAR_TYPE_STRING, "0.8,0.45,0.53" );

	load( "settings" );

}

std::vector< std::string > Config::get_config_files() {
	std::vector<std::string> names = {};

	for( auto &file_path : std::experimental::filesystem::directory_iterator( m_directory ) ) {
		if( !file_path.path().string().empty() ) {
			if( file_path.path().string().find( m_extension ) != std::string::npos )
				names.emplace_back( file_path.path().string().erase( 0, m_directory.length() + 1 ) );
		}
	}

	return names;
}

bool Config::load( std::string file_name ) {
	if( file_name.empty() )
		return false;

	if( file_name.find( m_extension ) == std::string::npos )
		return cfg_manager.Execute( file_name + m_extension );

	return cfg_manager.Execute( file_name );
}

bool Config::save( std::string file_name, bool should_reset ) {
	if( file_name.empty() )
		return false;

	if( file_name.find( m_extension ) == std::string::npos )
		return cfg_manager.Save( file_name + m_extension, should_reset );

	return cfg_manager.Save( file_name, should_reset );
}

bool Config::remove( const std::string &file_name ) {
	if( file_name.empty() )
		return false;

	std::string temp = m_directory + "/" + file_name;

	return std::remove( temp.c_str() ) == 0;
}

void tokenize(const std::string& str, std::vector< std::string>& tokens, const std::string& delimiters = ",") {
	// Skip delimiters at beginning.
	std::string::size_type lastPos = str.find_first_not_of(delimiters, 0);

	// Find first non-delimiter.
	std::string::size_type pos = str.find_first_of(delimiters, lastPos);

	while ( std::string::npos != pos || std::string::npos != lastPos) {
		// Found a token, add it to the vector.
		tokens.push_back(str.substr(lastPos, pos - lastPos));

		// Skip delimiters.
		lastPos = str.find_first_not_of(delimiters, pos);

		// Find next non-delimiter.
		pos = str.find_first_of(delimiters, lastPos);
	}
}

OSHGui::Drawing::Color Config::string_to_color( float alpha, std::string str ) {
	std::vector< std::string > vec;

	tokenize( str, vec );

	//return OSHGui::Drawing::Color::White();
	return OSHGui::Drawing::Color( alpha, std::atof( vec.at( 0 ).c_str() ), std::atof( vec.at( 1 ).c_str() ), std::atof( vec.at( 2 ).c_str() ) );
}

std::string Config::color_to_string( OSHGui::Drawing::Color color ) {
	std::stringstream ss;
	ss << color.GetRed() << ',' << color.GetGreen() << ',' << color.GetBlue();

	return ss.str();
}
