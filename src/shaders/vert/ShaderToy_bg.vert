#version 410 core
//Vertex

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aUV;

/* 	This Shader covers the entire viewport and is 
	intended to be used vary similar to ShaderToy.
	Many of the gameplay reactive animations will use 
	this shader.
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

uniform float u_var[6];

void main()
{
	//memory layout
	//bg
	iResolution.x = 	u_var[0];		
	iResolution.y = 	u_var[1];		
	iMouse.x = 			u_var[2];
	iMouse.y = 			u_var[3];
	iTime = 			u_var[4];
	iFrequency = 		u_var[5];
	gl_Position = vec4(0.0f ,0.0f, 1.0f, 1.0f);
}







