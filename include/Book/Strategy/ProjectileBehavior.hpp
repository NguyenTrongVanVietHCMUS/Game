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

    void update(Projectile2& projectile, const sf::Time &dt) override
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
    float RotationSpeed = 200.0f;
    float speedX, speedY;
    float heightVelocity;
    float gravity = 9.8f; // Gravity constant
    float CurrentHeight = 0.0f;
    float HeightScale = 100.0f;
    float OriginalScale;
    float HeightSpriteScale = 0.3f;
    //Random Current rotation
    float CurrentRotation = static_cast<float>(rand() % 360); // Current rotation of the projectile
public:
    ThrowMovement(float speedX, float speedY, float InitVelocity , float OriginalScale = 1.0f) 
        : speedX(speedX), speedY(speedY), heightVelocity(InitVelocity), OriginalScale(OriginalScale) {}
    ThrowMovement(  float FlyTime,
                    sf::Vector2f StartPosition,sf::Vector2f TargetPosition ,
                    float OriginalScale = 1.0f)
        : OriginalScale(OriginalScale) {
            sf::Vector2f direction = TargetPosition - StartPosition;
            heightVelocity = FlyTime * gravity / 2 ;
            speedX = direction.x / FlyTime;
            speedY = direction.y / FlyTime;

        }
    void update(Projectile2& projectile, const sf::Time& dt) override;

    std::unique_ptr<IMovement> clone() const override{
        return std::make_unique<ThrowMovement>(*this);
    }
};