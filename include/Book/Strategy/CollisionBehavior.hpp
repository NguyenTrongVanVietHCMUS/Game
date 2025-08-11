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
        // safe cast const pointer other to non-const pointer
        Entity* nonConstOther = const_cast<Entity*>(other);
        // try cast self to Projectile2
        if(auto projectile = dynamic_cast<const Projectile2*>(&self)) {
            if(projectile->type == Entity::Type::EnemyProjectile && other->type == Entity::Type::Ally) {
                nonConstOther->takeDamage(static_cast<int>(projectile->getAttribute("Damage")));
                Worldmap->popEntity(&self);
            } else if(projectile->type == Entity::Type::AllyProjectile && other->type == Entity::Type::Enemy) {
                nonConstOther->takeDamage(static_cast<int>(projectile->getAttribute("Damage")));
                Worldmap->popEntity(&self);
            } else if (other->type == Entity::Type::Object) {
                // Handle collision with objects
                Worldmap->popEntity(&self); // Remove the projectile from the worldmap
                return;
            }
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
        // safe cast const pointer other to non-const pointer
        Entity* nonConstOther = const_cast<Entity*>(other);
        if (self.type == Entity::Type::AllyProjectile && other->type == Entity::Type::EnemyProjectile) {
            std::cerr << "Ally projectile hit enemy\n";
            Worldmap->popEntity(nonConstOther); // Remove the projectile from the worldmap
        } else if (self.type == Entity::Type::EnemyProjectile && other->type == Entity::Type::AllyProjectile) {
            std::cerr << "Enemy projectile hit ally\n";
            Worldmap->popEntity(nonConstOther); // Remove the projectile from the worldmap
        }

        if(auto projectile = dynamic_cast<const Projectile2*>(other)) {
            if (projectile->type == Entity::Type::EnemyProjectile && other->type == Entity::Type::Ally) {
                nonConstOther->takeDamage(static_cast<int>(projectile->getAttribute("Damage")));
            } else if (projectile->type == Entity::Type::AllyProjectile && other->type == Entity::Type::Enemy) {
                nonConstOther->takeDamage(static_cast<int>(projectile->getAttribute("Damage")));
            } else if (other->type == Entity::Type::Object) {
                // Handle collision with objects
                Worldmap->popEntity(nonConstOther); // Remove the projectile from the worldmap
                return;
            }
        }
    }

    std::unique_ptr<ICollision> clone() const override {
        return std::make_unique<MeleeCollisionBehavior>(*this);
    }
};