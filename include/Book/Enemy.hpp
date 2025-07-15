#pragma once
#include<Book/Utility.hpp> 
#include<Book/Entity.hpp>
#include<Book/MovingAnimation.hpp>
#include<Control/ResourceManager.hpp>
#include<Control/State.hpp>
#include<Book/Inventory.hpp>
class AIEnemy; 
class Enemy : public Entity
{
protected:
    float range; 
    std::unique_ptr<AIEnemy>aiEnemy;
    std::unique_ptr<MovingAnimation>movingAnimation;
    std::shared_ptr<Inventory> inventory;
public:
    Enemy(std::string name, sf::Vector2f position);
    ~Enemy();
public:

    virtual void collide(const Entity* other);
    virtual void attack(Entity* target); 
    virtual bool update(const sf::Time& deltaTime);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        movingAnimation->draw(target, states);
        inventory->draw(target, states); 
        hitbox.draw(target, states); // Draw the 
    }
public:
    virtual void chase(sf::Vector2f position);
};