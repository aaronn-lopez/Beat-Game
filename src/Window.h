#pragma once
#include "SFML/Graphics.hpp"
#include "GLAD/glad.h"
#include "Mesh.hpp"
#include "Math/vec.h"

#include "UI.h"
#include "UniformLayouts.hpp"



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
    void set_font(sf::Font& font);

    //accessors
    vec2 get_resolution() const;
    vec2 get_ratio_correction() const;

    //Function automatically binds vao and shader while drawing.
    void draw_square(sf::Shader& shader);

    //Function automatically binds vao while drawing.
    void draw_square();
    void draw_text(const sf::String& text, vec2 position, float scale);

    void draw_ui(const UI::Button& layer, sf::Shader& s);
    //EXPERIMENTAL

private:
    Mesh square;
    sf::Text ui_text;
    vec2 resolution;
    vec2 ratio_correction;
    //testing
    void onResize();
    private:
private:
    GameWindow(const GameWindow&) = delete;
    void operator=(const GameWindow&) = delete;
};



