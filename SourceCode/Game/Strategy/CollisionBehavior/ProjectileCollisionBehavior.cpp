#include<Book/Strategy/CollisionBehavior.hpp>
#include<Book/Projectile2.hpp>
#include<Book/Character.hpp>
#include<Book/Enemy.hpp>
#include<Book/Ally.hpp>
void ProjectileCollisionBehavior::collide(Entity& self,const Entity* other) {
        // safe cast const pointer other to non-const pointer
        Entity* nonConstOther = const_cast<Entity*>(other);
        if(auto enemy = dynamic_cast<Enemy*>(nonConstOther)) {
            if(enemy->isDeath()) return;
        }
        if(auto ally = dynamic_cast<Ally*>(nonConstOther)) {
            if(ally->isDeath()) return;
        }
        // try cast self to Projectile2
        if(auto projectile = dynamic_cast<Projectile2*>(&self)) {
            if(projectile->type == Entity::Type::EnemyProjectile && other->type == Entity::Type::Ally) {
                nonConstOther->takeDamage(static_cast<int>(projectile->getAttribute("Damage")));
                Worldmap->popEntity(&self);
                nonConstOther->knockBack(projectile, 200.0f, nonConstOther);
                if(auto Player = dynamic_cast<Character*>(nonConstOther)) {
                    projectile->activateEffect(Player);
                }
            } else if(projectile->type == Entity::Type::AllyProjectile && other->type == Entity::Type::Enemy) {
                nonConstOther->takeDamage(static_cast<int>(projectile->getAttribute("Damage")));
                Worldmap->popEntity(&self);
                nonConstOther->knockBack(projectile, 1000.0f, nonConstOther);
            } else if(projectile->type == Entity::Type::Projectile && (other->type == Entity::Type::Enemy || other->type == Entity::Type::Ally)) {
                nonConstOther->takeDamage(static_cast<int>(projectile->getAttribute("Damage")));
                nonConstOther->knockBack(projectile, 1000.0f, nonConstOther);
                Worldmap->popEntity(&self); // Remove the projectile from the worldmap
            } else if (other->type == Entity::Type::Object) {
                // Handle collision with objects
                Worldmap->popEntity(&self); // Remove the projectile from the worldmap
                return;
            }
        }
    }
