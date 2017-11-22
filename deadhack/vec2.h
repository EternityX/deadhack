#pragma once

class Vec2_t {
public:
    float x, y;

    __forceinline Vec2_t() : x{ 0.f }, y{ 0.f } {
    
    }

    __forceinline Vec2_t( float x, float y ) : x{ x }, y{ y } {
    
    }
};