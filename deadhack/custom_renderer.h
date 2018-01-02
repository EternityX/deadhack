#pragma once

using Color = OSHGui::Drawing::Color;

enum : uint32_t {
    FONT_VERDANA_7PX = 0,
    FONT_VERDANA_BOLD_7PX,
    FONT_TAHOMA_BOLD_7PX,
    FONT_ARIALUNICODEMS_BOLD_8PX,
    FONT_MAX
};

class CustomRenderer {
private:
    std::unique_ptr< OSHGui::Drawing::Direct3D9Renderer > m_renderer;
	OSHGui::Drawing::GeometryBufferPtr                    m_geometry;
	OSHGui::Drawing::RenderTargetPtr                      m_render_target;
	
public:
	std::vector< OSHGui::Drawing::FontPtr > m_fonts;
	OSHGui::Application*                    m_instance;

	CustomRenderer();
	void init( IDirect3DDevice9 *device );
	OSHGui::Drawing::Renderer& get_renderer() const;

	void start_drawing();
	void end_drawing() const;
	
	void rect( const Color &color, float x, float y, float width, float height ) const;
	void filled_rect( const Color &color, float x, float y, float width, float height ) const;

	void ansi_text( OSHGui::Drawing::FontPtr font, const Color &color, float x, float y, const std::string str, ... ) const;
	void unicode_text( OSHGui::Drawing::FontPtr font, const Color &color, float x, float y, const std::wstring wstr, ... ) const;
};

extern CustomRenderer g_custom_renderer;
