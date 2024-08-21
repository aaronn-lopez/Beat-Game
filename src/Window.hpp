#pragma once
#include "SFML/Graphics.hpp"
#include "GLAD/glad.h"
#include <Array>
class Mesh
{
public:
    GLuint vao = 0;
    GLuint vbo = 0;
    GLuint ebo = 0;
    Mesh();
    Mesh(float* vertices, size_t v_bytes, GLuint* indices, size_t i_bytes);
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
Mesh::Mesh(float* vertices, size_t v_bytes, GLuint* indices, size_t i_bytes) : Mesh::Mesh()
{
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo);

    glBufferData(GL_ARRAY_BUFFER, v_bytes, vertices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, i_bytes, indices, GL_STATIC_DRAW);
}
Mesh::~Mesh()
{
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
    glDeleteVertexArrays(1, &vao);
}