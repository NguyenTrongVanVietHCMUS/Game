#include <Book/MovingAnimation.hpp>

Explosion_Animation::Explosion_Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, sf::Vector2f& position, float scale, sf::Vector2f middlePosition )
    : MovingAnimation(texture, imageCount, switchTime, position, scale, middlePosition)   
{}

Explosion_Animation::~Explosion_Animation()
{
    delete texture; // Clean up the texture if it was dynamically allocated
    // Destructor logic if needed
}

void Explosion_Animation::update(sf::Time dt)
{
    totalTime += dt.asSeconds();
    if (totalTime >= switchTime) {
        totalTime -= switchTime;
        currentImage.x++;
        if (currentImage.x >= imageCount.x) {
            currentImage.y++;
            if(currentImage.y >= imageCount.y) {
                currentImage.y = 0;
            }
            currentImage.x = 0;
        }
    }

    uvRect.top = currentImage.y * uvRect.height;
    uvRect.left = currentImage.x * uvRect.width;

    setSpritePosition();
}


void Explosion_Animation::handleEvent(const sf::Event& event, sf::RenderWindow* window)
{
    // No specific event handling for this animation
}

void Explosion_Animation::handleCollision(const Entity* other)
{
    setSpritePosition();
}
