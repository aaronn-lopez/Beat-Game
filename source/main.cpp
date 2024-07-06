#include <iostream>
#include "SFML/Graphics.hpp"
#include "DeltaTime.hpp";
#include "Input.hpp"
#include "Math/vec.h"
#include "GL/glew.h"

class myWin : public sf::Window
{
    using sf::Window::Window;
};

int main()
{
    //Window Initialization OpenGL version 3.3
    sf::ContextSettings settings;
    //settings.attributeFlags = sf::ContextSettings::Attribute::Core;

    settings.majorVersion = 4;
    settings.minorVersion = 5;
    sf::RenderWindow window(sf::VideoMode(1000, 900), "OpenGL SFML");
    glewExperimental = GL_TRUE;
    if (GLEW_OK != glewInit())
    {
        std::cout << "Failed to initialize GLEW\n";
        return EXIT_FAILURE;
    }

    //my own defined Triangle
    unsigned int vao, ebo, vbo;
    const vec2 vertices[] =
	{
		vec2(-1,-1), vec2(-1,-1),
		vec2(1,-1), vec2(1,-1),
		vec2(1,1), vec2(1,1),
		vec2(-1,1), vec2(-1,1)
	};
	const unsigned int indices[] = { 0,1,2,0,2,3 };
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(vec2) * 2, (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vec2) * 2, (void*)sizeof(vec2));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);





    sf::Shader shader;
    shader.loadFromFile("source/shaders/circle_default.vert", "source/shaders/circle_default.frag");
    shader.bind(&shader);

    sf::Font font;
    if (!font.loadFromFile("source/Exo.ttf"))
    {
        std::cout << "couldn't load fonts\n";
        return 1;
    }
    sf::Text text;
    text.setFont(font);
    text.setString("FRACTAL");
    text.setCharacterSize(50);
    text.setFillColor(sf::Color(200,0,200));
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);
    text.setOutlineThickness(2);
    text.setOutlineColor(sf::Color::Black);
    
    DeltaTime Time;
    float intensity = 0;
    while (window.isOpen())
    {
        intensity = 3.0f * sin(Time.get_time());
        Time.handle_time();
        Input::handle_events(window);
        //Time.show_fps();
        glClearColor(0.07, 0.13, 0.17, 1);
        glClear(GL_COLOR_BUFFER_BIT);



        //window.resetGLStates();
        //window.pushGLStates();
        //window.popGLStates();
        shader.setUniform("u_iTime", Time.get_time());
        shader.setUniform("u_intensity", pow(abs(intensity/2),0.6f));
        shader.bind(&shader);
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);
        shader.bind(0);
        window.draw(text);

        window.display();
    }


    window.close();
}