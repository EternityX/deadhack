#pragma once

namespace PE {
    using modules_t = std::vector< Module >;

    static bool get_all_modules( modules_t &out ) {
        //LIST_ENTRY *list;
        //Module      mod;

        // todo - dex; get peb, etc..

        //for( auto i = list->Flink; i != list; i = i->Flink ) {
        //    //// get current entry.
        //    //ldr_entry = CONTAINING_RECORD( it, LDR_DATA_TABLE_ENTRY, InMemoryOrderLinks );
        //    //if( !ldr_entry )
        //    //    continue;
        //
        //    //// attempt to init module.
        //    //if( !mod.init() )
        //    //    continue;
        //
        //    // add to out.
        //    out.push_back( mod );
        //}
    
        return !out.empty();
    }

    static Module get_module( hash32_t hash ) {
        modules_t modules;

        if( !get_all_modules( modules ) )
            return {};
        
        for( const auto &m : modules ) {
            // todo - dex; compare name hash, etc...
        }
    
        return {};
    }

    static Module get_module( const std::string &str ) {
        return get_module( Hash::fnv1a_32( str ) );
    }

    template< typename t = uintptr_t > static t get_export( const Module &mod, hash32_t hash ) {
    
        return 0;
    }

    template< typename t = uintptr_t > static t get_export( const Module &mod, const std::string &name ) {
        return get_export< t >( mod, Hash::fnv1a_32( name ) );
    }
}