#pragma once

#include<Book/Utility.hpp>
#include<Book/Character.hpp>
#include<Book/MovingAnimation.hpp>
#include<memory>
#include<Control/WeaponLoader.hpp>

class GoblinMageSorcerer : public Enemy
{
public:
    GoblinMageSorcerer(sf::Vector2f position, State* state) : Enemy("GoblinMageSorcerer", position)
    {
        sightRange = 250.f;
        movingAnimation = std::make_unique<HighRangeMob_MovingAnimation>(&ResourceManager::getInstance().get<sf::Texture>(Textures::ID::GoblinMageSorcerer), sf::Vector2u(8, 3), 0.1f, this->position, 2.5f, this);
        movingAnimation->speed = 125.0f;
        aiEnemy = std::make_unique<AIHighRangeEnemy>();
        inventory->addWeapon(WeaponLoader(state).LoadWeapons("GoblinGun"), this);
    }

    ~GoblinMageSorcerer() override = default; // Default destructor    
};