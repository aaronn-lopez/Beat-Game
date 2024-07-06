#version 460 core




out vec4 fragColor;

in vec2 UV;
in float iTime;
in vec3 color;

float sdStar5(in vec2 p, in float r, in float rf)
{
    const vec2 k1 = vec2(0.809016994375, -0.587785252292);
    const vec2 k2 = vec2(-k1.x,k1.y);
    p.x = abs(p.x);
    p -= 2.0*max(dot(k1,p),0.0)*k1;
    p -= 2.0*max(dot(k2,p),0.0)*k2;
    p.x = abs(p.x);
    p.y -= r;
    vec2 ba = rf*vec2(-k1.y,k1.x) - vec2(0,1);
    float h = clamp( dot(p,ba)/dot(ba,ba), 0.0, r );
    return length(p-ba*h) * sign(p.y*ba.x-p.x*ba.y);
}

void main()
{
    //star
    float d= sdStar5(UV, iTime, 0.5);

	float dis = 1-length(UV);
	dis = 1-smoothstep(0.5,1,length(UV));

    //circle
	//float d = length(UV);
	//d= sin(2*d-2.5*iTime)/2;

	d = abs(d);
	d = 0.02/d;
	fragColor = vec4(color, d*dis*(1-iTime));
}