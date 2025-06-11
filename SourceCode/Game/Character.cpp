#include <Book/Character.hpp>
Character::Character(
    std::string name , 
    sf::Texture& texture,
    sf::Vector2u imageCount, 
    float switchTime, 
    sf::Vector2f position
):Entity(name,position),movingAnimation(texture,imageCount,switchTime,this->position)
{
    skillHolder.setEntity(this); // Set the entity for the skill holder
    skillHolder.setSkill(new TestSkill(sf::seconds(1)));

}

Character::~Character()
{
    // Destructor logic if needed
}

bool Character::handleEvent(const sf::Event& event,sf::RenderWindow*window)
{
    movingAnimation.handleEvent(event,window);
    skillHolder.handleEvent(event, window);
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
bool Character::update(sf::Time deltaTime)
{
    //std::cout<<"updating Character " << position.x << ", " << position.y << std::endl;
    skillHolder.update(deltaTime); // Update the skill holder
    movingAnimation.update(deltaTime); // Update the animation
    return false;
}