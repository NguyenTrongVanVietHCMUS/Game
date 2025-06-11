#include"Book/MovingAnimation.hpp"

MovingAnimation::MovingAnimation(sf::Texture& texture  , sf::Vector2u imageCount,float switchTime,sf::Vector2f& position):texture(texture),imageCount(imageCount), switchTime(switchTime) , position(position)
{
    totalTime = 0; 
    row = 0; 
    uvRect.top = 0; // top of the sprite sheet
    uvRect.left = 0; // left of the sprite sheet
    currentImage.x = 0 ; 
    uvRect.width = int(texture.getSize().x / float(imageCount.x)); // width of each frame
    uvRect.height = int(texture.getSize().y / float(imageCount.y)); // height of each frame
    sprite.setTexture(texture); // set the texture for the sprite
    speed = 800.0f; 
};  

MovingAnimation::~MovingAnimation()
{
    // Destructor
}
void MovingAnimation::handleEvent(sf::Event event, sf::RenderWindow* window)
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
void MovingAnimation::update(sf::Time deltaTime)
{
    // Update the Character position based on velocity
    nextPosition = position ; 
    if(BIT(mask,UP))
    {
        nextPosition.y -= speed * deltaTime.asSeconds(); // Move up
    }
    if(BIT(mask,DOWN))
    {
        nextPosition.y += speed * deltaTime.asSeconds(); // Move down
    }
    if(BIT(mask,LEFT))
    {
        nextPosition.x -= speed * deltaTime.asSeconds(); // Move left
    }
    if(BIT(mask,RIGHT))
    {
        nextPosition.x += speed * deltaTime.asSeconds(); // Move right
    }
    if(nextPosition == position) {
        state = IDLE; // If the final position is the same as the current position, set the state to IDLE
    }
    else 
    {
        state = MOVING; // Set the state to MOVING
    }
    if (BIT(mask,LEFT)) {
        sprite.setScale(-2.55f, 2.55f); // Flip the sprite horizontally
    } else {
        sprite.setScale(2.55f, 2.55f); // Reset the scale to normal
    }
    // Set the animation base on State
    currentImage.y = state; // Set the current row based on the direction
    totalTime += deltaTime.asSeconds(); // update the total time
    
    if (totalTime >= switchTime) // if the total time is greater than the switch time
    {
        totalTime -= switchTime; // reset the total time
        currentImage.x++; // move to the next frame
        if (currentImage.x >= imageCount.x) // if we reach the end of the sprite sheet
        {
            currentImage.x = 0; // reset to the first frame
        }
    }
    uvRect.left = currentImage.x * uvRect.width; // set the left position of the sprite sheet
    uvRect.top = currentImage.y * uvRect.height; // set the top position of the sprite sheet
    sprite.setPosition(nextPosition); // set the position of the sprite
    sprite.setOrigin(uvRect.width / 2.0f, float(uvRect.height)); // set the origin of the sprite to the center
    sprite.setTextureRect(uvRect); // set the texture rectangle of the sprite
    // sprite.setScale(2.5f, 2.5f); // scale the sprite to 4 times its original size; 
    // std::cout<<current_position.x << " " << current_position.y << std::endl;
    // std::cout<<nextPosition.x << " " << nextPosition.y << std::endl;
    position = nextPosition ; 
}