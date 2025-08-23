#pragma once
#include <Control/StrategyFactory.hpp>

class ProjectileBuilder
{
    std::string             _name;
    float                   _lifeTime;
    sf::Vector2f            _position;
    float                   _scale;
    std::string             _texturePath;
    State*                  _map;

    // optional strategies
    std::unique_ptr<IMovement>     _movement   = nullptr;
    std::unique_ptr<ICollision>    _collision  = nullptr;
    std::unique_ptr<MovingAnimation> _animation = nullptr;
    std::vector<std::unique_ptr<IEffect>> _effects;

    ProjectileBuilder(
        std::string name,
        float lifeTime,
        sf::Vector2f position,
        float scale,
        std::string texPath,
        State* map
    )
    : _name(std::move(name))
    , _lifeTime(lifeTime)
    , _position(position)
    , _scale(scale)
    , _texturePath(std::move(texPath))
    , _map(map)
    {}

public:
    static ProjectileBuilder create(
        std::string name,
        float lifeTime,
        sf::Vector2f position,
        float scale,
        std::string texPath,
        State* map
    ) {
        return ProjectileBuilder(
            std::move(name),
            lifeTime,
            position,
            scale,
            std::move(texPath),
            map
        );
    }

    ProjectileBuilder& withMovement(std::unique_ptr<IMovement> m) {
        _movement = std::move(m);
        return *this;
    }
    ProjectileBuilder& withCollision(std::unique_ptr<ICollision> c) {
        _collision = std::move(c);
        return *this;
    }
    ProjectileBuilder& withMovingAnimation(std::unique_ptr<MovingAnimation> a) {
        _animation = std::move(a);
        return *this;
    }
    ProjectileBuilder& addEffect(std::unique_ptr<IEffect> e) {
        _effects.push_back(std::move(e));
        return *this;
    }

    Projectile2 * build() {
        auto proj = new Projectile2(
            _name,
            _lifeTime,
            _position,
            _scale,
            _map,
            _texturePath,
            std::move(_movement),
            std::move(_collision),
            std::move(_animation)
        );

        return proj;
    }
};