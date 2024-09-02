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
    ui_text.setOutlineColor(sf::Color::Black);
    ui_text.setOutlineThickness(1);
    ui_text.setStyle(sf::Text::Bold);
    onResize();
}
void GameWindow::clear_screen(const vec4& color)
{
        glClearColor(color.x, color.y, color.z, color.w);
        glClear(GL_COLOR_BUFFER_BIT);
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

    unsigned int font_size = r.x < r.y? r.x / 12: r.y/12;
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
void GameWindow::draw_text(const sf::String& text, vec2 position, float scale, const vec4 c)
{
    sf::Shader::bind(0);
    glBindVertexArray(0);
    position *= ratio_correction;
    position /= 100;
    position += vec2(1,1);
    position /= 2;
    position *= resolution;
    scale/=100;

    ui_text.setPosition(position.x, resolution.y - position.y);
    ui_text.setScale(scale, scale);
    ui_text.setFillColor
    (
        sf::Color(static_cast<sf::Uint32>(c.x * 255.0f), static_cast<sf::Uint32>(c.y * 255.0f),
        static_cast<sf::Uint32>(c.z * 255.0f), static_cast<sf::Uint32>(c.w * 255.0f))
    );
    ui_text.setString(text);
    sf::RenderWindow::draw(ui_text); 
}
void GameWindow::draw_ui(const ui::PanelNode& node, sf::Shader& s)
{
    vec2 pos = ui::convert_origin(node, node.origin);
    ui::uiNode* temp = node.parent;
    while(temp!=nullptr)
    {
        pos += temp->position;
        temp = temp->parent;
    }

    Uniform::shader_ui u;
    //UI Uniforms
    u.position = pos;
    u.size = node.size;
    u.iColor = node.color;
    u.CornerRadius = node.corner_radius;
    u.OutlineThickness = node.outline_thickness;
    //internal Uniforms
    u.iResolution = resolution;
    u.iTime = 0;
    u.iFrequency = 0;

    sf::Shader::bind(&s);
    s.setUniformArray("u_var", &u.iResolution.x, 14);
    draw_square();
}
void GameWindow::draw_ui(const ui::TextNode& node)
{
    vec2 pos(0,0);
    ui::uiNode* temp = node.parent;
    while(temp!=nullptr)
    {
        pos += temp->position;
        temp = temp->parent;
    }
    //to be changed
    draw_text(node.string, pos, node.size.x, node.color);
}









