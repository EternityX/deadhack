#pragma once

class IVModelInfo {
public:
	const model_t *GetModel( int modelindex ) {
		return Utils::get_method< model_t *( __thiscall *)( decltype( this ), int )>( this, 1 )( this, modelindex );
	}

	const char *GetModelName( const model_t *model ) {
		return Utils::get_method< const char *( __thiscall *)( decltype( this ), const model_t * )>( this, 3 )( this, model );
	}

	studiohdr_t *GetStudioModel( const model_t *model ) {
		return Utils::get_method< studiohdr_t *( __thiscall *)( decltype( this ), const model_t * )>( this, 30 )( this, model );
	}
};