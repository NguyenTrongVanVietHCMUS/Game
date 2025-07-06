#include <Book/Projectile2.hpp>

void Projectile2::setBehavior(std::unique_ptr<IMovement> movement, std::unique_ptr<ICollision> collision)
{
    if (movement) {
        movementStrategy = std::move(movement);
    }
    if (collision) {
        collisionStrategy = std::move(collision);
    }
}

void Projectile2::setMovement(std::unique_ptr<IMovement> movement)
{
    if (movement) {
        movementStrategy = std::move(movement);
    }
}

void Projectile2::setCollision(std::unique_ptr<ICollision> collision)
{
    if (collision) {
        collisionStrategy = std::move(collision);
    }
}

void Projectile2::addTrailEffect(std::unique_ptr<IEffect> effect)
{
    if (effect) {
        trailStrategies.push_back(std::move(effect));
    }
}

bool Projectile2::update(const sf::Time& dt)
{
    if (movementStrategy) {
        movementStrategy->update(*this, dt);
    }

    for (const auto& effect : trailStrategies) {
        effect->apply(*this);
    }

    // Handle collision if a collision strategy is set
    if (collisionStrategy) {
        // Assuming we have a method to get the collision point
        sf::Vector2f collisionPoint; // This should be set based on your collision detection logic
        collisionStrategy->collide(*this, collisionPoint);
    }
    return true;
}

void Projectile2::collide(const Entity* other)
{
    if (collisionStrategy) {
        sf::Vector2f collisionPoint = this->getPosition(); // Assuming the collision point is the projectile's position
        collisionStrategy->collide(*this, collisionPoint);
    }
}