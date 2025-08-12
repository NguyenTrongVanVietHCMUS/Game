#pragma once

#include<Book/Utility.hpp>
#include<Book/Character.hpp>
#include<Book/MovingAnimation.hpp>
#include<memory>
#include<Control/WeaponLoader.hpp>

class GoblinPriest : public Enemy
{
private : 
	sf::Texture goblinPriestTexture;
public:
    GoblinPriest(sf::Vector2f position, State* state) : Enemy("GoblinPriest", position)
    {
        goblinPriestTexture.loadFromFile("Media/Assets/Mobs/GoblinPriest/goblinpriest.png");
        sightRange = 1250.f;
        movingAnimation = std::make_unique<HighRangeMob_MovingAnimation>(&goblinPriestTexture, sf::Vector2u(8, 3), 0.1f, this->position, 0.8f, this);
        movingAnimation->speed = 125.0f;
        aiEnemy = std::make_unique<AIHighRangeEnemy>();
        inventory->addWeapon(WeaponLoader(state).LoadWeapons("ShootingStar"), this);
    }

    ~GoblinPriest() override = default; // Default destructor    

};