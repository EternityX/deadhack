#pragma once

using namespace OSHGui::Drawing;

class CustomRenderer {
private:
	RenderContext m_render_context;
	GeometryBufferPtr m_geometry;
	RenderSurface* m_surface;

	bool setup_drawing();
	void line( const Color &color, const PointF &from, const PointF &to ) const;
	

public:
	bool m_needs_redraw;
	std::vector< FontPtr > m_fonts;

	enum Fonts {
		VERDANA,
		VERDANA_BOLD
	};

	CustomRenderer();
	bool init( IDirect3DDevice9 *device );
	bool create_geometry_buffer();
	void draw();

	void filled_rect( const Color &color, const PointF &origin, const SizeF &size ) const;
	void filled_rect( const Color &color, float x, float y, float width, float height ) const;
};

extern CustomRenderer g_custom_renderer;
