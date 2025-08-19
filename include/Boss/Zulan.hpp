#pragma once

#include<Book/Utility.hpp>
#include<Book/Enemy.hpp>
#include<Book/MovingAnimation.hpp>
#include<Book/Strategy/WeaponBehavior.hpp>
#include<Book/Strategy/WeaponAnimation.hpp>
#include<Book/MovingAnimation/Zulan_MovingAnimation.hpp>
#include<memory>
#include<Book/AIEnemy.hpp>
class Zulan : public Enemy
{
private:
    float sightRange;
public:
    Zulan(sf::Vector2f position, State* state) : Enemy("Zulan", position)
    {
        sightRange = 350.f;
        movingAnimation = std::make_unique<Zulan_MovingAnimation>(this->position, 3, this);
        movingAnimation->speed = 80.0f;
        aiEnemy = std::make_unique<AIZulan>();
        this->attributes.setMaxHealth(3000); 
		this->attributes.setHealth(3000);
    }
    bool isFury()const
    {
        return(this->attributes.getHealth() <= this->attributes.getMaxHealth() / 2);
       
    }
    ~Zulan() override = default; // Default destructor    
    Hitbox getHitbox() const
    {
        sf::Vector2f position = this->getPosition() - sf::Vector2f(22.0f, 12.0f);
        Hitbox tempHitbox;
        tempHitbox.hitbox = sf::FloatRect(position.x, position.y, 50, 12);
        return tempHitbox; // Return the hitbox of the boar
    }
    void chase(Entity* target, sf::Time dt)
    {
        movingAnimation->chase(target, dt);
        movingAnimation->update(dt); 
    }
    void wander(sf::Time dt)
    {
        movingAnimation->wander(dt);
        movingAnimation->update(dt); 
        inventory->AimAt(position - sf::Vector2f(0, 100)); // Aim at the middle position of the moving animation
        inventory->update(dt);
        
    }
    void shoot(Entity* target, sf::Time dt)
    {
        inventory->shoot(this, target);
        //movingAnimation->update(dt); 
        inventory->update(dt);
    }
};