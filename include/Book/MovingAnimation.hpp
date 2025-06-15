#pragma once
#include<Book/Utility.hpp>
#include<Control/Hitbox.hpp>
class MovingAnimation : public sf::Drawable  
{

public :
    MovingAnimation(sf::Texture* texture , sf::Vector2u imageCount, float switchTime,sf::Vector2f& position); // Constructor with parameters
    MovingAnimation(sf::Texture* texture , sf::Vector2u imageCount, float switchTime,sf::Vector2f& position,Hitbox &hitbox, float scale = 2.55f); // Constructor with parameters
    ~MovingAnimation();
    virtual void update(const sf::Time& deltaTime);
    virtual void handleEvent(const sf::Event& event,sf::RenderWindow* window);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const;
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
    sf::Vector2f nextPosition; 
    float speed ; 
    float totalTime; 
    float switchTime; 
    float scale;
    
    int row; 
    int state;
};