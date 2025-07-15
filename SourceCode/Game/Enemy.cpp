#include <Book/Enemy.hpp>
#include<Book/AIEnemy.hpp>
Enemy::Enemy(
    std::string name,
    sf::Vector2f position
) :Entity(name, position)
{
    type = Entity::Type::Entity; // Set the type of the entity

}

Enemy::~Enemy()
{
    // Destructor logic if needed
}
bool Enemy::update(const sf::Time& deltaTime)
{
    movingAnimation->update(deltaTime); // Update the animation
    //inventory->update(deltaTime); // Update the weapon holder
    updateHitboxOnPosition(); // Update the hitbox position based on the entity's current position
    return false;
}
void Enemy::collide(const Entity* other)
{
    movingAnimation->handleCollision(other);
}
void Enemy::attack(Entity* target)
{
    aiEnemy->attack(this, target); 
}
void Enemy::chase(sf::Vector2f position)
{
    movingAnimation->chase(position);
}