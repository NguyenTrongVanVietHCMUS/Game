#include <Control/ResourceManager.hpp>

ResourceManager& ResourceManager::getInstance() {
    static ResourceManager instance;
    return instance;
}
ResourceManager::ResourceManager()
    : textures(), fonts(), sounds(), maps(),
    music()  // Initialize all members
{
    // Additional initialization if needed
}
// Template specializations for loading
template <>
void ResourceManager::load<sf::Texture, Textures::ID>(Textures::ID id, const std::string& path) {
    textures.load(id, path);
}

template <>
void ResourceManager::load<sf::Font, Fonts::ID>(Fonts::ID id, const std::string& path) {
    fonts.load(id, path);
}

template <>
void ResourceManager::load<TileMap, Map::ID>(Map::ID id, const std::string& path) {
    maps.load(id, path);
}

// Template specializations for getting resources
template <>
sf::Texture& ResourceManager::get<sf::Texture, Textures::ID>(Textures::ID id) {
    return textures.get(id);
}

template <>
sf::Font& ResourceManager::get<sf::Font, Fonts::ID>(Fonts::ID id) {
    return fonts.get(id);
}
template<> 
TileMap& ResourceManager::get<TileMap, Map::ID>(Map::ID id)
{
    return maps.get(id); 
}
// ... similar specializations for other types