#include "Object/Projectiles/Bullet.hpp"

Bullet::Bullet(std::string name, const sf::Vector2f& position, const sf::Vector2f& direction, float speed, float damage)
    :Projectile(name, position, direction, speed, damage, 5.0f, EntityType::EntityType_Ally)
{
    std::cerr << "Get speed : " << this->speed << ' ' << speed << '\n';
    // Load the texture and set the sprite
    if (!texture.loadFromFile("Media/Assets/Projectiles/PurpleBullet.png")) {
        throw std::runtime_error("Failed to load bullet texture");
    }
    // Scaling texture to size of 64x64 pixels
    texture.setSmooth(true); // Enable smooth scaling if needed
    texture.setRepeated(false); // Disable repeating if not needed


    // Set the sprite properties
    sprite.setTexture(texture);
    sprite.setPosition(position);
    
    sprite.setOrigin(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f); // Set origin to center of the sprite
    //sprite.setScale(0.5f, 0.5f); // Scale the sprite to half its size
}

bool Bullet::update(const sf::Time &dt)
{
    // Normalize the direction vector to speed up the bullet
    velocity = velocity / std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y) * speed;
    // Update the bullet's position based on its velocity
    position += velocity * dt.asSeconds();
    elapsedTime += dt.asSeconds();

    // Update the sprite's position
    sprite.setPosition(position);

    // Update the sprite's rotation based on the direction
    float angle = std::atan2(velocity.y, velocity.x) * 180 / 3.14159f; // Convert radians to degrees
    // Rotate 180 degrees to match the sprite's default orientation
    angle += 180.0f; // Adjust the angle to match the sprite's orientation
    
    sprite.setRotation(angle);

    // Check if the bullet has exceeded its lifetime
    if (elapsedTime >= lifetime)
    {
        // Mark the bullet for removal
        std::cerr << elapsedTime << ' ' << lifetime << " Check the life time of projectile\n";
        selfDestruct();
    }
    hitbox.update(sprite); // Update the hitbox based on the sprite's position and size
    return true;
}

void Bullet::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // Debug position
    hitbox.draw(target, states); // Draw the hitbox for debugging purposes
    target.draw(sprite, states);
}

bool Bullet::handleEvent(const sf::Event& event, sf::RenderWindow* window)
{
    // Handle events specific to the bullet
    return true;
}
