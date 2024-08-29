#include "CustomText.h"

void CustomText::on_resize()
{
    if(current_res != old_res)
    {
        old_res = current_res;
        font_size = old_res.x < old_res.y? old_res.x / 4: old_res.y/4;
        setCharacterSize(font_size); 
        //setOrigin(getLocalBounds().getSize().x/1.93f, getLocalBounds().getSize().y/1.1f);
    }
}
void CustomText::set_scale(const vec2& s)
{
    setScale(s.x, s.y);
}
vec2 CustomText::get_scale() const
{
    return getScale();
}
void CustomText::set_resolution(const sf::Vector2u& res)
{
    current_res = res;
    resolution = res;
}
void CustomText::set_position_centered(vec2 p)
{
    p/=100;

    //Normalized coordinates -1 to 1
    //Convertion to screenspace
    p += vec2(1,1);
    p /= 2;
    p *= resolution;  
    setPosition(p.x - getScale().x * getLocalBounds().width/2, resolution.y - p.y);
}
void CustomText::set_position(vec2 p)
{
    p/=100;

    //Normalized coordinates -1 to 1
    //Convertion to screenspace
    p += vec2(1,1);
    p /= 2;
    p *= resolution;  
    setPosition(p.x - getScale().x, resolution.y - p.y);
}
