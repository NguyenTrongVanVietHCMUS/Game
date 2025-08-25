#pragma once

#include<Book/Utility.hpp>
#include<Book/Character.hpp>
#include<Book/MovingAnimation.hpp>
#include<memory>
#include<Control/WeaponLoader.hpp>

class GoblinMageRoyal : public Enemy
{
public:
    GoblinMageRoyal(sf::Vector2f position, State* state) : Enemy("GoblinMageRoyal", position)
    {
        WeaponLoader weaponLoader(state);
        sightRange = 600.f;
        movingAnimation = std::make_unique<HighRangeMob_MovingAnimation>(&ResourceManager::getInstance().get<sf::Texture>(Textures::ID::GoblinMageRoyal), sf::Vector2u(8, 3), 0.1f, this->position, 2.5f, this);
        movingAnimation->speed = 100 + rand() % 30;
        aiEnemy = std::make_unique<AIHighRangeEnemy>();
        inventory->addWeapon(WeaponLoader(state).LoadWeapons("GoblinGun"), this);
    }
    ~GoblinMageRoyal() override = default; // Default destructor    
};