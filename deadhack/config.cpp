#include "includes.h"

#include <experimental/filesystem>

// todo - finish this...

#define REGISTER_CVAR( r, n, t, v ) r = cfg_manager.CVar::Add( n, t, v );

void Config::init() {
	VM_PUMA_WHITE_START

	if( !cfg_manager.is_ready() )
		return;

	cfg_manager.set_script_directory( m_directory );

	REGISTER_CVAR( g_cvar.m_visuals.activation_type, "esp_activation_type", config_manager::CVar::CVAR_TYPE_INT, "0" );
	REGISTER_CVAR( g_cvar.m_visuals.activation_key, "esp_activation_key", config_manager::CVar::CVAR_TYPE_INT, "6" );
	REGISTER_CVAR( g_cvar.m_visuals.teammates, "teammates", config_manager::CVar::CVAR_TYPE_BOOL, "0" );
	REGISTER_CVAR( g_cvar.m_visuals.bbox, "bbox", config_manager::CVar::CVAR_TYPE_BOOL, "0" );
	REGISTER_CVAR( g_cvar.m_visuals.healthbar, "healthbar", config_manager::CVar::CVAR_TYPE_BOOL, "0" );
	REGISTER_CVAR( g_cvar.m_visuals.name, "name", config_manager::CVar::CVAR_TYPE_BOOL, "0" );
	REGISTER_CVAR( g_cvar.m_visuals.flags, "flags", config_manager::CVar::CVAR_TYPE_BOOL, "0" );
	REGISTER_CVAR( g_cvar.m_visuals.weapon, "weapon", config_manager::CVar::CVAR_TYPE_BOOL, "0" );
	REGISTER_CVAR( g_cvar.m_visuals.ammo, "ammo", config_manager::CVar::CVAR_TYPE_INT, "0" );
	REGISTER_CVAR( g_cvar.m_visuals.money, "money", config_manager::CVar::CVAR_TYPE_BOOL, "0" );

	REGISTER_CVAR( g_cvar.m_visuals.player_chams, "player_chams", config_manager::CVar::CVAR_TYPE_BOOL, "0" );
	REGISTER_CVAR( g_cvar.m_visuals.player_chams_ignorez, "player_chams_ignorez", config_manager::CVar::CVAR_TYPE_BOOL, "0" );
	REGISTER_CVAR( g_cvar.m_visuals.cham_type, "cham_type", config_manager::CVar::CVAR_TYPE_INT, "0" );
	REGISTER_CVAR( g_cvar.m_visuals.cham_outline, "cham_outline", config_manager::CVar::CVAR_TYPE_BOOL, "0" );

	REGISTER_CVAR( g_cvar.m_visuals.dropped_weapons, "dropped_weapons", config_manager::CVar::CVAR_TYPE_BOOL, "0" );
	REGISTER_CVAR( g_cvar.m_visuals.objectives, "objectives", config_manager::CVar::CVAR_TYPE_BOOL, "0" );

	REGISTER_CVAR( g_cvar.m_visuals.override_fov, "override_fov", config_manager::CVar::CVAR_TYPE_INT, "90" );
	REGISTER_CVAR( g_cvar.m_visuals.weapon_fov, "weapon_fov", config_manager::CVar::CVAR_TYPE_INT, "68" ); // this can actually override the weapon fov that the player has set.
	REGISTER_CVAR( g_cvar.m_visuals.fullbright, "fullbright", config_manager::CVar::CVAR_TYPE_BOOL, "0" );
	REGISTER_CVAR( g_cvar.m_visuals.nightmode, "nightmode", config_manager::CVar::CVAR_TYPE_BOOL, "0" );

	REGISTER_CVAR( g_cvar.m_visuals.remove_fog, "remove_fog", config_manager::CVar::CVAR_TYPE_BOOL, "0" );
	REGISTER_CVAR( g_cvar.m_visuals.remove_scope, "remove_scopeoverlay", config_manager::CVar::CVAR_TYPE_BOOL, "0" );
	REGISTER_CVAR( g_cvar.m_visuals.remove_scopedirt, "remove_scopedirt", config_manager::CVar::CVAR_TYPE_BOOL, "0" );

	load( "settings" );

	VM_PUMA_WHITE_END
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