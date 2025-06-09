#pragma once
#include<Book/Utility.hpp> 
#include<Book/Entity.hpp>
#include<Book/MovingAnimation.hpp>
#include<Control/State.hpp>
class Character : public Entity
{
private :
    MovingAnimation movingAnimation ; 
public : 
    Character(std::string name , sf::Texture& texture,sf::Vector2u imageCount, float switchTime,sf::Vector2f position);
    ~Character(); 
public : 
    bool handleEvent(const sf::Event& event,sf::RenderWindow* window) ;  
    bool update(sf::Time deltaTime) ; 
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        movingAnimation.draw(target, states);
    }
};