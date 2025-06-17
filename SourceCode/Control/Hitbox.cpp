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

void Hitbox::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // Draw the hitbox as a rectangle (for debugging purposes)
    sf::RectangleShape rectangle(sf::Vector2f(hitbox.width, hitbox.height));
    rectangle.setPosition(hitbox.left, hitbox.top);
    rectangle.setFillColor(sf::Color(255, 0, 0, 100)); // Semi-transparent red color
    target.draw(rectangle, states);
}

// Note: The velocity member variable should be defined in the Entity class

void Hitbox::update(sf::Sprite const & sprite)
{
    // Update the hitbox size based on the sprite's texture size
    if (sprite.getTexture())
    {
        hitbox.width = static_cast<float>(sprite.getTexture()->getSize().x);
        hitbox.height = static_cast<float>(sprite.getTexture()->getSize().y);
    }
    // Set the position of the hitbox to match the sprite's position
    hitbox.left = sprite.getPosition().x - hitbox.width / 2;
    hitbox.top = sprite.getPosition().y - hitbox.height / 2;
}