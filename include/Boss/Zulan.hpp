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
public:
    Zulan(sf::Vector2f position, State* state) : Enemy("Blind shot", position)
    {
        sightRange = 1350.f;
        WeaponLoader weaponLoader(state, "Media/Config/ZulanWeaponPhase1.json");
        inventory->addWeapon(weaponLoader.LoadWeapons("Zulan Radial Shot"), this);
        inventory->addWeapon(weaponLoader.LoadWeapons("Zulan Laser"), this);
        inventory->addWeapon(weaponLoader.LoadWeapons("Zulan Shot"), this);
        inventory->addWeapon(weaponLoader.LoadWeapons("Zulan Bomb"), this);
        inventory->addWeapon(weaponLoader.LoadWeapons("Blind shot"), this);
    
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

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        movingAnimation->draw(target, states);
        
        /*getHitbox().draw(target, states);
        getBodyHitbox().draw(target, states); */
        
        sf::RectangleShape hitbox(sf::Vector2f(getHitbox().hitbox.width, getHitbox().hitbox.height));
        hitbox.setPosition(sf::Vector2f(getHitbox().hitbox.left, getHitbox().hitbox.top));
        hitbox.setFillColor(sf::Color(255, 0, 0, 128)); // semi-transparent red for visibility
        target.draw(hitbox, states); // Draw the hitbox shape

        sf::RectangleShape bodyHitbox(sf::Vector2f(getBodyHitbox().hitbox.width, getBodyHitbox().hitbox.height));
        bodyHitbox.setPosition(sf::Vector2f(getBodyHitbox().hitbox.left, getBodyHitbox().hitbox.top));
        bodyHitbox.setFillColor(sf::Color(0, 255, 0, 100)); // semi-transparent red for visibility
        target.draw(bodyHitbox, states); // Draw the hitbox shape
    }
};