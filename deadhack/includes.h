#pragma once

#pragma warning( disable : 4307 ) // warning C4307: '*': integral constant overflow

#define WIN32_LEAN_AND_MEAN
#define NOCOMM

// note - dex; undefine this when distributing!!
#define CHEAT_DBG

// custom types / etc.
using ulong_t = unsigned long;

// windows / stl.
#include <Windows.h>
#include <intrin.h>
#include <cstdint>
#include <string>
#include <array>
#include <vector>
#include <iostream>
#include <ShlObj.h> // needed for SHGetKnownFolderPath()
#include <filesystem>
#include <sstream>
#include <cctype>
#include <random>

#ifdef CHEAT_DBG
#include <assert.h>
    #define DBG_ASSERT( str ) \
        MessageBoxA( nullptr, "DBG_ASSERT", ( std::string( str ) + "( " + std::string( __FILE__ ) + " @ line " + std::string( __FILE__ ) ).c_str(), 0 );
#endif

// other stuff.
#include "hash.h"
#include "utils.h"
#include "pe_types.h"
#include "module.h"
#include "pe.h"
#include "sigscan.h"
#include "vmthook.h"
#include "input.h"

// direct3d9.
#include <d3d9.h>

// cheat stuff.
#include "hooks.h"