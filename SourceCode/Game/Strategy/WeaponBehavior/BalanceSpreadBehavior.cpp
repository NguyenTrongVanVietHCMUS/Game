#include <Book/Strategy/WeaponBehavior.hpp>
#include <Control/ProjectileLoader.hpp>
#include <Book/Projectile2.hpp>
void BalanceSpreadBehavior::activate(Weapon2& self, Entity* target) {
    // Implement the behavior for balancing spread shots
    float deltaAngle = 360.0f / numBullet;
    float posX = self.getStat("TargetPosX");
    float posY = self.getStat("TargetPosY");
    // Get current angle base on posx and posy
    sf::Vector2f SpawnPosition = self.GetProjectileSpawnPosition();
    float CurrentAngle = std::atan2(posY - SpawnPosition.y, posX - SpawnPosition.x) * 180.0f / 3.14159f;

    for (int i = 0; i < numBullet; ++i) {
        // Cast a small line base on CurrentAngle
        sf::Vector2f EndPosition = SpawnPosition + sf::Vector2f(std::cos(CurrentAngle * 3.14159f / 180.0f), std::sin(CurrentAngle * 3.14159f / 180.0f));
        Projectile2* proj = ProjectileLoader(Worldmap).LoadProjectile(ProjectileName, SpawnPosition, EndPosition);
        CurrentAngle += deltaAngle;
        proj->type = self.ProjectileTypeTransform(target);
        Worldmap->pushEntity(proj);
    }
}