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

    sprite.setPosition(getPosition()); // Update the sprite position to match the projectile's position

    for (const auto& effect : trailStrategies) {
        effect->apply(*this);
    }
    
    updateHitboxOnPosition(dt);
    // Handle collision if a collision strategy is set
    return true;
}

void Projectile2::collide(const Entity* other)
{
    if (collisionStrategy) {
        sf::Vector2f collisionPoint = this->getPosition(); // Assuming the collision point is the projectile's position
        collisionStrategy->collide(*this, other);
    }
}

void Projectile2::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    hitbox.draw(target, states); // Draw the hitbox for debugging purposes
    target.draw(sprite, states);
}