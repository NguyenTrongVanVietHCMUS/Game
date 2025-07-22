#include <Book/Character.hpp>
#include<Book/MovingAnimation.hpp>
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
void Character::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    movingAnimation->draw(target, states); // Draw the moving animation
    inventory->draw(target, states); // Draw the inventory
    hitbox.draw(target, states); // Draw the hitbox

}
bool Character::handleEvent(const sf::Event& event,sf::RenderWindow*window)
{
    dynamic_cast<Character_MovingAnimation*>(movingAnimation.get())->handleEvent(event, window); 
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
    inventory->AimAt(worldPos);
    return false; 
}
bool Character::update(sf::Time dt)
{

    movingAnimation->update(dt); // Update the animation
    inventory->update(dt); // Update the inventory
    updateHitboxOnPosition(); // Update the hitbox position based on the entity's current position

    return false;
}
void Character::collide(const Entity* other)
{    
    movingAnimation->handleCollision(other); 
}
sf::Vector2f Character::getHandPosition()const
{
    return movingAnimation->getHandPosition(); 
}
int Character::getMaxHealth()const
{
    return 10; // Maximum health value
}   
int Character::getMaxMana()const 
{
	return 120; // Maximum mana value    
}
int Character::getMaxShield()const
{
	return 3; // Maximum shield value  
}

int Character::getHealth()
{
    return 10; 
}
int Character::getMana()
{
    return 35; 
}   
int Character::getShield()
{
    return 2; 
}
