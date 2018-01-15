#include "includes.h"

HRESULT __stdcall Hooks::Present( IDirect3DDevice9 *device, const RECT *pSourceRect, const RECT *pDestRect, HWND hDestWindowOverride, const RGNDATA *pDirtyRegion ) {
    static bool once{ false };

    if( !once ) { // todo - dex; move to entry...
        g_custom_renderer.init( device );

        g_menu.init();

        once = true;
    }
    
    else {
        g_custom_renderer.start_drawing();
        
		if( g_cvar.m_misc.watermark->bValue )
			g_custom_renderer.ansi_text( g_custom_renderer.m_fonts[ FONT_VERDANA_7PX ], Color::White(), 22.f, 22.f, "deadcell.cc" );

        g_custom_renderer.end_drawing();
    }

    return g_D3D9_vmt.get_old_method< Present_t >( 17 )( device, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion );
}

HRESULT __stdcall Hooks::Reset( IDirect3DDevice9 *device, D3DPRESENT_PARAMETERS *pPresentationParameters ) {
	g_custom_renderer.m_instance->GetRenderer().PreD3DReset();

	HRESULT ret = g_D3D9_vmt.get_old_method< Reset_t >( 16 )( device, pPresentationParameters );

	g_custom_renderer.m_instance->GetRenderer().PostD3DReset();

	return ret;
}

void __fastcall Hooks::LevelInitPostEntity( CHLClient *ecx, uintptr_t edx ) {
	g_CHLClient_vmt.get_old_method< LevelInitPostEntity_t >( 6 )( ecx );
	g_client.m_local = C_CSPlayer::get_local();
}

void __fastcall Hooks::LevelShutdown( CHLClient *ecx, uintptr_t edx ) {
	g_CHLClient_vmt.get_old_method< LevelShutdown_t >( 7 )( ecx );
	g_client.m_local = nullptr;
}

bool __fastcall Hooks::CreateMove( uintptr_t ecx, uintptr_t edx, float flInputSampleTime, CUserCmd *cmd ) {
	bool ret = g_ClientMode_vmt.get_old_method< CreateMove_t >( 24 )( ecx, flInputSampleTime, cmd );

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

void __fastcall Hooks::OverrideView( uintptr_t ecx, uintptr_t edx, CViewSetup *pSetup ) {
	pSetup->m_fov = g_cvar.m_misc.override_fov->iValue;
	g_CHLClient_vmt.get_old_method< OverrideView_t >( 18 )( ecx, pSetup );
}

bool Hooks::init() {
    // initialize VMTs.
    if( !g_D3D9_vmt.init( g_csgo.m_d3d9_vmt ) )
        return false;

	if( !g_CHLClient_vmt.init( g_csgo.m_client ) )
		return false;

	if( !g_ClientMode_vmt.init( g_csgo.m_client_mode ) )
		return false;

    // hook virtual methods.
    if( !g_D3D9_vmt.hook_method( 17, &Present ) )
        return false;

	if( !g_D3D9_vmt.hook_method( 16, &Reset ) )
		return false;

	if( !g_CHLClient_vmt.hook_method( 6, &LevelInitPostEntity ) )
		return false;

	if( !g_CHLClient_vmt.hook_method( 7, &LevelShutdown ) )
		return false;

	if( !g_ClientMode_vmt.hook_method( 24, &CreateMove ) )
		return false;

	if( !g_ClientMode_vmt.hook_method( 18, &OverrideView ) )
		return false;

    return true;
}

bool Hooks::unload() {
	if( !g_D3D9_vmt.unhook_all() )
		return false;

	if( !g_CHLClient_vmt.unhook_all() )
		return false;

	if( !g_ClientMode_vmt.unhook_all() )
		return false;

	return true;
}