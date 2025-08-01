#pragma once

#include<Book/Utility.hpp>
#include<Book/Character.hpp>
#include<Book/MovingAnimation.hpp>
#include<Book/Strategy/WeaponBehavior.hpp>
#include<Book/Strategy/WeaponAnimation.hpp>
#include<memory>
#include<Book/AIEnemy.hpp>
#include<Book/Enemy.hpp>
class GoblinWarrior : public Enemy
{
private:
    float sightRange;
public:
    GoblinWarrior(sf::Vector2f position, State* state) : Enemy( GoblinWarrior", position)
    {
        sightRange = 250.f;
        movingAnimation = std::make_unique<ShortRangeMob_MovingAnimation>(&ResourceManager::getInstance().get<sf::Texture>(Textures::ID: GoblinWarrior), sf::Vector2u(8, 3), 0.1f, this->position, 2.2, this);
        movingAnimation->speed = 175.0f;
        aiEnemy = std::make_unique<AIHighRangeEnemy>();
        inventory->addWeapon(
            std::make_shared<Weapon2>(
                 GoblinWarriorSword",
                this->position, // Position of the weapon
                1.0f, // cooldowntime
                sf::Vector2(0.5f, -0.2f), // The Scale position of the bullet spawner
                std::make_unique<MeleeWeaponBehavior>(state), // Ranged weapon behavior with speed
                std::make_unique<SwordAnimation>(
                    0.2f, // Total time for the animation
                    -0.3f, // Scale of the animation
                    &ResourceManager::getInstance().get<sf::Texture>(Textures::ID::Crowbar), // Texture for the gun animation
                    this->position, // Position of the gun animation
                    -90.0f, // Start angle of the sword animation
                    90.0f, // End angle of the sword animation
                    this, // Owner of the gun animation
                    sf::Vector2f(0.1f, 0.1f) // Middle position for the gun animation
                )
            )
        );
    }

    GoblinWarrior() override = default; // Default destructor    
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