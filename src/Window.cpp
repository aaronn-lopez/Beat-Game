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
    square.load_buffer(vertices, sizeof(vertices), indices, 6);
    square.set_attrib_format(0, 2, GL_FLOAT, 4, 0);
    square.set_attrib_format(1, 2, GL_FLOAT, 4, 2);
    //fixing texture rendering
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    //Questionable decision for a static function
    onResize();
}

void GameWindow::set_font(sf::Font& font)
{
    ui_text.setFont(font);
}

void GameWindow::onResize()
{
    sf::Vector2u r = getSize();
    resolution = r;
    setView(sf::View(sf::FloatRect(0.f, 0.f, resolution.x, resolution.y)));

    //Questionable decision for a static function

    unsigned int font_size = r.x < r.y? r.x / 4: r.y/4;
    ui_text.setCharacterSize(font_size); 

    ratio_correction = resolution.x >= resolution.y?
        vec2(resolution.y/resolution.x, 1): vec2(1, resolution.x / resolution.y);
}
vec2 GameWindow::get_resolution() const
{
    return resolution;
}
vec2 GameWindow::get_ratio_correction() const
{
    return ratio_correction;
}
    
void GameWindow::draw_square() 
{
    square.bind();
    square.draw();
}
void GameWindow::draw_text(const sf::String& text, vec2 position, float scale)
{
    position *= ratio_correction;
    position /= 100;
    position += vec2(1,1);
    position /= 2;
    position *= resolution;

    ui_text.setPosition(position.x, resolution.y - position.y);
    ui_text.setScale(scale, scale);
    ui_text.setString(text);
    sf::RenderWindow::draw(ui_text); 
}
void GameWindow::draw_ui(const UI::Button& layer, sf::Shader& s)
{
    Uniform::shader_ui u; 
    u.iColor = layer.color;
    u.position = layer.position;
    u.size = layer.size;
    u.iResolution = get_resolution();
    u.CornerRadius = layer.corner_radius;
    u.OutlineThickness = layer.outline_thickness;
    if(layer.origin == UI::Origin::TopLeft) u.position += vec2(u.size.x, -u.size.y)/2;

    sf::Shader::bind(&s);
    s.setUniformArray("u_var", &u.iResolution.x, 14);
    draw_square();
    sf::Shader::bind(0);
    glBindVertexArray(0);
    draw_text(
        layer.text.string,
        u.position + layer.text.offset + vec2(-u.size.x, u.size.y)/2,
        layer.text.scale.x);
}



