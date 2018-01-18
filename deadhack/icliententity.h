#pragma once

#include "IClientUnknown.h"
#include "IClientRenderable.h"
#include "IClientNetworkable.h"

class IClientEntity : public IClientUnknown, public IClientRenderable, public IClientNetworkable {
public:
	Vec3_t &GetAbsOrigin() {
		return Utils::get_method< Vec3_t &(__thiscall *)( decltype( this ) )>( this, 10 )( this );
	}
};