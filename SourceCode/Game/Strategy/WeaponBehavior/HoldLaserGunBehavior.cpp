#include<Book/Strategy/WeaponBehavior.hpp>
#include<Control/WeaponLoader.hpp>
#include<Control/ProjectileLoader.hpp>

void HoldLaserGunBehavior::activate(Weapon2& self, Entity* target) {
    // Get the spawn position of the laser gun
    sf::Vector2f SpawnPosition = self.GetProjectileSpawnPosition();
    // Get the target position
    Projectile2* proj = ProjectileLoader(Worldmap).LoadProjectile("Laser Beam", SpawnPosition, target->position);
    proj->setMovement(std::make_unique<HoldLaserBeamMovement>(0.1f, self, Worldmap));
    proj->type = self.ProjectileTypeTransform(target); // Transform the projectile type based on the target type

    Worldmap->pushEntity(proj);
}