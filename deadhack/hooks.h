#pragma once

namespace Hooks {
    // hooked VMTs.
    static VMTHook g_D3D9_vmt{};
	static VMTHook g_CHLClient_vmt{};
	static VMTHook g_ClientMode_vmt{};

    // hooked func prototypes.
    using Present_t             = HRESULT (__stdcall *)( IDirect3DDevice9 *, const RECT *, const RECT *, HWND, const RGNDATA * );
	using Reset_t               = HRESULT (__stdcall *)( IDirect3DDevice9 *, D3DPRESENT_PARAMETERS * );
	using LevelInitPostEntity_t = void (__thiscall *)( CHLClient * );
	using LevelShutdown_t       = void (__thiscall *)( CHLClient * );
	using CreateMove_t          = bool (__thiscall *)( uintptr_t, float, CUserCmd * );

    // our funcs.
    static HRESULT __stdcall Present( IDirect3DDevice9 *device, const RECT *pSourceRect, const RECT *pDestRect, HWND hDestWindowOverride, const RGNDATA *pDirtyRegion );
	static HRESULT __stdcall Reset( IDirect3DDevice9 *device, D3DPRESENT_PARAMETERS *pPresentationParameters );
	static void __fastcall LevelInitPostEntity( CHLClient *ecx, uintptr_t edx );
	static void __fastcall LevelShutdown( CHLClient *ecx, uintptr_t edx );
	static bool __fastcall CreateMove( uintptr_t ecx, uintptr_t edx, float flInputSampleTime, CUserCmd *cmd );

    // initialize hooks.
    bool init();

	// unload hooks.
	bool unload();
}