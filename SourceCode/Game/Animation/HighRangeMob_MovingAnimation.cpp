#include<Book/MovingAnimation.hpp>

HighRangeMob_MovingAnimation::HighRangeMob_MovingAnimation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, sf::Vector2f& position, float scale, sf::Vector2f middlePosition)
    :MovingAnimation(texture, imageCount, switchTime, position, scale, middlePosition)
{

}

HighRangeMob_MovingAnimation::~HighRangeMob_MovingAnimation()
{

}
void HighRangeMob_MovingAnimation::getshot(const Entity* other)
{
    position.y -= 10;
    setSpritePosition();
}
void HighRangeMob_MovingAnimation::handleCollision(const Entity* other)
{
    // Handle collision logic here
    // This is a placeholder function and should be implemented with actual collision handling 
    if (other->type == Entity::Type::Enemy)return;
    if (other->type == Entity::Type::AllyProjectile)
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