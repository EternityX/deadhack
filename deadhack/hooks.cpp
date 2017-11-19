#include "includes.h"

static HRESULT __stdcall Hooks::EndScene( IDirect3DDevice9 *device ) {

    return D3D9_vmt.get_old_method< EndScene_t >( 42 )( device );
}

bool Hooks::init() {
    uintptr_t d3d9 = (uintptr_t)GetModuleHandleA( "d3d9.dll" );
    if( !d3d9 )
        return false;

    uintptr_t d3d9_vmt = SigScan::find( d3d9, 0x1854A, "C7 06 ? ? ? ? 89 86 ? ? ? ? 89 86" ) + 2;
    if( !d3d9_vmt )
        return false;

    //// initialize VMTs.
    //if( !D3D9_vmt.init( d3d9_vmt, false ) )
    //    return false;

    //// hook virtual methods.
    //if( !D3D9_vmt.hook_method( 42, &EndScene ) )
    //    return false;

    return true;
}