#include <Book/Character.hpp>
Character::Character(
    std::string name , 
    sf::Texture& texture,
    sf::Vector2u imageCount, 
    float switchTime
):movingAnimation(texture,imageCount,switchTime)
{
    this->name = name ; 
}
Character::Character()
{
	skillHolder.setEntity(this); // Set the entity for the skill holder
    skillHolder.setSkill(new TestSkill(sf::seconds(1)));
    // Initialize default values if needed
}
Character::~Character()
{
    // Destructor logic if needed
}

void Character::operator=(const Character& other)
{
    if (this != &other) {
        name = other.name;
        movingAnimation = other.movingAnimation;
        //skillManager = other.skillManager; // Copy the skill manager if needed
    }
}

bool Character::handleEvent(const sf::Event& event)
{
	skillHolder.handleEvent(event); // Handle events for the skill holder
    movingAnimation.handleEvent(event);  
    return false ;  
}
bool Character::update(sf::Time deltaTime)
{
    //std::cout<<"updating Character " << position.x << ", " << position.y << std::endl;
	skillHolder.update(deltaTime); // Update the skill holder
    movingAnimation.update(deltaTime); // Update the animation
    position = movingAnimation.getPosition(); // Update the character's position based on the animation
    return false ; 
}