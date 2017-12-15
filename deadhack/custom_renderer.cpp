#include "includes.h"

CustomRenderer::CustomRenderer() : m_renderer{}, m_geometry{}, m_render_target{}, m_fonts{} {
	
}

bool CustomRenderer::init( IDirect3DDevice9 *device ) {
	// create renderer.
	m_renderer = std::make_unique< OSHGui::Drawing::Direct3D9Renderer >( device );

	// initialize oshgui with renderer.
	OSHGui::Application::Initialize( std::move( m_renderer ) );

	// grab instance.
	auto &app = OSHGui::Application::Instance();

	// create fonts.
	m_fonts.push_back( OSHGui::Drawing::FontManager::LoadFont( "Verdana", 7.0f, true ) );
	app.SetDefaultFont( m_fonts.at( VERDANA ) );

	// create form.
	auto form = std::make_shared< OSHGui::Form>();

	// set form as mainform.
	app.Run( form );

	// enable it.
	app.Enable();

	// register hotkey.
	app.RegisterHotkey( OSHGui::Hotkey( OSHGui::Key::Insert, [] {
		OSHGui::Application::Instance().Toggle();
	}));

	return true;
}

bool CustomRenderer::create_geometry_buffer() {
	m_geometry = OSHGui::Application::Instance().GetRenderer().CreateGeometryBuffer();
	if( !m_geometry )
		return false;

	return true;
}

bool CustomRenderer::get_render_target() {
	m_render_target = OSHGui::Application::Instance().GetRenderer().GetDefaultRenderTarget();
	if( !m_render_target )
		return false;

	return true;
}

void CustomRenderer::start_drawing() {
	if( !create_geometry_buffer() )
		return;

	if( !get_render_target() )
		return;

	// let renderer begin its work.
	OSHGui::Application::Instance().GetRenderer().BeginRendering();
	// geometry will now be queued for drawing.
}

void CustomRenderer::end_drawing() const {
	// enable our geometry rendering.
	m_render_target->Activate();

	// draw our queued geometry (esp, etc).
	m_render_target->Draw( *m_geometry );

	// disable our geometry rendering.
	m_render_target->Deactivate();

	// render oshgui.
	OSHGui::Application::Instance().Render();

	// end the rendering.
	OSHGui::Application::Instance().GetRenderer().EndRendering();
}

void CustomRenderer::rect( const OSHGui::Drawing::Color &color, float x, float y, float width, float height ) const {
	OSHGui::Drawing::Graphics g( *m_geometry );
	g.DrawRectangle( color, OSHGui::Drawing::PointF( x, y ), OSHGui::Drawing::SizeF( width, height ) );
}

void CustomRenderer::filled_rect( const OSHGui::Drawing::Color &color, float x, float y, float width, float height ) const
{
	OSHGui::Drawing::Graphics g( *m_geometry );
	g.FillRectangle( color, OSHGui::Drawing::PointF( x, y ), OSHGui::Drawing::SizeF( width, height ) );
}

void CustomRenderer::text( const OSHGui::Misc::AnsiString &text, float x, float y ) const {
	OSHGui::Drawing::Graphics g( *m_geometry );

	// dropshadow.
	g.DrawString( text, OSHGui::Application::Instance().GetDefaultFont(), OSHGui::Drawing::Color( 0.8f, 0.03f, 0.03f, 0.03f ), OSHGui::Drawing::PointF( x + 1, y + 1 ) );
	
	g.DrawString( text, OSHGui::Application::Instance().GetDefaultFont(), OSHGui::Drawing::Color::White(), OSHGui::Drawing::PointF( x, y ) );
}