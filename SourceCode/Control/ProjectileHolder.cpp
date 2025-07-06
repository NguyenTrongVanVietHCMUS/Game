#include "Control/ProjectileHolder.hpp"
#include <Control/State.hpp>
void ProjectileHolder::addProjectile(Projectile * projectile)
{
    projectiles.push_back(projectile);
    if(CurrentMap)
    {
        CurrentMap->pushEntity(projectile);
    }
}

void ProjectileHolder::removeProjectile(Projectile* projectile)
{
    auto it = std::remove_if(projectiles.begin(), projectiles.end(),
                             [projectile](const Projectile* p) { return p == projectile; });
    if (it != projectiles.end())
    {
        projectiles.erase(it, projectiles.end());
        delete projectile;
    }
}

void ProjectileHolder::updateProjectiles(sf::Time dt)
{


    for (auto& projectile : projectiles)
    {
        if (projectile && projectile->isFlagDestruct())
        {
            if (CurrentMap)
            {
                CurrentMap->popEntity(projectile); // Remove from the map's entity list
            }
            removeProjectile(projectile);
            
            updateProjectiles(dt); // Recurse to handle the next projectile after removal
            break; // Skip updating this projectile since it's marked for removal
        } else if (projectile)
        {
            projectile->update(dt);
        }
    }
}


void ProjectileHolder::drawProjectiles(sf::RenderTarget& target, sf::RenderStates states) const
{

    if(CurrentMap)
        return; // if map set , use map's draw function instead
    for (const auto& projectile : projectiles)
    {
        
        if (!projectile) continue; // Skip if the projectile is null
        projectile->draw(target, states);
    }
}

void ProjectileHolder::handleEvents(const sf::Event& event, sf::RenderWindow* window)
{
    if(CurrentMap)
        return; // if map set , use map's handleEvent function instead
    for (auto& projectile : projectiles)
    {
        projectile->handleEvent(event, window);
    }
}
