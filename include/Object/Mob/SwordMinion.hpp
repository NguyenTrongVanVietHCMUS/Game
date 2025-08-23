#pragma once

#include<Book/Utility.hpp>
#include<Book/Character.hpp>
#include<Book/MovingAnimation.hpp>
#include<Book/Strategy/WeaponBehavior.hpp>
#include<Book/Strategy/WeaponAnimation.hpp>
#include<memory>

class SwordMinion : public Enemy
{
public:
    SwordMinion(sf::Vector2f position, State* state) : Enemy("SwordMinion", position)
    {
        WeaponLoader weaponLoader(state);
        sightRange = 250.f;
        movingAnimation = std::make_unique<ShortRangeMob_MovingAnimation>(&ResourceManager::getInstance().get<sf::Texture>(Textures::ID::SwordMinion), sf::Vector2u(8, 3), 0.1f, this->position, 0.4f, this);
        movingAnimation->speed = 175.0f;
        aiEnemy = std::make_unique<AIShortRangeEnemy>();
        inventory->addWeapon(WeaponLoader(state).LoadWeapons("MinionSword"), this);
    }   

    ~SwordMinion() override = default; 
};