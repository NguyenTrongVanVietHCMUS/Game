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
	skillManager.setEntity(this); // Set the entity for the skill manager
    skillManager.setSkill(new TestSkill(sf::seconds(1)));
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
	skillManager.handleEvent(event); // Handle events for the skill manager
    movingAnimation.handleEvent(event);  
    return false ;  
}
bool Character::update(sf::Time deltaTime)
{
    //std::cout<<"updating Character" << std::endl;
	skillManager.update(deltaTime); // Update the skill manager
    movingAnimation.update(deltaTime); // Update the animation
    return false ; 
}