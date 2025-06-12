#pragma once 
#include<Book/Utility.hpp>
#include<Book/Entity.hpp>
#include<Book/TileMap.hpp>
class World : public sf::Drawable
{

public : 
    World();
    ~World();
    
    // bool loadFromFile(const std::string& jsonFile);
    // void setLayerVisible(size_t layerIndex, bool visible);
    // bool isLayerVisible(size_t layerIndex) const;
}; 