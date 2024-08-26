#pragma once
#include "Mesh.hpp"
#include "Math/vec.h"
#include <array>
#include <iostream>


class CustomText
{
    struct Vertex
    {
        vec2 position;     
        vec2 uv;
    };



    static const sf::Uint32 Start = '!';
    static const sf::Uint32 End = '~';
    static const sf::Uint32 Letter_count = End - Start + 1;
private:
    Mesh mesh;
    unsigned int font_size;
    sf::Texture font_bitmap;
    std::array<Vertex, Letter_count> mesh_info;
public:
    CustomText();
    void set_font(sf::Font& font, unsigned int font_size = 64);
    void draw();
    
};