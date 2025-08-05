#pragma once
#include <Book/Utility.hpp>
#include <Book/StrategyClass.hpp>
#include <Book/Entity.hpp>
#include <Book/Strategy/ProjectileBehavior.hpp>
#include <Book/Strategy/CollisionBehavior.hpp>
#include <Control/State.hpp>
#include <Book/MovingAnimation.hpp>
#include <Control/ResourceManager.hpp>
#include <random>
class RangedWeaponBehavior : public IBehavior
{
private:
    float SpreadAngle = 0.0f;  
    std::mt19937 rng{ std::random_device{}() };
    std::uniform_real_distribution<float> dist{-SpreadAngle, SpreadAngle};
public:
    float projectileSpeed;
    State* Worldmap = nullptr;
    RangedWeaponBehavior(State* worldmap, float speed, float spread = 0.0f) : Worldmap(worldmap), projectileSpeed(speed), SpreadAngle(spread) {}

    void activate(Weapon2& self, Entity* target) override;
    std::unique_ptr<IBehavior> clone() const override {
        return std::make_unique<RangedWeaponBehavior>(*this);
    }
};


struct MeleeWeaponBehavior : public IBehavior
{
private:
    State* Worldmap = nullptr;
public:
    MeleeWeaponBehavior(State* worldmap) : Worldmap(worldmap) {}

    void activate(Weapon2& self, Entity* target) override;
    std::unique_ptr<IBehavior> clone() const override {
        return std::make_unique<MeleeWeaponBehavior>(*this);
    }
};

class ThrowBehavior : public IBehavior
{
private:
    State* Worldmap = nullptr;
public:
    ThrowBehavior(State* worldmap) : Worldmap(worldmap) {}

    void activate(Weapon2& self, Entity* target) override {
        sf::Texture* bombText = &ResourceManager::getInstance().get<sf::Texture>(Textures::ID::bomb);
        float posX = self.getStat("TargetPosX");
        float posY = self.getStat("TargetPosY");
        std::cerr << "Position X: " << posX << ", Y: " << posY << std::endl;
        // normalize the direction vector
        sf::Vector2f direction = sf::Vector2f(posX, posY) - target->getPosition();
        float Angle = std::atan2(direction.y, direction.x); // Calculate the angle of the throw
        // Offset the position of the projectile to be in front of the target
        sf::Vector2f offset(25.0f * std::cos(Angle), 25.0f * std::sin(Angle)); // Offset by 50 pixels in the direction of the throw
        float len = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        float projectileSpeedX = 500.0f * (direction.x / len),
              projectileSpeedY = 500.0f * (direction.y / len);
        auto proj = new Projectile2(
            "ThrowingBomb",
            1000.0f, // as seconds
            target->getPosition(),
            2.5f,
            Worldmap,
            "Media/Assets/Projectiles/bomb.png", // Path to the projectile texture
            std::make_unique<ThrowMovement>(1.0f, target->getPosition(), sf::Vector2f(posX, posY) , 2.5f, Worldmap), // No movement for melee
            nullptr,
            nullptr
        );
        proj->type = self.ProjectileTypeTransform(target); // Set the projectile type based on the target
        proj->update(sf::seconds(0)); // Initialize the projectile's animation
        Worldmap->pushEntity(proj);
    }
    std::unique_ptr<IBehavior> clone() const override {
        return std::make_unique<ThrowBehavior>(*this);
    }
};

class laserGunBehavior : public IBehavior
{
private:
    State* Worldmap = nullptr;
public:
    laserGunBehavior(State* worldmap) : Worldmap(worldmap) {}
    void activate(Weapon2& self, Entity* target) override ;
    std::unique_ptr<IBehavior> clone() const override {
        return std::make_unique<laserGunBehavior>(*this);
    }
};