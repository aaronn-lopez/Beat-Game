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

out vec2 texCoord;
out vec2 iScale;
out float CornerRadius;
out float OutlineThickness;
//========fragment variables========
//Resolution
out vec2 iResolution;
//Mouse screen position
out vec2 iMouse;	
//Global Time and sound frequency
out float iTime;
out float iFrequency;
out vec4 iColor;
//==================================

uniform float u_var[14];

void main()
{
	//Quad Dimensions
	vec2 position;
	vec2 size;
	//memory layout
	//bg
	iResolution.x = 	u_var[0];		
	iResolution.y = 	u_var[1];		
	iTime = 			u_var[2];
	iFrequency = 		u_var[3];
	//ui /m
	position.x = 		u_var[4];
	position.y = 		u_var[5];
	size.x = 			u_var[6];
	size.y = 			u_var[7];
	iColor = vec4(u_var[8], u_var[9], u_var[10], u_var[11]);
	iScale = size/100;
	CornerRadius = 		u_var[12];
	OutlineThickness = u_var[13];
	

 	vec2 r = iResolution;
	vec2 aspect_correction = r.x <= r.y? vec2(1,r.x/r.y): vec2(r.y/r.x, 1); 
	vec2 Pos = (aPos/200 * size + position/100) * aspect_correction;
	gl_Position = vec4(Pos, 1.0f, 1.0f);
	texCoord = aUV;
}
