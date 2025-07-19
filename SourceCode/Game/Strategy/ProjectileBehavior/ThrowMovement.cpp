#include <Book/Strategy/ProjectileBehavior.hpp>
#include <Book/Strategy/CollisionBehavior.hpp>
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
        auto proj = new Projectile2(
            "Explosion",
            0.45f, // as seconds
            projectile.position,
            Worldmap,
            "Media/Assets/Projectiles/sword_slash.png", // Path to the projectile texture
            nullptr, // No movement for melee
            std::make_unique<MeleeCollisionBehavior>(Worldmap), // Melee collision behavior
            nullptr
        );

        sf::Texture* texture = new sf::Texture();
        if(!texture->loadFromFile("Media/Assets/Projectiles/image.png")) {
            throw std::runtime_error("Failed to load explosion texture");
        }
        std::unique_ptr<MovingAnimation> movingAnimation = std::make_unique<Explosion_Animation>(
            texture,
            sf::Vector2u(3,3), // Assuming the explosion texture has 4x2 frames
            0.05f, // Switch time for the animation
            projectile.position, 
            2.0f, // Scale of the animation
            sf::Vector2f(0.5f, 0.5f) // Middle position for the animation
        );
        proj->setMovingAnimation(std::move(movingAnimation));
        proj->update(sf::seconds(0)); // Initialize the projectile's animation
        Worldmap->pushEntity(proj);
        return;
    }

    projectile.updateHitboxOnPosition(); // Update the hitbox position based on the new position
}