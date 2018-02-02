#pragma once

class IVModelRender {
public:
	void SetForcedMaterialOverride( IMaterial* material, OverrideType type = OVERRIDE_NORMAL, int unknown = 0 ) {
		return Utils::get_method< void( __thiscall *)( decltype( this ), IMaterial *, OverrideType, int )>( this, 1 )( this, material, type, unknown );
	}
};