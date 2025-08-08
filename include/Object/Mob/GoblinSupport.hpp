#pragma once

#include<Book/Utility.hpp>
#include<Book/Character.hpp>
#include<Book/MovingAnimation.hpp>
#include<Book/Strategy/WeaponBehavior.hpp>
#include<Book/Strategy/WeaponAnimation.hpp>
#include<memory>
#include<Book/AIEnemy.hpp>
#include<Book/Enemy.hpp>
class GoblinSupport : public Enemy
{
private:
    float sightRange;
public:
    GoblinSupport(sf::Vector2f position, State* state) : Enemy("GoblinSupport", position)
    {
        WeaponLoader weaponLoader(state);
        sightRange = 250.f;
        movingAnimation = std::make_unique<ShortRangeMob_MovingAnimation>(&ResourceManager::getInstance().get<sf::Texture>(Textures::ID::GoblinSupport), sf::Vector2u(8, 3), 0.1f, this->position, 2.2, this);
        movingAnimation->speed = 175.0f;
        aiEnemy = std::make_unique<AIHighRangeEnemy>();
        inventory->addWeapon(WeaponLoader(state).LoadWeapons("Sword"), this);
    }

    ~GoblinSupport() override = default; // Default destructor    
};