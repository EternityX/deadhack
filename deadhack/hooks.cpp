#include "includes.h"

static HRESULT __stdcall Hooks::Present( IDirect3DDevice9 *device, const RECT *pSourceRect, const RECT *pDestRect, HWND hDestWindowOverride, const RGNDATA *pDirtyRegion ) {
    // todo - dex; shitty test, should never draw this way, remove this later.
    D3DRECT rect{ 50, 50, 100, 100 };
    device->Clear( 1, &rect, D3DCLEAR_TARGET, D3DCOLOR_RGBA( 255, 255, 255, 255 ), 0, 0 );

    return g_D3D9_vmt.get_old_method< Present_t >( 17 )( device, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion );
}

bool Hooks::init() {
    // todo - dex; move all the sig scanning to CSGO class.
    uintptr_t shaderapidx9 = (uintptr_t)GetModuleHandleA( "shaderapidx9.dll" );
    if( !shaderapidx9 )
        return false;

    uintptr_t d3d9_vmt = SigScan::find( shaderapidx9, 0x9620, "A1 ? ? ? ? 6A 00 53" );
    if( !d3d9_vmt )
        return false;

    d3d9_vmt = **(uintptr_t **)( d3d9_vmt + 1 );

    MessageBoxA( 0, std::to_string( d3d9_vmt ).c_str(), "", 0 );

    // initialize VMTs.
    if( !g_D3D9_vmt.init( d3d9_vmt, false ) )
        return false;

    // hook virtual methods.
    if( !g_D3D9_vmt.hook_method( 17, &Present ) )
        return false;

    return true;
}