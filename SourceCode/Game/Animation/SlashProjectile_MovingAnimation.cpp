#include <Book/MovingAnimation.hpp>

SlashProjectile_MovingAnimation::SlashProjectile_MovingAnimation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, sf::Vector2f& position, float scale, float angle, sf::Vector2f middlePosition )
    : MovingAnimation(texture, imageCount, switchTime, position, scale, middlePosition), angle(angle)   
{}


SlashProjectile_MovingAnimation::SlashProjectile_MovingAnimation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, sf::Vector2f& position, float scale, sf::Vector2f startPosition, sf::Vector2f endPosition, sf::Vector2f middlePosition )
    : MovingAnimation(texture, imageCount, switchTime, position, scale, middlePosition)
{
    sf::Vector2f direction = endPosition - startPosition;
    if (direction.x != 0 || direction.y != 0) {
        angle = std::atan2(direction.y, direction.x); 
        if(std::abs(angle) > 3.14159f / 2) {
            sprite.setScale(-scale, -scale); // Flip the sprite if the angle is more than 90 degrees
        } else sprite.setScale(-scale, scale); // Normal scale
    }
}

SlashProjectile_MovingAnimation::~SlashProjectile_MovingAnimation()
{
    // Destructor logic if needed
}

void SlashProjectile_MovingAnimation::update(sf::Time dt)
{
    totalTime += dt.asSeconds();
    currentImage.y = 0; // Assuming the animation is always on the first row
    if (totalTime >= switchTime) {
        totalTime -= switchTime;
        currentImage.x++;
        if (currentImage.x >= imageCount.x) {
            currentImage.x = 0;
        }
    }

    uvRect.top = currentImage.y * uvRect.height;
    uvRect.left = currentImage.x * uvRect.width;

    setSpritePosition();
    sprite.setRotation(angle * 180 / 3.14159f); // Convert to degrees
}


void SlashProjectile_MovingAnimation::handleEvent(const sf::Event& event, sf::RenderWindow* window)
{
    // No specific event handling for this animation
}

void SlashProjectile_MovingAnimation::handleCollision(const Entity* other)
{
    setSpritePosition();
}
