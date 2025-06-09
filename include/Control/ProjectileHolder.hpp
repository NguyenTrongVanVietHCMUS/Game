#include <vector>
#include <memory>
#include <Book/Projectile.hpp>

#pragma once

class ProjectileHolder
{
public:
    void addProjectile(std::unique_ptr<Projectile> projectile);
    void removeProjectile(Projectile* projectile);
    void updateProjectiles(sf::Time dt);
    void drawProjectiles(sf::RenderTarget& target, sf::RenderStates states) const;
    void handleEvents(const sf::Event& event);

private:
    std::vector<std::unique_ptr<Projectile>> projectiles;
};
