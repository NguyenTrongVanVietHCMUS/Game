#pragma once
#include <Book/Utility.hpp>
#include <Book/StrategyClass.hpp>
class Projectile2 : public Entity
{
private:
    std::unique_ptr<IMovement> movementStrategy; // Strategy for movement
    std::unique_ptr<ICollision> collisionStrategy; // Strategy for collision handling
    std::vector<std::unique_ptr<IEffect>> trailStrategies; // Strategies for visual trails
public:
    Projectile2(std::string name, sf::Vector2f position, std::unique_ptr<IMovement> movement = nullptr, std::unique_ptr<ICollision> collision = nullptr)
        : Entity(name, position), movementStrategy(std::move(movement)), collisionStrategy(std::move(collision)) {}
    void setBehavior(std::unique_ptr<IMovement> movement, std::unique_ptr<ICollision> collision);
    void setMovement(std::unique_ptr<IMovement> movement);
    void setCollision(std::unique_ptr<ICollision> collision);
    void addTrailEffect(std::unique_ptr<IEffect> effect);

    bool update(const sf::Time& dt) override;
    void collide(const Entity* other) override;
};