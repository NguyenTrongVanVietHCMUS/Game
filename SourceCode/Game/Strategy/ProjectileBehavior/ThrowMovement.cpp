#include <Book/Strategy/ProjectileBehavior.hpp>
#include <Book/Strategy/CollisionBehavior.hpp>
#include <Control/ProjectileLoader.hpp>
void ThrowMovement::update(Projectile2& projectile, const sf::Time& dt)
{
    // Update the position of the projectile based on its speed and the elapsed time
    projectile.position.x += speedX * dt.asSeconds();
    projectile.position.y += speedY * dt.asSeconds();

    // Update the height of the projectile based on gravity
    CurrentHeight += heightVelocity * dt.asSeconds();
    heightVelocity -= gravity * dt.asSeconds(); // Apply gravity to height velocity
    projectile.setSpriteScale(OriginalScale + OriginalScale * HeightSpriteScale * CurrentHeight); // Scale the sprite based on the height scale
    // scale and offset the projectile's position base on the current height
    projectile.position.y -= heightVelocity * dt.asSeconds() * HeightScale;
    projectile.setSpriteRotation(CurrentRotation); // Update the rotation of the projectile
    CurrentRotation = (int)(CurrentRotation + RotationSpeed * dt.asSeconds()) % 360; // Update the rotation based on speedX
    projectile.setSpriteRotation(CurrentRotation); // Set the rotation of the sprite
    // If the projectile has fallen below its initial height, reset it
    if (CurrentHeight < 0.0f) {
        isActive = false; 
        auto proj = ProjectileLoader(Worldmap).LoadProjectile(
            "Explosion basic",
            projectile.getPosition(), 
            projectile.getPosition() + sf::Vector2f(speedX, speedY) // Set the target position for the explosion
        );
        proj->type = projectile.type; // Set the type of the projectile
        proj->update(sf::seconds(0)); // Initialize the projectile's animation
        Worldmap->pushEntity(proj);
        return;
    }

    projectile.updateHitboxOnPosition(); // Update the hitbox position based on the new position
}