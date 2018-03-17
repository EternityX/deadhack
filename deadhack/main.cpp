#include "includes.h"

// classes.
CSGO              g_csgo{};
Input	          g_input{};
CustomRenderer    g_custom_renderer{};
NetVars           g_netvars{};
CVar              g_cvar{};
Menu              g_menu{};
Config            g_config{};
Offsets           g_offsets{};
LagCompensation   g_lagcomp{};
Client            g_cl{};
Visuals           g_visuals{};
Legitbot          g_legitbot{};
EnginePrediction  g_engine_pred{};
Misc              g_misc{};
Events            g_events{};
//Security        g_security{};

static ulong_t __stdcall cheat_init( void *arg ) {
	g_config.init();

    if( !g_csgo.init() ) {
#ifdef CHEAT_DBG
        DBG_ERROR( "g_csgo.init failed" );
#endif
        return 0;
    }

	if( !g_input.init( "Valve001" ) ) {
#ifdef CHEAT_DBG
		DBG_ERROR( "g_input.init failed" );
#endif
		return 0;
	}
	
	g_netvars.init();

	if( !g_offsets.init() ) {
#ifdef CHEAT_DBG
		DBG_ERROR( "Offsets::init failed" );
#endif
		return 0;
	}

    if( !Hooks::init() ) {
#ifdef CHEAT_DBG
        DBG_ERROR( "Hooks::init failed" );
#endif
        return 0;
    }

	if( !g_config.load( "default.cfg" ) && !g_config.save( "default.cfg", false ) ) {
#ifdef CHEAT_DBG
		DBG_ERROR( "Failed to load default profile." );
#endif
	}

	ConVar *con_filter = g_csgo.m_convar->FindVar( "con_filter_enable" );
	con_filter->SetValue( 2 );

	// set developer to 1 so notifications can be sent.
	ConVar *developer = g_csgo.m_convar->FindVar( "developer" );
	developer->SetValue( 1 );

	CSGO_Util::push_notification( Color( 204, 115, 135, 255 ), "Initialization complete\n" );
	CSGO_Util::push_notification( Color::White(), "DEADCELL Beta 0.4.1\n" );

    return 1;
}

static ulong_t __stdcall cheat_free( void *arg ) {

	while( !g_input.m_key_pressed[ VK_END ] )
		std::this_thread::sleep_for( std::chrono::milliseconds( 25 ) );

	// fixes crashing when reinjecting.
	if( OSHGui::Application::HasBeenInitialized() )
		g_custom_renderer.get_renderer().PreD3DReset();

	// lol bad, fix later.
	ConVar *cl_mouseenable = g_csgo.m_convar->FindVar( "cl_mouseenable" );
	cl_mouseenable->SetValue( 1 );

	g_events.remove();

	// erase clantag.
	if( g_cvar.m_misc.clantag->bValue )
		CSGO_Util::set_clan_tag( "" );

	if( !Hooks::unload() )
#ifdef CHEAT_DBG
		DBG_ERROR( "Hooks::unload failed" );
#endif

	if( !g_input.remove() )
#ifdef CHEAT_DBG
		 DBG_ERROR( "g_input.remove failed" );
#endif

	// pop outta this nigga.
	FreeLibraryAndExitThread( (HMODULE)arg, 0 );
}

int __stdcall DllMain( HMODULE self, ulong_t reason_for_call, void *reserved ) {
    HANDLE cheat_thread, free_thread;

    if( reason_for_call == DLL_PROCESS_ATTACH ) {
        cheat_thread = CreateThread( nullptr, 0, &cheat_init, nullptr, 0, nullptr );
        if( !cheat_thread )
            return 0;

        free_thread = CreateThread( nullptr, 0, &cheat_free, self, 0, nullptr );
        if( !free_thread )
            return 0;

        CloseHandle( cheat_thread );

        return 1;
    }

    return 0;
}