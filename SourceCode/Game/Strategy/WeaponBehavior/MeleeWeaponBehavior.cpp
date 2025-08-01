#include<Book/Strategy/WeaponBehavior.hpp>

void MeleeWeaponBehavior::activate(Weapon2& self, Entity* target) {
    sf::Texture* texture = new sf::Texture();
    if(!texture->loadFromFile("Media/Assets/Projectiles/sword_slash.png")) {
        throw std::runtime_error("Failed to load melee projectile texture");
    }
    float posX = self.getStat("TargetPosX");
    float posY = self.getStat("TargetPosY");

    // normalize the direction vector
    sf::Vector2f SpawnerPosition = self.GetProjectileSpawnPosition();
    sf::Vector2f direction = SpawnerPosition - sf::Vector2f(posX, posY);
    float Angle = std::atan2(direction.y, direction.x); // Calculate the angle of the melee attack
    // Offset the position of the projectile to be in front of the target
    sf::Vector2f offset(25.0f * std::cos(Angle), 25.0f * std::sin(Angle)); // Offset by 50 pixels in the direction of the attack

    auto proj = new Projectile2(
        "MeleeProjectile",
        0.12f, // as seconds
        SpawnerPosition,
        Worldmap,
        "Media/Assets/Projectiles/sword_slash.png", // Path to the projectile texture
        nullptr, // No movement for melee
        std::make_unique<MeleeCollisionBehavior>(Worldmap), // Melee collision behavior
        nullptr
    );
    proj->position -= offset; // Set the position of the projectile to be in front of the target
    std::unique_ptr<MovingAnimation> movingAnimation = std::make_unique<SlashProjectile_MovingAnimation>(
        texture, 
        sf::Vector2u(3, 1), 
        0.04f, // Switch time for the animation
        proj->position, 
        5.0f, // Scale of the animation
        Angle,
        sf::Vector2f(0.5f, 0.5f) // Middle position for the animation
    );
    proj->type = self.ProjectileTypeTransform(target); // Transform the projectile type based on the target type
    proj->updateHitboxOnPosition(); // Update the hitbox position based on the entity's current position
    proj->setMovingAnimation(std::move(movingAnimation));
    proj->update(sf::seconds(0)); // Initialize the projectile's animation
    Worldmap->pushEntity(proj);
} 