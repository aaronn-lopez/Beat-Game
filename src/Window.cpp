#include "Window.h"






//LoadGL Implementaion
LoadGL::LoadGL() 
    {
        if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(sf::Context::getFunction)))
        {
            std::cout << "Failed to initialize GLEW\n";
            exit(1);
        } 
        const GLubyte* version = glGetString(GL_VERSION);
        if (version != nullptr) {
            std::cout << "LOADED OpenGL version: " << version << std::endl;
        } else {
            std::cerr << "Failed to get OpenGL version." << std::endl;
        }
    }


//GameWindow implementation
GameWindow::GameWindow(sf::VideoMode mode, const sf::String& title) 
:sf::RenderWindow(mode, title), LoadGL(), square(Mesh()),
    resolution(static_cast<float>(getSize().x), static_cast<float>(getSize().y))
{    
    const vec2 vertices[] =
	{
		vec2(-1,-1), vec2(0,0),
		vec2(1,-1), vec2(1,0),
		vec2(1,1), vec2(1,1),
		vec2(-1,1), vec2(0,1)
	};
	const unsigned int indices[] = { 0,1,2,0,2,3 };
    square.load_buffer(vertices, sizeof(vertices), indices, sizeof(indices));
    square.set_attrib_format(0, 2, GL_FLOAT, 4, 0);
    square.set_attrib_format(1, 2, GL_FLOAT, 4, 2);
    //fixing texture rendering
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}


void GameWindow::onResize()
{
    sf::Vector2u r = getSize();
    resolution = vec2(static_cast<float>(r.x), static_cast<float>(r.y));
    std::cout<<resolution<<'\n';
    glViewport(0, 0, r.x, r.y);
}
vec2 GameWindow::get_resolution() const
{
    return resolution;
}
    
void GameWindow::draw_square(sf::Shader& shader)
{
    sf::Shader::bind(&shader);
    square.bind();
    square.draw(); 
}
void GameWindow::draw_square() 
{
    square.bind();
    square.draw();
}




