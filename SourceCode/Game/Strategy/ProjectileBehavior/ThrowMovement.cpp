#include <Book/Strategy/ProjectileBehavior.hpp>

void ThrowMovement::update(Projectile2& projectile, const sf::Time& dt)
{
    // Update the position of the projectile based on its speed and the elapsed time
    projectile.position.x += speedX * dt.asSeconds();
    projectile.position.y += speedY * dt.asSeconds();

    // Update the height of the projectile based on gravity
    CurrentHeight += heightVelocity * dt.asSeconds();
    heightVelocity -= gravity * dt.asSeconds(); // Apply gravity to height velocity
    // scale and offset the projectile's position base on the current height
    projectile.position.y += heightVelocity * dt.asSeconds();
    // If the projectile has fallen below its initial height, reset it
    if (CurrentHeight < 0.0f) {
        CurrentHeight = 0.0f;
        heightVelocity = initialHeight; // Reset height velocity
    }

    projectile.updateHitboxOnPosition(); // Update the hitbox position based on the new position
}