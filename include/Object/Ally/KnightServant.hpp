#pragma once

#include<Book/Utility.hpp>
#include<Book/Character.hpp>
#include<Book/MovingAnimation.hpp>
#include<Book/Strategy/WeaponBehavior.hpp>
#include<Book/Strategy/WeaponAnimation.hpp>
#include<memory>
#include<Book/AIAlly.hpp>
#include<Book/Ally.hpp>
class KnightServant : public Ally
{
public:
    KnightServant(sf::Vector2f position, State* state, Entity* owner) : Ally("KnightServant", position, owner)
    {
        WeaponLoader weaponLoader(state);
        sightRange = 800.0f;
        movingAnimation = std::make_unique<Ally_MovingAnimation>(&ResourceManager::getInstance().get<sf::Texture>(Textures::ID::KnightServant), sf::Vector2u(8, 3), 0.1f, this->position, 2.2, this);
        movingAnimation->speed = 130 + rand() % 60;
        aiAlly = std::make_unique<AIShortRangeAlly>();
        inventory->addWeapon(WeaponLoader(state).LoadWeapons("LongSword"), this);
        this->attributes.setMaxHealth(3000);      
        this->attributes.setHealth(3000);
    } 
    Hitbox getHitbox() const
    {
        sf::Vector2f position = this->getPosition() - sf::Vector2f(22.0f, 12.0f);
        Hitbox tempHitbox;
        tempHitbox.hitbox = sf::FloatRect(position.x, position.y, 50, 12);
        return tempHitbox; // Return the hitbox of the knight
    }
    Hitbox getBodyHitbox() const override
    {
        sf::Vector2f position = this->getPosition() - sf::Vector2f(22.0f, 60.0f);
        Hitbox tempHitbox;
        tempHitbox.hitbox = sf::FloatRect(position.x, position.y, 50, 60);
        return tempHitbox; // Return the body hitbox of the knight
    }
    void collide(Entity* other) override final
    {
        movingAnimation->handleCollision(other);
    }
    ~KnightServant() override = default; // Default destructor    
};