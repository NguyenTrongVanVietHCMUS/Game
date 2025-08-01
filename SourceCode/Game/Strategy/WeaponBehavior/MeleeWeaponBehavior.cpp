#include<Book/Strategy/WeaponBehavior.hpp>
#include<Control/ProjectileLoader.hpp>
void MeleeWeaponBehavior::activate(Weapon2& self, Entity* target) {
    ProjectileLoader projectileLoader(Worldmap);
    float posX = self.getStat("TargetPosX");
    float posY = self.getStat("TargetPosY");

    // normalize the direction vector
    sf::Vector2f SpawnerPosition = self.GetProjectileSpawnPosition();
    sf::Vector2f direction = SpawnerPosition - sf::Vector2f(posX, posY);
    float Angle = std::atan2(direction.y, direction.x); // Calculate the angle of the melee attack
    // Offset the position of the projectile to be in front of the target
    sf::Vector2f offset(25.0f * std::cos(Angle), 25.0f * std::sin(Angle)); // Offset by 50 pixels in the direction of the attack
    Projectile2 *proj;
    try {
        proj = projectileLoader.LoadProjectile(
        ProjectileName,
        SpawnerPosition + offset, // Set the projectile's position to the spawn position with offset
        sf::Vector2f(SpawnerPosition.x + offset.x * 2, SpawnerPosition.y + offset.y * 2) // Set the target position for the projectile
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