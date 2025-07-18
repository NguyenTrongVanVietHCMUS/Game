#include<Book/MovingAnimation.hpp>

ShortRangeMob_MovingAnimation::ShortRangeMob_MovingAnimation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, sf::Vector2f& position, float scale, Entity* entity, sf::Vector2f middlePosition)
    :MovingAnimation(texture, imageCount, switchTime, position, scale, middlePosition)
{
    this->entity = entity; 
}

ShortRangeMob_MovingAnimation::~ShortRangeMob_MovingAnimation()
{

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
        sf::Vector2f res = oldPosition;
        sf::Vector2f temp = position;
        position = sf::Vector2f(oldPosition.x, temp.y);
        if (entity->isCollide(other))
        {
            position = sf::Vector2f(temp.x, oldPosition.y);
            if (entity->isCollide(other)) position = oldPosition;
        }
    }

    //std::cout << oldPosition.x << " " << oldPosition.y << " collided with " << other->name << std::endl;
    setSpritePosition();
}

