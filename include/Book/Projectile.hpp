#pragma once
#include <iostream>
#include <Book/Utility.hpp>

// interface for a projectile class
class Projectile
{
public:
    virtual void update(sf::Time dt) = 0;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
    virtual void handleEvent(const sf::Event& event) = 0;
    
    Projectile(sf::Vector2f position, sf::Vector2f velocity, float speed, float damage, float lifetime, EntityType entityType)
        : position(position), velocity(velocity), speed(speed), damage(damage), lifetime(lifetime), elapsedTime(0.0f), entityType(entityType){}
    virtual ~Projectile() = default;
    bool isFlagDestruct();
protected:
    Projectile() = default;
    sf::Vector2f position; // Position of the projectile
    sf::Vector2f velocity; // Velocity of the projectile
    float speed; // Speed of the projectile
    float damage; // Damage dealt by the projectile
    float lifetime; // Lifetime of the projectile
    float elapsedTime; // Time elapsed since the projectile was created
    EntityType entityType; // Type of the entity that fired the projectile
    sf::Sprite sprite; // Sprite representing the projectile
    sf::Texture texture; // Texture for the projectile sprite
    virtual void selfDestruct() { isSelfDestructed = true; } // virtual function to handle self-destruction logic

private:
    bool isSelfDestructed = false; // Flag to indicate if the projectile is marked for self-destruction
};
