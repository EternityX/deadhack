#pragma once

class IMaterial {
public:
	const char *GetName() {
		return Utils::get_method< const char *( __thiscall *)( decltype( this ) )>( this, 0 )( this );
	}

	const char *GetTextureGroupName() {
		return Utils::get_method< const char *( __thiscall *)( decltype( this ) )>( this, 1 )( this );
	}

	void AddReference() {
		Utils::get_method< void( __thiscall *)( decltype( this ) )>( this, 12 )( this );
	}

	void IncrementReferenceCount() {
		Utils::get_method< void( __thiscall *)( decltype( this ) )>( this, 14 )( this );
	}

	void SetAlpha( float alpha ) {
		Utils::get_method< void( __thiscall *)( decltype( this ), float )>( this, 27 )( this, alpha );
	}

	void SetColor( float r, float g, float b ) {
		Utils::get_method< void( __thiscall *)( decltype( this ), float, float, float )>( this, 28 )( this, r, g, b );
	}

	void SetVarFlag( int flag, bool setting ) {
		Utils::get_method< void( __thiscall *)( decltype( this ), int, bool )>( this, 29 )( this, flag, setting );
	}

	bool IsErrorMaterial() {
		return Utils::get_method< bool( __thiscall *)( decltype( this ) )>( this, 42 )( this );
	}

	float GetAlphaModulation() {
		return Utils::get_method< float( __thiscall *)( decltype( this ) )>( this, 44 )( this );
	}

	void GetColorModulation( float* r, float* g, float* b ) {
		Utils::get_method< void( __thiscall *)( decltype( this ), float *, float *, float * )>( this, 45 )( this, r, g, b );
	}
};