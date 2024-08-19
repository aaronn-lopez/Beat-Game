#version 460 core


layout (location = 0) in vec2 aPos;


out vec2 UV;
out float iTime;
out vec3 color;

uniform vec2 u_position;
uniform float u_iTime;
uniform float u_scale;
uniform vec3 u_color;

void main()
{
	gl_Position = vec4(aPos*u_scale + u_position,1.0f, 1.0f);
	UV = aPos;
	iTime = u_iTime;
	color = u_color;
}