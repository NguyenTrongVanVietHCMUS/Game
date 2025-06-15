#include"Book/MovingAnimation.hpp"

MovingAnimation::MovingAnimation(sf::Texture* texture  , sf::Vector2u imageCount,float switchTime,sf::Vector2f& position):texture(texture),imageCount(imageCount), switchTime(switchTime) , position(position)
{
    totalTime = 0; 
    row = 0; 
    uvRect.top = 0; 
    uvRect.left = 0; 
    currentImage.x = 0 ; 
    uvRect.width = int(texture->getSize().x / float(imageCount.x)); 
    uvRect.height = int(texture->getSize().y / float(imageCount.y)); 
    sprite.setTexture(*texture); 
    sprite.setScale(-2.15f, 2.15f);
    speed = 400.0f; 
};  
MovingAnimation::~MovingAnimation()
{

}
void MovingAnimation::draw(sf::RenderTarget& target,sf::RenderStates states)const
{
    states.texture = texture; 
    target.draw(sprite, states);

}
void MovingAnimation::handleEvent(const sf::Event& event,sf::RenderWindow* window)
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
    // std::cout<<"Mask: " << mask << std::endl ;// Debugging output to check the mask vadslue
}
void MovingAnimation::update(const sf::Time& deltaTime)
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

    if(position == oldPosition) {
        state = IDLE;
    }
    else 
    {
        state = MOVING;
    }
    if(state==MOVING)
    {
        if (BIT(mask,LEFT)) {
            sprite.setScale(-2.15f, 2.15f);
        } else {
            sprite.setScale(2.15f, 2.15f);
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
void MovingAnimation::handleCollision(Entity* other)
{
    // Handle collision logic here
    // This is a placeholder function and should be implemented with actual collision handling logic
    position = oldPosition ; 
    setSpritePosition(); 
}