#include "includes.h"

// todo - dex; maybe move this into its own class ( named after the cheat )?
static ulong_t __stdcall cheat_init( void *arg ) {
    // todo - dex; init cheat related stuff, etc...

    return 1;
}

static ulong_t __stdcall cheat_free( void *arg ) {
    // todo - dex; finish this...

    // FreeLibraryAndExitThread( 0, 0 );

    return 1;
}

int __stdcall DllMain( HMODULE self, ulong_t reason_for_call, void *reserved ) {
    HANDLE cheat_thread, free_thread;

    // todo - dex; testing, remove this later.
    static_assert( CT_CONSTHASH32( "testing123" ) == 0x374b74d5, "const hash failed" );

    if( reason_for_call == DLL_PROCESS_ATTACH ) {
        cheat_thread = CreateThread( nullptr, 0, &cheat_init, nullptr, 0, nullptr );
        if( !cheat_thread )
            return 0;

        // todo; save off handle to our module.

        // set up thread for freeing hack / etc.
        free_thread = CreateThread( nullptr, 0, &cheat_free, nullptr, 0, nullptr );
        //if( !free_thread )
        //    return 0;

        // close handle to main hack thread.
        CloseHandle( cheat_thread );

        return 1;
    }

    return 0;
}