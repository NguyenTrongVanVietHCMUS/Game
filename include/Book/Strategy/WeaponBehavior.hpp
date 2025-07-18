#pragma once
#include <Book/Utility.hpp>
#include <Book/StrategyClass.hpp>
#include <Book/Entity.hpp>
#include <Book/Strategy/ProjectileBehavior.hpp>
#include <Book/Strategy/CollisionBehavior.hpp>
#include <Control/State.hpp>
#include <Book/MovingAnimation.hpp>
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


    void activate(Weapon2& self, Entity* target) override{
        float posX = self.getStat("TargetPosX");
        float posY = self.getStat("TargetPosY");
        // normalize the direction vector
        sf::Vector2f SpawnPosition = self.GetProjectileSpawnPosition();
        sf::Vector2f direction =  sf::Vector2f(posX, posY) - SpawnPosition;

        //std::cerr << "Projectile speed X: " << projectileSpeedX << ", Y: " << projectileSpeedY << std::endl;
        float offsetAngle = dist(rng); // Randomly offset the angle within the spread range
        float cosA = std::cos(offsetAngle * 3.14159265358979323846f / 180.0f); // Convert angle to radians
        float sinA = std::sin(offsetAngle * 3.14159265358979323846f / 180.0f); // Convert angle to radians
        sf::Vector2f RotatedDirection(
            direction.x * cosA - direction.y * sinA,
            direction.x * sinA + direction.y * cosA
        );
        float len = std::sqrt(RotatedDirection.x * RotatedDirection.x + RotatedDirection.y * RotatedDirection.y);
        float projectileSpeedX = projectileSpeed * (RotatedDirection.x / len),
              projectileSpeedY = projectileSpeed * (RotatedDirection.y / len);

        auto proj = new Projectile2(
            "RangedProjectile",
            15.0f, // as seconds represent life time of the projectile
            SpawnPosition,
            Worldmap,
            "Media/Assets/Projectiles/PurpleBullet.png", // Path to the projectile texture
            std::make_unique<FollowMovement>(projectileSpeedX, projectileSpeedY, projectileSpeed, Worldmap, 60.0f),
            std::make_unique<ProjectileCollisionBehavior>(Worldmap)
        );
        std::cerr << "Spawn Bullet\n";
        proj->type = self.ProjectileTypeTransform(target); // Transform the projectile type based on the target type
        proj->update(sf::seconds(0)); // Initialize the projectile's animation
        Worldmap->pushEntity(proj);
    }
};


struct MeleeWeaponBehavior : public IBehavior
{
private:
    State* Worldmap = nullptr;
public:
    MeleeWeaponBehavior(State* worldmap) : Worldmap(worldmap) {}

    void activate(Weapon2& self, Entity* target) override {
        sf::Texture* texture = new sf::Texture();
        if(!texture->loadFromFile("Media/Assets/Projectiles/sword_slash.png")) {
            throw std::runtime_error("Failed to load melee projectile texture");
        }
        float posX = self.getStat("TargetPosX");
        float posY = self.getStat("TargetPosY");

        // normalize the direction vector
        sf::Vector2f SpawnerPosition = self.GetProjectileSpawnPosition();
        sf::Vector2f direction = SpawnerPosition - sf::Vector2f(posX, posY);
        float Angle = std::atan2(direction.y, direction.x); // Calculate the angle of the melee attack
        // Offset the position of the projectile to be in front of the target
        sf::Vector2f offset(25.0f * std::cos(Angle), 25.0f * std::sin(Angle)); // Offset by 50 pixels in the direction of the attack

        auto proj = new Projectile2(
            "MeleeProjectile",
            0.12f, // as seconds
            SpawnerPosition,
            Worldmap,
            "Media/Assets/Projectiles/sword_slash.png", // Path to the projectile texture
            nullptr, // No movement for melee
            std::make_unique<MeleeCollisionBehavior>(Worldmap), // Melee collision behavior
            nullptr
        );
        proj->position -= offset; // Set the position of the projectile to be in front of the target
        std::unique_ptr<MovingAnimation> movingAnimation = std::make_unique<SlashProjectile_MovingAnimation>(
            texture, 
            sf::Vector2u(3, 1), 
            0.04f, // Switch time for the animation
            proj->position, 
            5.0f, // Scale of the animation
            Angle,
            sf::Vector2f(0.5f, 0.5f) // Middle position for the animation
        );
        proj->type = self.ProjectileTypeTransform(target); // Transform the projectile type based on the target type
        proj->updateHitboxOnPosition(); // Update the hitbox position based on the entity's current position
        proj->setMovingAnimation(std::move(movingAnimation));
        proj->update(sf::seconds(0)); // Initialize the projectile's animation
        Worldmap->pushEntity(proj);
    }
};

class ThrowBehavior : public IBehavior
{
private:
    State* Worldmap = nullptr;
public:
    ThrowBehavior(State* worldmap) : Worldmap(worldmap) {}

    void activate(Weapon2& self, Entity* target) override {
        sf::Texture* bombText = new sf::Texture(ResourceManager::getInstance().get<sf::Texture>(Textures::ID::bomb));
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
        proj->type = target->type;
        proj->update(sf::seconds(0)); // Initialize the projectile's animation
        Worldmap->pushEntity(proj);
    }

};