#include "CustomText.h"


CustomText::CustomText() : mesh(Mesh()), font_size(64)
{

}
void CustomText::set_font(sf::Font& font, unsigned int font_size)
{
    this->font_size = font_size;
    struct GlyphData
    {
        sf::Vector2i position;
        sf::Vector2i size;
    };
    std::array<GlyphData, Letter_count> glyph_data;
    for(int i = Start; i<= End; i++)
    {
        sf::Glyph glyph = font.getGlyph(i, font_size, 0, 0);
        glyph_data[i - Start].position = glyph.textureRect.getPosition();
        glyph_data[i - Start].size = glyph.textureRect.getSize(); 
    }
    font_bitmap = font.getTexture(font_size);
}
void CustomText::draw()
{
    sf::Texture::bind(&font_bitmap);
}