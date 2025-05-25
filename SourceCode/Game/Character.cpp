#include "Book/Character.hpp"
Character::Character(
    std::string name , 
    std::string directory,
    sf::Vector2u imageCount, 
    float switchTime
)
    :name(name)
{
    //constructor for movingAnimation
    sf::Texture texture;
    if (!texture.loadFromFile(directory))
    {
        // Handle error
        std::cerr << "Error loading texture from file: " << directory << std::endl;
    }
    movingAnimation = MovingAnimation(texture, imageCount, switchTime);    
}

Character::~Character()
{
    // Destructor logic if needed
}

void Character::PollEvents(sf::Event event)    
{  
    movingAnimation.PollEvents(event) ;     
}
void Character::Update(sf::Time deltaTime)
{
    movingAnimation.Update(deltaTime); // Update the animation
}   
void Character::Render(sf::RenderWindow& window)
{
    // Draw the Character sprite
    movingAnimation.Render(window); 
}