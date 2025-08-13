#pragma once
#include <Book/Utility.hpp>
#include <Book/Entity.hpp>
#include <Book/Projectile2.hpp>
#include <Control/State.hpp>
class StraightMovement : public IMovement
{
private:
    float speedX, speedY;
    float speed;
public:
    StraightMovement(float speed, sf::Vector2f StartPosition, sf::Vector2f EndPosition)
        : speed(speed)
    {
        sf::Vector2f direction = EndPosition - StartPosition;
        setDirection(direction);
    }
    StraightMovement(float speedX, float speedY) : speedX(speedX), speedY(speedY) {}
    StraightMovement(float speed) : speed(speed) {}
    void update(Projectile2& projectile, const sf::Time &dt) override
    {
        // Update the position of the projectile based on its speed and the elapsed time
        projectile.position.x += speedX * dt.asSeconds();
        projectile.position.y += speedY * dt.asSeconds();
        float CurrentAngle = std::atan2(speedY, speedX);
        projectile.setAttribute("CurrentAngle", CurrentAngle);
        projectile.updateHitboxOnPosition(); // Update the hitbox position based on the new position
    }

    std::unique_ptr<IMovement> clone() const override
    {
        return std::make_unique<StraightMovement>(*this);
    }

    virtual void setDirection(sf::Vector2f direction) override
    {
        // Normalize the direction vector and set the speed components
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        if (length > 0)
        {
            speedX = (direction.x / length) * speed;
            speedY = (direction.y / length) * speed;
        }
    }

    sf::Vector2f getDirection() const override
    {
        return sf::Vector2f(speedX, speedY);
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
    FollowMovement(float speed, sf::Vector2f startPosition, sf::Vector2f endPosition, State* worldmap, float criticalAngle = 60.0f)
        : speed(speed), Worldmap(worldmap), CriticalAngle(criticalAngle * 3.14f / 180.0f)
    {
        // Calculate the direction vector and set the speed components
        sf::Vector2f direction = endPosition - startPosition;
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    
        if (length > 0)
        {
            speedX = (direction.x / length) * speed;
            speedY = (direction.y / length) * speed;
        }
    }
    FollowMovement(float speed, State* worldmap) : speed(speed), Worldmap(worldmap), speedX(0), speedY(0) {}
    FollowMovement(float speedX, float speedY, float speed, State* worldmap, float criticalAngle) : speed(speed), speedX(speedX), speedY(speedY), Worldmap(worldmap), CriticalAngle(criticalAngle * 3.14f / 180.0f) {}
    void update(Projectile2& projectile, const sf::Time& dt) override;
    
    std::unique_ptr<IMovement> clone() const override
    {
        return std::make_unique<FollowMovement>(*this);
    }
    void setDirection(sf::Vector2f direction) override
    {
        // Normalize the direction vector and set the speed components
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        if (length > 0)
        {
            speedX = (direction.x / length) * speed;
            speedY = (direction.y / length) * speed;
        }
    }
    sf::Vector2f getDirection() const override
    {
        return sf::Vector2f(speedX, speedY);
    }
};

class ThrowMovement : public IMovement
{
private:
    float RotationSpeed = 200.0f;
    float speedX, speedY;
    float heightVelocity;
    float gravity = 9.8f; // Gravity constant
    float CurrentHeight = 0.0f;
    float HeightScale = 100.0f;
    float OriginalScale;
    float HeightSpriteScale = 0.3f;
    State *Worldmap = nullptr;
    //Random Current rotation
    float CurrentRotation = static_cast<float>(rand() % 360); // Current rotation of the projectile
public:
    ThrowMovement(float speedX, float speedY, float InitVelocity , float OriginalScale = 1.0f, State* worldmap = nullptr) 
        : speedX(speedX), speedY(speedY), heightVelocity(InitVelocity), OriginalScale(OriginalScale), Worldmap(worldmap) {}
    ThrowMovement(  float FlyTime,
                    sf::Vector2f StartPosition,sf::Vector2f TargetPosition ,
                    float OriginalScale = 1.0f , State* worldmap = nullptr)
        : OriginalScale(OriginalScale), Worldmap(worldmap) {
            sf::Vector2f direction = TargetPosition - StartPosition;
            heightVelocity = FlyTime * gravity / 2 ;
            speedX = direction.x / FlyTime;
            speedY = direction.y / FlyTime;

        }
    void update(Projectile2& projectile, const sf::Time& dt) override;

    std::unique_ptr<IMovement> clone() const override{
        return std::make_unique<ThrowMovement>(*this);
    }

    sf::Vector2f getDirection() const override
    {
        return sf::Vector2f(speedX, speedY);
    }
};

class LaserBeamMovement : public IMovement
{
private:
    float HitCycle;
    float elapsedTime = 0.0f;
    State* Worldmap = nullptr;
    sf::Vector2f startPosition, endPosition;
public:
    LaserBeamMovement(float hitCycle, sf::Vector2f startPosition, sf::Vector2f endPosition, State* worldmap) : HitCycle(hitCycle), startPosition(startPosition), endPosition(endPosition), Worldmap(worldmap) {}

    void update(Projectile2& projectile, const sf::Time& dt) override;

    std::unique_ptr<IMovement> clone() const override {
        return std::make_unique<LaserBeamMovement>(*this);
    }

    sf::Vector2f getDirection() const override
    {
        return (endPosition - startPosition);
    }
};

class LaserAimMovement : public IMovement
{
private:
    float aimTime;
    float elapsedTime = 0.0f;
    sf::Vector2f startPosition, endPosition;
    State* Worldmap = nullptr;
public:
    LaserAimMovement(float aimTime, sf::Vector2f startPosition, sf::Vector2f endPosition, State* worldmap)
        : aimTime(aimTime), startPosition(startPosition), endPosition(endPosition), Worldmap(worldmap) {}

    void update(Projectile2& projectile, const sf::Time& dt) override;

    std::unique_ptr<IMovement> clone() const override {
        return std::make_unique<LaserAimMovement>(*this);
    }

    sf::Vector2f getDirection() const override
    {
        return (endPosition - startPosition);
    }
};