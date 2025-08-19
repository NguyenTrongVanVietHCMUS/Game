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

void ExplosiveBarrel::collide(Entity* entity)
{
    if (entity->type == Entity::Type::EnemyProjectile || entity->type == Entity::Type::AllyProjectile || entity->type == Entity::Type::Projectile)
    {
        isActive = true;
    }
}

void ExplosiveBarrel::setMap(State* map)
{
    CurrentMap = map;
    projLoader = new ProjectileLoader(map); 
    isActive = false;
}

ExplosiveBarrel::~ExplosiveBarrel()
{
    if (projLoader) {
        delete projLoader; // Clean up the projectile loader
    }
}

bool ExplosiveBarrel::update(sf::Time dt)
{
    if (isActive)
    {
        if(CurrentMap)
        {
            Projectile2* explosion = projLoader->LoadProjectile("Explosion Barrel", getPosition(), getPosition() + sf::Vector2f(0.5f,0.5f));
            explosion->type = Entity::Type::Projectile;
            CurrentMap->pushEntity(explosion);
            CurrentMap->popEntityNoDelete(this);
        }
    }
    return true;
}