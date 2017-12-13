#pragma once

namespace Hooks {
    // hooked VMTs.
    static VMTHook g_D3D9_vmt{};

    // hooked func prototypes.
    using Present_t = HRESULT (__stdcall *)( IDirect3DDevice9 *, const RECT *, const RECT *, HWND, const RGNDATA * );
	using Reset_t = HRESULT (__stdcall *)( IDirect3DDevice9 *, D3DPRESENT_PARAMETERS * );

    // our funcs.
    static HRESULT __stdcall Present( IDirect3DDevice9 *device, const RECT *pSourceRect, const RECT *pDestRect, HWND hDestWindowOverride, const RGNDATA *pDirtyRegion );
	static HRESULT __stdcall Reset( IDirect3DDevice9 *device, D3DPRESENT_PARAMETERS *pPresentationParameters );

    // initialize hooks.
    bool init();

	// unload hooks.
	bool unload();
}