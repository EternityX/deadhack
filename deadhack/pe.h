#pragma once

namespace PE {
    static Module get_module( hash32_t hash ) {
        
    
        return {};
    }

    static Module get_module( const std::string &str ) {
        return get_module( Hash::fnv1a_32( str ) );
    }
}