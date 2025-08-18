#pragma once

#include<Book/Utility.hpp>
#include<Book/Character.hpp>
#include<Book/MovingAnimation.hpp>
#include<memory>
#include<Control/WeaponLoader.hpp>

class GoblinShooter : public Enemy
{

public: 
    GoblinShooter(sf::Vector2f position,State* state) : Enemy("GoblinShooter", position)
    {
        sightRange = 1250.f; 
        movingAnimation = std::make_unique<HighRangeMob_MovingAnimation>(&ResourceManager::getInstance().get<sf::Texture>(Textures::ID::GoblinShooter), sf::Vector2u(8, 3), 0.1f, this->position, 2.5f, this);
        movingAnimation->speed   = 125.0f; 
        aiEnemy = std::make_unique<AIHighRangeEnemy>();
        inventory->addWeapon(WeaponLoader(state).LoadWeapons("Laser Gun"), this);
    }

    ~GoblinShooter() override = default; // Default destructor    

};