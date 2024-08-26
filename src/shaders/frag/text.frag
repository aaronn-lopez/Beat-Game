#version 410 core
//Frag


in vec2 texCoord;
uniform sampler2D tex0;

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
	fragColor = texture(tex0, vec2(texCoord.x, 1 - texCoord.y));
}