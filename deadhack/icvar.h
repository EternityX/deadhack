#pragma once

class ConVar {
public:
	float GetFloat() {
		return Utils::get_method< float(__thiscall *)( decltype( this ) )>( this, 12 )( this );
	}

	float GetInt() {
		return Utils::get_method< int(__thiscall *)( decltype( this ) )>( this, 13 )( this );
	}

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
