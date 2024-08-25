#version 410 core
//Frag



out vec4 fragColor;
//========fragment variables========
//Resolution
in vec2 iResolution;			
//Mouse screen position
in vec2 iMouse;			
//Global Time and sound frequency
in float iTime;	
in float iFrequency;	
//===================================
void main()
{
	vec3 color = vec3(1,0,0);	
	fragColor = vec4(color, 1.0f);	
}