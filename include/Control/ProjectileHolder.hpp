#include <vector>
#include <memory>
#include <Book/Projectile.hpp>

class State;

#pragma once
class Entity;
class ProjectileHolder
{
public:
    void addProjectile(Projectile * projectile);
    void removeProjectile(Projectile* projectile);
    void updateProjectiles(sf::Time dt);
    void drawProjectiles(sf::RenderTarget& target, sf::RenderStates states) const;
    void handleEvents(const sf::Event& event, sf::RenderWindow* window);
    void setCurrentMap(State* map) { CurrentMap = map; }
private:
    std::vector<Projectile*> projectiles;
    State* CurrentMap = nullptr;
};
