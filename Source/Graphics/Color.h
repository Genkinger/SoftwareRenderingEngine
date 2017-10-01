//
// Created by genkinger on 9/28/17.
//

#ifndef ENGINE_COLOR_H
#define ENGINE_COLOR_H

#include "../Common.h"

#define AMASK (255 << 24)
#define RMASK (255 << 16)
#define GMASK (255 << 8)
#define BMASK (255)

using namespace M3D;

typedef unsigned char byte;
typedef unsigned int uint;

inline uint rgba(byte r, byte g, byte b, byte a){
    return ((a << 24) | (r << 16) | (g << 8) | (b) );
}
inline uint rgb(byte r, byte g, byte b){
    return static_cast<uint>(((255 << 24) | (r << 16) | (g << 8) | (b) ));
}
inline uint rgba_float(float r, float g, float b, float a){

    auto rr = static_cast<byte>(Map(r,0,1,0,255));
    auto gg = static_cast<byte>(Map(g,0,1,0,255));
    auto bb = static_cast<byte>(Map(b,0,1,0,255));
    auto aa = static_cast<byte>(Map(a,0,1,0,255));

    return rgba(rr,gg,bb,aa);
}
inline uint rgb_float(float r, float g, float b){

    auto rr = static_cast<byte>(Map(r,0,1,0,255));
    auto gg = static_cast<byte>(Map(g,0,1,0,255));
    auto bb = static_cast<byte>(Map(b,0,1,0,255));

    return rgb(rr,gg,bb);
}

 inline Vec4f unpack_color(uint color) {
    auto a = static_cast<uint>((color & AMASK) >> 24) ;
    auto r = static_cast<uint>((color & RMASK) >> 16);
    auto g = static_cast<uint>((color & GMASK) >> 8);
    auto b = static_cast<uint>((color & BMASK));

     return Vec4f{Map(static_cast<float>(r),0,255,0,1),
                  Map(static_cast<float>(g),0,255,0,1),
                  Map(static_cast<float>(b),0,255,0,1),
                  Map(static_cast<float>(a),0,255,0,1)
     };
}

/*
{
    byte a = (byte)(color & AMASK);// >> 24;
    byte r = (byte)(color & RMASK);// >> 16;
    byte g = (byte)(color & GMASK);// >> 8;
    byte b = (byte)(color & BMASK);

    return vec4f(m3d_map(r,0,255,0,1),m3d_map(g,0,255,0,1),m3d_map(b,0,255,0,1),m3d_map(a,0,255,0,1));
}
 */

#endif //ENGINE_COLOR_H
