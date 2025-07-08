#pragma once
#include <Book/Utility.hpp>
#include <Book/StrategyClass.hpp>
#include <Book/Entity.hpp>
#include <Book/Strategy/ProjectileBehavior.hpp>
#include <Book/Strategy/CollisionBehavior.hpp>
#include <Control/State.hpp>


struct RangedWeaponBehavior : public IBehavior
{
    float projectileSpeed;
    State* Worldmap = nullptr;
    RangedWeaponBehavior(State* worldmap, float speed) : Worldmap(worldmap), projectileSpeed(speed) {}


    void activate(Weapon2& self, Entity* target) override{
        float posX = self.getStat("MousePosX");
        float posY = self.getStat("MousePosY");
        // normalize the direction vector
        sf::Vector2f direction = sf::Vector2f(posX, posY) - target->getPosition();
        float projectileSpeedX = projectileSpeed * (direction.x / std::sqrt(direction.x * direction.x + direction.y * direction.y)),
                projectileSpeedY = projectileSpeed * (direction.y / std::sqrt(direction.x * direction.x + direction.y * direction.y));
        //std::cerr << "Projectile speed X: " << projectileSpeedX << ", Y: " << projectileSpeedY << std::endl;
        auto proj = new Projectile2(
            "RangedProjectile",
            target->getPosition(),
            std::make_unique<StraightMovement>(projectileSpeedX, projectileSpeedY),
            std::make_unique<ProjectileCollisionBehavior>(Worldmap)
        );
    
        Worldmap->pushEntity(proj);
    }
};
