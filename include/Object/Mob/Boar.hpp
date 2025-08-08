#pragma once

#include<Book/Utility.hpp>
#include<Book/Enemy.hpp>
#include<Book/AIEnemy.hpp>

class Boar : public Enemy
{
private : 
    float sightRange; 
public:
    Boar(sf::Vector2f position,State* states) : Enemy("Boar", position)
    {
        //WeaponLoader weaponLoader(state);
        sightRange = 200; 
	    movingAnimation = std::make_unique<ShortRangeMob_MovingAnimation>(&ResourceManager::getInstance().get<sf::Texture>(Textures::ID::Boar), sf::Vector2u(8, 3), 0.1f, this->position, 2.5f, this);
		movingAnimation->speed = 150.0f; // Set the speed of the boar
        aiEnemy = std::make_unique<AIShortRangeEnemy>(); 
    }

    ~Boar() override = default; 
};  