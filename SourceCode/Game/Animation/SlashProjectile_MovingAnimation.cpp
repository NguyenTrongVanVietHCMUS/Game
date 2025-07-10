#include <Book/MovingAnimation.hpp>

SlashProjectile_MovingAnimation::SlashProjectile_MovingAnimation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, sf::Vector2f& position, float scale, float angle, sf::Vector2f middlePosition )
    : MovingAnimation(texture, imageCount, switchTime, position, scale, middlePosition), angle(angle)   
{}

SlashProjectile_MovingAnimation::~SlashProjectile_MovingAnimation()
{
    // Destructor logic if needed
}

void SlashProjectile_MovingAnimation::update(const sf::Time& deltaTime)
{
    totalTime += deltaTime.asSeconds();
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
