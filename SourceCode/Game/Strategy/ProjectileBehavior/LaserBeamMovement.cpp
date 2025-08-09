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
        }
    }
}
