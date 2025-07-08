#pragma once
#include<Book/Utility.hpp> 
#include<Book/MovingAnimation.hpp>
#include<Control/State.hpp>
#include<Book/Inventory.hpp>
class Character : public Entity
{
protected : 
    std::unique_ptr<MovingAnimation> movingAnimation ; 
    std::shared_ptr<Inventory> inventory;
public : 
    Character(std::string name , sf::Vector2f position);
    ~Character(); 
public : 
    //SkillHolder skillHolder;
    virtual void collide(const Entity*other); 
    virtual bool handleEvent(const sf::Event& event,sf::RenderWindow* window) ;  
    virtual bool update(const sf::Time& deltaTime) ; 
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        movingAnimation->draw(target, states);
        hitbox.draw(target, states); // Draw the hitbox
    }
};