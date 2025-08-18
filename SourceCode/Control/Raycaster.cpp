#include<Control/Raycaster.hpp>

RaycastHit Raycaster::cast(
    const sf::Vector2f& origin,
    const sf::Vector2f& direction,
    float maxDistance) const
{
    RaycastHit hit;

    // 1) Compute end point of the ray in world‐space
    // normalize the direction vector
    float length = std::hypot(direction.x, direction.y);
    sf::Vector2f end;
    if(length > 0.0f)
    {
        // Normalize the direction vector
        sf::Vector2f normalizedDirection = direction / length;
        // Scale it to the maximum distance
        end = origin + normalizedDirection * maxDistance;
    } else {
        // If the direction is zero, return the origin as the end point
        end = origin + direction * maxDistance;
    }

    // 2) Convert origin and end to integer pixel coords
    int x0 = static_cast<int>(std::floor(origin.x));
    int y0 = static_cast<int>(std::floor(origin.y));
    int x1 = static_cast<int>(std::floor(end.x));
    int y1 = static_cast<int>(std::floor(end.y));

    // 3) Bresenham setup
    int dx =  std::abs(x1 - x0);
    int dy = -std::abs(y1 - y0);
    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;
    int err = dx + dy;

    // 4) Step along the line
    std::vector<Entity*> entities = currentWorld->GetEntities(Entity::Type::Object);
    while (true) {
        // World‐space sample point (center of pixel)
        float sampleX = x0 + 0.5f;
        float sampleY = y0 + 0.5f;

        // 5) Check each entity’s AABB for containment
        for (Entity* e : entities) {
            if(e->type == Entity::Type::Object){
                const sf::FloatRect& r = e->hitbox.hitbox;
                if (r.contains(sampleX, sampleY)) {
                    // We’ve hit something!
                    hit.entity   = e;
                    hit.position = { sampleX, sampleY };
                    hit.distance = std::hypot(sampleX - origin.x,
                                            sampleY - origin.y);
                    return hit;
                }
            }
        }

        // 6) If we’ve reached the end pixel, stop
        if (x0 == x1 && y0 == y1) break;

        // 7) Advance Bresenham error and coords
        int e2 = 2 * err;
        if (e2 >= dy) { err += dy; x0 += sx; }
        if (e2 <= dx) { err += dx; y0 += sy; }
    }

    // 8) No hit: return end‐point info
    hit.position = end;
    hit.distance = maxDistance;
    return hit;
}

std::set<Entity*> Raycaster::castGetEntities(const sf::Vector2f& startPosition,
                                                const sf::Vector2f& endPosition) const{
   RaycastHit hit;


    // 2) Convert origin and end to integer pixel coords
    int x0 = static_cast<int>(std::floor(startPosition.x));
    int y0 = static_cast<int>(std::floor(startPosition.y));
    int x1 = static_cast<int>(std::floor(endPosition.x));
    int y1 = static_cast<int>(std::floor(endPosition.y));

    // 3) Bresenham setup
    int dx =  std::abs(x1 - x0);
    int dy = -std::abs(y1 - y0);
    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;
    int err = dx + dy;

    // 4) Step along the line
    std::vector<Entity*> entities = currentWorld->GetEntities();
    std::set<Entity*> hitEntities; 
    while (true) {
        // World‐space sample point (center of pixel)
        float sampleX = x0 + 0.5f;
        float sampleY = y0 + 0.5f;

        // 5) Check each entity’s AABB for containment
        for (Entity* e : entities) {
    
            const sf::FloatRect& r = e->getHitbox().hitbox;
            if (r.contains(sampleX, sampleY)) {
                if(e->type == Entity::Type::Ally || e->type == Entity::Type::Enemy) {
                   
                    hitEntities.insert(e);
                } 
            }
        }

        // 6) If we’ve reached the end pixel, stop
        if (x0 == x1 && y0 == y1) break;

        // 7) Advance Bresenham error and coords
        int e2 = 2 * err;
        if (e2 >= dy) { err += dy; x0 += sx; }
        if (e2 <= dx) { err += dx; y0 += sy; }
    }

    return hitEntities;
}


bool Raycaster::intersectAABB(const sf::FloatRect& rect, 
                            const sf::Vector2f& rayOrigin, 
                            const sf::Vector2f& rayDirection, 
                            float &near) const
{
    // Calculate the intersection of the ray with the AABB
    float t1 = (rect.left - rayOrigin.x) / rayDirection.x;
    float t2 = (rect.left + rect.width - rayOrigin.x) / rayDirection.x;
    float t3 = (rect.top - rayOrigin.y) / rayDirection.y;
    float t4 = (rect.top + rect.height - rayOrigin.y) / rayDirection.y;

    float tmin = std::max(std::min(t1, t2), std::min(t3, t4));
    float tmax = std::min(std::max(t1, t2), std::max(t3, t4));

    if (tmax < 0 || tmin > tmax) {
        return false; // No intersection
    }

    near = tmin; // Distance to the intersection point
    return true; // Intersection occurred
}