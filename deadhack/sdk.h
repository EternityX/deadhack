#pragma once

#ifndef CONCAT_IMPL
#define CONCAT_IMPL(x, y) x##y
#ifndef MACRO_CONCAT
#define MACRO_CONCAT(x, y) CONCAT_IMPL(x, y)
#ifndef PAD
#define PAD(SIZE) BYTE MACRO_CONCAT(_pad, __COUNTER__)[SIZE];
#endif
#endif
#endif

#include "dt_recv.h"
#include "client_class.h"

#include "def.h"

#include "clientdll.h"
#include "iclientmodeshared.h"
#include "icliententity.h"
#include "icliententitylist.h"
#include "ivmodelinfo.h"
#include "iclientrenderable.h"
#include "cinput.h"
#include "icvar.h"
#include "cglobalvars.h"
#include "chandle.h"
#include "imaterial.h"
#include "imaterialsystem.h"
#include "ivrenderview.h"
#include "ivmodelrender.h"
#include "isurface.h"
#include "ivdebugoverlay.h"
#include "ipanel.h"