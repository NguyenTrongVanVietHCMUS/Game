#pragma once

#include<Book/Utility.hpp>
#include<Book/Character.hpp>


class GoblinShooter : public Character
{
public:
    GoblinShooter(sf::Texture* texture, sf::Vector2f position) : Character("GoblinShooter", position)
    {
        movingAnimation = std::make_unique<HighRangeMob_MovingAnimation>(texture, sf::Vector2u(8, 3), 0.1f, this->position, 2.5f);
        movingAnimation->speed = 300.0f; // Set the speed of the boar
    }

    ~GoblinShooter() override = default; // Default destructor    
    Hitbox getHitbox() const
    {
        sf::Vector2f position = this->getPosition() - sf::Vector2f(22.0f, 12.0f);
        Hitbox tempHitbox;
        tempHitbox.hitbox = sf::FloatRect(position.x, position.y, 50, 12);
        return tempHitbox; // Return the hitbox of the boar
    }
    virtual bool handleEvent(const sf::Event& event, sf::RenderWindow* window) override
    {
        //movingAnimation->handleEvent(event, window);
        //skillHolder.handleEvent(event, window); // Handle events for the skill holder
        //weaponHolder.handleEvent(event, window); // Handle events for the weapon holder
        return false;
    }
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        movingAnimation->draw(target, states);
        //skillHolder.draw(target, states); // Draw the skill holder
        //weaponHolder.draw(target, states); // Draw the weapon holder


        sf::RectangleShape hitboxshape(sf::Vector2f(getHitbox().hitbox.width, getHitbox().hitbox.height));
        hitboxshape.setPosition(sf::Vector2f(getHitbox().hitbox.left, getHitbox().hitbox.top));
        hitboxshape.setFillColor(sf::Color(255, 0, 0, 128)); // semi-transparent red for visibility
        target.draw(hitboxshape, states); // Draw the hitbox shape
    }
};