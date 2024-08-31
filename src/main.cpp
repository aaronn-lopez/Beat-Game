#include "Window.h"
#include "Math/mat.h"
#include "DeltaTime.hpp"
//#include "Input.hpp"
#include "VertexShaderLayouts.h"
#include "UniformLayouts.hpp"
#include "Input.hpp"




int main()
{
    //Window Initialization OpenGL version 4.6 (Might not work on mac)
    GameWindow window(sf::VideoMode(900, 600), "OpenGL SFML"); 

    sf::Font font;
    font.loadFromFile("assets/Exo.ttf");
    window.set_font(font);

    sf::Shader shader1;
    shader1.loadFromFile("shaders/vert/shader_ui.vert", "shaders/frag/ui.frag");
     

    DeltaTime time;
    Input input(window);
    while (window.isOpen())
    {
        time.handle_time();
        input.handle_input(&window); 
        glClearColor(0.05f, 0.1f, 0.15f, 1);
        glClear(GL_COLOR_BUFFER_BIT);


        sf::Shader::bind(&shader1); 
        //b1.position = input.mouse_pos_a();
        UI::Button b1;
        b1.text.string = "Play";
        b1.position = vec2(-90,40);
        b1.size = vec2(100,30);
        if(b1.on_hover(input.mouse_pos_a(), window.get_resolution()))
        {
            b1.color *= 1.2;
            if(input.mouse_down(sf::Mouse::Left))
                b1.color *= 0.8;
        }
        window.draw_ui(b1, shader1);
        UI::Button b2;
        b2.text.string = "Options";
        b2.position = vec2(-90,0);
        b2.size = vec2(100,30);
        if(b2.on_hover(input.mouse_pos_a(), window.get_resolution()))
        {
            b2.color *= 1.2;
            if(input.mouse_down(sf::Mouse::Left))
                b2.color *= 0.8;
        }
        window.draw_ui(b2, shader1);
        UI::Button b3;
        b3.text.string = "Quit";
        b3.position = vec2(-90,-40);
        b3.size = vec2(100,30);
        if(b3.on_hover(input.mouse_pos_a(), window.get_resolution()))
        {
            b3.color *= 1.2;
            if(input.mouse_down(sf::Mouse::Left))
                b3.color *= 0.8;
        }
        window.draw_ui(b3, shader1);

        sf::Shader::bind(0);
        glBindVertexArray(0);
        window.draw_text("FPS: " + std::to_string(time.get_fps()), vec2(-150,100), 0.2);


        window.display();
    }


    window.close();
}