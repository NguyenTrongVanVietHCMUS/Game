#pragma once
#include<Book/Utility.hpp>
#include<Book/Entity.hpp>
#include<Book/Inventory.hpp>
#include<Book/EntityComponent.hpp>


class Projectile2;
class MovingAnimation : public sf::Drawable
{
protected:
    sf::Vector2f CurrentKnockbackForce = sf::Vector2f(0,0); // Current knockback force applied to the entity
    float KnockbackResistance = 10.0f; // Resistance to knockback, 0 means no resistance, 1 means full resistance
public :
    Entity* entity; 
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
    MovingAnimation(const MovingAnimation& other, sf::Vector2f& position)
        : texture(other.texture), imageCount(other.imageCount), switchTime(other.switchTime),
          position(position), scale(other.scale), middlePosition(other.middlePosition)
    {
        totalTime = 0;
        row = 0;
        uvRect.top = 0;
        uvRect.left = 0;
        currentImage.x = 0;
        if(texture)
        {
            
            uvRect.width = int(texture->getSize().x / float(imageCount.x));
            uvRect.height = int(texture->getSize().y / float(imageCount.y));
            sprite.setTexture(*texture);
        }else {
            std::cerr << "MovingAnimation: Texture is null, sprite will not be drawn." << std::endl;
        }
        sprite.setScale(-scale, scale);
        mask = 0; 
		direction = rand() % 2 == 0 ? LEFT : RIGHT; // Randomly set the initial direction
    }
    MovingAnimation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, sf::Vector2f& position, float scale, sf::Vector2f middlePosition)
        :texture(texture), imageCount(imageCount), switchTime(switchTime), position(position), scale(scale), middlePosition(middlePosition)
    {
        totalTime = 0;
        row = 0;
        uvRect.top = 0;
        uvRect.left = 0;
        currentImage.x = 0;
        if(texture)
        {
            
            uvRect.width = int(texture->getSize().x / float(imageCount.x));
            uvRect.height = int(texture->getSize().y / float(imageCount.y));
            sprite.setTexture(*texture);
        }else {
            std::cerr << "MovingAnimation: Texture is null, sprite will not be drawn." << std::endl;
        }
        sprite.setScale(-scale, scale);
        mask = 0; 
		direction = rand() % 2 == 0 ? LEFT : RIGHT; // Randomly set the initial direction
    }
    virtual ~MovingAnimation();
    virtual void update(sf::Time dt);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const;
    virtual void handleCollision(const Entity* other) {} // Handle collision with another entity
    virtual void chase(Entity* target,sf::Time dt); 
    virtual void wander(sf::Time dt); 
    virtual void Knockback(sf::Vector2f force);// Handle knockback effect
    virtual void Knockback(const Projectile2* projectile, float Force = 1000.0f, Entity *other = nullptr);
    virtual sf::Vector2f getHandPosition()const;
    void setSpriteScale(float scale);
    void setSpriteRotation(float angle);
    void teleport(sf::Vector2f position); 
public:
    sf::FloatRect getBoundingBox() const {
        sf::FloatRect boundingBox = sprite.getGlobalBounds();
        // shrink it a bit
        boundingBox.left += boundingBox.width * (1 - shrinkScaleSize) / 2;
        boundingBox.top += boundingBox.height * (1 - shrinkScaleSize) / 2;
        boundingBox.width *= shrinkScaleSize;
        boundingBox.height *= shrinkScaleSize;
        return boundingBox;
    }
    void setState(State newState);

protected: 
    Direction direction;
    virtual void setSpritePosition(); 

    float shrinkScaleSize = 0.8f;
};

class Character_MovingAnimation : public MovingAnimation 
{
    enum Direction
    {
        LEFT,
        RIGHT
    }; 
    Direction direction; 
private: 
    int jump = 0; 
    int distancefromground = 0; 
    bool moveX; 
    bool moveY;
    EntityAttributeActionComponent *attribute;
    
public :
    Character_MovingAnimation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, sf::Vector2f& position, float scale, Entity* entity ,sf::Vector2f middlePosition = sf::Vector2f(0.5f, 1), EntityAttributeActionComponent* attribute = nullptr); // Constructor with parameters
    ~Character_MovingAnimation();
    virtual void update(sf::Time dt);
    virtual void handleEvent(const sf::Event& event,sf::RenderWindow* window);
    virtual void handleCollision(const Entity* other); 
    void getshot(const Entity* other);
    void setSpritePosition();  
	sf::Vector2f getHandPosition()const; // Get the hand position for weapon activation
};

class ShortRangeMob_MovingAnimation : public MovingAnimation
{   
private : 
    float attackRange; 
public:
    ShortRangeMob_MovingAnimation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, sf::Vector2f& position, float scale, Entity* entity, sf::Vector2f middlePosition = sf::Vector2f(0.5f, 1));
    ~ShortRangeMob_MovingAnimation();

    virtual void handleCollision(const Entity* other);
    void getshot(const Entity* other); 
};

class HighRangeMob_MovingAnimation : public MovingAnimation
{
private : 
    float attackRange; 
public:
    HighRangeMob_MovingAnimation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, sf::Vector2f& position, float scale, Entity* entity, sf::Vector2f middlePosition = sf::Vector2f(0.5f, 1));
    ~HighRangeMob_MovingAnimation();
    virtual void handleCollision(const Entity* other);
    void getshot(const Entity* other);
   
};
class SlashProjectile_MovingAnimation : public MovingAnimation
{
    float angle = 0.5f; // Angle for the projectile movement
public:
    SlashProjectile_MovingAnimation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, sf::Vector2f& position, float scale,float Angle = 0.5f, sf::Vector2f middlePosition = sf::Vector2f(0.5f, 1));
    SlashProjectile_MovingAnimation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, sf::Vector2f& position, float scale, sf::Vector2f startPosition, sf::Vector2f endPosition, sf::Vector2f middlePosition = sf::Vector2f(0.5f, 1));
    ~SlashProjectile_MovingAnimation();
    virtual void update(sf::Time dt);
    virtual void handleEvent(const sf::Event& event, sf::RenderWindow* window);
    virtual void handleCollision(const Entity* other);
};


class Explosion_Animation : public MovingAnimation
{
public:
    Explosion_Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, sf::Vector2f& position, float scale, sf::Vector2f middlePosition = sf::Vector2f(0.5f, 0.5f));
    ~Explosion_Animation();
    virtual void update(sf::Time dt);
    virtual void handleEvent(const sf::Event& event, sf::RenderWindow* window);
    virtual void handleCollision(const Entity* other);
};

class laserAimAnimation : public MovingAnimation
{
private:
    sf::Vector2f BeginPosition;
    sf::Vector2f TargetPosition;
    
public:
    laserAimAnimation(sf::Vector2f BeginPosition, sf::Vector2f targetPosition, sf::Vector2f middlePosition , sf::Vector2f& position)
        : BeginPosition(BeginPosition), TargetPosition(targetPosition), 
        MovingAnimation(nullptr, sf::Vector2u(0.f, 0.f), 0, position, 1.0f, sf::Vector2f(0.5f, 0.5f)) {}

    void draw(sf::RenderTarget& target, sf::RenderStates states)const override;
    void update(sf::Time dt) {}
};

class LaserAnimation : public MovingAnimation
{
private:
    sf::Vector2f startPosition;
    sf::Vector2f endPosition;
    float elapseTime = 0.0f;
    sf::Texture* BallTexture;
    sf::Sprite ballSprite1 , ballSprite2 , supportSprite;
    Projectile2* owner = nullptr; // Pointer to the owner projectile
public:
    LaserAnimation(sf::Texture *texture, sf::Vector2f startPosition, sf::Vector2f endPosition, sf::Vector2f middlePosition, sf::Vector2f& position);
    ~LaserAnimation() {
        if (BallTexture) {
            delete BallTexture; // Clean up the ball texture if it was dynamically allocated
        }
    }
    void update(sf::Time dt) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
    void ReCalculateScale();
    void setOwner(Projectile2* projectile) {
        owner = projectile;
    }
}; 

class HoldLaserAnimation : public MovingAnimation
{
private:
    sf::Vector2f startPosition;
    sf::Vector2f endPosition;
    float elapseTime = 0.0f;
    sf::Texture* BallTexture;
    sf::Sprite ballSprite1 , ballSprite2 , supportSprite;
    Projectile2* owner; // Pointer to the owner projectile

    void ReCalculateScale();
public:
    HoldLaserAnimation(sf::Texture *texture, sf::Vector2f middlePosition, sf::Vector2f& position);
    ~HoldLaserAnimation() {
        if (BallTexture) {
            delete BallTexture; // Clean up the ball texture if it was dynamically allocated
        }
    }
    void update(sf::Time dt) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
  
public:
    void setOwner(Projectile2* projectile) {
        owner = projectile;
    }
};