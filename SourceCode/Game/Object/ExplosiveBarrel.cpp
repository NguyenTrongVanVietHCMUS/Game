#include <Object/Chest/ExplosiveBarrel.hpp>
#include <Book/InteractingAnimation/BarrelAnimation.hpp>

ExplosiveBarrel::ExplosiveBarrel(sf::Vector2f position, Hitbox hitbox, float scalex, float scaley) 
    : Object("ExplosiveBarrel", position, hitbox, scalex, scaley)
{
    type = Entity::Type::Object;
    interactingAnimation = std::make_unique<BarrelAnimation>(
        this, scalex, scaley, "Media/Assets/TileSets/Objects/BombBarrel.png"
    );
}

void ExplosiveBarrel::collide(const Entity* entity)
{
    if (entity->type == Entity::Type::EnemyProjectile || entity->type == Entity::Type::AllyProjectile)
    {
        if(CurrentMap)
        {
            Projectile2* allyProjectile = projLoader->LoadProjectile("Explosion basic", entity->getPosition(), this->getPosition());
            Projectile2* enemyProjectile = projLoader->LoadProjectile("Explosion basic", entity->getPosition(), this->getPosition());
            allyProjectile->type = Entity::Type::AllyProjectile;
            enemyProjectile->type = Entity::Type::EnemyProjectile;
            CurrentMap->pushEntity(allyProjectile);
            CurrentMap->pushEntity(enemyProjectile);
            CurrentMap->popEntity(this);
        }
    }
}

void ExplosiveBarrel::setMap(State* map)
{
    CurrentMap = map;
    projLoader = new ProjectileLoader(map); 
}

ExplosiveBarrel::~ExplosiveBarrel()
{
    if (projLoader) {
        delete projLoader; // Clean up the projectile loader
    }
}