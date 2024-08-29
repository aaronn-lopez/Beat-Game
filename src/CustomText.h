#pragma once
#include <SFML/Graphics.hpp>
#include "Math/vec.h"



/**
 * @brief This is a class wrapper for sf::Text used to adjust the Coordinate 
 * System to fit any resolution. This class is especially useful in making 
 * UI.
 * @note
 * Coordinate System is changed to range from [-100, 100] 
 * regardless of resolution
 */
class CustomText : public sf::Text
{
    inline static vec2 resolution;
    inline static unsigned int font_size;
private:
    using sf::Text::setPosition;
    using sf::Text::setScale;
    using sf::Text::setCharacterSize;
    using sf::Text::getScale;
    using sf::Text::getPosition;
private:
    inline static sf::Vector2u  current_res;
    sf::Vector2u                old_res;
public:

    //This Function is automatically called when draw(text) is called and 
    //resizes the font size to the desired resolution
    //
    //setCharacterSize() is only called when resolution does not equal 
    //the previous set resolution.
    void on_resize();
public:

    //Globally adjust the resolution for all CustomText Objects.
    // 
    //Function is automatically called when resolution changes.
    static void set_resolution(const sf::Vector2u& res);

    /**
    * set the scale 
    * \n
    * default is (0, 0)
    * @param scale scales the (x, y) 
    */
    void set_scale(const vec2& scale);
    
    /**
     * get the scale of the text
     * \n
     * @return vec2(x , y)
     */
    vec2 get_scale() const;



    
    /**
     * \brief Set the "Text" position with the 
     * Origin set to the middle of "Text" making it 
     * ideal for Centered UI
     * @note
     * Coordinate System ranges from [-100, 100] 
     * \param position
     */
    void set_position_centered(vec2 position);



    /**
     * \brief Set the "Text" position with the
     * Origin set to the Top Left of "Text" making it 
     * ideal for UI that requires alignment
     * @note
     * Coordinate System ranges from [-100, 100] 
     * 
     * \param position
     */
    void set_position(vec2 position);

};

