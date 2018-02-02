#pragma once

class Vec3_t {
public:
    float x, y, z;

    __forceinline Vec3_t() : x{ 0.f }, y{ 0.f }, z{ 0.f } {
    
    }

    __forceinline Vec3_t( float x, float y, float z ) : x{ x }, y{ y }, z{ z } {
    
    }

	float &operator[]( int i ) {
		return reinterpret_cast<float *>( this )[ i ];
	}

	__forceinline float operator[]( int i ) const {
		return reinterpret_cast< float * >( (Vec3_t*)this )[ i ];
	}

	bool operator==( const Vec3_t &src ) const {
		return src.x == x && src.y == y && src.z == z;
	}

	bool operator!=( const Vec3_t& src ) const {
		return src.x != x || src.y != y;
	}

	Vec3_t &operator+=( const Vec3_t &v ) {
		x += v.x; y += v.y; z += v.z;
		return *this;
	}

	Vec3_t &operator+=( float fl ) {
		x += fl; y += fl; z += fl;
		return *this;
	}

	Vec3_t operator+( const Vec3_t &v ) const {
		return Vec3_t( x + v.x, y + v.y, z + v.z );
	}

	Vec3_t operator+( float fl ) const {
		return Vec3_t( x + fl, y + fl, z + fl );
	}

	Vec3_t &operator=( const Vec3_t &vec ) { 
		x = vec.x; y = vec.y; z = vec.z;
		return *this;
	}

	bool operator==( const Vec3_t &source ) {
		return source.x == x && source.y == y && source.z == z;
	}

	Vec3_t operator*( const float &fl ) const {
		return Vec3_t( x * fl, y * fl, z * fl );
	}

	Vec3_t &operator+=( const float &fl ) {
		x += fl; y += fl; z += fl;
		return *this;
	}

	Vec3_t &operator-=( const float &fl ) {
		x -= fl; y -= fl; z -= fl;
		return *this;
	}

	Vec3_t &operator/=( const float &fl ) {
		float oofl = 1.0f / fl;
		x *= oofl; y *= oofl; z *= oofl;
		return *this;
	}

	float dot( const float *fl ) const {
		const Vec3_t &a = *this;
		return a.x * fl[ 0 ] + a.y * fl[ 1 ] + a.z * fl[ 2 ];
	}

	float dot( const Vec3_t &vec ) const {
		const Vec3_t &a = *this;
		return a.x * vec.x + a.y * vec.y + a.z * vec.z;
	}

	float length( ) const {
		float sqsr = x * x + y * y + z * z;

		const auto sqrtss = [ ]( float in ) {
			__m128 reg = _mm_load_ss( &in );
			return _mm_mul_ss( reg, _mm_rsqrt_ss( reg ) ).m128_f32 [ 0 ];
		};

		return sqrtss( sqsr );
	}
};
