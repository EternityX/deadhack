#pragma once

#pragma warning( disable : 4307 ) // warning C4307: '*': integral constant overflow

// note - dex; undefine this when distributing!!
#define CHEAT_DBG

#define WIN32_LEAN_AND_MEAN
#define NOCOMM

// custom types / etc.
using ulong_t = unsigned long;

// windows / stl.
#include <Windows.h>
#include <intrin.h>
#include <cstdint>
#include <string>
#include <array>
#include <vector>
#include <memory>
#include <sstream>
#include <cctype>
#include <random>

#ifdef CHEAT_DBG
    #define DBG_ERROR( str )                                                                                                    \
        MessageBoxA(                                                                                                            \
            nullptr,                                                                                                            \
            ( std::string( str ) + " (" + std::string( __FILE__ ) + " @ line " + std::to_string( __LINE__ ) + ")" ).c_str(),    \
            "DBG_ERROR",                                                                                                        \
            0                                                                                                                   \
        );
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
#include "interfaces.h"
#include "csgo.h"
#include "hooks.h"