#pragma once

namespace Hooks {
    // hooked VMTs.
    static VMTHook g_D3D9_vmt{};
	static VMTHook g_CHLClient_vmt{};
	static VMTHook g_ClientMode_vmt{};
	static VMTHook g_MaterialSystem_vmt{};
	static VMTHook g_RenderView_vmt{};
	static VMTHook g_Surface_vmt{};
	static VMTHook g_ModelRender_vmt{};
	static VMTHook g_Panel_vmt{};
	static VMTHook g_StudioRender_vmt{};

    // hooked func prototypes.
    using Present_t             = HRESULT (__stdcall *)( IDirect3DDevice9 *, const RECT *, const RECT *, HWND, const RGNDATA * );
	using Reset_t               = HRESULT (__stdcall *)( IDirect3DDevice9 *, D3DPRESENT_PARAMETERS * );
	using PaintTraverse_t       = void (__thiscall *)( uintptr_t, int, bool, bool );
	using LevelInitPostEntity_t = void (__thiscall *)( uintptr_t );
	using LevelShutdown_t       = void (__thiscall *)( uintptr_t );
	using CreateMove_t          = bool (__thiscall *)( uintptr_t, float, CUserCmd * );
	using ShouldDrawFog_t       = bool (__thiscall *)( uintptr_t );
	using OverrideView_t        = void (__thiscall *)( uintptr_t, CViewSetup * );
	using GetViewModelFOV_t     = float(__thiscall *)( uintptr_t );
	using OverrideConfig_t      = bool( __thiscall * )( uintptr_t, MaterialSystem_Config_t *, bool );
	using BeginFrame_t          = void (__thiscall *)( uintptr_t, float );
	using SceneEnd_t            = void (__thiscall *)( uintptr_t );
	using DrawModelExecute_t    = void (__thiscall *)( uintptr_t, void *, void *, const ModelRenderInfo_t &, matrix3x4_t * );
	using FrameStageNotify_t    = void (__thiscall *)( uintptr_t, ClientFrameStage_t );
	using DrawModel_t           = void (__thiscall *)( uintptr_t, uintptr_t, DrawModelInfo_t &, matrix3x4_t *, float *, float *, Vec3_t &, int );
	using DoPostScreenEffects_t = bool (__thiscall *)( uintptr_t, const CViewSetup * );

    // our funcs.
    static HRESULT __stdcall Present( IDirect3DDevice9 *device, const RECT *pSourceRect, const RECT *pDestRect, HWND hDestWindowOverride, const RGNDATA *pDirtyRegion );
	static HRESULT __stdcall Reset( IDirect3DDevice9 *device, D3DPRESENT_PARAMETERS *pPresentationParameters );
	static void __fastcall PaintTraverse( uintptr_t ecx, uintptr_t edx, int vguiPanel, bool forceRepaint, bool allowForce );
	static void __fastcall LevelInitPostEntity( uintptr_t ecx, uintptr_t edx );
	static void __fastcall LevelShutdown( uintptr_t ecx, uintptr_t edx );
	static bool __fastcall CreateMove( uintptr_t ecx, uintptr_t edx, float flInputSampleTime, CUserCmd *cmd );
	static bool __fastcall ShouldDrawFog( uintptr_t ecx, uintptr_t edx );
	static void __fastcall OverrideView( uintptr_t ecx, uintptr_t edx, CViewSetup *pSetup );
	static float __fastcall GetViewModelFOV( uintptr_t ecx, uintptr_t edx );
	static bool __fastcall OverrideConfig( uintptr_t ecx, uintptr_t edx, MaterialSystem_Config_t *config, bool bForceUpdate );
	static void __fastcall BeginFrame( uintptr_t ecx, uintptr_t edx, float frameTime );
	static void __fastcall SceneEnd( uintptr_t ecx, uintptr_t edx );
	static void __fastcall DrawModelExecute( uintptr_t ecx, uintptr_t edx, void *ctx, void *state, const ModelRenderInfo_t &pInfo, matrix3x4_t *pCustomBoneToWorld );
	static void __fastcall FrameStageNotify( uintptr_t ecx, uintptr_t edx, ClientFrameStage_t curstage );
	static void __fastcall DrawModel( uintptr_t ecx, uintptr_t edx, uintptr_t results, DrawModelInfo_t &info, matrix3x4_t *pBoneToWorld, float *pFlexWeights, float *pFlexDelayedWeights, Vec3_t &origin, int drawFlags );
	static bool __fastcall DoPostScreenSpaceEffects( uintptr_t ecx, uintptr_t edx, const CViewSetup *pSetup );

    // initialize hooks.
    bool init();

	// unload hooks.
	bool unload();
}