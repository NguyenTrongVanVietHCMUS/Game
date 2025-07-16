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
    
    void collide(Entity& self,const Entity* other) override {
        if(self.type == Entity::Type::AllyProjectile && other->type == Entity::Type::Enemy)
        {
            std::cerr << "Ally projectile hit enemy\n";
            Worldmap->popEntity(&self); // Remove the projectile from the worldmap
        }
        else if(self.type == Entity::Type::EnemyProjectile && other->type == Entity::Type::Ally)
        {
            std::cerr << "Enemy projectile hit ally\n";
            Worldmap->popEntity(&self); // Remove the projectile from the worldmap
        }
        else if(self.type == Entity::Type::AllyProjectile && other->type == Entity::Type::Object)
        {
            std::cerr << "Ally projectile hit object\n";
            Worldmap->popEntity(&self); // Remove the projectile from the worldmap
            return ;
        }
    }

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
    void collide(Entity& self, const Entity* other) override {
        if(self.type == Entity::Type::Ally && other->type == Entity::Type::Enemy)
        {
            std::cerr << "Ally hit enemy\n";
        }
        else if(self.type == Entity::Type::Enemy && other->type == Entity::Type::Ally)
        {
            std::cerr << "Enemy hit ally\n";
        }
    }

    std::unique_ptr<ICollision> clone() const override {
        return std::make_unique<MeleeCollisionBehavior>(*this);
    }
};