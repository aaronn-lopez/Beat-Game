#include "ui.h"








ui::uiNode::uiNode
    (uiNode* parent, const vec2& positio, const vec2& size, Origin origin)
    : parent(parent), position(position), size(size), origin(origin){}


ui::TextNode::TextNode( const std::string& text, uiNode* parent,
                        const vec2& position, const vec2& size)
    : string(text), uiNode(parent, position, size){}


vec2 ui::origin_to_position(const ui::uiNode& node, Origin origin)
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
bool ui::PanelNode::on_press(vec2 mouse, bool press, bool release)
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