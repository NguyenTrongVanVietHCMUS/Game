#include <Object/Chest/Barrel.hpp>
#include <Book/InteractingAnimation/BarrelAnimation.hpp>

Barrel::Barrel(sf::Vector2f position, Hitbox hitbox, float scalex, float scaley) 
    : Object("Barrel", position, hitbox, scalex, scaley)
{
    type = Entity::Type::Object;
    interactingAnimation = std::make_unique<BarrelAnimation>(
        this, scalex, scaley, "Media/Assets/TileSets/Objects/barrel.png"
    );
}

void Barrel::collide(Entity* entity)
{
    if (entity->type == Entity::Type::EnemyProjectile || entity->type == Entity::Type::AllyProjectile || entity->type == Entity::Type::Projectile)
    {
        isActive = true;
    }
}

void Barrel::setMap(State* map)
{
    CurrentMap = map;
    isActive = false;
}


bool Barrel::update(sf::Time dt)
{
    if (isActive)
    {
        if(CurrentMap)
        {
            CurrentMap->popEntityNoDelete(this);
        }
    }
    return true;
}