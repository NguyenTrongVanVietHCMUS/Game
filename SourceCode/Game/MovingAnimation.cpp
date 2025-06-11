#include"Book/MovingAnimation.hpp"

MovingAnimation::MovingAnimation(sf::Texture& texture  , sf::Vector2u imageCount,float switchTime,sf::Vector2f& position):texture(texture),imageCount(imageCount), switchTime(switchTime) , current_position(position)
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
    final_position = current_position; 
    velocity = sf::Vector2f(0.0f, 0.0f);
    
};  

MovingAnimation::~MovingAnimation()
{
    // Destructor
}
void MovingAnimation::handleEvent(sf::Event event, sf::RenderWindow* window)
{
    //std::cout<<"Handling event in MovingAnimation" << std::endl;
    if(event.type==sf::Event::MouseButtonPressed)
    {
        if(event.mouseButton.button==sf::Mouse::Right)
        {
            // Get the mouse position in the window
            // final_position = sf::Vector2f(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y));
            // get the current mouse position in the window
            // sf::Vector2i pixelPos = ;

            // convert it to world coordinates
            final_position = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
            // sf::Vector2i mousePixel = sf::Mouse::getPosition(window);
            // sf::Vector2f worldPos = window.mapPixelToCoords(mousePixel, gameView);
        }
    }
    // Calculate the direction vector
    sf::Vector2f direction = final_position - current_position;
    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if(distance==0.0f)
        return; // Avoid division by zero
    // Normalize the direction vector
    direction /= distance;
    // Set the velocity based on speed and direction
    velocity = direction * speed;
    std::cout<<"Current Position: " << current_position.x << ", " << current_position.y << std::endl;
    std::cout<<"Final Position: " << final_position.x << ", " << final_position.y << std::endl;
    // Update the sprite's position
}
void MovingAnimation::update(sf::Time deltaTime)
{
    // Update the Character position based on velocity
    sf::Vector2f last_position = current_position;
    current_position += velocity * deltaTime.asSeconds();
    sf::Vector2f to_final = final_position - last_position;
    sf::Vector2f to_current = current_position - last_position;
    float to_final_len = std::sqrt(to_final.x * to_final.x + to_final.y * to_final.y);
    float to_current_len = std::sqrt(to_current.x * to_current.x + to_current.y * to_current.y);
    state = MOVING; // Set the state to MOVING
    if (abs(to_final_len - to_current_len) < 0.01f) {
        state = IDLE; // If we are close to the final position, set the state to IDLE
    }
    if (to_current_len > to_final_len) {
        current_position = final_position;
        velocity = sf::Vector2f(0.0f, 0.0f);
    }
    // sprite.setPosition(current_position);
    if(final_position.x<current_position.x)
    {
        row = LEFT ; 
    }
    else if(final_position.x>current_position.x)
    {
        row = RIGHT ; 
    }
 // Update the animation
    // Flip the sprite based on the direction
    if (row == LEFT) {
        sprite.setScale(-2.5f, 2.5f); // Flip the sprite horizontally
    } else {
        sprite.setScale(2.5f, 2.5f); // Reset the scale to normal
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
    
    if(row == LEFT) {
        sprite.setPosition(current_position.x + uvRect.width / 2.0f, current_position.y + uvRect.height); // set the position of the sprite
     } else sprite.setPosition(current_position.x - uvRect.width / 2.0f, current_position.y + uvRect.height); // set the position of the sprite
    sprite.setOrigin(uvRect.width / 2.0f, float(uvRect.height)); // set the origin of the sprite to the center
    sprite.setTextureRect(uvRect); // set the texture rectangle of the sprite
    // sprite.setScale(2.5f, 2.5f); // scale the sprite to 4 times its original size; 
    // std::cout<<current_position.x << " " << current_position.y << std::endl;
    // std::cout<<final_position.x << " " << final_position.y << std::endl;
}