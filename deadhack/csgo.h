#pragma once

class CSGO : protected Interfaces {
private:
    // todo - dex; func prototypes go here.

public:
    // modules.
    PE::Module m_client_dll;
    PE::Module m_engine_dll;

    // misc ptrs;
    uintptr_t m_d3d9_vmt;

    // interfaces.
    CHLClient            *m_client;
	IEngineClient        *m_engine;
	IClientModeShared    *m_client_mode;
	IClientEntityList    *m_entity_list;
	CGlobalVars          *m_global_vars;
	ICVar                *m_convar;

    // functions.

    CSGO() : m_client_dll{}, m_engine_dll{}, m_d3d9_vmt{} {
    
    }

    bool init() {
        // modules.
        m_client_dll = PE::get_module( CT_HASH32( "client.dll" ) );
        m_engine_dll = PE::get_module( CT_HASH32( "engine.dll" ) );
        if( !m_client_dll || !m_engine_dll )
            return false;

        // misc ptrs.
        m_d3d9_vmt = SigScan::find( CT_HASH32( "shaderapidx9.dll" ), "A1 ? ? ? ? 6A 00 53" );
        if( !m_d3d9_vmt )
            return false;

        m_d3d9_vmt = **(uintptr_t **)( m_d3d9_vmt + 1 );

        // interfaces.
        m_client = get_interface< CHLClient >( CT_HASH32( "VClient" ) );
        if( !m_client )
            return false;

		m_engine = get_interface< IEngineClient >( CT_HASH32( "VEngineClient" ) );
		if( !m_engine )
			return false;

		m_client_mode = **(IClientModeShared ***)( ( *(uintptr_t **)m_client )[ 10 ] + 5 );
		if( !m_client_mode )
			return false;

		m_entity_list = get_interface< IClientEntityList >( CT_HASH32( "VClientEntityList" ) );
		if( !m_entity_list )
			return false;

		m_global_vars = **(CGlobalVars ***)( SigScan::find( m_client_dll, "A1 ? ? ? ? 5E 8B 40 10" ) + 1 );
		if( !m_global_vars )
			return false;

		m_convar = get_interface< ICVar >( CT_HASH32( "VEngineCvar" ) );
		if( !m_convar )
			return false;
        
        return true;
    }
};

extern CSGO g_csgo;