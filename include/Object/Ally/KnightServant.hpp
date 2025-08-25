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
        sightRange = 250.f;
        movingAnimation = std::make_unique<ShortRangeMob_MovingAnimation>(&ResourceManager::getInstance().get<sf::Texture>(Textures::ID::GoblinExecutor), sf::Vector2u(8, 3), 0.1f, this->position, 2.2, this);
        movingAnimation->speed = 175.0f;
        aiAlly = std::make_unique<AIHighRangeAlly>();
        inventory->addWeapon(WeaponLoader(state).LoadWeapons("GoblinExecutorWeapon"), this);
    }

    ~KnightServant() override = default; // Default destructor    
};