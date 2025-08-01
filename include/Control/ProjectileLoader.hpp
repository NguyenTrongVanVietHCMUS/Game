#pragma once
#include <string>
#include <memory>
#include <nlohmann/json.hpp>
#include <Control/State.hpp>
#include <Control/ProjectileBuilder.hpp>

using json = nlohmann::json;

class ProjectileLoader {
    std::string filePath;
    State*      mState;
    json animationData;
public:
    ProjectileLoader(State* state, std::string path = "Media/Config/projectileList.json")
        : filePath(std::move(path)), mState(state) {}

    Projectile2* LoadProjectile(const std::string& name, sf::Vector2f StartPosition, sf::Vector2f EndPosition);
    Projectile2* LoadRandomProjectile(sf::Vector2f StartPosition, sf::Vector2f EndPosition);
};