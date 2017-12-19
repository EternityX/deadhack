#pragma once

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
	
	void rect( const OSHGui::Drawing::Color &color, float x, float y, float width, float height ) const;
	void filled_rect( const OSHGui::Drawing::Color &color, float x, float y, float width, float height ) const;
	void text( OSHGui::Drawing::FontPtr font, OSHGui::Drawing::Color color, float x, float y, const char *format,... ) const;
	void text( OSHGui::Drawing::FontPtr font, float x, float y, const char *format,... ) const;
	void text( float x, float y, const char *format, ... ) const;
};

extern CustomRenderer g_custom_renderer;
