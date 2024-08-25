#pragma once
#include "Math/vec.h"


struct ShaderToy_bg
{
    //Fragment shader variables
    vec2 iResolution;
    vec2 iMouse;
    float iTime;
    float iFrequency; 
    ShaderToy_bg() : iResolution(0,0), 
    iMouse(0,0), iTime(0), iFrequency(0) {}
};

struct ShaderToy_ui : public ShaderToy_bg
{
    //Quad position and size
    vec2 position; 
    float width;
    float height;

    //Fragment shader variables
    ShaderToy_ui() :ShaderToy_bg(), position(0,0), width(1), height(1){}
};

struct ShaderToy_m : public ShaderToy_ui{};