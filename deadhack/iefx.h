#pragma once

enum DlightFlags {
	DLIGHT_NO_WORLD_ILLUMINATION = 0x1,
	DLIGHT_NO_MODEL_ILLUMINATION = 0x2,
	DLIGHT_ADD_DISPLACEMENT_ALPHA = 0x4,
	DLIGHT_SUBTRACT_DISPLACEMENT_ALPHA = 0x8,
	DLIGHT_DISPLACEMENT_MASK = ( DLIGHT_ADD_DISPLACEMENT_ALPHA | DLIGHT_SUBTRACT_DISPLACEMENT_ALPHA ),
};

struct ColorRGBExp32 {
	unsigned char r, g, b;
	signed char exponent;
};

struct dlight_t
{
	int flags;
	Vec3_t origin;
	float radius;
	ColorRGBExp32 color;
	float die;
	float decay;
	float minlight;
	int	key;
	int style;
	Vec3_t direction;
	float innerAngle;
	float outerAngle;
};

class IVEfx {
public:
	dlight_t *CL_AllocDlight( int key )
	{
		using original_fn = dlight_t *( __thiscall * )( void *, int );
		return Utils::get_method<original_fn>( this, 4 )( this, key );
	}

	dlight_t *CL_AllocElight( int key )
	{
		using original_fn = dlight_t *( __thiscall * )( void *, int );
		return Utils::get_method<original_fn>( this, 5 )( this, key );
	}

	dlight_t *GetElightByKey( int key )
	{
		using original_fn = dlight_t *( __thiscall * )( void *, int );
		return Utils::get_method<original_fn>( this, 8 )( this, key );
	}
};
