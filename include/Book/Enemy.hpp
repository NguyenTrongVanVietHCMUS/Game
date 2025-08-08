#pragma once
#include<Book/Utility.hpp> 
#include<Book/Entity.hpp>
#include<Book/MovingAnimation.hpp>
#include<Control/ResourceManager.hpp>
#include<Control/State.hpp>
#include<Book/Inventory.hpp>
#include<Control/WeaponLoader.hpp>
#include<Book/EntityComponent.hpp>
class AIEnemy; 
class Enemy : public Entity
{
protected:
    float range; 
    std::unique_ptr<AIEnemy>aiEnemy; 
    std::unique_ptr<MovingAnimation>movingAnimation;
    std::shared_ptr<Inventory> inventory = std::make_shared<Inventory>();
    float elapseDeathTime = 0.0f;
    float despawnDeathTime = 3.0f;
    EntityAttributeActionComponent attributes;
public:
    Enemy(std::string name, sf::Vector2f position);
    ~Enemy();
public:

    virtual void collide(const Entity* other);
    virtual void update(Entity* target , sf::Time dt);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        movingAnimation->draw(target, states);
        //inventory->draw(target, states); 
        hitbox.draw(target, states); // Draw the 
    }
public:
    virtual void chase(Entity* target,sf::Time dt);
    virtual void wander(sf::Time dt); 
    virtual void shoot(Entity* target,sf::Time dt); 
public:
    virtual bool isAllowClean();
    virtual bool isDeath();
};