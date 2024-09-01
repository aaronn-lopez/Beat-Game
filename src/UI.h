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


    struct uiNode
    {
        vec2 position = vec2(0, 0);
        vec2 size = vec2(100,50);
        Origin origin = ui::TopLeft;
        uiNode* parent = nullptr;
        void connect(uiNode* parent);
    };



    struct TextNode : public uiNode
    {
        std::string string = "Empty";
    };



    struct PanelNode : public uiNode
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




inline vec2 ui::origin_to_position(const ui::uiNode& node, Origin origin)
{
    switch(node.origin)
    {
        case ui::Origin::TopLeft:
            return node.position + vec2(node.size.x, -node.size.y)/2;
        case ui::Origin::TopRight:
            return node.position - node.size/2;
        case ui::Origin::BottomLeft:
            return node.position + node.size/2;
        case ui::Origin::BottomRight:
            return node.position + vec2(-node.size.x, node.size.y)/2;
        case ui::Origin::Centered:
            return node.position;
    }
}
inline void ui::uiNode::connect(ui::uiNode* parent)
{
    this->parent = parent;
}

//PanelNode
inline bool ui::PanelNode::on_hover(vec2 mouse)
{
    vec2 pos = this->position;
    ui::uiNode* temp = this->parent;
    while(temp!=nullptr)
    {
        pos += temp->position;
        temp = temp->parent;
    }
    return (mouse.x > pos.x && mouse.x < pos.x + size.x &&
            mouse.y < pos.y && mouse.y > pos.y - size.y);
}
inline bool ui::PanelNode::on_press(vec2 mouse, bool press, bool release)
{
    if(pressed_node == this) 
        color *= 1.1f;
    if(on_hover(mouse))
    {
        color *= 1.1f;
        if(press)
        {
            pressed_node = this;
            return 0;
        }
        if(release && pressed_node == this)
        {
            pressed_node = nullptr;
            return 1;
        } 
    }
    if(release && pressed_node == this)
        pressed_node = nullptr;
    return 0;
}
    



