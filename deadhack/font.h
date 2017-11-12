#pragma once

namespace Font {
	// todo - maybe use the registry instead?
	// font_name should be the full path to desired font e.g C:\\WINDOWS\\Fonts\\font.ttf
	inline bool does_exist( const std::string& font_name ) {
		wchar_t* font_path = nullptr;

		if ( FAILED( SHGetKnownFolderPath( FOLDERID_Fonts, 0, nullptr, &font_path ) ) )
			return false;

		for ( auto &it : std::experimental::filesystem::directory_iterator( font_path ) ) {
			if ( font_name == it ) {
				// note - eternity; not sure if this is ok
				#if defined( CHEAT_DBG )  
					std::wcout << "found " << it << "\n";
				#endif  

				return true;
			}
		}

		return false;
	}
}
