#pragma once

class Interfaces {
private:
    // used internally by the game to register classes.
    class InterfaceReg {
    private:
        using create_t = void *(__cdecl *)();

    public:
        create_t        m_create_fn;
        const char      *m_name;
        InterfaceReg    *m_next;
    };

    struct interface_t {
        std::string m_name;
        uintptr_t   m_ptr;
    };

    // holds every interface used by the game.
    std::vector< interface_t > m_interfaces;

protected:
    Interfaces() : m_interfaces{} {
        PE::modules_t   modules;
        uintptr_t       createinterface;
        InterfaceReg    *reg;

        if( !PE::get_all_modules( modules ) )
            return;

        for( const auto &m : modules ) {
            createinterface = PE::get_export( m, CT_HASH32( "CreateInterface" ) );
            if( !Utils::valid( createinterface ) )
                continue;

            // ensure 4th byte is actually a jmp instruction.
            if( *(uint8_t *)( createinterface + 4 ) != 0xE9 )
                continue;

            // 5th byte is the jmp's rel32.
            // we need to follow it to CreateInterfaces real function.
            createinterface = Utils::follow_rel32( createinterface + 5 );
            if( !createinterface )
                continue;

            // now we need to get s_pInterfaceRegs.
            // in csgo, its generally the first "mov, esi imm32" instruction.
            // we're just going to use the hardcoded offset to it here.
            reg = **(InterfaceReg ***)( createinterface + 6 );
            if( !reg )
                continue;

            // iterate s_pInterfaceRegs linked list and store off needed data.
            for( reg; reg != nullptr; reg = reg->m_next )
                m_interfaces.push_back( { reg->m_name, (uintptr_t)reg->m_create_fn() } );
        }
    }

    // get interface by hash.
    template< typename t > t get_interface( hash32_t name, size_t skip = 0, bool truncate = true ) {
        std::string interface_name;

        if( m_interfaces.empty() )
            return t{};

        for( const auto &i : m_interfaces ) {
            interface_name = i.m_name;

            if( truncate )
                interface_name.resize( interface_name.size() - 3 );

            if( Hash::fnv1a_32( interface_name ) == name ) {
                // some interfaces have multiple versions.
                // so we will skip this interface if a newer one is desired.
                if( skip > 0 ) {
                    --skip;
                    continue;
                }

                return (t)i.m_ptr;
            }
        }

        return t{};
    }

};