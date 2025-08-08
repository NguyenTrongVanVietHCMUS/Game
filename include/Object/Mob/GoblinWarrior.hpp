#pragma once

#include<Book/Utility.hpp>
#include<Book/Character.hpp>
#include<Book/MovingAnimation.hpp>
#include<memory>
#include<Control/WeaponLoader.hpp>

class GoblinWarrior : public Enemy
{
private:
    float sightRange;
public:
    GoblinWarrior(sf::Vector2f position, State* state) : Enemy("GoblinWarrior", position)
    {
        WeaponLoader weaponLoader(state);
        sightRange = 250.f;
        movingAnimation = std::make_unique<ShortRangeMob_MovingAnimation>(&ResourceManager::getInstance().get<sf::Texture>(Textures::ID::GoblinWarrior), sf::Vector2u(8, 3), 0.1f, this->position, 2.3, this);
        movingAnimation->speed = 175.0f;
        aiEnemy = std::make_unique<AIHighRangeEnemy>();
        inventory->addWeapon(WeaponLoader(state).LoadWeapons("Sword"), this);
    }

    ~GoblinWarrior() override = default; // Default destructor    
};