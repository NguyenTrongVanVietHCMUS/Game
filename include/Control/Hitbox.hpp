#pragma once 
#include <Book/Utility.hpp>


class Hitbox
{
public:
    Hitbox(); // Constructor with default position
    ~Hitbox();
    sf::FloatRect hitbox; // Hitbox of the entity
    bool isColliding(const Hitbox& other) const;
    void update(sf::Time dt);
};