#include<Book/Strategy/WeaponBehavior.hpp>
#include<Control/ProjectileLoader.hpp>
void MeleeWeaponBehavior::activate(Weapon2& self, Entity* target) {
    ProjectileLoader projectileLoader(Worldmap);
    float posX = self.getStat("TargetPosX");
    float posY = self.getStat("TargetPosY");

    // normalize the direction vector
    sf::Vector2f SpawnerPosition = self.GetProjectileSpawnPosition();
    sf::Vector2f direction = target->position - sf::Vector2f(posX, posY);
    float Angle = std::atan2(direction.y, direction.x); // Calculate the angle of the melee attack
    Projectile2 *proj;
    try {
        proj = projectileLoader.LoadProjectile(
        ProjectileName,
        SpawnerPosition, 
        sf::Vector2f(SpawnerPosition + direction) // Set the target position for the projectile
    );
    } catch (const std::exception& e) {
        std::cerr << "Error creating projectile: " << e.what() << std::endl;
        return; // Exit if projectile creation fails
    }
    
    proj->type = self.ProjectileTypeTransform(target); // Transform the projectile type based on the target type
    proj->updateHitboxOnPosition(); // Update the hitbox position based on the entity's current position
    proj->update(sf::seconds(0)); // Initialize the projectile's animation
    Worldmap->pushEntity(proj);
} 