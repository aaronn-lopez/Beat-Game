#include "ui.h"


vec2 ui::convert_origin(const ui::uiNode& node, Origin origin)
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
        default:
            return node.position;
    }
}






ui::uiNode::uiNode
    (uiNode* parent, const vec2& position, const vec2& size, Origin origin)
    : parent(parent), position(position), size(size), origin(origin){}


ui::TextNode::TextNode( const std::string& text, uiNode* parent,
                        const vec2& position, const vec2& size, const vec4& color)
    : string(text), uiNode(parent, position, size), color(color){}

ui::PanelNode::PanelNode(const vec2& p, uiNode* parent) : uiNode(parent, p), color(vec4(1,1,1,0.1f)){}

void ui::uiNode::connect(ui::uiNode* parent)
{
    this->parent = parent;
}

//PanelNode
bool ui::PanelNode::on_hover(vec2 mouse)
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
bool ui::ButtonNode::on_press(vec2 mouse, bool press, bool release)
{
    color = button_color;
    if(on_hover(mouse))
    {
        color += 0.1f;
        if(press)
        {
            is_pressed = 1;
            return 0;
        }
        if(release && is_pressed)
        {
            is_pressed = 0;
            return 1;
        }
    }
    if(release && is_pressed)
        is_pressed = 0;
    if(is_pressed) color = button_color + 0.15f;
    return 0;
}