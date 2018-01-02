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
};

extern Config g_config;