#pragma once
#include<Book/Utility.hpp> 
#include<Book/Entity.hpp>
#include<Book/MovingAnimation.hpp>
class Character : public Entity
{
private :
    MovingAnimation movingAnimation ; 
public : 
    Character();
    Character(std::string name , sf::Texture& texture,sf::Vector2u imageCount, float switchTime);
    ~Character(); 
public : 
    bool handleEvent(const sf::Event& event) ; 
    bool update(sf::Time deltaTime) ; 
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        movingAnimation.draw(target, states);
    }
};