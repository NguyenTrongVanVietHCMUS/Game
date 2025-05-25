#include<Control/Hitbox.hpp>


Hitbox::Hitbox() : hitbox(0, 0, 50, 50) // Initialize hitbox with default size
{
    // Constructor implementation
}
Hitbox::~Hitbox()
{
    // Destructor implementation
}
bool Hitbox::isColliding(const Hitbox& other) const
{
    // Check for collision using SFML's FloatRect::intersects method
    return hitbox.intersects(other.hitbox);
}
// Note: The velocity member variable should be defined in the Entity class