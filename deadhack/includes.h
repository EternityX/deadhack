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

// utils / other stuff.
#include "hash.h"

// cheat stuff.