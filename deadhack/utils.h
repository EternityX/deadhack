#pragma once

namespace Utils {
    // checks if address is not null and has correct page protection.
	static __forceinline bool valid( uintptr_t addr ) {
		MEMORY_BASIC_INFORMATION mbi;

		// check for invalid address.
		if( !addr )
			return false;

		// check for invalid page protection.
		if( !VirtualQuery( (const void *)addr, &mbi, sizeof( mbi ) ) )
			return false;

        // todo - dex; fix this, its wrong... check for rwe or something too...
		if( /*!( mbi.State & MEM_COMMIT ) ||*/ ( mbi.Protect & PAGE_NOACCESS ) || ( mbi.Protect & PAGE_GUARD ) )
			return false;

		return true;
	}

    // get method from VMT.
    template < typename t = uintptr_t > __forceinline t get_method( uintptr_t this_ptr, uint16_t index ) {
		return ( *(t **)this_ptr )[ index ];
	}

    // get base ptr ( EBP ).
	__forceinline uintptr_t get_baseptr() {
		return (uintptr_t)_AddressOfReturnAddress() - sizeof( uintptr_t );
	}

    // wide -> multi-byte
	__forceinline std::string wide_to_multibyte( const std::wstring &str ) {
		std::string out;
		int         str_len;

		if( str.empty() )
			return {};

		// get needed size.
		str_len = WideCharToMultiByte( CP_UTF8, 0, str.data(), (int)str.size(), 0, 0, 0, nullptr );

		// allocate room for string.
		out.resize( str_len );

		// finally, convert the string.
		WideCharToMultiByte( CP_UTF8, 0, str.data(), (int)str.size(), &out[ 0 ], str_len, 0, nullptr );

		return out;
	}

    // multi-byte -> wide
	__forceinline std::wstring multibyte_to_wide( const std::string &str ) {
		std::wstring    out;
		int		        str_len;

		if( str.empty() )
			return {};

		// get needed size.
		str_len = MultiByteToWideChar( CP_UTF8, 0, str.data(), (int)str.size(), 0, 0 );

		// allocate room for string.
		out.resize( str_len );

		// finally, convert the string.
		MultiByteToWideChar( CP_UTF8, 0, str.data(), (int)str.size(), &out[ 0 ], str_len );

		return out;
	}

    // returns a random floating point number in range.
	template < typename T > __forceinline T get_random_float_range( const T &min, T max ) {
        static_assert( std::is_floating_point< T >::value, "invalid type for: get_random_float_range." );

		static std::random_device                  device;
		static std::minstd_rand                    engine( device() );

		std::uniform_real_distribution< T > distribution( min, max );

		return distribution( engine );
	}
}