#pragma once 
#include <Book/Utility.hpp>

class Hitbox :public sf::Drawable
{
private : 
    bool intersect(float l, float r, float t, float p)const
    {
        assert(l <= r && t <= p); 
        return std::max(l, t) < std::min(r, p);
    }
public:
    Hitbox(); // Constructor with default position
    Hitbox(sf::FloatRect rect) : hitbox(rect) {} // Constructor with a rectangle
    ~Hitbox();
    sf::FloatRect hitbox; // Hitbox of the entity
    void print()const;
    bool isCollide(const Hitbox& other) const;
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
    void extend(float len);
}; 