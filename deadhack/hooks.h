#pragma once

namespace Hooks {
    // hooked VMTs.
    static VMTHook D3D9_vmt{};

    // hooked func prototypes.
    using EndScene_t = HRESULT (__stdcall *)( IDirect3DDevice9 *device );

    // todo; add hooked funcs here...
    static HRESULT __stdcall EndScene( IDirect3DDevice9 *device );
    // ex: static __fastcall CreateMove( CHLClient *ecx, uintptr_t edx, args... );

    bool init();
}