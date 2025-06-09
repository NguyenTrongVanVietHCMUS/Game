#include <Book/Character.hpp>
Character::Character(
    std::string name , 
    sf::Texture& texture,
    sf::Vector2u imageCount, 
    float switchTime, 
    sf::Vector2f position
):Entity(name,position),movingAnimation(texture,imageCount,switchTime,this->position)
{
    std::cout<<"Character()"<<std::endl;
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
    return false;
}
bool Character::update(sf::Time deltaTime)
{
    std::cout<<"updating Character" << std::endl;
    movingAnimation.update(deltaTime); // Update the animation
    position = movingAnimation.current_position;
    return false;
}