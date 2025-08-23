#pragma once

#include<Book/Utility.hpp>
#include<Book/Character.hpp>
#include<Book/MovingAnimation.hpp>
#include<Book/Strategy/WeaponBehavior.hpp>
#include<Book/Strategy/WeaponAnimation.hpp>
#include<memory>

class RifleMinion : public Enemy
{

public:
    RifleMinion(sf::Vector2f position, State* state) : Enemy("RifleMinion", position)
    {
        WeaponLoader weaponLoader(state);
        sightRange = 600.f;
        movingAnimation = std::make_unique<ShortRangeMob_MovingAnimation>(&ResourceManager::getInstance().get<sf::Texture>(Textures::ID::RifleMinion), sf::Vector2u(8, 3), 0.1f, this->position, 0.4f, this);
        movingAnimation->speed = 120.0f;
        aiEnemy = std::make_unique<AIHighRangeEnemy>();
        inventory->addWeapon(WeaponLoader(state).LoadWeapons("MinionRifle"), this);
    }

    ~RifleMinion() override = default; // Default destructor    
};