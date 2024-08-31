#pragma once
#include "Math/vec.h"



//a namespace containing all the vertex shader uniform memory layouts
namespace Uniform
{
    struct shadertoy_bg
    {
        //fragment shader variables
        vec2 iresolution;
        vec2 imouse;
        float itime;
        float ifrequency; 
    };
    struct shader_ui
    {
        vec2 iResolution;
        float iTime;
        float iFrequency;
        vec2 position;
        vec2 size;
        vec4 iColor;
        float CornerRadius;
        float OutlineThickness;
    };
};
