#include <Book/Character.hpp>
Character::Character(
    std::string name , 
    sf::Texture& texture,
    sf::Vector2u imageCount, 
    float switchTime, 
    sf::Vector2f position
):Entity(name,position),movingAnimation(texture,imageCount,switchTime,this->position)
{
Character::Character()
{
	skillHolder.setEntity(this); // Set the entity for the skill holder
  skillHolder.setSkill(new TestSkill(sf::seconds(1)));
    // Initialize default values if needed
}
// Character::Character(const Character& character)
// : Entity(character.name, this->position = character.position), 
//   movingAnimation(character.movingAnimation)
// {
//     // Copy constructor logic if needed
// }
Character::~Character()
{
    // Destructor logic if needed
}

bool Character::handleEvent(const sf::Event& event,sf::RenderWindow*window)
{
    movingAnimation.handleEvent(event,window);
    movingAnimation.handleEvent(event);  
    return false; 
}
  void Character::operator=(const Character& other)
{
    if (this != &other) {
        name = other.name;
        movingAnimation = other.movingAnimation;
        //skillManager = other.skillManager; // Copy the skill manager if needed
    }
}
bool Character::update(sf::Time deltaTime)
{
    //std::cout<<"updating Character " << position.x << ", " << position.y << std::endl;
    skillHolder.update(deltaTime); // Update the skill holder
    movingAnimation.update(deltaTime); // Update the animation
    return false;
}