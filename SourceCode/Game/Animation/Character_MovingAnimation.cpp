#include<Book/MovingAnimation.hpp>

Character_MovingAnimation::Character_MovingAnimation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, sf::Vector2f& position, float scale, sf::Vector2f middlePosition)
    :MovingAnimation(texture, imageCount, switchTime, position, scale, middlePosition)
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
void Character_MovingAnimation::update(const sf::Time& deltaTime)
{
    oldPosition = position ;  
    if(BIT(mask,UP))
    {
        position.y -= speed * deltaTime.asSeconds();
    }
    if(BIT(mask,DOWN))
    {
        position.y += speed * deltaTime.asSeconds();
    }
    if(BIT(mask,LEFT))
    {
        position.x -= speed * deltaTime.asSeconds();
    }
    if(BIT(mask,RIGHT))
    {
        position.x += speed * deltaTime.asSeconds();
    }
    if(position == oldPosition) 
    {
        state = IDLE;
    }
    else 
    {
        state = MOVING;
    }
    // update the rotation base on position of mouse 

        if (direction == LEFT)
        {
            sprite.setScale(-scale, scale);
        } 
        else
        {
            sprite.setScale(scale, scale);
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
void Character_MovingAnimation::getshot(const Entity*other)
{

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
    //std::cout << oldPosition.x << " " << oldPosition.y << " collided with " << other->name <<   std::endl;
    setSpritePosition(); 
}