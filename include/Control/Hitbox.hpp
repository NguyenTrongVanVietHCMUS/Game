#pragma once 
#include <Book/Utility.hpp>

class Hitbox:public sf::Drawable
{
public:
    Hitbox(); // Constructor with default position
    Hitbox(sf::FloatRect rect) : hitbox(rect) {} // Constructor with a rectangle
    ~Hitbox();
    sf::FloatRect hitbox; // Hitbox of the entity
    bool isColliding(Hitbox& other);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const ; // Draw the hitbox
};