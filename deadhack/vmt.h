#pragma once

class VMTHook {
private:
    uintptr_t                       m_vmt_base;
    uintptr_t                       *m_old_vmt;
    uint16_t                        m_total_methods;
    std::unique_ptr< uintptr_t[] >  m_new_vmt;
    uintptr_t                       *m_new_vmt_start;

    __forceinline uint16_t count_methods() {
        uint16_t i = 0;

        for( i; Utils::valid( m_old_vmt[ i ] ) != false; ++i );
    
        return i;
    }

public:
    __forceinline VMTHook( void *ptr, bool copy_rtti = true ) : m_vmt_base{}, m_old_vmt{}, m_total_methods{}, m_new_vmt{}, m_new_vmt_start{} {
        init( ptr, copy_rtti );
    }

    __forceinline ~VMTHook() {
        
    }

    __forceinline bool init( void *base, bool copy_rtti = true ) {
        // invalid base.
        if( !base )
            return false;

        // get ptr to old VMT.
		m_old_vmt = *(uintptr_t **)base;
		if( !m_old_vmt )
			return false;

        // save VMT base.
        m_vmt_base = (uintptr_t)base;

        // count number of methods in old VMT.
		m_total_methods = count_methods();
		if( !m_total_methods )
			return false;

        // allocate new VMT.
		m_new_vmt = std::make_unique< uintptr_t[] >( ( copy_rtti ) ? m_total_methods + 1 : m_total_methods );
		if( !m_new_vmt )
			return false;

        if( copy_rtti ) {
            // copy VMT, starting from RTTI.
			std::memcpy(
				(void *)m_new_vmt.get(),
				m_old_vmt - 1,
				( m_total_methods + 1 ) * sizeof( uintptr_t )
			);

            // get start for new VMT.
            // VMT start is actually 1 function ahead due to RTTI copy.
            m_new_vmt_start = (uintptr_t *)( m_new_vmt.get() + 1 );

            // set base to our new VMT.
            *(uintptr_t *)base = m_new_vmt_start[ 0 ];
        }

        else {
            // copy VMT.
			std::memcpy(
				(void *)m_new_vmt.get(),
				m_old_vmt,
				m_total_methods * sizeof( uintptr_t )
			);

            // get start for new VMT.
            m_new_vmt_start = m_new_vmt.get();

            // set base to our new VMT.
            *(uintptr_t *)base = m_new_vmt_start[ 0 ];
        }

        return true;
    }

    __forceinline bool hook_method( uint16_t index, void *func ) {
        // invalid args / member vars.
        if( !m_old_vmt || !m_new_vmt_start || index > m_total_methods || !func )
            return false;
        
        // redirect function.
        m_new_vmt_start[ index ] = m_old_vmt[ index ];

        return true;
    }

    __forceinline bool unhook_method( uint16_t index ) {
        // invalid args / member vars.
        if( !m_old_vmt || !m_new_vmt_start || index > m_total_methods )
            return false;
        
        // redirect function.
        m_old_vmt[ index ] = m_new_vmt_start[ index ];

        return true;
    }

    __forceinline bool unhook_all() {
        // note - dex; untested...
        *(uintptr_t *)m_vmt_base = m_old_vmt[ 0 ];
    }
};