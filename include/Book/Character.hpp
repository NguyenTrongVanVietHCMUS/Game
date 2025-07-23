#pragma once
#include<Book/Utility.hpp> 

#include<Control/ResourceManager.hpp>
#include<Control/State.hpp>
#include<Book/Inventory.hpp>
#include<Book/StrategyClass.hpp>
class MovingAnimation;
class Character : public Entity
{
protected:
    float pickupRange = 50.0f;
protected: 
    virtual sf::Vector2f getHandPosition()const; 
protected : 
    std::unique_ptr<MovingAnimation> movingAnimation ; 
    std::shared_ptr<Inventory> inventory;
    std::vector<std::shared_ptr<IStatusEffect> > statusEffect; // Status effect for the character
    State *map;
    
public : 
    Character(std::string name , sf::Vector2f position, State *state =nullptr);
    ~Character(); 
public : 
    //SkillHolder skillHolder;
    virtual void collide(const Entity*other); 
    virtual bool handleEvent(const sf::Event& event,sf::RenderWindow* window) ;  
    virtual bool update(sf::Time dt) ; 
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const; 
};