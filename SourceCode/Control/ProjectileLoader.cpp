#include <Control/ProjectileLoader.hpp>
#include "Control/ProjectileLoader.hpp"
#include "Control/StrategyFactory.hpp"
#include <fstream>
#include <stdexcept>
#include <cstdlib>

Projectile2* ProjectileLoader::LoadProjectile(const std::string& name, sf::Vector2f StartPosition, sf::Vector2f EndPosition) {
    std::ifstream in{filePath};
    if (!in.is_open())
        throw std::runtime_error("Failed to open projectile file: " + filePath);

    json data;
    in >> data;
    in.close();

    if (!data.contains(name))
        throw std::runtime_error("Projectile not found: " + name);
    auto& j = data[name];

    // core fields
    float        lifeTime   = j.value("lifeTime", 1.0f);
    sf::Vector2f position   = StartPosition;
    float        scale      = j.value("scale", 1.0f);
    std::string  texPath    = j.at("texturePath");

    // start builder
    auto builder = ProjectileBuilder::create(
        name, lifeTime, position, scale, texPath, mState
    );
    // optional movement
    if (j.contains("movement")) {
        sf::Vector2f endPos = EndPosition;
        builder.withMovement(
            StrategyFactory::createMovement(
                j["movement"], mState, position, endPos
            )
        );
    }


    // optional collision
    if (j.contains("collisionBehavior")) {
        builder.withCollision(
            StrategyFactory::createCollisionBehavior(j["collisionBehavior"], mState)
        );
    }
    auto proj = builder.build();
    if(j.contains("animation")) {
        proj->setMovingAnimation(
            StrategyFactory::createMovingAnimation(j["animation"], proj->position, StartPosition, EndPosition)
        );
    }
    if(j.contains("Damage"))
    {
        proj->setAttribute("Damage", j["Damage"].get<float>());
    }
    in.close();
    return proj;
}

Projectile2* ProjectileLoader::LoadRandomProjectile(sf::Vector2f StartPosition, sf::Vector2f EndPosition) {
    std::ifstream in{filePath};
    if (!in.is_open())
        throw std::runtime_error("Failed to open projectile file: " + filePath);

    json data;
    in >> data;
    in.close();

    if (data.empty())
        throw std::runtime_error("No projectiles in file: " + filePath);

    auto it = data.begin();
    std::advance(it, std::rand() % data.size());
    return LoadProjectile(it.key(), StartPosition, EndPosition);
}