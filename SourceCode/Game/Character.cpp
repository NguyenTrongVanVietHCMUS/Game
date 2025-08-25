#include <Book/Character.hpp>
#include<Book/MovingAnimation.hpp>
#include<Object/Chest/Chest.hpp>
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
    this->updateRange = 1000.0f; // Set the update range for the character
    hurt = false ; 
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
                Entity* NearestWeapon = map->GetClosestItem(getPosition());
                if(NearestWeapon)
                {
                    sf::Vector2f distance = NearestWeapon->getPosition() - getPosition();
                    float length = std::sqrt(distance.x * distance.x + distance.y * distance.y);
                    if(length <= pickupRange){
                
                        std::shared_ptr<Weapon2> weapon = nullptr;
                        if(auto item = dynamic_cast<Weapon2*>(NearestWeapon)) {
                            weapon = std::dynamic_pointer_cast<Weapon2>(item->shared_from_this()); // Create a shared pointer to the weapon
                        } else if(auto chest = dynamic_cast<Chest*>(NearestWeapon)) {
                            chest->takeItem(weapon); // Take the item away from the chest
                        }else 
                        {
                            std::cerr << "Nearest entity is not a Weapon2 or Chest." << std::endl;
                            return false; // Exit if the nearest entity is not a weapon or chest
                        }
                        weapon->switchHold(true, this); // Switch hold state to true
                        inventory->addWeapon(weapon); // Add the nearest weapon to the inventory
                    }
                } else {
                    std::cerr << "No nearest weapon found." << std::endl;
                }
            }
        }
        if(event.key.code == sf::Keyboard::Space)
        {
            if (cameraManager) {
                cameraManager->applyEffect(new ShakeCameraEffect(1.0f, cameraManager, 10.0f)); 
            }
        }
        if(event.key.code == sf::Keyboard::C)
        {
            if(cameraManager) {
                cameraManager->applyEffect(new DarknessCameraEffect(100.0f, cameraManager)); 
            }
        }
    }

    if(event.type == sf::Event::MouseButtonPressed){
        isClickHold = true;
    } else if(event.type == sf::Event::MouseButtonReleased){
        isClickHold = false;
    }
    // Handle when mouse position changes
    
    sf::Vector2i mousePixel = sf::Mouse::getPosition(*window);
    sf::Vector2f worldPos = window->mapPixelToCoords(mousePixel, window->getView());
    inventory->AimAt(worldPos);
    return false; 
}
bool Character::update(sf::Time dt)
{
    if(isClickHold)
    {
        inventory->activateWeapon(this);
    }
    movingAnimation->update(dt); // Update the animation
    inventory->update(dt); // Update the inventory
    updateHitboxOnPosition(); // Update the hitbox position based on the entity's current position
    attributes.update(dt); // Update the entity's attributes
    return false;
}
void Character::collide(Entity* other)
{    
    movingAnimation->handleCollision(other);
}
sf::Vector2f Character::getHandPosition()const
{
    return movingAnimation->getHandPosition(); 
}
int Character::getMaxHealth()const
{
    return attributes.getMaxHealth();
}
int Character::getMaxMana()const
{
	return attributes.getMaxMana();
}
int Character::getMaxShield()const
{
	return attributes.getMaxShield();
}

int Character::getHealth()
{
    return attributes.getHealth();
}
int Character::getMana()
{
    return attributes.getMana();
}   
int Character::getShield()
{
    return attributes.getShield();
}


void Character::setAttribute(CharacterResourceType type, float current, float max)
{
    attributes.setAttribute(type, current, max);
}

bool Character::isDeath() const
{
    return attributes.isDeath();
}

void Character::takeDamage(int damage)
{
    attributes.TakeDamage(damage);
    if (isDeath()) {   
        attributes.TakeDamage(attributes.getHealth()); 
    }
}

void Character::reduceMana(int amount)
{
    int newMana = attributes.getMana() - amount;
    attributes.setAttribute(CharacterResourceType::Mana, newMana, attributes.getMaxMana());
}

void Character::knockBack(sf::Vector2f force)
{
    movingAnimation->Knockback(force);
}

void Character::knockBack(const Projectile2* projectile, float Force, Entity *other)
{
    movingAnimation->Knockback(projectile, Force, other);
}