#pragma once

#include<Book/Utility.hpp>
#include<Book/Character.hpp>
#include<Book/MovingAnimation.hpp>
#include<Book/Strategy/WeaponBehavior.hpp>
#include<Book/Strategy/WeaponAnimation.hpp>
#include<memory>

class BlunderbussPistolMinion : public Enemy
{
private:
    float sightRange;
public:
    BlunderbussPistolMinion(sf::Vector2f position, State* state) : Enemy("BlunderbussPistolMinion", position)
    {
        WeaponLoader weaponLoader(state);
        sightRange = 350.f;
        movingAnimation = std::make_unique<ShortRangeMob_MovingAnimation>(&ResourceManager::getInstance().get<sf::Texture>(Textures::ID::BlunderbussPistolMinion), sf::Vector2u(8, 3), 0.1f, this->position, 0.4f, this);
        movingAnimation->speed = 80.0f;
        aiEnemy = std::make_unique<AIHighRangeEnemy>();
		inventory->addWeapon(weaponLoader.LoadWeapons("BlunderbussPistol"), this);
    }

    ~BlunderbussPistolMinion() override = default; // Default destructor    
    Hitbox getHitbox() const
    {
        sf::Vector2f position = this->getPosition() - sf::Vector2f(22.0f, 12.0f);
        Hitbox tempHitbox;
        tempHitbox.hitbox = sf::FloatRect(position.x, position.y, 50, 12);
        return tempHitbox; // Return the hitbox of the boar
    }
};