#version 330 core

// The texture coordinates from the vertex shader
in vec2 fragTexCoords;

// The output color of the fragment
out vec4 fragColor;

// The texture containing the font glyphs
uniform sampler2D fontTexture;

// The text color passed from SFML
uniform vec4 textColor;


void main()
{
    // Sample the texture to get the alpha value of the glyph
    float alpha = texture(fontTexture, fragTexCoords).r;

    // Apply the text color and alpha blending
    fragColor = vec4(textColor.rgb, textColor.a * alpha);
}