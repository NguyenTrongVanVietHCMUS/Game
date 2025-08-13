#include<Book/Strategy/CollisionBehavior.hpp>
#include<Book/Projectile2.hpp>
void MeleeCollisionBehavior::collide(Entity& self, const Entity* other) {
    // safe cast const pointer other to non-const pointer
    Entity* nonConstOther = const_cast<Entity*>(other);
    if (self.type == Entity::Type::AllyProjectile && other->type == Entity::Type::EnemyProjectile) {
        std::cerr << "Ally projectile hit enemy\n";
        Worldmap->popEntity(nonConstOther); // Remove the projectile from the worldmap
    } else if (self.type == Entity::Type::EnemyProjectile && other->type == Entity::Type::AllyProjectile) {
        std::cerr << "Enemy projectile hit ally\n";
        Worldmap->popEntity(nonConstOther); // Remove the projectile from the worldmap
    }

    if(auto projectile = dynamic_cast<const Projectile2*>(&self)) {
        if (projectile->type == Entity::Type::EnemyProjectile && other->type == Entity::Type::Ally) {
            nonConstOther->knockBack(projectile, 1000.0f, nonConstOther);
            nonConstOther->takeDamage(static_cast<int>(projectile->getAttribute("Damage")));
        } else if (projectile->type == Entity::Type::AllyProjectile && other->type == Entity::Type::Enemy) {
            nonConstOther->knockBack(projectile, 1000.0f, nonConstOther);
            nonConstOther->takeDamage(static_cast<int>(projectile->getAttribute("Damage")));
        } else if (projectile->type == Entity::Type::Projectile && (other->type == Entity::Type::Enemy || other->type == Entity::Type::Ally)) {
            nonConstOther->takeDamage(static_cast<int>(projectile->getAttribute("Damage")));
            return;
        }
    }
}