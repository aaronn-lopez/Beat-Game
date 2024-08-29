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
    //time.set_target_fps(245);
    sf::Font font;
    font.loadFromFile("assets/Exo.ttf");

    CustomText text;
    text.setFont(font);
    text.setString("Game"); 

    Input input(window);
    while (window.isOpen())
    {
        time.handle_time();
        //std::cout<<time.get_fps()<<'\n';
        input.handle_input(&window); 
        glClearColor(0.05f, 0.1f, 0.15f, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        sf::Shader::bind(&shader1);
        s.width = 30;
        s.height = 15;
        s.position = input.mouse_pos() + vec2(0,s.height);
        s.iResolution = window.get_resolution();
        //text.set_position_centered(s.position);
        text.set_scale(vec2(0.5,0.5));
        //text.set_position_centered(vec2(0,0));
        text.set_position(vec2(0,0));


        sf::Shader::bind(&shader1);
        //sf::Texture::bind(0);
        shader1.setUniformArray("u_var", &s.iResolution.x, 10);
        window.draw_square(); 
        

        sf::Shader::bind(0);
        glBindVertexArray(0);
        window.draw(text);


        window.display();
    }


    window.close();
}