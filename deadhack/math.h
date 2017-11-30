#pragma once

class vec2_t;
class vec3_t;

namespace Math {
    // pi constants.
    constexpr float pi{ 3.141592654f };
    constexpr float pi_2{ pi * 2.f };
    constexpr float pi_1divpi{ 1.f / pi };
    constexpr float pi_1div2pi{ 1.f / pi_2 };
    constexpr float pi_div2{ pi / 2.f };
    constexpr float pi_div4{ pi / 4.f };

    // degrees to radians.
    __forceinline constexpr float deg_to_rad( float val ) {
        return val * ( pi / 180.f );
    }
    
    // radians to degrees.
    __forceinline constexpr float rad_to_deg( float val ) {
        return val * ( 180.f / pi );
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
}