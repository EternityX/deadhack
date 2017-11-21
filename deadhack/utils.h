#pragma once

namespace Utils {
    // various global vars.
    static std::random_device g_rand_device{};
    static std::minstd_rand   g_rand_engine( g_rand_device() );

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

    // get Thread Environment Block.
    __forceinline PE::Types::TEB *get_TEB() {
        return (PE::Types::TEB *)__readfsdword( 0x18 );
    }

    // get Thread Environment Block.
    __forceinline PE::Types::PEB *get_PEB() {
        PE::Types::TEB *teb{ get_TEB() };
        if( !teb )
            return nullptr;

        return teb->ProcessEnvironmentBlock;
    }

    // follow relative32 offset.
    // input argument is the address of the relative offset.
    template< typename t = uintptr_t > __forceinline t follow_rel32( uintptr_t address ) {
        uint32_t disp;

        if( !address )
            return 0;

        // get rel32 offset.
		disp = *(uint32_t *)address;
		if( !disp )
			return 0;

        // displacement is relative to address of the next instruction.
        return ( address + sizeof( uint32_t ) ) + disp;
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
	template< typename t > __forceinline t get_random_float_range( const t &min, const t &max ) {
        static_assert( std::is_floating_point< t >::value, "invalid type for: get_random_float_range." );

        std::uniform_real_distribution< t > distribution( min, max );
        
        return distribution( engine );
	}

    // returns a random number in range.
    template< typename t > __forceinline t get_random_int_range( const t &min, const t &max ) {

    }
}