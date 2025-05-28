#include "Book/TileMap.hpp"
#include<Control/Foreach.hpp>
#include <fstream>

TileMap::TileMap()
{

}
TileMap::TileMap(const TileMap& map)
{
    this->File = File ; 
    this->loadFromFile(map.File) ; 
}

TileMap::~TileMap() 
{
    // Destructor
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
    for (auto& tilesetData : mapData["tilesets"]) 
    {
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
    for (auto& layerData : mapData["layers"]) 
    {
        if (layerData["type"] == "imagelayer") 
        {
            std::string imagePath = layerData["image"];
            std::filesystem::path jsonPath(jsonFile);
            std::filesystem::path jsonDir = jsonPath.parent_path();
            std::filesystem::path resolvedImagePath = jsonDir / imagePath;
            // Resolve imagePath relative to the JSON file's directory
            
            // Load the background texture
            sf::Texture backgroundTexture;
            std::cout<< "Loading background texture from: " << resolvedImagePath.string() << std::endl;

            if (!backgroundTexture.loadFromFile(resolvedImagePath.string())) {
                return false;
            }
            // backgroundTexture.loadFromFile("Media/Assets/Maps/Title/background.png");
            layers.push_back(new ImageLayer());
            auto layer = static_cast<ImageLayer*>(layers.back());
            layer->type = Layer::ImageLayer ; 
            layer->name = layerData["name"];
            layer->visible = layerData["visible"];
            layer->texture.loadFromFile(resolvedImagePath.string()) ; 
            layer->sprite.setTexture(layer->texture);
            layer->sprite.setPosition(layerData["x"], layerData["y"]);
        }
        else if(layerData["type"] == "tilelayer")
        {
            layers.push_back(new TileLayer());
            auto layer = static_cast<TileLayer*>(layers.back()) ; 
            layer->type = Layer::TileLayer;
            layer->name = layerData["name"];
            layer->visible = layerData["visible"];
            layer->width = layerData["width"];
            layer->height = layerData["height"];
            layer->setPosition(layerData["x"], layerData["y"]);
            // Load tile data
            layer->vertices.resize(tilesets.size());
            for (size_t i = 0; i < tilesets.size(); ++i) {
                layer->vertices[i].setPrimitiveType(sf::Quads);
                layer->vertices[i].resize(layerData["data"].size() * 4);
            }
            layer->tilesets = tilesets;
            for(int i=0;i<layerData["data"].size();i++)
            {
                int tileId = layerData["data"][i];
                if(tileId == 0) continue ; // Skip empty tiles
                int tilesetIndex = 0 ; 
                for(size_t j=0;j<tilesets.size();j++)
                {
                    if(tileId >= tilesets[j].firstGid && tileId < tilesets[j].firstGid + tilesets[j].tileCount)
                    {
                        tilesetIndex = j ; 
                        break ; 
                    }
                }
                int localTileId = tileId - tilesets[tilesetIndex].firstGid ;
                int tileX = (localTileId % tilesets[tilesetIndex].columns) * tilesets[tilesetIndex].tileWidth;
                int tileY = (localTileId / tilesets[tilesetIndex].columns) * tilesets[tilesetIndex].tileHeight;
                
                // Calculate the position of the tile in the layer
                int x = (i % layer->width) * tilesets[tilesetIndex].tileWidth;
                int y = (i / layer->width) * tilesets[tilesetIndex].tileHeight;

                // Define the vertices for the tile
                sf::Vertex* quad = &layer->vertices[tilesetIndex][i * 4];
                quad[0].position = sf::Vector2f(x, y);
                quad[1].position = sf::Vector2f(x + tilesets[tilesetIndex].tileWidth, y);
                quad[2].position = sf::Vector2f(x + tilesets[tilesetIndex].tileWidth, y + tilesets[tilesetIndex].tileHeight);
                quad[3].position = sf::Vector2f(x, y + tilesets[tilesetIndex].tileHeight);

                // Set the texture coordinates
                quad[0].texCoords = sf::Vector2f(tileX, tileY);
                quad[1].texCoords = sf::Vector2f(tileX + tilesets[tilesetIndex].tileWidth, tileY);
                quad[2].texCoords = sf::Vector2f(tileX + tilesets[tilesetIndex].tileWidth, tileY + tilesets[tilesetIndex].tileHeight);
                quad[3].texCoords = sf::Vector2f(tileX, tileY + tilesets[tilesetIndex].tileHeight);
            }
        }
        else if(layerData["type"] == "objectlayer")
        {

        }
    }
    return true;
}

void TileMap::setLayerVisible(size_t layerIndex, bool visible) 
{
    if (layerIndex < layers.size()) {
        layers[layerIndex]->visible = visible;
    }
}

bool TileMap::isLayerVisible(size_t layerIndex) const 
{
    return (layerIndex < layers.size()) ? layers[layerIndex]->visible : false;
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states)const
{
    // std::cout<< "Drawing TileMap from file: " << File << std::endl;
    for(auto x : layers)
    {
        if(x->visible)
        {
            x->draw(target,states) ; 
        }
    }
    // You may want to draw tile layers here as well
}
bool TileMap::handleEvent(const sf::Event& event) 
{
    return 0 ; 
}
bool TileMap::update(sf::Time dt)
{
    return  0 ; 
}