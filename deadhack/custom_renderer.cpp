#include "includes.h"

// todo - eternity; finish this...

CustomRenderer::CustomRenderer() : m_render_context{}, m_geometry{}, m_needs_redraw{ false }, m_fonts{} {
	
}

bool CustomRenderer::init( IDirect3DDevice9 *device ) {
	// create renderer.
	auto renderer = std::make_unique< Direct3D9Renderer >( device );

	// initialize oshgui with renderer.
	OSHGui::Application::Initialize( std::move( renderer ) );

	// grab instance.
	auto &app = OSHGui::Application::Instance();

	// create fonts.
	m_fonts.push_back( FontManager::LoadFont( "Verdana", 7.0f, true ) );
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

	if( !create_geometry_buffer() )
		return false;

	return true;
}

bool CustomRenderer::create_geometry_buffer() {
	m_geometry = OSHGui::Application::Instance().GetRenderer().CreateGeometryBuffer();
	if( !m_geometry )
		return false;

	return true;
}

void CustomRenderer::draw() {
	// retrieve renderer.
	auto &renderer = OSHGui::Application::Instance().GetRenderer();

	// let renderer begin its work.
	renderer.BeginRendering();

	// queue geometry.
	OSHGui::Application::Instance().GetRenderSurface().AddGeometry( RenderQueueType::Underlay, m_geometry );

	// render oshgui.
	OSHGui::Application::Instance().Render();

	// end the rendering.
	renderer.EndRendering();
}

void CustomRenderer::line( const Color &color, const PointF &from, const PointF &to ) const {
	m_geometry->SetVertexDrawMode( VertexDrawMode::LineList );

	Vertex vertices[ ] = {
		{ Vector( from.X, from.Y, 0.0f ), color },
		{ Vector( to.X, to.Y, 0.0f ), color }
	};
	m_geometry->AppendGeometry( vertices, 2 );

	m_geometry->SetVertexDrawMode( VertexDrawMode::TriangleList );
}

void CustomRenderer::filled_rect( const Color &color, const PointF &origin, const SizeF &size ) const {
	Graphics g( *m_geometry );
	g.FillRectangle( color, origin, size );
}

void CustomRenderer::filled_rect( const Color &color, float x, float y, float width, float height ) const
{
	Vertex vertices[ ] = {
		{ Vector( x, y, 0.0f ), color },
		{ Vector( x + width, y, 0.0f ), color },
		{ Vector( x, y + height, 0.0f ), color },
		{ Vector( x + width, y + height, 0.0f ), color },
		{ Vector( x, y + height, 0.0f ), color },
		{ Vector( x + width, y, 0.0f ), color }
	};
	m_geometry->AppendGeometry( vertices, 6 );
}