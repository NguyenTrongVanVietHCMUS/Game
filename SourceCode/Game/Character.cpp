#include <Book/Character.hpp>

Character::Character(
    std::string name , 
    sf::Vector2f position
):Entity(name,position)
{
	type = Entity::Type::Entity; // Set the type of the entity
    inventory = std::make_shared<Inventory>(); // Initialize the inventory
}

Character::~Character()
{
    // Destructor logic if needed
} 
bool Character::handleEvent(const sf::Event& event,sf::RenderWindow*window)
{
    movingAnimation->handleEvent(event, window); 
    return false; 
}
bool Character::update(const sf::Time& deltaTime)
{
    //std::cout<<"updating Character " << position.x << ", " << position.y << std::endl;
    
    movingAnimation->update(deltaTime); // Update the animation
    inventory->update(deltaTime); // Update the inventory
    updateHitboxOnPosition(); // Update the hitbox position based on the entity's current position
    return false;
}
void Character::collide(const Entity* other)
{    
    movingAnimation->handleCollision(other); 
}
void Character::chase(sf::Vector2f position)
{
    movingAnimation->chase(position);
}