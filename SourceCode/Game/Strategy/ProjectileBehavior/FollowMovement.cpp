#include <Book/Strategy/ProjectileBehavior.hpp>

void FollowMovement::update(Projectile2& projectile, const sf::Time& dt)
{
    if (!Worldmap) return; // Ensure Worldmap is valid
 
    // Find the closest entity of the same type as the projectile's type
    Entity::Type TargetType;
    if(projectile.type == Entity::Type::AllyProjectile)
    {
        TargetType = Entity::Type::Enemy;
    } else TargetType = Entity::Type::Ally;
    target = Worldmap->GetClosestEntity(TargetType, projectile.getPosition());
    
    if (!target) 
    {
        projectile.position.x += speedX * dt.asSeconds();
        projectile.position.y += speedY * dt.asSeconds();
        projectile.updateHitboxOnPosition();
        return; // No target found
    }
    sf::Vector2f pos = projectile.getPosition();
    sf::Vector2f targetPos = target->getPosition();
    sf::Vector2f toTarget = targetPos - pos;

    float targetDist = std::sqrt(toTarget.x * toTarget.x + toTarget.y * toTarget.y);
    if (targetDist < 0.01f) return; // Already at target

    // Normalize vectors
    sf::Vector2f desiredDir = toTarget / targetDist;
    sf::Vector2f currentDir = sf::Vector2f(speedX, speedY);
    float currentMag = std::sqrt(currentDir.x * currentDir.x + currentDir.y * currentDir.y);
    if (currentMag < 0.01f) return; // No direction

    currentDir /= currentMag;

    // Calculate current and desired angles
    float currentAngle = std::atan2(currentDir.y, currentDir.x);
    float desiredAngle = std::atan2(desiredDir.y, desiredDir.x);

    // Angle difference [-pi, pi]
    float deltaAngle = desiredAngle - currentAngle;

    // Wrap angle to [-pi, pi]
    while (deltaAngle > 3.14f) deltaAngle -= 2 * 3.14f;
    while (deltaAngle < -3.14f) deltaAngle += 2 * 3.14f;

    // Clamp to CriticalAngle
    if (std::abs(deltaAngle) > CriticalAngle * dt.asSeconds())
        deltaAngle = (deltaAngle > 0 ? 1 : -1) * CriticalAngle * dt.asSeconds();

    // Apply new angle
    float newAngle = currentAngle + deltaAngle;
    speedX = std::cos(newAngle) * speed;
    speedY = std::sin(newAngle) * speed;

    projectile.position.x += speedX * dt.asSeconds();
    projectile.position.y += speedY * dt.asSeconds();
    projectile.updateHitboxOnPosition(); // Update the hitbox position based on the new position
}