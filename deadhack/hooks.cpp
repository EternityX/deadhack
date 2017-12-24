#include "includes.h"

static HRESULT __stdcall Hooks::Present( IDirect3DDevice9 *device, const RECT *pSourceRect, const RECT *pDestRect, HWND hDestWindowOverride, const RGNDATA *pDirtyRegion ) {
    static bool init{ false };

    if( !init ) {
		// init oshgui and renderer.
		g_custom_renderer.init( device );

		// init menu.
		g_menu.init();
	    
		init = true;
    }
    else {
		g_custom_renderer.start_drawing();

		if ( g_cvar.m_misc.watermark )
			g_custom_renderer.text( 50, 100, "deadcell" );

		g_custom_renderer.end_drawing();
    }

    return g_D3D9_vmt.get_old_method< Present_t >( 17 )( device, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion );
}

static HRESULT __stdcall Hooks::Reset( IDirect3DDevice9 *device, D3DPRESENT_PARAMETERS *pPresentationParameters ) {
	g_custom_renderer.m_instance->GetRenderer().PreD3DReset();

	HRESULT ret = g_D3D9_vmt.get_old_method< Reset_t >( 16 )( device, pPresentationParameters );

	g_custom_renderer.m_instance->GetRenderer().PostD3DReset();

	return ret;
}

bool __stdcall Hooks::CreateMove( float flInputSampleTime, CUserCmd *cmd ) {
	bool ret = g_ClientMode_vmt.get_old_method< CreateMove_t >( 24 )( flInputSampleTime, cmd );

	// called from CInput::ExtraMouseSample -> return original.
	if( !cmd->m_command_number )
		return ret;

	// if we arrived here, called from -> CInput::CreateMove
	// call EngineClient::SetViewAngles according to what the original returns.
	if( ret )
		return false; // todo

	// todo; finish this :s

	return false;
}

bool Hooks::init() {
    // initialize VMTs.
    if( !g_D3D9_vmt.init( g_csgo.m_d3d9_vmt ) )
        return false;

	if( !g_ClientMode_vmt.init( g_csgo.m_client_mode ) )
		return false;

    // hook virtual methods.
    if( !g_D3D9_vmt.hook_method( 17, &Present ) )
        return false;

	if( !g_D3D9_vmt.hook_method( 16, &Reset ) )
		return false;

	if( !g_ClientMode_vmt.hook_method( 24, &CreateMove ) )
		return false;

    return true;
}

bool Hooks::unload() {
	if( !g_D3D9_vmt.unhook_all() )
		return false;

	if( !g_ClientMode_vmt.unhook_all() )
		return false;

	return true;
}