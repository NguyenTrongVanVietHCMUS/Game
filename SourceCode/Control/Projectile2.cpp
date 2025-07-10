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

void Projectile2::setMovingAnimation(std::unique_ptr<MovingAnimation> animation)
{
    if (animation) {
        movingAnimation = std::move(animation);
    }
}

void Projectile2::setAttribute(const std::string& attributeName, float value)
{
    attributes[attributeName] = value;
}

float Projectile2::getAttribute(const std::string& attributeName) const
{
    auto it = attributes.find(attributeName);
    if (it != attributes.end()) {
        return it->second;
    }
    return 0.0f; // Default value if attribute not found
}

bool Projectile2::update(const sf::Time& dt)
{
    float CurrentLifeTime = getAttribute("CurrentLifeTime");
    CurrentLifeTime += dt.asSeconds(); // Increment the current lifetime by the delta time
    float MaxLifeTime = getAttribute("MaxLifeTime");
    if (CurrentLifeTime >= MaxLifeTime) {

        // Projectile has reached its maximum lifetime, handle destruction
        currentMap->popEntity(this); // Remove the projectile from the map
        return true; // Indicate that the projectile should be removed
    }
    if (movementStrategy) {
        movementStrategy->update(*this, dt);
    }

    sprite.setPosition(getPosition()); // Update the sprite position to match the projectile's position

    for (const auto& effect : trailStrategies) {
        effect->apply(*this);
    }
    setAttribute("CurrentLifeTime", CurrentLifeTime); // Update the current lifetime attribute
    if (movingAnimation) {
        movingAnimation->update(dt); // Update the moving animation if it exists
    }
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
    if(movingAnimation) {
        movingAnimation->draw(target, states); // Draw the moving animation if it exists
        hitbox.draw(target, states); //Draw the hitbox for debugging purposes
    } else {
        hitbox.draw(target, states); // Draw the hitbox for debugging purposes
        target.draw(sprite, states);  
        
    }
     
}