#pragma once

class IVRenderView {
public:
	void SetBlend( float blend ) {
		Utils::get_method< void( __thiscall *)( decltype( this ), float )>( this, 4 )( this, blend );
	}

	float GetBlend() {
		return Utils::get_method< float( __thiscall *)( decltype( this ) )>( this, 5 )( this );
	}

	void SetColorModulation( const float *blend ) {
		Utils::get_method< void( __thiscall *)( decltype( this ), const float * )>( this, 6 )( this, blend );
	}

	void GetColorModulation( float *blend ) {
		Utils::get_method< void( __thiscall *)( decltype( this ), float * )>( this, 7 )( this, blend );
	}
};