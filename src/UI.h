#pragma once
#include "Math/vec.h"

namespace UI
{

    enum Origin
    {
        TopLeft = 0,
        TopRight = 1,
        BottomLeft = 2,
        BottomRight = 3,
        Centered = 4
    };
    struct TextNode
    {
        std::string string = "Empty";
        vec2 offset = vec2(5,0);
        vec2 scale = vec2(0.25,0.25);
    };
    class Button
    { 
    public:
        vec2 position =     vec2(0,0);
        vec2 size =         vec2(100,100);

        vec4 color =        vec4(1,1,1,0.1f);
        Origin origin =     UI::TopLeft;

        
        float corner_radius =    0.05f;
        float outline_thickness = 0.05f; 
        UI::TextNode text;
        bool on_hover(vec2 mouse, vec2 res) const;
    };

inline bool UI::Button::on_hover(vec2 mouse, vec2 res) const
{
    return (mouse.x < position.x + size.x && mouse.y > position.y - size.y
            && mouse.x > position.x && mouse.y < position.y);
}
    


};

