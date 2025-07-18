#include <Book/Strategy/WeaponAnimation.hpp>
#include <Book/Weapon2.hpp>
// ------------------------- SWORD ANIMATION -------------------------

SwordAnimation::SwordAnimation(float TotalTime, float scale, sf::Texture* texture, 
                                 const sf::Vector2f& position, float startAngle, float endAngle,
                                    Entity* owner,
                                 const sf::Vector2f& middlePosition)
    : IWeaponAnimation(TotalTime, scale, texture, position, middlePosition), 
      startAngle(startAngle), endAngle(endAngle), owner(owner) {
    
 
    
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
    // Get the Original Angle of the sword based on the mouse position
    sf::Vector2f direction = owner->getPosition() - sf::Vector2f(posX, posY);
    float originalAngle = std::atan2(direction.y, direction.x) * 180.0f / 3.14159f; // Convert to degrees

    float t = CurrentTime / TotalTime; // Normalized time [0, 1]
    float angleOffset = startAngle + t * (endAngle - startAngle); // Interpolate angle
    sprite.setRotation(originalAngle + angleOffset); // Set the rotation of the sprite

    // Set the position of the sprite based on the owner entity's position
    float PositionX = owner->getPosition().x; // Center the sword on the owner
    float PositionY = owner->getPosition().y - 20.0f;
    weapon.position = {PositionX, PositionY};
    sprite.setPosition(PositionX  , PositionY);
}

void SwordAnimation::draw(sf::RenderTarget& target, sf::RenderStates states) {
    target.draw(sprite, states); // Draw the sprite with the current rotation
}