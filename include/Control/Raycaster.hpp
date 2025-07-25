#pragma once
#include<Book/Utility.hpp>
#include<Book/Entity.hpp>
#include<Control/State.hpp>
struct RaycastHit{
    Entity* entity = nullptr; // Pointer to the entity hit by the raycast
    sf::Vector2f position; // Position of the hit
    float distance = 0.0f; // Distance from the raycaster to the hit position};
};

class Raycaster {
private:
    State* currentWorld = nullptr;

public:
    Raycaster(State* world) : currentWorld(world) {}

    RaycastHit cast(const sf::Vector2f& origin, 
                     const sf::Vector2f& direction, 
                    float maxDistance = 2000.0f) const;

private:
    bool intersectAABB(const sf::FloatRect& rect, 
                       const sf::Vector2f& rayOrigin, 
                       const sf::Vector2f& rayDirection, 
                       float &near) const;
};