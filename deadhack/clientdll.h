#pragma once

class CHLClient {
public:
	__forceinline ClientClass *GetAllClasses() {
		return Utils::get_method< ClientClass *(__thiscall *)( decltype( this ) )>( this, 8 )( this );
	}
};