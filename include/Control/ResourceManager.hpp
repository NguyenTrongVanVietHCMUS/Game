#pragma once
#include <stdexcept>
#include <Control/ResourceIdentifiers.hpp>  // Contains your namespaced enums
#include<Control/SoundPlayer.hpp> 
#include<Control/MusicPlayer.hpp>
#include<Book/TileMap.hpp>
// Forward declarations
class ResourceManager {
public:
    // Delete copy/move operations
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;

    // Singleton access
    static ResourceManager& getInstance();

    // Load resources using type-specific enums
    template <typename ResourceType, typename Identifier>
    void load(Identifier id, const std::string& path);

    // Get resources with compile-time type safety
    template <typename ResourceType, typename Identifier>
    ResourceType& get(Identifier id);

    // Access resource holders directly

private:
    ResourceManager(); 
    ~ResourceManager() = default;

    // Resource holders
    TextureHolder textures;
    FontHolder fonts;
    MapHolder maps;
    MusicPlayer music;  // Handles streaming, not loaded resources
    SoundPlayer sounds;  // Plays sounds using loaded buffers
};