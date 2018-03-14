#pragma once

class Config {
private:
	config_manager::BaseScripting    cfg_manager;
	std::string                      m_directory = "profiles";
	std::string                      m_extension = ".cfg";

public:
	void init();
	std::vector< std::string > get_config_files();
	bool load( std::string file_name );
	bool save( std::string file_name, bool should_reset );
	bool remove( const std::string &file_name );
	static OSHGui::Drawing::Color string_to_color( float alpha, std::string str );
	static std::string color_to_string( OSHGui::Drawing::Color color );
};

extern Config g_config;