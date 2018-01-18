#pragma once

class ConVar {
public:
	void SetValue( int value ) {
		Utils::get_method< void(__thiscall *)( decltype( this ), int )>( this, 16 )( this, value );
	}
};

class ICVar {
public:
	ConVar *FindVar( const char *var ) {
		return Utils::get_method< ConVar *(__thiscall *)( decltype( this ), const char * )>( this, 15 )( this, var );
	}
};