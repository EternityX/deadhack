#include "includes.h"

static HRESULT __stdcall Hooks::Present( IDirect3DDevice9 *device, const RECT *pSourceRect, const RECT *pDestRect, HWND hDestWindowOverride, const RGNDATA *pDirtyRegion ) {
    //// todo - dex; shitty test, should never draw this way, remove this later.
    //D3DRECT rect{ 50, 50, 100, 100 };
    //device->Clear( 1, &rect, D3DCLEAR_TARGET, D3DCOLOR_RGBA( 255, 255, 255, 255 ), 0, 0 );

    static bool once{ false };

    if( !once ) {
        // todo - dex; make this a global for rendering...?
        // std::unique_ptr< OSHGui::Drawing::Direct3D9Renderer > renderer;
        // 
        // renderer = std::make_unique< OSHGui::Drawing::Direct3D9Renderer >();

        // 1. create our renderer, Direct3D9 in this case
	    auto renderer = std::unique_ptr<OSHGui::Drawing::Direct3D9Renderer>(new OSHGui::Drawing::Direct3D9Renderer(device));
	    
	    // 2. and initialize the OSHGui with it
	    OSHGui::Application::Initialize(std::move(renderer));

        // OSHGui::Application::Initialize( std::unique_ptr< OSHGui::Drawing::Direct3D9Renderer >( new OSHGui::Drawing::Direct3D9Renderer( device ) ) );

        auto &app = OSHGui::Application::Instance();

        auto font = OSHGui::Drawing::FontManager::LoadFont("Arial", 8.0f, false); //Arial, 8PT, no anti-aliasing
	    app.SetDefaultFont(font);

        auto form = std::make_shared< OSHGui::Form >();
	    form->SetText("Test");

	    //5. set this form as our mainform
	    app.Run(form);

	    //optional: enable the OSHGui drawing
	    app.Enable();

	    //optional: register a Hotkey with which we can toggle the OSHGui drawing
	    app.RegisterHotkey(OSHGui::Hotkey(OSHGui::Key::Insert, []
	    {
	    	OSHGui::Application::Instance().Toggle();
	    }));

        once = true;
    }

    if( once ) {
        //static OSHGui::Drawing::GeometryBufferPtr geometry_;
        //
        //// add custom stuff...
        //OSHGui::Drawing::Graphics g( *geometry_ );
        //
        //g.DrawRectangle( OSHGui::Drawing::Color( 255, 255, 255, 255 ), 50.f, 50.f, 100.f, 100.f );

        auto &renderer = OSHGui::Application::Instance().GetRenderer();
        
	    // let our renderer begin its work.
	    renderer.BeginRendering();
        
	    // render the OSHGui.
	    OSHGui::Application::Instance().Render();
        
	    // end the rendering.
	    renderer.EndRendering();
    }

    return g_D3D9_vmt.get_old_method< Present_t >( 17 )( device, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion );
}

bool Hooks::init() {
    // initialize VMTs.
    if( !g_D3D9_vmt.init( g_csgo.m_d3d9_vmt ) )
        return false;

    // hook virtual methods.
    if( !g_D3D9_vmt.hook_method( 17, &Present ) )
        return false;

    return true;
}