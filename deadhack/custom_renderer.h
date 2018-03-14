#pragma once

using OSHColor = OSHGui::Drawing::Color;

enum : uint32_t {
    FONT_VERDANA_7PX = 0,
    FONT_VERDANA_BOLD_7PX,
    FONT_04B03_6PX,
    FONT_ARIALUNICODEMS_BOLD_8PX,
    FONT_MAX
};

enum : uint32_t {
	NO_FLAGS = 0,
	CENTERED_X = 1,
	CENTERED_Y = 2,
	OUTLINED = 4,
	DROPSHADOW = 8
};

class CustomRenderer {
private:
    std::unique_ptr< OSHGui::Drawing::Direct3D9Renderer > m_renderer;
	
public:
	OSHGui::Drawing::GeometryBufferPtr                    m_geometry;
	OSHGui::Drawing::RenderTargetPtr                      m_render_target;
	std::vector< OSHGui::Drawing::FontPtr > m_fonts;
	OSHGui::Application*                    m_instance;

	CustomRenderer();
	void init( IDirect3DDevice9 *device );
	OSHGui::Drawing::Renderer& get_renderer() const;

	void start_drawing();
	void end_drawing() const;
	void rect( const OSHColor &color, int x, int y, int width, int height ) const;
	void filled_rect( const OSHColor &color, int x, int y, int width, int height ) const;
	void line( const OSHColor &color, int x, int y, int end_x, int end_y ) const;
	void circle( const OSHColor &color, int x, int y, int radius );
	void fill_polygon( const std::vector<OSHGui::Drawing::PointF> &vertices, const OSHColor &color );

	/*void rect( const OSHColor &color, float x, float y, float width, float height ) const;
	void filled_rect( const OSHColor &color, float x, float y, float width, float height ) const;*/

	void ansi_text( OSHGui::Drawing::FontPtr font, const OSHColor &color, const OSHColor &shadow_color, float x, float y, int flags, const std::string str, ... ) const;
	void unicode_text( OSHGui::Drawing::FontPtr font, const OSHColor &color, const OSHColor &shadow_color, float x, float y, int flags, const std::wstring wstr, ... ) const;
};

extern CustomRenderer g_custom_renderer;
