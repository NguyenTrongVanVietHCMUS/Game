#pragma once

#include<Book/Utility.hpp>
#include<Book/Character.hpp>


class Knight : public Character
{
public:
    Knight(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, sf::Vector2f position): Character("Knight", texture, imageCount, switchTime, position)
    {
        movingAnimation.middlePosition = sf::Vector2f(2.0f/3, 1.0f); // Set the middle position for the knight
        // Initialize the knight-specific properties here if needed
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
        movingAnimation.draw(target, states);
        //skillHolder.draw(target, states); // Draw the skill holder
        weaponHolder.draw(target, states); // Draw the weapon holder


        sf::RectangleShape hitboxshape(sf::Vector2f(getHitbox().hitbox.width, getHitbox().hitbox.height));
        hitboxshape.setPosition(sf::Vector2f(getHitbox().hitbox.left, getHitbox().hitbox.top));
        hitboxshape.setFillColor(sf::Color(255, 0, 0, 128)); // semi-transparent red for visibility
        target.draw(hitboxshape, states); // Draw the hitbox shape
    }
};