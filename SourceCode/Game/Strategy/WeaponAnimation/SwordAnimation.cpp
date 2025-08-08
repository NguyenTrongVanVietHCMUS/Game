#include <Book/Strategy/WeaponAnimation.hpp>
#include <Book/Weapon2.hpp>
#include <Book/Enemy.hpp>
#include <Book/Character.hpp>
// ------------------------- SWORD ANIMATION -------------------------

SwordAnimation::SwordAnimation(float TotalTime, float scale, sf::Texture* texture, 
                                 const sf::Vector2f& position, float startAngle, float endAngle,
                                    Entity* owner,
                                 const sf::Vector2f& middlePosition)
    : IWeaponAnimation(TotalTime, scale, texture, position, middlePosition, owner), 
      startAngle(startAngle), endAngle(endAngle){
    
 
    
    sprite.setPosition(position);
    sprite.setScale(scale, -scale );
}

void SwordAnimation::update(Weapon2& weapon, sf::Time dt) {
    CurrentTime += dt.asSeconds();
    if (CurrentTime >= TotalTime) {
        CurrentTime = TotalTime; // Clamp to TotalTime
    }

    float posX = weapon.getStat("TargetPosX");
    float posY = weapon.getStat("TargetPosY");


    if(owner != nullptr)
    {
        if(auto enemy = dynamic_cast<Enemy*>(owner))
        {
            if(enemy->isDeath())
            {
                sprite.setColor(sf::Color(100.0f, 100.0f, 100.0f)); // Change color to red if the owner is dead
            } else
            {
                sprite.setColor(sf::Color(255.0f, 255.0f, 255.0f)); // Reset color if the owner is not dead
            }
        }
        if(auto character = dynamic_cast<Character*>(owner))
        {
            if(character->isDeath())
            {
                sprite.setColor(sf::Color(100.0f, 100.0f, 100.0f)); // Change color to red if the owner is dead
            } else
            {
                sprite.setColor(sf::Color(255.0f, 255.0f, 255.0f)); // Reset color if the owner is not dead
            }
        }
    }
    // Get the Original Angle of the sword based on the mouse position
    sf::Vector2f direction = owner->getHandPosition() - sf::Vector2f(posX, posY);
    float originalAngle = std::atan2(direction.y, direction.x) * 180.0f / 3.14159f; // Convert to degrees
    
    float t = CurrentTime / TotalTime; // Normalized time [0, 1]
    float angleOffset = startAngle + t * (endAngle - startAngle); // Interpolate angle
    if(abs(originalAngle) > 90.0f) {
        sprite.setRotation(originalAngle - angleOffset); // Adjust for flipping
    } else sprite.setRotation(originalAngle + angleOffset); // Set the rotation of the sprite;
    weapon.setStat("OriginalAngle", originalAngle);
    // Set the position of the sprite based on the owner entity's position
    sf::Vector2f OwnerHandPosition = owner->getHandPosition();
    weapon.position = OwnerHandPosition;
    sprite.setPosition(OwnerHandPosition);
}

void SwordAnimation::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite, states); // Draw the sprite with the current rotation
}