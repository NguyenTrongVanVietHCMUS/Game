#pragma once
#include <Book/Utility.hpp>
#include <Book/StrategyClass.hpp>
#include <Control/State.hpp>
#include <Book/MovingAnimation.hpp>
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
    Projectile2(std::string name,float LifeTime,sf::Vector2f position, State* CurrentMap, std::string texturePath,
        std::unique_ptr<IMovement> movement = nullptr, std::unique_ptr<ICollision> collision = nullptr, std::unique_ptr<MovingAnimation> animation = nullptr)
        : Entity(name, position), movementStrategy(std::move(movement)), collisionStrategy(std::move(collision)), currentMap(CurrentMap), movingAnimation(std::move(animation)) {
            // Load the projectile texture
            if (!texture.loadFromFile(texturePath)) {
                throw std::runtime_error("Failed to load projectile texture");
            }
            attributes["MaxLifeTime"] = LifeTime; // Set the maximum lifetime of the projectile
            sprite.setTexture(texture);
            // update hitbox size
            hitbox.hitbox = sf::FloatRect(position.x, position.y, texture.getSize().x, texture.getSize().y);
            // set origin hitbox to center of the sprite
            
            sprite.setOrigin(texture.getSize().x / 2.f, texture.getSize().y);
        }
    void setBehavior(std::unique_ptr<IMovement> movement, std::unique_ptr<ICollision> collision);
    void setMovement(std::unique_ptr<IMovement> movement);
    void setCollision(std::unique_ptr<ICollision> collision);
    void setMovingAnimation(std::unique_ptr<MovingAnimation> animation);
    void addTrailEffect(std::unique_ptr<IEffect> effect);

    void setAttribute(const std::string& attributeName, float value);
    float getAttribute(const std::string& attributeName) const;

    bool update(sf::Time dt) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void collide(const Entity* other) override;
};