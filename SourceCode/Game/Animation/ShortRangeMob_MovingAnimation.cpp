#include<Book/MovingAnimation.hpp>

ShortRangeMob_MovingAnimation::ShortRangeMob_MovingAnimation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, sf::Vector2f& position, float scale, sf::Vector2f middlePosition)
    :MovingAnimation(texture, imageCount, switchTime, position, scale, middlePosition)
{
   
}

ShortRangeMob_MovingAnimation::~ShortRangeMob_MovingAnimation()
{

}
void ShortRangeMob_MovingAnimation::update(const sf::Time& deltaTime)
{
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
void ShortRangeMob_MovingAnimation::getshot(const Entity* other)
{
    position.y -= 10;
    setSpritePosition();
}
void ShortRangeMob_MovingAnimation::handleCollision(const Entity* other)
{
    // Handle collision logic here
    // This is a placeholder function and should be implemented with actual collision handling 
    if (other->type == Entity::Type::Enemy)return; 
    if(other->type==Entity::Type::AllyProjectile)
    {
        getshot(other); // Handle getting shot by ally projectile
	}
    if (other->type == Entity::Type::Object)
    {
        position = oldPosition; 
    }

    //std::cout << oldPosition.x << " " << oldPosition.y << " collided with " << other->name << std::endl;
    setSpritePosition();
}


void ShortRangeMob_MovingAnimation::chase(sf::Vector2f target)
{
    // Chase logic for short-range mob
    mask = 0; 
    if (this->position.x < target.x)
    {
		mask = BIT_SET(mask, RIGHT); // Set the right direction bit
    }
    if (this->position.x > target.x)
    {
		mask = BIT_SET(mask, LEFT); // Set the left direction bit
    }
    if (this->position.y < target.y)
    {
        mask = BIT_SET(mask, DOWN);
    }
    if(this->position.y > target.y)
    {
        mask = BIT_SET(mask, UP);
	}
    //setSpritePosition();
}