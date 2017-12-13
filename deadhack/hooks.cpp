#include "includes.h"

static HRESULT __stdcall Hooks::Present( IDirect3DDevice9 *device, const RECT *pSourceRect, const RECT *pDestRect, HWND hDestWindowOverride, const RGNDATA *pDirtyRegion ) {
    static bool once{ false };

    if( !once ) {
		// create renderer.
		auto renderer = std::make_unique< OSHGui::Drawing::Direct3D9Renderer >( device );
	    
	    // initialize oshgui with renderer.
	    OSHGui::Application::Initialize( std::move( renderer ) );

		// grab instance.
	    auto &app = OSHGui::Application::Instance();

		// create fonts.
	    auto font = OSHGui::Drawing::FontManager::LoadFont( "Verdana", 7.0f, true ); // general
		app.SetDefaultFont( font );

		auto form = std::make_shared< OSHGui::Form>();

		// test input stuff (remove later).
	    OSHGui::TextBox* textbox = new OSHGui::TextBox();
		textbox->SetFont( font );
		textbox->SetForeColor( OSHGui::Drawing::Color::FromARGB( 255, 201, 201, 201 ) );

		form->AddControl( textbox );

	    // set form as mainform.
	    app.Run( form );

		// enable it.
	    app.Enable();

	    // register hotkey.
	    app.RegisterHotkey( OSHGui::Hotkey( OSHGui::Key::Insert, [] {
	    	OSHGui::Application::Instance().Toggle();
	    }));

        once = true;
    }

    if( once ) {
		// retrieve renderer.
        auto &renderer = OSHGui::Application::Instance().GetRenderer();

	    // let renderer begin its work.
	    renderer.BeginRendering();

	    // render oshgui.
	    OSHGui::Application::Instance().Render();
        
	    // end the rendering.
	    renderer.EndRendering();
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