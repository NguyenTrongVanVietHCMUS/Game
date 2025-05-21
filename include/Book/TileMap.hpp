#pragma once
#include <Book/Utility.hpp> 
#include <nlohmann/json.hpp>
using json = nlohmann::json;

struct TileLayer {
    std::vector<int> data;
    std::string name;
    int width;
    int height;
    bool visible;
};

struct Tileset {
    sf::Texture texture;
    int firstGid;
    int tileWidth;
    int tileHeight;
    int columns;
    int tileCount;
};

class TileMap : public sf::Drawable {
private:
    std::vector<TileLayer> layers;
    std::vector<Tileset> tilesets;
    std::vector<sf::VertexArray> layerVertices;
    
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
    bool load(const std::string& jsonFile);
    void setLayerVisible(size_t layerIndex, bool visible);
    bool isLayerVisible(size_t layerIndex) const;
};
