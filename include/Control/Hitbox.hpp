#pragma once 
#include <Book/Utility.hpp>


class Hitbox
{
public:
    Hitbox(); // Constructor with default position
    Hitbox(sf::FloatRect rect) : hitbox(rect) {} // Constructor with a rectangle
    ~Hitbox();
    sf::FloatRect hitbox; // Hitbox of the entity
    bool isColliding(const Hitbox& other) const;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const; // Draw the hitbo
    void update(sf::Time dt);
};