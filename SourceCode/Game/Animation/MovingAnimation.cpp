#include<Book/MovingAnimation.hpp>

MovingAnimation::~MovingAnimation()
{
    delete texture; 
}
void MovingAnimation::update(sf::Time dt)
{
    oldPosition = position;
    if (BIT(mask, UP))
    {
        position.y -= speed * dt.asSeconds();
    }
    if (BIT(mask, DOWN))
    {
        position.y += speed * dt.asSeconds();
    }
    if (BIT(mask, LEFT))
    {
        position.x -= speed * dt.asSeconds();
    }
    if (BIT(mask, RIGHT))
    {
        position.x += speed * dt.asSeconds();
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

    totalTime += dt.asSeconds();

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
void MovingAnimation::setSpritePosition()
{
    sprite.setPosition(position);
    sprite.setOrigin(middlePosition.x * uvRect.width, middlePosition.y * uvRect.height);
    sprite.setTextureRect(uvRect);
}
void MovingAnimation::chase(Entity* target , sf::Time dt )
{
	sf::Vector2f destination = target->getPosition();
    mask = 0;
    if (this->position.x < destination.x)
    {
        mask = BIT_SET(mask, RIGHT); // Set the right direction bit
    }
    if (this->position.x > destination.x)
    {
        mask = BIT_SET(mask, LEFT); // Set the left direction bit
    }
    if (this->position.y < destination.y)
    {
        mask = BIT_SET(mask, DOWN);
    }
    if (this->position.y > destination.y)
    {
        mask = BIT_SET(mask, UP);
    }
    MovingAnimation::update(dt); 
}
void MovingAnimation::wander(sf::Time dt )
{

    MovingAnimation::update(dt); 
}
