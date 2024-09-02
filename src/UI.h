#pragma once
#include "Math/vec.h"

namespace ui
{
    class uiNode;

    enum Origin
    {
        TopLeft = 0,
        TopRight = 1,
        BottomLeft = 2,
        BottomRight = 3,
        Centered = 4
    };

    //Everything is natually Centered around sf::Origin::Centered.
    //This Function simply converts the position with the givin origin setting.
    vec2 convert_origin(const uiNode& node, Origin origin);    


    class uiNode 
    {
    public:
        uiNode
        (
            uiNode* parent      = nullptr,
            const vec2& position = vec2(0,0),
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
            const vec2& size = vec2(100,100), 
            const vec4& color = vec4(1, 1, 1, 1)
        );
        std::string string;
        vec4 color;
    };



    class PanelNode : public uiNode
    {
    public:
        PanelNode(const vec2& position = vec2(0,0), uiNode* parent = nullptr);
        float corner_radius =    0.05f;
        float outline_thickness = 0.025f;  
        vec4 color =        vec4(1,1,1,0.1f); 
        bool on_hover(vec2 mouse);
    };

    class ButtonNode : public PanelNode
    {
    private:
        bool is_pressed = 0;
    public:
        vec4 button_color = vec4(1,1,1,0.1f); 
        bool on_press(vec2 mouse, bool press, bool release);
    };


    

};




    



