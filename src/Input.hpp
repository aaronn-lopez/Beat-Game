#pragma once
#include "Window.h"

class Input
{
private:
    vec2 resolution;
    vec2 mouse;
    float mouse_w;
    int pressed_key;
    unsigned char mouse_state[sf::Mouse::ButtonCount] = {};
    unsigned char key_state[sf::Keyboard::Scancode::ScancodeCount] = {};
public:
    Input(sf::Window& window);
    void handle_input(GameWindow* window);
    bool key_down(sf::Keyboard::Key key);
    bool key_press(sf::Keyboard::Key key);
    bool key_release(sf::Keyboard::Key key);
    bool mouse_down(sf::Mouse::Button button);
    bool mouse_press(sf::Mouse::Button button);
    bool mouse_release(sf::Mouse::Button button);
    vec2 mouse_pos_vp() const;
    vec2 mouse_pos() const;
};

inline Input::Input(sf::Window& window) : pressed_key(-1), mouse_w(0)
{
    sf::Vector2u res = window.getSize();
    resolution =  vec2(
        static_cast<float>(window.getSize().x),
        static_cast<float>(window.getSize().y));
}
inline void Input::handle_input(GameWindow* window)
{
    sf::Event e;
    pressed_key = -1;
    mouse_w = 0;
    while(window->pollEvent(e))
    {
        switch(e.type)
        {
            case sf::Event::Closed:
                window->close();
            break;
            case sf::Event::KeyPressed:
                pressed_key = e.key.scancode;
                key_state[e.key.scancode] = 1;
            break;
            case sf::Event::KeyReleased:
                key_state[e.key.scancode] = 2;
            break;
            case sf::Event::MouseButtonPressed:
                mouse_state[e.mouseButton.button] = 1;
            break;
            case sf::Event::MouseButtonReleased:
                mouse_state[e.mouseButton.button] = 2;
            break;
            case sf::Event::MouseMoved:
                mouse.x = static_cast<float>(e.mouseMove.x);
                mouse.y = resolution.y - static_cast<float>(e.mouseMove.y);
            break;
            case sf::Event::MouseWheelScrolled:
               mouse_w = e.mouseWheelScroll.delta;
            break;
            case sf::Event::Resized:
                resolution = window->get_resolution();
            break;

        }
    }
}

inline bool Input::key_down(sf::Keyboard::Key key)
{
    return sf::Keyboard::isKeyPressed(key);
}
inline bool Input::key_press(sf::Keyboard::Key key)
{
    if(key_state[key] == 1)
    {
        key_state[key] = 0;
        return 1;
    }
    return 0;
}
inline bool Input::key_release(sf::Keyboard::Key key)
{
    if(key_state[key] == 2)
    {
        key_state[key] = 0;
        return 1;
    }
    return 0;
}
inline bool Input::mouse_down(sf::Mouse::Button button)
{
    return sf::Mouse::isButtonPressed(button);
}
inline bool Input::mouse_press(sf::Mouse::Button button)
{
    if(mouse_state[button] == 1)
    {
        mouse_state[button] = 0;
        return 1;
    }
    return 0;
}
inline bool Input::mouse_release(sf::Mouse::Button button)
{
    if(mouse_state[button] == 2)
    {
        mouse_state[button] = 0;
        return 1;
    }
    return 0;
}
inline vec2 Input::mouse_pos_vp() const
{
    return mouse / resolution * 2 - vec2(1,1);
}
inline vec2 Input::mouse_pos() const
{
    float r = resolution.x / resolution.y;
    return resolution.x >= resolution.y? 
        mouse_pos_vp() * vec2(r,1):
        mouse_pos_vp() / vec2(1, r);
    
}
