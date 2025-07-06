#pragma once

#include<Book/Utility.hpp>
#include<Book/Character.hpp>
#include<Book/Strategy/WeaponBehavior.hpp>

class Knight : public Character
{
public:
    Knight(sf::Texture* texture,  sf::Vector2f position,State* state): Character("Knight", position)
    {
        movingAnimation = std::make_unique<Character_MovingAnimation>(
            texture, 
            sf::Vector2u(8, 3), 
            0.1f,  // Switch time for the animation
            this->position, 
            2.1f, // Scale of the animation,
            this->inventory,
            this, 
            sf::Vector2f(2.0f/3, 1)
        );  
        inventory->addWeapon(
            std::make_shared<Weapon2>(
                std::make_unique<RangedWeaponBehavior>(state, 500.0f) // Ranged weapon behavior with speed
            )
        );
        movingAnimation->speed = 500.0f; 
        this->weaponHolder.setCurrentMap(state);
        // Initialize the knight-specific properties here 
    }   
    
    ~Knight() override = default; // Default destructor    
    Hitbox getHitbox() const 
    {
        sf::Vector2f position = this->getPosition()-sf::Vector2f(22.0f,12.0f);
        Hitbox tempHitbox;
        tempHitbox.hitbox = sf::FloatRect(position.x, position.y, 50, 12);
        return tempHitbox; // Return the hitbox of the knight
    }
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        movingAnimation->draw(target, states);
        weaponHolder.draw(target, states); // Draw 
        sf::RectangleShape hitboxshape(sf::Vector2f(getHitbox().hitbox.width, getHitbox().hitbox.height));
        hitboxshape.setPosition(sf::Vector2f(getHitbox().hitbox.left, getHitbox().hitbox.top));
        hitboxshape.setFillColor(sf::Color(255, 0, 0, 128)); // semi-transparent red for visibility
        target.draw(hitboxshape, states); // Draw the hitbox shape
    }
};