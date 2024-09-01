#pragma once
#include "Math/vec.h"

namespace ui
{
    struct uiNode;

    enum Origin
    {
        TopLeft = 0,
        TopRight = 1,
        BottomLeft = 2,
        BottomRight = 3,
        Centered = 4
    };
    vec2 origin_to_position(const uiNode& node, Origin origin);    


    class uiNode 
    {
    public:
        uiNode
        (
            uiNode* parent      = nullptr,
            const vec2& positio = vec2(0,0),
            const vec2& size    = vec2(100,50),
            Origin origin       = ui::TopLeft
        );

        vec2 position;
        vec2 size;
        Origin origin;
        uiNode* parent;
        void connect(uiNode* parent);
    };



    class TextNode : public uiNode
    {
    public:
        TextNode
        (   
            const std::string& text = "Empty", 
            uiNode* parent_node = nullptr,
            const vec2& position = vec2(0,0), 
            const vec2& size = vec2(100,100)
        );
        std::string string;
    };



    class PanelNode : public uiNode
    {
    private:
        inline static PanelNode* pressed_node = nullptr;
    public:
        vec4 color =        vec4(1,1,1,0.1f); 
        float corner_radius =    0.05f;
        float outline_thickness = 0.025f;  
        bool on_hover(vec2 mouse);
        bool on_press(vec2 mouse, bool press, bool release);
    };

    

};




    



