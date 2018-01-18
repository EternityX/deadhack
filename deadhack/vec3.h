#pragma once

class Vec3_t {
public:
    float x, y, z;

    __forceinline Vec3_t() : x{ 0.f }, y{ 0.f }, z{ 0.f } {
    
    }

    __forceinline Vec3_t( float x, float y, float z ) : x{ x }, y{ y }, z{ z } {
    
    }

	__forceinline Vec3_t &operator[]( int i ) {
		return ( (Vec3_t *)this )[ i ];
	}

	__forceinline Vec3_t operator[]( int i ) const {
		return ( (Vec3_t *)this )[ i ];
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
};