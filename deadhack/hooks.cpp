#include "includes.h"

static HRESULT __stdcall Hooks::Present( IDirect3DDevice9 *device, const RECT *pSourceRect, const RECT *pDestRect, HWND hDestWindowOverride, const RGNDATA *pDirtyRegion ) {
    static bool init{ false };

    if( !init ) {
		// init oshgui and renderer.
		g_custom_renderer.init( device );
		init = true;
    }
    else {
		g_custom_renderer.start_drawing();

		g_custom_renderer.rect( OSHGui::Drawing::Color::Blue(), 50, 50, 50, 50 );
		g_custom_renderer.text( "nigga", 50, 100 );
		g_custom_renderer.filled_rect( OSHGui::Drawing::Color::Red(), 50, 125, 50, 50 );

		g_custom_renderer.end_drawing();
    }

    return g_D3D9_vmt.get_old_method< Present_t >( 17 )( device, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion );
}

static HRESULT __stdcall Hooks::Reset( IDirect3DDevice9 *device, D3DPRESENT_PARAMETERS *pPresentationParameters ) {
	auto &renderer = OSHGui::Application::Instance().GetRenderer();

	renderer.PreD3DReset();

	HRESULT ret = g_D3D9_vmt.get_old_method< Reset_t >( 16 )( device, pPresentationParameters );

	renderer.PostD3DReset();

	return ret;
}

bool Hooks::init() {
    // initialize VMTs.
    if( !g_D3D9_vmt.init( g_csgo.m_d3d9_vmt ) )
        return false;

    // hook virtual methods.
    if( !g_D3D9_vmt.hook_method( 17, &Present ) )
        return false;

	if( !g_D3D9_vmt.hook_method( 16, &Reset ) )
		return false;

    return true;
}

bool Hooks::unload() {
	if( !g_D3D9_vmt.unhook_all() )
		return false;

	return true;
}