#include "includes.h"

CustomRenderer::CustomRenderer() : m_renderer{}, m_geometry{}, m_render_target{}, m_fonts{}, m_instance{ nullptr } {
	
}

void CustomRenderer::init( IDirect3DDevice9 *device ) {
	m_renderer = std::make_unique< OSHGui::Drawing::Direct3D9Renderer >( device );

	// initialize oshgui with our renderer.
	OSHGui::Application::Initialize( std::move( m_renderer ) );

	m_instance = OSHGui::Application::InstancePtr();

    m_fonts.resize( FONT_MAX );

	m_fonts[ FONT_VERDANA_7PX ]      = OSHGui::Drawing::FontManager::LoadFont( "Verdana", 7.0f, true );
    m_fonts[ FONT_VERDANA_BOLD_7PX ] = OSHGui::Drawing::FontManager::LoadFont( "Verdana Bold", 7.0f, true );
    m_fonts[ FONT_04B03_6PX ]  = OSHGui::Drawing::FontManager::LoadFont( "04b03", 6.0f, false );
    
    // fallback font.
    m_fonts[ FONT_ARIALUNICODEMS_BOLD_8PX ] = OSHGui::Drawing::FontManager::LoadFont( "Arial Unicode MS", 8.0f, false );

	m_instance->SetDefaultFont( m_fonts[ FONT_VERDANA_7PX ] );
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

void CustomRenderer::ansi_text( OSHGui::Drawing::FontPtr font, const Color &color, const Color &shadow_color, float x, float y, int flags, const std::string str, ... ) const {
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
    //       do we really want this here yet?

    OSHGui::Drawing::Graphics g( *m_geometry );

	if( flags & CENTERED_X || flags & CENTERED_Y ) {
		OSHGui::Misc::TextHelper text_helper( font );
		text_helper.SetText( str );

		if( flags & CENTERED_X )
			x -= ( text_helper.GetSize().Width / 2.0f );

		if ( flags & CENTERED_Y )
			y -= text_helper.GetSize().Height / 2.0f;
	}

	if( flags & DROPSHADOW )
		g.DrawString( buf, font, shadow_color, x + 1, y + 1 );

	if( flags & OUTLINED ) {
		g.DrawString( buf, font, shadow_color, x, y + 1 );
		g.DrawString( buf, font, shadow_color, x, y - 1 );
		g.DrawString( buf, font, shadow_color, x + 1, y );
		g.DrawString( buf, font, shadow_color, x - 1, y );
	}

    g.DrawString( buf, font, color, x, y );
}

void CustomRenderer::unicode_text( OSHGui::Drawing::FontPtr font, const Color &color, const Color &shadow_color, float x, float y, int flags, const std::wstring wstr, ... ) const {
    va_list      va;
    int          str_len;
    std::wstring buf;
    bool         invalid_font;

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

    // ensure this string has all the characters needed.
    invalid_font = false;

    for( const auto &c : buf ) {
        if( !font->GetGlyphData( c ) )
            invalid_font = true;
    }

    // just try to use the fallback font...
    if( invalid_font )
        font = m_fonts[ FONT_ARIALUNICODEMS_BOLD_8PX ];

    OSHGui::Drawing::Graphics g( *m_geometry );

	if( flags & DROPSHADOW )
		g.DrawString( buf, font, shadow_color, x + 1, y + 1 );

	if( flags & OUTLINED ) {
		g.DrawString( buf, font, shadow_color, x, y + 1 );
		g.DrawString( buf, font, shadow_color, x, y - 1 );
		g.DrawString( buf, font, shadow_color, x + 1, y );
		g.DrawString( buf, font, shadow_color, x - 1, y );
	}

    g.DrawString( buf, font, color, x, y );
}