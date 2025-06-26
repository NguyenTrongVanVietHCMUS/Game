#pragma once
#include<Book/Utility.hpp> 
#include<Book/Entity.hpp>
#include<Object/Skills/TestSkill.hpp>
#include<Book/MovingAnimation.hpp>
#include<Control/State.hpp>
#include<Control/SkillLoader.hpp>
#include<Control/WeaponHolder.hpp>
#include<Object/Weapon/Gun.hpp>
#include<Control/WeaponLoader.hpp>
class Character : public Entity
{
protected : 
    MovingAnimation movingAnimation ; 
public : 
    Character(std::string name , sf::Texture* texture,sf::Vector2u imageCount, float switchTime,sf::Vector2f position);
    ~Character(); 
public : 
    //SkillHolder skillHolder;
    WeaponHolder weaponHolder;
    virtual void collide(Entity*other); 
    virtual bool handleEvent(const sf::Event& event,sf::RenderWindow* window) ;  
    virtual void operator=(const Character& other); // Disable assignment operator
    virtual bool update(const sf::Time& deltaTime) ; 
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        hitbox.draw(target, states); // Draw the hitbox
        movingAnimation.draw(target, states);
        //skillHolder.draw(target, states); // Draw the skill holder
        weaponHolder.draw(target, states); // Draw the weapon holder
    }
};