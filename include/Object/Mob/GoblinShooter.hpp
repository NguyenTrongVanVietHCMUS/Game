#pragma once

#include<Book/Utility.hpp>
#include<Book/Character.hpp>
#include<Book/MovingAnimation.hpp>
#include<memory>

class GoblinShooter : public Enemy
{
private : 
    float sightRange; 
public:
    GoblinShooter(sf::Vector2f position,State* state) : Enemy("GoblinShooter", position)
    {
        sightRange = 200.0f; 
        movingAnimation = std::make_unique<HighRangeMob_MovingAnimation>(&ResourceManager::getInstance().get<sf::Texture>(Textures::ID::GoblinShooter), sf::Vector2u(8, 3), 0.1f, this->position, 2.5f, this);
        movingAnimation->speed   = 125.0f; 
        aiEnemy = std::make_unique<AIHighRangeEnemy>();
        inventory->addWeapon(
            std::make_shared<Weapon2>(
                "AK_47",
                this->position, // Position of the weapon
                std::make_unique<RangedWeaponBehavior>(state, 500.0f, 20.0f), // Ranged weapon behavior with speed
                std::make_unique<GunAnimation>(
                    0.2f, // Total time for the animation
                    0.4f, // Scale of the animation
                    &ResourceManager::getInstance().get<sf::Texture>(Textures::ID::AK_47), // Texture for the gun animation
                    this->position, // Position of the gun animation
                    10.0f, // Start angle of the gun animation
                    0.0f, // End angle of the gun animation
                    25.0f, // Recoil offset for the gun animation
                    this, // Owner of the gun animation
                    sf::Vector2f(0.5f, 0.5f) // Middle position for the gun animation
                )
            )
        );
    }

    ~GoblinShooter() override = default; // Default destructor    
    Hitbox getHitbox() const
    {
        sf::Vector2f position = this->getPosition() - sf::Vector2f(22.0f, 12.0f);
        Hitbox tempHitbox;
        tempHitbox.hitbox = sf::FloatRect(position.x, position.y, 50, 12);
        return tempHitbox; // Return the hitbox of the boar
    }
    float getRange()const final
    {
        return sightRange;
    }
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        movingAnimation->draw(target, states);
        inventory->draw(target, states); 
        //skillHolder.draw(target, states); // Draw the skill holder
        //weaponHolder.draw(target, states); // Draw the weapon holder


        sf::RectangleShape hitboxshape(sf::Vector2f(getHitbox().hitbox.width, getHitbox().hitbox.height));
        hitboxshape.setPosition(sf::Vector2f(getHitbox().hitbox.left, getHitbox().hitbox.top));
        hitboxshape.setFillColor(sf::Color(255, 0, 0, 128)); // semi-transparent red for visibility
        target.draw(hitboxshape, states); // Draw the hitbox shape
    }
};