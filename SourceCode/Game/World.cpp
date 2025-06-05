#include<Book/World.hpp>
#include<algorithm>

World::World() {
    // Constructor implementation
}
World::~World() {   
    // Destructor implementation
}

void World::draw(sf::RenderTarget& target, sf::RenderStates states)const
{
    // Draw implementation
    map->draw(target, states); // Assuming map is a member of World
}
bool World::handleEvent(const sf::Event& event) {
    // Handle event implementation
    for (auto entity : entities) {
        if (entity->handleEvent(event)) {
            return true;
        }
    }
    return false;
}
bool World::update(sf::Time dt) {
    // Update implementation
    for (auto entity : entities) {
        entity->update(dt);
    }
    return true;
}