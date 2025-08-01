#include<Book/Strategy/WeaponBehavior.hpp>
void RangedWeaponBehavior::activate(Weapon2& self, Entity* target){
        float posX = self.getStat("TargetPosX");
        float posY = self.getStat("TargetPosY");
        // normalize the direction vector
        sf::Vector2f SpawnPosition = self.GetProjectileSpawnPosition();
        sf::Vector2f direction =  sf::Vector2f(posX, posY) - SpawnPosition;

        //std::cerr << "Projectile speed X: " << projectileSpeedX << ", Y: " << projectileSpeedY << std::endl;
        float offsetAngle = dist(rng); // Randomly offset the angle within the spread range
        float cosA = std::cos(offsetAngle * 3.14159265358979323846f / 180.0f); // Convert angle to radians
        float sinA = std::sin(offsetAngle * 3.14159265358979323846f / 180.0f); // Convert angle to radians
        sf::Vector2f RotatedDirection(
            direction.x * cosA - direction.y * sinA,
            direction.x * sinA + direction.y * cosA
        );
        float len = std::sqrt(RotatedDirection.x * RotatedDirection.x + RotatedDirection.y * RotatedDirection.y);
        float projectileSpeedX = projectileSpeed * (RotatedDirection.x / len),
              projectileSpeedY = projectileSpeed * (RotatedDirection.y / len);

        auto proj = projectile->clone(sf::Vector2f(projectileSpeedX, projectileSpeedY));
        proj->position = SpawnPosition; // Set the projectile's position to the spawn position
        std::cerr << "Spawn Bullet\n";
        proj->type = self.ProjectileTypeTransform(target); // Transform the projectile type based on the target type
        proj->update(sf::seconds(0)); // Initialize the projectile's animation
        Worldmap->pushEntity(proj);
    }