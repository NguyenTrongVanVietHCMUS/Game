#include <Book/Ally.hpp>
#include<Book/AIAlly.hpp>
Ally::Ally(
    std::string name,
    sf::Vector2f position,
    Entity* owner 
) :Entity(name, position)
{
    type = Entity::Type::Ally; // Set the type of the ally
    this->owner = owner;
}
Entity* Ally::getOwner()const
{
    return owner;  
}
Ally::~Ally()

{
    // Destructor logic if needed
}
void Ally::collide(Entity* other)
{
    if (attributes.isDeath())
        return; // If the ally is dead, do not handle collisions
    movingAnimation->handleCollision(other);

}
void Ally::update(Entity* target, sf::Time dt)
{
    if (attributes.isDeath())
    {
        movingAnimation->setState(MovingAnimation::State::DEATH);
        movingAnimation->update(dt); // Update the death animation
        inventory->update(dt); // Update the inventory
    }
    else
    {
        aiAlly->update(this, target, dt);
        elapseDeathTime = 0.0f;
    }

}
void Ally::chase(Entity* target, sf::Time dt)
{
    movingAnimation->chase(target, dt);
    inventory->AimAt(position - sf::Vector2f(0, 100));
    inventory->update(dt);
}
void Ally::wander(sf::Time dt)
{
    movingAnimation->wander(dt);
    inventory->AimAt(position - sf::Vector2f(0, 100)); // Aim at the middle position of the moving animation
    inventory->update(dt);
}
void Ally::shoot(Entity* target, sf::Time dt)
{
    inventory->shoot(this, target);
    inventory->update(dt);
}

std::string Ally::getCurrentWeaponName() const
{
    return inventory->getCurrentWeaponName();
}

void Ally::SwitchWeapon()
{
    inventory->SwitchRandomWeapon();
}

bool Ally::isAllowClean()
{
    return false;
}

bool Ally::isDeath()
{
    return attributes.isDeath();
}

void Ally::takeDamage(int damage)
{

    attributes.TakeDamage(damage);
    if (isDeath()) {
        movingAnimation->setState(MovingAnimation::State::DEATH);
        movingAnimation->update(sf::seconds(0));
    }
}

void Ally::knockBack(sf::Vector2f force)
{
    movingAnimation->Knockback(force);
}

void Ally::knockBack(const Projectile2* projectile, float Force, Entity* other)
{
    movingAnimation->Knockback(projectile, Force, other);
}

void Ally::teleport(sf::Vector2f position)
{
    movingAnimation->teleport(position);
}