#include<Book/Strategy/ProjectileBehavior.hpp>
#include<Control/Raycaster.hpp>
#include<set>
void LaserBeamMovement::update(Projectile2& projectile, const sf::Time& dt) {
    elapsedTime += dt.asSeconds();
    projectile.HitboxMode = false;
    
    if(elapsedTime >= HitCycle) {
        elapsedTime = 0;
        Raycaster raycaster(Worldmap);
        std::set<Entity*> hitEntities = raycaster.castGetEntities(startPosition, endPosition);

        for(Entity* entity : hitEntities) {
            entity->collide(&projectile);
            if(entity->type == Entity::Type::Enemy && projectile.type == Entity::Type::AllyProjectile) {
                // Apply damage to the entity
                int damage = static_cast<int>(projectile.getAttribute("Damage"));
                entity->takeDamage(damage);
            } else if(entity->type == Entity::Type::Ally && projectile.type == Entity::Type::EnemyProjectile) {
                // Apply damage to the entity
                int damage = static_cast<int>(projectile.getAttribute("Damage"));
                entity->takeDamage(damage);
            }
        }
    }
}
