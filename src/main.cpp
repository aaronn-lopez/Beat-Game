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

        bool press = input.mouse_press(sf::Mouse::Left);
        bool release = input.mouse_release(sf::Mouse::Left);
        ui::PanelNode p1;
        p1.color = vec4(0.1,0.4,0.4,1);
        p1.position = vec2(-100,90);
        if(p1.on_press(input.mouse_pos_a(), press, release))
            std::cout<<"WOW\n";
        window.draw_ui(p1, shader1);

        ui::TextNode t1("play", &p1);
        window.draw_ui(t1);

        ui::PanelNode p2 = p1;
        p2.color = vec4(0.1, 0.3, 0.3, 1);
        p2.connect(&p1); //offset from p1
        p2.position = vec2(0,-60);
        if(p2.on_press(input.mouse_pos_a(), press, release))
            std::cout<<"WOW2\n";
        window.draw_ui(p2, shader1);

        ui::TextNode t2("Options", &p2);
        window.draw_ui(t2);



        sf::Shader::bind(0);
        glBindVertexArray(0);
        window.draw_text("FPS: " + std::to_string(time.get_fps()), vec2(-150,100), 50);


        window.display();
    }


    window.close();
}