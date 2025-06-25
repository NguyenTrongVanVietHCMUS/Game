#include<Control/Hitbox.hpp>


Hitbox::Hitbox() : hitbox(0, 0, 50, 50) // Initialize hitbox with default size
{
    // Constructor implementation
}
Hitbox::~Hitbox()
{
    // Destructor implementation
}
bool Hitbox::isColliding(Hitbox& other) 
{
    return hitbox.intersects(other.hitbox);
}

void Hitbox::draw(sf::RenderTarget& target, sf::RenderStates states) const 
{
    // Draw the hitbox as a rectangle shape for visualization
    sf::RectangleShape shape(sf::Vector2f(hitbox.width, hitbox.height));
    shape.setPosition(hitbox.left, hitbox.top);
    shape.setFillColor(sf::Color(255, 0, 0, 128)); // semi-transparent red for visibility
    target.draw(shape, states); // Draw the hitbox shape
}


// Note: The velocity member variable should be defined in the Entity class
