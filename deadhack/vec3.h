#pragma once

class Vec3_t {
public:
    float x, y, z;

    __forceinline Vec3_t() : x{ 0.f }, y{ 0.f }, z{ 0.f } {
    
    }

    __forceinline Vec3_t( float x, float y, float z ) : x{ x }, y{ y }, z{ z } {
    
    }
};