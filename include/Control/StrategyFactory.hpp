#pragma once
#include<Book/Strategyclass.hpp>
#include <nlohmann/json.hpp>
#include <Control/State.hpp>
#include <Book/Strategy/WeaponBehavior.hpp>
#include <Book/Strategy/WeaponAnimation.hpp>
using json = nlohmann::json;

class StrategyFactory
{
public:
    static std::unique_ptr<IBehavior> createBehavior(const json& data, State* map = nullptr)
    {
        auto it = behaviorRegistry().find(data.at("type").get<std::string>());
        if (it != behaviorRegistry().end())
        {
            return it->second(data, map);
        }
        throw std::runtime_error("Unknown behavior type: " + data.at("type").get<std::string>());
    }

    static std::unique_ptr<IWeaponAnimation> createAnimation(const json& data, Entity* owner)
    {
        auto it = animationRegistry().find(data.at("type").get<std::string>());
        if (it != animationRegistry().end())
        {
            return it->second(data, owner);
        }
        throw std::runtime_error("Unknown animation type: " + data.at("type").get<std::string>());
    }

    static std::unique_ptr<IMovement> createMovement(const json& data, State* map, sf::Vector2f startPos, sf::Vector2f endPos)
    {
        auto it = movingBehaviorRegistry().find(data.at("type").get<std::string>());
        if (it != movingBehaviorRegistry().end())
        {
            return it->second(data, map, startPos, endPos);
        }
        throw std::runtime_error("Unknown movement type: " + data.at("type").get<std::string>());
    }

    static std::unique_ptr<ICollision> createCollisionBehavior(const json& data, State* map)
    {
        auto it = collisionBehaviorRegistry().find(data.at("type").get<std::string>());
        if (it != collisionBehaviorRegistry().end())
        {
            return it->second(data, map);
        }
        throw std::runtime_error("Unknown collision behavior type: " + data.at("type").get<std::string>());
    }

    static std::unique_ptr<MovingAnimation> createMovingAnimation(const json& data, sf::Vector2f& position, sf::Vector2f startPosition = sf::Vector2f(0.0f, 0.0f), sf::Vector2f endPosition = sf::Vector2f(0.0f, 0.0f))
    {
        auto it = movingAnimationRegistry().find(data.at("type").get<std::string>());
        if (it != movingAnimationRegistry().end())
        {
            return it->second(data, position, startPosition, endPosition);
        }
        throw std::runtime_error("Unknown moving animation type: " + data.at("type").get<std::string>());
    }

private:
//SlashProjectile_MovingAnimation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, sf::Vector2f& position, float scale,float Angle = 0.5f, sf::Vector2f middlePosition = sf::Vector2f(0.5f, 1));
    using BehaviorFactoryMap = std::unordered_map<std::string, std::function<std::unique_ptr<IBehavior>(const json&, State*)>>;
    using AnimationFactoryMap = std::unordered_map<std::string, std::function<std::unique_ptr<IWeaponAnimation>(const json&, Entity*)>>;
    using MovingBehaviorFactoryMap = std::unordered_map<std::string, std::function<std::unique_ptr<IMovement>(const json&, State*, sf::Vector2f, sf::Vector2f)>>;
    using CollisionBehaviorFactoryMap = std::unordered_map<std::string, std::function<std::unique_ptr<ICollision>(const json&, State*)>>;
    using MovingAnimationFactoryMap = std::unordered_map<std::string, std::function<std::unique_ptr<MovingAnimation>(const json&, sf::Vector2f, sf::Vector2f, sf::Vector2f&)>>;
private:
    static std::unordered_map<std::string, sf::Texture*> textureCache;
private:
    // Factory methods for each type of behavior
    static BehaviorFactoryMap& behaviorRegistry()
    {
        static BehaviorFactoryMap registry{
            {"Ranged Weapon Behavior", [](const json& data, State* map){
                return std::make_unique<RangedWeaponBehavior>(map,
                    data.value("projectileSpeed", 500.0f),
                    data.value("spreadAngle", 0.0f));
            }},
            {"Melee Weapon Behavior", [](const json& data, State* map){
                return std::make_unique<MeleeWeaponBehavior>(map);
            }},
            {"Throw Weapon Behavior", [](const json& data, State* map)
            {
                return std::make_unique<ThrowBehavior>(map);
            }},
            {"Laser Weapon Behavior", [](const json& data, State* map)
            {
                return std::make_unique<laserGunBehavior>(map);
            }}
        };
        return registry;
    }

    static AnimationFactoryMap& animationRegistry()
    {
        static AnimationFactoryMap registry{
            {"Gun Animation", [](const json& data, Entity* owner){
                return std::make_unique<GunAnimation>(
                    data.at("totalTime").get<float>(),
                    data.at("scale").get<float>(),
                    getTexture(data.at("texture").get<std::string>()),
                    owner? owner->getPosition() : sf::Vector2f{0.0f, 0.0f},
                    data.value("startAngle", 0.0f),
                    data.value("endAngle", 0.0f),
                    data.value("recoilOffset", 0.0f),
                    owner,
                    sf::Vector2f(0.4f, 0.6f)
                );
            }},
            {"Sword Animation", [](const json& data, Entity* owner){
                return std::make_unique<SwordAnimation>(
                    data.at("totalTime").get<float>(),
                    data.at("scale").get<float>(),
                    getTexture(data.at("texture").get<std::string>()),
                    owner? owner->getHandPosition() : sf::Vector2f{0.0f, 0.0f},
                    data.value("startAngle", 0.0f),
                    data.value("endAngle", 0.0f),
                    owner,
                    sf::Vector2f(data.value("middlePositionX", 0.5f), data.value("middlePositionY", 0.5f))
                );

            }}
        };
        return registry;
    }

    static MovingBehaviorFactoryMap& movingBehaviorRegistry()
    {
        static MovingBehaviorFactoryMap registry{
            {"Follow Movement", [](const json& data, State* map, sf::Vector2f startPos, sf::Vector2f endPos){
                return std::make_unique<FollowMovement>(
                    data.value("speed", 500.0f),
                    startPos,
                    endPos,
                    map,
                    data.value("criticalAngle", 60.0f)
                );
            }},
            {"Straight Movement", [](const json& data, State* map, sf::Vector2f startPos, sf::Vector2f endPos){
                return std::make_unique<StraightMovement>(
                    data.value("Speed", 500.0f),
                    startPos,
                    endPos
                );
            }},
            {"Throw Movement", [](const json& data, State* map, sf::Vector2f startPos, sf::Vector2f endPos){
                return std::make_unique<ThrowMovement>(
                    data.value("FlyTime", 500.0f),
                    startPos,
                    endPos,
                    data.value("Scale", 1.0f),
                    map
                );

            }},
            {"Laser Beam Movement", [](const json& data, State* map, sf::Vector2f startPos, sf::Vector2f endPos){
                return std::make_unique<LaserBeamMovement>(
                    data.value("HitCycle", 0.5f)
                );

            }},
            {"Laser Aim Movement", [](const json& data, State* map, sf::Vector2f startPos, sf::Vector2f endPos){
                return std::make_unique<LaserAimMovement>(
                    data.value("AimTime", 1.0f),
                    startPos,
                    endPos,
                    map
                );
            }}
        };
        return registry;
    }

    static CollisionBehaviorFactoryMap& collisionBehaviorRegistry()
    {
        static CollisionBehaviorFactoryMap registry{
            {"Projectile Collision Behavior", [](const json& data, State* map){

                std::cerr << "Creating ProjectileCollisionBehavior " << std::endl;
                return std::make_unique<ProjectileCollisionBehavior>(map);
            }},
            {"Melee Collision Behavior", [](const json& data, State* map){
                return std::make_unique<MeleeCollisionBehavior>(map);
            }}
        };
        return registry;
    }

    static MovingAnimationFactoryMap& movingAnimationRegistry()
    {
        static MovingAnimationFactoryMap registry{
            {"Slash Projectile Animation", [](const json& data, sf::Vector2f startPosition, sf::Vector2f endPosition,sf::Vector2f& position){
                return std::make_unique<SlashProjectile_MovingAnimation>(
                    getTexture(data.at("texture").get<std::string>()),
                    sf::Vector2u(data.at("imageCount").at("x").get<float>(), data.at("imageCount").at("y").get<float>()),
                    data.at("switchTime").get<float>(),
                    position,
                    data.value("scale", 1.0f),
                    data.value("angle", 0.5f),
                    sf::Vector2f(data.value("middlePositionX", 0.5f), data.value("middlePositionY", 1.0f))
                );
            }}
        };
        return registry;
    }
private:
    static sf::Texture* getTexture(const std::string& texturePath)
    {
        auto it = textureCache.find(texturePath);
        if (it != textureCache.end())
        {
            return it->second;
        }
        sf::Texture* texture = new sf::Texture();
        if (!texture->loadFromFile(texturePath))
        {
            throw std::runtime_error("Failed to load texture: " + texturePath);
        }
        textureCache[texturePath] = texture;
        return texture;
    }
};