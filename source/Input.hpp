#pragma once
#include "SFML/Window.hpp"
#include "Math/vec.h"

class Input
{
	int last_pressed_key = -1;
	int mouse_wheel_state = 0;
	float _mouse_x = 0, _mouse_y = 0;
	unsigned char key_state[sf::Keyboard::Scancode::ScancodeCount] = {};
	unsigned char mouse_button_state[sf::Mouse::ButtonCount] = {};
	static Input& get() { static Input instance; return instance; }
	Input() {};
	Input(const Input&) = delete;
public:
	static void handle_events(sf::Window& window);
	static bool key_pressed(sf::Keyboard::Key key);
	static bool key_released(sf::Keyboard::Key key);
	static bool key_down(sf::Keyboard::Key key) { return sf::Keyboard::isKeyPressed(key); };
	static bool mouse_pressed(sf::Mouse::Button button);
	static bool mouse_released(sf::Mouse::Button button);
	static int mouse_wheel() { return get().mouse_wheel_state; }
	static float mouse_x() { return get()._mouse_x; }
	static float mouse_y() { return get()._mouse_y; }
	static vec2 mouse_pos() { return vec2(get()._mouse_x, get()._mouse_y); }
	static int get_key_scancode() { return get().last_pressed_key; }
	static bool is_keyboard_pressed() { return get().last_pressed_key != -1; }
};

inline void Input::handle_events(sf::Window& window)
{
	//0 = inactive
	//1 = pressed
	//2 = released
	sf::Event Event;
	get().mouse_wheel_state = 0;
	get().last_pressed_key = -1;//no key pressed
	while (window.pollEvent(Event))
	{
		switch (Event.type)
		{
		case sf::Event::Closed:
			window.close();
			break;
		case sf::Event::KeyPressed:
			get().last_pressed_key = Event.key.scancode;
				get().key_state[Event.key.scancode] = 1;
			break;
		case sf::Event::KeyReleased:
			get().key_state[Event.key.scancode] = 2;
			break;
		case sf::Event::MouseButtonPressed:
				get().mouse_button_state[Event.mouseButton.button] = 1;
			break;
		case sf::Event::MouseButtonReleased:
				get().mouse_button_state[Event.mouseButton.button] = 2;
			break;
		case sf::Event::MouseMoved:
			get()._mouse_x = Event.mouseMove.x;
			get()._mouse_y = Event.mouseMove.y;
			break;
		case sf::Event::MouseWheelScrolled:
			get().mouse_wheel_state = Event.mouseWheelScroll.delta;
			break;
		}
	}
}
inline bool Input::key_pressed(sf::Keyboard::Key key)
{
	if (get().key_state[key] == 1)
	{
		get().key_state[key] = 0;
		return 1;
	}
	return 0;
}
inline bool Input::key_released(sf::Keyboard::Key key)
{
	if (get().key_state[key] == 2)
	{
		get().key_state[key] = 0;
		return 1;
	}
	return 0;
}

inline bool Input::mouse_pressed(sf::Mouse::Button button)
{
	if (get().mouse_button_state[button] == 1)
	{
		get().mouse_button_state[button] = 0;
		return 1;
	}
	return 0;
}
inline bool Input::mouse_released(sf::Mouse::Button button)
{
	if (get().mouse_button_state[button] == 2)
	{
		get().mouse_button_state[button] = 0;
		return 1;
	}
	return 0;
}