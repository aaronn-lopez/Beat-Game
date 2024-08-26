#include "Window.h"
#include "Math/mat.h"
#include "DeltaTime.hpp"
//#include "Input.hpp"
#include "VertexShaderLayouts.h"
#include "Input.hpp"




int main()
{
    ShaderToy_ui s;
    //Window Initialization OpenGL version 4.6 (Might not work on mac)
    GameWindow window(sf::VideoMode(900, 600), "OpenGL SFML"); 

    sf::Shader shader1;
    shader1.loadFromFile("shaders/vert/ShaderToy_ui.vert", "shaders/frag/s1.frag");
    sf::Shader shader2;
    //shader2.loadFromFile("shaders/vert/ShaderToy_ui.vert", "shaders/frag/s1.frag");
    shader2.loadFromFile("shaders/vert/text.vert", "shaders/frag/text.frag");
     
    s.iResolution = vec2(1,1);
    DeltaTime time;
    time.set_target_fps(245);
    sf::Font font;
    font.loadFromFile("assets/Exo.ttf");

    CustomText custom_text;
    custom_text.set_font(font);

    //sf::Glyph glyph = font.getGlyph(95, 45, 0);
    //text.setFillColor(sf::Color::Black); // Set the text color
    Input input(window);
    while (window.isOpen())
    {
        time.handle_time();
        input.handle_input(&window); 
        glClearColor(0.1f, 0.1f, 0.1f, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        //sf::Shader::bind(&shader1);
        s.position = input.mouse_pos_vp();
        s.iResolution = window.get_resolution();

        sf::Shader::bind(&shader2);
        shader2.setUniformArray("u_var", &s.iResolution.x, 10);
        custom_text.draw();
        window.draw_square(); 

        glBindVertexArray(0);
        sf::Shader::bind(0);
        //window.draw(text);
        window.display();
    }


    window.close();
}