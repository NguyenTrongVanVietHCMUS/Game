#pragma once
#include<Book/Utility.hpp>
#include<Book/Entity.hpp>
class MovingAnimation : public sf::Drawable  
{

public :
    // MovingAnimation(sf::Texture* texture , sf::Vector2u imageCount, float switchTime,sf::Vector2f& position); // Constructor with parameters
    MovingAnimation(sf::Texture* texture , sf::Vector2u imageCount, float switchTime,sf::Vector2f& position); // Constructor with parameters
    ~MovingAnimation();
    virtual void update(const sf::Time& deltaTime);
    virtual void handleEvent(const sf::Event& event,sf::RenderWindow* window);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const;
    virtual void handleCollision(Entity* other);
    // sf::Vector2f getPosition() const { return sprite.getPosition(); } // Get the current position of the animation
    sf::Sprite sprite;
public : 
    enum Direction
    {
        LEFT,
        RIGHT,
        UP,
        DOWN
    };
    int mask ; 
    enum State
    {
        IDLE,
        MOVING,
        DEATH
    };
    sf::Texture* texture;
    sf::IntRect uvRect;
    sf::Vector2u imageCount; 
    sf::Vector2u currentImage; 
    sf::Vector2f& position ; 
    sf::Vector2f oldPosition ;
    float speed ; 
    float totalTime; 
    float switchTime; 
    float scale;
    
    int row; 
    int state;
    sf::Vector2f middlePosition; // Center
private : 
    void setSpritePosition()
    {
        sprite.setPosition(position);
        sprite.setOrigin(middlePosition.x*uvRect.width, middlePosition.y*uvRect.height);
        sprite.setTextureRect(uvRect); 
    }
};