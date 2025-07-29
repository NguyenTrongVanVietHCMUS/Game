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
};

class LaserBeamMovement : public IMovement
{
private:
    float HitCycle;
    float elapsedTime = 0.0f;
public:
    LaserBeamMovement(float hitCycle) : HitCycle(hitCycle) {}

    void update(Projectile2& projectile, const sf::Time& dt) override {
        elapsedTime += dt.asSeconds();
        if (elapsedTime >= HitCycle) {
            elapsedTime = 0.0f; // Reset the timer
        }

    }

    std::unique_ptr<IMovement> clone() const override {
        return std::make_unique<LaserBeamMovement>(*this);
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

    void update(Projectile2& projectile, const sf::Time& dt) override {
        elapsedTime += dt.asSeconds();
        if (elapsedTime >= aimTime) {
            // Logic for when the laser beam is ready to fire
            aimTime = 1000000.0f;
            elapsedTime = 0.0f; // Reset the timer
            auto proj = new Projectile2(
                "LaserBeam",
                0.2f, // Lifetime of the laser beam
                startPosition,
                Worldmap,
                "Media/Assets/Projectiles/Laser.png", // Path to the laser beam texture
                std::make_unique<LaserBeamMovement>(0.1f), // Movement strategy for the laser beam
                nullptr, // No collision strategy for the laser beam
                nullptr
            );
            sf::Texture* texture = new sf::Texture();
            if (!texture->loadFromFile("Media/Assets/Projectiles/Laser.png")) {
                throw std::runtime_error("Failed to load laser beam texture");
            }
            std::unique_ptr<MovingAnimation> animation = std::make_unique<LaserAnimation>(
                texture,
                startPosition,
                endPosition,
                sf::Vector2f(0.5f, 0.5f),
                proj->position
            );
            proj->setMovingAnimation(std::move(animation));
            proj->type = projectile.type;
            proj->update(sf::seconds(0)); // Initialize the projectile's animation
            Worldmap->pushEntity(proj); // Add the laser beam to the world map
        }
    }

    std::unique_ptr<IMovement> clone() const override {
        return std::make_unique<LaserAimMovement>(*this);
    }
};