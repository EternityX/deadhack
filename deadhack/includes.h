#pragma once

#pragma warning( disable : 4307 ) // warning C4307: '*': integral constant overflow

// note - dex; undefine this when distributing!!
#define CHEAT_DBG

#define WIN32_LEAN_AND_MEAN
#define NOCOMM
#define NOMINMAX

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
#include <thread>

#ifdef CHEAT_DBG
    // todo - dex; this is pretty silly for debugging, we should really implement a proper testing function here or something so we can debug issues from users.

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
#include "pe_types.h"
#include "utils.h"
#include "module.h"
#include "pe.h"
#include "sigscan.h"
#include "vmthook.h"
#include "input.h"
#include "math.h"
#include "vec2.h"
#include "vec3.h"
#include "angle.h"

// direct3d9.
#include <d3d9.h>
#pragma comment( lib, "d3d9.lib" )
#pragma comment( lib, "D3dx9.lib" )

// OSHGUI.
#include "OSHGui.hpp"
#include "Input/WindowsMessage.hpp"
#include "Drawing/Direct3D9/Direct3D9Renderer.hpp"
#include "renderer.h"
#include "forms.h"

#pragma comment( lib, "oshgui.lib" )

// using namespace OSHGui;
// using namespace OSHGui::Drawing;

// cheat stuff.
#include "interfaces.h"
#include "sdk.h"
#include "csgo.h"
#include "hooks.h"