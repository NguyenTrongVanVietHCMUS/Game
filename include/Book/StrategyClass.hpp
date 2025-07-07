#pragma once
#include <Book/Utility.hpp>
#include <Book/Entity.hpp>
class Projectile2;
class Weapon2;
struct IMovement
{
    virtual void update(Projectile2& projectile, const sf::Time& dt) = 0;
    virtual std::unique_ptr<IMovement> clone() const = 0;
    virtual ~IMovement() = default;
};

struct ICollision
{
    virtual void collide(Entity& projectile,const Entity *other) = 0;
    virtual std::unique_ptr<ICollision> clone() const = 0;
    virtual ~ICollision() = default;
};

struct IEffect
{
    virtual void apply(Projectile2& projectile) = 0;
    virtual std::unique_ptr<IEffect> clone() const = 0;
    virtual ~IEffect() = default;
};

struct IBehavior
{
    virtual void activate(Weapon2& weapon, Entity* target) = 0;
    virtual ~IBehavior() = default;
};