#include <Book/Character.hpp>

Character::Character(
    std::string name , 
    sf::Vector2f position
):Entity(name,position)
{
	type = Entity::Type::Entity; // Set the type of the entity
    weaponHolder.addWeapon(WeaponLoader::Instance().GetWeapon("RapidGun", this)); // Add a gun to the weapon holder
}

Character::~Character()
{
    // Destructor logic if needed
}

bool Character::handleEvent(const sf::Event& event,sf::RenderWindow*window)
{
    movingAnimation->handleEvent(event, window); 
    weaponHolder.handleEvent(event,window); // Handle events for the weapon holder
    return false; 
}
bool Character::update(const sf::Time& deltaTime)
{
    //std::cout<<"updating Character " << position.x << ", " << position.y << std::endl;
    
    movingAnimation->update(deltaTime); // Update the animation
    weaponHolder.update(deltaTime); // Update the weapon holder
    updateHitboxOnPosition(deltaTime); // Update the hitbox position based on the entity's current position
    return false;
}
void Character::collide(const Entity* other)
{    
    movingAnimation->handleCollision(other); 
}
