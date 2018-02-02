#include "includes.h"

// classes.
CSGO            g_csgo{};
Input	        g_input{};
CustomRenderer  g_custom_renderer{};
NetVars         g_netvars{};
CVar            g_cvar{};
Menu            g_menu{};
Config          g_config{};
Offsets         g_offsets{};
LagCompensation g_lagcomp{};
Client          g_client{};
Visuals         g_visuals{};

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

	CSGO_Util::push_notification( Color( 180, 255, 0, 255 ), "Initialization complete\n" );
	CSGO_Util::push_notification( Color( 255, 255, 255, 255 ), "DEADCELL Beta 0.1.3" );

    return 1;
}

static ulong_t __stdcall cheat_free( void *arg ) {
#ifdef CHEAT_DBG
	while( !g_input.m_key_pressed[ VK_END ] )
		std::this_thread::sleep_for( std::chrono::milliseconds( 25 ) );

	// fixes crashing when reinjecting.
	if( g_custom_renderer.m_instance->HasBeenInitialized() )
		g_custom_renderer.get_renderer().PreD3DReset();

	// lol bad, fix later
	ConVar *cl_mouseenable = g_csgo.m_convar->FindVar( "cl_mouseenable" );
	cl_mouseenable->SetValue( 1 );

#ifdef CHEAT_DBG
	if( !Hooks::unload() )
		DBG_ERROR( "Hooks::unload failed" );

	if( !g_input.remove() )
		 DBG_ERROR( "g_input.remove failed" );
#endif

	// pop outta this nigga.
	FreeLibraryAndExitThread( (HMODULE)arg, 0 );
#endif
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