#pragma once

namespace PE {
    // get DOS / NT headers.
    static bool get_file_headers( uintptr_t base, PIMAGE_DOS_HEADER &out_dos, PIMAGE_NT_HEADERS &out_nt ) {
        // get DOS header and check for invalid DOS / DOS signature.
        auto dos = (IMAGE_DOS_HEADER *)base;
        if( !dos || dos->e_magic != IMAGE_DOS_SIGNATURE /* "MZ" */ )
            return false;
        
        // get NT headers and check for invalid NT / NT signature.
        auto nt = (IMAGE_NT_HEADERS *)( (uintptr_t)dos + dos->e_lfanew );
        if( !nt || nt->Signature != IMAGE_NT_SIGNATURE /* "PE\0\0" */ )
            return false;

        out_dos = dos;
        out_nt  = nt;
        
        return true;
    }

    class Module {
    private:
        Types::LDR_DATA_TABLE_ENTRY *m_ldr_entry;
        IMAGE_DOS_HEADER            *m_dos;
        IMAGE_NT_HEADERS            *m_nt;
        uintptr_t                   m_base;
        std::wstring                m_pathW;

    public:
        __forceinline Module() : m_ldr_entry{ nullptr }, m_dos{ nullptr }, m_nt{ nullptr }, m_base{ 0 }, m_pathW{} {
        
        }

        //__forceinline Module( uintptr_t base_address ) : m_dos{ nullptr }, m_nt{ nullptr }, m_base{ 0 }, m_name{} {
        //    init( base_address );
        //}
        //
        //__forceinline Module( uintptr_t base_address, const std::string &name = "" ) : m_dos{ nullptr }, m_nt{ nullptr }, m_base{ 0 }, m_name{} {
        //    init( base_address, name );
        //}

        __forceinline bool init( Types::LDR_DATA_TABLE_ENTRY *ldr_entry ) {
            uintptr_t        base;
            IMAGE_DOS_HEADER *dos;
            IMAGE_NT_HEADERS *nt;

            if( !ldr_entry )
                return false;

            base = ldr_entry->DllBase;

            if( !get_file_headers( base, dos, nt ) )
                return false;

            m_ldr_entry = ldr_entry;
            m_dos       = dos;
            m_nt        = nt;
            m_base      = base;
            m_pathW     = ldr_entry->FullDllName.Buffer;

            std::transform( m_pathW.begin(), m_pathW.end(), m_pathW.begin(), std::tolower );

            return true;
        }

        // returns module base address.
        __forceinline uintptr_t get_base() const {
            return m_base;
        }

        __forceinline operator uintptr_t() const {
            return m_base;
        }

        // valid checks.
        __forceinline operator bool() const {
            return get_base();
        }

        __forceinline bool operator !() const {
            return !get_base();
        }

        __forceinline IMAGE_DOS_HEADER *get_dos_header() const {
            return ( m_dos ) ? m_dos : nullptr;
        }

        __forceinline IMAGE_NT_HEADERS *get_nt_headers() const {
            return ( m_nt ) ? m_nt : nullptr;
        }

        __forceinline size_t get_code_size() const {
            return ( m_nt ) ? m_nt->OptionalHeader.SizeOfCode : 0;
        }

        __forceinline size_t get_image_size() const  {
            return ( m_nt ) ? m_nt->OptionalHeader.SizeOfImage : 0;
        }

        template< typename t = uintptr_t > __forceinline t RVA( size_t offset ) const {
            if( !m_base || !offset )
                return t{};

            return (t)( m_base + offset );
        }
        
        // returns data directory entry from OptionalHeader->DataDirectory array.
        __forceinline IMAGE_DATA_DIRECTORY *get_data_dir_entry( size_t entry ) const {
            if( !m_nt || entry > IMAGE_NUMBEROF_DIRECTORY_ENTRIES )
                return nullptr;

            return &m_nt->OptionalHeader.DataDirectory[ entry ];
        }

        // returns actual data directory in memory.
        template< typename t > __forceinline t *get_data_dir( size_t entry ) const {
            auto data_dir = get_data_dir_entry( entry );
            if( !data_dir || !data_dir->VirtualAddress )
                return nullptr;

            return RVA< t * >( data_dir->VirtualAddress );
        }

        __forceinline std::wstring get_pathW() const {
            return m_pathW;
        }

        __forceinline std::string get_pathA() const {
            return Utils::wide_to_multibyte( get_pathW() );
        }

        __forceinline std::wstring get_module_nameW() const {
            std::wstring out;
            size_t       delim;

            out = m_pathW;

            delim = out.find_last_of( '\\' );
            if( delim == std::wstring::npos )
                return {};

            // keep only name + extension.
            return out.substr( delim + 1 );
        }

        __forceinline std::string get_module_nameA() const {
            return Utils::wide_to_multibyte( get_module_nameW() );
        }
    };
}