#pragma once
#include <Book/Utility.hpp>
#include <Book/Entity.hpp>
#include <Book/StrategyClass.hpp>


struct ProjectileCollisionBehavior : public ICollision
{
    void collide(Entity& self,const Entity* other) override {
        std::cerr << "Projectile collided with another entity\n";
    }
    std::unique_ptr<ICollision> clone() const override {
        return std::make_unique<ProjectileCollisionBehavior>(*this);
    }
};