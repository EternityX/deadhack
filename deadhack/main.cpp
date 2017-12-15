#include "includes.h"

// classes.
CSGO             g_csgo{};
Input	         g_input{};
CustomRenderer   g_custom_renderer{};

static ulong_t __stdcall cheat_init( void *arg ) {
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

    if( !Hooks::init() ) {
#ifdef CHEAT_DBG
        DBG_ERROR( "Hooks::init failed" );
#endif
        return 0;
    }

#ifdef CHEAT_DBG
    MessageBoxA( nullptr, "loaded", "cheat_init", 0 );
#endif

    return 1;
}

static ulong_t __stdcall cheat_free( void *arg ) {
#ifdef CHEAT_DBG
	while( !g_input.m_key_pressed[ VK_END ] )
		std::this_thread::sleep_for( std::chrono::milliseconds( 25 ) );

	// fixes crashing when reinjecting.
	if( OSHGui::Application::HasBeenInitialized() )
		OSHGui::Application::Instance().GetRenderer().PreD3DReset();

	// unhook everything.
	if( !Hooks::unload() )
		DBG_ERROR( "Hooks::unload failed" );

	// remove wndproc hook.
	if( !g_input.remove() )
		 DBG_ERROR( "g_input.remove failed" );

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