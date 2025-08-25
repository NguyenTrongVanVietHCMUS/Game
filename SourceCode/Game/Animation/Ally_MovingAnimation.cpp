#include<Book/MovingAnimation.hpp>

Ally_MovingAnimation::Ally_MovingAnimation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, sf::Vector2f& position, float scale, Entity* entity, sf::Vector2f middlePosition)
    :MovingAnimation(texture, imageCount, switchTime, position, scale, middlePosition)
{
    this->entity = entity;
}

Ally_MovingAnimation::~Ally_MovingAnimation()
{

}
void Ally_MovingAnimation::getshot(const Entity* other)
{
    //position.y -= 10;
    setSpritePosition();
}
void Ally_MovingAnimation::handleCollision(const Entity* other)
{
    // Handle collision logic here

    if (other->type == Entity::Type::EnemyProjectile)
    {
        getshot(other);
    }
    if (other->type == Entity::Type::Object && !other->passAble())
    {
        sf::Vector2f temp = position;
        sf::Vector2f res = oldPosition;
        position = sf::Vector2f(temp.x, oldPosition.y);
        if (entity->isCollide(other))
        {
            temp.x = oldPosition.x;
        }
        position = sf::Vector2f(oldPosition.x, temp.y);
        if (entity->isCollide(other))
        {
            temp.y = oldPosition.y;
        }
        position = temp;
        std::cout << " COLLIDE" << std::endl;
    }


    //std::cout << oldPosition.x << " " << oldPosition.y << " collided with " << other->name << std::endl;
    setSpritePosition();
}

