#pragma once

namespace Hooks {
    // hooked VMTs.
    static VMTHook g_D3D9_vmt{};

    // hooked func prototypes.
    using Present_t = HRESULT (__stdcall *)( IDirect3DDevice9 *, const RECT *, const RECT *, HWND, const RGNDATA * );

    // our funcs.
    static HRESULT __stdcall Present( IDirect3DDevice9 *device, const RECT *pSourceRect, const RECT *pDestRect, HWND hDestWindowOverride, const RGNDATA *pDirtyRegion );

    // initialize hooks.
    bool init();
}