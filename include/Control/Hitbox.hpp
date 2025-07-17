#pragma once 
#include <Book/Utility.hpp>

class Hitbox :public sf::Drawable
{
public:
    Hitbox(); // Constructor with default position
    Hitbox(sf::FloatRect rect) : hitbox(rect) {} // Constructor with a rectangle
    ~Hitbox();
    sf::FloatRect hitbox; // Hitbox of the entity

    bool isColliding(const Hitbox& other) const;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const; // Draw the hitbo
    void update(sf::Time dt);
    void update(const sf::Sprite& sprite); // Set the size of the hitbox based on 
    bool operator<(const Hitbox& other)const
    {
        return hitbox.top + hitbox.height < other.hitbox.top + other.hitbox.height || (
            hitbox.top + hitbox.height == other.hitbox.top + other.hitbox.height &&
            hitbox.left + hitbox.width < other.hitbox.left + other.hitbox.width
            );
    }
}; 