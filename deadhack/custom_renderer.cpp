#include "includes.h"

CustomRenderer::CustomRenderer() : m_renderer{}, m_geometry{}, m_render_target{}, m_fonts{}, m_instance{ nullptr } {
	
}

void CustomRenderer::init( IDirect3DDevice9 *device ) {
	// create renderer.
	m_renderer = std::make_unique< OSHGui::Drawing::Direct3D9Renderer >( device );

	// initialize oshgui with renderer.
	OSHGui::Application::Initialize( std::move( m_renderer ) );

	// grab instance.
	m_instance = OSHGui::Application::InstancePtr();

	// create fonts.
	m_fonts.push_back( OSHGui::Drawing::FontManager::LoadFont( "Verdana", 7.0f, true ) );
	m_fonts.push_back( OSHGui::Drawing::FontManager::LoadFont( "Verdana Bold", 7.0f, true ) );
	m_fonts.push_back( OSHGui::Drawing::FontManager::LoadFont( "Tahoma Bold", 7.0f, false ) );

	// unicode font for use when tahoma can't display the character.
	// arial unicode is probably the best for our use, but it's not included with windows?...
    m_fonts.push_back( OSHGui::Drawing::FontManager::LoadFont( "Arial Unicode MS", 8.0f, false ) );

	m_instance->SetDefaultFont( m_fonts.at( 0 ) );
}

OSHGui::Drawing::Renderer& CustomRenderer::get_renderer() const {
	return m_instance->GetRenderer();
}

void CustomRenderer::start_drawing() {
	m_geometry = get_renderer().CreateGeometryBuffer();
	if( !m_geometry )
		return;

	m_render_target = get_renderer().GetDefaultRenderTarget();
	if( !m_render_target )
		return;

	// let renderer begin its work.
	get_renderer().BeginRendering();
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
	m_instance->Render();

	// end the rendering.
	get_renderer().EndRendering();
}

void CustomRenderer::rect( const OSHGui::Drawing::Color &color, float x, float y, float width, float height ) const {
	OSHGui::Drawing::Graphics g( *m_geometry );
	g.DrawRectangle( color, OSHGui::Drawing::PointF( x, y ), OSHGui::Drawing::SizeF( width, height ) );
}

void CustomRenderer::filled_rect( const OSHGui::Drawing::Color &color, float x, float y, float width, float height ) const {
	OSHGui::Drawing::Graphics g( *m_geometry );
	g.FillRectangle( color, OSHGui::Drawing::PointF( x, y ), OSHGui::Drawing::SizeF( width, height ) );
}

void CustomRenderer::ansi_text( OSHGui::Drawing::FontPtr font, OSHGui::Drawing::Color color, float x, float y, const char *format, ... ) const {
	char buffer[ 1024 ] = { };

	OSHGui::Drawing::FontPtr font_to_use = font;

	va_list va;
	va_start( va, format );
	vsnprintf_s( buffer, 1024, format, va );
	va_end( va );

	OSHGui::Drawing::Graphics g( *m_geometry );

	g.DrawString( buffer, font_to_use, color, OSHGui::Drawing::PointF( x, y ) );
}

void CustomRenderer::ansi_text( float x, float y, const char *format, ... ) const {
	ansi_text( m_instance->GetDefaultFont(), OSHGui::Drawing::Color::White(), x, y, format );
}

void CustomRenderer::ansi_text( OSHGui::Drawing::FontPtr font, float x, float y, const char *format, ... ) const {
	ansi_text( font, OSHGui::Drawing::Color::White(), x, y, format );
}

void CustomRenderer::unicode_text( OSHGui::Drawing::FontPtr font, OSHGui::Drawing::Color color, float x, float y, wchar_t *format, ... ) const {
	wchar_t buffer[ 1024 ] = { };

	va_list va;
	va_start( va, format );
	vswprintf( buffer, 1024, format, va );
	va_end( va );

	OSHGui::Drawing::Graphics g( *m_geometry );

	g.DrawString( buffer, font, color, OSHGui::Drawing::PointF( x, y ) );
}

void CustomRenderer::unicode_text( float x, float y, wchar_t *format, ... ) const {
	unicode_text( m_fonts.at( 3 ), OSHGui::Drawing::Color::White(), x, y, format );
}

void CustomRenderer::unicode_text( OSHGui::Drawing::FontPtr font, float x, float y, wchar_t *format, ... ) const {
	unicode_text( font, OSHGui::Drawing::Color::White(), x, y, format );
}

void CustomRenderer::unicode_text( OSHGui::Drawing::Color color, float x, float y, wchar_t *format, ... ) const {
	unicode_text( m_fonts.at( 3 ), color, x, y, format );
}