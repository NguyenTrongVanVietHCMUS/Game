#include<Book/MovingAnimation.hpp>

Character_MovingAnimation::Character_MovingAnimation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, sf::Vector2f& position, float scale, Entity* target, sf::Vector2f middlePosition)
    :MovingAnimation(texture, imageCount, switchTime, position, scale, middlePosition), target(target)
{
	direction = rand() % 2 == 0 ? LEFT : RIGHT; // Randomly set the initial direction
}

Character_MovingAnimation::~Character_MovingAnimation()
{

}
void Character_MovingAnimation::handleEvent(const sf::Event& event,sf::RenderWindow* window)
{    
    if(event.type==sf::Event::KeyPressed)
    {
        if(event.key.code==sf::Keyboard::W)
        {
            mask = BIT_SET(mask, UP); 
        }
        if(event.key.code==sf::Keyboard::S)
        {
            mask = BIT_SET(mask,DOWN) ; 
        }
       
        if(event.key.code==sf::Keyboard::A)
        {
            mask = BIT_SET(mask,LEFT) ; 
        }
       
        if(event.key.code==sf::Keyboard::D)
        {
            mask = BIT_SET(mask,RIGHT) ; 
        }
    }
    
    if(event.type==sf::Event::KeyReleased)
    {
        if(event.key.code==sf::Keyboard::W)
        {
            mask = BIT_CLEAR(mask, UP); 
        }
        if(event.key.code==sf::Keyboard::S)
        {
            mask = BIT_CLEAR(mask,DOWN) ; 
        }
        if(event.key.code==sf::Keyboard::A)
        {
            mask = BIT_CLEAR(mask,LEFT) ; 
        }
        if(event.key.code==sf::Keyboard::D)
        {
            mask = BIT_CLEAR(mask,RIGHT) ; 
        }
    }
    sf::Vector2i mousePixel = sf::Mouse::getPosition(*window);
    sf::Vector2f worldPos = window->mapPixelToCoords(mousePixel, window->getView());

    if (worldPos.x < position.x)
    {
		direction = LEFT;
    }
    else if (worldPos.x > position.x)
    {
        direction = RIGHT;
    }
    else
    {
        // stay the same 
    }
}
void Character_MovingAnimation::update(sf::Time dt)
{
    oldPosition = position ;  
    if(BIT(mask,UP))
    {
        position.y -= speed * dt.asSeconds();
    }
    if(BIT(mask,DOWN))
    {
        position.y += speed * dt.asSeconds();
    }
    if(BIT(mask,LEFT))
    {
        position.x -= speed * dt.asSeconds();
    }
    if(BIT(mask,RIGHT))
    {
        position.x += speed * dt.asSeconds();
    }
    if((BIT(mask,UP)!=BIT(mask,DOWN)) || (BIT(mask,LEFT) != BIT(mask,RIGHT)))
    {
        state = MOVING; // Moving state
    }
    else
    {
        state = IDLE; // Idle state
	}
    // update the rotation base on position of 
    if (direction == LEFT)
    {
        sprite.setScale(-scale, scale);
    } 
    else
    {
        sprite.setScale(scale, scale);
    }
    
    currentImage.y = state;

    totalTime += dt.asSeconds();
    if (state == IDLE || state == DEATH) jump = 0,distancefromground=0; 
    if (totalTime >= switchTime)
    {
        totalTime -= switchTime;
        currentImage.x++; 
        if (state == MOVING)
        {
            jump = distancefromground == 0 ? 1 : jump;
            jump = distancefromground == 4 ? -1 : jump;
            distancefromground += jump; // corrected the variable name
        }
        else distancefromground = 0; 

        if (currentImage.x >= imageCount.x)
        {
            currentImage.x = 0;
        }
    }
    uvRect.left = currentImage.x * uvRect.width;
    uvRect.top = currentImage.y * uvRect.height;
    setSpritePosition(); 
}
void Character_MovingAnimation::getshot(const Entity*other)
{

}   
void Character_MovingAnimation::setSpritePosition()
{
    sprite.setPosition(position);
    if (state == MOVING)
    {
        std::cerr << distancefromground << std::endl;
        sprite.setPosition(position.x, position.y - 1.5 * distancefromground); // Adjust for jump effect
    }
    sprite.setOrigin(middlePosition.x * uvRect.width, middlePosition.y * uvRect.height);
    sprite.setTextureRect(uvRect);
}
void Character_MovingAnimation::handleCollision(const Entity* other)
{
    // Handle collision logic here
    // This is a placeholder function and should be implemented with actual collision handling 
    if(other->type==Entity::Type::EnemyProjectile)
    {
        getshot(other); 
	}
    if (other->type == Entity::Type::Object)
    {
        position = oldPosition;
    }

    setSpritePosition(); 
}