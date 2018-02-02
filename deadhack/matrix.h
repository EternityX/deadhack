#pragma once

using matrix4x4_t = float[ 4 ][ 4 ];

class matrix3x4_t {
public:
	matrix3x4_t() { }

	matrix3x4_t(
		float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23 ) {
		mat_val[ 0 ][ 0 ] = m00;
		mat_val[ 0 ][ 1 ] = m01;
		mat_val[ 0 ][ 2 ] = m02;
		mat_val[ 0 ][ 3 ] = m03;
		mat_val[ 1 ][ 0 ] = m10;
		mat_val[ 1 ][ 1 ] = m11;
		mat_val[ 1 ][ 2 ] = m12;
		mat_val[ 1 ][ 3 ] = m13;
		mat_val[ 2 ][ 0 ] = m20;
		mat_val[ 2 ][ 1 ] = m21;
		mat_val[ 2 ][ 2 ] = m22;
		mat_val[ 2 ][ 3 ] = m23;
	}

	void init( const Vec3_t &x, const Vec3_t &y, const Vec3_t &z, const Vec3_t &origin ) {
		mat_val[ 0 ][ 0 ] = x.x;
		mat_val[ 0 ][ 1 ] = y.x;
		mat_val[ 0 ][ 2 ] = z.x;
		mat_val[ 0 ][ 3 ] = origin.x;
		mat_val[ 1 ][ 0 ] = x.y;
		mat_val[ 1 ][ 1 ] = y.y;
		mat_val[ 1 ][ 2 ] = z.y;
		mat_val[ 1 ][ 3 ] = origin.y;
		mat_val[ 2 ][ 0 ] = x.z;
		mat_val[ 2 ][ 1 ] = y.z;
		mat_val[ 2 ][ 2 ] = z.z;
		mat_val[ 2 ][ 3 ] = origin.z;
	}

	matrix3x4_t( const Vec3_t &x, const Vec3_t &y, const Vec3_t &z, const Vec3_t &origin ) {
		init( x, y, z, origin );
	}

	void set_origin( const Vec3_t &p ) {
		mat_val[ 0 ][ 3 ] = p.x;
		mat_val[ 1 ][ 3 ] = p.y;
		mat_val[ 2 ][ 3 ] = p.z;
	}

	void invalidate() {
		for( int i = 0; i < 3; i++ ) {
			for( int j = 0; j < 4; j++ )
				mat_val[ i ][ j ] = std::numeric_limits< float >::infinity( );
		}
	}

	float *operator[]( int i ) {
		return mat_val[ i ];
	}

	const float *operator[]( int i ) const {
		return mat_val[ i ];
	}

	float *base() {
		return &mat_val[ 0 ][ 0 ];
	}

	const float *base() const {
		return &mat_val[ 0 ][ 0 ];
	}

	float mat_val[ 3 ][ 4 ];
};
