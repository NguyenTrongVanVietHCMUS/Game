#include "Book/TileMap.hpp"
#include <fstream>

TileMap::TileMap()
{

}
TileMap::TileMap(const TileMap& map)
{
    this->File = File ; 
    this->loadFromFile(map.File) ; 
}

bool TileMap::loadFromFile(const std::string& jsonFile) {
    File = jsonFile ; 
    // Load JSON file
    std::ifstream file(jsonFile);
    if (!file.is_open()) {
        return false;
    }
    
    json mapData;
    file >> mapData;
    
    // Load tilesetsf
    for (auto& tilesetData : mapData["tilesets"]) {
        Tileset tileset;
        std::string imagePath = tilesetData["image"];
        // Resolve imagePath relative to the JSON file's directory
        std::filesystem::path jsonPath(jsonFile);
        std::filesystem::path jsonDir = jsonPath.parent_path();
        std::filesystem::path resolvedImagePath = jsonDir / imagePath;

        // Load the tileset texture from the resolved path
        if (!tileset.texture.loadFromFile(resolvedImagePath.string())) {
            return false;
        }
        
        tileset.firstGid = tilesetData["firstgid"];
        tileset.tileWidth = tilesetData["tilewidth"];
        tileset.tileHeight = tilesetData["tileheight"]; 
        tileset.columns = tilesetData["columns"];
        tileset.tileCount = tilesetData["tilecount"];
        tilesets.push_back(tileset);
    }
    
    // Load layers
    for (auto& layerData : mapData["layers"]) {
        if (layerData["type"] == "imagelayer") 
        {
            std::string imagePath = layerData["image"];
            // Resolve imagePath relative to the JSON file's directory
            std::filesystem::path jsonPath(jsonFile);
            std::filesystem::path jsonDir = jsonPath.parent_path();
            std::filesystem::path resolvedImagePath = jsonDir / imagePath;
            
            // Load the background texture
            sf::Texture backgroundTexture;
            if (!backgroundTexture.loadFromFile(resolvedImagePath.string())) {
                return false;
            }
            sf::Sprite backgroundSprite(backgroundTexture);

            backgroundSprite.setPosition(layerData["x"], layerData["y"]);
            backgroundSprites.push_back(backgroundSprite);
        }
        else if(layerData["type"] == "objectlayer")
        {
            
        }
    }
    return true;
}

TileMap::~TileMap() {
    // Destructor
}  
void TileMap::setLayerVisible(size_t layerIndex, bool visible) {
    if (layerIndex < layers.size()) {
        layers[layerIndex].visible = visible;
    }
}

bool TileMap::isLayerVisible(size_t layerIndex) const {
    return (layerIndex < layers.size()) ? layers[layerIndex].visible : false;
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (const auto& sprite : backgroundSprites) {
        target.draw(sprite, states);
    }
    // You may want to draw tile layers here as well
}
bool TileMap::handleEvent(const sf::Event& event) 
{
    return 0 ;
}
bool TileMap::update(sf::Time dt)
{
    return 0 ;  
}