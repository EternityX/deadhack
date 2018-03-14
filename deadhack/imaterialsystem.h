#pragma once
#include "imatrendercontext.h"

class IMaterialSystem {
public:
	const char *GetName() {
		return Utils::get_method< const char *( __thiscall *)( decltype( this ) )>( this, 0 )( this );
	}

	IMaterial *CreateMaterial( const char *material_name, KeyValues *key_values ) {
		return Utils::get_method< IMaterial *( __thiscall *)( decltype( this ), const char *, KeyValues * )>( this, 83 )( this, material_name, key_values );
	}

	IMaterial *GetMaterial( const char *material_name, const char *texture_group_name, bool complain = true, const char *complain_prefix = nullptr ) {
		return Utils::get_method< IMaterial *( __thiscall * )( decltype( this ), const char *, const char *, bool, const char * )>( this, 84 )( this, material_name, texture_group_name, complain, complain_prefix );
	}

	int FirstMaterial() {
		return Utils::get_method< int( __thiscall *)( decltype( this ) )>( this, 86 )( this );
	}

	int NextMaterial( int handle ) {
		return Utils::get_method< int( __thiscall *)( decltype( this ), int )>( this, 87 )( this, handle );
	}

	int InvalidMaterial() {
		return Utils::get_method< int( __thiscall *)( decltype( this ) )>( this, 88 )( this );
	}

	IMaterial *FindMaterial( int handle ) {
		return Utils::get_method< IMaterial *( __thiscall *)( decltype( this ), int )>( this, 89 )( this, handle );
	}

	ITexture *FindTexture( char const *pTextureName, const char *pTextureGroupName, bool complain = true ) {
		return Utils::get_method< ITexture *( __thiscall *)( decltype( this ), char const *, const char *, bool )>( this, 91 )( this, pTextureName, pTextureGroupName, complain );
	}

	IMatRenderContext *GetRenderContext() {
		return Utils::get_method< IMatRenderContext *( __thiscall *)( decltype( this ) )>( this, 115 )( this );
	}
};
