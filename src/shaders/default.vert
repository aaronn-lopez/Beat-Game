#version 330 core


layout (location = 0) in vec2 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aUV;

out vec3 color;



void main()
{
	gl_Position = vec4(aPos * 0.5,1.0f, 1.0f);
	//color = vec3(aUV, 1);
	color = vec3(aPos,0.0f);
}