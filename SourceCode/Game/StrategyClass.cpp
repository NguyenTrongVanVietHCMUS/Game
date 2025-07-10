#include <Book/StrategyClass.hpp>

IWeaponAnimation::IWeaponAnimation(float TotalTime, float scale, sf::Texture* texture, 
                                       const sf::Vector2f& position, const sf::Vector2f& middlePosition)
    : TotalTime(TotalTime), scale(scale), position(position), middlePosition(middlePosition), texture(texture) {
    if (texture) {
        sprite.setTexture(*texture);
        sprite.setScale(scale, scale);
        sprite.setPosition(position);
        sprite.setOrigin(middlePosition.x * texture->getSize().x, 
                         middlePosition.y * texture->getSize().y);
        std::cerr << "Middle Position: " 
                  << middlePosition.x << ", " << middlePosition.y << std::endl;
        CurrentTime = TotalTime;
    }
}

void IWeaponAnimation::play() {
    CurrentTime = 0.0f; // Reset the current time to start the animation
    if (texture) {
        sprite.setPosition(position);
    }
}