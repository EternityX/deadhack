#pragma once

#include <ShlObj.h> // needed for SHGetKnownFolderPath()
#include <filesystem>

namespace Font {
	// todo - maybe use the registry instead?
	// font_name should be the full path to desired font e.g C:\\WINDOWS\\Fonts\\font.ttf
	inline bool does_exist( const std::string& font_name ) {
		wchar_t* font_path = nullptr;

		if ( FAILED( SHGetKnownFolderPath( FOLDERID_Fonts, 0, nullptr, &font_path ) ) )
			return false;

		for ( auto &p : std::experimental::filesystem::directory_iterator( font_path ) ) {
			if ( font_name == p ) {
				// note - eternity; not sure if this is ok
				#if defined( CHEAT_DBG )  
					std::wcout << "found " << p << "\n";
				#endif  

				return true;
			}
		}

		return false;
	}
}
