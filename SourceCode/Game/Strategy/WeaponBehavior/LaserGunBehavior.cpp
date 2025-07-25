#include<Book/Strategy/WeaponBehavior.hpp>
#include<Control/Raycaster.hpp>
void laserGunBehavior::activate(Weapon2& self, Entity* target) {
    // Get the spawn position of the laser gun
    sf::Vector2f SpawnPosition = self.GetProjectileSpawnPosition();
    
    // Get the target position
    float posX = self.getStat("TargetPosX");
    float posY = self.getStat("TargetPosY");
    
    // Calculate the direction vector towards the target
    sf::Vector2f direction = sf::Vector2f(posX, posY) - SpawnPosition;
    Raycaster raycaster(Worldmap);
    RaycastHit raycast = raycaster.cast(SpawnPosition, direction, 2000.0f); // Cast a ray from the spawn position towards the target
    if(raycast.entity)
    {
        std::cerr << "Laser hit entity: " << raycast.entity->name << " at position: " << raycast.position.x << ", " << raycast.position.y << std::endl;
        
        auto proj = new Projectile2(
            "RangedProjectile",
            15.0f, // as seconds represent life time of the projectile
            target->position,
            Worldmap,
            "Media/Assets/Projectiles/Laser.png", // Path to the projectile texture
            nullptr,
            nullptr
        );
        std::cerr << "Creating laser aim animation.\n";
        std::unique_ptr<MovingAnimation> animation = std::make_unique<laserAimAnimation>
        (
            SpawnPosition, 
            raycast.position, 
            sf::Vector2f(0.5f, 0.5f), 
            proj->position  
        );
        proj->setMovingAnimation(std::move(animation));
        proj->type = self.ProjectileTypeTransform(target); // Transform the projectile type based on the target type
        proj->update(sf::seconds(0));
        Worldmap->pushEntity(proj);
        
    } else std::cerr << "Laser did not hit any entity." << std::endl;
}