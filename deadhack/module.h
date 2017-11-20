#pragma once

namespace PE {
    class Module {
    private:
        uintptr_t m_base;

    public:
        __forceinline Module() : m_base{ 0 } {
        
        }

        __forceinline Module( uintptr_t base_address ) : m_base{ 0 } {
            init( base_address );
        }

        __forceinline bool init( uintptr_t base_address ) {
            if( !base_address )
                return false;

            // todo - dex;  finish this...
            //              add func for getting file headers

            m_base = base_address;

            return true;
        }

        __forceinline size_t get_code_size() const {
            return 0;
        }

        __forceinline size_t get_image_size() const  {
            return 0;
        }
    };
}