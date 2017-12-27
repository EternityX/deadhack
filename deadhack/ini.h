#pragma once

// todo; eternity - finish this

namespace ini {
	class Key
	{
	protected:
		friend class     Section;

		std::string      m_item;
		std::string      m_value;
	public:

		Key( std::string &name, float &value ) : m_item{ name }, m_value( std::to_string( value ) )	{
		}

		Key( std::string &name, std::string &value ) : m_item{ name }, m_value{ value } {
		}
	};

	class Section {
	private:
		std::vector< Key > m_keys;

	public:
		Section( const std::string &name ) { }

		void add_key( const Key &key ) {
			m_keys.push_back( key );
		}

		Key get_key( std::string &item ) const {
			for each ( auto key in m_keys ) {
				if( key.m_item == item )
					return key;
			}
		}
	};

	class File {
	private:
		std::string                               m_path;
		std::vector< std::unique_ptr< Section > > m_sections;

	public:
		File( std::string &path ) : m_path{ path } {
			std::ifstream stream( path );

			if( !stream.is_open() )
				return;

			std::string line;
			std::string current_section{ };

			// iterate through file.
			while( std::getline( stream, line ) ) {
				// remove any white spaces / tabs.
				auto trim = []( std::string &line ) {
					while( line.back() == ' ' || line.back() == '\t' ) line.pop_back();
					while( line.back() == ' ' || line.back() == '\t' )  line = line.substr( 1 );
				};

				trim( line );

				// ignore lines opening with a semicolon.
				if( line.front() == ';' )
					continue;

				// found a new section.
				if( line.front() == '[' && line.back() == ']' ) {
					// grab name.
					current_section = line.substr( line.find( '[' ) + 1, line.find( ']' ) - 1 );

					m_sections.push_back( std::make_unique< Section >( current_section ) );
				}
				else {
					std::size_t equals_pos = line.find_first_of( '=' );

					std::string item = line.substr( 0, equals_pos );
					std::string value = line.substr( equals_pos + 1, line.size() );

					m_sections.back()->add_key( Key( item, value ) );
				}
			}
		}

		void save_to_file( std::string path ) {
			std::ofstream file( m_path.data(), std::ios::out | std::ios::trunc );

			for( auto &section : m_sections ) {
				
			}

			file.close();
		}

		void save() {
			save_to_file( m_path );
		}
	};
}