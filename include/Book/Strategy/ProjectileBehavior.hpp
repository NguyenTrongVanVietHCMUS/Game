#pragma once
#include <Book/Utility.hpp>
#include <Book/Entity.hpp>
#include <Book/Projectile2.hpp>
#include <Control/State.hpp>
class StraightMovement : public IMovement
{
private:
    float speedX, speedY;

public:
    StraightMovement(float speedX, float speedY) : speedX(speedX), speedY(speedY) {}

    void update(Projectile2& projectile, const sf::Time& dt) override
    {
        // Update the position of the projectile based on its speed and the elapsed time
        projectile.position.x += speedX * dt.asSeconds();
        projectile.position.y += speedY * dt.asSeconds();
        projectile.updateHitboxOnPosition(); // Update the hitbox position based on the new position
    }

    std::unique_ptr<IMovement> clone() const override
    {
        return std::make_unique<StraightMovement>(*this);
    }
};

class FollowMovement : public IMovement
{
private:
    float speed;
    float CriticalAngle = 0.0f;
    float speedX, speedY;

    State* Worldmap = nullptr;
    Entity* target = nullptr; // Target entity to follow
public:
    FollowMovement(float speed, State* worldmap) : speed(speed), Worldmap(worldmap), speedX(0), speedY(0) {}
    FollowMovement(float speedX, float speedY, float speed, State* worldmap, float criticalAngle) : speed(speed), speedX(speedX), speedY(speedY), Worldmap(worldmap), CriticalAngle(criticalAngle * 3.14f / 180.0f) {}
    void update(Projectile2& projectile, const sf::Time& dt) override;
    
    std::unique_ptr<IMovement> clone() const override
    {
        return std::make_unique<FollowMovement>(*this);
    }
};

class ThrowMovement : public IMovement
{
private:
    float speedX, speedY;
    float heightVelocity;
    float gravity = 9.81f; // Gravity constant
    float CurrentHeight = 0.0f;
    float initialHeight = 0.0f; // Initial height of the projectile
public:
    ThrowMovement(float speedX, float speedY, float initialHeight) 
        : speedX(speedX), speedY(speedY), initialHeight(initialHeight), heightVelocity(initialHeight) {}
    
    void update(Projectile2& projectile, const sf::Time& dt) override;

    std::unique_ptr<IMovement> clone() const override{
        return std::make_unique<ThrowMovement>(*this);
    }
};