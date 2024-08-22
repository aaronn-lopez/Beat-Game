#include "Window.h"


GLsizei GLsizeof(GLenum type)
{
    switch(type)
    {
        case GL_BYTE: return sizeof(GLbyte); break;
        case GL_UNSIGNED_BYTE: return sizeof(GLubyte); break;
        case GL_SHORT: return sizeof(GLshort); break;
        case GL_UNSIGNED_SHORT: return sizeof(GLushort); break;
        case GL_INT: return sizeof(GLint); break;
        case GL_UNSIGNED_INT: return sizeof(GLuint); break;
        case GL_FLOAT: return sizeof(GLfloat); break;
        case GL_DOUBLE: return sizeof(GLdouble); break;
        default: return 0;
    } 
}





//Mesh Implementation
Mesh::Mesh()
{
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);
}
Mesh::Mesh(const void* vertices_data, size_t v_bytes, const void* indices_data, int indices_count) : Mesh::Mesh()
{ 
    this->indices_count = sizeof(GLuint) * indices_count;
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ARRAY_BUFFER, v_bytes, vertices_data, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices_count, indices_data, GL_STATIC_DRAW);
}
Mesh::~Mesh()
{
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
    glDeleteVertexArrays(1, &vao);
}
void Mesh::bind()
{
    glBindVertexArray(vao);
}
void Mesh::set_attrib_format(GLuint layout_index, GLint size, GLenum gl_type, int stride, int offset) 
{
    //WARNING - possible warning, int to void*
    glVertexAttribPointer(layout_index, size, gl_type, GL_FALSE, GLsizeof(gl_type) * stride, (void*)(GLsizeof(gl_type) * offset));
    glEnableVertexAttribArray(layout_index);
}
void Mesh::draw() const
{
    glDrawElements(GL_TRIANGLES, indices_count, GL_UNSIGNED_INT, 0);  
}
void Mesh::load_buffer(const void* vertices_data, size_t v_bytes, const void* indices_data, int indices_count)
{
    this->indices_count = sizeof(GLuint) * indices_count;
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ARRAY_BUFFER, v_bytes, vertices_data, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices_count, indices_data, GL_STATIC_DRAW);
}







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
:sf::RenderWindow(mode, title), LoadGL(), square(Mesh())
{    
    const vec2 vertices[] =
	{
		vec2(-1,-1), vec2(-1,-1),
		vec2(1,-1), vec2(1,-1),
		vec2(1,1), vec2(1,1),
		vec2(-1,1), vec2(-1,1)
	};
	const unsigned int indices[] = { 0,1,2,0,2,3 };
    square.load_buffer(vertices, sizeof(vertices), indices, sizeof(indices));
    square.set_attrib_format(0, 2, GL_FLOAT, 4, 0);
    square.set_attrib_format(1, 2, GL_FLOAT, 4, 2);
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








