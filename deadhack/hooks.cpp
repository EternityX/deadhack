#include "includes.h"

HRESULT __stdcall Hooks::Present( IDirect3DDevice9 *device, const RECT *pSourceRect, const RECT *pDestRect, HWND hDestWindowOverride, const RGNDATA *pDirtyRegion ) {
    static bool once{ false };

    if( !once ) { // todo - dex; move to entry...
        g_custom_renderer.init( device );

        g_menu.init();

        once = true;
    }
    else {
		int screen_width, screen_height;
		
		if( g_csgo.m_engine )
			g_csgo.m_engine->GetScreenSize( screen_width, screen_height );
	
		OSHGui::Drawing::SizeF osh_screen_size = g_custom_renderer.m_instance->GetRenderer().GetDisplaySize();

		if( screen_width != osh_screen_size.Width || screen_height != osh_screen_size.Height )
			g_custom_renderer.m_instance->GetRenderer().SetDisplaySize( OSHGui::Drawing::SizeF( screen_width, screen_height ) );
			
        g_custom_renderer.start_drawing();
        
#ifdef CHEAT_DBG
		g_cl.m_local = C_CSPlayer::get_local();
#endif
		
		g_visuals.work();

		if( g_cvar.m_misc.spectators->bValue )
			Visuals::draw_spectators();

	    Visuals::watermark();

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
		if ( std::string( g_csgo.m_panel->GetName( vguiPanel ) ) == "HudZoom" )
			hud_zoom_panel = vguiPanel;
	}
	else {
		if ( g_cvar.m_visuals.remove_scope->bValue ) {
			if ( vguiPanel == hud_zoom_panel )
				return;
		}
	}

	g_Panel_vmt.get_old_method< PaintTraverse_t >( 41 )( ecx, vguiPanel, forceRepaint, allowForce );

	// ghetto fix for people who don't use net_graph/cl_showpos/cl_showfps.
	g_csgo.m_surface->DrawSetColor( Color( 0, 0, 0, 255 ) );
	g_csgo.m_surface->DrawFilledRect( 1, 1, 1, 1 );
}

void __fastcall Hooks::LevelInitPostEntity( uintptr_t ecx, uintptr_t edx ) {
	g_CHLClient_vmt.get_old_method< LevelInitPostEntity_t >( 6 )( ecx );

	std::fill( std::begin( g_lagcomp.m_players ), std::end( g_lagcomp.m_players ), PlayerRecord_t() );

	g_cl.m_local  = C_CSPlayer::get_local();
	g_cl.c4_timer = g_csgo.m_convar->FindVar( "mp_c4timer" );
}

void __fastcall Hooks::LevelShutdown( uintptr_t ecx, uintptr_t edx ) {
	g_CHLClient_vmt.get_old_method< LevelShutdown_t >( 7 )( ecx );

	std::fill( std::begin( g_lagcomp.m_players ), std::end( g_lagcomp.m_players ), PlayerRecord_t() );

	g_cl.m_local      = nullptr;
	g_visuals.m_nightmode = false;
}

bool __fastcall Hooks::CreateMove( uintptr_t ecx, uintptr_t edx, float flInputSampleTime, CUserCmd *cmd ) {
	bool ret = g_ClientMode_vmt.get_old_method< CreateMove_t >( 24 )( ecx, flInputSampleTime, cmd );

	// called from CInput::ExtraMouseSample -> return original.
	if( !cmd->m_command_number )
		return ret;

	const Vec3_t original_view_angles = cmd->m_viewangles;

	if( g_cvar.m_misc.reveal_ranks->bValue && cmd->m_buttons & IN_SCORE )
		g_misc.reveal_ranks();

	INetChannelInfo *channel_info = g_csgo.m_engine->GetNetChannelInfo();
	if( channel_info ) {
		float latency = channel_info->GetLatency( FLOW_INCOMING ) + channel_info->GetLatency( FLOW_OUTGOING );

		g_cl.m_rtt = (int)std::round( latency * 1000.f );
		g_cl.m_ping = (int)std::round( channel_info->GetAverageLatency( FLOW_OUTGOING ) * 1000.f );
	}

	g_cl.m_cmd = cmd;

	/*ulong_t base = (uintptr_t)_AddressOfReturnAddress() - sizeof( uintptr_t );
	*( *(bool **)base - 0x1C ) = g_cl.m_send_packet;*/

	// if we arrived here, called from -> CInput::CreateMove
	// call EngineClient::SetViewAngles according to what the original returns.
	if( ret )
		g_csgo.m_engine->SetViewAngles( cmd->m_viewangles );

	if( g_cvar.m_misc.bunnyhop->bValue )
		g_misc.bunnyhop( cmd );

	g_engine_pred.start( cmd );

	C_BaseCombatWeapon *local_weapon = nullptr;
	if( g_cl.m_local ) local_weapon = g_cl.m_local->get_active_weapon();

	g_legitbot.setup_group_config( local_weapon );

	if( g_legitbot.m_cfg.history_aim )
		g_legitbot.history_aim( cmd );

	if( g_legitbot.m_cfg.trigger_enabled )
		g_legitbot.triggerbot( local_weapon, cmd );

	if( g_cvar.m_misc.autopistol->bValue )
		g_misc.automatic_fire( local_weapon, cmd );

	g_engine_pred.end();

	return false;
}

bool __fastcall Hooks::ShouldDrawFog( uintptr_t ecx, uintptr_t edx ) {
	return !g_cvar.m_visuals.remove_fog->bValue;
}

void __fastcall Hooks::OverrideView( uintptr_t ecx, uintptr_t edx, CViewSetup *pSetup ) {
	if( !g_cl.m_local )
		return;

	if( !g_cl.m_local->is_scoped() && g_cl.m_local->get_health() > 0 )
		pSetup->m_fov = g_cvar.m_visuals.override_fov->iValue;

	//CTraceFilter filter;
	//filter.m_skip = g_cl.m_local;

	//Vec3_t view_angles;
	//g_csgo.m_engine->GetViewAngles( view_angles );

	//Vec3_t cam_offset = Vec3_t( view_angles.x, view_angles.y, 120.f );	
	//Vec3_t eye_pos = g_cl.m_local->get_eye_position();

	//// move the camera distance closer if it hit something.
	//Ray_t ray;
	//ray.init( eye_pos, eye_pos - Vec3_t( cam_offset.x, cam_offset.y, 0.f ).forward() * cam_offset.z, Vec3_t( -16.f, -16.f, -16.f ), Vec3_t( 16.f, 16.f, 16.f ) );

	//CGameTrace trace;
	//g_csgo.m_engine_trace->TraceRay( ray, MASK_ALL, &filter, &trace );

	//if( trace.m_fraction < 1.f )
	//	cam_offset.z *= trace.m_fraction;

	//Vec3_t forward = Vec3_t( cam_offset.x, cam_offset.y, 0.f ).forward();

	//// birds eye view. basically lets you look over objects nicely.
	//// not required obviously.
	//pSetup->m_origin = Vec3_t(
	//	pSetup->m_origin.x + -cam_offset.z * forward.x,
	//	pSetup->m_origin.y + -cam_offset.z * forward.y,
	//	pSetup->m_origin.z + -cam_offset.z * forward.z
	//);

	//pSetup->m_angles = Vec3_t( cam_offset.x, cam_offset.y, 0.f );

	g_ClientMode_vmt.get_old_method< OverrideView_t >( 18 )( ecx, pSetup );
}

float __fastcall Hooks::GetViewModelFOV( uintptr_t ecx, uintptr_t edx ) {
	return g_cvar.m_visuals.weapon_fov->iValue;
}

bool __fastcall Hooks::OverrideConfig( uintptr_t ecx, uintptr_t edx, MaterialSystem_Config_t *config, bool bForceUpdate ) {
	//config->m_bDrawGray = g_cvar.m_visuals.draw_gray->bValue;
	config->m_nFullbright = g_cvar.m_visuals.fullbright->bValue;
	//config->m_bShowLowResImage = g_cvar.m_visuals.low_res->bValue;

	return g_MaterialSystem_vmt.get_old_method< OverrideConfig_t >( 21 )( ecx, config, bForceUpdate );
}

void __fastcall Hooks::BeginFrame( uintptr_t ecx, uintptr_t edx, float frameTime ) {
	g_csgo.m_debug_overlay->ClearAllOverlays();

	g_MaterialSystem_vmt.get_old_method< BeginFrame_t >( 42 )( ecx, frameTime  );

	if( !g_cl.m_local )
		return;

	g_misc.clan_tag();

	// what's the point in doing it here...
	if( g_cvar.m_visuals.grenade_projectiles->bValue ) {
		for( auto &i : g_events.m_inferno_start_burn->m_inferno )
			g_csgo.m_debug_overlay->Cross3D( i.m_position, 15.f, 255, 0, 255, true, 7.f );
	}
}

void __fastcall Hooks::SceneEnd( uintptr_t ecx, uintptr_t edx ) {
	g_RenderView_vmt.get_old_method< SceneEnd_t >( 9 )( ecx );

	g_visuals.player_chams();

	g_csgo.m_model_render->ForcedMaterialOverride( nullptr );
}

void __fastcall Hooks::DrawModelExecute( uintptr_t ecx, uintptr_t edx, void *ctx, void *state, const ModelRenderInfo_t &pInfo, matrix3x4_t *pCustomBoneToWorld  ) {
	/*const char *model_name = g_csgo.m_model_info->GetModelName( (model_t *)pInfo.m_model );*/	
	g_ModelRender_vmt.get_old_method< DrawModelExecute_t >( 21 )( ecx, ctx, state, pInfo, pCustomBoneToWorld );
}

void __fastcall Hooks::FrameStageNotify( uintptr_t ecx, uintptr_t edx, ClientFrameStage_t curstage ) {
	if( curstage == FRAME_NET_UPDATE_POSTDATAUPDATE_START ) {
		/*if( g_cvar.m_legit.historyaim->iValue )*/
			g_lagcomp.think();

		if( g_cl.m_local != nullptr ) {
			if( g_cvar.m_visuals.remove_flash->bValue )
				g_cl.m_local->get_flash_max_alpha() = 0.f;
			else
				g_cl.m_local->get_flash_max_alpha() = 255.f;
		}
	}

	if( curstage == FRAME_RENDER_START ) {
		for( int i = 1; i <= g_csgo.m_global_vars->m_max_clients; i++ ) {
			C_CSPlayer *entity = (C_CSPlayer *)g_csgo.m_entity_list->GetClientEntity( i );
			if( !entity || entity == g_cl.m_local )
				continue;

			if( g_cvar.m_visuals.cham_lagrecords ) {
				// todo: only do this for occluded players.
				*(int *) ( (uintptr_t) entity + 0xA30 ) = g_csgo.m_global_vars->m_frame_count;
				*(int *) ( (uintptr_t) entity + 0xA28 ) = 0;
			}
		}

		if( g_offsets.m_OverridePostProcessingDisable )
			*(bool *)g_offsets.m_OverridePostProcessingDisable = g_cvar.m_visuals.remove_post_processing->bValue;
	}

	g_CHLClient_vmt.get_old_method< FrameStageNotify_t >( 36 )( ecx, curstage );
}

void __fastcall Hooks::DrawModel( uintptr_t ecx, uintptr_t edx, uintptr_t results, DrawModelInfo_t &info, matrix3x4_t *pBoneToWorld, float *pFlexWeights, float *pFlexDelayedWeights, Vec3_t &origin, int drawFlags ) {	
	static auto meme = g_StudioRender_vmt.get_old_method< DrawModel_t >( 29 );

	if( g_visuals.world_chams( meme, ecx, results, info, pBoneToWorld, pFlexWeights, pFlexDelayedWeights, origin, drawFlags ) ) {
		g_csgo.m_model_render->ForcedMaterialOverride( nullptr );
		return;
	}

	g_StudioRender_vmt.get_old_method< DrawModel_t >( 29 )( ecx, results, info, pBoneToWorld, pFlexWeights, pFlexDelayedWeights, origin, drawFlags );
}

bool __fastcall Hooks::DoPostScreenSpaceEffects( uintptr_t ecx, uintptr_t edx, const CViewSetup *pSetup ) {
	if( !g_cl.m_local )
		return g_ClientMode_vmt.get_old_method< DoPostScreenEffects_t >( 44 )( ecx, pSetup );;

	if( g_cvar.m_visuals.glow->bValue )
		g_visuals.draw_glow();

	return g_ClientMode_vmt.get_old_method< DoPostScreenEffects_t >( 44 )( ecx, pSetup );
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

	if( !g_StudioRender_vmt.init( g_csgo.m_studio_render ) )
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

	if( !g_CHLClient_vmt.hook_method( 36, &FrameStageNotify ) )
		return false;

	if( !g_ClientMode_vmt.hook_method( 24, &CreateMove ) )
		return false;

	if( !g_ClientMode_vmt.hook_method( 17, &ShouldDrawFog ) )
		return false;

	if( !g_ClientMode_vmt.hook_method( 18, &OverrideView ) )
		return false;

	if( !g_ClientMode_vmt.hook_method( 35, &GetViewModelFOV ) )
		return false;

	if( !g_ClientMode_vmt.hook_method( 44, &DoPostScreenSpaceEffects ) )
		return false;

	if( !g_MaterialSystem_vmt.hook_method( 21, &OverrideConfig ) )
		return false;

	if( !g_MaterialSystem_vmt.hook_method( 42, &BeginFrame ) )
		return false;

	if( !g_RenderView_vmt.hook_method( 9, &SceneEnd ) )
		return false;

	if( !g_ModelRender_vmt.hook_method( 21, &DrawModelExecute ) )
		return false;

	if( !g_StudioRender_vmt.hook_method( 29, &DrawModel ) )
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

	if( !g_StudioRender_vmt.unhook_all() )
		return false;

	return true;
}