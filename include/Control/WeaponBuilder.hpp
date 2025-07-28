#pragma once
#include<Book/Weapon2.hpp>
#include<Book/StrategyClass.hpp>
#include<Book/Utility.hpp>


class WeaponBuilder
{
    std::string             _name;
    sf::Vector2f            _position;
    
    std::unique_ptr<IBehavior> _behavior = nullptr;
    std::unique_ptr<IWeaponAnimation> _animation = nullptr;
    std::unique_ptr<ICooldownBehavior> _cooldownBehavior = nullptr;
    sf::Vector2f            _scaleBulletSpawnPosition = sf::Vector2f(0, 0); // Position where the bullet spawns based on the weapon's scale

    State*                  _worldmap;

    WeaponBuilder(std::string name, sf::Vector2f position, State* worldmap = nullptr)
        : _name(std::move(name)), _position(position), _worldmap(worldmap) {}
public:
    static WeaponBuilder create(std::string name, sf::Vector2f position, State* worldmap = nullptr)
    {
        return WeaponBuilder(std::move(name), position, worldmap);
    }

    WeaponBuilder& withBehavior(std::unique_ptr<IBehavior> behavior)
    {
        _behavior = std::move(behavior);
        return *this;
    }

    WeaponBuilder& withAnimation(std::unique_ptr<IWeaponAnimation> animation)
    {
        _animation = std::move(animation);
        return *this;
    }
    WeaponBuilder& withCooldownBehavior(std::unique_ptr<ICooldownBehavior> cooldownBehavior)
    {
        _cooldownBehavior = std::move(cooldownBehavior);
        return *this;
    }
    WeaponBuilder& withCooldownTime(float cooldownTime)
    {
        _cooldownBehavior = std::make_unique<BasicCooldownBehavior>(cooldownTime);
        return *this;
    }

    WeaponBuilder& withMap(State* worldmap)
    {
        _worldmap = worldmap;
        return *this;
    }

    WeaponBuilder& withScaleBulletSpawnPosition(sf::Vector2f scaleBulletSpawnPosition)
    {
        _scaleBulletSpawnPosition = scaleBulletSpawnPosition;
        return *this;
    }

    Weapon2 build()
    {
        std::unique_ptr<IBehavior> behaviorPtr = _behavior? _behavior->clone() : nullptr;
        std::unique_ptr<IWeaponAnimation> animationPtr = _animation? _animation->clone() : nullptr;
        std::unique_ptr<ICooldownBehavior> cooldownBehaviorPtr = _cooldownBehavior? _cooldownBehavior->clone() : nullptr;
        return Weapon2(
            _name,
            _position,
            std::move(behaviorPtr),
            std::move(animationPtr),
            std::move(cooldownBehaviorPtr),
            _scaleBulletSpawnPosition,
            _worldmap
        );
    }
};