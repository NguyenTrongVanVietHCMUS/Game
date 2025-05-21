#include "Book/TileMap.hpp"
#include <fstream>

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (size_t i = 0; i < layerVertices.size(); ++i) {
        if (layers[i].visible) {
            states.texture = &tilesets[0].texture; // Assuming single tileset
            target.draw(layerVertices[i], states);
        }
    }
}

bool TileMap::load(const std::string& jsonFile) {
    // Load JSON file
    std::ifstream file(jsonFile);
    if (!file.is_open()) {
        return false;
    }

    json mapData;
    file >> mapData;
    
    // Load tilesets
    for (auto& tilesetData : mapData["tilesets"]) {
        Tileset tileset;
        std::string imagePath = tilesetData["image"];
        
        // Fix path if needed (remove "../../../" etc.)
        size_t pos = imagePath.find_last_of("/\\");
        if (pos != std::string::npos) {
            imagePath = imagePath.substr(pos + 1);
        }
        
        if (!tileset.texture.loadFromFile("Media/Assets/TileSets/" + imagePath)) {
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
        if (layerData["type"] == "tilelayer") {
            TileLayer layer;
            layer.name = layerData["name"];
            layer.width = layerData["width"];
            layer.height = layerData["height"];
            layer.visible = layerData["visible"];
            layer.data = layerData["data"].get<std::vector<int>>();
            layers.push_back(layer);
        }
    }
    
    // Create vertex arrays for each layer
    layerVertices.resize(layers.size());
    
    for (size_t layerIdx = 0; layerIdx < layers.size(); ++layerIdx) {
        const auto& layer = layers[layerIdx];
        layerVertices[layerIdx].setPrimitiveType(sf::Quads);
        layerVertices[layerIdx].resize(layer.width * layer.height * 4);
        
        for (size_t i = 0; i < layer.width; ++i) {
            for (size_t j = 0; j < layer.height; ++j) {
                int tileID = layer.data[i + j * layer.width];
                
                if (tileID == 0) continue;
                
                // Find tileset
                Tileset* tileset = nullptr;
                for (auto& ts : tilesets) {
                    if (tileID >= ts.firstGid && tileID < ts.firstGid + ts.tileCount) {
                        tileset = &ts;
                        break;
                    }
                }
                
                if (!tileset) continue;
                
                // Calculate texture coordinates
                int relativeID = tileID - tileset->firstGid;
                int tu = relativeID % tileset->columns;
                int tv = relativeID / tileset->columns;
                
                // Get quad pointer
                sf::Vertex* quad = &layerVertices[layerIdx][(i + j * layer.width) * 4];
                
                // Set positions
                quad[0].position = sf::Vector2f(i * tileset->tileWidth, j * tileset->tileHeight);
                quad[1].position = sf::Vector2f((i + 1) * tileset->tileWidth, j * tileset->tileHeight);
                quad[2].position = sf::Vector2f((i + 1) * tileset->tileWidth, (j + 1) * tileset->tileHeight);
                quad[3].position = sf::Vector2f(i * tileset->tileWidth, (j + 1) * tileset->tileHeight);
                
                // Set texture coordinates
                quad[0].texCoords = sf::Vector2f(tu * tileset->tileWidth, tv * tileset->tileHeight);
                quad[1].texCoords = sf::Vector2f((tu + 1) * tileset->tileWidth, tv * tileset->tileHeight);
                quad[2].texCoords = sf::Vector2f((tu + 1) * tileset->tileWidth, (tv + 1) * tileset->tileHeight);
                quad[3].texCoords = sf::Vector2f(tu * tileset->tileWidth, (tv + 1) * tileset->tileHeight);
            }
        }
    }
    
    return true;
}

void TileMap::setLayerVisible(size_t layerIndex, bool visible) {
    if (layerIndex < layers.size()) {
        layers[layerIndex].visible = visible;
    }
}

bool TileMap::isLayerVisible(size_t layerIndex) const {
    return (layerIndex < layers.size()) ? layers[layerIndex].visible : false;
}