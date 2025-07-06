#pragma once
#include <Book/Utility.hpp>
#include <Book/StrategyClass.hpp>
#include <Book/Entity.hpp>
#include <Book/Strategy/ProjectileBehavior.hpp>
#include <Control/State.hpp>
struct RangedWeaponBehavior : public IBehavior
{
    float projectileSpeed;
    State* Worldmap = nullptr;
    RangedWeaponBehavior(State* worldmap, float speed) : Worldmap(worldmap), projectileSpeed(speed) {}


    void activate(Weapon2& self, Entity* target) override{
        auto proj = new Projectile2(
            "RangedProjectile",
            target->getPosition(),
            std::make_unique<StraightMovement>(projectileSpeed, projectileSpeed),
            nullptr
        );
        std::cerr << "Ranged Weapon Activated" << std::endl;
        Worldmap->pushEntity(proj);
    }
};
