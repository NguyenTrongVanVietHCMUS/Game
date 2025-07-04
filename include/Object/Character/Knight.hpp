#pragma once

#include<Book/Utility.hpp>
#include<Book/Character.hpp>


class Knight : public Character
{
public:
    Knight(sf::Texture* texture,  sf::Vector2f position,State* state): Character("Knight", position)
    {
		type = Entity::Type::Ally; // Set the type of the entity
        movingAnimation = std::make_unique<Character_MovingAnimation>(texture, sf::Vector2u(8, 3), 0.1f, this->position, 2.1f,sf::Vector2f(0.5,1)); 
        movingAnimation->speed = 500.0f; 
        this->weaponHolder.setCurrentMap(state);
        weaponHolder.addWeapon(WeaponLoader::Instance().GetWeapon("RapidGun", this)); // Add a gun to the weapon 
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
    void collide(const Entity* other) override final 
    {
        movingAnimation->handleCollision(other); 
	}
};