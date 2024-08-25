#pragma once
#include "SFML/Graphics.hpp"
#include "GLAD/glad.h"
#include <Array>
#include "Math/vec.h"
//#include "Input.hpp"

//Function for checking opengl datatype enums(GL_FLOAT, GL_INT, GL_UNSIGNED_INT, etc)
GLsizei GLsizeof(GLenum type);



/*Class for basic OpenGL functionality like
vao, vbo, ebo, as well as setting their attribute formats.
Use the Constructor or "load_buffer" to load vertices with their indices.
*/
class Mesh
{
    //not implimented yet
    inline static GLuint current_binded_vao = 0;
private:
    int indices_count = 0;
    GLuint vao = 0;
    GLuint vbo = 0;
    GLuint ebo = 0;
public:
    Mesh();
    Mesh(const void* vertices_data, size_t v_bytes, const void* indices_data, int indices_count);
    void load_buffer(const void* vertices_data, size_t v_bytes, const void* indices_data, int indices_count);
    void set_attrib_format(GLuint layout_index, GLint size, GLenum gl_type, int stride, int offset);
    void draw() const;
    void bind();
    ~Mesh();
private:
    Mesh(Mesh& m) = delete;
    void operator=(const Mesh&) = delete;
};



/*This Class is meant to be inherited in order
to load glad into a Window on construction.
*/
class LoadGL
{
protected:
    LoadGL(); 
};




/*This class will for rendering the main game and ui
*/
class GameWindow : public sf::RenderWindow, private LoadGL
{
public:
    GameWindow(sf::VideoMode mode, const sf::String& title);

    //accessors
    vec2 get_resolution() const;

    //Function automatically binds vao and shader while drawing.
    void draw_square(sf::Shader& shader);

    //Function automatically binds vao while drawing.
    void draw_square();

private:
    Mesh square;
    vec2 resolution;
    //testing
    void onResize();
    private:
private:
    GameWindow(const GameWindow&) = delete;
    void operator=(const GameWindow&) = delete;
};



