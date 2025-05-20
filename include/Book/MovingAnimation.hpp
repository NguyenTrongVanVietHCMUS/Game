#pragma once
#include<Book/Utility.hpp>
class MovingAnimation 
{

public : 
    MovingAnimation(sf::Texture& texture , sf::Vector2u imageCount, float switchTime);
    MovingAnimation() = default; // Default constructor
    ~MovingAnimation();
    void Update(sf::Time deltaTime);
    void PollEvents(sf::Event event) ;
    void Render(sf::RenderWindow& window) ; 
private : 
    enum Direction
    {
        LEFT,
        RIGHT,
        UP,
        DOWN
    };
    sf::Texture texture;
    sf::Sprite sprite ; 
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
    
};