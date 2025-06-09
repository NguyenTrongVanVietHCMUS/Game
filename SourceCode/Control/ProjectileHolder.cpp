#include "Control/ProjectileHolder.hpp"
void ProjectileHolder::addProjectile(std::unique_ptr<Projectile> projectile)
{
    projectiles.push_back(std::move(projectile));
}

void ProjectileHolder::removeProjectile(Projectile* projectile)
{
    auto it = std::remove_if(projectiles.begin(), projectiles.end(),
                             [projectile](const std::unique_ptr<Projectile>& p) { return p.get() == projectile; });
    if (it != projectiles.end())
    {
        projectiles.erase(it, projectiles.end());
    }
}

void ProjectileHolder::updateProjectiles(sf::Time dt)
{
    for (auto& projectile : projectiles)
    {
        if (projectile->isFlagDestruct())
        {
            std::cerr << "Projectile is marked for removal" << std::endl;
            removeProjectile(projectile.get());
            updateProjectiles(dt); // Recurse to handle the next projectile after removal
            return; // Skip updating this projectile since it's marked for removal
        }
        // Update the projectile
    
        projectile->update(dt);
    }
}

void ProjectileHolder::drawProjectiles(sf::RenderTarget& target, sf::RenderStates states) const
{

    for (const auto& projectile : projectiles)
    {
        
        if (!projectile) continue; // Skip if the projectile is null
        projectile->draw(target, states);
    }
}

void ProjectileHolder::handleEvents(const sf::Event& event)
{
    for (auto& projectile : projectiles)
    {
        projectile->handleEvent(event);
    }
}
