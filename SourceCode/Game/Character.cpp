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
    // Initialize default values if needed
}
Character::~Character()
{
    // Destructor logic if needed
}

bool Character::handleEvent(const sf::Event& event)
{
    movingAnimation.handleEvent(event);  
    return false ;  
}
bool Character::update(sf::Time deltaTime)
{
    std::cout<<"updating Character" << std::endl;
    movingAnimation.update(deltaTime); // Update the animation
    return false ; 
}