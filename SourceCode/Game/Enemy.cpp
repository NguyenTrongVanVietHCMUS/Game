#include <Book/Enemy.hpp>
#include<Book/AIEnemy.hpp>
Enemy::Enemy(
    std::string name,
    sf::Vector2f position
) :Entity(name, position)
{
    type = Entity::Type::Entity; // Set the type of the entity
    weaponHolder.addWeapon(WeaponLoader::Instance().GetWeapon("RapidGun", this)); // Add a gun to the weapon holder
}

Enemy::~Enemy()
{
    // Destructor logic if needed
}
bool Enemy::update(const sf::Time& deltaTime)
{
    movingAnimation->update(deltaTime); // Update the animation
    weaponHolder.update(deltaTime); // Update the weapon holder
    updateHitboxOnPosition(deltaTime); // Update the hitbox position based on the entity's current position
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