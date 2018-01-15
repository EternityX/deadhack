#pragma once

class IClientEntityList {
public:
	IClientEntity* GetClientEntity( int entNum ) {
		return Utils::get_method< IClientEntity *(__thiscall *)( decltype( this ), int )>( this, 3 )( this, entNum );
	}
	int GetHighestEntityIndex() {
		return Utils::get_method< int(__thiscall *)( decltype( this ) )>( this, 6 )( this );
	}
};