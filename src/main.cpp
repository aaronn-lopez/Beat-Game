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
    font.loadFromFile("assets/Roboto.ttf");
    window.set_font(font);

    sf::Shader shader1;
    shader1.loadFromFile("shaders/vert/shader_ui.vert", "shaders/frag/ui.frag");

    //UI Generation
        ui::ButtonNode PLAY;
        PLAY.button_color = vec4(0.5, 0.5, 0, 1);
        PLAY.position = vec2(-100, 90);
        ui::TextNode t1("PLAY", &PLAY);


        ui::ButtonNode OPTIONS;
        OPTIONS.connect(&PLAY);
        OPTIONS.position = vec2(0, -PLAY.size.y);
        ui::TextNode t2("OPTIONS", &OPTIONS);

        ui::ButtonNode EXIT;
        EXIT.connect(&OPTIONS);
        EXIT.position = vec2(0, -OPTIONS.size.y);
        ui::TextNode t3("EXIT", &EXIT);
     

    DeltaTime time;
    time.set_target_fps(360);
    Input input(window);
    while (window.isOpen())
    {
        time.handle_time();
        input.handle_input(&window); 
        window.clear_screen();

        bool press = input.mouse_press(sf::Mouse::Left);
        bool release = input.mouse_release(sf::Mouse::Left);


        if(PLAY.on_press(input.mouse_pos_a(), press, release))
            std::cout<<"PLAY\n";
        if(OPTIONS.on_press(input.mouse_pos_a(), press, release))
            std::cout<<"OPTIONS\n";

        if(EXIT.on_press(input.mouse_pos_a(), press, release))
            window.close();
        //p1.position = vec2(-100,90);
        //p1.position = vec2(0,0);
        window.draw_ui(PLAY, shader1);
        window.draw_ui(t1);

        window.draw_ui(OPTIONS, shader1);
        window.draw_ui(t2);

        window.draw_ui(EXIT, shader1);
        window.draw_ui(t3);


        sf::Shader::bind(0);
        glBindVertexArray(0);
        window.draw_text("FPS: " + std::to_string(time.get_fps()), vec2(-150,100), 50);


        window.display();
    }


    window.close();
}