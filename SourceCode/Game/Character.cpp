#include <Book/Character.hpp>

Character::Character(
    std::string name , 
    sf::Texture* texture,
    sf::Vector2u imageCount, 
    float switchTime, 
    sf::Vector2f position
):Entity(name,position),movingAnimation(texture,imageCount,switchTime,this->position,hitbox)
{
    //skillHolder.setEntity(this); // Set the entity for the skill holder
    //skillHolder.setSkill(SkillLoader::loadSkills("Test Skill", 1.0f)); // Load a skill for the character
    weaponHolder.addWeapon(WeaponLoader::Instance().GetWeapon("Sniper", this)); // Add a gun to the weapon holder
}

Character::~Character()
{
    // Destructor logic if needed
}

bool Character::handleEvent(const sf::Event& event,sf::RenderWindow*window)
{
    movingAnimation.handleEvent(event,window);
    //skillHolder.handleEvent(event, window);
    weaponHolder.handleEvent(event,window); // Handle events for the weapon holder
    return false; 
}
void Character::operator=(const Character& other)
{
    if (this != &other) {
        name = other.name;

        // movingAnimation = other.movingAnimation;
        //skillManager = other.skillManager; // Copy the skill manager if needed
    }
}
bool Character::update(const sf::Time& deltaTime)
{
    //std::cout<<"updating Character " << position.x << ", " << position.y << std::endl;
    
    movingAnimation.update(deltaTime); // Update the animation
    //skillHolder.update(deltaTime); // Update the skill holder
    weaponHolder.update(deltaTime); // Update the weapon holder
    updateHitboxOnPosition(deltaTime); // Update the hitbox position based on the entity's current position
    return false;
}