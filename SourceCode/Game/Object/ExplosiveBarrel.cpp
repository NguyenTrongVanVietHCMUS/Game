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
    if (entity->type == Entity::Type::EnemyProjectile || entity->type == Entity::Type::AllyProjectile || entity->type == Entity::Type::Projectile)
    {
        if(CurrentMap)
        {
            Projectile2* explosion = projLoader->LoadProjectile("Explosion basic", getPosition(), entity->getPosition());
            explosion->type = Entity::Type::Projectile;
            CurrentMap->pushEntity(explosion);
            CurrentMap->popEntityNoDelete(this);
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