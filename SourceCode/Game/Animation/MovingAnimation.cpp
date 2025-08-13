#include<Book/MovingAnimation.hpp>
#include<Book/Projectile2.hpp>
MovingAnimation::~MovingAnimation()
{
    
}
void MovingAnimation::update(sf::Time dt)
{
    oldPosition = position;
    if(state == DEATH)
    {
        currentImage.x = 0;
        currentImage.y = 2; // Assuming row 2 is for death animation
        uvRect.top = currentImage.y * uvRect.height;
        uvRect.left = currentImage.x * uvRect.width;
        setSpritePosition();
        sprite.setColor(sf::Color(100, 100, 100));
    } else {
        sprite.setColor(sf::Color::White);
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
        float ForceLimit = 500.0f;
        
        position += 
            sf::Vector2f(std::max(std::min(CurrentKnockbackForce.x ,ForceLimit), -ForceLimit)* dt.asSeconds(),
                        std::max(std::min(CurrentKnockbackForce.y ,ForceLimit), -ForceLimit)* dt.asSeconds()); // Apply knockback force
        CurrentKnockbackForce = CurrentKnockbackForce - CurrentKnockbackForce * KnockbackResistance * dt.asSeconds(); // Reduce knockback force over time
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
    if(state == DEATH)
    {
        currentImage.x = 0; // Reset to the first frame of death animation
    }
    uvRect.left = currentImage.x * uvRect.width;
    uvRect.top = currentImage.y * uvRect.height;
    setSpritePosition();
}
void MovingAnimation::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.texture = texture;
    target.draw(sprite, states);
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
    if(abs(this->position.x - destination.x) > 5.0f)
    {
        if (this->position.x < destination.x)
        {
            mask = BIT_SET(mask, RIGHT); // Set the right direction bit
        }
        if (this->position.x > destination.x)
        {
            mask = BIT_SET(mask, LEFT); // Set the left direction bit
        }
    }
    if(abs(this->position.y - destination.y) > 5.0f)
    {
        if (this->position.y < destination.y)
        {
            mask = BIT_SET(mask, DOWN); // Set the down direction bit
        }
        if (this->position.y > destination.y)
        {
            mask = BIT_SET(mask, UP); // Set the up direction bit
        }
	}
    MovingAnimation::update(dt); 
}
void MovingAnimation::wander(sf::Time dt)
{
    bool change = rand() % 68 == 0;
    if (change)
    {
        mask = rand() % 16;
    }
    MovingAnimation::update(dt);
}
sf::Vector2f MovingAnimation::getHandPosition()const
{
    return sf::Vector2f(position.x, position.y - sprite.getGlobalBounds().height / 2 + 100);
}

void MovingAnimation::setSpriteScale(float scale)
{
    this->scale = scale; // Set the scale of the sprite
    sprite.setScale(scale, scale); // Apply the scale to the sprite
}

void MovingAnimation::setSpriteRotation(float angle)
{
    sprite.setRotation(angle); // Set the rotation of the sprite
}

void MovingAnimation::setState(State newState)
{
    state = newState;
}

void MovingAnimation::Knockback(sf::Vector2f force)
{
    CurrentKnockbackForce += force;
    setSpritePosition(); // Update the sprite position after knockback
}

void MovingAnimation::Knockback(const Projectile2* projectile, float Force, Entity *other)
{
    if (projectile)
    {
        sf::Vector2f direction = projectile->getProjDirection(other);
        // normalize the direction
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        if (length != 0)
        {
            direction /= length;
        }
        CurrentKnockbackForce += direction * Force;
    }
}