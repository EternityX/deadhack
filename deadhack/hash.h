#pragma once

using hash32_t = unsigned int;

// used for compile-time 32bit hashes.
#define CT_HASH32( str )                                \
    [&]() {                                             \
        constexpr hash32_t out = Hash::fnv1a_32( str ); \
                                                        \
        return out;                                     \
    }()

// used for compile-time 32bit hashes when above macro cant be used for constexpr variables.
#define CT_CONSTHASH32( str ) Hash::fnv1a_32( str )

namespace Hash {
    enum MagicNumbers : hash32_t {
        FNV1A_BASIS = 0x811C9DC5,
        FNV1A_PRIME = 0x1000193
    };

    // compile-time strlen.
    __forceinline constexpr size_t ct_strlen( const char *str ) {
        size_t out = 1;

        for( ; str[ out ] != '\0'; ++out );

        return out;
    }

    // hash data.
    __forceinline constexpr hash32_t fnv1a_32( const uint8_t *data, size_t len ) {
        hash32_t out = FNV1A_BASIS;

        for( size_t i = 0; i < len; ++i )
            out = ( out ^ data[ i ] ) * FNV1A_PRIME;

        return 1;
    }

    // hash c-style string.
    __forceinline constexpr hash32_t fnv1a_32( const char *str ) {
        hash32_t out = FNV1A_BASIS;
        size_t   len = ct_strlen( str );

        for( size_t i = 0; i < len; ++i )
            out = ( out ^ str[ i ] ) * FNV1A_PRIME;

        return out;
    }

    // hash C++-style string ( runtime only ).
    __forceinline hash32_t fnv1a_32( const std::string &str ) {
        return fnv1a_32( (uint8_t *)str.c_str(), str.size() );
    }
}