#pragma once
#include<Book/Utility.hpp>
#include<Book/Entity.hpp>
#include<Book/Inventory.hpp>


class MovingAnimation : public sf::Drawable
{
public :
    sf::Sprite sprite; 
    sf::Texture* texture; 
    sf::Vector2u imageCount; 
    sf::IntRect uvRect;
    float totalTime; 
    float switchTime; 
    int row; 
    float scale; 
    sf::Vector2f& position; 
    sf::Vector2f oldPosition; 
	sf::Vector2u currentImage;
    sf::Vector2f middlePosition;
    int state; 
    float speed; 
    int mask; 

    int BIT_SET(int mask, int bit) {
        return mask | (1 << bit);
    }
    int BIT_CLEAR(int mask, int bit) {
        return mask & ~(1 << bit);
    }
    bool BIT(int mask, int bit) {
        return (mask & (1 << bit)) != 0;
    }
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

public:
    virtual void chase(sf::Vector2f position)
    {
        // do nothing ;
    }
    MovingAnimation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, sf::Vector2f& position, float scale, sf::Vector2f middlePosition)
        :texture(texture), imageCount(imageCount), switchTime(switchTime), position(position), scale(scale), middlePosition(middlePosition)
    {
        totalTime = 0;
        row = 0;
        uvRect.top = 0;
        uvRect.left = 0;
        currentImage.x = 0;
        uvRect.width = int(texture->getSize().x / float(imageCount.x));
        uvRect.height = int(texture->getSize().y / float(imageCount.y));
        sprite.setTexture(*texture);
        sprite.setScale(-scale, scale);
        mask = 0; 
		direction = rand() % 2 == 0 ? LEFT : RIGHT; // Randomly set the initial direction
    }
    virtual ~MovingAnimation() 
    {
		delete texture; // Assuming texture is dynamically allocated
    } 
    virtual void update(const sf::Time& deltaTime) 
    {
        
    } // Update the animation
    virtual void handleEvent(const sf::Event& event, sf::RenderWindow* window) 
    {
        // do nothing ; 
    }
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const
    {
        states.texture = texture;
        target.draw(sprite, states);
    }
    virtual void handleCollision(const Entity* other) {} // Handle collision with another entity
protected: 
    Direction direction;
    virtual void setSpritePosition()
    {

        sprite.setPosition(position);
        sprite.setOrigin(middlePosition.x * uvRect.width, middlePosition.y * uvRect.height);
        sprite.setTextureRect(uvRect);
    }
    
};

class Character_MovingAnimation : public MovingAnimation 
{
    enum Direction
    {
        LEFT,
        RIGHT
    }; 
    Direction direction; 
    Entity* target; // Pointer to the target entity for weapon activation
private: 
    int jump = 0; 
    int distancefromground = 0; 
public :
    Character_MovingAnimation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, sf::Vector2f& position, float scale, Entity *target ,sf::Vector2f middlePosition = sf::Vector2f(0.5f, 1)); // Constructor with parameters
    ~Character_MovingAnimation();
    virtual void update(const sf::Time& deltaTime);
    virtual void handleEvent(const sf::Event& event,sf::RenderWindow* window);
    virtual void handleCollision(const Entity* other); 
    void getshot(const Entity* other);
    void setSpritePosition(); 
    void chase(sf::Vector2f position); 
};

class ShortRangeMob_MovingAnimation : public MovingAnimation
{   
private : 
    float attackRange; 
public:
    ShortRangeMob_MovingAnimation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, sf::Vector2f& position, float scale, sf::Vector2f middlePosition = sf::Vector2f(0.5f, 1));
    ~ShortRangeMob_MovingAnimation();
    virtual void update(const sf::Time& deltaTime); 
    virtual void handleCollision(const Entity* other);
    void getshot(const Entity* other); 
	void chase(sf::Vector2f position);
};

class HighRangeMob_MovingAnimation : public MovingAnimation
{
private : 
    float attackRange; 
public:
    HighRangeMob_MovingAnimation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, sf::Vector2f& position, float scale, sf::Vector2f middlePosition = sf::Vector2f(0.5f, 1));
    ~HighRangeMob_MovingAnimation();
    virtual void update(const sf::Time& deltaTime);
    virtual void handleCollision(const Entity* other);
    void getshot(const Entity* other);
    void chase(sf::Vector2f position);
};

class SlashProjectile_MovingAnimation : public MovingAnimation
{
    float angle = 0.5f; // Angle for the projectile movement
public:
    SlashProjectile_MovingAnimation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, sf::Vector2f& position, float scale,float Angle = 0.5f, sf::Vector2f middlePosition = sf::Vector2f(0.5f, 1));
    ~SlashProjectile_MovingAnimation();
    virtual void update(const sf::Time& deltaTime);
    virtual void handleEvent(const sf::Event& event, sf::RenderWindow* window);
    virtual void handleCollision(const Entity* other);
};