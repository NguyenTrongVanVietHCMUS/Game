#include<Book/Strategy/ProjectileBehavior.hpp>
#include<Control/ProjectileLoader.hpp>
void LaserAimMovement::update(Projectile2& projectile, const sf::Time& dt) {
    // Aim the laser at the target
    elapsedTime += dt.asSeconds();
    projectile.HitboxMode = false;
    if (elapsedTime >= aimTime) {
        // Logic for when the laser beam is ready to fire
        aimTime = 1000000.0f;
        elapsedTime = 0.0f; // Reset the timer
        Projectile2* proj = ProjectileLoader(Worldmap).LoadProjectile("Laser Beam", startPosition, endPosition);
        proj->type = projectile.type;
        proj->update(sf::seconds(0)); // Initialize the projectile's animation
        Worldmap->pushEntity(proj); // Add the laser beam to the world map
    }
}