#pragma once
#include<Book/Utility.hpp> 

#include<Control/ResourceManager.hpp>
#include<Control/State.hpp>
#include<Book/Inventory.hpp>
class MovingAnimation;
class Character : public Entity
{
protected: 
    virtual sf::Vector2f getHandPosition()const; 
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
    virtual bool update(sf::Time dt) ; 
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const; 
    
	virtual int getMaxHealth() const;
	virtual int getMaxMana() const;
    virtual int getMaxShield() const;
    virtual int getHealth(); 
    virtual int getMana(); 
    virtual int getShield();
};