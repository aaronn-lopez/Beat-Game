#version 410 core
//Frag



out vec4 fragColor;
//========fragment variables========
in vec2 iResolution;			
in float iTime;	
in float iFrequency;	
in vec4 iColor;
in vec2 texCoord;
in vec2 iScale;
//===================================
in float CornerRadius;
in float OutlineThickness;

void main()
{
	vec4 color = iColor;
	float r = CornerRadius;
	vec2 uv = (texCoord*2) - vec2(1,1);
	//vec2 uv2 = uv;
	vec2 d = vec2(1,1) * iScale - r;
	uv = abs(uv) * iScale;
	if(uv.x > d.x && uv.y > d.y) 
	{
		if(length(uv - d) > r)
			discard;	
		if(length(uv - d) > r - OutlineThickness)
			color = vec4(iColor.rbg * 0.7f, iColor.a);		


	}
	vec2 line = vec2(1,1) * iScale - OutlineThickness;
	if(uv.x > line.x || uv.y > line.y)
		color = vec4(iColor.rbg * 0.7f, iColor.a);		

	//float distance = 0.1 + length(uv2);
	fragColor = vec4(clamp(color, 0, 1));	
}