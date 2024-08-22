#pragma once
#include "SFML/Graphics.hpp"
#include "GLAD/glad.h"
#include <Array>
inline GLsizei GLsizeof(GLenum type)
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
//class MeshFormat
//{
//public:
//    GLuint attribute_index = 0;
//    GLint size = 0;
//    GLenum gl_type = 0;
//    GLsizei stride_bytes = 0;
//    GLsizei offset_bytes = 0;
//    MeshFormat(){};
//    MeshFormat(GLuint attribute_index, GLint size, GLenum gl_type, GLsizei stride_bytes, GLsizei offset_bytes)
//    : attribute_index(attribute_index), size(size), gl_type(gl_type), stride_bytes(stride_bytes), offset_bytes(offset_bytes){}
//};
class Mesh
{
    inline static GLuint current_binded_vao = 0;
private:
    int vertex_count = 0;
public:
    GLuint vao = 0;
    GLuint vbo = 0;
    GLuint ebo = 0;
    Mesh();
    Mesh(const void* vertices_data, size_t v_bytes, const void* indices_data, size_t i_bytes);
    void set_attrib_format(GLuint layout_index, GLint size, GLenum gl_type, int stride, int offset);
    void bind();
    ~Mesh();
};



class GameWindow : public sf::RenderWindow
{
public:
    GameWindow(sf::VideoMode mode, const std::string& title);

};





//Mesh Implementation
Mesh::Mesh()
{
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);
}
Mesh::Mesh(const void* vertices_data, size_t v_bytes, const void* indices_data, size_t i_bytes) : Mesh::Mesh()
{ 
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, v_bytes, vertices_data, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, i_bytes, indices_data, GL_STATIC_DRAW);
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
    glVertexAttribPointer(layout_index, size, gl_type, GL_FALSE, GLsizeof(gl_type) * stride, (void*)(GLsizeof(gl_type) * offset));
}