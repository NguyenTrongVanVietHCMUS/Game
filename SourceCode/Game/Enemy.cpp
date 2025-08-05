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
void Enemy::collide(const Entity* other)
{
    movingAnimation->handleCollision(other);
}
void Enemy::update(Entity* target, sf::Time dt)
{
    aiEnemy->update(this, target, dt);
}
void Enemy::chase(Entity* target , sf::Time dt)
{
    movingAnimation->chase(target,dt); 
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