#pragma once
#include <Book/Utility.hpp>
#include <Book/Entity.hpp>
#include <Book/StrategyClass.hpp>
#include <Control/State.hpp>

struct ProjectileCollisionBehavior : public ICollision
{
private:
    State* Worldmap;
public:
    ProjectileCollisionBehavior(State* worldmap) : Worldmap(worldmap) {}
    
    void collide(Entity& self,const Entity* other) override;

    std::unique_ptr<ICollision> clone() const override {
        return std::make_unique<ProjectileCollisionBehavior>(*this);
    }
};

struct MeleeCollisionBehavior : public ICollision
{
private:
    State* Worldmap;
public:
    MeleeCollisionBehavior(State* worldmap) : Worldmap(worldmap) {}
    void collide(Entity& self, const Entity* other) override;
    std::unique_ptr<ICollision> clone() const override {
        return std::make_unique<MeleeCollisionBehavior>(*this);
    }
};