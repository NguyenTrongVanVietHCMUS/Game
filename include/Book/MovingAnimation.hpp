#pragma once
#include<Book/Utility.hpp>
class MovingAnimation : public sf::Drawable  
{

public : 
    MovingAnimation(sf::Texture& texture , sf::Vector2u imageCount, float switchTime);
    MovingAnimation(); // Default constructor
    ~MovingAnimation();
    virtual void update(sf::Time deltaTime);
    virtual void handleEvent(sf::Event event);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        // std::cout<< "Drawing MovingAnimation" << std::endl;
        states.texture = &texture; // Set the texture for the sprite
        target.draw(sprite, states); // Draw the sprite to the target
        // std::cout<<uvRect.left << " " << uvRect.top << std::endl;
    }
    sf::Vector2f getPosition() const { return sprite.getPosition(); } // Get the current position of the animation
    sf::Sprite sprite;
public : 
    enum Direction
    {
        LEFT,
        RIGHT,
        UP,
        DOWN
    };

    enum State
    {
        IDLE,
        MOVING,
        DEATH
    };
    sf::Texture texture;
    sf::IntRect uvRect;
    sf::Vector2u imageCount; 
    sf::Vector2u currentImage; 
    sf::Vector2f current_position; 
    sf::Vector2f final_position;
    float speed ; 
    
    sf::Vector2f velocity;
    float totalTime; 
    float switchTime; 
    int row; 
    int state;
    
};