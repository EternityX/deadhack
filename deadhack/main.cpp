#include "includes.h"

// classes.
CSGO    g_csgo{};
Input   g_input{};

// todo - dex; maybe move this into its own class ( named after the cheat )?
static ulong_t __stdcall cheat_init( void *arg ) {
    if( !g_csgo.init() ) {
#ifdef CHEAT_DBG
        DBG_ERROR( "g_csgo.init failed" );
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
    // todo - dex; finish this... or not...

    return 1;
}

int __stdcall DllMain( HMODULE self, ulong_t reason_for_call, void *reserved ) {
    HANDLE cheat_thread /*, free_thread*/;

    if( reason_for_call == DLL_PROCESS_ATTACH ) {
        cheat_thread = CreateThread( nullptr, 0, &cheat_init, nullptr, 0, nullptr );
        if( !cheat_thread )
            return 0;

        // todo - dex; save off handle to our module...?

        //// todo - dex; do we really need an unload routine?
        //free_thread = CreateThread( nullptr, 0, &cheat_free, nullptr, 0, nullptr );
        //if( !free_thread )
        //    return 0;

        CloseHandle( cheat_thread );

        return 1;
    }

    return 0;
}