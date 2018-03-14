#pragma once

class OverlayText_t;

class IVDebugOverlay {
public:
	virtual void unkn() = 0;
	virtual void AddEntityTextOverlay( int ent_index, int line_offset, float duration, int r, int g, int b, int a, const char *format, ... ) = 0;
	virtual void AddBoxOverlay( const Vec3_t &origin, const Vec3_t &mins, const Vec3_t &max, Vec3_t const &orientation, int r, int g, int b, int a, float duration ) = 0;
	virtual void AddSphereOverlay( const Vec3_t &vOrigin, float flRadius, int nTheta, int nPhi, int r, int g, int b, int a, float flDuration ) = 0;
	virtual void AddTriangleOverlay( const Vec3_t &p1, const Vec3_t &p2, const Vec3_t &p3, int r, int g, int b, int a, bool noDepthTest, float duration ) = 0;
	virtual void AddLineOverlay( const Vec3_t &origin, const Vec3_t &dest, int r, int g, int b, bool noDepthTest, float duration ) = 0;
	virtual void AddTextOverlay( const Vec3_t &origin, float duration, const char *format, ... ) = 0;
	virtual void AddTextOverlay( const Vec3_t &origin, int line_offset, float duration, const char *format, ... ) = 0;
	virtual void AddScreenTextOverlay( float flXPos, float flYPos, float flDuration, int r, int g, int b, int a, const char *text ) = 0;
	virtual void AddSweptBoxOverlay( const Vec3_t &start, const Vec3_t &end, const Vec3_t &mins, const Vec3_t &max, const Vec3_t &angles, int r, int g, int b, int a, float flDuration ) = 0;
	virtual void AddGridOverlay( const Vec3_t &origin ) = 0;
	virtual void AddCoordFrameOverlay( const matrix3x4_t &frame, float flScale, int vColorTable[3][3] = nullptr ) = 0;
	virtual int ScreenPosition( const Vec3_t &point, Vec3_t &screen ) = 0;
	virtual int ScreenPosition( float flXPos, float flYPos, Vec3_t &screen ) = 0;
	virtual OverlayText_t *GetFirst( void ) = 0;
	virtual OverlayText_t *GetNext( OverlayText_t *current ) = 0;
	virtual void ClearDeadOverlays( void ) = 0;
	virtual void ClearAllOverlays() = 0;
	virtual void AddTextOverlayRGB( const Vec3_t &origin, int line_offset, float duration, float r, float g, float b, float alpha, const char *format, ... ) = 0;
	virtual void AddTextOverlayRGB( const Vec3_t &origin, int line_offset, float duration, int r, int g, int b, int a, const char *format, ... ) = 0;
	virtual void AddLineOverlayAlpha( const Vec3_t &origin, const Vec3_t &dest, int r, int g, int b, int a, bool noDepthTest, float duration ) = 0;
	virtual void AddBoxOverlay2( const Vec3_t &origin, const Vec3_t &mins, const Vec3_t &max, Vec3_t const &orientation, const uint8_t *faceColor, const uint8_t *edgeColor, float duration ) = 0;
	virtual void PurgeTextOverlays() = 0;
	virtual void DrawPill( const Vec3_t &mins, const Vec3_t &max, float &diameter, int r, int g, int b, int a, float duration ) = 0;

	void Cross3D( const Vec3_t &position, float size, int r, int g, int b, bool noDepthTest, float flDuration ) {
		AddLineOverlay( position + Vec3_t( size, 0, 0 ), position - Vec3_t( size, 0, 0 ), r, g, b, noDepthTest, flDuration );
		AddLineOverlay( position + Vec3_t( 0, size, 0 ), position - Vec3_t( 0, size, 0 ), r, g, b, noDepthTest, flDuration );
		AddLineOverlay( position + Vec3_t( 0, 0, size ), position - Vec3_t( 0, 0, size ), r, g, b, noDepthTest, flDuration );
	}

	//-----------------------------------------------------------------------------
	// Purpose: Draw circles to suggest a sphere
	//-----------------------------------------------------------------------------
	void Sphere( const Vec3_t &center, float radius, int r, int g, int b, bool noDepthTest, float flDuration ) {
		Vec3_t edge, lastEdge;

		float axisSize = radius;
		AddLineOverlay( center + Vec3_t( 0, 0, -axisSize ), center + Vec3_t( 0, 0, axisSize ), r, g, b, noDepthTest, flDuration );
		AddLineOverlay( center + Vec3_t( 0, -axisSize, 0 ), center + Vec3_t( 0, axisSize, 0 ), r, g, b, noDepthTest, flDuration );
		AddLineOverlay( center + Vec3_t( -axisSize, 0, 0 ), center + Vec3_t( axisSize, 0, 0 ), r, g, b, noDepthTest, flDuration );

		lastEdge = Vec3_t( radius + center.x, center.y, center.z );
		float angle;
		for( angle = 0.0f; angle <= 360.0f; angle += 22.5f ) {
			edge.x = radius * cosf( angle / 180.0f * Math::pi ) + center.x;
			edge.y = center.y;
			edge.z = radius * sinf( angle / 180.0f * Math::pi ) + center.z;

			AddLineOverlay( edge, lastEdge, r, g, b, noDepthTest, flDuration );

			lastEdge = edge;
		}

		lastEdge = Vec3_t( center.x, radius + center.y, center.z );
		for( angle = 0.0f; angle <= 360.0f; angle += 22.5f ) {
			edge.x = center.x;
			edge.y = radius * cosf( angle / 180.0f * Math::pi ) + center.y;
			edge.z = radius * sinf( angle / 180.0f * Math::pi ) + center.z;

			AddLineOverlay( edge, lastEdge, r, g, b, noDepthTest, flDuration );

			lastEdge = edge;
		}

		lastEdge = Vec3_t( center.x, radius + center.y, center.z );
		for( angle = 0.0f; angle <= 360.0f; angle += 22.5f ) {
			edge.x = radius * cosf( angle / 180.0f * Math::pi ) + center.x;
			edge.y = radius * sinf( angle / 180.0f * Math::pi ) + center.y;
			edge.z = center.z;

			AddLineOverlay( edge, lastEdge, r, g, b, noDepthTest, flDuration );

			lastEdge = edge;
		}
	}
};
