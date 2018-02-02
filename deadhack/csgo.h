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
	IVModelInfo          *m_model_info;
	IMaterialSystem      *m_material_system;
	IVRenderView         *m_render_view;
	IVModelRender        *m_model_render;
	ISurface             *m_surface;
	IVDebugOverlay       *m_debug_overlay;
	IPanel               *m_panel;

    // functions.

    CSGO() : m_client_dll{}, m_engine_dll{}, m_d3d9_vmt{} {
    
    }

    bool init() {
		VM_DOLPHIN_WHITE_START

		int local_tamper;

        // modules.
        m_client_dll = PE::get_module( CT_HASH32( "client.dll" ) );
        m_engine_dll = PE::get_module( CT_HASH32( "engine.dll" ) );
        if( !m_client_dll || !m_engine_dll )
            return false;

		CHECK_PROTECTION( local_tamper, 0x8773 )

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

		// just fuck my shit up here.
		if( local_tamper != 0x8773 ) {
			m_client = **(CHLClient ***)*(uintptr_t ***)m_engine;
			delete m_engine;
		}

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

		m_model_info = get_interface< IVModelInfo >( CT_HASH32( "VModelInfoClient" ) );
		if( !m_model_info )
			return false;

		m_material_system = get_interface< IMaterialSystem >( CT_HASH32( "VMaterialSystem" ) );
		if( !m_material_system )
			return false;

		m_render_view = get_interface< IVRenderView >( CT_HASH32( "VEngineRenderView" ) );
		if( !m_render_view )
			return false;

		m_model_render = get_interface< IVModelRender >( CT_HASH32( "VEngineModel" ) );
		if( !m_model_render )
			return false;
        
		m_surface = get_interface< ISurface >( CT_HASH32( "VGUI_Surface" ) );
		if( !m_surface )
			return false;

		m_debug_overlay = get_interface< IVDebugOverlay >( CT_HASH32( "VDebugOverlay" ) );
		if( !m_debug_overlay )
			return false;

		m_panel = get_interface< IPanel >( CT_HASH32( "VGUI_Panel" ) );
		if( !m_panel )
			return false;

		VM_DOLPHIN_WHITE_END

        return true;
    }
};

extern CSGO g_csgo;