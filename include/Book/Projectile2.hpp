#pragma once
#include <Book/Utility.hpp>
#include <Book/StrategyClass.hpp>
#include <Control/State.hpp>
#include <Book/MovingAnimation.hpp>
#include <Control/State.hpp>
class Projectile2 : public Entity
{
private:
    std::unique_ptr<IMovement> movementStrategy; // Strategy for movement
    std::unique_ptr<ICollision> collisionStrategy; // Strategy for collision handling
    std::unique_ptr<MovingAnimation> movingAnimation; // Animation for the projectile
    std::vector<std::unique_ptr<IEffect>> trailStrategies; // Strategies for visual trails
    sf::Sprite sprite; // Sprite representing the projectile
    sf::Texture texture; // Texture for the projectile sprite
    std::unordered_map<std::string, float> attributes; // Additional stats for the projectile

    State* currentMap; // Pointer to the current map or state
public:
    // Basic constructor for builder
    Projectile2(std::string name, float lifeTime, sf::Vector2f position, State* currentMap, std::string texturePath);

    Projectile2(std::string name,float LifeTime,sf::Vector2f position, State* CurrentMap, std::string texturePath,
        std::unique_ptr<IMovement> movement = nullptr, std::unique_ptr<ICollision> collision = nullptr, std::unique_ptr<MovingAnimation> animation = nullptr);

    Projectile2(std::string name,float LifeTime,sf::Vector2f position, float scale, State* CurrentMap, std::string texturePath,
    std::unique_ptr<IMovement> movement = nullptr, std::unique_ptr<ICollision> collision = nullptr, std::unique_ptr<MovingAnimation> animation = nullptr);
    
    void setBehavior(std::unique_ptr<IMovement> movement, std::unique_ptr<ICollision> collision);
    void setMovement(std::unique_ptr<IMovement> movement);
    void setCollision(std::unique_ptr<ICollision> collision);
    void setMovingAnimation(std::unique_ptr<MovingAnimation> animation);
    void addTrailEffect(std::unique_ptr<IEffect> effect);

    void setSpriteScale(float scale);
    void setSpriteRotation(float angle);
    void setAttribute(const std::string& attributeName, float value);
    float getAttribute(const std::string& attributeName) const;

    bool update(sf::Time dt) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void collide(const Entity* other) override;
};