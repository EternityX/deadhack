#pragma once

#pragma warning( disable : 4307 ) // warning C4307: '*': integral constant overflow
#pragma warning( disable : 4244 ) // warning C4244: '=': conversion possible loss of data

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
#include <stdio.h>
#include <array>
#include <vector>
#include <map>
#include <memory>
#include <sstream>
#include <fstream>
#include <iostream>
#include <iomanip>
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

// OSHGUI.
#include "OSHGui.hpp"
#include "Input/WindowsMessage.hpp"
#include "Drawing/Direct3D9/Direct3D9Renderer.hpp"
#include "Drawing/RenderTarget.hpp"

#include "ThemidaSDK.h"

// other stuff.
#include "hash.h"
#include "cfg_manager.h"
#include "config.h"
#include "pe_types.h"
#include "utils.h"
#include "module.h"
#include "pe.h"
#include "sigscan.h"
#include "vmthook.h"
#include "vec2.h"
#include "vec3.h"
#include "angle.h"
#include "matrix.h"
#include "math.h"
#include "cvar.h"
#include "color.h"

// direct3d9.
#include <d3d9.h>
#pragma comment( lib, "d3d9.lib" )
#pragma comment( lib, "D3dx9.lib" )

// OSHGUI.
#include "custom_renderer.h"
#include "menu.h"

#pragma comment( lib, "oshgui.lib" )

#include "input.h"

// cheat stuff.
#include "interfaces.h"
#include "sdk.h"
#include "csgo.h"

#include "netvars.h"
#include "offsets.h"

#include "csgo_util.h"

// structs.
#include "cbaseentity.h"
#include "cbasecombatweapon.h"
#include "ccsplayer.h"

#include "lagcomp.h"

#include "client.h"

#include "hooks.h"

#include "visuals.h"
#include "legitbot.h"
#include "misc.h"