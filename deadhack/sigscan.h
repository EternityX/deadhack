#pragma once

namespace SigScan {
    // wraps a uint8_t and has a bool if the byte should be ignored.
    class PatternByte_t {
    private:
        uint8_t m_byte;
        bool    m_is_wildcard;
    
    public:
        __forceinline PatternByte_t() : m_byte{ 0 }, m_is_wildcard{ true } {
            
        }

        __forceinline PatternByte_t( uint8_t byte, bool is_wildcard ) : m_byte{ byte }, m_is_wildcard{ is_wildcard } {
            
        }

        __forceinline uint8_t get_byte() const {
            return m_byte;
        }

        __forceinline bool is_wildcard() const {
            return m_is_wildcard;
        }

        __forceinline bool match( const uint8_t other ) const {
            return m_byte == other || m_is_wildcard;
        }
    };

    // converts a string into a pattern.
    class Pattern {
    private:
        // pattern types.
        using pattern_t       = std::vector< PatternByte_t >;
        using pattern_citer_t = pattern_t::const_iterator;

        // actual pattern.
        pattern_t m_pattern;

    public:
        __forceinline Pattern() : m_pattern{} {
        
        }

        __forceinline Pattern( const std::string &str ) : m_pattern{} {
            std::string part;

            if( str.empty() )
                return;

            // setup string stream.
            auto ss = std::stringstream( str );

            // iterate string stream, splitting by space delim.
            do {
                //// too long...
                //if( part.size() > 2 )
                //    continue;

                // it's a wildcard.
                if( part[ 0 ] == '?' )
                    m_pattern.push_back( {} );

                // valid byte.
                else if( std::isxdigit( (uint8_t)part[ 0 ] ) && std::isxdigit( (uint8_t)part[ 1 ] ) )
                    m_pattern.push_back( { (uint8_t)std::strtoul( part.c_str(), 0, 16 ), false } );
            }
            while( ss >> part );
        }

        // access pattern.
        __forceinline const PatternByte_t &operator []( size_t index ) const {
            if( index > m_pattern.size() )
                return {};

            return m_pattern[ index ];
        }

        // begin / end of pattern.
        __forceinline pattern_citer_t begin() const {
            return m_pattern.cbegin();
        }

        __forceinline pattern_citer_t end() const {
            return m_pattern.cend();
        }
    };

    // todo - dex; add a find_all method that returns a vector?

    __forceinline uintptr_t find( uintptr_t start, size_t len, const std::string &pattern ) {
        uint8_t *scan_start, *scan_end;
        Pattern scan_pattern;

        static auto search_pred = []( const uint8_t a, const PatternByte_t &b ) {
            return b.match( a );
        };

        if( !start || !len || pattern.empty() )
            return 0;

        // set up scan start / end.
        scan_start  = (uint8_t *)start;
        scan_end    = scan_start + len;

        // set up pattern.
        scan_pattern = pattern;

        auto it = std::search(
            scan_start,
            scan_end,
            scan_pattern.begin(),
            scan_pattern.end(),
            search_pred
        );

        // nothing found...
        if( it == scan_end )
            return 0;
    
        return (uintptr_t)it;
    }
    
    __forceinline uintptr_t find( const PE::Module &module, const std::string &pattern ) {
        return find( module.get_code_size(), pattern );
    }
}