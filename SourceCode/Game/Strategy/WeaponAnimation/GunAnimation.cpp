#include <Book/Strategy/WeaponAnimation.h>
#include <Book/Weapon2.hpp>
GunAnimation::GunAnimation(float TotalTime, float scale, sf::Texture* texture, 
                             const sf::Vector2f& position, float startAngle, float endAngle,
                             float recoilOffset, Entity* owner,
                             const sf::Vector2f& middlePosition)
    : IWeaponAnimation(TotalTime, scale, texture, position, middlePosition), 
      startAngle(startAngle), endAngle(endAngle), recoilOffset(recoilOffset), owner(owner), scale(scale) {

    sprite.setPosition(position);
    sprite.setScale(scale, scale);
}

void GunAnimation::update(Weapon2& weapon, const sf::Time& dt) {
    CurrentTime += dt.asSeconds();
    if (CurrentTime >= TotalTime) {
        CurrentTime = TotalTime; // Clamp to TotalTime
    }
    
    float posX = weapon.getStat("MousePosX");
    float posY = weapon.getStat("MousePosY");
    // Get the Original Angle of the gun based on the mouse position
    sf::Vector2f direction = sf::Vector2f(posX, posY) - owner->getPosition();
    float originalAngle = std::atan2(direction.y, direction.x) * 180.0f / 3.14159f; // Convert to degrees
    std::cerr << "Original Angle: " << originalAngle << std::endl;
    float t = CurrentTime / TotalTime; // Normalized time [0, 1]
    float angleOffset = startAngle + t * (endAngle - startAngle); // Interpolate angle
    if(abs(originalAngle) > 90.0f) {
        sprite.setScale(scale, -scale);
    } else sprite.setScale(scale, scale); 
    sprite.setRotation(originalAngle + angleOffset); // Set the rotation of the sprite
    
    // Set the position of the sprite based on the owner entity's position
    float PositionX = owner->getPosition().x - recoilOffset * (1.0f - t); // Center the gun on the owner
    float PositionY = owner->getPosition().y - recoilOffset * (1.0f - t) - 15; // Apply recoil effect
    sprite.setPosition(PositionX, PositionY);
}

void GunAnimation::draw(sf::RenderTarget& target, sf::RenderStates states) {
    target.draw(sprite, states); // Draw the sprite with the current rotation
}