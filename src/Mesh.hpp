#pragma once
#include "SFML/Graphics.hpp"
#include "GLAD/glad.h"

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


//Mesh Implementation
inline Mesh::Mesh()
{
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);
}
inline Mesh::Mesh(const void* vertices_data, size_t v_bytes, const void* indices_data, int indices_count) : Mesh::Mesh()
{ 
    this->indices_count = sizeof(GLuint) * indices_count;
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ARRAY_BUFFER, v_bytes, vertices_data, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices_count, indices_data, GL_STATIC_DRAW);
}
inline Mesh::~Mesh()
{
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
    glDeleteVertexArrays(1, &vao);
}
inline void Mesh::bind()
{
    glBindVertexArray(vao);
}
inline void Mesh::set_attrib_format(GLuint layout_index, GLint size, GLenum gl_type, int stride, int offset) 
{
    //WARNING - possible warning, int to void*
    glVertexAttribPointer(layout_index, size, gl_type, GL_FALSE, GLsizeof(gl_type) * stride, (void*)(GLsizeof(gl_type) * offset));
    glEnableVertexAttribArray(layout_index);
}
inline void Mesh::draw() const
{
    glDrawElements(GL_TRIANGLES, indices_count, GL_UNSIGNED_INT, 0);  
}
inline void Mesh::load_buffer(const void* vertices_data, size_t v_bytes, const void* indices_data, int indices_count)
{
    this->indices_count = sizeof(GLuint) * indices_count;
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ARRAY_BUFFER, v_bytes, vertices_data, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices_count, indices_data, GL_STATIC_DRAW);
}
