#pragma once
#include "SFML/Graphics.hpp"
#include "GLAD/glad.h"
#include "Mesh.hpp"
#include "Math/vec.h"

#include "CustomText.h"
//#include "Input.hpp"



/*This Class is meant to be inherited in order
to load glad into a Window on construction.
*/
class LoadGL
{
protected:
    LoadGL(); 
};




/*This class will for rendering the main game and ui
*/
class GameWindow : public sf::RenderWindow, private LoadGL
{
public:
    GameWindow(sf::VideoMode mode, const sf::String& title);

    //accessors
    vec2 get_resolution() const;

    //Function automatically binds vao and shader while drawing.
    void draw_square(sf::Shader& shader);

    //Function automatically binds vao while drawing.
    void draw_square();

private:
    Mesh square;
    vec2 resolution;
    //testing
    void onResize();
    private:
private:
    GameWindow(const GameWindow&) = delete;
    void operator=(const GameWindow&) = delete;
};



