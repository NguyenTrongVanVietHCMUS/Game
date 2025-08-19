#include<Book/MovingAnimation/Zulan_MovingAnimation.hpp>
#include<Boss/Zulan.hpp>
Zulan_MovingAnimation::Zulan_MovingAnimation(sf::Vector2f& position, float scale, Entity* entity, sf::Vector2f middlePosition)
    :MovingAnimation(nullptr, sf::Vector2u(0,0),0, position, scale, middlePosition)
{
    this->entity = entity;
    death.loadFromFile("Media/Assets/Mobs/Zulan/DeadZulan.png");
    ring.loadFromFile("Media/Assets/Mobs/Zulan/NormalRing.png"); 
    body.loadFromFile("Media/Assets/Mobs/Zulan/NormalZulan.png"); 
    
    furyRing.loadFromFile("Media/Assets/Mobs/Zulan/FuryRing.png"); 
    furyBody.loadFromFile("Media/Assets/Mobs/Zulan/FuryZulan.png");
    
    deathSprite.setTexture(death); 
    ringSprite.setTexture(ring); 
	bodySprite.setTexture(body);
    furyRingSprite.setTexture(furyRing); 
    furyBodySprite.setTexture(furyBody);

    deathSprite.setScale(scale, scale);
	ringSprite.setScale(scale, scale);
    bodySprite.setScale(scale, scale);
    furyRingSprite.setScale(scale, scale);
    furyBodySprite.setScale(scale, scale);
	deathSprite.setOrigin(death.getSize().x / 2.f, death.getSize().y / 2.f);
	ringSprite.setOrigin(ring.getSize().x / 2.f, ring.getSize().y / 2.f);
	bodySprite.setOrigin(body.getSize().x / 2.f, body.getSize().y / 2.f);
	furyRingSprite.setOrigin(furyRing.getSize().x / 2.f, furyRing.getSize().y / 2.f);
	furyBodySprite.setOrigin(furyBody.getSize().x / 2.f, furyBody.getSize().y / 2.f);
    jump = 1; 
    center = 0; 
    setSpritePosition();

}
void Zulan_MovingAnimation::setSpritePosition()
{
    ringSprite.setPosition(sf::Vector2f(position.x, position.y - center * 3));
    bodySprite.setPosition(position);
    furyRingSprite.setPosition(sf::Vector2f(position.x, position.y - center * 3));
    furyBodySprite.setPosition(position);
    deathSprite.setPosition(position);
}
Zulan_MovingAnimation::~Zulan_MovingAnimation()
{

}
void Zulan_MovingAnimation::update(sf::Time dt)
{
    elapsedTime += dt; 
    if (elapsedTime.asSeconds()>0.3)
    {
        elapsedTime = sf::Time::Zero; 
        center += jump; 
        if (center == 2)jump = -1; 
        if (center == 0) jump = 1; 
    }
	auto zulan = dynamic_cast<Zulan*>(entity);
    float num  = 1e9; 
    if(!zulan->isFury())
    {
        ringSprite.rotate(39.f);
        furyRingSprite.rotate(39.f);
    }
    else
    {
        furyRingSprite.rotate(41.f);
        ringSprite.rotate(41.f);
    }
    if(position.x<oldPosition.x)
    {
        ringSprite.setScale(-scale, scale);
        furyRingSprite.setScale(-scale, scale);
        bodySprite.setScale(-scale, scale);
        furyBodySprite.setScale(-scale, scale);
    }
    else
    {
        ringSprite.setScale(scale, scale);
        furyRingSprite.setScale(scale, scale);
        bodySprite.setScale(scale, scale);
        furyBodySprite.setScale(scale, scale);
	}
}
void Zulan_MovingAnimation::getshot(const Entity* other)
{
    
}

void Zulan_MovingAnimation::handleCollision(const Entity* other)
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
    }

    //std::cout << oldPosition.x << " " << oldPosition.y << " collided with " << other->name << std::endl;
    setSpritePosition();
}

void Zulan_MovingAnimation::draw(sf::RenderTarget& target, sf::RenderStates states)const
{
	auto zulan= dynamic_cast<Zulan*>(entity);

    if (zulan->isDeath())
    {
		target.draw(deathSprite, states);
    }
    else if (!zulan->isFury())
    {
        target.draw(ringSprite, states);
        target.draw(bodySprite, states);
    }
    else
    {
		target.draw(furyRingSprite, states);
		target.draw(furyBodySprite, states);
    }
}
