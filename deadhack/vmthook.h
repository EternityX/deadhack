#pragma once

class VMTHook {
private:
    uintptr_t                       m_vmt_base;         // VMT base ( on heap / in rdata ).
    uintptr_t                       *m_old_vmt;         // actual VMT.
    uint16_t                        m_total_methods;    // total number of methods in VMT.
    std::unique_ptr< uintptr_t[] >  m_new_vmt;          // our newly allocated VMT.
    uintptr_t                       *m_new_vmt_start;   // the start ptr to our new VMT ( incase RTTI was copied ).

    __forceinline uint16_t count_methods() {
        uint16_t i = 0;

        while( Utils::valid( m_old_vmt[ i ] ) != false )
            ++i;
    
        return i;
    }

public:
    __forceinline VMTHook() : m_vmt_base{ 0 }, m_old_vmt{ nullptr }, m_total_methods{ 0 }, m_new_vmt{ 0 }, m_new_vmt_start{ nullptr } {

    }

    __forceinline VMTHook( void *base, bool copy_rtti = true ) : m_vmt_base{ 0 }, m_old_vmt{ nullptr }, m_total_methods{ 0 }, m_new_vmt{ 0 }, m_new_vmt_start{ nullptr } {
        init( base, copy_rtti );
    }

    __forceinline VMTHook( uintptr_t base, bool copy_rtti = true ) : m_vmt_base{ 0 }, m_old_vmt{ nullptr }, m_total_methods{ 0 }, m_new_vmt{ 0 }, m_new_vmt_start{ nullptr } {
        init( base, copy_rtti );
    }

    __forceinline ~VMTHook() {
        
    }

    __forceinline bool init( void *base, bool copy_rtti = true ) {
        return init( (uintptr_t)base, copy_rtti );
    }

    __forceinline bool init( uintptr_t base, bool copy_rtti = true ) {
        uintptr_t new_vmt_ptr;

        if( !base )
            return false;

        m_vmt_base = base;

        // get ptr to old VMT.
		m_old_vmt = *(uintptr_t **)base;
		if( !m_old_vmt )
			return false;

		m_total_methods = count_methods();
		if( !m_total_methods )
			return false;

        // allocate new VMT, making room for RTTI ptr if needed.
        m_new_vmt = std::make_unique< uintptr_t[] >( ( copy_rtti ) ? m_total_methods + 1 : m_total_methods );
        if( !m_new_vmt )
        	return false;

        // get address of our newly allocated memory.
        new_vmt_ptr = (uintptr_t)m_new_vmt.get();
        
        if( copy_rtti ) {
            // copy VMT, starting from RTTI.
        	std::memcpy(
        		(void *)new_vmt_ptr,
        		(const void *)( m_old_vmt - 1 ),
        		( m_total_methods + 1 ) * sizeof( uintptr_t )
        	);
        
            // get start for new VMT.
            // VMT start is actually 1 function ahead due to RTTI copy.
            m_new_vmt_start = (uintptr_t *)( new_vmt_ptr + sizeof( uintptr_t ) );
        
            // set base to our new VMT.
            *(uintptr_t *)base = (uintptr_t)m_new_vmt_start;
        }
        
        else {
            // copy VMT.
        	std::memcpy(
        		(void *)new_vmt_ptr,
        		(const void *)m_old_vmt,
        		m_total_methods * sizeof( uintptr_t )
        	);

            // get start for new VMT.
            m_new_vmt_start = (uintptr_t *)new_vmt_ptr;

            // set base to our new VMT.
            *(uintptr_t *)base = (uintptr_t)m_new_vmt_start;
        }

        return true;
    }

    __forceinline bool hook_method( uint16_t index, void *func ) {
        if( !m_old_vmt || !m_new_vmt_start || index > m_total_methods || !func )
            return false;

        m_new_vmt_start[ index ] = (uintptr_t)func;

        return true;
    }

    __forceinline bool unhook_method( uint16_t index ) {
        if( !m_old_vmt || !m_new_vmt_start || index > m_total_methods )
            return false;

        m_old_vmt[ index ] = m_new_vmt_start[ index ];

        return true;
    }

    template< typename t = uintptr_t > __forceinline t get_old_method( uint16_t index ) {
        return (t)m_old_vmt[ index ];
    }

    __forceinline bool unhook_all() {
        if( !m_old_vmt || !m_vmt_base )
            return false;

        *(uintptr_t *)m_vmt_base = (uintptr_t)m_old_vmt;

        return true;
    }
};