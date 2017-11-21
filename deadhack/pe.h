#pragma once

namespace PE {
    // container type for "get_all_modules" function.
    using modules_t = std::vector< Module >;

    // returns a vector containing all modules in current process.
    static bool get_all_modules( modules_t &out ) {
        Types::PEB                  *peb;
        Types::LIST_ENTRY           *list;
        Types::LDR_DATA_TABLE_ENTRY *ldr_entry;
        Module                      mod;

        peb = Utils::get_PEB();
        if( !peb )
            return false;

        // valid list?
        if( !peb->Ldr->InMemoryOrderModuleList.Flink )
            return false;

        list = &peb->Ldr->InMemoryOrderModuleList;

        // iterate doubly linked list.
        for( auto i = list->Flink; i != list; i = i->Flink ) {
            // get current entry.
            ldr_entry = CONTAINING_RECORD( i, Types::LDR_DATA_TABLE_ENTRY, InMemoryOrderLinks );
            if( !ldr_entry )
                continue;

            // attempt to initialize current module.
            if( !mod.init( ldr_entry ) )
                continue;

            // MessageBoxW( nullptr, mod.get_pathW().c_str(), L"get_all_modules", 0 );

            out.push_back( mod );
        }
    
        return !out.empty();
    }

    // get module by name hash.
    static Module get_module( hash32_t hash ) {
        // PE::Types::PEB  *peb;
        modules_t       modules;

        //if( !hash ) {
        //    peb = Utils::get_PEB();
        //    if( !peb )
        //        return {};
        //
        //    // todo - dex;  add functionality to get process module.... gross...
        //    //              honestly don't even want this, doubt it'll be used for a while.
        //    //              also take a look at ProcessParameters->CurrentDirectoryPath 
        //    /*
        //        read: peb->ProcessParameters->DllPath
        //
        //        if !Length
        //            read: peb->ProcessParameters->ImagePathName
        //    */
        //
        //    return {};
        //}

        if( !get_all_modules( modules ) )
            return {};
        
        for( const auto &m : modules ) {
            if( Hash::fnv1a_32( m.get_module_nameA() ) == hash )
                return m;
        }
    
        return {};
    }

    // get module by name.
    static Module get_module( std::string name ) {
        if( name.empty() )
            return get_module( 0 );

        std::transform( name.begin(), name.end(), name.begin(), std::tolower );

        return get_module( Hash::fnv1a_32( name ) );
    }

    // todo - dex;  this wont work, uintptr_t and hash32_t have the same type
    //              need to make one into its one class...
    //static Module get_module( uintptr_t base ) {
    //    modules_t modules;
    //
    //    if( !base )
    //        return {};
    //
    //    if( !get_all_modules( modules ) )
    //        return {};
    //    
    //    for( const auto &m : modules ) {
    //        if( m.get_base() == base )
    //            return m;
    //    }
    //
    //    return {};
    //}

    // get export by hash.
    template< typename t = uintptr_t > static t get_export( const Module &mod, hash32_t hash ) {
        uintptr_t   export_ptr;
        std::string export_name, fwd_str, fwd_module_name, fwd_export_name;
        size_t      delim;

        if( !mod )
            return t{};

        // get export data directory entry.
        auto export_dir_entry = mod.get_data_dir_entry( IMAGE_DIRECTORY_ENTRY_EXPORT );
        if( !export_dir_entry || !export_dir_entry->VirtualAddress )
            return t{};

        // get export data directory.
        auto export_dir = mod.RVA< IMAGE_EXPORT_DIRECTORY * >( export_dir_entry->VirtualAddress );
        if( !export_dir )
            return t{};

        // get needed arrays.
        auto names  = mod.RVA< uint32_t * >( export_dir->AddressOfNames );
        auto funcs  = mod.RVA< uint32_t * >( export_dir->AddressOfFunctions );
        auto ords   = mod.RVA< uint16_t * >( export_dir->AddressOfNameOrdinals );
        if( !names || !funcs || !ords )
            return t{};

        for( size_t i = 0; i < export_dir->NumberOfNames; ++i ) {
            export_name = mod.RVA< const char * >( names[ i ] );
            if( export_name.empty( ) )
                continue;

            // compare hash.
            if( Hash::fnv1a_32( export_name ) == hash ) {
                // get export pointer.
                export_ptr = mod.RVA( funcs[ ords[ i ] ] );
                if( !export_ptr )
                    continue;

                // inside dir, it's an export and we must resolve it.
                if( export_ptr >= (uintptr_t)export_dir && export_ptr < ( (uintptr_t)export_dir + export_dir_entry->Size ) ) {
                    // get forwarder string.
                    fwd_str = (const char *)export_ptr;

                    delim = fwd_str.find_last_of( '.' );
                    if( delim == std::string::npos )
                        return t{};

                    // get forwarder module name.
                    fwd_module_name = fwd_str.substr( 0, delim + 1 );
                    fwd_module_name += 'd';
                    fwd_module_name += 'l';
                    fwd_module_name += 'l';

                    // get forwarder export name.
                    fwd_export_name = fwd_str.substr( delim );

                    // get real export ptr ( recursively ).
                    export_ptr = get_export( get_module( fwd_module_name ), fwd_export_name );
                    if( !export_ptr )
                        return {};

                    return export_ptr;
                }

                return (t)export_ptr;
            }
        }

        return t{};
    }

    // get export by name.
    template< typename t = uintptr_t > static t get_export( const Module &mod, const std::string &name ) {
        return get_export< t >( mod, Hash::fnv1a_32( name ) );
    }
}