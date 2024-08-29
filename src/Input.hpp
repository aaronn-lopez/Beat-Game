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
    
    /**
     * Handles all the input for GameWindow. Place This Function inside 
     * Currently Active Gameloops for input to work properly
     */
    void handle_input(GameWindow* window);
    //Returns if current key is held down.
    bool key_down(sf::Keyboard::Key key);
    //Return if current key was pressed.
    bool key_press(sf::Keyboard::Key key);
    //Return if current key was released.
    bool key_release(sf::Keyboard::Key key);
    //Return if current button is down.
    bool mouse_down(sf::Mouse::Button button);
    //return if current button was pressed.
    bool mouse_press(sf::Mouse::Button button);
    //return is current button was released.
    bool mouse_release(sf::Mouse::Button button);
    /**
     * @brief This Function returns the current position of the mouse 
     * within local space Coordinates of -100 to 100
     * regardless of resolution or aspect ratio
     * @note Similar to OpenGL local space -1 to 1 regardless of Aspect Ratio 
     */
    vec2 mouse_pos() const;
    /**
     * @brief Similar to mouse_pos() but aspect ratio is corrected. Meaning
     * Local Coordinates can range from vec2(-1.5, -1) to vec2(1.5, 1) multiplied by 100 or vec2(-150, -100) to vec2(150, 100)
     * 
     * @note The local coordinate components will never go below |1|
     * and will always fit the smaller resolution component.
     */
    vec2 mouse_pos_a() const;
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
inline vec2 Input::mouse_pos() const
{
    //Screen space to Normalized -1 to 1
    return (mouse / resolution * 2 - vec2(1,1)) * 100;
}
inline vec2 Input::mouse_pos_a() const
{
    //Aspect ratio correction
    float r = resolution.x / resolution.y;
    return resolution.x >= resolution.y? 
        mouse_pos() * vec2(r,1):
        mouse_pos() / vec2(1, r);
    
}
