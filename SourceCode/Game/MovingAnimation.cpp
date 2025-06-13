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
    speed = 800.0f; 
};  
MovingAnimation::~MovingAnimation()
{

}
void MovingAnimation::draw(sf::RenderTarget& target,sf::RenderStates states)const
{
    std::cout<<sprite.getPosition().x<<" "<<sprite.getPosition().y<<std::endl;
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
    nextPosition = position ; 
    if(BIT(mask,UP))
    {
        nextPosition.y -= speed * deltaTime.asSeconds();
    }
    if(BIT(mask,DOWN))
    {
        nextPosition.y += speed * deltaTime.asSeconds();
    }
    if(BIT(mask,LEFT))
    {
        nextPosition.x -= speed * deltaTime.asSeconds();
    }
    if(BIT(mask,RIGHT))
    {
        nextPosition.x += speed * deltaTime.asSeconds();
    }
    if(nextPosition == position) {
        state = IDLE;
    }
    else 
    {
        state = MOVING;
    }
    if (BIT(mask,LEFT)) {
        sprite.setScale(-2.55f, 2.55f);
    } else {
        sprite.setScale(2.55f, 2.55f);
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
    sprite.setPosition(nextPosition);
    sprite.setOrigin(uvRect.width / 1.5f, float(uvRect.height));
    sprite.setTextureRect(uvRect); 
    position = nextPosition ; 
}
