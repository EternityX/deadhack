#include "includes.h"

CustomRenderer::CustomRenderer() : m_renderer{}, m_geometry{}, m_render_target{}, m_fonts{}, m_instance{ nullptr } {
	
}

void CustomRenderer::init( IDirect3DDevice9 *device ) {
	m_renderer = std::make_unique< OSHGui::Drawing::Direct3D9Renderer >( device );

	// initialize oshgui with our renderer.
	OSHGui::Application::Initialize( std::move( m_renderer ) );

	m_instance = OSHGui::Application::InstancePtr();

	m_fonts.push_back( OSHGui::Drawing::FontManager::LoadFont( "Verdana", 7.0f, true ) );
    m_fonts.push_back( OSHGui::Drawing::FontManager::LoadFont( "Verdana Bold", 7.0f, true ) );
    m_fonts.push_back( OSHGui::Drawing::FontManager::LoadFont( "Tahoma Bold", 7.0f, false ) );
    
    // fallback font.
    m_fonts.push_back( OSHGui::Drawing::FontManager::LoadFont( "Arial Unicode MS", 8.0f, false ) );

	m_instance->SetDefaultFont( m_fonts[ 0 ] );
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

	get_renderer().BeginRendering();
}

void CustomRenderer::end_drawing() const {
	m_render_target->Activate();

	m_render_target->Draw( *m_geometry );

	m_render_target->Deactivate();

	m_instance->Render();

	get_renderer().EndRendering();
}

void CustomRenderer::rect( const Color &color, float x, float y, float width, float height ) const {
	OSHGui::Drawing::Graphics g( *m_geometry );

	g.DrawRectangle( color, OSHGui::Drawing::PointF( x, y ), OSHGui::Drawing::SizeF( width, height ) );
}

void CustomRenderer::filled_rect( const Color &color, float x, float y, float width, float height ) const {
	OSHGui::Drawing::Graphics g( *m_geometry );

	g.FillRectangle( color, OSHGui::Drawing::PointF( x, y ), OSHGui::Drawing::SizeF( width, height ) );
}

void CustomRenderer::ansi_text( OSHGui::Drawing::FontPtr font, const Color &color, float x, float y, const std::string str, ... ) const {
	// OSHGui::Drawing::FontPtr font_to_use;
    va_list     va;
    int         str_len;
    std::string buf;

    if( str.empty() )
        return;

    va_start( va, str );

    str_len = std::vsnprintf( nullptr, 0, str.c_str(), va );
    if( str_len < 0 ) {
        va_end( va );

        return;
    }

    buf.resize( str_len );

    std::vsnprintf( &buf[ 0 ], str_len + 1, str.c_str(), va );

    // todo; now we have to iterate over the font, check if the desired char is inside the font (should be a simple array / vector search) and draw...
    //       if not, fallback to the unicode font (should have lots of chars).

    OSHGui::Drawing::Graphics g( *m_geometry );

    g.DrawString( buf, font, color, x, y );
}

void CustomRenderer::unicode_text( OSHGui::Drawing::FontPtr font, const Color &color, float x, float y, const std::wstring wstr, ... ) const {
    va_list      va;
    int          str_len;
    std::wstring buf;

    if( wstr.empty() )
        return;

    va_start( va, wstr );

    str_len = std::vswprintf( nullptr, 0, wstr.c_str(), va );
    if( str_len < 0 ) {
        va_end( va );

        return;
    }

    buf.resize( str_len );

    std::vswprintf( &buf[ 0 ], str_len + 1, wstr.c_str(), va );

    // todo; now we have to iterate over the font, check if the desired char is inside the font (should be a simple array / vector search) and draw...
    //       if not, fallback to the unicode font (should have lots of chars).

    OSHGui::Drawing::Graphics g( *m_geometry );

    g.DrawString( buf, font, color, x, y );
}