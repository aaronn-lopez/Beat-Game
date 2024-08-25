#version 410 core
//Vertex

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aUV;

/* 	This shader is used for a Quad that is positioned
	from -1 to 1 with a default radius of 1. 
	The default position and radius coverse the entire screen.
	This shader is meant to emulate many of the basic ShaderToy
	features while being able to move around the ViewPort with 
	"position" and scaled with "radius"

	This shader is affected by aspect ratio making it 
	suitable for game objects or ui
	game objects the wont be affected by viewport aspect ratio
*/

//========fragment variables========
//Resolution
out vec2 iResolution;
//Mouse screen position
out vec2 iMouse;	
//Global Time and sound frequency
out float iTime;
out float iFrequency;
//==================================

uniform float u_var[10];

void main()
{
	//Quad Dimensions
	vec2 position;
	float width;
	float height;
	//memory layout
	//bg
	iResolution.x = 	u_var[0];		
	iResolution.y = 	u_var[1];		
	iMouse.x = 			u_var[2];
	iMouse.y = 			u_var[3];
	iTime = 			u_var[4];
	iFrequency = 		u_var[5];
	//ui /m
	position.x = 		u_var[6];
	position.y = 		u_var[7];
	width = 			u_var[8];
	height = 			u_var[9];

	float r = iResolution.x / iResolution.y;	
	vec2 Pos = aPos * vec2(width, height);
	Pos *= iResolution.x >= iResolution.y? 1/vec2(r,1): vec2(1, r); 
	gl_Position = vec4(Pos + position, 1.0f, 1.0f);

}







