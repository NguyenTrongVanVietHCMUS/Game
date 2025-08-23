#include<Book/Strategy/ProjectileBehavior.hpp>
#include<Control/Raycaster.hpp>
#include<set>
void HoldLaserBeamMovement::update(Projectile2& projectile, const sf::Time& dt)
{
    elapsedTime += dt.asSeconds();
    projectile.HitboxMode = false;
    float posX = weapon.getStat("TargetPosX");
    float posY = weapon.getStat("TargetPosY");
    
    if(elapsedTime >= aimTime)
    {
      
        elapsedTime = 0;
        // If the weapon is set, use its direction
        Raycaster raycaster(Worldmap);
    sf::Vector2f spawnPosition = weapon.GetProjectileSpawnPosition();
    RaycastHit raycast = raycaster.cast(spawnPosition, sf::Vector2f(posX, posY) - spawnPosition, 1000.0f);
        
        std::set<Entity*> hitEntities = raycaster.castGetEntities(spawnPosition, raycast.position);
        
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
        projectile.setAttribute("Start Position X", spawnPosition.x);
        projectile.setAttribute("Start Position Y", spawnPosition.y);
        projectile.setAttribute("End Position X", raycast.position.x);
        projectile.setAttribute("End Position Y", raycast.position.y);
    }
    
}
