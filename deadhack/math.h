#pragma once

class Vec2_t;
class Vec3_t;

namespace Math {
    // pi constants.
    constexpr float pi{ 3.141592654f };
    constexpr float pi_2{ pi * 2.f };
    constexpr float pi_1divpi{ 1.f / pi };
    constexpr float pi_1div2pi{ 1.f / pi_2 };
    constexpr float pi_div2{ pi / 2.f };
    constexpr float pi_div4{ pi / 4.f };
#define rad( a ) a * 0.01745329251

    // degrees to radians.
    __forceinline constexpr float deg_to_rad( float val ) {
        return val * ( pi / 180.f );
    }
    
    // radians to degrees.
    __forceinline constexpr float rad_to_deg( float val ) {
        return val * ( 180.f / pi );
    }

	__forceinline void sin_to_cos( const float radians, float &sine, float &cosine ) {
		const __m128 _ps_fopi = _mm_set_ss( 1.27323954473516f );

		const __m128 _ps_0p5 = _mm_set_ss( 0.5f );
		const __m128 _ps_1 = _mm_set_ss( 1.0f );

		const __m128 _ps_dp1 = _mm_set_ss( -0.7851562f );
		const __m128 _ps_dp2 = _mm_set_ss( -2.4187564849853515625e-4f );
		const __m128 _ps_dp3 = _mm_set_ss( -3.77489497744594108e-8f );

		const __m128 _ps_sincof_p0 = _mm_set_ss( 2.443315711809948e-5f );
		const __m128 _ps_sincof_p1 = _mm_set_ss( 8.3321608736e-3f );
		const __m128 _ps_sincof_p2 = _mm_set_ss( -1.6666654611e-1f );
		const __m128 _ps_coscof_p0 = _mm_set_ss( 2.443315711809948e-5f );
		const __m128 _ps_coscof_p1 = _mm_set_ss( -1.388731625493765e-3f );
		const __m128 _ps_coscof_p2 = _mm_set_ss( 4.166664568298827e-2f );

		const __m128i _pi32_1 = _mm_set1_epi32( 1 );
		const __m128i _pi32_i1 = _mm_set1_epi32( ~1 );
		const __m128i _pi32_2 = _mm_set1_epi32( 2 );
		const __m128i _pi32_4 = _mm_set1_epi32( 4 );

		const __m128 _mask_sign_raw = *(__m128 *)&_mm_set1_epi32( 0x80000000 );
		const __m128 _mask_sign_inv = *(__m128 *)&_mm_set1_epi32( ~0x80000000 );

		__m128i emm0, emm2, emm4;

		__m128 sign_bit_cos, sign_bit_sin;

		__m128 x, y, z;
		__m128 y1, y2;

		__m128 a = _mm_set_ss( radians );

		x = _mm_and_ps( a, _mask_sign_inv );
		y = _mm_mul_ps( x, _ps_fopi );

		emm2 = _mm_cvtps_epi32( y );
		emm2 = _mm_add_epi32( emm2, _pi32_1 );
		emm2 = _mm_and_si128( emm2, _pi32_i1 );
		y = _mm_cvtepi32_ps( emm2 );

		emm4 = emm2;

		emm0 = _mm_and_si128( emm2, _pi32_4 );
		emm0 = _mm_slli_epi32( emm0, 29 );
		__m128 swap_sign_bit_sin = _mm_castsi128_ps( emm0 );

		emm2 = _mm_and_si128( emm2, _pi32_2 );
		emm2 = _mm_cmpeq_epi32( emm2, _mm_setzero_si128( ) );
		__m128 poly_mask = _mm_castsi128_ps( emm2 );

		x = _mm_add_ps( x, _mm_mul_ps( y, _ps_dp1 ) );
		x = _mm_add_ps( x, _mm_mul_ps( y, _ps_dp2 ) );
		x = _mm_add_ps( x, _mm_mul_ps( y, _ps_dp3 ) );

		emm4 = _mm_sub_epi32( emm4, _pi32_2 );
		emm4 = _mm_andnot_si128( emm4, _pi32_4 );
		emm4 = _mm_slli_epi32( emm4, 29 );

		sign_bit_cos = _mm_castsi128_ps( emm4 );
		sign_bit_sin = _mm_xor_ps( _mm_and_ps( a, _mask_sign_raw ), swap_sign_bit_sin );

		z = _mm_mul_ps( x, x );

		y1 = _mm_mul_ps( _ps_coscof_p0, z );
		y1 = _mm_add_ps( y1, _ps_coscof_p1 );
		y1 = _mm_mul_ps( y1, z );
		y1 = _mm_add_ps( y1, _ps_coscof_p2 );
		y1 = _mm_mul_ps( y1, z );
		y1 = _mm_mul_ps( y1, z );
		y1 = _mm_sub_ps( y1, _mm_mul_ps( z, _ps_0p5 ) );
		y1 = _mm_add_ps( y1, _ps_1 );

		y2 = _mm_mul_ps( _ps_sincof_p0, z );
		y2 = _mm_add_ps( y2, _ps_sincof_p1 );
		y2 = _mm_mul_ps( y2, z );
		y2 = _mm_add_ps( y2, _ps_sincof_p2 );
		y2 = _mm_mul_ps( y2, z );
		y2 = _mm_mul_ps( y2, x );
		y2 = _mm_add_ps( y2, x );

		__m128 ysin2 = _mm_and_ps( poly_mask, y2 );
		__m128 ysin1 = _mm_andnot_ps( poly_mask, y1 );

		sine = _mm_cvtss_f32( _mm_xor_ps( _mm_add_ps( ysin1, ysin2 ), sign_bit_sin ) );
		cosine = _mm_cvtss_f32( _mm_xor_ps( _mm_add_ps( _mm_sub_ps( y1, ysin1 ), _mm_sub_ps( y2, ysin2 ) ), sign_bit_cos ) );
	}

    // sse min.
    template< typename t = float > __forceinline t min( const t &a, const t &b ) {
        // check type.
        static_assert( std::is_arithmetic< t >::value, "Math::min only supports integral types." );

        return (t)_mm_cvtss_f32( 
            _mm_min_ss( _mm_set_ss( (float)a ), 
            _mm_set_ss( (float)b ) ) 
        );
    }
    
    // sse max.
    template< typename t = float > __forceinline t max( const t &a, const t &b ) {
        // check type.
        static_assert( std::is_arithmetic< t >::value, "Math::max only supports integral types." );

        return (t)_mm_cvtss_f32( 
            _mm_max_ss( _mm_set_ss( (float)a ), 
            _mm_set_ss( (float)b ) ) 
        );
    }
    
    // sse clamp.
    template< typename t = float > __forceinline void clamp( t &val, const t &min, const t &max ) {
        // check type.
        static_assert( std::is_arithmetic< t >::value, "Math::clamp only supports integral types." );
    
        val = (t)_mm_cvtss_f32( 
            _mm_min_ss( _mm_max_ss( _mm_set_ss( (float)val ), _mm_set_ss( (float)min ) ), 
            _mm_set_ss( (float)max ) ) 
        );
    }
    
    // sse sqrt.
    template< typename t = float > __forceinline t sqrt( const t &val ) {
        // check type.
        static_assert( std::is_arithmetic< t >::value, "Math::sqrt only supports integral types." );
    
        return _mm_cvtss_f32( _mm_sqrt_ss( _mm_set_ss( (float)val ) ) );
    }

    // todo - dex; add other math funcs here for vectors / etc, if linker errors occur we will need a math.cpp.
	__forceinline Vec3_t vector_transform( Vec3_t vector, matrix3x4_t matrix ) {
		return Vec3_t( vector.dot( matrix[ 0 ] ) + matrix[ 0 ][ 3 ], vector.dot( matrix[ 1 ] ) + matrix[ 1 ][ 3 ],
		               vector.dot( matrix[ 2 ] ) + matrix[ 2 ][ 3 ] );
	}

	__forceinline float dot_product( const Vec3_t &a, const Vec3_t &b ) {
		return a.x * b.x + a.y * b.y + a.z * b.z;
	}

	__forceinline float dot_product( const Vec3_t &a, const float *b ) {
		return a.x * b[ 0 ] + a.y * b[ 1 ] + a.z * b[ 2 ];
	}

	__forceinline void matrix_position( const matrix3x4_t &matrix, Vec3_t &out ) {
		out.x = matrix.m_mat_val[ 0 ][ 3 ];
		out.y = matrix.m_mat_val[ 1 ][ 3 ];
		out.z = matrix.m_mat_val[ 2 ][ 3 ];
	}

	__forceinline void angle_to_vector( const Vec3_t &angles, Vec3_t &forward ) {
		float sp, sy, cp, cy;

		sin_to_cos( deg_to_rad( angles.y ), sy, cy );
		sin_to_cos( deg_to_rad( angles.x ), sp, cp );

		forward.x = cp * cy;
		forward.y = cp * sy;
		forward.z = -sp;
	}

	__forceinline void angle_to_vectors( const Vec3_t &angles, Vec3_t *forward, Vec3_t *right, Vec3_t *up ) {
		float sr, sp, sy, cr, cp, cy;

		sin_to_cos( deg_to_rad( angles.y ), sy, cy );
		sin_to_cos( deg_to_rad( angles.x ), sp, cp );
		sin_to_cos( deg_to_rad( angles.z ), sr, cr );

		if( forward ) {
			forward->x = cp * cy;
			forward->y = cp * sy;
			forward->z = -sp;
		}

		if( right ) {
			right->x = -1.0f * sr * sp * cy + -1.0f * cr * -sy;
			right->y = -1.0f * sr * sp * sy + -1.0f * cr * cy;
			right->z = -1.0f * sr * cp;
		}

		if( up ) {
			up->x = cr * sp * cy + -sr * -sy;
			up->y = cr * sp * sy + -sr * cy;
			up->z = cr * cp;
		}
	}

	__forceinline Vec3_t cross_product(const Vec3_t &a, const Vec3_t &b ) {
		return Vec3_t( a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x );
	}

	__forceinline Vec3_t cross_product( const Vec3_t &a, const Vec3_t &b, Vec3_t &out ) {
		return Vec3_t( out.x = a.y * b.z - a.z * b.y, out.y = a.z * b.x - a.x * b.z, out.z = a.x * b.y - a.y * b.x );
	}

	__forceinline float normalize_vector( Vec3_t &v ) {
		float l = v.length();
		if( l != 0.0f )
			v /= l;
		else
			v.x = v.y = 0.0f; v.z = 1.0f;

		return l;
	}
}