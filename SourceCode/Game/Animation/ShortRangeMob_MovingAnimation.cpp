#include<Book/MovingAnimation.hpp>

ShortRangeMob_MovingAnimation::ShortRangeMob_MovingAnimation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, sf::Vector2f& position, float scale, sf::Vector2f middlePosition)
    :MovingAnimation(texture, imageCount, switchTime, position, scale, middlePosition)
{
   
}

ShortRangeMob_MovingAnimation::~ShortRangeMob_MovingAnimation()
{

}
void ShortRangeMob_MovingAnimation::handleEvent(const sf::Event& event, sf::RenderWindow* window)
{
	mask = rand() % 16; // Randomly set the mask for movement
}
void ShortRangeMob_MovingAnimation::update(const sf::Time& deltaTime)
{
    std::cerr << "Mask: " << mask << std::endl;
    mask = rand() % 16; 
    oldPosition = position;
    if (BIT(mask, UP))
    {
        position.y -= speed * deltaTime.asSeconds();
    }
    if (BIT(mask, DOWN))
    {
        position.y += speed * deltaTime.asSeconds();
    }
    if (BIT(mask, LEFT))
    {
        position.x -= speed * deltaTime.asSeconds();
    }
    if (BIT(mask, RIGHT))
    {
        position.x += speed * deltaTime.asSeconds();
    }

    if (position == oldPosition) {
        state = IDLE;
    }
    else
    {
        state = MOVING;
    }
    if (mask)
    {
        if (BIT(mask, LEFT))
        {
            sprite.setScale(-scale, scale);
        }
        else {
            sprite.setScale(scale, scale);
        }
    }

    currentImage.y = state;

    totalTime += deltaTime.asSeconds();

    if (totalTime >= switchTime)
    {
        totalTime -= switchTime;
        currentImage.x++;
        if (currentImage.x >= imageCount.x)
        {
            currentImage.x = 0;
        }
    }
    uvRect.left = currentImage.x * uvRect.width;
    uvRect.top = currentImage.y * uvRect.height;
    setSpritePosition();
}
void ShortRangeMob_MovingAnimation::handleCollision(const Entity* other)
{
    // Handle collision logic here
    // This is a placeholder function and should be implemented with actual collision handling logic
    position = oldPosition;
    setSpritePosition();
}