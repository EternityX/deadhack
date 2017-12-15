#pragma once

class CustomRenderer {
private:
    std::unique_ptr< OSHGui::Drawing::Direct3D9Renderer > m_renderer;
	OSHGui::Drawing::GeometryBufferPtr m_geometry;
	OSHGui::Drawing::RenderTargetPtr m_render_target;

	bool create_geometry_buffer();
	bool get_render_target();
	
public:
	std::vector< OSHGui::Drawing::FontPtr > m_fonts;

	enum Fonts {
		VERDANA,
		VERDANA_BOLD
	};

	enum FontFlags
	{
		NO_FLAGS = 0,
		CENTERED_X = 1,
		CENTERED_Y = 2,
		OUTLINED = 4,
		DROPSHADOW = 8
	};

	CustomRenderer();
	bool init( IDirect3DDevice9 *device );

	void start_drawing();
	void end_drawing() const;
	
	void rect( const OSHGui::Drawing::Color &color, float x, float y, float width, float height ) const;
	void filled_rect( const OSHGui::Drawing::Color &color, float x, float y, float width, float height ) const;
	void text( const OSHGui::Misc::AnsiString &text, float x, float y ) const;
};

extern CustomRenderer g_custom_renderer;
