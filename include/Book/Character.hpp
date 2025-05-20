#pragma once
#include<Book/Utility.hpp> 
#include<Book/Entity.hpp>
#include<Book/MovingAnimation.hpp>
class Character : public Entity 
{
private :
    
    std::string name ; 
    MovingAnimation movingAnimation ; 

public : 
// Constructor and Destructor   
    Character(){} 
    Character(std::string name , std::string directory,sf::Vector2u imageCount, float switchTime);
    ~Character(); 
public : 
// Functions
    void PollEvents(sf::Event event) ; 
    void Update(sf::Time deltaTime) ; 
    void Render(sf::RenderWindow& window) ; 
};