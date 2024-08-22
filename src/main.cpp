
//#include "SFML/Graphics.hpp"
//#include "GLAD/glad.h"
//#include <Array>
#include "Window.hpp"
#include "Math/mat.h"
#include "DeltaTime.hpp"
#include "Input.hpp"
//we can define our own window class
class myWin : public sf::RenderWindow
{
    //copying RenderWindow constructors
    using sf::RenderWindow::RenderWindow;
};

int main()
{
    //Window Initialization OpenGL version 4.6 (Might not work on mac)
    sf::RenderWindow window(sf::VideoMode(900, 900), "OpenGL SFML");
    //Initializing opengl functions
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(sf::Context::getFunction)))
    {
        std::cout << "Failed to initialize GLEW\n";
        return EXIT_FAILURE;
    }

    //Defining a square covering the screen (JUST FOR TESTING)
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


    Mesh v(vertices, sizeof(vertices), indices, sizeof(indices));
    v.set_attrib_format(0, 2, GL_FLOAT, sizeof(vec2)*2, 0);
    v.set_attrib_format(1, 2, GL_FLOAT, sizeof(vec2)*2, sizeof(vec2));




    //shaders just for testing
    sf::Shader shader1;
    shader1.loadFromFile("shaders/circle_default.vert", "shaders/circle_default.frag");

    sf::Shader shader2;
    shader2.loadFromFile("shaders/Ring.vert", "shaders/Ring.frag");

    sf::Font font;
    if (!font.loadFromFile("assets/Exo.ttf"))
    {
        std::cout << "couldn't load fonts\n";
        return 1;
    }
    sf::Text text;
    text.setFont(font);
    text.setString("RHYTHM");
    text.setCharacterSize(50);
    text.setFillColor(sf::Color(200,0,200));
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);
    text.setOutlineThickness(2);
    text.setOutlineColor(sf::Color::Black);
    


    DeltaTime Time;
    Time.set_target_fps(266);


    //This is just for testing!
    float intensity = 0;
    float anim = 0;
    bool animation_flag = 0;
    sf::Vector2f pos;
    while (window.isOpen())
    {
        if (Input::mouse_pressed(sf::Mouse::Left))
        {
            animation_flag = 1;
            anim = 0;
            pos = sf::Vector2f(Input::mouse_x()/450-1, -1*(Input::mouse_y()/450-1));
        }
        if (animation_flag == 1 && anim < 1)
            anim += Time.frame_time()/2;
        else {
            anim = 0;
            animation_flag = 0;
        }
        intensity = 4.0f * sin(Time.get_time()/4);
        Time.handle_time();
        Input::handle_events(window);
        //Time.show_fps();

        //glClearColor(0.07, 0.13, 0.17, 1);
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        //setting the variables in the shader
        shader1.setUniform("u_iTime", Time.get_time());
        shader1.setUniform("u_intensity", pow(abs(intensity/2),0.6f));
        shader1.bind(&shader1);
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        //Setting the variables in the shader
        shader2.setUniform("u_iTime", anim);
        shader2.setUniform("u_scale", 1.0f);
        shader2.setUniform("u_position", pos);
        shader2.setUniform("u_color", sf::Vector3f(0, 1, 0));
        shader2.bind(&shader2);
        glBindVertexArray(vao);
        if(animation_flag==1)
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        //unbinding to draw text
        glBindVertexArray(0);
        shader1.bind(0);

        window.draw(text);

        window.display();
    }


    window.close();
}