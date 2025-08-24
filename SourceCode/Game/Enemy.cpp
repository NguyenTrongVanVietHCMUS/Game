#include <Book/Enemy.hpp>
#include<Book/AIEnemy.hpp>
Enemy::Enemy(
    std::string name,
    sf::Vector2f position
) :Entity(name, position)
{
    type = Entity::Type::Enemy; // Set the type of the 

}

Enemy::~Enemy()

{
    // Destructor logic if needed
}
void Enemy::collide(Entity* other)
{
    if(attributes.isDeath())
        return; // If the enemy is dead, do not handle collisions
    movingAnimation->handleCollision(other);
        
}
void Enemy::update(Entity* target, sf::Time dt)
{
    
    if(attributes.isDeath())
    {
        movingAnimation->setState(MovingAnimation::State::DEATH);
        movingAnimation->update(dt); // Update the death animation
        
        inventory->update(dt); // Update the inventory
    } else
    { 
        aiEnemy->update(this, target, dt);
        elapseDeathTime = 0.0f;
    }

}
void Enemy::chase(Entity* target , sf::Time dt)
{
    movingAnimation->chase(target,dt); 
    inventory->AimAt(position - sf::Vector2f(0, 100)); 
    inventory->update(dt);
}
void Enemy::wander(sf::Time dt)
{
    movingAnimation->wander(dt); 
	inventory->AimAt(position-sf::Vector2f(0,100)); // Aim at the middle position of the moving animation
    inventory->update(dt); 
}
void Enemy::shoot(Entity* target,sf::Time dt)
{
    inventory->shoot(this,target);  
    inventory->update(dt); 
}

bool Enemy::isAllowClean()
{
    return false;
}

bool Enemy::isDeath()
{
    return attributes.isDeath();
}

void Enemy::takeDamage(int damage)
{
  
    attributes.TakeDamage(damage);
    if (isDeath()) {
        movingAnimation->setState(MovingAnimation::State::DEATH);
        movingAnimation->update(sf::seconds(0)); 
    }
}

void Enemy::knockBack(sf::Vector2f force)
{
    movingAnimation->Knockback(force);
}

void Enemy::knockBack(const Projectile2* projectile, float Force, Entity *other)
{
    movingAnimation->Knockback(projectile, Force, other);
}
