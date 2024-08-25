#version 330 core

// The vertex position passed from SFML
layout(location = 0) in vec2 vertexPosition;

// The texture coordinates of the glyph
layout(location = 1) in vec2 texCoords;

// The output to the fragment shader
out vec2 fragTexCoords;
uniform vec2 u_position;

void main()
{
    // Directly set the vertex position without transformation
    gl_Position = vec4(vertexPosition/900*3, 0.0, 1.0);
    // Pass the texture coordinates to the fragment shader
    fragTexCoords = texCoords;
}