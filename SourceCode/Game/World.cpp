#include<Book/World.hpp>
#include<algorithm>

World::World() 
{
    
}
World::~World() 
{   

}

void World::draw(sf::RenderTarget& target, sf::RenderStates states)const
{
    throw std::runtime_error("World::draw not implemented");
}
bool World::handleEvent(const sf::Event& event) {
    // Handle event implementation
    // for (auto entity : entities) {
    //     if (entity->handleEvent(event)) {
    //         return true;
    //     }
    // }
    throw std::runtime_error("World::handleEvent not implemented");
    return false;
}
bool World::update(sf::Time dt) {
    // Update implementation
    for (auto entity : entities) {
        entity->update(dt);
    }
    return true;
}