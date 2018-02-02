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
        
		g_visuals.work();

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

void __fastcall Hooks::PaintTraverse( uintptr_t ecx, uintptr_t edx, int vguiPanel, bool forceRepaint, bool allowForce ) {
	static int hud_zoom_panel = 0;
	if ( !hud_zoom_panel ) {
		if ( std::string( g_csgo.m_panel->GetName( vguiPanel ) ).compare( "HudZoom" ) == 0 )
			hud_zoom_panel = vguiPanel;
	}
	else {
		if ( g_cvar.m_visuals.remove_scope->bValue ) {
			if ( vguiPanel == hud_zoom_panel )
				return;
		}
	}

	g_Panel_vmt.get_old_method< PaintTraverse_t >( 41 )( ecx, vguiPanel, forceRepaint, allowForce );
}

void __fastcall Hooks::LevelInitPostEntity( CHLClient *ecx, uintptr_t edx ) {
	g_CHLClient_vmt.get_old_method< LevelInitPostEntity_t >( 6 )( ecx );
	g_client.m_local = C_CSPlayer::get_local();
	g_client.c4_timer = g_csgo.m_convar->FindVar( "mp_c4timer" );
}

void __fastcall Hooks::LevelShutdown( CHLClient *ecx, uintptr_t edx ) {
	g_CHLClient_vmt.get_old_method< LevelShutdown_t >( 7 )( ecx );
	g_client.m_local = nullptr;
	g_visuals.m_nightmode = false;
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

bool __fastcall Hooks::ShouldDrawFog( uintptr_t ecx, uintptr_t edx ) {
	return g_cvar.m_visuals.remove_fog->bValue ? false : true;
}

void __fastcall Hooks::OverrideView( uintptr_t ecx, uintptr_t edx, CViewSetup *pSetup ) {
	if( !g_client.m_local )
		return;

	if( !g_client.m_local->is_scoped() )
		pSetup->m_fov = g_cvar.m_visuals.override_fov->iValue;

	g_ClientMode_vmt.get_old_method< OverrideView_t >( 18 )( ecx, pSetup );
}

float __fastcall Hooks::GetViewModelFOV( uintptr_t ecx, uintptr_t edx ) {
	return g_cvar.m_visuals.weapon_fov->iValue;
}

bool __fastcall Hooks::OverrideConfig( IMaterialSystem *this0, void *, MaterialSystem_Config_t *config, bool bForceUpdate ) {
	//config->m_bDrawGray = g_cvar.m_visuals.draw_gray->bValue;
	config->m_nFullbright = g_cvar.m_visuals.fullbright->bValue;
	//config->m_bShowLowResImage = g_cvar.m_visuals.low_res->bValue;

	return g_MaterialSystem_vmt.get_old_method< OverrideConfig_t >( 21 )( this0, config, bForceUpdate );
}

void __fastcall Hooks::SceneEnd( uintptr_t ecx, uintptr_t edx ) {
	g_RenderView_vmt.get_old_method< SceneEnd_t >( 9 )( ecx );
	g_visuals.player_chams();
	g_csgo.m_model_render->SetForcedMaterialOverride( nullptr );
}

void __fastcall Hooks::DrawModelExecute( uintptr_t ecx, uintptr_t edx, void *ctx, void *state, const ModelRenderInfo_t &pInfo, matrix3x4_t *pCustomBoneToWorld  ) {
	const char *model_name = g_csgo.m_model_info->GetModelName( (model_t *)pInfo.m_model );
	
	g_ModelRender_vmt.get_old_method< DrawModelExecute_t >( 21 )( ecx, ctx, state, pInfo, pCustomBoneToWorld );
}

bool Hooks::init() {
	VM_EAGLE_WHITE_START

    // initialize VMTs.
    if( !g_D3D9_vmt.init( g_csgo.m_d3d9_vmt ) )
        return false;

	if( !g_CHLClient_vmt.init( g_csgo.m_client ) )
		return false;

	if( !g_ClientMode_vmt.init( g_csgo.m_client_mode ) )
		return false;

	if( !g_MaterialSystem_vmt.init( g_csgo.m_material_system ) )
		return false;

	if( !g_RenderView_vmt.init( g_csgo.m_render_view ) )
		return false;

	if( !g_Surface_vmt.init( g_csgo.m_surface ) )
		return false;

	if( !g_ModelRender_vmt.init( g_csgo.m_model_render ) )
		return false;

	if( !g_Panel_vmt.init( g_csgo.m_panel ) )
		return false;

    // hook virtual methods.
    if( !g_D3D9_vmt.hook_method( 17, &Present ) )
        return false;

	if( !g_D3D9_vmt.hook_method( 16, &Reset ) )
		return false;

	if( !g_Panel_vmt.hook_method( 41, &PaintTraverse ) )
		return false;

	if( !g_CHLClient_vmt.hook_method( 6, &LevelInitPostEntity ) )
		return false;

	if( !g_CHLClient_vmt.hook_method( 7, &LevelShutdown ) )
		return false;

	if( !g_ClientMode_vmt.hook_method( 24, &CreateMove ) )
		return false;

	if( !g_ClientMode_vmt.hook_method( 17, &ShouldDrawFog ) )
		return false;

	if( !g_ClientMode_vmt.hook_method( 18, &OverrideView ) )
		return false;

	if( !g_ClientMode_vmt.hook_method( 35, &GetViewModelFOV ) )
		return false;

	if( !g_MaterialSystem_vmt.hook_method( 21, &OverrideConfig ) )
		return false;

	if( !g_RenderView_vmt.hook_method( 9, &SceneEnd ) )
		return false;

	if( !g_ModelRender_vmt.hook_method( 21, &DrawModelExecute ) )
		return false;

	VM_EAGLE_WHITE_END

    return true;
}

bool Hooks::unload() {
	if( !g_D3D9_vmt.unhook_all() )
		return false;

	if( !g_Surface_vmt.unhook_all() )
		return false;

	if( !g_CHLClient_vmt.unhook_all() )
		return false;

	if( !g_ClientMode_vmt.unhook_all() )
		return false;

	if( !g_MaterialSystem_vmt.unhook_all() )
		return false;

	if( !g_RenderView_vmt.unhook_all() )
		return false;

	if( !g_ModelRender_vmt.unhook_all() )
		return false;

	if( !g_Panel_vmt.unhook_all() )
		return false;

	return true;
}