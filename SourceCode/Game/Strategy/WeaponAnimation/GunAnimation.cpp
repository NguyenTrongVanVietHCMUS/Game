#include <Book/Strategy/WeaponAnimation.hpp>
#include <Book/Weapon2.hpp>
GunAnimation::GunAnimation(float TotalTime, float scale, sf::Texture* texture, 
                             const sf::Vector2f& position, float startAngle, float endAngle,
                             float recoilOffset, Entity* owner,
                             const sf::Vector2f& middlePosition)
    : IWeaponAnimation(TotalTime, scale, texture, position, middlePosition, owner), 
      startAngle(startAngle), endAngle(endAngle), recoilOffset(recoilOffset), scale(scale) {

}

void GunAnimation::update(Weapon2& weapon, sf::Time dt) {
    CurrentTime += dt.asSeconds();
    if (CurrentTime >= TotalTime) {
        CurrentTime = TotalTime; // Clamp to TotalTime
    }
    
    float posX = weapon.getStat("TargetPosX");
    float posY = weapon.getStat("TargetPosY");
    
    // Get the Original Angle of the gun based on the mouse position
    sf::Vector2f direction = sf::Vector2f(posX, posY) - owner->getHandPosition();
    float originalAngle = std::atan2(direction.y, direction.x) * 180.0f / 3.14159f; // Convert to degrees
    weapon.setStat("OriginalAngle", originalAngle); // Store the original angle in the weapon's stats
    float t = CurrentTime / TotalTime; // Normalized time [0, 1]
    float angleOffset = startAngle + t * (endAngle - startAngle); // Interpolate angle
    
    if(abs(originalAngle) > 90.0f) {
        sprite.setScale(scale, -scale);
    } else sprite.setScale(scale, scale); 
    sprite.setRotation(originalAngle + angleOffset); // Set the rotation of the sprite
	sprite.setOrigin(middlePosition.x * sprite.getTexture()->getSize().x, middlePosition.y * sprite.getTexture()->getSize().y); // Set the origin of the sprite
    // Set the position of the sprite based on the owner entity's position
    float OffsetX = recoilOffset * std::cos(originalAngle * 3.14159f / 180.0f); // Recoil offset in X direction
    float OffsetY = recoilOffset * std::sin(originalAngle * 3.14159f / 180.0f); // Recoil offset in Y direction

    float PositionX = owner->getHandPosition().x - OffsetX * (1-t); // Center the gun on the owner
    float PositionY = owner->getHandPosition().y - OffsetY * (1-t) ; // Apply recoil effect
    
    weapon.position = {PositionX, PositionY};
    sprite.setPosition(PositionX, PositionY);
}

void GunAnimation::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite, states); // Draw the sprite with the current rotation
}