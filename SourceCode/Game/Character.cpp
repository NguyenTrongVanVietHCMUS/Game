#include <Book/Character.hpp>
#include<Book/MovingAnimation.hpp>
Character::Character(
    std::string name , 
    sf::Vector2f position,
    State *state,
    CameraManager* cameraManager
):Entity(name,position)
{
	type = Entity::Type::Entity; // Set the type of the entity
    inventory = std::make_shared<Inventory>(); // Initialize the inventory
    map = state;
    this->cameraManager = cameraManager;
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
        if(event.key.code == sf::Keyboard::R)
        {
            inventory->removeCurrentWeapon(); // Remove the current weapon
            return true; 
        }
        if(event.key.code == sf::Keyboard::F)
        {
            if(map){

                std::cerr << "F key pressed, trying to pick up the nearest weapon." << std::endl;
                Entity* NearestWeapon = map->GetClosestEntity(Entity::Type::Weapon, getPosition());
                if(NearestWeapon)
                {
                    sf::Vector2f distance = NearestWeapon->getPosition() - getPosition();
                    float length = std::sqrt(distance.x * distance.x + distance.y * distance.y);
                    if(length <= pickupRange){
                        std::shared_ptr<Weapon2> weapon = std::dynamic_pointer_cast<Weapon2>(NearestWeapon->shared_from_this());
                        weapon->switchHold(true, this); // Switch hold state to true
                        inventory->addWeapon(weapon); // Add the nearest weapon to the inventory
                    }
                }
                
            }
        }
        if(event.key.code == sf::Keyboard::Space)
        {
            if (cameraManager) {
                cameraManager->applyEffect(new ShakeCameraEffect(1.0f, cameraManager, 10.0f)); // Apply a shake effect to the camera
            }
        }
        if(event.key.code == sf::Keyboard::C)
        {
            if(cameraManager) {
                cameraManager->applyEffect(new DarknessCameraEffect(100.0f, cameraManager)); // Apply a zoom effect to the camera
            }
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
