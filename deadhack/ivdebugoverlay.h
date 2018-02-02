#pragma once

class IVDebugOverlay {
public:
	int GetScreenPosition( const Vec3_t &point, Vec3_t &screen ) {
		return Utils::get_method< int(__thiscall *)( decltype( this ), const Vec3_t &, Vec3_t & )>( this, 13 )( this, point, screen );
	}
};