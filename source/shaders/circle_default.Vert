#version 460 core


layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aUV;

out vec2 UV_coord;
out vec3 Color;
out float iTime;
out float mag;

uniform float u_intensity;
uniform float u_iTime;

void main()
{
	//vec2 position = vec2(aPos.x / u_aspect_ratio, aPos.y);
	gl_Position = vec4(aPos,0, 1.0f);

	UV_coord = aPos;

	Color = vec3(1,0,1);
	iTime = u_iTime;
	mag = u_intensity;
}