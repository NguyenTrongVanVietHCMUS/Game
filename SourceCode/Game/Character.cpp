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
    if(event.type == sf::Event::KeyPressed)
    {
        if(event.key.code == sf::Keyboard::Q)
        {
            inventory->activateWeapon(this); // Activate the skill
            return true; 
        }
        if(event.key.code == sf::Keyboard::E)
        {
            inventory->SwitchWeapon(); // Switch to the next weapon
            return true; 
        }
    }
    // Handle when mouse position changes
    
    sf::Vector2i mousePixel = sf::Mouse::getPosition(*window);
    sf::Vector2f worldPos = window->mapPixelToCoords(mousePixel, window->getView());
    std::shared_ptr<Weapon2> weapon = inventory->getCurrentWeapon();
    if (weapon)
    {
        weapon->setStat("TargetPosX", worldPos.x);
        weapon->setStat("TargetPosY", worldPos.y);
        weapon->setStat("MousePosX", position.x);
        weapon->setStat("MousePosY", position.y);
    }
    
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